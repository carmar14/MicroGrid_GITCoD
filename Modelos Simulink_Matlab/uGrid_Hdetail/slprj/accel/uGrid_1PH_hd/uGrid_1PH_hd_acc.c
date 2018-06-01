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
S ) { ssCallAccelRunBlock ( S , 35 , 131 , SS_CALL_MDL_OUTPUTS ) ; } void
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term ( SimStruct *
const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T
B_35_361_0 ; real_T B_35_369_0 ; real_T B_35_379_0 ; real_T B_35_387_0 ;
boolean_T resetIntg ; ZCEventType zcEvent ; real_T * lastU ; uint32_T
numCycles ; real_T rtb_B_35_397_0 ; real_T rtb_RealImagtoComplex_re ; real_T
rtb_RealImagtoComplex_im ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP
; X_uGrid_1PH_hd_T * _rtX ; PrevZCX_uGrid_1PH_hd_T * _rtZCE ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtZCE = ( ( PrevZCX_uGrid_1PH_hd_T * ) _ssGetPrevZCSigState ( S )
) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_35_1_0 = 0.0 ; _rtB -> B_35_1_0 +=
_rtP -> P_121 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtB -> B_35_2_0 = _rtP ->
P_122 * _rtB -> B_35_1_0 ; _rtB -> B_35_3_0 = _rtP -> P_123 * _rtB ->
B_35_2_0 ; _rtB -> B_35_4_0 = 0.0 ; _rtB -> B_35_4_0 += _rtP -> P_125 * _rtX
-> TransferFcn_CSTATE ; _rtB -> B_35_5_0 = _rtP -> P_126 * _rtB -> B_35_4_0 ;
_rtB -> B_35_6_0 = _rtB -> B_35_3_0 - _rtB -> B_35_5_0 ; _rtB -> B_35_16_0 =
0.0 ; _rtB -> B_35_16_0 += _rtP -> P_138 * _rtX -> Currentfilter_CSTATE ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_35_14_0 = _rtDW ->
itinit1_PreviousInput ; _rtB -> B_35_15_0 = _rtP -> P_136 * _rtB -> B_35_14_0
; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode = ( _rtB ->
B_35_16_0 > uGrid_1PH_hd_rtC ( S ) -> B_35_17_0 ) ; } _rtB -> B_35_19_0 =
_rtDW -> Compare_Mode ; _rtB -> B_35_20_0 = _rtDW -> itinit_PreviousInput ; }
if ( ssIsMajorTimeStep ( S ) ) { resetIntg = false ; zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & _rtZCE -> inti_Reset_ZCE , ( _rtB -> B_35_19_0 ) ) ;
if ( ( zcEvent != NO_ZCEVENT ) || ( _rtDW -> inti_IWORK != 0 ) ) { resetIntg
= true ; _rtX -> inti_CSTATE = _rtB -> B_35_20_0 ; } if ( resetIntg ) {
ssSetSolverNeedsReset ( S ) ; } if ( _rtX -> inti_CSTATE >= _rtP -> P_141 ) {
_rtX -> inti_CSTATE = _rtP -> P_141 ; } else { if ( _rtX -> inti_CSTATE <=
_rtP -> P_142 ) { _rtX -> inti_CSTATE = _rtP -> P_142 ; } } } _rtB ->
B_35_21_0 = _rtX -> inti_CSTATE ; _rtB -> B_35_22_0 = _rtP -> P_143 * _rtB ->
B_35_21_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S )
) { _rtDW -> LowerRelop1_Mode = ( _rtB -> B_35_22_0 > _rtB -> B_35_15_0 ) ;
_rtDW -> UpperRelop_Mode = ( _rtB -> B_35_22_0 < _rtB -> B_35_24_0 ) ; } _rtB
-> B_35_23_0 = _rtDW -> LowerRelop1_Mode ; _rtB -> B_35_25_0 = _rtDW ->
UpperRelop_Mode ; } if ( _rtB -> B_35_23_0 ) { _rtB -> B_35_27_0 = _rtB ->
B_35_15_0 ; } else { if ( _rtB -> B_35_25_0 ) { _rtB -> B_13_0_0 = _rtB ->
B_35_24_0 ; } else { _rtB -> B_13_0_0 = _rtB -> B_35_22_0 ; } _rtB ->
B_35_27_0 = _rtB -> B_13_0_0 ; } _rtB -> B_35_29_0 = 0.0 ; _rtB -> B_35_29_0
+= _rtP -> P_147 * _rtX -> StateSpace_CSTATE ; if ( _rtB -> B_35_30_0 > _rtP
-> P_151 ) { _rtB -> B_35_33_0 = muDoubleScalarExp ( ( 1.0 / _rtB ->
B_35_29_0 - 0.0034112229234180458 ) * 0.0 ) ; } else { _rtB -> B_35_33_0 =
_rtB -> B_35_31_0 ; } _rtB -> B_35_34_0 = - 0.0605295518538322 * _rtB ->
B_35_14_0 / ( _rtB -> B_35_14_0 - _rtB -> B_35_27_0 ) * _rtB -> B_35_27_0 *
_rtB -> B_35_33_0 ; _rtB -> B_35_36_0 = - _rtB -> B_35_19_0 *
0.0605295518538322 * _rtB -> B_35_16_0 * _rtB -> B_35_14_0 / ( _rtB ->
B_35_14_0 - _rtB -> B_35_27_0 ) * _rtB -> B_35_33_0 ; if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_35_39_0 = _rtP -> P_154 * _rtB -> B_35_14_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> LowerRelop1_Mode_g = ( _rtB -> B_35_22_0
> _rtB -> B_35_39_0 ) ; } _rtB -> B_35_40_0 = _rtDW -> LowerRelop1_Mode_g ;
_rtB -> B_35_41_0 = - _rtB -> B_35_39_0 * 0.999 * 0.1 * 0.9999 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> UpperRelop_Mode_g = ( _rtB -> B_35_22_0
< _rtB -> B_35_41_0 ) ; } _rtB -> B_35_42_0 = _rtDW -> UpperRelop_Mode_g ; if
( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_k = ( _rtB -> B_35_16_0 <
uGrid_1PH_hd_rtC ( S ) -> B_35_45_0 ) ; } _rtB -> B_35_47_0 = _rtDW ->
Compare_Mode_k ; } if ( _rtB -> B_35_40_0 ) { _rtB -> B_35_44_0 = _rtB ->
B_35_39_0 ; } else { if ( _rtB -> B_35_42_0 ) { _rtB -> B_14_0_0 = _rtB ->
B_35_41_0 ; } else { _rtB -> B_14_0_0 = _rtB -> B_35_22_0 ; } _rtB ->
B_35_44_0 = _rtB -> B_14_0_0 ; } switch ( ( int32_T ) _rtB -> B_35_37_0 ) {
case 1 : _rtB -> B_10_0_0 [ 0 ] = _rtB -> B_35_38_0 * _rtB -> B_35_44_0 ;
_rtB -> B_10_0_0 [ 1 ] = _rtB -> B_35_38_0 * _rtB -> B_35_16_0 ; _rtB ->
B_10_0_0 [ 2 ] = _rtB -> B_35_38_0 * _rtB -> B_35_47_0 ; _rtB -> B_10_0_0 [ 3
] = _rtB -> B_35_38_0 * _rtB -> B_35_14_0 ; _rtB -> B_35_55_0 = - _rtB ->
B_10_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_10_0_0 [ 1 ] * (
1.0339999999999974 / ( _rtB -> B_10_0_0 [ 0 ] + 0.10339999999999974 ) ) ;
break ; case 2 : _rtB -> B_9_0_0 [ 0 ] = _rtB -> B_35_48_0 * _rtB ->
B_35_44_0 ; _rtB -> B_9_0_0 [ 1 ] = _rtB -> B_35_48_0 * _rtB -> B_35_16_0 ;
_rtB -> B_9_0_0 [ 2 ] = _rtB -> B_35_48_0 * _rtB -> B_35_47_0 ; _rtB ->
B_9_0_0 [ 3 ] = _rtB -> B_35_48_0 * _rtB -> B_35_14_0 ; _rtB -> B_35_55_0 = -
_rtB -> B_9_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_9_0_0 [ 1 ] * _rtB ->
B_9_0_0 [ 3 ] / ( _rtB -> B_9_0_0 [ 3 ] * 0.1 + _rtB -> B_9_0_0 [ 0 ] ) ;
break ; case 3 : _rtB -> B_8_0_0 [ 0 ] = _rtB -> B_35_49_0 * _rtB ->
B_35_44_0 ; _rtB -> B_8_0_0 [ 1 ] = _rtB -> B_35_49_0 * _rtB -> B_35_16_0 ;
_rtB -> B_8_0_0 [ 2 ] = _rtB -> B_35_49_0 * _rtB -> B_35_47_0 ; _rtB ->
B_8_0_0 [ 3 ] = _rtB -> B_35_49_0 * _rtB -> B_35_14_0 ; _rtB -> B_35_55_0 = -
_rtB -> B_8_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_8_0_0 [ 1 ] * (
1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_8_0_0 [ 0 ] ) +
0.10339999999999974 ) ) ; break ; default : _rtB -> B_7_0_0 [ 0 ] = _rtB ->
B_35_50_0 * _rtB -> B_35_44_0 ; _rtB -> B_7_0_0 [ 1 ] = _rtB -> B_35_50_0 *
_rtB -> B_35_16_0 ; _rtB -> B_7_0_0 [ 2 ] = _rtB -> B_35_50_0 * _rtB ->
B_35_47_0 ; _rtB -> B_7_0_0 [ 3 ] = _rtB -> B_35_50_0 * _rtB -> B_35_14_0 ;
_rtB -> B_35_55_0 = - _rtB -> B_7_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_7_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_7_0_0
[ 0 ] ) + 0.10339999999999974 ) ) ; break ; } _rtB -> B_35_56_0 = _rtB ->
B_35_55_0 * _rtB -> B_35_33_0 ; _rtB -> B_35_58_0 = _rtX ->
Integrator2_CSTATE ; switch ( ( int32_T ) _rtB -> B_35_57_0 ) { case 1 : _rtB
-> B_35_60_0 = _rtB -> B_35_58_0 ; break ; case 2 : _rtB -> B_35_60_0 =
muDoubleScalarExp ( - 61.061946632469265 * _rtB -> B_35_27_0 ) *
83.400845004248509 ; break ; case 3 : _rtB -> B_35_60_0 = _rtB -> B_35_58_0 ;
break ; default : _rtB -> B_35_60_0 = _rtB -> B_35_58_0 ; break ; } _rtB ->
B_35_66_0 = 0.0 ; _rtB -> B_35_66_0 += _rtP -> P_166 * _rtX ->
Currentfilter1_CSTATE ; if ( _rtB -> B_35_67_0 > _rtP -> P_169 ) { _rtB ->
B_35_70_0 = muDoubleScalarExp ( ( 1.0 / _rtB -> B_35_29_0 -
0.0034112229234180458 ) * 0.0 ) * - _rtB -> B_35_65_0 * _rtB -> B_35_66_0 +
0.05 * _rtB -> B_35_66_0 ; } else { _rtB -> B_35_70_0 = _rtB -> B_35_68_0 ; }
_rtB -> B_35_71_0 = ( ( ( ( _rtB -> B_35_34_0 + _rtB -> B_35_36_0 ) + _rtB ->
B_35_56_0 ) + _rtB -> B_35_60_0 ) + - 0.0 * _rtB -> B_35_27_0 ) + _rtB ->
B_35_70_0 ; if ( _rtB -> B_35_72_0 > _rtP -> P_172 ) { _rtB -> B_35_75_0 = (
_rtB -> B_35_29_0 - 293.15 ) * 0.0 ; } else { _rtB -> B_35_75_0 = _rtB ->
B_35_73_0 ; } _rtB -> B_35_76_0 = ( _rtB -> B_35_11_0 + _rtB -> B_35_71_0 ) +
_rtB -> B_35_75_0 ; _rtB -> B_35_78_0 = _rtP -> P_173 * _rtB -> B_35_16_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> LowerRelop1_Mode_c = ( _rtB -> B_35_76_0 > _rtB -> B_35_7_0 ) ; } _rtB ->
B_35_77_0 = _rtDW -> LowerRelop1_Mode_c ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> UpperRelop_Mode_gu = ( _rtB -> B_35_76_0 < _rtB -> B_35_78_0 ) ; }
_rtB -> B_35_79_0 = _rtDW -> UpperRelop_Mode_gu ; } if ( _rtB -> B_35_77_0 )
{ _rtB -> B_35_81_0 = _rtB -> B_35_7_0 ; } else { if ( _rtB -> B_35_79_0 ) {
_rtB -> B_12_0_0 = _rtB -> B_35_78_0 ; } else { _rtB -> B_12_0_0 = _rtB ->
B_35_76_0 ; } _rtB -> B_35_81_0 = _rtB -> B_12_0_0 ; }
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S ) ; _rtB ->
B_35_132_0 = _rtP -> P_195 * _rtB ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 . B_0_9_0 ; ssCallAccelRunBlock (
S , 35 , 145 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 146 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_in , ( _rtB -> B_35_146_0 [ 7 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 28 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC = 4 ; } zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING
, & _rtZCE -> Subsystem_Trig_ZCE_k , ( _rtB -> B_35_146_0 [ 9 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 29 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_d = 4 ; } } } _rtB ->
B_35_149_0 = 0.0 ; _rtB -> B_35_149_0 += _rtP -> P_272 * _rtX -> Hw2_CSTATE [
3 ] ; _rtB -> B_35_150_0 = 0.0 ; _rtB -> B_35_150_0 += _rtP -> P_276 * _rtX
-> Hw6_CSTATE [ 3 ] ; _rtB -> B_35_151_0 = 0.0 ; _rtB -> B_35_151_0 += _rtP
-> P_280 * _rtX -> Hw1_CSTATE [ 3 ] ; _rtB -> B_35_152_0 = 0.0 ; _rtB ->
B_35_152_0 += _rtP -> P_284 * _rtX -> Hw3_CSTATE [ 3 ] ; ssCallAccelRunBlock
( S , 35 , 153 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_e , ( _rtB -> B_35_146_0 [ 3 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 26 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_e = 4 ; } }
ssCallAccelRunBlock ( S , 35 , 155 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_at , ( _rtB -> B_35_146_0 [ 1 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 25 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_j = 4 ; } } ssCallAccelRunBlock ( S , 35 , 157
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 158 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_35_159_0 = 0.0 ; _rtB -> B_35_159_0 +=
_rtP -> P_288 * _rtX -> Hw4_CSTATE [ 1 ] ; _rtB -> B_35_160_0 = 0.0 ; _rtB ->
B_35_160_0 += _rtP -> P_292 * _rtX -> Hw1_CSTATE_k [ 1 ] ;
ssCallAccelRunBlock ( S , 35 , 161 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 162 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_35_163_0 = 0.0 ; _rtB -> B_35_163_0 +=
_rtP -> P_296 * _rtX -> Hw7_CSTATE [ 1 ] ; _rtB -> B_35_164_0 = 0.0 ; _rtB ->
B_35_164_0 += _rtP -> P_300 * _rtX -> Hw3_CSTATE_e [ 1 ] ;
ssCallAccelRunBlock ( S , 35 , 165 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 166 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 167 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_211_0 = _rtB -> B_35_166_0 [ 0 ] + _rtB
-> B_35_210_0 ; } _rtB -> B_35_168_0 = _rtP -> P_316 * _rtB -> B_35_145_0 [ 6
] ; _rtB -> B_35_172_0 = 0.0 ; _rtB -> B_35_172_0 += _rtP -> P_318 * _rtX ->
TransferFcn_CSTATE_j ; _rtB -> B_35_173_0 = 0.0 ; _rtB -> B_35_173_0 += _rtP
-> P_320 * _rtX -> TransferFcn1_CSTATE ; _rtB -> B_35_174_0 = _rtP -> P_321 *
_rtB -> B_35_145_0 [ 1 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
B_35_225_0 = ( real_T ) ( ( _rtB -> B_35_211_0 != uGrid_1PH_hd_rtC ( S ) ->
B_35_212_0 ) && ( _rtB -> B_35_211_0 >= ( ( muDoubleScalarRem ( ssGetTaskTime
( S , 2 ) + _rtP -> P_328 , _rtP -> P_329 ) * _rtP -> P_330 * 2.0 - 1.0 ) +
1.0 ) * 0.5 ) ) * _rtP -> P_331 ; if ( ssGetTaskTime ( S , 2 ) < _rtP ->
P_332 ) { rtb_B_35_397_0 = _rtP -> P_333 ; } else { rtb_B_35_397_0 = _rtP ->
P_334 ; } _rtB -> B_35_227_0 = _rtB -> B_35_225_0 * rtb_B_35_397_0 ;
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime
( S , 2 ) < _rtP -> P_335 ) { rtb_B_35_397_0 = _rtP -> P_336 ; } else {
rtb_B_35_397_0 = _rtP -> P_337 ; } _rtB -> B_35_230_0 = _rtB -> B_1_0_1 *
rtb_B_35_397_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> Step_MODE =
( ssGetTaskTime ( S , 1 ) >= _rtP -> P_339 ) ; if ( _rtDW -> Step_MODE == 1 )
{ _rtB -> B_35_232_0 = _rtP -> P_341 ; } else { _rtB -> B_35_232_0 = _rtP ->
P_340 ; } } _rtB -> B_35_234_0 = rt_Lookup ( _rtP -> P_342 , 5 , ssGetT ( S )
, _rtP -> P_343 ) ; if ( _rtB -> B_35_231_0 >= _rtP -> P_344 ) { _rtB ->
B_35_235_0 = _rtB -> B_35_232_0 ; } else { _rtB -> B_35_235_0 = _rtB ->
B_35_234_0 ; } if ( ( _rtDW -> TimeStampA >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_35_236_0 = 0.0 ; } else {
rtb_B_35_397_0 = _rtDW -> TimeStampA ; lastU = & _rtDW -> LastUAtTimeA ; if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW -> TimeStampB <
ssGetT ( S ) ) { rtb_B_35_397_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S ) ) {
rtb_B_35_397_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_35_236_0 = ( _rtB -> B_35_234_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_35_397_0 ) ; } _rtB -> B_35_247_0 = _rtP -> P_346 * _rtB -> B_35_145_0
[ 8 ] ; _rtB -> B_35_251_0 = 0.0 ; _rtB -> B_35_251_0 += _rtP -> P_348 * _rtX
-> TransferFcn_CSTATE_g ; _rtB -> B_35_252_0 = 0.0 ; _rtB -> B_35_252_0 +=
_rtP -> P_350 * _rtX -> TransferFcn1_CSTATE_p ; _rtB -> B_35_253_0 = _rtP ->
P_351 * _rtB -> B_35_145_0 [ 3 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 290 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_291_0 = _rtB -> B_35_290_0 [ 0 ] + _rtB -> B_35_289_0 ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_35_305_0 = ( real_T ) ( ( _rtB ->
B_35_291_0 != uGrid_1PH_hd_rtC ( S ) -> B_35_292_0 ) && ( _rtB -> B_35_291_0
>= ( ( muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_372 , _rtP ->
P_373 ) * _rtP -> P_374 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_375 ; if
( ssGetTaskTime ( S , 2 ) < _rtP -> P_376 ) { rtb_B_35_397_0 = _rtP -> P_377
; } else { rtb_B_35_397_0 = _rtP -> P_378 ; } _rtB -> B_35_307_0 = _rtB ->
B_35_305_0 * rtb_B_35_397_0 ; ssCallAccelRunBlock ( S , 3 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_379 ) {
rtb_B_35_397_0 = _rtP -> P_380 ; } else { rtb_B_35_397_0 = _rtP -> P_381 ; }
_rtB -> B_35_310_0 = _rtB -> B_3_0_1 * rtb_B_35_397_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_c = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_383 ) ; if ( _rtDW -> Step_MODE_c == 1 ) { _rtB -> B_35_312_0 = _rtP ->
P_385 ; } else { _rtB -> B_35_312_0 = _rtP -> P_384 ; } } _rtB -> B_35_314_0
= rt_Lookup ( _rtP -> P_386 , 5 , ssGetT ( S ) , _rtP -> P_387 ) ; if ( _rtB
-> B_35_311_0 >= _rtP -> P_388 ) { _rtB -> B_35_315_0 = _rtB -> B_35_312_0 ;
} else { _rtB -> B_35_315_0 = _rtB -> B_35_314_0 ; } if ( ( _rtDW ->
TimeStampA_k >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_f >= ssGetT ( S ) ) )
{ _rtB -> B_35_316_0 = 0.0 ; } else { rtb_B_35_397_0 = _rtDW -> TimeStampA_k
; lastU = & _rtDW -> LastUAtTimeA_m ; if ( _rtDW -> TimeStampA_k < _rtDW ->
TimeStampB_f ) { if ( _rtDW -> TimeStampB_f < ssGetT ( S ) ) { rtb_B_35_397_0
= _rtDW -> TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } else { if (
_rtDW -> TimeStampA_k >= ssGetT ( S ) ) { rtb_B_35_397_0 = _rtDW ->
TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } _rtB -> B_35_316_0 = (
_rtB -> B_35_314_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_35_397_0 ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 327 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 328 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) { _rtB ->
B_35_329_0 [ 0 ] = _rtB -> B_28_0_0 [ 0 ] ; _rtB -> B_35_329_0 [ 1 ] = _rtB
-> B_28_0_0 [ 1 ] ; _rtB -> B_35_330_0 [ 0 ] = _rtB -> B_35_149_0 ; _rtB ->
B_35_330_0 [ 1 ] = _rtB -> B_35_150_0 ; } memcpy ( & _rtB -> B_35_331_0 [ 0 ]
, & _rtDW -> Memory1_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB
-> B_35_332_0 [ 0 ] = _rtDW -> Memory2_PreviousInput [ 0 ] ; _rtB ->
B_35_332_0 [ 1 ] = _rtDW -> Memory2_PreviousInput [ 1 ] ; } if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 336 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 16 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 35 , 338 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 339 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 35 , 340 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 341 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 343 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 35 , 344 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 345 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 35 , 346 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsSampleHit ( S , 3 , 0 ) ) { _rtB -> B_35_349_0 [ 0 ] = _rtB -> B_29_0_0 [
0 ] ; _rtB -> B_35_349_0 [ 1 ] = _rtB -> B_29_0_0 [ 1 ] ; _rtB -> B_35_350_0
[ 0 ] = _rtB -> B_35_151_0 ; _rtB -> B_35_350_0 [ 1 ] = _rtB -> B_35_152_0 ;
} memcpy ( & _rtB -> B_35_351_0 [ 0 ] , & _rtDW -> Memory3_PreviousInput [ 0
] , 200U * sizeof ( real_T ) ) ; _rtB -> B_35_352_0 [ 0 ] = _rtDW ->
Memory4_PreviousInput [ 0 ] ; _rtB -> B_35_352_0 [ 1 ] = _rtDW ->
Memory4_PreviousInput [ 1 ] ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 35 , 354 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 18 , 0 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_35_357_0 = 0.0 ; _rtB -> B_35_357_0 += _rtP -> P_402 * _rtX -> Hw2_CSTATE_p
[ 1 ] ; _rtB -> B_35_358_0 = _rtP -> P_404 * _rtB -> B_35_145_0 [ 5 ] ;
ssCallAccelRunBlock ( S , 35 , 359 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_360_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_406 ;
B_35_361_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_407 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_35_363_0 = _rtP -> P_408
; _rtB -> B_35_365_0 = _rtDW -> Memory_PreviousInput ; } if ( ssGetT ( S ) >=
_rtB -> B_35_363_0 ) { _rtB -> B_35_367_0 = ( _rtB -> B_35_360_0 - B_35_361_0
) * _rtP -> P_1 ; } else { _rtB -> B_35_367_0 = _rtB -> B_35_365_0 ; } _rtB
-> B_35_368_0 = _rtX -> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_411 ; B_35_369_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_h . Last , _rtDW ->
TransportDelay_IWORK_h . Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP
-> P_412 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_35_371_0 = _rtP -> P_413 ; _rtB -> B_35_373_0 = _rtDW
-> Memory_PreviousInput_f ; } if ( ssGetT ( S ) >= _rtB -> B_35_371_0 ) {
_rtB -> B_35_375_0 = ( _rtB -> B_35_368_0 - B_35_369_0 ) * _rtP -> P_0 ; }
else { _rtB -> B_35_375_0 = _rtB -> B_35_373_0 ; } rtb_RealImagtoComplex_re =
_rtB -> B_35_367_0 ; rtb_RealImagtoComplex_im = _rtB -> B_35_375_0 ; _rtB ->
B_35_378_0 = _rtX -> integrator_CSTATE_p ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_416 ; B_35_379_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_417 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_35_381_0 = _rtP -> P_418 ; _rtB -> B_35_383_0 = _rtDW
-> Memory_PreviousInput_p ; } if ( ssGetT ( S ) >= _rtB -> B_35_381_0 ) {
_rtB -> B_35_385_0 = ( _rtB -> B_35_378_0 - B_35_379_0 ) * _rtP -> P_3 ; }
else { _rtB -> B_35_385_0 = _rtB -> B_35_383_0 ; } _rtB -> B_35_386_0 = _rtX
-> integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_421 ; B_35_387_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_422 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_35_389_0 = _rtP -> P_423
; _rtB -> B_35_391_0 = _rtDW -> Memory_PreviousInput_k ; } if ( ssGetT ( S )
>= _rtB -> B_35_389_0 ) { _rtB -> B_35_393_0 = ( _rtB -> B_35_386_0 -
B_35_387_0 ) * _rtP -> P_2 ; } else { _rtB -> B_35_393_0 = _rtB -> B_35_391_0
; } rtb_B_35_397_0 = muDoubleScalarHypot ( rtb_RealImagtoComplex_re ,
rtb_RealImagtoComplex_im ) * muDoubleScalarHypot ( _rtB -> B_35_385_0 , _rtB
-> B_35_393_0 ) * _rtP -> P_425 ; rtb_RealImagtoComplex_re = ( _rtP -> P_426
* muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im , rtb_RealImagtoComplex_re )
- _rtP -> P_427 * muDoubleScalarAtan2 ( _rtB -> B_35_393_0 , _rtB ->
B_35_385_0 ) ) * _rtP -> P_428 ; _rtB -> B_35_403_0 = rtb_B_35_397_0 *
muDoubleScalarCos ( rtb_RealImagtoComplex_re ) ; _rtB -> B_35_405_0 =
rtb_B_35_397_0 * muDoubleScalarSin ( rtb_RealImagtoComplex_re ) ;
ssCallAccelRunBlock ( S , 35 , 406 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_407_0 = _rtP -> P_429 * _rtB -> B_35_145_0 [ 0 ] ; ssCallAccelRunBlock (
S , 35 , 408 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_410_0 = muDoubleScalarSin
( _rtP -> P_433 * ssGetTaskTime ( S , 0 ) + _rtP -> P_434 ) * _rtP -> P_431 +
_rtP -> P_432 ; if ( ( _rtDW -> TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB_a >= ssGetT ( S ) ) ) { _rtB -> B_35_411_0 = 0.0 ; } else {
rtb_B_35_397_0 = _rtDW -> TimeStampA_b ; lastU = & _rtDW -> LastUAtTimeA_f ;
if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { if ( _rtDW ->
TimeStampB_a < ssGetT ( S ) ) { rtb_B_35_397_0 = _rtDW -> TimeStampB_a ;
lastU = & _rtDW -> LastUAtTimeB_n ; } } else { if ( _rtDW -> TimeStampA_b >=
ssGetT ( S ) ) { rtb_B_35_397_0 = _rtDW -> TimeStampB_a ; lastU = & _rtDW ->
LastUAtTimeB_n ; } } _rtB -> B_35_411_0 = ( _rtB -> B_35_410_0 - * lastU ) /
( ssGetT ( S ) - rtb_B_35_397_0 ) ; } _rtB -> B_35_412_0 = _rtB -> B_35_409_0
* _rtB -> B_35_411_0 ; _rtB -> B_35_413_0 = _rtB -> B_35_357_0 + _rtB ->
B_35_412_0 ; _rtB -> B_35_414_0 = 0.0 ; _rtB -> B_35_414_0 += _rtP -> P_437 *
_rtX -> Hi_Pass1_CSTATE ; _rtB -> B_35_414_0 += _rtP -> P_438 * _rtB ->
B_35_413_0 ; _rtB -> B_35_415_0 = 0.0 ; _rtB -> B_35_415_0 += _rtP -> P_442 *
_rtX -> Hw5_CSTATE [ 1 ] ; _rtB -> B_35_416_0 = _rtB -> B_35_415_0 + _rtB ->
B_35_357_0 ; _rtB -> B_35_417_0 = _rtB -> B_35_414_0 - _rtB -> B_35_416_0 ;
_rtB -> B_35_419_0 = 0.0 ; _rtB -> B_35_419_0 += _rtP -> P_446 [ 0 ] * _rtX
-> TransferFcn1_CSTATE_e [ 0 ] ; _rtB -> B_35_419_0 += _rtP -> P_446 [ 1 ] *
_rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtB -> B_35_422_0 = ( _rtP -> P_444 *
_rtB -> B_35_417_0 + _rtB -> B_35_419_0 ) + _rtB -> B_35_421_0 ;
ssCallAccelRunBlock ( S , 35 , 423 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_424_0 = 0.0 ; _rtB -> B_35_424_0 += _rtP -> P_450 * _rtX -> Hw6_CSTATE_f
[ 1 ] ; ssCallAccelRunBlock ( S , 35 , 425 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 5 , 0 ) ) { rtb_B_35_397_0 = ssGetTaskTime ( S , 5 ) ; if
( ssGetTNextWasAdjusted ( S , 5 ) ) { _rtDW -> nextTime =
_ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled != 0 ) { _rtDW
-> justEnabled = 0 ; if ( rtb_B_35_397_0 >= _rtP -> P_455 ) {
rtb_RealImagtoComplex_re = ( rtb_B_35_397_0 - _rtP -> P_455 ) / _rtP -> P_453
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_453 + _rtP ->
P_455 ) + _rtP -> P_454 * _rtP -> P_453 / 100.0 ; if ( rtb_B_35_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue = 0 ; _rtDW ->
nextTime = ( real_T ) ( numCycles + 1U ) * _rtP -> P_453 + _rtP -> P_455 ; }
} else { _rtDW -> numCompleteCycles = _rtP -> P_455 != 0.0 ? - 1 : 0 ; _rtDW
-> currentValue = 0 ; _rtDW -> nextTime = _rtP -> P_455 ; } } else { if (
_rtDW -> nextTime <= rtb_B_35_397_0 ) { if ( _rtDW -> currentValue == 1 ) {
_rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW ->
numCompleteCycles + 1LL ) * _rtP -> P_453 + _rtP -> P_455 ; } else { _rtDW ->
numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ( _rtP
-> P_454 * _rtP -> P_453 * 0.01 + ( real_T ) _rtDW -> numCompleteCycles *
_rtP -> P_453 ) + _rtP -> P_455 ; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW
-> nextTime ) ; if ( _rtDW -> currentValue == 1 ) { _rtB -> B_35_426_0 = _rtP
-> P_452 ; } else { _rtB -> B_35_426_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1
, 0 ) && ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_i , ( _rtB ->
B_35_426_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 30
, 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_eb = 4 ; } } if
( ssIsSampleHit ( S , 6 , 0 ) ) { rtb_B_35_397_0 = ssGetTaskTime ( S , 6 ) ;
if ( ssGetTNextWasAdjusted ( S , 6 ) ) { _rtDW -> nextTime_e =
_ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW -> justEnabled_l != 0 ) { _rtDW
-> justEnabled_l = 0 ; if ( rtb_B_35_397_0 >= _rtP -> P_463 ) {
rtb_RealImagtoComplex_re = ( rtb_B_35_397_0 - _rtP -> P_463 ) / _rtP -> P_461
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_j = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_461 + _rtP ->
P_463 ) + _rtP -> P_462 * _rtP -> P_461 / 100.0 ; if ( rtb_B_35_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_d = 1 ; _rtDW ->
nextTime_e = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_d = 0
; _rtDW -> nextTime_e = ( real_T ) ( numCycles + 1U ) * _rtP -> P_461 + _rtP
-> P_463 ; } } else { _rtDW -> numCompleteCycles_j = _rtP -> P_463 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = _rtP -> P_463 ; }
} else { if ( _rtDW -> nextTime_e <= rtb_B_35_397_0 ) { if ( _rtDW ->
currentValue_d == 1 ) { _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = (
real_T ) ( _rtDW -> numCompleteCycles_j + 1LL ) * _rtP -> P_461 + _rtP ->
P_463 ; } else { _rtDW -> numCompleteCycles_j ++ ; _rtDW -> currentValue_d =
1 ; _rtDW -> nextTime_e = ( _rtP -> P_462 * _rtP -> P_461 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_j * _rtP -> P_461 ) + _rtP -> P_463 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_e ) ; if ( _rtDW ->
currentValue_d == 1 ) { _rtB -> B_35_433_0 = _rtP -> P_460 ; } else { _rtB ->
B_35_433_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_a , ( _rtB -> B_35_433_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 31 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_o = 4 ; } } if ( ssIsSampleHit ( S , 8 , 0 ) ) {
rtb_B_35_397_0 = ssGetTaskTime ( S , 8 ) ; if ( ssGetTNextWasAdjusted ( S , 8
) ) { _rtDW -> nextTime_f = _ssGetVarNextHitTime ( S , 3 ) ; } if ( _rtDW ->
justEnabled_k != 0 ) { _rtDW -> justEnabled_k = 0 ; if ( rtb_B_35_397_0 >=
_rtP -> P_471 ) { rtb_RealImagtoComplex_re = ( rtb_B_35_397_0 - _rtP -> P_471
) / _rtP -> P_469 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_o = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_469 + _rtP ->
P_471 ) + _rtP -> P_470 * _rtP -> P_469 / 100.0 ; if ( rtb_B_35_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_a = 1 ; _rtDW ->
nextTime_f = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_a = 0
; _rtDW -> nextTime_f = ( real_T ) ( numCycles + 1U ) * _rtP -> P_469 + _rtP
-> P_471 ; } } else { _rtDW -> numCompleteCycles_o = _rtP -> P_471 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = _rtP -> P_471 ; }
} else { if ( _rtDW -> nextTime_f <= rtb_B_35_397_0 ) { if ( _rtDW ->
currentValue_a == 1 ) { _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = (
real_T ) ( _rtDW -> numCompleteCycles_o + 1LL ) * _rtP -> P_469 + _rtP ->
P_471 ; } else { _rtDW -> numCompleteCycles_o ++ ; _rtDW -> currentValue_a =
1 ; _rtDW -> nextTime_f = ( _rtP -> P_470 * _rtP -> P_469 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_o * _rtP -> P_469 ) + _rtP -> P_471 ; } } }
_ssSetVarNextHitTime ( S , 3 , _rtDW -> nextTime_f ) ; if ( _rtDW ->
currentValue_a == 1 ) { _rtB -> B_35_440_0 = _rtP -> P_468 ; } else { _rtB ->
B_35_440_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_d , ( _rtB -> B_35_440_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 33 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_p = 4 ; } } _rtB -> B_35_447_0 = _rtP -> P_476 * _rtB
-> B_35_145_0 [ 7 ] ; _rtB -> B_35_451_0 = 0.0 ; _rtB -> B_35_451_0 += _rtP
-> P_478 * _rtX -> TransferFcn_CSTATE_m ; _rtB -> B_35_452_0 = 0.0 ; _rtB ->
B_35_452_0 += _rtP -> P_480 * _rtX -> TransferFcn1_CSTATE_l ; _rtB ->
B_35_453_0 = _rtP -> P_481 * _rtB -> B_35_145_0 [ 2 ] ; _rtB -> B_35_457_0 =
_rtP -> P_482 * _rtB -> B_35_145_0 [ 9 ] ; _rtB -> B_35_461_0 = 0.0 ; _rtB ->
B_35_461_0 += _rtP -> P_484 * _rtX -> TransferFcn2_CSTATE ; _rtB ->
B_35_495_0 = _rtB -> B_35_422_0 + _rtB -> B_35_494_0 ; if ( ssIsSampleHit ( S
, 2 , 0 ) ) { _rtB -> B_35_509_0 = ( real_T ) ( ( _rtB -> B_35_495_0 !=
uGrid_1PH_hd_rtC ( S ) -> B_35_496_0 ) && ( _rtB -> B_35_495_0 >= ( (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_491 , _rtP -> P_492 )
* _rtP -> P_493 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_494 ; if (
ssGetTaskTime ( S , 2 ) < _rtP -> P_495 ) { rtb_B_35_397_0 = _rtP -> P_496 ;
} else { rtb_B_35_397_0 = _rtP -> P_497 ; } _rtB -> B_35_511_0 = _rtB ->
B_35_509_0 * rtb_B_35_397_0 ; ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_498 ) {
rtb_B_35_397_0 = _rtP -> P_499 ; } else { rtb_B_35_397_0 = _rtP -> P_500 ; }
_rtB -> B_35_514_0 = _rtB -> B_2_0_1 * rtb_B_35_397_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_f = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_502 ) ; if ( _rtDW -> Step_MODE_f == 1 ) { _rtB -> B_35_516_0 = _rtP ->
P_504 ; } else { _rtB -> B_35_516_0 = _rtP -> P_503 ; } } _rtB -> B_35_518_0
= rt_Lookup ( _rtP -> P_505 , 5 , ssGetT ( S ) , _rtP -> P_506 ) ; if ( _rtB
-> B_35_515_0 >= _rtP -> P_507 ) { _rtB -> B_35_519_0 = _rtB -> B_35_516_0 ;
} else { _rtB -> B_35_519_0 = _rtB -> B_35_518_0 ; } if ( ( _rtDW ->
TimeStampA_n >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_m >= ssGetT ( S ) ) )
{ _rtB -> B_35_520_0 = 0.0 ; } else { rtb_B_35_397_0 = _rtDW -> TimeStampA_n
; lastU = & _rtDW -> LastUAtTimeA_ma ; if ( _rtDW -> TimeStampA_n < _rtDW ->
TimeStampB_m ) { if ( _rtDW -> TimeStampB_m < ssGetT ( S ) ) { rtb_B_35_397_0
= _rtDW -> TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } else { if (
_rtDW -> TimeStampA_n >= ssGetT ( S ) ) { rtb_B_35_397_0 = _rtDW ->
TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } _rtB -> B_35_520_0 = (
_rtB -> B_35_518_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_35_397_0 ) ; } _rtB
-> B_35_535_0 = ( muDoubleScalarSin ( _rtP -> P_511 * ssGetTaskTime ( S , 0 )
+ _rtP -> P_512 ) * _rtP -> P_509 + _rtP -> P_510 ) * _rtB -> B_35_407_0 ;
_rtB -> B_35_537_0 = ( muDoubleScalarSin ( _rtP -> P_515 * ssGetTaskTime ( S
, 0 ) + _rtP -> P_516 ) * _rtP -> P_513 + _rtP -> P_514 ) * _rtB ->
B_35_407_0 ; _rtB -> B_35_539_0 = ( muDoubleScalarSin ( _rtP -> P_519 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_520 ) * _rtP -> P_517 + _rtP -> P_518 ) *
_rtB -> B_35_358_0 ; _rtB -> B_35_541_0 = ( muDoubleScalarSin ( _rtP -> P_523
* ssGetTaskTime ( S , 0 ) + _rtP -> P_524 ) * _rtP -> P_521 + _rtP -> P_522 )
* _rtB -> B_35_358_0 ; ssCallAccelRunBlock ( S , 35 , 542 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 543 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_547_0 = _rtP -> P_525 * _rtB ->
B_35_145_0 [ 10 ] ; ssCallAccelRunBlock ( S , 35 , 548 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_35_550_0 = _rtB -> B_35_81_0 - _rtP -> P_526 * _rtB ->
B_35_547_0 ; ssCallAccelRunBlock ( S , 35 , 551 , SS_CALL_MDL_OUTPUTS ) ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_35_552_0 = _rtP -> P_527 * _rtB
-> B_35_14_0 ; } _rtB -> B_35_553_0 = ( 1.0 - _rtB -> B_35_27_0 / _rtB ->
B_35_552_0 ) * 100.0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_35_553_0 >= _rtP -> P_528 ? 1 : _rtB ->
B_35_553_0 > _rtP -> P_529 ? 0 : - 1 ; } _rtB -> B_35_554_0 = _rtDW ->
Saturation_MODE == 1 ? _rtP -> P_528 : _rtDW -> Saturation_MODE == - 1 ? _rtP
-> P_529 : _rtB -> B_35_553_0 ; ssCallAccelRunBlock ( S , 35 , 555 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE =
( _rtB -> B_35_547_0 >= 0.0 ) ; } _rtB -> B_35_565_0 = _rtDW -> Abs_MODE > 0
? _rtB -> B_35_547_0 : - _rtB -> B_35_547_0 ; if ( ssIsSampleHit ( S , 1 , 0
) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_i = ( _rtB ->
B_35_547_0 < uGrid_1PH_hd_rtC ( S ) -> B_35_566_0 ) ; } _rtB -> B_35_569_0 =
_rtP -> P_534 * ( real_T ) _rtDW -> Compare_Mode_i ; } _rtB -> B_35_570_0 =
_rtB -> B_35_569_0 - _rtB -> B_35_58_0 ; _rtB -> B_35_571_0 = _rtB ->
B_35_565_0 * _rtB -> B_35_570_0 ; _rtB -> B_35_572_0 = _rtP -> P_535 * _rtB
-> B_35_571_0 ; _rtB -> B_35_576_0 = _rtP -> P_537 * _rtB -> B_35_27_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE_d = ( _rtB -> B_35_66_0 >= 0.0
) ; } _rtB -> B_35_577_0 = _rtDW -> Abs_MODE_d > 0 ? _rtB -> B_35_66_0 : -
_rtB -> B_35_66_0 ; _rtB -> B_35_578_0 = 0.05 * _rtB -> B_35_66_0 + - _rtB ->
B_35_71_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs1_MODE = ( _rtB ->
B_35_578_0 >= 0.0 ) ; } _rtB -> B_35_579_0 = _rtDW -> Abs1_MODE > 0 ? _rtB ->
B_35_578_0 : - _rtB -> B_35_578_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_e = ( _rtB -> B_35_66_0 <
uGrid_1PH_hd_rtC ( S ) -> B_35_580_0 ) ; } _rtB -> B_35_583_0 = _rtP -> P_539
* ( real_T ) _rtDW -> Compare_Mode_e ; } _rtB -> B_35_585_0 = _rtB ->
B_35_577_0 * _rtB -> B_35_579_0 ; _rtB -> B_35_586_0 = ( 0.0 * _rtB ->
B_35_577_0 * _rtB -> B_35_29_0 + _rtB -> B_35_583_0 ) + _rtB -> B_35_585_0 ;
_rtB -> B_35_589_0 = 0.0 ; _rtB -> B_35_589_0 += _rtP -> P_544 * _rtX ->
TransferFcn1_CSTATE_g ; _rtB -> B_35_590_0 = _rtP -> P_545 * _rtB ->
B_35_589_0 ; _rtB -> B_35_591_0 = _rtB -> B_35_574_0 + _rtB -> B_35_590_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_d4 , ( _rtB
-> B_35_146_0 [ 5 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock
( S , 27 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_l = 4 ;
} } _rtB -> B_35_597_0 = _rtP -> P_547 * _rtB -> B_27_0_0 [ 1 ] ;
ssCallAccelRunBlock ( S , 20 , 0 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 601 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 602 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 603 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 19 , 0 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 608 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 609 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 7 , 0 ) ) { rtb_B_35_397_0
= ssGetTaskTime ( S , 7 ) ; if ( ssGetTNextWasAdjusted ( S , 7 ) ) { _rtDW ->
nextTime_j = _ssGetVarNextHitTime ( S , 2 ) ; } if ( _rtDW -> justEnabled_j
!= 0 ) { _rtDW -> justEnabled_j = 0 ; if ( rtb_B_35_397_0 >= _rtP -> P_556 )
{ rtb_RealImagtoComplex_re = ( rtb_B_35_397_0 - _rtP -> P_556 ) / _rtP ->
P_554 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_h = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_554 + _rtP ->
P_556 ) + _rtP -> P_555 * _rtP -> P_554 / 100.0 ; if ( rtb_B_35_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_n = 1 ; _rtDW ->
nextTime_j = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_n = 0
; _rtDW -> nextTime_j = ( real_T ) ( numCycles + 1U ) * _rtP -> P_554 + _rtP
-> P_556 ; } } else { _rtDW -> numCompleteCycles_h = _rtP -> P_556 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = _rtP -> P_556 ; }
} else { if ( _rtDW -> nextTime_j <= rtb_B_35_397_0 ) { if ( _rtDW ->
currentValue_n == 1 ) { _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = (
real_T ) ( _rtDW -> numCompleteCycles_h + 1LL ) * _rtP -> P_554 + _rtP ->
P_556 ; } else { _rtDW -> numCompleteCycles_h ++ ; _rtDW -> currentValue_n =
1 ; _rtDW -> nextTime_j = ( _rtP -> P_555 * _rtP -> P_554 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_h * _rtP -> P_554 ) + _rtP -> P_556 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime_j ) ; if ( _rtDW ->
currentValue_n == 1 ) { _rtB -> B_35_610_0 = _rtP -> P_553 ; } else { _rtB ->
B_35_610_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_o , ( _rtB -> B_35_610_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 32 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_b = 4 ; } } if ( ssIsSampleHit ( S , 9 , 0 ) ) {
rtb_B_35_397_0 = ssGetTaskTime ( S , 9 ) ; if ( ssGetTNextWasAdjusted ( S , 9
) ) { _rtDW -> nextTime_l = _ssGetVarNextHitTime ( S , 4 ) ; } if ( _rtDW ->
justEnabled_o != 0 ) { _rtDW -> justEnabled_o = 0 ; if ( rtb_B_35_397_0 >=
_rtP -> P_564 ) { rtb_RealImagtoComplex_re = ( rtb_B_35_397_0 - _rtP -> P_564
) / _rtP -> P_562 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_hh = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_562 + _rtP ->
P_564 ) + _rtP -> P_563 * _rtP -> P_562 / 100.0 ; if ( rtb_B_35_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_f = 1 ; _rtDW ->
nextTime_l = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_f = 0
; _rtDW -> nextTime_l = ( real_T ) ( numCycles + 1U ) * _rtP -> P_562 + _rtP
-> P_564 ; } } else { _rtDW -> numCompleteCycles_hh = _rtP -> P_564 != 0.0 ?
- 1 : 0 ; _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = _rtP -> P_564 ;
} } else { if ( _rtDW -> nextTime_l <= rtb_B_35_397_0 ) { if ( _rtDW ->
currentValue_f == 1 ) { _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = (
real_T ) ( _rtDW -> numCompleteCycles_hh + 1LL ) * _rtP -> P_562 + _rtP ->
P_564 ; } else { _rtDW -> numCompleteCycles_hh ++ ; _rtDW -> currentValue_f =
1 ; _rtDW -> nextTime_l = ( _rtP -> P_563 * _rtP -> P_562 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_hh * _rtP -> P_562 ) + _rtP -> P_564 ; } } }
_ssSetVarNextHitTime ( S , 4 , _rtDW -> nextTime_l ) ; if ( _rtDW ->
currentValue_f == 1 ) { _rtB -> B_35_617_0 = _rtP -> P_561 ; } else { _rtB ->
B_35_617_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE , ( _rtB -> B_35_617_0 ) ) ; if ( zcEvent != NO_ZCEVENT )
{ ssCallAccelRunBlock ( S , 34 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_g = 4 ; } } if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 35 , 624 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 35 , 625 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 35 , 626 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_632_0 = 0.0 ; _rtB -> B_35_632_0 += _rtP -> P_572 * _rtX ->
Actuador1_CSTATE ; _rtB -> B_35_633_0 = _rtP -> P_573 * _rtB -> B_35_632_0 ;
{ real_T * * uBuffer = ( real_T * * ) & _rtDW -> MotordeCombustin1_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_574 ; _rtB -> B_35_634_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Last , _rtDW -> MotordeCombustin1_IWORK . Tail ,
_rtDW -> MotordeCombustin1_IWORK . Head , _rtP -> P_575 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_35_635_0 = _rtB -> B_35_634_0 - _rtB -> B_35_630_0 ; _rtB ->
B_35_636_0 = _rtP -> P_576 * _rtB -> B_35_145_0 [ 4 ] ; _rtB -> B_35_640_0 =
_rtB -> B_35_631_0 - _rtB -> B_35_6_0 ; _rtB -> B_35_641_0 = _rtP -> P_577 *
_rtB -> B_35_640_0 ; _rtB -> B_35_642_0 = _rtX -> Filter_CSTATE ; _rtB ->
B_35_643_0 = _rtB -> B_35_641_0 - _rtB -> B_35_642_0 ; _rtB -> B_35_644_0 =
_rtP -> P_579 * _rtB -> B_35_643_0 ; _rtB -> B_35_645_0 = _rtP -> P_580 *
_rtB -> B_35_640_0 ; _rtB -> B_35_646_0 = _rtX -> Integrator_CSTATE ; _rtB ->
B_35_647_0 = _rtP -> P_582 * _rtB -> B_35_640_0 ; _rtB -> B_35_648_0 = ( _rtB
-> B_35_647_0 + _rtB -> B_35_646_0 ) + _rtB -> B_35_644_0 ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 35 , 652 ,
SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID10 ( SimStruct * S , int_T tid ) { real_T rtb_B_35_89_0 ; real_T
rtb_B_35_127_0 ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; _rtP = (
( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T *
) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_35_0_0 = _rtP -> P_119 ; _rtB ->
B_35_7_0 = _rtP -> P_127 ; if ( _rtP -> P_131 > _rtP -> P_132 ) { if ( _rtP
-> P_128 > _rtP -> P_129 ) { _rtB -> B_35_11_0 = _rtP -> P_129 ; } else if (
_rtP -> P_128 < _rtP -> P_130 ) { _rtB -> B_35_11_0 = _rtP -> P_130 ; } else
{ _rtB -> B_35_11_0 = _rtP -> P_128 ; } } else { _rtB -> B_35_11_0 = _rtP ->
P_128 ; } _rtB -> B_35_13_0 = _rtP -> P_134 ; _rtB -> B_35_24_0 = _rtP ->
P_144 ; _rtB -> B_35_30_0 = _rtP -> P_149 ; _rtB -> B_35_31_0 = _rtP -> P_150
; _rtB -> B_35_37_0 = _rtP -> P_152 ; _rtB -> B_35_38_0 = _rtP -> P_153 ;
_rtB -> B_35_48_0 = _rtP -> P_156 ; _rtB -> B_35_49_0 = _rtP -> P_157 ; _rtB
-> B_35_50_0 = _rtP -> P_158 ; _rtB -> B_35_57_0 = _rtP -> P_159 ; if ( _rtP
-> P_162 > _rtP -> P_164 ) { _rtB -> B_35_65_0 = _rtP -> P_161 ; } else {
_rtB -> B_35_65_0 = _rtP -> P_163 ; } _rtB -> B_35_67_0 = _rtP -> P_167 ;
_rtB -> B_35_68_0 = _rtP -> P_168 ; _rtB -> B_35_72_0 = _rtP -> P_170 ; _rtB
-> B_35_73_0 = _rtP -> P_171 ; rtb_B_35_89_0 = _rtP -> P_178 + _rtP -> P_179
; _rtB -> B_35_95_0 = _rtP -> P_181 ; _rtB -> B_35_96_0 = ( ( rtb_B_35_89_0 -
_rtP -> P_180 ) * _rtP -> P_177 + _rtP -> P_176 ) * ( _rtP -> P_174 / _rtP ->
P_175 ) * _rtB -> B_35_95_0 ; _rtB -> B_35_97_0 = _rtP -> P_182 ; _rtB ->
B_35_98_0 = _rtP -> P_183 ; _rtB -> B_35_99_0 = _rtP -> P_184 ; _rtB ->
B_35_100_0 = 0.0 / _rtB -> B_35_99_0 ; _rtB -> B_35_105_0 = _rtP -> P_186 *
rtb_B_35_89_0 / _rtP -> P_187 * _rtP -> P_185 ; _rtB -> B_35_106_0 = _rtP ->
P_188 ; rtb_B_35_127_0 = rtb_B_35_89_0 / _rtP -> P_180 ; _rtB -> B_35_130_0 =
_rtP -> P_176 / ( muDoubleScalarExp ( _rtP -> P_192 * _rtP -> P_187 / ( _rtP
-> P_186 * _rtP -> P_193 * rtb_B_35_89_0 * _rtP -> P_185 ) ) - _rtP -> P_194
) * ( rtb_B_35_127_0 * rtb_B_35_127_0 * rtb_B_35_127_0 ) * muDoubleScalarExp
( ( _rtP -> P_190 / rtb_B_35_89_0 - _rtP -> P_189 / _rtP -> P_180 ) * ( _rtP
-> P_187 * _rtP -> P_191 / ( _rtP -> P_186 * _rtP -> P_185 ) ) ) ; _rtB ->
B_35_133_0 = _rtP -> P_196 ; _rtB -> B_35_134_0 = _rtP -> P_197 ; _rtB ->
B_35_135_0 = _rtP -> P_198 ; _rtB -> B_35_136_0 = _rtP -> P_199 ; _rtB ->
B_35_137_0 = _rtP -> P_200 ; _rtB -> B_35_138_0 = _rtP -> P_201 ; _rtB ->
B_35_139_0 = _rtP -> P_202 ; _rtB -> B_35_140_0 = _rtP -> P_203 ; _rtB ->
B_35_141_0 = _rtP -> P_204 ; _rtB -> B_35_142_0 = _rtP -> P_205 ; _rtB ->
B_35_143_0 = _rtP -> P_206 ; _rtB -> B_35_144_0 = _rtP -> P_207 ; _rtB ->
B_35_190_0 = _rtP -> P_322 ; _rtB -> B_35_194_0 = _rtP -> P_323 ; _rtB ->
B_35_198_0 = _rtP -> P_324 ; _rtB -> B_35_202_0 = _rtP -> P_325 ; _rtB ->
B_35_210_0 = _rtP -> P_326 ; _rtB -> B_35_231_0 = _rtP -> P_338 ; _rtB ->
B_35_269_0 = _rtP -> P_352 ; _rtB -> B_35_273_0 = _rtP -> P_353 ; _rtB ->
B_35_277_0 = _rtP -> P_354 ; _rtB -> B_35_281_0 = _rtP -> P_355 ; _rtB ->
B_35_289_0 = _rtP -> P_356 ; _rtB -> B_35_311_0 = _rtP -> P_382 ; _rtB ->
B_35_342_0 = _rtP -> P_394 ; memcpy ( & _rtB -> B_35_333_0 [ 0 ] , & _rtP ->
P_392 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_35_334_0 [
0 ] , & _rtP -> P_393 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB
-> B_35_347_0 [ 0 ] , & _rtP -> P_395 [ 0 ] , 40000U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_35_348_0 [ 0 ] , & _rtP -> P_396 [ 0 ] , 40000U * sizeof
( real_T ) ) ; _rtB -> B_35_356_0 = _rtP -> P_399 ; _rtB -> B_35_409_0 = _rtP
-> P_430 ; _rtB -> B_35_421_0 = _rtP -> P_447 ; _rtB -> B_35_428_0 = _rtP ->
P_456 ; _rtB -> B_35_429_0 = _rtP -> P_457 ; _rtB -> B_35_430_0 = _rtP ->
P_458 ; _rtB -> B_35_431_0 = _rtP -> P_459 ; _rtB -> B_35_435_0 = _rtP ->
P_464 ; _rtB -> B_35_436_0 = _rtP -> P_465 ; _rtB -> B_35_437_0 = _rtP ->
P_466 ; _rtB -> B_35_438_0 = _rtP -> P_467 ; _rtB -> B_35_442_0 = _rtP ->
P_472 ; _rtB -> B_35_443_0 = _rtP -> P_473 ; _rtB -> B_35_444_0 = _rtP ->
P_474 ; _rtB -> B_35_445_0 = _rtP -> P_475 ; _rtB -> B_35_474_0 = _rtP ->
P_485 ; _rtB -> B_35_478_0 = _rtP -> P_486 ; _rtB -> B_35_482_0 = _rtP ->
P_487 ; _rtB -> B_35_486_0 = _rtP -> P_488 ; _rtB -> B_35_494_0 = _rtP ->
P_489 ; _rtB -> B_35_515_0 = _rtP -> P_501 ; _rtB -> B_35_574_0 = _rtP ->
P_536 + _rtP -> P_532 ; if ( _rtP -> P_530 > _rtP -> P_542 ) { rtb_B_35_89_0
= ( _rtB -> B_35_574_0 - 293.15 ) * 0.0 + 1.0339999999999974 ; if (
rtb_B_35_89_0 > _rtP -> P_540 ) { _rtB -> B_35_588_0 = _rtP -> P_540 ; } else
if ( rtb_B_35_89_0 < _rtP -> P_541 ) { _rtB -> B_35_588_0 = _rtP -> P_541 ; }
else { _rtB -> B_35_588_0 = rtb_B_35_89_0 ; } } else { _rtB -> B_35_588_0 =
_rtP -> P_531 ; } _rtB -> B_35_595_0 = _rtP -> P_546 ; _rtB -> B_35_604_0 =
_rtP -> P_550 ; _rtB -> B_35_598_0 [ 0 ] = _rtP -> P_548 [ 0 ] ; _rtB ->
B_35_599_0 [ 0 ] = _rtP -> P_549 [ 0 ] ; _rtB -> B_35_605_0 [ 0 ] = _rtP ->
P_551 [ 0 ] ; _rtB -> B_35_606_0 [ 0 ] = _rtP -> P_552 [ 0 ] ; _rtB ->
B_35_598_0 [ 1 ] = _rtP -> P_548 [ 1 ] ; _rtB -> B_35_599_0 [ 1 ] = _rtP ->
P_549 [ 1 ] ; _rtB -> B_35_605_0 [ 1 ] = _rtP -> P_551 [ 1 ] ; _rtB ->
B_35_606_0 [ 1 ] = _rtP -> P_552 [ 1 ] ; _rtB -> B_35_612_0 = _rtP -> P_557 ;
_rtB -> B_35_613_0 = _rtP -> P_558 ; _rtB -> B_35_614_0 = _rtP -> P_559 ;
_rtB -> B_35_615_0 = _rtP -> P_560 ; _rtB -> B_35_619_0 = _rtP -> P_565 ;
_rtB -> B_35_620_0 = _rtP -> P_566 ; _rtB -> B_35_621_0 = _rtP -> P_567 ;
_rtB -> B_35_622_0 = _rtP -> P_568 ; _rtB -> B_35_630_0 = _rtP -> P_569 ;
_rtB -> B_35_631_0 = _rtP -> P_570 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = (
( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T *
) _ssGetModelBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_35_588_0 ; _rtDW -> itinit_PreviousInput =
_rtB -> B_35_576_0 ; } _rtDW -> inti_IWORK = 0 ; if ( _rtX -> inti_CSTATE ==
_rtP -> P_141 ) { switch ( _rtDW -> inti_MODE ) { case 3 : if ( _rtB ->
B_35_547_0 < 0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 1 ; }
break ; case 1 : if ( _rtB -> B_35_547_0 >= 0.0 ) { _rtDW -> inti_MODE = 3 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_35_547_0 < 0.0 ) { _rtDW -> inti_MODE = 1 ; } else { _rtDW
-> inti_MODE = 3 ; } break ; } } else if ( _rtX -> inti_CSTATE == _rtP ->
P_142 ) { switch ( _rtDW -> inti_MODE ) { case 4 : if ( _rtB -> B_35_547_0 >
0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 2 ; } break ; case
2 : if ( _rtB -> B_35_547_0 <= 0.0 ) { _rtDW -> inti_MODE = 4 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_35_547_0 > 0.0 ) { _rtDW -> inti_MODE = 2 ; } else { _rtDW
-> inti_MODE = 4 ; } break ; } } else { _rtDW -> inti_MODE = 0 ; }
ssCallAccelRunBlock ( S , 35 , 145 , SS_CALL_MDL_UPDATE ) ; if ( _rtDW ->
TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == ( rtInf ) ) {
_rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } else
if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else { _rtDW -> TimeStampB
= ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } * lastU = _rtB ->
B_35_234_0 ; if ( _rtDW -> TimeStampA_k == ( rtInf ) ) { _rtDW ->
TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_m ; } else if (
_rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW -> TimeStampB_f = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_o ; } else if ( _rtDW -> TimeStampA_k < _rtDW
-> TimeStampB_f ) { _rtDW -> TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_m ; } else { _rtDW -> TimeStampB_f = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB_o ; } * lastU = _rtB -> B_35_314_0 ; if ( ssIsSampleHit
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
TransportDelay_IWORK . Last , simTime - _rtP -> P_406 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_35_360_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_35_367_0 ; } { real_T * * uBuffer = ( real_T
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
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_411 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_35_368_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_f = _rtB -> B_35_375_0 ; } { real_T * * uBuffer = (
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
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_416 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_35_378_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_p = _rtB -> B_35_385_0 ; } { real_T * * uBuffer = (
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
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_421 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_35_386_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_k = _rtB -> B_35_393_0 ; } if ( _rtDW -> TimeStampA_b ==
( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_f ; } else if ( _rtDW -> TimeStampB_a == ( rtInf ) ) { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } else if (
_rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { _rtDW -> TimeStampA_b =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } * lastU =
_rtB -> B_35_410_0 ; if ( _rtDW -> TimeStampA_n == ( rtInf ) ) { _rtDW ->
TimeStampA_n = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_ma ; } else if
( _rtDW -> TimeStampB_m == ( rtInf ) ) { _rtDW -> TimeStampB_m = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeB_g ; } else if ( _rtDW -> TimeStampA_n <
_rtDW -> TimeStampB_m ) { _rtDW -> TimeStampA_n = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA_ma ; } else { _rtDW -> TimeStampB_m = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_g ; } * lastU = _rtB -> B_35_518_0 ; { real_T
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
& _rtDW -> MotordeCombustin1_IWORK . Last , simTime - _rtP -> P_574 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
MotordeCombustin1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = _rtB -> B_35_633_0 ; } UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID10 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
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
P_120 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtXdot -> Dinmicaeneleje1_CSTATE +=
_rtB -> B_35_635_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_124 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_35_636_0 ; _rtXdot -> Currentfilter_CSTATE =
0.0 ; _rtXdot -> Currentfilter_CSTATE += _rtP -> P_137 * _rtX ->
Currentfilter_CSTATE ; _rtXdot -> Currentfilter_CSTATE += _rtB -> B_35_547_0
; if ( ( _rtDW -> inti_MODE != 3 ) && ( _rtDW -> inti_MODE != 4 ) ) { _rtXdot
-> inti_CSTATE = _rtB -> B_35_547_0 ; _rtXdis -> inti_CSTATE = false ; } else
{ _rtXdot -> inti_CSTATE = 0.0 ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW
-> inti_MODE == 4 ) ) { _rtXdis -> inti_CSTATE = true ; } } _rtXdot ->
StateSpace_CSTATE = 0.0 ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_145 *
_rtX -> StateSpace_CSTATE ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_146 *
_rtB -> B_35_591_0 ; _rtXdot -> Integrator2_CSTATE = _rtB -> B_35_572_0 ;
_rtXdot -> Currentfilter1_CSTATE = 0.0 ; _rtXdot -> Currentfilter1_CSTATE +=
_rtP -> P_165 * _rtX -> Currentfilter1_CSTATE ; _rtXdot ->
Currentfilter1_CSTATE += _rtB -> B_35_547_0 ; ssCallAccelRunBlock ( S , 35 ,
145 , SS_CALL_MDL_DERIVATIVES ) ; _rtXdot -> Hw2_CSTATE [ 0 ] = 0.0 ; _rtXdot
-> Hw6_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_270 [ 0 ] *
_rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_270 [ 1 ]
* _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 1 ] += _rtP -> P_270 [ 2
] * _rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_270 [
3 ] * _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_270
[ 4 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP ->
P_270 [ 5 ] * _rtX -> Hw2_CSTATE [ 3 ] ; _rtXdot -> Hw2_CSTATE [ 3 ] += _rtP
-> P_270 [ 6 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] +=
_rtP -> P_271 * _rtB -> B_35_166_0 [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 0 ] +=
_rtP -> P_274 [ 0 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [ 0 ]
+= _rtP -> P_274 [ 1 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 1
] += _rtP -> P_274 [ 2 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [
2 ] += _rtP -> P_274 [ 3 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE
[ 2 ] += _rtP -> P_274 [ 4 ] * _rtX -> Hw6_CSTATE [ 2 ] ; _rtXdot ->
Hw6_CSTATE [ 2 ] += _rtP -> P_274 [ 5 ] * _rtX -> Hw6_CSTATE [ 3 ] ; _rtXdot
-> Hw6_CSTATE [ 3 ] += _rtP -> P_274 [ 6 ] * _rtX -> Hw6_CSTATE [ 2 ] ;
_rtXdot -> Hw6_CSTATE [ 0 ] += _rtP -> P_275 * _rtB -> B_35_166_0 [ 2 ] ;
_rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_278 [ 0 ] * _rtX -> Hw1_CSTATE [ 0 ]
; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_278 [ 1 ] * _rtX -> Hw1_CSTATE [ 1
] ; _rtXdot -> Hw1_CSTATE [ 1 ] += _rtP -> P_278 [ 2 ] * _rtX -> Hw1_CSTATE [
0 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_278 [ 3 ] * _rtX -> Hw1_CSTATE
[ 1 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_278 [ 4 ] * _rtX ->
Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_278 [ 5 ] * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtXdot -> Hw1_CSTATE [ 3 ] += _rtP -> P_278 [ 6 ] *
_rtX -> Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_279 *
_rtB -> B_35_290_0 [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_282 [ 0 ]
* _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_282 [ 1
] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 1 ] += _rtP -> P_282 [
2 ] * _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP -> P_282
[ 3 ] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP ->
P_282 [ 4 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP
-> P_282 [ 5 ] * _rtX -> Hw3_CSTATE [ 3 ] ; _rtXdot -> Hw3_CSTATE [ 3 ] +=
_rtP -> P_282 [ 6 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 0 ]
+= _rtP -> P_283 * _rtB -> B_35_290_0 [ 2 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] =
0.0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 0 ] = 0.0
; _rtXdot -> Hw3_CSTATE_e [ 0 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw1_CSTATE_k [ 1 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw3_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP ->
P_286 [ 0 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP
-> P_286 [ 1 ] * _rtX -> Hw4_CSTATE [ 1 ] ; _rtXdot -> Hw4_CSTATE [ 1 ] +=
_rtP -> P_286 [ 2 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ]
+= _rtP -> P_287 * _rtB -> B_35_173_0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] += _rtP
-> P_290 [ 0 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot -> Hw1_CSTATE_k [ 0 ]
+= _rtP -> P_290 [ 1 ] * _rtX -> Hw1_CSTATE_k [ 1 ] ; _rtXdot -> Hw1_CSTATE_k
[ 1 ] += _rtP -> P_290 [ 2 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot ->
Hw1_CSTATE_k [ 0 ] += _rtP -> P_291 * _rtB -> B_35_172_0 ; _rtXdot ->
Hw7_CSTATE [ 0 ] += _rtP -> P_294 [ 0 ] * _rtX -> Hw7_CSTATE [ 0 ] ; _rtXdot
-> Hw7_CSTATE [ 0 ] += _rtP -> P_294 [ 1 ] * _rtX -> Hw7_CSTATE [ 1 ] ;
_rtXdot -> Hw7_CSTATE [ 1 ] += _rtP -> P_294 [ 2 ] * _rtX -> Hw7_CSTATE [ 0 ]
; _rtXdot -> Hw7_CSTATE [ 0 ] += _rtP -> P_295 * _rtB -> B_35_251_0 ; _rtXdot
-> Hw3_CSTATE_e [ 0 ] += _rtP -> P_298 [ 0 ] * _rtX -> Hw3_CSTATE_e [ 0 ] ;
_rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_298 [ 1 ] * _rtX -> Hw3_CSTATE_e [
1 ] ; _rtXdot -> Hw3_CSTATE_e [ 1 ] += _rtP -> P_298 [ 2 ] * _rtX ->
Hw3_CSTATE_e [ 0 ] ; _rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_299 * _rtB ->
B_35_252_0 ; _rtXdot -> TransferFcn_CSTATE_j = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_j += _rtP -> P_317 * _rtX -> TransferFcn_CSTATE_j ;
_rtXdot -> TransferFcn_CSTATE_j += _rtB -> B_35_168_0 ; _rtXdot ->
TransferFcn1_CSTATE = 0.0 ; _rtXdot -> TransferFcn1_CSTATE += _rtP -> P_319 *
_rtX -> TransferFcn1_CSTATE ; _rtXdot -> TransferFcn1_CSTATE += _rtB ->
B_35_174_0 ; _rtXdot -> TransferFcn_CSTATE_g = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_g += _rtP -> P_347 * _rtX -> TransferFcn_CSTATE_g ;
_rtXdot -> TransferFcn_CSTATE_g += _rtB -> B_35_247_0 ; _rtXdot ->
TransferFcn1_CSTATE_p = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_p += _rtP ->
P_349 * _rtX -> TransferFcn1_CSTATE_p ; _rtXdot -> TransferFcn1_CSTATE_p +=
_rtB -> B_35_253_0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] = 0.0 ; _rtXdot ->
Hw2_CSTATE_p [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP -> P_400 [ 0
] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP ->
P_400 [ 1 ] * _rtX -> Hw2_CSTATE_p [ 1 ] ; _rtXdot -> Hw2_CSTATE_p [ 1 ] +=
_rtP -> P_400 [ 2 ] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [
0 ] += _rtP -> P_401 * _rtB -> B_35_451_0 ; _rtXdot -> integrator_CSTATE =
_rtB -> B_35_535_0 ; _rtXdot -> integrator_CSTATE_i = _rtB -> B_35_537_0 ;
_rtXdot -> integrator_CSTATE_p = _rtB -> B_35_539_0 ; _rtXdot ->
integrator_CSTATE_l = _rtB -> B_35_541_0 ; _rtXdot -> Hi_Pass1_CSTATE = 0.0 ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_435 * _rtX -> Hi_Pass1_CSTATE ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_436 * _rtB -> B_35_413_0 ; _rtXdot ->
Hw5_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] = 0.0 ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtP -> P_445 [ 0 ] * _rtX ->
TransferFcn1_CSTATE_e [ 0 ] ; _rtXdot -> Hw5_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
TransferFcn1_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] +=
_rtP -> P_445 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtXdot ->
Hw5_CSTATE [ 0 ] += _rtP -> P_440 [ 0 ] * _rtX -> Hw5_CSTATE [ 0 ] ; _rtXdot
-> Hw5_CSTATE [ 0 ] += _rtP -> P_440 [ 1 ] * _rtX -> Hw5_CSTATE [ 1 ] ;
_rtXdot -> Hw5_CSTATE [ 1 ] += _rtP -> P_440 [ 2 ] * _rtX -> Hw5_CSTATE [ 0 ]
; _rtXdot -> Hw5_CSTATE [ 0 ] += _rtP -> P_441 * _rtB -> B_35_461_0 ; _rtXdot
-> TransferFcn1_CSTATE_e [ 1 ] += _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtB -> B_35_417_0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] = 0.0 ; _rtXdot -> Hw6_CSTATE_f [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] += _rtP -> P_448 [ 0 ] * _rtX -> Hw6_CSTATE_f [ 0 ] ;
_rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_448 [ 1 ] * _rtX -> Hw6_CSTATE_f [
1 ] ; _rtXdot -> Hw6_CSTATE_f [ 1 ] += _rtP -> P_448 [ 2 ] * _rtX ->
Hw6_CSTATE_f [ 0 ] ; _rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_449 * _rtB ->
B_35_452_0 ; _rtXdot -> TransferFcn_CSTATE_m = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_m += _rtP -> P_477 * _rtX -> TransferFcn_CSTATE_m ;
_rtXdot -> TransferFcn_CSTATE_m += _rtB -> B_35_447_0 ; _rtXdot ->
TransferFcn1_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_l += _rtP ->
P_479 * _rtX -> TransferFcn1_CSTATE_l ; _rtXdot -> TransferFcn1_CSTATE_l +=
_rtB -> B_35_453_0 ; _rtXdot -> TransferFcn2_CSTATE = 0.0 ; _rtXdot ->
TransferFcn2_CSTATE += _rtP -> P_483 * _rtX -> TransferFcn2_CSTATE ; _rtXdot
-> TransferFcn2_CSTATE += _rtB -> B_35_457_0 ; _rtXdot ->
TransferFcn1_CSTATE_g = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_g += _rtP ->
P_543 * _rtX -> TransferFcn1_CSTATE_g ; _rtXdot -> TransferFcn1_CSTATE_g +=
_rtB -> B_35_586_0 ; _rtXdot -> Actuador1_CSTATE = 0.0 ; _rtXdot ->
Actuador1_CSTATE += _rtP -> P_571 * _rtX -> Actuador1_CSTATE ; _rtXdot ->
Actuador1_CSTATE += _rtB -> B_35_648_0 ; _rtXdot -> Filter_CSTATE = _rtB ->
B_35_644_0 ; _rtXdot -> Integrator_CSTATE = _rtB -> B_35_645_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; ssCallAccelRunBlock ( S , 35 , 145 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { boolean_T anyStateSaturated
; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX
; ZCV_uGrid_1PH_hd_T * _rtZCSV ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_uGrid_1PH_hd_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( (
X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_35_16_0 -
uGrid_1PH_hd_rtC ( S ) -> B_35_17_0 ; if ( ( _rtDW -> inti_MODE == 1 ) && (
_rtX -> inti_CSTATE >= _rtP -> P_141 ) ) { _rtZCSV -> inti_IntgUpLimit_ZC =
0.0 ; } else { _rtZCSV -> inti_IntgUpLimit_ZC = _rtX -> inti_CSTATE - _rtP ->
P_141 ; } if ( ( _rtDW -> inti_MODE == 2 ) && ( _rtX -> inti_CSTATE <= _rtP
-> P_142 ) ) { _rtZCSV -> inti_IntgLoLimit_ZC = 0.0 ; } else { _rtZCSV ->
inti_IntgLoLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_142 ; }
anyStateSaturated = false ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW ->
inti_MODE == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> inti_LeaveSaturate_ZC = _rtB -> B_35_547_0 ; } else { _rtZCSV ->
inti_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB
-> B_35_22_0 - _rtB -> B_35_15_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB
-> B_35_22_0 - _rtB -> B_35_24_0 ; _rtZCSV -> LowerRelop1_RelopInput_ZC_i =
_rtB -> B_35_22_0 - _rtB -> B_35_39_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f
= _rtB -> B_35_22_0 - _rtB -> B_35_41_0 ; _rtZCSV -> Compare_RelopInput_ZC_d
= _rtB -> B_35_16_0 - uGrid_1PH_hd_rtC ( S ) -> B_35_45_0 ; _rtZCSV ->
LowerRelop1_RelopInput_ZC_a = _rtB -> B_35_76_0 - _rtB -> B_35_7_0 ; _rtZCSV
-> UpperRelop_RelopInput_ZC_g = _rtB -> B_35_76_0 - _rtB -> B_35_78_0 ;
ssCallAccelRunBlock ( S , 35 , 145 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 35 , 146 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 35 , 166 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_339 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_35_236_0 - _rtP -> P_345 ;
ssCallAccelRunBlock ( S , 35 , 290 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC_d = ssGetT ( S ) - _rtP -> P_383 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_j = _rtB -> B_35_316_0 - _rtP -> P_389 ; _rtZCSV
-> Step_StepTime_ZC_b = ssGetT ( S ) - _rtP -> P_502 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_e = _rtB -> B_35_520_0 - _rtP -> P_508 ; _rtZCSV
-> Saturation_UprLim_ZC = _rtB -> B_35_553_0 - _rtP -> P_528 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_35_553_0 - _rtP -> P_529 ; _rtZCSV ->
Abs_AbsZc_ZC = _rtB -> B_35_547_0 ; _rtZCSV -> Compare_RelopInput_ZC_f = _rtB
-> B_35_547_0 - uGrid_1PH_hd_rtC ( S ) -> B_35_566_0 ; _rtZCSV ->
Abs_AbsZc_ZC_j = _rtB -> B_35_66_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_35_578_0 ; _rtZCSV -> Compare_RelopInput_ZC_b = _rtB -> B_35_66_0 -
uGrid_1PH_hd_rtC ( S ) -> B_35_580_0 ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3713779156U ) ; ssSetChecksumVal
( S , 1 , 2043591230U ) ; ssSetChecksumVal ( S , 2 , 1133517289U ) ;
ssSetChecksumVal ( S , 3 , 3481222857U ) ; { mxArray * slVerStructMat = NULL
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
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_130 = rtMinusInf ; ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_142 = rtMinusInf ; } static
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
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID10 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
