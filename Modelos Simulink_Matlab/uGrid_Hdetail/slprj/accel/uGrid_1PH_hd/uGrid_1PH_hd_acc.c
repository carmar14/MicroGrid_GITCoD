#include "__cf_uGrid_1PH_hd.h"
#include <math.h>
#include "uGrid_1PH_hd_acc.h"
#include "uGrid_1PH_hd_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T
testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf =
* tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T uGrid_1PH_hd_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz ,
int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct * const
S ) { ssCallAccelRunBlock ( S , 38 , 131 , SS_CALL_MDL_OUTPUTS ) ; } void
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term ( SimStruct *
const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T
B_38_361_0 ; real_T B_38_369_0 ; real_T B_38_379_0 ; real_T B_38_387_0 ;
boolean_T resetIntg ; ZCEventType zcEvent ; real_T * lastU ; uint32_T
numCycles ; real_T rtb_B_38_397_0 ; real_T rtb_RealImagtoComplex_re ; real_T
rtb_RealImagtoComplex_im ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP
; X_uGrid_1PH_hd_T * _rtX ; PrevZCX_uGrid_1PH_hd_T * _rtZCE ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtZCE = ( ( PrevZCX_uGrid_1PH_hd_T * ) _ssGetPrevZCSigState ( S )
) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_38_1_0 = 0.0 ; _rtB -> B_38_1_0 +=
_rtP -> P_144 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtB -> B_38_2_0 = _rtP ->
P_145 * _rtB -> B_38_1_0 ; _rtB -> B_38_3_0 = _rtP -> P_146 * _rtB ->
B_38_2_0 ; _rtB -> B_38_4_0 = 0.0 ; _rtB -> B_38_4_0 += _rtP -> P_148 * _rtX
-> TransferFcn_CSTATE ; _rtB -> B_38_5_0 = _rtP -> P_149 * _rtB -> B_38_4_0 ;
_rtB -> B_38_6_0 = _rtB -> B_38_3_0 - _rtB -> B_38_5_0 ; _rtB -> B_38_16_0 =
0.0 ; _rtB -> B_38_16_0 += _rtP -> P_161 * _rtX -> Currentfilter_CSTATE ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_38_14_0 = _rtDW ->
itinit1_PreviousInput ; _rtB -> B_38_15_0 = _rtP -> P_159 * _rtB -> B_38_14_0
; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode = ( _rtB ->
B_38_16_0 > uGrid_1PH_hd_rtC ( S ) -> B_38_17_0 ) ; } _rtB -> B_38_19_0 =
_rtDW -> Compare_Mode ; _rtB -> B_38_20_0 = _rtDW -> itinit_PreviousInput ; }
if ( ssIsMajorTimeStep ( S ) ) { resetIntg = false ; zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & _rtZCE -> inti_Reset_ZCE , ( _rtB -> B_38_19_0 ) ) ;
if ( ( zcEvent != NO_ZCEVENT ) || ( _rtDW -> inti_IWORK != 0 ) ) { resetIntg
= true ; _rtX -> inti_CSTATE = _rtB -> B_38_20_0 ; } if ( resetIntg ) {
ssSetSolverNeedsReset ( S ) ; } if ( _rtX -> inti_CSTATE >= _rtP -> P_164 ) {
_rtX -> inti_CSTATE = _rtP -> P_164 ; } else { if ( _rtX -> inti_CSTATE <=
_rtP -> P_165 ) { _rtX -> inti_CSTATE = _rtP -> P_165 ; } } } _rtB ->
B_38_21_0 = _rtX -> inti_CSTATE ; _rtB -> B_38_22_0 = _rtP -> P_166 * _rtB ->
B_38_21_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S )
) { _rtDW -> LowerRelop1_Mode = ( _rtB -> B_38_22_0 > _rtB -> B_38_15_0 ) ;
_rtDW -> UpperRelop_Mode = ( _rtB -> B_38_22_0 < _rtB -> B_38_24_0 ) ; } _rtB
-> B_38_23_0 = _rtDW -> LowerRelop1_Mode ; _rtB -> B_38_25_0 = _rtDW ->
UpperRelop_Mode ; } if ( _rtB -> B_38_23_0 ) { _rtB -> B_38_27_0 = _rtB ->
B_38_15_0 ; } else { if ( _rtB -> B_38_25_0 ) { _rtB -> B_13_0_0 = _rtB ->
B_38_24_0 ; } else { _rtB -> B_13_0_0 = _rtB -> B_38_22_0 ; } _rtB ->
B_38_27_0 = _rtB -> B_13_0_0 ; } _rtB -> B_38_29_0 = 0.0 ; _rtB -> B_38_29_0
+= _rtP -> P_170 * _rtX -> StateSpace_CSTATE ; if ( _rtB -> B_38_30_0 > _rtP
-> P_174 ) { _rtB -> B_38_33_0 = muDoubleScalarExp ( ( 1.0 / _rtB ->
B_38_29_0 - 0.0034112229234180458 ) * 0.0 ) ; } else { _rtB -> B_38_33_0 =
_rtB -> B_38_31_0 ; } _rtB -> B_38_34_0 = - 0.0605295518538322 * _rtB ->
B_38_14_0 / ( _rtB -> B_38_14_0 - _rtB -> B_38_27_0 ) * _rtB -> B_38_27_0 *
_rtB -> B_38_33_0 ; _rtB -> B_38_36_0 = - _rtB -> B_38_19_0 *
0.0605295518538322 * _rtB -> B_38_16_0 * _rtB -> B_38_14_0 / ( _rtB ->
B_38_14_0 - _rtB -> B_38_27_0 ) * _rtB -> B_38_33_0 ; if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_38_39_0 = _rtP -> P_177 * _rtB -> B_38_14_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> LowerRelop1_Mode_g = ( _rtB -> B_38_22_0
> _rtB -> B_38_39_0 ) ; } _rtB -> B_38_40_0 = _rtDW -> LowerRelop1_Mode_g ;
_rtB -> B_38_41_0 = - _rtB -> B_38_39_0 * 0.999 * 0.1 * 0.9999 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> UpperRelop_Mode_g = ( _rtB -> B_38_22_0
< _rtB -> B_38_41_0 ) ; } _rtB -> B_38_42_0 = _rtDW -> UpperRelop_Mode_g ; if
( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_k = ( _rtB -> B_38_16_0 <
uGrid_1PH_hd_rtC ( S ) -> B_38_45_0 ) ; } _rtB -> B_38_47_0 = _rtDW ->
Compare_Mode_k ; } if ( _rtB -> B_38_40_0 ) { _rtB -> B_38_44_0 = _rtB ->
B_38_39_0 ; } else { if ( _rtB -> B_38_42_0 ) { _rtB -> B_14_0_0 = _rtB ->
B_38_41_0 ; } else { _rtB -> B_14_0_0 = _rtB -> B_38_22_0 ; } _rtB ->
B_38_44_0 = _rtB -> B_14_0_0 ; } switch ( ( int32_T ) _rtB -> B_38_37_0 ) {
case 1 : _rtB -> B_10_0_0 [ 0 ] = _rtB -> B_38_38_0 * _rtB -> B_38_44_0 ;
_rtB -> B_10_0_0 [ 1 ] = _rtB -> B_38_38_0 * _rtB -> B_38_16_0 ; _rtB ->
B_10_0_0 [ 2 ] = _rtB -> B_38_38_0 * _rtB -> B_38_47_0 ; _rtB -> B_10_0_0 [ 3
] = _rtB -> B_38_38_0 * _rtB -> B_38_14_0 ; _rtB -> B_38_55_0 = - _rtB ->
B_10_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_10_0_0 [ 1 ] * (
1.0339999999999974 / ( _rtB -> B_10_0_0 [ 0 ] + 0.10339999999999974 ) ) ;
break ; case 2 : _rtB -> B_9_0_0 [ 0 ] = _rtB -> B_38_48_0 * _rtB ->
B_38_44_0 ; _rtB -> B_9_0_0 [ 1 ] = _rtB -> B_38_48_0 * _rtB -> B_38_16_0 ;
_rtB -> B_9_0_0 [ 2 ] = _rtB -> B_38_48_0 * _rtB -> B_38_47_0 ; _rtB ->
B_9_0_0 [ 3 ] = _rtB -> B_38_48_0 * _rtB -> B_38_14_0 ; _rtB -> B_38_55_0 = -
_rtB -> B_9_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_9_0_0 [ 1 ] * _rtB ->
B_9_0_0 [ 3 ] / ( _rtB -> B_9_0_0 [ 3 ] * 0.1 + _rtB -> B_9_0_0 [ 0 ] ) ;
break ; case 3 : _rtB -> B_8_0_0 [ 0 ] = _rtB -> B_38_49_0 * _rtB ->
B_38_44_0 ; _rtB -> B_8_0_0 [ 1 ] = _rtB -> B_38_49_0 * _rtB -> B_38_16_0 ;
_rtB -> B_8_0_0 [ 2 ] = _rtB -> B_38_49_0 * _rtB -> B_38_47_0 ; _rtB ->
B_8_0_0 [ 3 ] = _rtB -> B_38_49_0 * _rtB -> B_38_14_0 ; _rtB -> B_38_55_0 = -
_rtB -> B_8_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_8_0_0 [ 1 ] * (
1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_8_0_0 [ 0 ] ) +
0.10339999999999974 ) ) ; break ; default : _rtB -> B_7_0_0 [ 0 ] = _rtB ->
B_38_50_0 * _rtB -> B_38_44_0 ; _rtB -> B_7_0_0 [ 1 ] = _rtB -> B_38_50_0 *
_rtB -> B_38_16_0 ; _rtB -> B_7_0_0 [ 2 ] = _rtB -> B_38_50_0 * _rtB ->
B_38_47_0 ; _rtB -> B_7_0_0 [ 3 ] = _rtB -> B_38_50_0 * _rtB -> B_38_14_0 ;
_rtB -> B_38_55_0 = - _rtB -> B_7_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_7_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_7_0_0
[ 0 ] ) + 0.10339999999999974 ) ) ; break ; } _rtB -> B_38_56_0 = _rtB ->
B_38_55_0 * _rtB -> B_38_33_0 ; _rtB -> B_38_58_0 = _rtX ->
Integrator2_CSTATE ; switch ( ( int32_T ) _rtB -> B_38_57_0 ) { case 1 : _rtB
-> B_38_60_0 = _rtB -> B_38_58_0 ; break ; case 2 : _rtB -> B_38_60_0 =
muDoubleScalarExp ( - 61.061946632469265 * _rtB -> B_38_27_0 ) *
83.400845004248509 ; break ; case 3 : _rtB -> B_38_60_0 = _rtB -> B_38_58_0 ;
break ; default : _rtB -> B_38_60_0 = _rtB -> B_38_58_0 ; break ; } _rtB ->
B_38_66_0 = 0.0 ; _rtB -> B_38_66_0 += _rtP -> P_189 * _rtX ->
Currentfilter1_CSTATE ; if ( _rtB -> B_38_67_0 > _rtP -> P_192 ) { _rtB ->
B_38_70_0 = muDoubleScalarExp ( ( 1.0 / _rtB -> B_38_29_0 -
0.0034112229234180458 ) * 0.0 ) * - _rtB -> B_38_65_0 * _rtB -> B_38_66_0 +
0.05 * _rtB -> B_38_66_0 ; } else { _rtB -> B_38_70_0 = _rtB -> B_38_68_0 ; }
_rtB -> B_38_71_0 = ( ( ( ( _rtB -> B_38_34_0 + _rtB -> B_38_36_0 ) + _rtB ->
B_38_56_0 ) + _rtB -> B_38_60_0 ) + - 0.0 * _rtB -> B_38_27_0 ) + _rtB ->
B_38_70_0 ; if ( _rtB -> B_38_72_0 > _rtP -> P_195 ) { _rtB -> B_38_75_0 = (
_rtB -> B_38_29_0 - 293.15 ) * 0.0 ; } else { _rtB -> B_38_75_0 = _rtB ->
B_38_73_0 ; } _rtB -> B_38_76_0 = ( _rtB -> B_38_11_0 + _rtB -> B_38_71_0 ) +
_rtB -> B_38_75_0 ; _rtB -> B_38_78_0 = _rtP -> P_196 * _rtB -> B_38_16_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> LowerRelop1_Mode_c = ( _rtB -> B_38_76_0 > _rtB -> B_38_7_0 ) ; } _rtB ->
B_38_77_0 = _rtDW -> LowerRelop1_Mode_c ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> UpperRelop_Mode_gu = ( _rtB -> B_38_76_0 < _rtB -> B_38_78_0 ) ; }
_rtB -> B_38_79_0 = _rtDW -> UpperRelop_Mode_gu ; } if ( _rtB -> B_38_77_0 )
{ _rtB -> B_38_81_0 = _rtB -> B_38_7_0 ; } else { if ( _rtB -> B_38_79_0 ) {
_rtB -> B_12_0_0 = _rtB -> B_38_78_0 ; } else { _rtB -> B_12_0_0 = _rtB ->
B_38_76_0 ; } _rtB -> B_38_81_0 = _rtB -> B_12_0_0 ; }
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S ) ; _rtB ->
B_38_132_0 = _rtP -> P_218 * _rtB ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 . B_0_9_0 ; ssCallAccelRunBlock (
S , 38 , 145 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 146 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_in , ( _rtB -> B_38_146_0 [ 7 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 29 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC = 4 ; } zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING
, & _rtZCE -> Subsystem_Trig_ZCE_k , ( _rtB -> B_38_146_0 [ 9 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 30 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_d = 4 ; } } } _rtB ->
B_38_149_0 = 0.0 ; _rtB -> B_38_149_0 += _rtP -> P_295 * _rtX -> Hw2_CSTATE [
3 ] ; _rtB -> B_38_150_0 = 0.0 ; _rtB -> B_38_150_0 += _rtP -> P_299 * _rtX
-> Hw6_CSTATE [ 3 ] ; _rtB -> B_38_151_0 = 0.0 ; _rtB -> B_38_151_0 += _rtP
-> P_303 * _rtX -> Hw1_CSTATE [ 3 ] ; _rtB -> B_38_152_0 = 0.0 ; _rtB ->
B_38_152_0 += _rtP -> P_307 * _rtX -> Hw3_CSTATE [ 3 ] ; ssCallAccelRunBlock
( S , 38 , 153 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_e , ( _rtB -> B_38_146_0 [ 3 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 27 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_e = 4 ; } }
ssCallAccelRunBlock ( S , 38 , 155 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_at , ( _rtB -> B_38_146_0 [ 1 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 26 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_j = 4 ; } } ssCallAccelRunBlock ( S , 38 , 157
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 158 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_38_159_0 = 0.0 ; _rtB -> B_38_159_0 +=
_rtP -> P_311 * _rtX -> Hw4_CSTATE [ 1 ] ; _rtB -> B_38_160_0 = 0.0 ; _rtB ->
B_38_160_0 += _rtP -> P_315 * _rtX -> Hw1_CSTATE_k [ 1 ] ;
ssCallAccelRunBlock ( S , 38 , 161 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 162 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_38_163_0 = 0.0 ; _rtB -> B_38_163_0 +=
_rtP -> P_319 * _rtX -> Hw7_CSTATE [ 1 ] ; _rtB -> B_38_164_0 = 0.0 ; _rtB ->
B_38_164_0 += _rtP -> P_323 * _rtX -> Hw3_CSTATE_e [ 1 ] ;
ssCallAccelRunBlock ( S , 38 , 165 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 166 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 167 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_38_211_0 = _rtB -> B_38_166_0 [ 0 ] + _rtB
-> B_38_210_0 ; } _rtB -> B_38_168_0 = _rtP -> P_339 * _rtB -> B_38_145_0 [ 6
] ; _rtB -> B_38_172_0 = 0.0 ; _rtB -> B_38_172_0 += _rtP -> P_341 * _rtX ->
TransferFcn_CSTATE_j ; _rtB -> B_38_173_0 = 0.0 ; _rtB -> B_38_173_0 += _rtP
-> P_343 * _rtX -> TransferFcn1_CSTATE ; _rtB -> B_38_174_0 = _rtP -> P_344 *
_rtB -> B_38_145_0 [ 1 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
B_38_225_0 = ( real_T ) ( ( _rtB -> B_38_211_0 != uGrid_1PH_hd_rtC ( S ) ->
B_38_212_0 ) && ( _rtB -> B_38_211_0 >= ( ( muDoubleScalarRem ( ssGetTaskTime
( S , 2 ) + _rtP -> P_351 , _rtP -> P_352 ) * _rtP -> P_353 * 2.0 - 1.0 ) +
1.0 ) * 0.5 ) ) * _rtP -> P_354 ; if ( ssGetTaskTime ( S , 2 ) < _rtP ->
P_355 ) { rtb_B_38_397_0 = _rtP -> P_356 ; } else { rtb_B_38_397_0 = _rtP ->
P_357 ; } _rtB -> B_38_227_0 = _rtB -> B_38_225_0 * rtb_B_38_397_0 ;
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime
( S , 2 ) < _rtP -> P_358 ) { rtb_B_38_397_0 = _rtP -> P_359 ; } else {
rtb_B_38_397_0 = _rtP -> P_360 ; } _rtB -> B_38_230_0 = _rtB -> B_1_0_1 *
rtb_B_38_397_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> Step_MODE =
( ssGetTaskTime ( S , 1 ) >= _rtP -> P_362 ) ; if ( _rtDW -> Step_MODE == 1 )
{ _rtB -> B_38_232_0 = _rtP -> P_364 ; } else { _rtB -> B_38_232_0 = _rtP ->
P_363 ; } } _rtB -> B_38_234_0 = rt_Lookup ( _rtP -> P_365 , 5 , ssGetT ( S )
, _rtP -> P_366 ) ; if ( _rtB -> B_38_231_0 >= _rtP -> P_367 ) { _rtB ->
B_38_235_0 = _rtB -> B_38_232_0 ; } else { _rtB -> B_38_235_0 = _rtB ->
B_38_234_0 ; } if ( ( _rtDW -> TimeStampA >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_38_236_0 = 0.0 ; } else {
rtb_B_38_397_0 = _rtDW -> TimeStampA ; lastU = & _rtDW -> LastUAtTimeA ; if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW -> TimeStampB <
ssGetT ( S ) ) { rtb_B_38_397_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S ) ) {
rtb_B_38_397_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_38_236_0 = ( _rtB -> B_38_234_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_38_397_0 ) ; } _rtB -> B_38_247_0 = _rtP -> P_369 * _rtB -> B_38_145_0
[ 8 ] ; _rtB -> B_38_251_0 = 0.0 ; _rtB -> B_38_251_0 += _rtP -> P_371 * _rtX
-> TransferFcn_CSTATE_g ; _rtB -> B_38_252_0 = 0.0 ; _rtB -> B_38_252_0 +=
_rtP -> P_373 * _rtX -> TransferFcn1_CSTATE_p ; _rtB -> B_38_253_0 = _rtP ->
P_374 * _rtB -> B_38_145_0 [ 3 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 290 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_38_291_0 = _rtB -> B_38_290_0 [ 0 ] + _rtB -> B_38_289_0 ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_38_305_0 = ( real_T ) ( ( _rtB ->
B_38_291_0 != uGrid_1PH_hd_rtC ( S ) -> B_38_292_0 ) && ( _rtB -> B_38_291_0
>= ( ( muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_395 , _rtP ->
P_396 ) * _rtP -> P_397 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_398 ; if
( ssGetTaskTime ( S , 2 ) < _rtP -> P_399 ) { rtb_B_38_397_0 = _rtP -> P_400
; } else { rtb_B_38_397_0 = _rtP -> P_401 ; } _rtB -> B_38_307_0 = _rtB ->
B_38_305_0 * rtb_B_38_397_0 ; ssCallAccelRunBlock ( S , 3 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_402 ) {
rtb_B_38_397_0 = _rtP -> P_403 ; } else { rtb_B_38_397_0 = _rtP -> P_404 ; }
_rtB -> B_38_310_0 = _rtB -> B_3_0_1 * rtb_B_38_397_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_c = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_406 ) ; if ( _rtDW -> Step_MODE_c == 1 ) { _rtB -> B_38_312_0 = _rtP ->
P_408 ; } else { _rtB -> B_38_312_0 = _rtP -> P_407 ; } } _rtB -> B_38_314_0
= rt_Lookup ( _rtP -> P_409 , 5 , ssGetT ( S ) , _rtP -> P_410 ) ; if ( _rtB
-> B_38_311_0 >= _rtP -> P_411 ) { _rtB -> B_38_315_0 = _rtB -> B_38_312_0 ;
} else { _rtB -> B_38_315_0 = _rtB -> B_38_314_0 ; } if ( ( _rtDW ->
TimeStampA_k >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_f >= ssGetT ( S ) ) )
{ _rtB -> B_38_316_0 = 0.0 ; } else { rtb_B_38_397_0 = _rtDW -> TimeStampA_k
; lastU = & _rtDW -> LastUAtTimeA_m ; if ( _rtDW -> TimeStampA_k < _rtDW ->
TimeStampB_f ) { if ( _rtDW -> TimeStampB_f < ssGetT ( S ) ) { rtb_B_38_397_0
= _rtDW -> TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } else { if (
_rtDW -> TimeStampA_k >= ssGetT ( S ) ) { rtb_B_38_397_0 = _rtDW ->
TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } _rtB -> B_38_316_0 = (
_rtB -> B_38_314_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_38_397_0 ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 327 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 328 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) { _rtB ->
B_38_329_0 [ 0 ] = _rtB -> B_29_0_0 [ 0 ] ; _rtB -> B_38_329_0 [ 1 ] = _rtB
-> B_29_0_0 [ 1 ] ; _rtB -> B_38_330_0 [ 0 ] = _rtB -> B_38_149_0 ; _rtB ->
B_38_330_0 [ 1 ] = _rtB -> B_38_150_0 ; } memcpy ( & _rtB -> B_38_331_0 [ 0 ]
, & _rtDW -> Memory1_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB
-> B_38_332_0 [ 0 ] = _rtDW -> Memory2_PreviousInput [ 0 ] ; _rtB ->
B_38_332_0 [ 1 ] = _rtDW -> Memory2_PreviousInput [ 1 ] ; } if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 336 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 16 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 38 , 338 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 339 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 38 , 340 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 341 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 343 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 38 , 344 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 345 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 38 , 346 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsSampleHit ( S , 3 , 0 ) ) { _rtB -> B_38_349_0 [ 0 ] = _rtB -> B_30_0_0 [
0 ] ; _rtB -> B_38_349_0 [ 1 ] = _rtB -> B_30_0_0 [ 1 ] ; _rtB -> B_38_350_0
[ 0 ] = _rtB -> B_38_151_0 ; _rtB -> B_38_350_0 [ 1 ] = _rtB -> B_38_152_0 ;
} memcpy ( & _rtB -> B_38_351_0 [ 0 ] , & _rtDW -> Memory3_PreviousInput [ 0
] , 200U * sizeof ( real_T ) ) ; _rtB -> B_38_352_0 [ 0 ] = _rtDW ->
Memory4_PreviousInput [ 0 ] ; _rtB -> B_38_352_0 [ 1 ] = _rtDW ->
Memory4_PreviousInput [ 1 ] ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 38 , 354 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 18 , 0 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_38_357_0 = 0.0 ; _rtB -> B_38_357_0 += _rtP -> P_425 * _rtX -> Hw2_CSTATE_p
[ 1 ] ; _rtB -> B_38_358_0 = _rtP -> P_427 * _rtB -> B_38_145_0 [ 5 ] ;
ssCallAccelRunBlock ( S , 38 , 359 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_38_360_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_429 ;
B_38_361_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_430 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_38_363_0 = _rtP -> P_431
; _rtB -> B_38_365_0 = _rtDW -> Memory_PreviousInput ; } if ( ssGetT ( S ) >=
_rtB -> B_38_363_0 ) { _rtB -> B_38_367_0 = ( _rtB -> B_38_360_0 - B_38_361_0
) * _rtP -> P_1 ; } else { _rtB -> B_38_367_0 = _rtB -> B_38_365_0 ; } _rtB
-> B_38_368_0 = _rtX -> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_434 ; B_38_369_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_h . Last , _rtDW ->
TransportDelay_IWORK_h . Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP
-> P_435 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_38_371_0 = _rtP -> P_436 ; _rtB -> B_38_373_0 = _rtDW
-> Memory_PreviousInput_f ; } if ( ssGetT ( S ) >= _rtB -> B_38_371_0 ) {
_rtB -> B_38_375_0 = ( _rtB -> B_38_368_0 - B_38_369_0 ) * _rtP -> P_0 ; }
else { _rtB -> B_38_375_0 = _rtB -> B_38_373_0 ; } rtb_RealImagtoComplex_re =
_rtB -> B_38_367_0 ; rtb_RealImagtoComplex_im = _rtB -> B_38_375_0 ; _rtB ->
B_38_378_0 = _rtX -> integrator_CSTATE_p ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_439 ; B_38_379_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_440 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_38_381_0 = _rtP -> P_441 ; _rtB -> B_38_383_0 = _rtDW
-> Memory_PreviousInput_p ; } if ( ssGetT ( S ) >= _rtB -> B_38_381_0 ) {
_rtB -> B_38_385_0 = ( _rtB -> B_38_378_0 - B_38_379_0 ) * _rtP -> P_3 ; }
else { _rtB -> B_38_385_0 = _rtB -> B_38_383_0 ; } _rtB -> B_38_386_0 = _rtX
-> integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_444 ; B_38_387_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_445 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_38_389_0 = _rtP -> P_446
; _rtB -> B_38_391_0 = _rtDW -> Memory_PreviousInput_k ; } if ( ssGetT ( S )
>= _rtB -> B_38_389_0 ) { _rtB -> B_38_393_0 = ( _rtB -> B_38_386_0 -
B_38_387_0 ) * _rtP -> P_2 ; } else { _rtB -> B_38_393_0 = _rtB -> B_38_391_0
; } rtb_B_38_397_0 = muDoubleScalarHypot ( rtb_RealImagtoComplex_re ,
rtb_RealImagtoComplex_im ) * muDoubleScalarHypot ( _rtB -> B_38_385_0 , _rtB
-> B_38_393_0 ) * _rtP -> P_448 ; rtb_RealImagtoComplex_re = ( _rtP -> P_449
* muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im , rtb_RealImagtoComplex_re )
- _rtP -> P_450 * muDoubleScalarAtan2 ( _rtB -> B_38_393_0 , _rtB ->
B_38_385_0 ) ) * _rtP -> P_451 ; _rtB -> B_38_403_0 = rtb_B_38_397_0 *
muDoubleScalarCos ( rtb_RealImagtoComplex_re ) ; _rtB -> B_38_405_0 =
rtb_B_38_397_0 * muDoubleScalarSin ( rtb_RealImagtoComplex_re ) ;
ssCallAccelRunBlock ( S , 38 , 406 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_38_407_0 = _rtP -> P_452 * _rtB -> B_38_145_0 [ 0 ] ; ssCallAccelRunBlock (
S , 38 , 408 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_38_410_0 = muDoubleScalarSin
( _rtP -> P_456 * ssGetTaskTime ( S , 0 ) + _rtP -> P_457 ) * _rtP -> P_454 +
_rtP -> P_455 ; if ( ( _rtDW -> TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB_a >= ssGetT ( S ) ) ) { _rtB -> B_38_411_0 = 0.0 ; } else {
rtb_B_38_397_0 = _rtDW -> TimeStampA_b ; lastU = & _rtDW -> LastUAtTimeA_f ;
if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { if ( _rtDW ->
TimeStampB_a < ssGetT ( S ) ) { rtb_B_38_397_0 = _rtDW -> TimeStampB_a ;
lastU = & _rtDW -> LastUAtTimeB_n ; } } else { if ( _rtDW -> TimeStampA_b >=
ssGetT ( S ) ) { rtb_B_38_397_0 = _rtDW -> TimeStampB_a ; lastU = & _rtDW ->
LastUAtTimeB_n ; } } _rtB -> B_38_411_0 = ( _rtB -> B_38_410_0 - * lastU ) /
( ssGetT ( S ) - rtb_B_38_397_0 ) ; } _rtB -> B_38_412_0 = _rtB -> B_38_409_0
* _rtB -> B_38_411_0 ; _rtB -> B_38_413_0 = _rtB -> B_38_357_0 + _rtB ->
B_38_412_0 ; _rtB -> B_38_414_0 = 0.0 ; _rtB -> B_38_414_0 += _rtP -> P_460 *
_rtX -> Hi_Pass1_CSTATE ; _rtB -> B_38_414_0 += _rtP -> P_461 * _rtB ->
B_38_413_0 ; _rtB -> B_38_415_0 = 0.0 ; _rtB -> B_38_415_0 += _rtP -> P_465 *
_rtX -> Hw5_CSTATE [ 1 ] ; _rtB -> B_38_416_0 = _rtB -> B_38_415_0 + _rtB ->
B_38_357_0 ; _rtB -> B_38_417_0 = _rtB -> B_38_414_0 - _rtB -> B_38_416_0 ;
_rtB -> B_38_419_0 = 0.0 ; _rtB -> B_38_419_0 += _rtP -> P_469 [ 0 ] * _rtX
-> TransferFcn1_CSTATE_e [ 0 ] ; _rtB -> B_38_419_0 += _rtP -> P_469 [ 1 ] *
_rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtB -> B_38_422_0 = ( _rtP -> P_467 *
_rtB -> B_38_417_0 + _rtB -> B_38_419_0 ) + _rtB -> B_38_421_0 ;
ssCallAccelRunBlock ( S , 38 , 423 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_38_424_0 = 0.0 ; _rtB -> B_38_424_0 += _rtP -> P_473 * _rtX -> Hw6_CSTATE_f
[ 1 ] ; ssCallAccelRunBlock ( S , 38 , 425 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 5 , 0 ) ) { rtb_B_38_397_0 = ssGetTaskTime ( S , 5 ) ; if
( ssGetTNextWasAdjusted ( S , 5 ) ) { _rtDW -> nextTime =
_ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled != 0 ) { _rtDW
-> justEnabled = 0 ; if ( rtb_B_38_397_0 >= _rtP -> P_478 ) {
rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_478 ) / _rtP -> P_476
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_476 + _rtP ->
P_478 ) + _rtP -> P_477 * _rtP -> P_476 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue = 0 ; _rtDW ->
nextTime = ( real_T ) ( numCycles + 1U ) * _rtP -> P_476 + _rtP -> P_478 ; }
} else { _rtDW -> numCompleteCycles = _rtP -> P_478 != 0.0 ? - 1 : 0 ; _rtDW
-> currentValue = 0 ; _rtDW -> nextTime = _rtP -> P_478 ; } } else { if (
_rtDW -> nextTime <= rtb_B_38_397_0 ) { if ( _rtDW -> currentValue == 1 ) {
_rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW ->
numCompleteCycles + 1LL ) * _rtP -> P_476 + _rtP -> P_478 ; } else { _rtDW ->
numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ( _rtP
-> P_477 * _rtP -> P_476 * 0.01 + ( real_T ) _rtDW -> numCompleteCycles *
_rtP -> P_476 ) + _rtP -> P_478 ; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW
-> nextTime ) ; if ( _rtDW -> currentValue == 1 ) { _rtB -> B_38_426_0 = _rtP
-> P_475 ; } else { _rtB -> B_38_426_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1
, 0 ) && ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_i , ( _rtB ->
B_38_426_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 32
, 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_eb = 4 ; } } if
( ssIsSampleHit ( S , 6 , 0 ) ) { rtb_B_38_397_0 = ssGetTaskTime ( S , 6 ) ;
if ( ssGetTNextWasAdjusted ( S , 6 ) ) { _rtDW -> nextTime_e =
_ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW -> justEnabled_l != 0 ) { _rtDW
-> justEnabled_l = 0 ; if ( rtb_B_38_397_0 >= _rtP -> P_486 ) {
rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_486 ) / _rtP -> P_484
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_j = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_484 + _rtP ->
P_486 ) + _rtP -> P_485 * _rtP -> P_484 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_d = 1 ; _rtDW ->
nextTime_e = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_d = 0
; _rtDW -> nextTime_e = ( real_T ) ( numCycles + 1U ) * _rtP -> P_484 + _rtP
-> P_486 ; } } else { _rtDW -> numCompleteCycles_j = _rtP -> P_486 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = _rtP -> P_486 ; }
} else { if ( _rtDW -> nextTime_e <= rtb_B_38_397_0 ) { if ( _rtDW ->
currentValue_d == 1 ) { _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = (
real_T ) ( _rtDW -> numCompleteCycles_j + 1LL ) * _rtP -> P_484 + _rtP ->
P_486 ; } else { _rtDW -> numCompleteCycles_j ++ ; _rtDW -> currentValue_d =
1 ; _rtDW -> nextTime_e = ( _rtP -> P_485 * _rtP -> P_484 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_j * _rtP -> P_484 ) + _rtP -> P_486 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_e ) ; if ( _rtDW ->
currentValue_d == 1 ) { _rtB -> B_38_433_0 = _rtP -> P_483 ; } else { _rtB ->
B_38_433_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_a , ( _rtB -> B_38_433_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 33 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_o = 4 ; } } if ( ssIsSampleHit ( S , 8 , 0 ) ) {
rtb_B_38_397_0 = ssGetTaskTime ( S , 8 ) ; if ( ssGetTNextWasAdjusted ( S , 8
) ) { _rtDW -> nextTime_f = _ssGetVarNextHitTime ( S , 3 ) ; } if ( _rtDW ->
justEnabled_k != 0 ) { _rtDW -> justEnabled_k = 0 ; if ( rtb_B_38_397_0 >=
_rtP -> P_494 ) { rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_494
) / _rtP -> P_492 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_o = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_492 + _rtP ->
P_494 ) + _rtP -> P_493 * _rtP -> P_492 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_a = 1 ; _rtDW ->
nextTime_f = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_a = 0
; _rtDW -> nextTime_f = ( real_T ) ( numCycles + 1U ) * _rtP -> P_492 + _rtP
-> P_494 ; } } else { _rtDW -> numCompleteCycles_o = _rtP -> P_494 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = _rtP -> P_494 ; }
} else { if ( _rtDW -> nextTime_f <= rtb_B_38_397_0 ) { if ( _rtDW ->
currentValue_a == 1 ) { _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = (
real_T ) ( _rtDW -> numCompleteCycles_o + 1LL ) * _rtP -> P_492 + _rtP ->
P_494 ; } else { _rtDW -> numCompleteCycles_o ++ ; _rtDW -> currentValue_a =
1 ; _rtDW -> nextTime_f = ( _rtP -> P_493 * _rtP -> P_492 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_o * _rtP -> P_492 ) + _rtP -> P_494 ; } } }
_ssSetVarNextHitTime ( S , 3 , _rtDW -> nextTime_f ) ; if ( _rtDW ->
currentValue_a == 1 ) { _rtB -> B_38_440_0 = _rtP -> P_491 ; } else { _rtB ->
B_38_440_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_d , ( _rtB -> B_38_440_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 35 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_p = 4 ; } } _rtB -> B_38_447_0 = _rtP -> P_499 * _rtB
-> B_38_145_0 [ 7 ] ; _rtB -> B_38_451_0 = 0.0 ; _rtB -> B_38_451_0 += _rtP
-> P_501 * _rtX -> TransferFcn_CSTATE_m ; _rtB -> B_38_452_0 = 0.0 ; _rtB ->
B_38_452_0 += _rtP -> P_503 * _rtX -> TransferFcn1_CSTATE_l ; _rtB ->
B_38_453_0 = _rtP -> P_504 * _rtB -> B_38_145_0 [ 2 ] ; _rtB -> B_38_457_0 =
_rtP -> P_505 * _rtB -> B_38_145_0 [ 9 ] ; _rtB -> B_38_461_0 = 0.0 ; _rtB ->
B_38_461_0 += _rtP -> P_507 * _rtX -> TransferFcn2_CSTATE ; _rtB ->
B_38_495_0 = _rtB -> B_38_422_0 + _rtB -> B_38_494_0 ; if ( ssIsSampleHit ( S
, 2 , 0 ) ) { _rtB -> B_38_509_0 = ( real_T ) ( ( _rtB -> B_38_495_0 !=
uGrid_1PH_hd_rtC ( S ) -> B_38_496_0 ) && ( _rtB -> B_38_495_0 >= ( (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_514 , _rtP -> P_515 )
* _rtP -> P_516 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_517 ; if (
ssGetTaskTime ( S , 2 ) < _rtP -> P_518 ) { rtb_B_38_397_0 = _rtP -> P_519 ;
} else { rtb_B_38_397_0 = _rtP -> P_520 ; } _rtB -> B_38_511_0 = _rtB ->
B_38_509_0 * rtb_B_38_397_0 ; ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_521 ) {
rtb_B_38_397_0 = _rtP -> P_522 ; } else { rtb_B_38_397_0 = _rtP -> P_523 ; }
_rtB -> B_38_514_0 = _rtB -> B_2_0_1 * rtb_B_38_397_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_f = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_525 ) ; if ( _rtDW -> Step_MODE_f == 1 ) { _rtB -> B_38_516_0 = _rtP ->
P_527 ; } else { _rtB -> B_38_516_0 = _rtP -> P_526 ; } } _rtB -> B_38_518_0
= rt_Lookup ( _rtP -> P_528 , 5 , ssGetT ( S ) , _rtP -> P_529 ) ; if ( _rtB
-> B_38_515_0 >= _rtP -> P_530 ) { _rtB -> B_38_519_0 = _rtB -> B_38_516_0 ;
} else { _rtB -> B_38_519_0 = _rtB -> B_38_518_0 ; } if ( ( _rtDW ->
TimeStampA_n >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_m >= ssGetT ( S ) ) )
{ _rtB -> B_38_520_0 = 0.0 ; } else { rtb_B_38_397_0 = _rtDW -> TimeStampA_n
; lastU = & _rtDW -> LastUAtTimeA_ma ; if ( _rtDW -> TimeStampA_n < _rtDW ->
TimeStampB_m ) { if ( _rtDW -> TimeStampB_m < ssGetT ( S ) ) { rtb_B_38_397_0
= _rtDW -> TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } else { if (
_rtDW -> TimeStampA_n >= ssGetT ( S ) ) { rtb_B_38_397_0 = _rtDW ->
TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } _rtB -> B_38_520_0 = (
_rtB -> B_38_518_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_38_397_0 ) ; } _rtB
-> B_38_535_0 = ( muDoubleScalarSin ( _rtP -> P_534 * ssGetTaskTime ( S , 0 )
+ _rtP -> P_535 ) * _rtP -> P_532 + _rtP -> P_533 ) * _rtB -> B_38_407_0 ;
_rtB -> B_38_537_0 = ( muDoubleScalarSin ( _rtP -> P_538 * ssGetTaskTime ( S
, 0 ) + _rtP -> P_539 ) * _rtP -> P_536 + _rtP -> P_537 ) * _rtB ->
B_38_407_0 ; _rtB -> B_38_539_0 = ( muDoubleScalarSin ( _rtP -> P_542 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_543 ) * _rtP -> P_540 + _rtP -> P_541 ) *
_rtB -> B_38_358_0 ; _rtB -> B_38_541_0 = ( muDoubleScalarSin ( _rtP -> P_546
* ssGetTaskTime ( S , 0 ) + _rtP -> P_547 ) * _rtP -> P_544 + _rtP -> P_545 )
* _rtB -> B_38_358_0 ; ssCallAccelRunBlock ( S , 38 , 542 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 543 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_38_547_0 = _rtP -> P_548 * _rtB ->
B_38_145_0 [ 10 ] ; ssCallAccelRunBlock ( S , 38 , 548 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_38_550_0 = _rtB -> B_38_81_0 - _rtP -> P_549 * _rtB ->
B_38_547_0 ; ssCallAccelRunBlock ( S , 38 , 551 , SS_CALL_MDL_OUTPUTS ) ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_38_552_0 = _rtP -> P_550 * _rtB
-> B_38_14_0 ; } _rtB -> B_38_553_0 = ( 1.0 - _rtB -> B_38_27_0 / _rtB ->
B_38_552_0 ) * 100.0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_38_553_0 >= _rtP -> P_551 ? 1 : _rtB ->
B_38_553_0 > _rtP -> P_552 ? 0 : - 1 ; } _rtB -> B_38_554_0 = _rtDW ->
Saturation_MODE == 1 ? _rtP -> P_551 : _rtDW -> Saturation_MODE == - 1 ? _rtP
-> P_552 : _rtB -> B_38_553_0 ; ssCallAccelRunBlock ( S , 38 , 555 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 10 , 0 ) ) { rtb_B_38_397_0
= ssGetTaskTime ( S , 10 ) ; if ( ssGetTNextWasAdjusted ( S , 10 ) ) { _rtDW
-> nextTime_i = _ssGetVarNextHitTime ( S , 5 ) ; } if ( _rtDW ->
justEnabled_m != 0 ) { _rtDW -> justEnabled_m = 0 ; if ( rtb_B_38_397_0 >=
_rtP -> P_556 ) { rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_556
) / _rtP -> P_554 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_f = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_554 + _rtP ->
P_556 ) + _rtP -> P_555 * _rtP -> P_554 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_h = 1 ; _rtDW ->
nextTime_i = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_h = 0
; _rtDW -> nextTime_i = ( real_T ) ( numCycles + 1U ) * _rtP -> P_554 + _rtP
-> P_556 ; } } else { _rtDW -> numCompleteCycles_f = _rtP -> P_556 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = _rtP -> P_556 ; }
} else { if ( _rtDW -> nextTime_i <= rtb_B_38_397_0 ) { if ( _rtDW ->
currentValue_h == 1 ) { _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = (
real_T ) ( _rtDW -> numCompleteCycles_f + 1LL ) * _rtP -> P_554 + _rtP ->
P_556 ; } else { _rtDW -> numCompleteCycles_f ++ ; _rtDW -> currentValue_h =
1 ; _rtDW -> nextTime_i = ( _rtP -> P_555 * _rtP -> P_554 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_f * _rtP -> P_554 ) + _rtP -> P_556 ; } } }
_ssSetVarNextHitTime ( S , 5 , _rtDW -> nextTime_i ) ; if ( _rtDW ->
currentValue_h == 1 ) { _rtB -> B_38_556_0 = _rtP -> P_553 ; } else { _rtB ->
B_38_556_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE , ( _rtB -> B_38_556_0 ) ) ; if ( zcEvent != NO_ZCEVENT )
{ ssCallAccelRunBlock ( S , 37 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_m = 4 ; } } if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Abs_MODE = ( _rtB -> B_38_547_0 >= 0.0 ) ; } _rtB -> B_38_572_0 = _rtDW ->
Abs_MODE > 0 ? _rtB -> B_38_547_0 : - _rtB -> B_38_547_0 ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_i =
( _rtB -> B_38_547_0 < uGrid_1PH_hd_rtC ( S ) -> B_38_573_0 ) ; } _rtB ->
B_38_576_0 = _rtP -> P_565 * ( real_T ) _rtDW -> Compare_Mode_i ; } _rtB ->
B_38_577_0 = _rtB -> B_38_576_0 - _rtB -> B_38_58_0 ; _rtB -> B_38_578_0 =
_rtB -> B_38_572_0 * _rtB -> B_38_577_0 ; _rtB -> B_38_579_0 = _rtP -> P_566
* _rtB -> B_38_578_0 ; _rtB -> B_38_583_0 = _rtP -> P_568 * _rtB -> B_38_27_0
; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE_d = ( _rtB -> B_38_66_0
>= 0.0 ) ; } _rtB -> B_38_584_0 = _rtDW -> Abs_MODE_d > 0 ? _rtB -> B_38_66_0
: - _rtB -> B_38_66_0 ; _rtB -> B_38_585_0 = 0.05 * _rtB -> B_38_66_0 + -
_rtB -> B_38_71_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs1_MODE = (
_rtB -> B_38_585_0 >= 0.0 ) ; } _rtB -> B_38_586_0 = _rtDW -> Abs1_MODE > 0 ?
_rtB -> B_38_585_0 : - _rtB -> B_38_585_0 ; if ( ssIsSampleHit ( S , 1 , 0 )
) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_e = ( _rtB ->
B_38_66_0 < uGrid_1PH_hd_rtC ( S ) -> B_38_587_0 ) ; } _rtB -> B_38_590_0 =
_rtP -> P_570 * ( real_T ) _rtDW -> Compare_Mode_e ; } _rtB -> B_38_592_0 =
_rtB -> B_38_584_0 * _rtB -> B_38_586_0 ; _rtB -> B_38_593_0 = ( 0.0 * _rtB
-> B_38_584_0 * _rtB -> B_38_29_0 + _rtB -> B_38_590_0 ) + _rtB -> B_38_592_0
; _rtB -> B_38_596_0 = 0.0 ; _rtB -> B_38_596_0 += _rtP -> P_575 * _rtX ->
TransferFcn1_CSTATE_g ; _rtB -> B_38_597_0 = _rtP -> P_576 * _rtB ->
B_38_596_0 ; _rtB -> B_38_598_0 = _rtB -> B_38_581_0 + _rtB -> B_38_597_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_h , ( _rtB ->
B_38_146_0 [ 11 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock (
S , 31 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_k = 4 ; }
} ssCallAccelRunBlock ( S , 19 , 0 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_d4 , ( _rtB -> B_38_146_0 [ 5 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 28 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_l = 4 ; } } _rtB -> B_38_605_0 = _rtP -> P_577
* _rtB -> B_28_0_0 [ 1 ] ; ssCallAccelRunBlock ( S , 21 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 609 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 38 , 610 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 611 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 38 , 612 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 20 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 616 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 38 , 617 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 7 , 0 ) ) { rtb_B_38_397_0 = ssGetTaskTime ( S , 7 ) ; if
( ssGetTNextWasAdjusted ( S , 7 ) ) { _rtDW -> nextTime_j =
_ssGetVarNextHitTime ( S , 2 ) ; } if ( _rtDW -> justEnabled_j != 0 ) { _rtDW
-> justEnabled_j = 0 ; if ( rtb_B_38_397_0 >= _rtP -> P_585 ) {
rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_585 ) / _rtP -> P_583
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_h = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_583 + _rtP ->
P_585 ) + _rtP -> P_584 * _rtP -> P_583 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_n = 1 ; _rtDW ->
nextTime_j = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_n = 0
; _rtDW -> nextTime_j = ( real_T ) ( numCycles + 1U ) * _rtP -> P_583 + _rtP
-> P_585 ; } } else { _rtDW -> numCompleteCycles_h = _rtP -> P_585 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = _rtP -> P_585 ; }
} else { if ( _rtDW -> nextTime_j <= rtb_B_38_397_0 ) { if ( _rtDW ->
currentValue_n == 1 ) { _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = (
real_T ) ( _rtDW -> numCompleteCycles_h + 1LL ) * _rtP -> P_583 + _rtP ->
P_585 ; } else { _rtDW -> numCompleteCycles_h ++ ; _rtDW -> currentValue_n =
1 ; _rtDW -> nextTime_j = ( _rtP -> P_584 * _rtP -> P_583 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_h * _rtP -> P_583 ) + _rtP -> P_585 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime_j ) ; if ( _rtDW ->
currentValue_n == 1 ) { _rtB -> B_38_618_0 = _rtP -> P_582 ; } else { _rtB ->
B_38_618_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_o , ( _rtB -> B_38_618_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 34 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_b = 4 ; } } if ( ssIsSampleHit ( S , 9 , 0 ) ) {
rtb_B_38_397_0 = ssGetTaskTime ( S , 9 ) ; if ( ssGetTNextWasAdjusted ( S , 9
) ) { _rtDW -> nextTime_l = _ssGetVarNextHitTime ( S , 4 ) ; } if ( _rtDW ->
justEnabled_o != 0 ) { _rtDW -> justEnabled_o = 0 ; if ( rtb_B_38_397_0 >=
_rtP -> P_593 ) { rtb_RealImagtoComplex_re = ( rtb_B_38_397_0 - _rtP -> P_593
) / _rtP -> P_591 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_hh = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_591 + _rtP ->
P_593 ) + _rtP -> P_592 * _rtP -> P_591 / 100.0 ; if ( rtb_B_38_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_f = 1 ; _rtDW ->
nextTime_l = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_f = 0
; _rtDW -> nextTime_l = ( real_T ) ( numCycles + 1U ) * _rtP -> P_591 + _rtP
-> P_593 ; } } else { _rtDW -> numCompleteCycles_hh = _rtP -> P_593 != 0.0 ?
- 1 : 0 ; _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = _rtP -> P_593 ;
} } else { if ( _rtDW -> nextTime_l <= rtb_B_38_397_0 ) { if ( _rtDW ->
currentValue_f == 1 ) { _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = (
real_T ) ( _rtDW -> numCompleteCycles_hh + 1LL ) * _rtP -> P_591 + _rtP ->
P_593 ; } else { _rtDW -> numCompleteCycles_hh ++ ; _rtDW -> currentValue_f =
1 ; _rtDW -> nextTime_l = ( _rtP -> P_592 * _rtP -> P_591 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_hh * _rtP -> P_591 ) + _rtP -> P_593 ; } } }
_ssSetVarNextHitTime ( S , 4 , _rtDW -> nextTime_l ) ; if ( _rtDW ->
currentValue_f == 1 ) { _rtB -> B_38_625_0 = _rtP -> P_590 ; } else { _rtB ->
B_38_625_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_f , ( _rtB -> B_38_625_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 36 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_g = 4 ; } } if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 38 , 632 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 38 , 633 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 38 , 634 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_38_640_0 = 0.0 ; _rtB -> B_38_640_0 += _rtP -> P_601 * _rtX ->
Actuador1_CSTATE ; _rtB -> B_38_641_0 = _rtP -> P_602 * _rtB -> B_38_640_0 ;
{ real_T * * uBuffer = ( real_T * * ) & _rtDW -> MotordeCombustin1_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_603 ; _rtB -> B_38_642_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Last , _rtDW -> MotordeCombustin1_IWORK . Tail ,
_rtDW -> MotordeCombustin1_IWORK . Head , _rtP -> P_604 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_38_643_0 = _rtB -> B_38_642_0 - _rtB -> B_38_638_0 ; _rtB ->
B_38_644_0 = _rtP -> P_605 * _rtB -> B_38_145_0 [ 4 ] ; _rtB -> B_38_648_0 =
_rtB -> B_38_639_0 - _rtB -> B_38_6_0 ; _rtB -> B_38_649_0 = _rtP -> P_606 *
_rtB -> B_38_648_0 ; _rtB -> B_38_650_0 = _rtX -> Filter_CSTATE ; _rtB ->
B_38_651_0 = _rtB -> B_38_649_0 - _rtB -> B_38_650_0 ; _rtB -> B_38_652_0 =
_rtP -> P_608 * _rtB -> B_38_651_0 ; _rtB -> B_38_653_0 = _rtP -> P_609 *
_rtB -> B_38_648_0 ; _rtB -> B_38_654_0 = _rtX -> Integrator_CSTATE ; _rtB ->
B_38_655_0 = _rtP -> P_611 * _rtB -> B_38_648_0 ; _rtB -> B_38_656_0 = ( _rtB
-> B_38_655_0 + _rtB -> B_38_654_0 ) + _rtB -> B_38_652_0 ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 38 , 660 ,
SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID11 ( SimStruct * S , int_T tid ) { real_T rtb_B_38_89_0 ; real_T
rtb_B_38_127_0 ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; _rtP = (
( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T *
) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_38_0_0 = _rtP -> P_142 ; _rtB ->
B_38_7_0 = _rtP -> P_150 ; if ( _rtP -> P_154 > _rtP -> P_155 ) { if ( _rtP
-> P_151 > _rtP -> P_152 ) { _rtB -> B_38_11_0 = _rtP -> P_152 ; } else if (
_rtP -> P_151 < _rtP -> P_153 ) { _rtB -> B_38_11_0 = _rtP -> P_153 ; } else
{ _rtB -> B_38_11_0 = _rtP -> P_151 ; } } else { _rtB -> B_38_11_0 = _rtP ->
P_151 ; } _rtB -> B_38_13_0 = _rtP -> P_157 ; _rtB -> B_38_24_0 = _rtP ->
P_167 ; _rtB -> B_38_30_0 = _rtP -> P_172 ; _rtB -> B_38_31_0 = _rtP -> P_173
; _rtB -> B_38_37_0 = _rtP -> P_175 ; _rtB -> B_38_38_0 = _rtP -> P_176 ;
_rtB -> B_38_48_0 = _rtP -> P_179 ; _rtB -> B_38_49_0 = _rtP -> P_180 ; _rtB
-> B_38_50_0 = _rtP -> P_181 ; _rtB -> B_38_57_0 = _rtP -> P_182 ; if ( _rtP
-> P_185 > _rtP -> P_187 ) { _rtB -> B_38_65_0 = _rtP -> P_184 ; } else {
_rtB -> B_38_65_0 = _rtP -> P_186 ; } _rtB -> B_38_67_0 = _rtP -> P_190 ;
_rtB -> B_38_68_0 = _rtP -> P_191 ; _rtB -> B_38_72_0 = _rtP -> P_193 ; _rtB
-> B_38_73_0 = _rtP -> P_194 ; rtb_B_38_89_0 = _rtP -> P_201 + _rtP -> P_202
; _rtB -> B_38_95_0 = _rtP -> P_204 ; _rtB -> B_38_96_0 = ( ( rtb_B_38_89_0 -
_rtP -> P_203 ) * _rtP -> P_200 + _rtP -> P_199 ) * ( _rtP -> P_197 / _rtP ->
P_198 ) * _rtB -> B_38_95_0 ; _rtB -> B_38_97_0 = _rtP -> P_205 ; _rtB ->
B_38_98_0 = _rtP -> P_206 ; _rtB -> B_38_99_0 = _rtP -> P_207 ; _rtB ->
B_38_100_0 = 0.0 / _rtB -> B_38_99_0 ; _rtB -> B_38_105_0 = _rtP -> P_209 *
rtb_B_38_89_0 / _rtP -> P_210 * _rtP -> P_208 ; _rtB -> B_38_106_0 = _rtP ->
P_211 ; rtb_B_38_127_0 = rtb_B_38_89_0 / _rtP -> P_203 ; _rtB -> B_38_130_0 =
_rtP -> P_199 / ( muDoubleScalarExp ( _rtP -> P_215 * _rtP -> P_210 / ( _rtP
-> P_209 * _rtP -> P_216 * rtb_B_38_89_0 * _rtP -> P_208 ) ) - _rtP -> P_217
) * ( rtb_B_38_127_0 * rtb_B_38_127_0 * rtb_B_38_127_0 ) * muDoubleScalarExp
( ( _rtP -> P_213 / rtb_B_38_89_0 - _rtP -> P_212 / _rtP -> P_203 ) * ( _rtP
-> P_210 * _rtP -> P_214 / ( _rtP -> P_209 * _rtP -> P_208 ) ) ) ; _rtB ->
B_38_133_0 = _rtP -> P_219 ; _rtB -> B_38_134_0 = _rtP -> P_220 ; _rtB ->
B_38_135_0 = _rtP -> P_221 ; _rtB -> B_38_136_0 = _rtP -> P_222 ; _rtB ->
B_38_137_0 = _rtP -> P_223 ; _rtB -> B_38_138_0 = _rtP -> P_224 ; _rtB ->
B_38_139_0 = _rtP -> P_225 ; _rtB -> B_38_140_0 = _rtP -> P_226 ; _rtB ->
B_38_141_0 = _rtP -> P_227 ; _rtB -> B_38_142_0 = _rtP -> P_228 ; _rtB ->
B_38_143_0 = _rtP -> P_229 ; _rtB -> B_38_144_0 = _rtP -> P_230 ; _rtB ->
B_38_190_0 = _rtP -> P_345 ; _rtB -> B_38_194_0 = _rtP -> P_346 ; _rtB ->
B_38_198_0 = _rtP -> P_347 ; _rtB -> B_38_202_0 = _rtP -> P_348 ; _rtB ->
B_38_210_0 = _rtP -> P_349 ; _rtB -> B_38_231_0 = _rtP -> P_361 ; _rtB ->
B_38_269_0 = _rtP -> P_375 ; _rtB -> B_38_273_0 = _rtP -> P_376 ; _rtB ->
B_38_277_0 = _rtP -> P_377 ; _rtB -> B_38_281_0 = _rtP -> P_378 ; _rtB ->
B_38_289_0 = _rtP -> P_379 ; _rtB -> B_38_311_0 = _rtP -> P_405 ; _rtB ->
B_38_342_0 = _rtP -> P_417 ; memcpy ( & _rtB -> B_38_333_0 [ 0 ] , & _rtP ->
P_415 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_38_334_0 [
0 ] , & _rtP -> P_416 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB
-> B_38_347_0 [ 0 ] , & _rtP -> P_418 [ 0 ] , 40000U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_38_348_0 [ 0 ] , & _rtP -> P_419 [ 0 ] , 40000U * sizeof
( real_T ) ) ; _rtB -> B_38_356_0 = _rtP -> P_422 ; _rtB -> B_38_409_0 = _rtP
-> P_453 ; _rtB -> B_38_421_0 = _rtP -> P_470 ; _rtB -> B_38_428_0 = _rtP ->
P_479 ; _rtB -> B_38_429_0 = _rtP -> P_480 ; _rtB -> B_38_430_0 = _rtP ->
P_481 ; _rtB -> B_38_431_0 = _rtP -> P_482 ; _rtB -> B_38_435_0 = _rtP ->
P_487 ; _rtB -> B_38_436_0 = _rtP -> P_488 ; _rtB -> B_38_437_0 = _rtP ->
P_489 ; _rtB -> B_38_438_0 = _rtP -> P_490 ; _rtB -> B_38_442_0 = _rtP ->
P_495 ; _rtB -> B_38_443_0 = _rtP -> P_496 ; _rtB -> B_38_444_0 = _rtP ->
P_497 ; _rtB -> B_38_445_0 = _rtP -> P_498 ; _rtB -> B_38_474_0 = _rtP ->
P_508 ; _rtB -> B_38_478_0 = _rtP -> P_509 ; _rtB -> B_38_482_0 = _rtP ->
P_510 ; _rtB -> B_38_486_0 = _rtP -> P_511 ; _rtB -> B_38_494_0 = _rtP ->
P_512 ; _rtB -> B_38_515_0 = _rtP -> P_524 ; _rtB -> B_38_558_0 = _rtP ->
P_557 ; _rtB -> B_38_559_0 = _rtP -> P_558 ; _rtB -> B_38_560_0 = _rtP ->
P_559 ; _rtB -> B_38_561_0 = _rtP -> P_560 ; _rtB -> B_38_581_0 = _rtP ->
P_567 + _rtP -> P_563 ; if ( _rtP -> P_561 > _rtP -> P_573 ) { rtb_B_38_89_0
= ( _rtB -> B_38_581_0 - 293.15 ) * 0.0 + 1.0339999999999974 ; if (
rtb_B_38_89_0 > _rtP -> P_571 ) { _rtB -> B_38_595_0 = _rtP -> P_571 ; } else
if ( rtb_B_38_89_0 < _rtP -> P_572 ) { _rtB -> B_38_595_0 = _rtP -> P_572 ; }
else { _rtB -> B_38_595_0 = rtb_B_38_89_0 ; } } else { _rtB -> B_38_595_0 =
_rtP -> P_562 ; } _rtB -> B_38_606_0 [ 0 ] = _rtP -> P_578 [ 0 ] ; _rtB ->
B_38_607_0 [ 0 ] = _rtP -> P_579 [ 0 ] ; _rtB -> B_38_613_0 [ 0 ] = _rtP ->
P_580 [ 0 ] ; _rtB -> B_38_614_0 [ 0 ] = _rtP -> P_581 [ 0 ] ; _rtB ->
B_38_606_0 [ 1 ] = _rtP -> P_578 [ 1 ] ; _rtB -> B_38_607_0 [ 1 ] = _rtP ->
P_579 [ 1 ] ; _rtB -> B_38_613_0 [ 1 ] = _rtP -> P_580 [ 1 ] ; _rtB ->
B_38_614_0 [ 1 ] = _rtP -> P_581 [ 1 ] ; _rtB -> B_38_620_0 = _rtP -> P_586 ;
_rtB -> B_38_621_0 = _rtP -> P_587 ; _rtB -> B_38_622_0 = _rtP -> P_588 ;
_rtB -> B_38_623_0 = _rtP -> P_589 ; _rtB -> B_38_627_0 = _rtP -> P_594 ;
_rtB -> B_38_628_0 = _rtP -> P_595 ; _rtB -> B_38_629_0 = _rtP -> P_596 ;
_rtB -> B_38_630_0 = _rtP -> P_597 ; _rtB -> B_38_638_0 = _rtP -> P_598 ;
_rtB -> B_38_639_0 = _rtP -> P_599 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = (
( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T *
) _ssGetModelBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_38_595_0 ; _rtDW -> itinit_PreviousInput =
_rtB -> B_38_583_0 ; } _rtDW -> inti_IWORK = 0 ; if ( _rtX -> inti_CSTATE ==
_rtP -> P_164 ) { switch ( _rtDW -> inti_MODE ) { case 3 : if ( _rtB ->
B_38_547_0 < 0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 1 ; }
break ; case 1 : if ( _rtB -> B_38_547_0 >= 0.0 ) { _rtDW -> inti_MODE = 3 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_38_547_0 < 0.0 ) { _rtDW -> inti_MODE = 1 ; } else { _rtDW
-> inti_MODE = 3 ; } break ; } } else if ( _rtX -> inti_CSTATE == _rtP ->
P_165 ) { switch ( _rtDW -> inti_MODE ) { case 4 : if ( _rtB -> B_38_547_0 >
0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 2 ; } break ; case
2 : if ( _rtB -> B_38_547_0 <= 0.0 ) { _rtDW -> inti_MODE = 4 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_38_547_0 > 0.0 ) { _rtDW -> inti_MODE = 2 ; } else { _rtDW
-> inti_MODE = 4 ; } break ; } } else { _rtDW -> inti_MODE = 0 ; }
ssCallAccelRunBlock ( S , 38 , 145 , SS_CALL_MDL_UPDATE ) ; if ( _rtDW ->
TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == ( rtInf ) ) {
_rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } else
if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else { _rtDW -> TimeStampB
= ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } * lastU = _rtB ->
B_38_234_0 ; if ( _rtDW -> TimeStampA_k == ( rtInf ) ) { _rtDW ->
TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_m ; } else if (
_rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW -> TimeStampB_f = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_o ; } else if ( _rtDW -> TimeStampA_k < _rtDW
-> TimeStampB_f ) { _rtDW -> TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_m ; } else { _rtDW -> TimeStampB_f = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB_o ; } * lastU = _rtB -> B_38_314_0 ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Memory2_PreviousInput [ 0 ] = _rtB -> B_16_0_1 [ 0
] ; _rtDW -> Memory2_PreviousInput [ 1 ] = _rtB -> B_16_0_1 [ 1 ] ; memcpy (
& _rtDW -> Memory1_PreviousInput [ 0 ] , & _rtB -> B_16_0_2 [ 0 ] , 200U *
sizeof ( real_T ) ) ; memcpy ( & _rtDW -> Memory3_PreviousInput [ 0 ] , &
_rtB -> B_18_0_2 [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtDW ->
Memory4_PreviousInput [ 0 ] = _rtB -> B_18_0_1 [ 0 ] ; _rtDW ->
Memory4_PreviousInput [ 1 ] = _rtB -> B_18_0_1 [ 1 ] ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK . Head < (
_rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_429 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_38_360_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_38_367_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_h . Head =
( ( _rtDW -> TransportDelay_IWORK_h . Head < ( _rtDW ->
TransportDelay_IWORK_h . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_h . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_h . Head == _rtDW -> TransportDelay_IWORK_h . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_h . CircularBufSize , & _rtDW -> TransportDelay_IWORK_h
. Tail , & _rtDW -> TransportDelay_IWORK_h . Head , & _rtDW ->
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_434 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_38_368_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_f = _rtB -> B_38_375_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_j .
Head = ( ( _rtDW -> TransportDelay_IWORK_j . Head < ( _rtDW ->
TransportDelay_IWORK_j . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_j . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_j . Head == _rtDW -> TransportDelay_IWORK_j . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_j . CircularBufSize , & _rtDW -> TransportDelay_IWORK_j
. Tail , & _rtDW -> TransportDelay_IWORK_j . Head , & _rtDW ->
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_439 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_38_378_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_p = _rtB -> B_38_385_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_a .
Head = ( ( _rtDW -> TransportDelay_IWORK_a . Head < ( _rtDW ->
TransportDelay_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_a . Head == _rtDW -> TransportDelay_IWORK_a . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_a . CircularBufSize , & _rtDW -> TransportDelay_IWORK_a
. Tail , & _rtDW -> TransportDelay_IWORK_a . Head , & _rtDW ->
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_444 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_38_386_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_k = _rtB -> B_38_393_0 ; } if ( _rtDW -> TimeStampA_b ==
( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_f ; } else if ( _rtDW -> TimeStampB_a == ( rtInf ) ) { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } else if (
_rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { _rtDW -> TimeStampA_b =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } * lastU =
_rtB -> B_38_410_0 ; if ( _rtDW -> TimeStampA_n == ( rtInf ) ) { _rtDW ->
TimeStampA_n = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_ma ; } else if
( _rtDW -> TimeStampB_m == ( rtInf ) ) { _rtDW -> TimeStampB_m = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeB_g ; } else if ( _rtDW -> TimeStampA_n <
_rtDW -> TimeStampB_m ) { _rtDW -> TimeStampA_n = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA_ma ; } else { _rtDW -> TimeStampB_m = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_g ; } * lastU = _rtB -> B_38_518_0 ; { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> MotordeCombustin1_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; _rtDW -> MotordeCombustin1_IWORK . Head = ( ( _rtDW ->
MotordeCombustin1_IWORK . Head < ( _rtDW -> MotordeCombustin1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> MotordeCombustin1_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> MotordeCombustin1_IWORK . Head == _rtDW ->
MotordeCombustin1_IWORK . Tail ) { if ( !
uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Tail , & _rtDW -> MotordeCombustin1_IWORK . Head ,
& _rtDW -> MotordeCombustin1_IWORK . Last , simTime - _rtP -> P_603 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
MotordeCombustin1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = _rtB -> B_38_641_0 ; } UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID11 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX ; XDot_uGrid_1PH_hd_T *
_rtXdot ; XDis_uGrid_1PH_hd_T * _rtXdis ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW =
( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtXdis = ( (
XDis_uGrid_1PH_hd_T * ) ssGetContStateDisabled ( S ) ) ; _rtXdot = ( (
XDot_uGrid_1PH_hd_T * ) ssGetdX ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Dinmicaeneleje1_CSTATE = 0.0 ; _rtXdot -> Dinmicaeneleje1_CSTATE += _rtP ->
P_143 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtXdot -> Dinmicaeneleje1_CSTATE +=
_rtB -> B_38_643_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_147 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_38_644_0 ; _rtXdot -> Currentfilter_CSTATE =
0.0 ; _rtXdot -> Currentfilter_CSTATE += _rtP -> P_160 * _rtX ->
Currentfilter_CSTATE ; _rtXdot -> Currentfilter_CSTATE += _rtB -> B_38_547_0
; if ( ( _rtDW -> inti_MODE != 3 ) && ( _rtDW -> inti_MODE != 4 ) ) { _rtXdot
-> inti_CSTATE = _rtB -> B_38_547_0 ; _rtXdis -> inti_CSTATE = false ; } else
{ _rtXdot -> inti_CSTATE = 0.0 ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW
-> inti_MODE == 4 ) ) { _rtXdis -> inti_CSTATE = true ; } } _rtXdot ->
StateSpace_CSTATE = 0.0 ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_168 *
_rtX -> StateSpace_CSTATE ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_169 *
_rtB -> B_38_598_0 ; _rtXdot -> Integrator2_CSTATE = _rtB -> B_38_579_0 ;
_rtXdot -> Currentfilter1_CSTATE = 0.0 ; _rtXdot -> Currentfilter1_CSTATE +=
_rtP -> P_188 * _rtX -> Currentfilter1_CSTATE ; _rtXdot ->
Currentfilter1_CSTATE += _rtB -> B_38_547_0 ; ssCallAccelRunBlock ( S , 38 ,
145 , SS_CALL_MDL_DERIVATIVES ) ; _rtXdot -> Hw2_CSTATE [ 0 ] = 0.0 ; _rtXdot
-> Hw6_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_293 [ 0 ] *
_rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_293 [ 1 ]
* _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 1 ] += _rtP -> P_293 [ 2
] * _rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_293 [
3 ] * _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_293
[ 4 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP ->
P_293 [ 5 ] * _rtX -> Hw2_CSTATE [ 3 ] ; _rtXdot -> Hw2_CSTATE [ 3 ] += _rtP
-> P_293 [ 6 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] +=
_rtP -> P_294 * _rtB -> B_38_166_0 [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 0 ] +=
_rtP -> P_297 [ 0 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [ 0 ]
+= _rtP -> P_297 [ 1 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 1
] += _rtP -> P_297 [ 2 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [
2 ] += _rtP -> P_297 [ 3 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE
[ 2 ] += _rtP -> P_297 [ 4 ] * _rtX -> Hw6_CSTATE [ 2 ] ; _rtXdot ->
Hw6_CSTATE [ 2 ] += _rtP -> P_297 [ 5 ] * _rtX -> Hw6_CSTATE [ 3 ] ; _rtXdot
-> Hw6_CSTATE [ 3 ] += _rtP -> P_297 [ 6 ] * _rtX -> Hw6_CSTATE [ 2 ] ;
_rtXdot -> Hw6_CSTATE [ 0 ] += _rtP -> P_298 * _rtB -> B_38_166_0 [ 2 ] ;
_rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_301 [ 0 ] * _rtX -> Hw1_CSTATE [ 0 ]
; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_301 [ 1 ] * _rtX -> Hw1_CSTATE [ 1
] ; _rtXdot -> Hw1_CSTATE [ 1 ] += _rtP -> P_301 [ 2 ] * _rtX -> Hw1_CSTATE [
0 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_301 [ 3 ] * _rtX -> Hw1_CSTATE
[ 1 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_301 [ 4 ] * _rtX ->
Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_301 [ 5 ] * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtXdot -> Hw1_CSTATE [ 3 ] += _rtP -> P_301 [ 6 ] *
_rtX -> Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_302 *
_rtB -> B_38_290_0 [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_305 [ 0 ]
* _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_305 [ 1
] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 1 ] += _rtP -> P_305 [
2 ] * _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP -> P_305
[ 3 ] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP ->
P_305 [ 4 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP
-> P_305 [ 5 ] * _rtX -> Hw3_CSTATE [ 3 ] ; _rtXdot -> Hw3_CSTATE [ 3 ] +=
_rtP -> P_305 [ 6 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 0 ]
+= _rtP -> P_306 * _rtB -> B_38_290_0 [ 2 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] =
0.0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 0 ] = 0.0
; _rtXdot -> Hw3_CSTATE_e [ 0 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw1_CSTATE_k [ 1 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw3_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP ->
P_309 [ 0 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP
-> P_309 [ 1 ] * _rtX -> Hw4_CSTATE [ 1 ] ; _rtXdot -> Hw4_CSTATE [ 1 ] +=
_rtP -> P_309 [ 2 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ]
+= _rtP -> P_310 * _rtB -> B_38_173_0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] += _rtP
-> P_313 [ 0 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot -> Hw1_CSTATE_k [ 0 ]
+= _rtP -> P_313 [ 1 ] * _rtX -> Hw1_CSTATE_k [ 1 ] ; _rtXdot -> Hw1_CSTATE_k
[ 1 ] += _rtP -> P_313 [ 2 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot ->
Hw1_CSTATE_k [ 0 ] += _rtP -> P_314 * _rtB -> B_38_172_0 ; _rtXdot ->
Hw7_CSTATE [ 0 ] += _rtP -> P_317 [ 0 ] * _rtX -> Hw7_CSTATE [ 0 ] ; _rtXdot
-> Hw7_CSTATE [ 0 ] += _rtP -> P_317 [ 1 ] * _rtX -> Hw7_CSTATE [ 1 ] ;
_rtXdot -> Hw7_CSTATE [ 1 ] += _rtP -> P_317 [ 2 ] * _rtX -> Hw7_CSTATE [ 0 ]
; _rtXdot -> Hw7_CSTATE [ 0 ] += _rtP -> P_318 * _rtB -> B_38_251_0 ; _rtXdot
-> Hw3_CSTATE_e [ 0 ] += _rtP -> P_321 [ 0 ] * _rtX -> Hw3_CSTATE_e [ 0 ] ;
_rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_321 [ 1 ] * _rtX -> Hw3_CSTATE_e [
1 ] ; _rtXdot -> Hw3_CSTATE_e [ 1 ] += _rtP -> P_321 [ 2 ] * _rtX ->
Hw3_CSTATE_e [ 0 ] ; _rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_322 * _rtB ->
B_38_252_0 ; _rtXdot -> TransferFcn_CSTATE_j = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_j += _rtP -> P_340 * _rtX -> TransferFcn_CSTATE_j ;
_rtXdot -> TransferFcn_CSTATE_j += _rtB -> B_38_168_0 ; _rtXdot ->
TransferFcn1_CSTATE = 0.0 ; _rtXdot -> TransferFcn1_CSTATE += _rtP -> P_342 *
_rtX -> TransferFcn1_CSTATE ; _rtXdot -> TransferFcn1_CSTATE += _rtB ->
B_38_174_0 ; _rtXdot -> TransferFcn_CSTATE_g = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_g += _rtP -> P_370 * _rtX -> TransferFcn_CSTATE_g ;
_rtXdot -> TransferFcn_CSTATE_g += _rtB -> B_38_247_0 ; _rtXdot ->
TransferFcn1_CSTATE_p = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_p += _rtP ->
P_372 * _rtX -> TransferFcn1_CSTATE_p ; _rtXdot -> TransferFcn1_CSTATE_p +=
_rtB -> B_38_253_0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] = 0.0 ; _rtXdot ->
Hw2_CSTATE_p [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP -> P_423 [ 0
] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP ->
P_423 [ 1 ] * _rtX -> Hw2_CSTATE_p [ 1 ] ; _rtXdot -> Hw2_CSTATE_p [ 1 ] +=
_rtP -> P_423 [ 2 ] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [
0 ] += _rtP -> P_424 * _rtB -> B_38_451_0 ; _rtXdot -> integrator_CSTATE =
_rtB -> B_38_535_0 ; _rtXdot -> integrator_CSTATE_i = _rtB -> B_38_537_0 ;
_rtXdot -> integrator_CSTATE_p = _rtB -> B_38_539_0 ; _rtXdot ->
integrator_CSTATE_l = _rtB -> B_38_541_0 ; _rtXdot -> Hi_Pass1_CSTATE = 0.0 ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_458 * _rtX -> Hi_Pass1_CSTATE ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_459 * _rtB -> B_38_413_0 ; _rtXdot ->
Hw5_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] = 0.0 ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtP -> P_468 [ 0 ] * _rtX ->
TransferFcn1_CSTATE_e [ 0 ] ; _rtXdot -> Hw5_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
TransferFcn1_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] +=
_rtP -> P_468 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtXdot ->
Hw5_CSTATE [ 0 ] += _rtP -> P_463 [ 0 ] * _rtX -> Hw5_CSTATE [ 0 ] ; _rtXdot
-> Hw5_CSTATE [ 0 ] += _rtP -> P_463 [ 1 ] * _rtX -> Hw5_CSTATE [ 1 ] ;
_rtXdot -> Hw5_CSTATE [ 1 ] += _rtP -> P_463 [ 2 ] * _rtX -> Hw5_CSTATE [ 0 ]
; _rtXdot -> Hw5_CSTATE [ 0 ] += _rtP -> P_464 * _rtB -> B_38_461_0 ; _rtXdot
-> TransferFcn1_CSTATE_e [ 1 ] += _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtB -> B_38_417_0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] = 0.0 ; _rtXdot -> Hw6_CSTATE_f [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] += _rtP -> P_471 [ 0 ] * _rtX -> Hw6_CSTATE_f [ 0 ] ;
_rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_471 [ 1 ] * _rtX -> Hw6_CSTATE_f [
1 ] ; _rtXdot -> Hw6_CSTATE_f [ 1 ] += _rtP -> P_471 [ 2 ] * _rtX ->
Hw6_CSTATE_f [ 0 ] ; _rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_472 * _rtB ->
B_38_452_0 ; _rtXdot -> TransferFcn_CSTATE_m = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_m += _rtP -> P_500 * _rtX -> TransferFcn_CSTATE_m ;
_rtXdot -> TransferFcn_CSTATE_m += _rtB -> B_38_447_0 ; _rtXdot ->
TransferFcn1_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_l += _rtP ->
P_502 * _rtX -> TransferFcn1_CSTATE_l ; _rtXdot -> TransferFcn1_CSTATE_l +=
_rtB -> B_38_453_0 ; _rtXdot -> TransferFcn2_CSTATE = 0.0 ; _rtXdot ->
TransferFcn2_CSTATE += _rtP -> P_506 * _rtX -> TransferFcn2_CSTATE ; _rtXdot
-> TransferFcn2_CSTATE += _rtB -> B_38_457_0 ; _rtXdot ->
TransferFcn1_CSTATE_g = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_g += _rtP ->
P_574 * _rtX -> TransferFcn1_CSTATE_g ; _rtXdot -> TransferFcn1_CSTATE_g +=
_rtB -> B_38_593_0 ; _rtXdot -> Actuador1_CSTATE = 0.0 ; _rtXdot ->
Actuador1_CSTATE += _rtP -> P_600 * _rtX -> Actuador1_CSTATE ; _rtXdot ->
Actuador1_CSTATE += _rtB -> B_38_656_0 ; _rtXdot -> Filter_CSTATE = _rtB ->
B_38_652_0 ; _rtXdot -> Integrator_CSTATE = _rtB -> B_38_653_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; ssCallAccelRunBlock ( S , 38 , 145 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { boolean_T anyStateSaturated
; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX
; ZCV_uGrid_1PH_hd_T * _rtZCSV ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_uGrid_1PH_hd_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( (
X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_38_16_0 -
uGrid_1PH_hd_rtC ( S ) -> B_38_17_0 ; if ( ( _rtDW -> inti_MODE == 1 ) && (
_rtX -> inti_CSTATE >= _rtP -> P_164 ) ) { _rtZCSV -> inti_IntgUpLimit_ZC =
0.0 ; } else { _rtZCSV -> inti_IntgUpLimit_ZC = _rtX -> inti_CSTATE - _rtP ->
P_164 ; } if ( ( _rtDW -> inti_MODE == 2 ) && ( _rtX -> inti_CSTATE <= _rtP
-> P_165 ) ) { _rtZCSV -> inti_IntgLoLimit_ZC = 0.0 ; } else { _rtZCSV ->
inti_IntgLoLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_165 ; }
anyStateSaturated = false ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW ->
inti_MODE == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> inti_LeaveSaturate_ZC = _rtB -> B_38_547_0 ; } else { _rtZCSV ->
inti_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB
-> B_38_22_0 - _rtB -> B_38_15_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB
-> B_38_22_0 - _rtB -> B_38_24_0 ; _rtZCSV -> LowerRelop1_RelopInput_ZC_i =
_rtB -> B_38_22_0 - _rtB -> B_38_39_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f
= _rtB -> B_38_22_0 - _rtB -> B_38_41_0 ; _rtZCSV -> Compare_RelopInput_ZC_d
= _rtB -> B_38_16_0 - uGrid_1PH_hd_rtC ( S ) -> B_38_45_0 ; _rtZCSV ->
LowerRelop1_RelopInput_ZC_a = _rtB -> B_38_76_0 - _rtB -> B_38_7_0 ; _rtZCSV
-> UpperRelop_RelopInput_ZC_g = _rtB -> B_38_76_0 - _rtB -> B_38_78_0 ;
ssCallAccelRunBlock ( S , 38 , 145 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 38 , 146 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 38 , 166 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_362 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_38_236_0 - _rtP -> P_368 ;
ssCallAccelRunBlock ( S , 38 , 290 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC_d = ssGetT ( S ) - _rtP -> P_406 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_j = _rtB -> B_38_316_0 - _rtP -> P_412 ; _rtZCSV
-> Step_StepTime_ZC_b = ssGetT ( S ) - _rtP -> P_525 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_e = _rtB -> B_38_520_0 - _rtP -> P_531 ; _rtZCSV
-> Saturation_UprLim_ZC = _rtB -> B_38_553_0 - _rtP -> P_551 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_38_553_0 - _rtP -> P_552 ; _rtZCSV ->
Abs_AbsZc_ZC = _rtB -> B_38_547_0 ; _rtZCSV -> Compare_RelopInput_ZC_f = _rtB
-> B_38_547_0 - uGrid_1PH_hd_rtC ( S ) -> B_38_573_0 ; _rtZCSV ->
Abs_AbsZc_ZC_j = _rtB -> B_38_66_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_38_585_0 ; _rtZCSV -> Compare_RelopInput_ZC_b = _rtB -> B_38_66_0 -
uGrid_1PH_hd_rtC ( S ) -> B_38_587_0 ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 1183366770U ) ; ssSetChecksumVal
( S , 1 , 1016088236U ) ; ssSetChecksumVal ( S , 2 , 2482598311U ) ;
ssSetChecksumVal ( S , 3 , 2393595331U ) ; { mxArray * slVerStructMat = NULL
; mxArray * slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ]
; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver"
) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0
, "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.9" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_uGrid_1PH_hd_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_uGrid_1PH_hd_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_uGrid_1PH_hd_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & uGrid_1PH_hd_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
uGrid_1PH_hd_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_153 = rtMinusInf ; ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_165 = rtMinusInf ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 3 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 4 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 5 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 6 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 7 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 8 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 9 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID11 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
