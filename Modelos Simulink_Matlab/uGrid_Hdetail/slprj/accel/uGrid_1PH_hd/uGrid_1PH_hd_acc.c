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
S ) { ssCallAccelRunBlock ( S , 31 , 131 , SS_CALL_MDL_OUTPUTS ) ; } void
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term ( SimStruct *
const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T
B_31_359_0 ; real_T B_31_367_0 ; real_T B_31_377_0 ; real_T B_31_385_0 ;
boolean_T resetIntg ; ZCEventType zcEvent ; real_T * lastU ; uint32_T
numCycles ; real_T rtb_B_31_395_0 ; real_T rtb_RealImagtoComplex_re ; real_T
rtb_RealImagtoComplex_im ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP
; X_uGrid_1PH_hd_T * _rtX ; PrevZCX_uGrid_1PH_hd_T * _rtZCE ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtZCE = ( ( PrevZCX_uGrid_1PH_hd_T * ) _ssGetPrevZCSigState ( S )
) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_31_1_0 = 0.0 ; _rtB -> B_31_1_0 +=
_rtP -> P_75 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtB -> B_31_2_0 = _rtP ->
P_76 * _rtB -> B_31_1_0 ; _rtB -> B_31_3_0 = _rtP -> P_77 * _rtB -> B_31_2_0
; _rtB -> B_31_4_0 = 0.0 ; _rtB -> B_31_4_0 += _rtP -> P_79 * _rtX ->
TransferFcn_CSTATE ; _rtB -> B_31_5_0 = _rtP -> P_80 * _rtB -> B_31_4_0 ;
_rtB -> B_31_6_0 = _rtB -> B_31_3_0 - _rtB -> B_31_5_0 ; _rtB -> B_31_16_0 =
0.0 ; _rtB -> B_31_16_0 += _rtP -> P_92 * _rtX -> Currentfilter_CSTATE ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_31_14_0 = _rtDW ->
itinit1_PreviousInput ; _rtB -> B_31_15_0 = _rtP -> P_90 * _rtB -> B_31_14_0
; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode = ( _rtB ->
B_31_16_0 > uGrid_1PH_hd_rtC ( S ) -> B_31_17_0 ) ; } _rtB -> B_31_19_0 =
_rtDW -> Compare_Mode ; _rtB -> B_31_20_0 = _rtDW -> itinit_PreviousInput ; }
if ( ssIsMajorTimeStep ( S ) ) { resetIntg = false ; zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & _rtZCE -> inti_Reset_ZCE , ( _rtB -> B_31_19_0 ) ) ;
if ( ( zcEvent != NO_ZCEVENT ) || ( _rtDW -> inti_IWORK != 0 ) ) { resetIntg
= true ; _rtX -> inti_CSTATE = _rtB -> B_31_20_0 ; } if ( resetIntg ) {
ssSetSolverNeedsReset ( S ) ; } if ( _rtX -> inti_CSTATE >= _rtP -> P_95 ) {
_rtX -> inti_CSTATE = _rtP -> P_95 ; } else { if ( _rtX -> inti_CSTATE <=
_rtP -> P_96 ) { _rtX -> inti_CSTATE = _rtP -> P_96 ; } } } _rtB -> B_31_21_0
= _rtX -> inti_CSTATE ; _rtB -> B_31_22_0 = _rtP -> P_97 * _rtB -> B_31_21_0
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> LowerRelop1_Mode = ( _rtB -> B_31_22_0 > _rtB -> B_31_15_0 ) ; _rtDW ->
UpperRelop_Mode = ( _rtB -> B_31_22_0 < _rtB -> B_31_24_0 ) ; } _rtB ->
B_31_23_0 = _rtDW -> LowerRelop1_Mode ; _rtB -> B_31_25_0 = _rtDW ->
UpperRelop_Mode ; } if ( _rtB -> B_31_23_0 ) { _rtB -> B_31_27_0 = _rtB ->
B_31_15_0 ; } else { if ( _rtB -> B_31_25_0 ) { _rtB -> B_13_0_0 = _rtB ->
B_31_24_0 ; } else { _rtB -> B_13_0_0 = _rtB -> B_31_22_0 ; } _rtB ->
B_31_27_0 = _rtB -> B_13_0_0 ; } _rtB -> B_31_29_0 = 0.0 ; _rtB -> B_31_29_0
+= _rtP -> P_101 * _rtX -> StateSpace_CSTATE ; if ( _rtB -> B_31_30_0 > _rtP
-> P_105 ) { _rtB -> B_31_33_0 = muDoubleScalarExp ( ( 1.0 / _rtB ->
B_31_29_0 - 0.0034112229234180458 ) * 0.0 ) ; } else { _rtB -> B_31_33_0 =
_rtB -> B_31_31_0 ; } _rtB -> B_31_34_0 = - 0.0605295518538322 * _rtB ->
B_31_14_0 / ( _rtB -> B_31_14_0 - _rtB -> B_31_27_0 ) * _rtB -> B_31_27_0 *
_rtB -> B_31_33_0 ; _rtB -> B_31_36_0 = - _rtB -> B_31_19_0 *
0.0605295518538322 * _rtB -> B_31_16_0 * _rtB -> B_31_14_0 / ( _rtB ->
B_31_14_0 - _rtB -> B_31_27_0 ) * _rtB -> B_31_33_0 ; if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_31_39_0 = _rtP -> P_108 * _rtB -> B_31_14_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> LowerRelop1_Mode_g = ( _rtB -> B_31_22_0
> _rtB -> B_31_39_0 ) ; } _rtB -> B_31_40_0 = _rtDW -> LowerRelop1_Mode_g ;
_rtB -> B_31_41_0 = - _rtB -> B_31_39_0 * 0.999 * 0.1 * 0.9999 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> UpperRelop_Mode_g = ( _rtB -> B_31_22_0
< _rtB -> B_31_41_0 ) ; } _rtB -> B_31_42_0 = _rtDW -> UpperRelop_Mode_g ; if
( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_k = ( _rtB -> B_31_16_0 <
uGrid_1PH_hd_rtC ( S ) -> B_31_45_0 ) ; } _rtB -> B_31_47_0 = _rtDW ->
Compare_Mode_k ; } if ( _rtB -> B_31_40_0 ) { _rtB -> B_31_44_0 = _rtB ->
B_31_39_0 ; } else { if ( _rtB -> B_31_42_0 ) { _rtB -> B_14_0_0 = _rtB ->
B_31_41_0 ; } else { _rtB -> B_14_0_0 = _rtB -> B_31_22_0 ; } _rtB ->
B_31_44_0 = _rtB -> B_14_0_0 ; } switch ( ( int32_T ) _rtB -> B_31_37_0 ) {
case 1 : _rtB -> B_10_0_0 [ 0 ] = _rtB -> B_31_38_0 * _rtB -> B_31_44_0 ;
_rtB -> B_10_0_0 [ 1 ] = _rtB -> B_31_38_0 * _rtB -> B_31_16_0 ; _rtB ->
B_10_0_0 [ 2 ] = _rtB -> B_31_38_0 * _rtB -> B_31_47_0 ; _rtB -> B_10_0_0 [ 3
] = _rtB -> B_31_38_0 * _rtB -> B_31_14_0 ; _rtB -> B_31_55_0 = - _rtB ->
B_10_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_10_0_0 [ 1 ] * (
1.0339999999999974 / ( _rtB -> B_10_0_0 [ 0 ] + 0.10339999999999974 ) ) ;
break ; case 2 : _rtB -> B_9_0_0 [ 0 ] = _rtB -> B_31_48_0 * _rtB ->
B_31_44_0 ; _rtB -> B_9_0_0 [ 1 ] = _rtB -> B_31_48_0 * _rtB -> B_31_16_0 ;
_rtB -> B_9_0_0 [ 2 ] = _rtB -> B_31_48_0 * _rtB -> B_31_47_0 ; _rtB ->
B_9_0_0 [ 3 ] = _rtB -> B_31_48_0 * _rtB -> B_31_14_0 ; _rtB -> B_31_55_0 = -
_rtB -> B_9_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_9_0_0 [ 1 ] * _rtB ->
B_9_0_0 [ 3 ] / ( _rtB -> B_9_0_0 [ 3 ] * 0.1 + _rtB -> B_9_0_0 [ 0 ] ) ;
break ; case 3 : _rtB -> B_8_0_0 [ 0 ] = _rtB -> B_31_49_0 * _rtB ->
B_31_44_0 ; _rtB -> B_8_0_0 [ 1 ] = _rtB -> B_31_49_0 * _rtB -> B_31_16_0 ;
_rtB -> B_8_0_0 [ 2 ] = _rtB -> B_31_49_0 * _rtB -> B_31_47_0 ; _rtB ->
B_8_0_0 [ 3 ] = _rtB -> B_31_49_0 * _rtB -> B_31_14_0 ; _rtB -> B_31_55_0 = -
_rtB -> B_8_0_0 [ 2 ] * 0.0605295518538322 * _rtB -> B_8_0_0 [ 1 ] * (
1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_8_0_0 [ 0 ] ) +
0.10339999999999974 ) ) ; break ; default : _rtB -> B_7_0_0 [ 0 ] = _rtB ->
B_31_50_0 * _rtB -> B_31_44_0 ; _rtB -> B_7_0_0 [ 1 ] = _rtB -> B_31_50_0 *
_rtB -> B_31_16_0 ; _rtB -> B_7_0_0 [ 2 ] = _rtB -> B_31_50_0 * _rtB ->
B_31_47_0 ; _rtB -> B_7_0_0 [ 3 ] = _rtB -> B_31_50_0 * _rtB -> B_31_14_0 ;
_rtB -> B_31_55_0 = - _rtB -> B_7_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_7_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_7_0_0
[ 0 ] ) + 0.10339999999999974 ) ) ; break ; } _rtB -> B_31_56_0 = _rtB ->
B_31_55_0 * _rtB -> B_31_33_0 ; _rtB -> B_31_58_0 = _rtX ->
Integrator2_CSTATE ; switch ( ( int32_T ) _rtB -> B_31_57_0 ) { case 1 : _rtB
-> B_31_60_0 = _rtB -> B_31_58_0 ; break ; case 2 : _rtB -> B_31_60_0 =
muDoubleScalarExp ( - 61.061946632469265 * _rtB -> B_31_27_0 ) *
83.400845004248509 ; break ; case 3 : _rtB -> B_31_60_0 = _rtB -> B_31_58_0 ;
break ; default : _rtB -> B_31_60_0 = _rtB -> B_31_58_0 ; break ; } _rtB ->
B_31_66_0 = 0.0 ; _rtB -> B_31_66_0 += _rtP -> P_120 * _rtX ->
Currentfilter1_CSTATE ; if ( _rtB -> B_31_67_0 > _rtP -> P_123 ) { _rtB ->
B_31_70_0 = muDoubleScalarExp ( ( 1.0 / _rtB -> B_31_29_0 -
0.0034112229234180458 ) * 0.0 ) * - _rtB -> B_31_65_0 * _rtB -> B_31_66_0 +
0.05 * _rtB -> B_31_66_0 ; } else { _rtB -> B_31_70_0 = _rtB -> B_31_68_0 ; }
_rtB -> B_31_71_0 = ( ( ( ( _rtB -> B_31_34_0 + _rtB -> B_31_36_0 ) + _rtB ->
B_31_56_0 ) + _rtB -> B_31_60_0 ) + - 0.0 * _rtB -> B_31_27_0 ) + _rtB ->
B_31_70_0 ; if ( _rtB -> B_31_72_0 > _rtP -> P_126 ) { _rtB -> B_31_75_0 = (
_rtB -> B_31_29_0 - 293.15 ) * 0.0 ; } else { _rtB -> B_31_75_0 = _rtB ->
B_31_73_0 ; } _rtB -> B_31_76_0 = ( _rtB -> B_31_11_0 + _rtB -> B_31_71_0 ) +
_rtB -> B_31_75_0 ; _rtB -> B_31_78_0 = _rtP -> P_127 * _rtB -> B_31_16_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> LowerRelop1_Mode_c = ( _rtB -> B_31_76_0 > _rtB -> B_31_7_0 ) ; } _rtB ->
B_31_77_0 = _rtDW -> LowerRelop1_Mode_c ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> UpperRelop_Mode_gu = ( _rtB -> B_31_76_0 < _rtB -> B_31_78_0 ) ; }
_rtB -> B_31_79_0 = _rtDW -> UpperRelop_Mode_gu ; } if ( _rtB -> B_31_77_0 )
{ _rtB -> B_31_81_0 = _rtB -> B_31_7_0 ; } else { if ( _rtB -> B_31_79_0 ) {
_rtB -> B_12_0_0 = _rtB -> B_31_78_0 ; } else { _rtB -> B_12_0_0 = _rtB ->
B_31_76_0 ; } _rtB -> B_31_81_0 = _rtB -> B_12_0_0 ; }
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S ) ; _rtB ->
B_31_132_0 = _rtP -> P_149 * _rtB ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 . B_0_9_0 ; ssCallAccelRunBlock (
S , 31 , 145 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
rtb_B_31_395_0 = ssGetTaskTime ( S , 1 ) ; _rtDW -> Step4_MODE [ 0 ] = (
rtb_B_31_395_0 >= _rtP -> P_182 [ 0 ] ) ; if ( _rtDW -> Step4_MODE [ 0 ] == 1
) { _rtB -> B_31_146_0 [ 0 ] = _rtP -> P_184 [ 0 ] ; } else { _rtB ->
B_31_146_0 [ 0 ] = _rtP -> P_183 [ 0 ] ; } _rtDW -> Step4_MODE [ 1 ] = (
rtb_B_31_395_0 >= _rtP -> P_182 [ 1 ] ) ; if ( _rtDW -> Step4_MODE [ 1 ] == 1
) { _rtB -> B_31_146_0 [ 1 ] = _rtP -> P_184 [ 1 ] ; } else { _rtB ->
B_31_146_0 [ 1 ] = _rtP -> P_183 [ 1 ] ; } rtb_B_31_395_0 = ssGetTaskTime ( S
, 1 ) ; _rtDW -> Step_MODE [ 0 ] = ( rtb_B_31_395_0 >= _rtP -> P_185 [ 0 ] )
; if ( _rtDW -> Step_MODE [ 0 ] == 1 ) { _rtB -> B_31_147_0 [ 0 ] = _rtP ->
P_187 [ 0 ] ; } else { _rtB -> B_31_147_0 [ 0 ] = _rtP -> P_186 [ 0 ] ; }
_rtDW -> Step_MODE [ 1 ] = ( rtb_B_31_395_0 >= _rtP -> P_185 [ 1 ] ) ; if (
_rtDW -> Step_MODE [ 1 ] == 1 ) { _rtB -> B_31_147_0 [ 1 ] = _rtP -> P_187 [
1 ] ; } else { _rtB -> B_31_147_0 [ 1 ] = _rtP -> P_186 [ 1 ] ; } } _rtB ->
B_31_148_0 = 0.0 ; _rtB -> B_31_148_0 += _rtP -> P_190 * _rtX -> Hw2_CSTATE [
3 ] ; _rtB -> B_31_149_0 = 0.0 ; _rtB -> B_31_149_0 += _rtP -> P_194 * _rtX
-> Hw6_CSTATE [ 3 ] ; _rtB -> B_31_150_0 = 0.0 ; _rtB -> B_31_150_0 += _rtP
-> P_198 * _rtX -> Hw1_CSTATE [ 3 ] ; _rtB -> B_31_151_0 = 0.0 ; _rtB ->
B_31_151_0 += _rtP -> P_202 * _rtX -> Hw3_CSTATE [ 3 ] ; ssCallAccelRunBlock
( S , 31 , 152 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 153 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_e , ( _rtB -> B_31_153_0 [ 3 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 26 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC = 4 ; } } ssCallAccelRunBlock ( S , 31 , 155 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_at , ( _rtB -> B_31_153_0
[ 1 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 25 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_j = 4 ; } }
ssCallAccelRunBlock ( S , 31 , 157 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_31_158_0 = 0.0 ; _rtB -> B_31_158_0 += _rtP -> P_248 * _rtX -> Hw4_CSTATE [
1 ] ; _rtB -> B_31_159_0 = 0.0 ; _rtB -> B_31_159_0 += _rtP -> P_252 * _rtX
-> Hw1_CSTATE_k [ 1 ] ; ssCallAccelRunBlock ( S , 31 , 160 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_161_0 = 0.0 ; _rtB -> B_31_161_0 += _rtP
-> P_256 * _rtX -> Hw7_CSTATE [ 1 ] ; _rtB -> B_31_162_0 = 0.0 ; _rtB ->
B_31_162_0 += _rtP -> P_260 * _rtX -> Hw3_CSTATE_e [ 1 ] ;
ssCallAccelRunBlock ( S , 31 , 163 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 164 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 165 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_209_0 = _rtB -> B_31_164_0 [ 0 ] + _rtB
-> B_31_208_0 ; } _rtB -> B_31_166_0 = _rtP -> P_276 * _rtB -> B_31_145_0 [ 6
] ; _rtB -> B_31_170_0 = 0.0 ; _rtB -> B_31_170_0 += _rtP -> P_278 * _rtX ->
TransferFcn_CSTATE_j ; _rtB -> B_31_171_0 = 0.0 ; _rtB -> B_31_171_0 += _rtP
-> P_280 * _rtX -> TransferFcn1_CSTATE ; _rtB -> B_31_172_0 = _rtP -> P_281 *
_rtB -> B_31_145_0 [ 1 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
B_31_223_0 = ( real_T ) ( ( _rtB -> B_31_209_0 != uGrid_1PH_hd_rtC ( S ) ->
B_31_210_0 ) && ( _rtB -> B_31_209_0 >= ( ( muDoubleScalarRem ( ssGetTaskTime
( S , 2 ) + _rtP -> P_288 , _rtP -> P_289 ) * _rtP -> P_290 * 2.0 - 1.0 ) +
1.0 ) * 0.5 ) ) * _rtP -> P_291 ; if ( ssGetTaskTime ( S , 2 ) < _rtP ->
P_292 ) { rtb_B_31_395_0 = _rtP -> P_293 ; } else { rtb_B_31_395_0 = _rtP ->
P_294 ; } _rtB -> B_31_225_0 = _rtB -> B_31_223_0 * rtb_B_31_395_0 ;
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime
( S , 2 ) < _rtP -> P_295 ) { rtb_B_31_395_0 = _rtP -> P_296 ; } else {
rtb_B_31_395_0 = _rtP -> P_297 ; } _rtB -> B_31_228_0 = _rtB -> B_1_0_1 *
rtb_B_31_395_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> Step_MODE_b
= ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_299 ) ; if ( _rtDW -> Step_MODE_b ==
1 ) { _rtB -> B_31_230_0 = _rtP -> P_301 ; } else { _rtB -> B_31_230_0 = _rtP
-> P_300 ; } } _rtB -> B_31_232_0 = rt_Lookup ( _rtP -> P_302 , 5 , ssGetT (
S ) , _rtP -> P_303 ) ; if ( _rtB -> B_31_229_0 >= _rtP -> P_304 ) { _rtB ->
B_31_233_0 = _rtB -> B_31_230_0 ; } else { _rtB -> B_31_233_0 = _rtB ->
B_31_232_0 ; } if ( ( _rtDW -> TimeStampA >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_31_234_0 = 0.0 ; } else {
rtb_B_31_395_0 = _rtDW -> TimeStampA ; lastU = & _rtDW -> LastUAtTimeA ; if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW -> TimeStampB <
ssGetT ( S ) ) { rtb_B_31_395_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S ) ) {
rtb_B_31_395_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_31_234_0 = ( _rtB -> B_31_232_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_31_395_0 ) ; } _rtB -> B_31_245_0 = _rtP -> P_306 * _rtB -> B_31_145_0
[ 8 ] ; _rtB -> B_31_249_0 = 0.0 ; _rtB -> B_31_249_0 += _rtP -> P_308 * _rtX
-> TransferFcn_CSTATE_g ; _rtB -> B_31_250_0 = 0.0 ; _rtB -> B_31_250_0 +=
_rtP -> P_310 * _rtX -> TransferFcn1_CSTATE_p ; _rtB -> B_31_251_0 = _rtP ->
P_311 * _rtB -> B_31_145_0 [ 3 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 288 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_31_289_0 = _rtB -> B_31_288_0 [ 0 ] + _rtB -> B_31_287_0 ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_31_303_0 = ( real_T ) ( ( _rtB ->
B_31_289_0 != uGrid_1PH_hd_rtC ( S ) -> B_31_290_0 ) && ( _rtB -> B_31_289_0
>= ( ( muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_332 , _rtP ->
P_333 ) * _rtP -> P_334 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_335 ; if
( ssGetTaskTime ( S , 2 ) < _rtP -> P_336 ) { rtb_B_31_395_0 = _rtP -> P_337
; } else { rtb_B_31_395_0 = _rtP -> P_338 ; } _rtB -> B_31_305_0 = _rtB ->
B_31_303_0 * rtb_B_31_395_0 ; ssCallAccelRunBlock ( S , 3 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_339 ) {
rtb_B_31_395_0 = _rtP -> P_340 ; } else { rtb_B_31_395_0 = _rtP -> P_341 ; }
_rtB -> B_31_308_0 = _rtB -> B_3_0_1 * rtb_B_31_395_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_c = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_343 ) ; if ( _rtDW -> Step_MODE_c == 1 ) { _rtB -> B_31_310_0 = _rtP ->
P_345 ; } else { _rtB -> B_31_310_0 = _rtP -> P_344 ; } } _rtB -> B_31_312_0
= rt_Lookup ( _rtP -> P_346 , 5 , ssGetT ( S ) , _rtP -> P_347 ) ; if ( _rtB
-> B_31_309_0 >= _rtP -> P_348 ) { _rtB -> B_31_313_0 = _rtB -> B_31_310_0 ;
} else { _rtB -> B_31_313_0 = _rtB -> B_31_312_0 ; } if ( ( _rtDW ->
TimeStampA_k >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_f >= ssGetT ( S ) ) )
{ _rtB -> B_31_314_0 = 0.0 ; } else { rtb_B_31_395_0 = _rtDW -> TimeStampA_k
; lastU = & _rtDW -> LastUAtTimeA_m ; if ( _rtDW -> TimeStampA_k < _rtDW ->
TimeStampB_f ) { if ( _rtDW -> TimeStampB_f < ssGetT ( S ) ) { rtb_B_31_395_0
= _rtDW -> TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } else { if (
_rtDW -> TimeStampA_k >= ssGetT ( S ) ) { rtb_B_31_395_0 = _rtDW ->
TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; } } _rtB -> B_31_314_0 = (
_rtB -> B_31_312_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_31_395_0 ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 325 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 326 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) { _rtB ->
B_31_327_0 [ 0 ] = _rtB -> B_31_146_0 [ 0 ] ; _rtB -> B_31_327_0 [ 1 ] = _rtB
-> B_31_146_0 [ 1 ] ; _rtB -> B_31_328_0 [ 0 ] = _rtB -> B_31_148_0 ; _rtB ->
B_31_328_0 [ 1 ] = _rtB -> B_31_149_0 ; } memcpy ( & _rtB -> B_31_329_0 [ 0 ]
, & _rtDW -> Memory1_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB
-> B_31_330_0 [ 0 ] = _rtDW -> Memory2_PreviousInput [ 0 ] ; _rtB ->
B_31_330_0 [ 1 ] = _rtDW -> Memory2_PreviousInput [ 1 ] ; } if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 334 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 16 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 31 , 336 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 337 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 31 , 338 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 339 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 341 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 31 , 342 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 343 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 31 , 344 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsSampleHit ( S , 3 , 0 ) ) { _rtB -> B_31_347_0 [ 0 ] = _rtB -> B_31_147_0
[ 0 ] ; _rtB -> B_31_347_0 [ 1 ] = _rtB -> B_31_147_0 [ 1 ] ; _rtB ->
B_31_348_0 [ 0 ] = _rtB -> B_31_150_0 ; _rtB -> B_31_348_0 [ 1 ] = _rtB ->
B_31_151_0 ; } memcpy ( & _rtB -> B_31_349_0 [ 0 ] , & _rtDW ->
Memory3_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB -> B_31_350_0
[ 0 ] = _rtDW -> Memory4_PreviousInput [ 0 ] ; _rtB -> B_31_350_0 [ 1 ] =
_rtDW -> Memory4_PreviousInput [ 1 ] ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 352 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 18 , 0 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_31_355_0 = 0.0 ; _rtB -> B_31_355_0 += _rtP -> P_362 * _rtX -> Hw2_CSTATE_p
[ 1 ] ; _rtB -> B_31_356_0 = _rtP -> P_364 * _rtB -> B_31_145_0 [ 5 ] ;
ssCallAccelRunBlock ( S , 31 , 357 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_31_358_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_366 ;
B_31_359_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_367 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_31_361_0 = _rtP -> P_368
; _rtB -> B_31_363_0 = _rtDW -> Memory_PreviousInput ; } if ( ssGetT ( S ) >=
_rtB -> B_31_361_0 ) { _rtB -> B_31_365_0 = ( _rtB -> B_31_358_0 - B_31_359_0
) * _rtP -> P_1 ; } else { _rtB -> B_31_365_0 = _rtB -> B_31_363_0 ; } _rtB
-> B_31_366_0 = _rtX -> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_371 ; B_31_367_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_h . Last , _rtDW ->
TransportDelay_IWORK_h . Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP
-> P_372 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_31_369_0 = _rtP -> P_373 ; _rtB -> B_31_371_0 = _rtDW
-> Memory_PreviousInput_f ; } if ( ssGetT ( S ) >= _rtB -> B_31_369_0 ) {
_rtB -> B_31_373_0 = ( _rtB -> B_31_366_0 - B_31_367_0 ) * _rtP -> P_0 ; }
else { _rtB -> B_31_373_0 = _rtB -> B_31_371_0 ; } rtb_RealImagtoComplex_re =
_rtB -> B_31_365_0 ; rtb_RealImagtoComplex_im = _rtB -> B_31_373_0 ; _rtB ->
B_31_376_0 = _rtX -> integrator_CSTATE_p ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_376 ; B_31_377_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_377 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_31_379_0 = _rtP -> P_378 ; _rtB -> B_31_381_0 = _rtDW
-> Memory_PreviousInput_p ; } if ( ssGetT ( S ) >= _rtB -> B_31_379_0 ) {
_rtB -> B_31_383_0 = ( _rtB -> B_31_376_0 - B_31_377_0 ) * _rtP -> P_3 ; }
else { _rtB -> B_31_383_0 = _rtB -> B_31_381_0 ; } _rtB -> B_31_384_0 = _rtX
-> integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_381 ; B_31_385_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_382 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_31_387_0 = _rtP -> P_383
; _rtB -> B_31_389_0 = _rtDW -> Memory_PreviousInput_k ; } if ( ssGetT ( S )
>= _rtB -> B_31_387_0 ) { _rtB -> B_31_391_0 = ( _rtB -> B_31_384_0 -
B_31_385_0 ) * _rtP -> P_2 ; } else { _rtB -> B_31_391_0 = _rtB -> B_31_389_0
; } rtb_B_31_395_0 = muDoubleScalarHypot ( rtb_RealImagtoComplex_re ,
rtb_RealImagtoComplex_im ) * muDoubleScalarHypot ( _rtB -> B_31_383_0 , _rtB
-> B_31_391_0 ) * _rtP -> P_385 ; rtb_RealImagtoComplex_re = ( _rtP -> P_386
* muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im , rtb_RealImagtoComplex_re )
- _rtP -> P_387 * muDoubleScalarAtan2 ( _rtB -> B_31_391_0 , _rtB ->
B_31_383_0 ) ) * _rtP -> P_388 ; _rtB -> B_31_401_0 = rtb_B_31_395_0 *
muDoubleScalarCos ( rtb_RealImagtoComplex_re ) ; _rtB -> B_31_403_0 =
rtb_B_31_395_0 * muDoubleScalarSin ( rtb_RealImagtoComplex_re ) ;
ssCallAccelRunBlock ( S , 31 , 404 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_31_405_0 = _rtP -> P_389 * _rtB -> B_31_145_0 [ 0 ] ; ssCallAccelRunBlock (
S , 31 , 406 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_408_0 = muDoubleScalarSin
( _rtP -> P_393 * ssGetTaskTime ( S , 0 ) + _rtP -> P_394 ) * _rtP -> P_391 +
_rtP -> P_392 ; if ( ( _rtDW -> TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB_a >= ssGetT ( S ) ) ) { _rtB -> B_31_409_0 = 0.0 ; } else {
rtb_B_31_395_0 = _rtDW -> TimeStampA_b ; lastU = & _rtDW -> LastUAtTimeA_f ;
if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { if ( _rtDW ->
TimeStampB_a < ssGetT ( S ) ) { rtb_B_31_395_0 = _rtDW -> TimeStampB_a ;
lastU = & _rtDW -> LastUAtTimeB_n ; } } else { if ( _rtDW -> TimeStampA_b >=
ssGetT ( S ) ) { rtb_B_31_395_0 = _rtDW -> TimeStampB_a ; lastU = & _rtDW ->
LastUAtTimeB_n ; } } _rtB -> B_31_409_0 = ( _rtB -> B_31_408_0 - * lastU ) /
( ssGetT ( S ) - rtb_B_31_395_0 ) ; } _rtB -> B_31_410_0 = _rtB -> B_31_407_0
* _rtB -> B_31_409_0 ; _rtB -> B_31_411_0 = _rtB -> B_31_355_0 + _rtB ->
B_31_410_0 ; _rtB -> B_31_412_0 = 0.0 ; _rtB -> B_31_412_0 += _rtP -> P_397 *
_rtX -> Hi_Pass1_CSTATE ; _rtB -> B_31_412_0 += _rtP -> P_398 * _rtB ->
B_31_411_0 ; _rtB -> B_31_413_0 = 0.0 ; _rtB -> B_31_413_0 += _rtP -> P_402 *
_rtX -> Hw5_CSTATE [ 1 ] ; _rtB -> B_31_414_0 = _rtB -> B_31_413_0 + _rtB ->
B_31_355_0 ; _rtB -> B_31_415_0 = _rtB -> B_31_412_0 - _rtB -> B_31_414_0 ;
_rtB -> B_31_417_0 = 0.0 ; _rtB -> B_31_417_0 += _rtP -> P_406 [ 0 ] * _rtX
-> TransferFcn1_CSTATE_e [ 0 ] ; _rtB -> B_31_417_0 += _rtP -> P_406 [ 1 ] *
_rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtB -> B_31_420_0 = ( _rtP -> P_404 *
_rtB -> B_31_415_0 + _rtB -> B_31_417_0 ) + _rtB -> B_31_419_0 ;
ssCallAccelRunBlock ( S , 31 , 421 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_31_422_0 = 0.0 ; _rtB -> B_31_422_0 += _rtP -> P_410 * _rtX -> Hw6_CSTATE_f
[ 1 ] ; ssCallAccelRunBlock ( S , 31 , 423 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 5 , 0 ) ) { rtb_B_31_395_0 = ssGetTaskTime ( S , 5 ) ; if
( ssGetTNextWasAdjusted ( S , 5 ) ) { _rtDW -> nextTime =
_ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled != 0 ) { _rtDW
-> justEnabled = 0 ; if ( rtb_B_31_395_0 >= _rtP -> P_415 ) {
rtb_RealImagtoComplex_re = ( rtb_B_31_395_0 - _rtP -> P_415 ) / _rtP -> P_413
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_413 + _rtP ->
P_415 ) + _rtP -> P_414 * _rtP -> P_413 / 100.0 ; if ( rtb_B_31_395_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue = 0 ; _rtDW ->
nextTime = ( real_T ) ( numCycles + 1U ) * _rtP -> P_413 + _rtP -> P_415 ; }
} else { _rtDW -> numCompleteCycles = _rtP -> P_415 != 0.0 ? - 1 : 0 ; _rtDW
-> currentValue = 0 ; _rtDW -> nextTime = _rtP -> P_415 ; } } else { if (
_rtDW -> nextTime <= rtb_B_31_395_0 ) { if ( _rtDW -> currentValue == 1 ) {
_rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW ->
numCompleteCycles + 1LL ) * _rtP -> P_413 + _rtP -> P_415 ; } else { _rtDW ->
numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ( _rtP
-> P_414 * _rtP -> P_413 * 0.01 + ( real_T ) _rtDW -> numCompleteCycles *
_rtP -> P_413 ) + _rtP -> P_415 ; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW
-> nextTime ) ; if ( _rtDW -> currentValue == 1 ) { _rtB -> B_31_424_0 = _rtP
-> P_412 ; } else { _rtB -> B_31_424_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1
, 0 ) && ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_i , ( _rtB ->
B_31_424_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 28
, 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_e = 4 ; } } if (
ssIsSampleHit ( S , 6 , 0 ) ) { rtb_B_31_395_0 = ssGetTaskTime ( S , 6 ) ; if
( ssGetTNextWasAdjusted ( S , 6 ) ) { _rtDW -> nextTime_e =
_ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW -> justEnabled_l != 0 ) { _rtDW
-> justEnabled_l = 0 ; if ( rtb_B_31_395_0 >= _rtP -> P_423 ) {
rtb_RealImagtoComplex_re = ( rtb_B_31_395_0 - _rtP -> P_423 ) / _rtP -> P_421
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_j = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_421 + _rtP ->
P_423 ) + _rtP -> P_422 * _rtP -> P_421 / 100.0 ; if ( rtb_B_31_395_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_d = 1 ; _rtDW ->
nextTime_e = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_d = 0
; _rtDW -> nextTime_e = ( real_T ) ( numCycles + 1U ) * _rtP -> P_421 + _rtP
-> P_423 ; } } else { _rtDW -> numCompleteCycles_j = _rtP -> P_423 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = _rtP -> P_423 ; }
} else { if ( _rtDW -> nextTime_e <= rtb_B_31_395_0 ) { if ( _rtDW ->
currentValue_d == 1 ) { _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = (
real_T ) ( _rtDW -> numCompleteCycles_j + 1LL ) * _rtP -> P_421 + _rtP ->
P_423 ; } else { _rtDW -> numCompleteCycles_j ++ ; _rtDW -> currentValue_d =
1 ; _rtDW -> nextTime_e = ( _rtP -> P_422 * _rtP -> P_421 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_j * _rtP -> P_421 ) + _rtP -> P_423 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_e ) ; if ( _rtDW ->
currentValue_d == 1 ) { _rtB -> B_31_431_0 = _rtP -> P_420 ; } else { _rtB ->
B_31_431_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_a , ( _rtB -> B_31_431_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 29 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_o = 4 ; } } if ( ssIsSampleHit ( S , 7 , 0 ) ) {
rtb_B_31_395_0 = ssGetTaskTime ( S , 7 ) ; if ( ssGetTNextWasAdjusted ( S , 7
) ) { _rtDW -> nextTime_f = _ssGetVarNextHitTime ( S , 2 ) ; } if ( _rtDW ->
justEnabled_k != 0 ) { _rtDW -> justEnabled_k = 0 ; if ( rtb_B_31_395_0 >=
_rtP -> P_431 ) { rtb_RealImagtoComplex_re = ( rtb_B_31_395_0 - _rtP -> P_431
) / _rtP -> P_429 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_o = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_429 + _rtP ->
P_431 ) + _rtP -> P_430 * _rtP -> P_429 / 100.0 ; if ( rtb_B_31_395_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_a = 1 ; _rtDW ->
nextTime_f = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_a = 0
; _rtDW -> nextTime_f = ( real_T ) ( numCycles + 1U ) * _rtP -> P_429 + _rtP
-> P_431 ; } } else { _rtDW -> numCompleteCycles_o = _rtP -> P_431 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = _rtP -> P_431 ; }
} else { if ( _rtDW -> nextTime_f <= rtb_B_31_395_0 ) { if ( _rtDW ->
currentValue_a == 1 ) { _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = (
real_T ) ( _rtDW -> numCompleteCycles_o + 1LL ) * _rtP -> P_429 + _rtP ->
P_431 ; } else { _rtDW -> numCompleteCycles_o ++ ; _rtDW -> currentValue_a =
1 ; _rtDW -> nextTime_f = ( _rtP -> P_430 * _rtP -> P_429 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_o * _rtP -> P_429 ) + _rtP -> P_431 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime_f ) ; if ( _rtDW ->
currentValue_a == 1 ) { _rtB -> B_31_438_0 = _rtP -> P_428 ; } else { _rtB ->
B_31_438_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE , ( _rtB -> B_31_438_0 ) ) ; if ( zcEvent != NO_ZCEVENT )
{ ssCallAccelRunBlock ( S , 30 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_p = 4 ; } } _rtB -> B_31_445_0 = _rtP -> P_436 * _rtB
-> B_31_145_0 [ 7 ] ; _rtB -> B_31_449_0 = 0.0 ; _rtB -> B_31_449_0 += _rtP
-> P_438 * _rtX -> TransferFcn_CSTATE_m ; _rtB -> B_31_450_0 = 0.0 ; _rtB ->
B_31_450_0 += _rtP -> P_440 * _rtX -> TransferFcn1_CSTATE_l ; _rtB ->
B_31_451_0 = _rtP -> P_441 * _rtB -> B_31_145_0 [ 2 ] ; _rtB -> B_31_455_0 =
_rtP -> P_442 * _rtB -> B_31_145_0 [ 9 ] ; _rtB -> B_31_459_0 = 0.0 ; _rtB ->
B_31_459_0 += _rtP -> P_444 * _rtX -> TransferFcn2_CSTATE ; _rtB ->
B_31_493_0 = _rtB -> B_31_420_0 + _rtB -> B_31_492_0 ; if ( ssIsSampleHit ( S
, 2 , 0 ) ) { _rtB -> B_31_507_0 = ( real_T ) ( ( _rtB -> B_31_493_0 !=
uGrid_1PH_hd_rtC ( S ) -> B_31_494_0 ) && ( _rtB -> B_31_493_0 >= ( (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_451 , _rtP -> P_452 )
* _rtP -> P_453 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_454 ; if (
ssGetTaskTime ( S , 2 ) < _rtP -> P_455 ) { rtb_B_31_395_0 = _rtP -> P_456 ;
} else { rtb_B_31_395_0 = _rtP -> P_457 ; } _rtB -> B_31_509_0 = _rtB ->
B_31_507_0 * rtb_B_31_395_0 ; ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_458 ) {
rtb_B_31_395_0 = _rtP -> P_459 ; } else { rtb_B_31_395_0 = _rtP -> P_460 ; }
_rtB -> B_31_512_0 = _rtB -> B_2_0_1 * rtb_B_31_395_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_f = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_462 ) ; if ( _rtDW -> Step_MODE_f == 1 ) { _rtB -> B_31_514_0 = _rtP ->
P_464 ; } else { _rtB -> B_31_514_0 = _rtP -> P_463 ; } } _rtB -> B_31_516_0
= rt_Lookup ( _rtP -> P_465 , 5 , ssGetT ( S ) , _rtP -> P_466 ) ; if ( _rtB
-> B_31_513_0 >= _rtP -> P_467 ) { _rtB -> B_31_517_0 = _rtB -> B_31_514_0 ;
} else { _rtB -> B_31_517_0 = _rtB -> B_31_516_0 ; } if ( ( _rtDW ->
TimeStampA_n >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_m >= ssGetT ( S ) ) )
{ _rtB -> B_31_518_0 = 0.0 ; } else { rtb_B_31_395_0 = _rtDW -> TimeStampA_n
; lastU = & _rtDW -> LastUAtTimeA_ma ; if ( _rtDW -> TimeStampA_n < _rtDW ->
TimeStampB_m ) { if ( _rtDW -> TimeStampB_m < ssGetT ( S ) ) { rtb_B_31_395_0
= _rtDW -> TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } else { if (
_rtDW -> TimeStampA_n >= ssGetT ( S ) ) { rtb_B_31_395_0 = _rtDW ->
TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } _rtB -> B_31_518_0 = (
_rtB -> B_31_516_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_31_395_0 ) ; } _rtB
-> B_31_533_0 = ( muDoubleScalarSin ( _rtP -> P_471 * ssGetTaskTime ( S , 0 )
+ _rtP -> P_472 ) * _rtP -> P_469 + _rtP -> P_470 ) * _rtB -> B_31_405_0 ;
_rtB -> B_31_535_0 = ( muDoubleScalarSin ( _rtP -> P_475 * ssGetTaskTime ( S
, 0 ) + _rtP -> P_476 ) * _rtP -> P_473 + _rtP -> P_474 ) * _rtB ->
B_31_405_0 ; _rtB -> B_31_537_0 = ( muDoubleScalarSin ( _rtP -> P_479 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_480 ) * _rtP -> P_477 + _rtP -> P_478 ) *
_rtB -> B_31_356_0 ; _rtB -> B_31_539_0 = ( muDoubleScalarSin ( _rtP -> P_483
* ssGetTaskTime ( S , 0 ) + _rtP -> P_484 ) * _rtP -> P_481 + _rtP -> P_482 )
* _rtB -> B_31_356_0 ; ssCallAccelRunBlock ( S , 31 , 540 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 541 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_545_0 = _rtP -> P_485 * _rtB ->
B_31_145_0 [ 10 ] ; ssCallAccelRunBlock ( S , 31 , 546 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_31_548_0 = _rtB -> B_31_81_0 - _rtP -> P_486 * _rtB ->
B_31_545_0 ; ssCallAccelRunBlock ( S , 31 , 549 , SS_CALL_MDL_OUTPUTS ) ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_31_550_0 = _rtP -> P_487 * _rtB
-> B_31_14_0 ; } _rtB -> B_31_551_0 = ( 1.0 - _rtB -> B_31_27_0 / _rtB ->
B_31_550_0 ) * 100.0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_31_551_0 >= _rtP -> P_488 ? 1 : _rtB ->
B_31_551_0 > _rtP -> P_489 ? 0 : - 1 ; } _rtB -> B_31_552_0 = _rtDW ->
Saturation_MODE == 1 ? _rtP -> P_488 : _rtDW -> Saturation_MODE == - 1 ? _rtP
-> P_489 : _rtB -> B_31_551_0 ; ssCallAccelRunBlock ( S , 31 , 553 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE =
( _rtB -> B_31_545_0 >= 0.0 ) ; } _rtB -> B_31_563_0 = _rtDW -> Abs_MODE > 0
? _rtB -> B_31_545_0 : - _rtB -> B_31_545_0 ; if ( ssIsSampleHit ( S , 1 , 0
) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_i = ( _rtB ->
B_31_545_0 < uGrid_1PH_hd_rtC ( S ) -> B_31_564_0 ) ; } _rtB -> B_31_567_0 =
_rtP -> P_494 * ( real_T ) _rtDW -> Compare_Mode_i ; } _rtB -> B_31_568_0 =
_rtB -> B_31_567_0 - _rtB -> B_31_58_0 ; _rtB -> B_31_569_0 = _rtB ->
B_31_563_0 * _rtB -> B_31_568_0 ; _rtB -> B_31_570_0 = _rtP -> P_495 * _rtB
-> B_31_569_0 ; _rtB -> B_31_574_0 = _rtP -> P_497 * _rtB -> B_31_27_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE_d = ( _rtB -> B_31_66_0 >= 0.0
) ; } _rtB -> B_31_575_0 = _rtDW -> Abs_MODE_d > 0 ? _rtB -> B_31_66_0 : -
_rtB -> B_31_66_0 ; _rtB -> B_31_576_0 = 0.05 * _rtB -> B_31_66_0 + - _rtB ->
B_31_71_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs1_MODE = ( _rtB ->
B_31_576_0 >= 0.0 ) ; } _rtB -> B_31_577_0 = _rtDW -> Abs1_MODE > 0 ? _rtB ->
B_31_576_0 : - _rtB -> B_31_576_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_e = ( _rtB -> B_31_66_0 <
uGrid_1PH_hd_rtC ( S ) -> B_31_578_0 ) ; } _rtB -> B_31_581_0 = _rtP -> P_499
* ( real_T ) _rtDW -> Compare_Mode_e ; } _rtB -> B_31_583_0 = _rtB ->
B_31_575_0 * _rtB -> B_31_577_0 ; _rtB -> B_31_584_0 = ( 0.0 * _rtB ->
B_31_575_0 * _rtB -> B_31_29_0 + _rtB -> B_31_581_0 ) + _rtB -> B_31_583_0 ;
_rtB -> B_31_587_0 = 0.0 ; _rtB -> B_31_587_0 += _rtP -> P_504 * _rtX ->
TransferFcn1_CSTATE_g ; _rtB -> B_31_588_0 = _rtP -> P_505 * _rtB ->
B_31_587_0 ; _rtB -> B_31_589_0 = _rtB -> B_31_572_0 + _rtB -> B_31_588_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_d , ( _rtB ->
B_31_153_0 [ 7 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S
, 27 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_l = 4 ; } }
ssCallAccelRunBlock ( S , 20 , 0 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 598 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 599 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 600 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 19 , 0 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 31 , 605 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 31 , 606 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 31 , 607 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_613_0 = 0.0 ; _rtB -> B_31_613_0 += _rtP
-> P_515 * _rtX -> Actuador1_CSTATE ; _rtB -> B_31_614_0 = _rtP -> P_516 *
_rtB -> B_31_613_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_517 ; _rtB
-> B_31_615_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> MotordeCombustin1_IWORK . CircularBufSize , &
_rtDW -> MotordeCombustin1_IWORK . Last , _rtDW -> MotordeCombustin1_IWORK .
Tail , _rtDW -> MotordeCombustin1_IWORK . Head , _rtP -> P_518 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_31_616_0 = _rtB -> B_31_615_0 - _rtB ->
B_31_611_0 ; _rtB -> B_31_617_0 = _rtP -> P_519 * _rtB -> B_31_145_0 [ 4 ] ;
_rtB -> B_31_621_0 = _rtB -> B_31_612_0 - _rtB -> B_31_6_0 ; _rtB ->
B_31_622_0 = _rtP -> P_520 * _rtB -> B_31_621_0 ; _rtB -> B_31_623_0 = _rtX
-> Filter_CSTATE ; _rtB -> B_31_624_0 = _rtB -> B_31_622_0 - _rtB ->
B_31_623_0 ; _rtB -> B_31_625_0 = _rtP -> P_522 * _rtB -> B_31_624_0 ; _rtB
-> B_31_626_0 = _rtP -> P_523 * _rtB -> B_31_621_0 ; _rtB -> B_31_627_0 =
_rtX -> Integrator_CSTATE ; _rtB -> B_31_628_0 = _rtP -> P_525 * _rtB ->
B_31_621_0 ; _rtB -> B_31_629_0 = ( _rtB -> B_31_628_0 + _rtB -> B_31_627_0 )
+ _rtB -> B_31_625_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 31 , 633 , SS_CALL_MDL_OUTPUTS ) ; }
UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID8 ( SimStruct * S ,
int_T tid ) { real_T rtb_B_31_89_0 ; real_T rtb_B_31_127_0 ; B_uGrid_1PH_hd_T
* _rtB ; P_uGrid_1PH_hd_T * _rtP ; _rtP = ( ( P_uGrid_1PH_hd_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO (
S ) ) ; _rtB -> B_31_0_0 = _rtP -> P_73 ; _rtB -> B_31_7_0 = _rtP -> P_81 ;
if ( _rtP -> P_85 > _rtP -> P_86 ) { if ( _rtP -> P_82 > _rtP -> P_83 ) {
_rtB -> B_31_11_0 = _rtP -> P_83 ; } else if ( _rtP -> P_82 < _rtP -> P_84 )
{ _rtB -> B_31_11_0 = _rtP -> P_84 ; } else { _rtB -> B_31_11_0 = _rtP ->
P_82 ; } } else { _rtB -> B_31_11_0 = _rtP -> P_82 ; } _rtB -> B_31_13_0 =
_rtP -> P_88 ; _rtB -> B_31_24_0 = _rtP -> P_98 ; _rtB -> B_31_30_0 = _rtP ->
P_103 ; _rtB -> B_31_31_0 = _rtP -> P_104 ; _rtB -> B_31_37_0 = _rtP -> P_106
; _rtB -> B_31_38_0 = _rtP -> P_107 ; _rtB -> B_31_48_0 = _rtP -> P_110 ;
_rtB -> B_31_49_0 = _rtP -> P_111 ; _rtB -> B_31_50_0 = _rtP -> P_112 ; _rtB
-> B_31_57_0 = _rtP -> P_113 ; if ( _rtP -> P_116 > _rtP -> P_118 ) { _rtB ->
B_31_65_0 = _rtP -> P_115 ; } else { _rtB -> B_31_65_0 = _rtP -> P_117 ; }
_rtB -> B_31_67_0 = _rtP -> P_121 ; _rtB -> B_31_68_0 = _rtP -> P_122 ; _rtB
-> B_31_72_0 = _rtP -> P_124 ; _rtB -> B_31_73_0 = _rtP -> P_125 ;
rtb_B_31_89_0 = _rtP -> P_132 + _rtP -> P_133 ; _rtB -> B_31_95_0 = _rtP ->
P_135 ; _rtB -> B_31_96_0 = ( ( rtb_B_31_89_0 - _rtP -> P_134 ) * _rtP ->
P_131 + _rtP -> P_130 ) * ( _rtP -> P_128 / _rtP -> P_129 ) * _rtB ->
B_31_95_0 ; _rtB -> B_31_97_0 = _rtP -> P_136 ; _rtB -> B_31_98_0 = _rtP ->
P_137 ; _rtB -> B_31_99_0 = _rtP -> P_138 ; _rtB -> B_31_100_0 = 0.0 / _rtB
-> B_31_99_0 ; _rtB -> B_31_105_0 = _rtP -> P_140 * rtb_B_31_89_0 / _rtP ->
P_141 * _rtP -> P_139 ; _rtB -> B_31_106_0 = _rtP -> P_142 ; rtb_B_31_127_0 =
rtb_B_31_89_0 / _rtP -> P_134 ; _rtB -> B_31_130_0 = _rtP -> P_130 / (
muDoubleScalarExp ( _rtP -> P_146 * _rtP -> P_141 / ( _rtP -> P_140 * _rtP ->
P_147 * rtb_B_31_89_0 * _rtP -> P_139 ) ) - _rtP -> P_148 ) * (
rtb_B_31_127_0 * rtb_B_31_127_0 * rtb_B_31_127_0 ) * muDoubleScalarExp ( (
_rtP -> P_144 / rtb_B_31_89_0 - _rtP -> P_143 / _rtP -> P_134 ) * ( _rtP ->
P_141 * _rtP -> P_145 / ( _rtP -> P_140 * _rtP -> P_139 ) ) ) ; _rtB ->
B_31_133_0 = _rtP -> P_150 ; _rtB -> B_31_134_0 = _rtP -> P_151 ; _rtB ->
B_31_135_0 = _rtP -> P_152 ; _rtB -> B_31_136_0 = _rtP -> P_153 ; _rtB ->
B_31_137_0 = _rtP -> P_154 ; _rtB -> B_31_138_0 = _rtP -> P_155 ; _rtB ->
B_31_139_0 = _rtP -> P_156 ; _rtB -> B_31_140_0 = _rtP -> P_157 ; _rtB ->
B_31_141_0 = _rtP -> P_158 ; _rtB -> B_31_142_0 = _rtP -> P_159 ; _rtB ->
B_31_143_0 = _rtP -> P_160 ; _rtB -> B_31_144_0 = _rtP -> P_161 ; _rtB ->
B_31_188_0 = _rtP -> P_282 ; _rtB -> B_31_192_0 = _rtP -> P_283 ; _rtB ->
B_31_196_0 = _rtP -> P_284 ; _rtB -> B_31_200_0 = _rtP -> P_285 ; _rtB ->
B_31_208_0 = _rtP -> P_286 ; _rtB -> B_31_229_0 = _rtP -> P_298 ; _rtB ->
B_31_267_0 = _rtP -> P_312 ; _rtB -> B_31_271_0 = _rtP -> P_313 ; _rtB ->
B_31_275_0 = _rtP -> P_314 ; _rtB -> B_31_279_0 = _rtP -> P_315 ; _rtB ->
B_31_287_0 = _rtP -> P_316 ; _rtB -> B_31_309_0 = _rtP -> P_342 ; _rtB ->
B_31_340_0 = _rtP -> P_354 ; memcpy ( & _rtB -> B_31_331_0 [ 0 ] , & _rtP ->
P_352 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_31_332_0 [
0 ] , & _rtP -> P_353 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB
-> B_31_345_0 [ 0 ] , & _rtP -> P_355 [ 0 ] , 40000U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_31_346_0 [ 0 ] , & _rtP -> P_356 [ 0 ] , 40000U * sizeof
( real_T ) ) ; _rtB -> B_31_354_0 = _rtP -> P_359 ; _rtB -> B_31_407_0 = _rtP
-> P_390 ; _rtB -> B_31_419_0 = _rtP -> P_407 ; _rtB -> B_31_426_0 = _rtP ->
P_416 ; _rtB -> B_31_427_0 = _rtP -> P_417 ; _rtB -> B_31_428_0 = _rtP ->
P_418 ; _rtB -> B_31_429_0 = _rtP -> P_419 ; _rtB -> B_31_433_0 = _rtP ->
P_424 ; _rtB -> B_31_434_0 = _rtP -> P_425 ; _rtB -> B_31_435_0 = _rtP ->
P_426 ; _rtB -> B_31_436_0 = _rtP -> P_427 ; _rtB -> B_31_440_0 = _rtP ->
P_432 ; _rtB -> B_31_441_0 = _rtP -> P_433 ; _rtB -> B_31_442_0 = _rtP ->
P_434 ; _rtB -> B_31_443_0 = _rtP -> P_435 ; _rtB -> B_31_472_0 = _rtP ->
P_445 ; _rtB -> B_31_476_0 = _rtP -> P_446 ; _rtB -> B_31_480_0 = _rtP ->
P_447 ; _rtB -> B_31_484_0 = _rtP -> P_448 ; _rtB -> B_31_492_0 = _rtP ->
P_449 ; _rtB -> B_31_513_0 = _rtP -> P_461 ; _rtB -> B_31_572_0 = _rtP ->
P_496 + _rtP -> P_492 ; if ( _rtP -> P_490 > _rtP -> P_502 ) { rtb_B_31_89_0
= ( _rtB -> B_31_572_0 - 293.15 ) * 0.0 + 1.0339999999999974 ; if (
rtb_B_31_89_0 > _rtP -> P_500 ) { _rtB -> B_31_586_0 = _rtP -> P_500 ; } else
if ( rtb_B_31_89_0 < _rtP -> P_501 ) { _rtB -> B_31_586_0 = _rtP -> P_501 ; }
else { _rtB -> B_31_586_0 = rtb_B_31_89_0 ; } } else { _rtB -> B_31_586_0 =
_rtP -> P_491 ; } _rtB -> B_31_593_0 = _rtP -> P_506 ; _rtB -> B_31_601_0 =
_rtP -> P_509 ; _rtB -> B_31_595_0 [ 0 ] = _rtP -> P_507 [ 0 ] ; _rtB ->
B_31_596_0 [ 0 ] = _rtP -> P_508 [ 0 ] ; _rtB -> B_31_602_0 [ 0 ] = _rtP ->
P_510 [ 0 ] ; _rtB -> B_31_603_0 [ 0 ] = _rtP -> P_511 [ 0 ] ; _rtB ->
B_31_595_0 [ 1 ] = _rtP -> P_507 [ 1 ] ; _rtB -> B_31_596_0 [ 1 ] = _rtP ->
P_508 [ 1 ] ; _rtB -> B_31_602_0 [ 1 ] = _rtP -> P_510 [ 1 ] ; _rtB ->
B_31_603_0 [ 1 ] = _rtP -> P_511 [ 1 ] ; _rtB -> B_31_611_0 = _rtP -> P_512 ;
_rtB -> B_31_612_0 = _rtP -> P_513 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = (
( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T *
) _ssGetModelBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_31_586_0 ; _rtDW -> itinit_PreviousInput =
_rtB -> B_31_574_0 ; } _rtDW -> inti_IWORK = 0 ; if ( _rtX -> inti_CSTATE ==
_rtP -> P_95 ) { switch ( _rtDW -> inti_MODE ) { case 3 : if ( _rtB ->
B_31_545_0 < 0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 1 ; }
break ; case 1 : if ( _rtB -> B_31_545_0 >= 0.0 ) { _rtDW -> inti_MODE = 3 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_31_545_0 < 0.0 ) { _rtDW -> inti_MODE = 1 ; } else { _rtDW
-> inti_MODE = 3 ; } break ; } } else if ( _rtX -> inti_CSTATE == _rtP ->
P_96 ) { switch ( _rtDW -> inti_MODE ) { case 4 : if ( _rtB -> B_31_545_0 >
0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> inti_MODE = 2 ; } break ; case
2 : if ( _rtB -> B_31_545_0 <= 0.0 ) { _rtDW -> inti_MODE = 4 ;
ssSetSolverNeedsReset ( S ) ; } break ; default : ssSetSolverNeedsReset ( S )
; if ( _rtB -> B_31_545_0 > 0.0 ) { _rtDW -> inti_MODE = 2 ; } else { _rtDW
-> inti_MODE = 4 ; } break ; } } else { _rtDW -> inti_MODE = 0 ; }
ssCallAccelRunBlock ( S , 31 , 145 , SS_CALL_MDL_UPDATE ) ; if ( _rtDW ->
TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == ( rtInf ) ) {
_rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } else
if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else { _rtDW -> TimeStampB
= ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } * lastU = _rtB ->
B_31_232_0 ; if ( _rtDW -> TimeStampA_k == ( rtInf ) ) { _rtDW ->
TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_m ; } else if (
_rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW -> TimeStampB_f = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_o ; } else if ( _rtDW -> TimeStampA_k < _rtDW
-> TimeStampB_f ) { _rtDW -> TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_m ; } else { _rtDW -> TimeStampB_f = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB_o ; } * lastU = _rtB -> B_31_312_0 ; if ( ssIsSampleHit
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
TransportDelay_IWORK . Last , simTime - _rtP -> P_366 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_31_358_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_31_365_0 ; } { real_T * * uBuffer = ( real_T
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
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_371 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_31_366_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_f = _rtB -> B_31_373_0 ; } { real_T * * uBuffer = (
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
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_376 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_31_376_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_p = _rtB -> B_31_383_0 ; } { real_T * * uBuffer = (
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
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_381 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_31_384_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_k = _rtB -> B_31_391_0 ; } if ( _rtDW -> TimeStampA_b ==
( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_f ; } else if ( _rtDW -> TimeStampB_a == ( rtInf ) ) { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } else if (
_rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { _rtDW -> TimeStampA_b =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } * lastU =
_rtB -> B_31_408_0 ; if ( _rtDW -> TimeStampA_n == ( rtInf ) ) { _rtDW ->
TimeStampA_n = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_ma ; } else if
( _rtDW -> TimeStampB_m == ( rtInf ) ) { _rtDW -> TimeStampB_m = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeB_g ; } else if ( _rtDW -> TimeStampA_n <
_rtDW -> TimeStampB_m ) { _rtDW -> TimeStampA_n = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA_ma ; } else { _rtDW -> TimeStampB_m = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_g ; } * lastU = _rtB -> B_31_516_0 ; { real_T
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
& _rtDW -> MotordeCombustin1_IWORK . Last , simTime - _rtP -> P_517 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
MotordeCombustin1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = _rtB -> B_31_614_0 ; } UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID8 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
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
P_74 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtXdot -> Dinmicaeneleje1_CSTATE +=
_rtB -> B_31_616_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_78 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_31_617_0 ; _rtXdot -> Currentfilter_CSTATE =
0.0 ; _rtXdot -> Currentfilter_CSTATE += _rtP -> P_91 * _rtX ->
Currentfilter_CSTATE ; _rtXdot -> Currentfilter_CSTATE += _rtB -> B_31_545_0
; if ( ( _rtDW -> inti_MODE != 3 ) && ( _rtDW -> inti_MODE != 4 ) ) { _rtXdot
-> inti_CSTATE = _rtB -> B_31_545_0 ; _rtXdis -> inti_CSTATE = false ; } else
{ _rtXdot -> inti_CSTATE = 0.0 ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW
-> inti_MODE == 4 ) ) { _rtXdis -> inti_CSTATE = true ; } } _rtXdot ->
StateSpace_CSTATE = 0.0 ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_99 * _rtX
-> StateSpace_CSTATE ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_100 * _rtB
-> B_31_589_0 ; _rtXdot -> Integrator2_CSTATE = _rtB -> B_31_570_0 ; _rtXdot
-> Currentfilter1_CSTATE = 0.0 ; _rtXdot -> Currentfilter1_CSTATE += _rtP ->
P_119 * _rtX -> Currentfilter1_CSTATE ; _rtXdot -> Currentfilter1_CSTATE +=
_rtB -> B_31_545_0 ; ssCallAccelRunBlock ( S , 31 , 145 ,
SS_CALL_MDL_DERIVATIVES ) ; _rtXdot -> Hw2_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_188 [ 0 ] *
_rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_188 [ 1 ]
* _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 1 ] += _rtP -> P_188 [ 2
] * _rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_188 [
3 ] * _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_188
[ 4 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP ->
P_188 [ 5 ] * _rtX -> Hw2_CSTATE [ 3 ] ; _rtXdot -> Hw2_CSTATE [ 3 ] += _rtP
-> P_188 [ 6 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] +=
_rtP -> P_189 * _rtB -> B_31_164_0 [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 0 ] +=
_rtP -> P_192 [ 0 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [ 0 ]
+= _rtP -> P_192 [ 1 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 1
] += _rtP -> P_192 [ 2 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [
2 ] += _rtP -> P_192 [ 3 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE
[ 2 ] += _rtP -> P_192 [ 4 ] * _rtX -> Hw6_CSTATE [ 2 ] ; _rtXdot ->
Hw6_CSTATE [ 2 ] += _rtP -> P_192 [ 5 ] * _rtX -> Hw6_CSTATE [ 3 ] ; _rtXdot
-> Hw6_CSTATE [ 3 ] += _rtP -> P_192 [ 6 ] * _rtX -> Hw6_CSTATE [ 2 ] ;
_rtXdot -> Hw6_CSTATE [ 0 ] += _rtP -> P_193 * _rtB -> B_31_164_0 [ 2 ] ;
_rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_196 [ 0 ] * _rtX -> Hw1_CSTATE [ 0 ]
; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_196 [ 1 ] * _rtX -> Hw1_CSTATE [ 1
] ; _rtXdot -> Hw1_CSTATE [ 1 ] += _rtP -> P_196 [ 2 ] * _rtX -> Hw1_CSTATE [
0 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_196 [ 3 ] * _rtX -> Hw1_CSTATE
[ 1 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_196 [ 4 ] * _rtX ->
Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_196 [ 5 ] * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtXdot -> Hw1_CSTATE [ 3 ] += _rtP -> P_196 [ 6 ] *
_rtX -> Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_197 *
_rtB -> B_31_288_0 [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_200 [ 0 ]
* _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_200 [ 1
] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 1 ] += _rtP -> P_200 [
2 ] * _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP -> P_200
[ 3 ] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP ->
P_200 [ 4 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP
-> P_200 [ 5 ] * _rtX -> Hw3_CSTATE [ 3 ] ; _rtXdot -> Hw3_CSTATE [ 3 ] +=
_rtP -> P_200 [ 6 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 0 ]
+= _rtP -> P_201 * _rtB -> B_31_288_0 [ 2 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] =
0.0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 0 ] = 0.0
; _rtXdot -> Hw3_CSTATE_e [ 0 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw1_CSTATE_k [ 1 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw3_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP ->
P_246 [ 0 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP
-> P_246 [ 1 ] * _rtX -> Hw4_CSTATE [ 1 ] ; _rtXdot -> Hw4_CSTATE [ 1 ] +=
_rtP -> P_246 [ 2 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ]
+= _rtP -> P_247 * _rtB -> B_31_171_0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] += _rtP
-> P_250 [ 0 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot -> Hw1_CSTATE_k [ 0 ]
+= _rtP -> P_250 [ 1 ] * _rtX -> Hw1_CSTATE_k [ 1 ] ; _rtXdot -> Hw1_CSTATE_k
[ 1 ] += _rtP -> P_250 [ 2 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot ->
Hw1_CSTATE_k [ 0 ] += _rtP -> P_251 * _rtB -> B_31_170_0 ; _rtXdot ->
Hw7_CSTATE [ 0 ] += _rtP -> P_254 [ 0 ] * _rtX -> Hw7_CSTATE [ 0 ] ; _rtXdot
-> Hw7_CSTATE [ 0 ] += _rtP -> P_254 [ 1 ] * _rtX -> Hw7_CSTATE [ 1 ] ;
_rtXdot -> Hw7_CSTATE [ 1 ] += _rtP -> P_254 [ 2 ] * _rtX -> Hw7_CSTATE [ 0 ]
; _rtXdot -> Hw7_CSTATE [ 0 ] += _rtP -> P_255 * _rtB -> B_31_249_0 ; _rtXdot
-> Hw3_CSTATE_e [ 0 ] += _rtP -> P_258 [ 0 ] * _rtX -> Hw3_CSTATE_e [ 0 ] ;
_rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_258 [ 1 ] * _rtX -> Hw3_CSTATE_e [
1 ] ; _rtXdot -> Hw3_CSTATE_e [ 1 ] += _rtP -> P_258 [ 2 ] * _rtX ->
Hw3_CSTATE_e [ 0 ] ; _rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_259 * _rtB ->
B_31_250_0 ; _rtXdot -> TransferFcn_CSTATE_j = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_j += _rtP -> P_277 * _rtX -> TransferFcn_CSTATE_j ;
_rtXdot -> TransferFcn_CSTATE_j += _rtB -> B_31_166_0 ; _rtXdot ->
TransferFcn1_CSTATE = 0.0 ; _rtXdot -> TransferFcn1_CSTATE += _rtP -> P_279 *
_rtX -> TransferFcn1_CSTATE ; _rtXdot -> TransferFcn1_CSTATE += _rtB ->
B_31_172_0 ; _rtXdot -> TransferFcn_CSTATE_g = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_g += _rtP -> P_307 * _rtX -> TransferFcn_CSTATE_g ;
_rtXdot -> TransferFcn_CSTATE_g += _rtB -> B_31_245_0 ; _rtXdot ->
TransferFcn1_CSTATE_p = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_p += _rtP ->
P_309 * _rtX -> TransferFcn1_CSTATE_p ; _rtXdot -> TransferFcn1_CSTATE_p +=
_rtB -> B_31_251_0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] = 0.0 ; _rtXdot ->
Hw2_CSTATE_p [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP -> P_360 [ 0
] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP ->
P_360 [ 1 ] * _rtX -> Hw2_CSTATE_p [ 1 ] ; _rtXdot -> Hw2_CSTATE_p [ 1 ] +=
_rtP -> P_360 [ 2 ] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [
0 ] += _rtP -> P_361 * _rtB -> B_31_449_0 ; _rtXdot -> integrator_CSTATE =
_rtB -> B_31_533_0 ; _rtXdot -> integrator_CSTATE_i = _rtB -> B_31_535_0 ;
_rtXdot -> integrator_CSTATE_p = _rtB -> B_31_537_0 ; _rtXdot ->
integrator_CSTATE_l = _rtB -> B_31_539_0 ; _rtXdot -> Hi_Pass1_CSTATE = 0.0 ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_395 * _rtX -> Hi_Pass1_CSTATE ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_396 * _rtB -> B_31_411_0 ; _rtXdot ->
Hw5_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] = 0.0 ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtP -> P_405 [ 0 ] * _rtX ->
TransferFcn1_CSTATE_e [ 0 ] ; _rtXdot -> Hw5_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
TransferFcn1_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] +=
_rtP -> P_405 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtXdot ->
Hw5_CSTATE [ 0 ] += _rtP -> P_400 [ 0 ] * _rtX -> Hw5_CSTATE [ 0 ] ; _rtXdot
-> Hw5_CSTATE [ 0 ] += _rtP -> P_400 [ 1 ] * _rtX -> Hw5_CSTATE [ 1 ] ;
_rtXdot -> Hw5_CSTATE [ 1 ] += _rtP -> P_400 [ 2 ] * _rtX -> Hw5_CSTATE [ 0 ]
; _rtXdot -> Hw5_CSTATE [ 0 ] += _rtP -> P_401 * _rtB -> B_31_459_0 ; _rtXdot
-> TransferFcn1_CSTATE_e [ 1 ] += _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtB -> B_31_415_0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] = 0.0 ; _rtXdot -> Hw6_CSTATE_f [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] += _rtP -> P_408 [ 0 ] * _rtX -> Hw6_CSTATE_f [ 0 ] ;
_rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_408 [ 1 ] * _rtX -> Hw6_CSTATE_f [
1 ] ; _rtXdot -> Hw6_CSTATE_f [ 1 ] += _rtP -> P_408 [ 2 ] * _rtX ->
Hw6_CSTATE_f [ 0 ] ; _rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_409 * _rtB ->
B_31_450_0 ; _rtXdot -> TransferFcn_CSTATE_m = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_m += _rtP -> P_437 * _rtX -> TransferFcn_CSTATE_m ;
_rtXdot -> TransferFcn_CSTATE_m += _rtB -> B_31_445_0 ; _rtXdot ->
TransferFcn1_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_l += _rtP ->
P_439 * _rtX -> TransferFcn1_CSTATE_l ; _rtXdot -> TransferFcn1_CSTATE_l +=
_rtB -> B_31_451_0 ; _rtXdot -> TransferFcn2_CSTATE = 0.0 ; _rtXdot ->
TransferFcn2_CSTATE += _rtP -> P_443 * _rtX -> TransferFcn2_CSTATE ; _rtXdot
-> TransferFcn2_CSTATE += _rtB -> B_31_455_0 ; _rtXdot ->
TransferFcn1_CSTATE_g = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_g += _rtP ->
P_503 * _rtX -> TransferFcn1_CSTATE_g ; _rtXdot -> TransferFcn1_CSTATE_g +=
_rtB -> B_31_584_0 ; _rtXdot -> Actuador1_CSTATE = 0.0 ; _rtXdot ->
Actuador1_CSTATE += _rtP -> P_514 * _rtX -> Actuador1_CSTATE ; _rtXdot ->
Actuador1_CSTATE += _rtB -> B_31_629_0 ; _rtXdot -> Filter_CSTATE = _rtB ->
B_31_625_0 ; _rtXdot -> Integrator_CSTATE = _rtB -> B_31_626_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; ssCallAccelRunBlock ( S , 31 , 145 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { boolean_T anyStateSaturated
; real_T tmp ; real_T tmp_0 ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T *
_rtP ; X_uGrid_1PH_hd_T * _rtX ; ZCV_uGrid_1PH_hd_T * _rtZCSV ;
DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * ) ssGetRootDWork
( S ) ) ; _rtZCSV = ( ( ZCV_uGrid_1PH_hd_T * ) ssGetSolverZcSignalVector ( S
) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB ->
B_31_16_0 - uGrid_1PH_hd_rtC ( S ) -> B_31_17_0 ; if ( ( _rtDW -> inti_MODE
== 1 ) && ( _rtX -> inti_CSTATE >= _rtP -> P_95 ) ) { _rtZCSV ->
inti_IntgUpLimit_ZC = 0.0 ; } else { _rtZCSV -> inti_IntgUpLimit_ZC = _rtX ->
inti_CSTATE - _rtP -> P_95 ; } if ( ( _rtDW -> inti_MODE == 2 ) && ( _rtX ->
inti_CSTATE <= _rtP -> P_96 ) ) { _rtZCSV -> inti_IntgLoLimit_ZC = 0.0 ; }
else { _rtZCSV -> inti_IntgLoLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_96 ;
} anyStateSaturated = false ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW ->
inti_MODE == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> inti_LeaveSaturate_ZC = _rtB -> B_31_545_0 ; } else { _rtZCSV ->
inti_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB
-> B_31_22_0 - _rtB -> B_31_15_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB
-> B_31_22_0 - _rtB -> B_31_24_0 ; _rtZCSV -> LowerRelop1_RelopInput_ZC_i =
_rtB -> B_31_22_0 - _rtB -> B_31_39_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f
= _rtB -> B_31_22_0 - _rtB -> B_31_41_0 ; _rtZCSV -> Compare_RelopInput_ZC_d
= _rtB -> B_31_16_0 - uGrid_1PH_hd_rtC ( S ) -> B_31_45_0 ; _rtZCSV ->
LowerRelop1_RelopInput_ZC_a = _rtB -> B_31_76_0 - _rtB -> B_31_7_0 ; _rtZCSV
-> UpperRelop_RelopInput_ZC_g = _rtB -> B_31_76_0 - _rtB -> B_31_78_0 ;
ssCallAccelRunBlock ( S , 31 , 145 , SS_CALL_MDL_ZERO_CROSSINGS ) ; tmp =
ssGetT ( S ) ; tmp_0 = ssGetT ( S ) ; _rtZCSV -> Step4_StepTime_ZC [ 0 ] =
tmp - _rtP -> P_182 [ 0 ] ; _rtZCSV -> Step_StepTime_ZC [ 0 ] = tmp_0 - _rtP
-> P_185 [ 0 ] ; _rtZCSV -> Step4_StepTime_ZC [ 1 ] = tmp - _rtP -> P_182 [ 1
] ; _rtZCSV -> Step_StepTime_ZC [ 1 ] = tmp_0 - _rtP -> P_185 [ 1 ] ;
ssCallAccelRunBlock ( S , 31 , 153 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 31 , 164 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC_n = ssGetT ( S ) - _rtP -> P_299 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_31_234_0 - _rtP -> P_305 ;
ssCallAccelRunBlock ( S , 31 , 288 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC_d = ssGetT ( S ) - _rtP -> P_343 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_j = _rtB -> B_31_314_0 - _rtP -> P_349 ; _rtZCSV
-> Step_StepTime_ZC_b = ssGetT ( S ) - _rtP -> P_462 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_e = _rtB -> B_31_518_0 - _rtP -> P_468 ; _rtZCSV
-> Saturation_UprLim_ZC = _rtB -> B_31_551_0 - _rtP -> P_488 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_31_551_0 - _rtP -> P_489 ; _rtZCSV ->
Abs_AbsZc_ZC = _rtB -> B_31_545_0 ; _rtZCSV -> Compare_RelopInput_ZC_f = _rtB
-> B_31_545_0 - uGrid_1PH_hd_rtC ( S ) -> B_31_564_0 ; _rtZCSV ->
Abs_AbsZc_ZC_j = _rtB -> B_31_66_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_31_576_0 ; _rtZCSV -> Compare_RelopInput_ZC_b = _rtB -> B_31_66_0 -
uGrid_1PH_hd_rtC ( S ) -> B_31_578_0 ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 2941330294U ) ; ssSetChecksumVal
( S , 1 , 792555269U ) ; ssSetChecksumVal ( S , 2 , 1960921257U ) ;
ssSetChecksumVal ( S , 3 , 2305098295U ) ; { mxArray * slVerStructMat = NULL
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
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_84 = rtMinusInf ; ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_96 = rtMinusInf ; } static
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
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID8 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
