#include "__cf_uGrid_1PH_hd_caso3.h"
#include <math.h>
#include "uGrid_1PH_hd_caso3_acc.h"
#include "uGrid_1PH_hd_caso3_acc_private.h"
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
boolean_T uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
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
return ( true ) ; } real_T uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate (
real_T tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T
bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput
, boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
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
uGrid_1PH_hd_caso3_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct *
const S ) { ssCallAccelRunBlock ( S , 40 , 131 , SS_CALL_MDL_OUTPUTS ) ; }
void uGrid_1PH_hd_caso3_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term (
SimStruct * const S ) { } real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u )
{ uint32_T lo ; uint32_T hi ; lo = * u % 127773U * 16807U ; hi = * u /
127773U * 2836U ; if ( lo < hi ) { * u = 2147483647U - ( hi - lo ) ; } else {
* u = lo - hi ; } return ( real_T ) * u * 4.6566128752457969E-10 ; } real_T
rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { real_T y ; real_T sr ; real_T
si ; do { sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } static void mdlOutputs ( SimStruct * S , int_T tid ) {
real_T B_40_361_0 ; real_T B_40_369_0 ; real_T B_40_379_0 ; real_T B_40_387_0
; boolean_T resetIntg ; ZCEventType zcEvent ; real_T * lastU ; real_T
rtb_B_40_663_0 ; uint32_T numCycles ; real_T rtb_B_40_397_0 ; real_T
rtb_RealImagtoComplex_re ; real_T rtb_RealImagtoComplex_im ;
B_uGrid_1PH_hd_caso3_T * _rtB ; P_uGrid_1PH_hd_caso3_T * _rtP ;
X_uGrid_1PH_hd_caso3_T * _rtX ; PrevZCX_uGrid_1PH_hd_caso3_T * _rtZCE ;
DW_uGrid_1PH_hd_caso3_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_caso3_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_uGrid_1PH_hd_caso3_T * )
_ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_caso3_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtB -> B_40_1_0 = 0.0 ; _rtB -> B_40_1_0 += _rtP -> P_167 * _rtX ->
Dinmicaeneleje1_CSTATE ; _rtB -> B_40_2_0 = _rtP -> P_168 * _rtB -> B_40_1_0
; _rtB -> B_40_3_0 = _rtP -> P_169 * _rtB -> B_40_2_0 ; _rtB -> B_40_4_0 =
0.0 ; _rtB -> B_40_4_0 += _rtP -> P_171 * _rtX -> TransferFcn_CSTATE ; _rtB
-> B_40_5_0 = _rtP -> P_172 * _rtB -> B_40_4_0 ; _rtB -> B_40_6_0 = _rtB ->
B_40_3_0 - _rtB -> B_40_5_0 ; _rtB -> B_40_16_0 = 0.0 ; _rtB -> B_40_16_0 +=
_rtP -> P_184 * _rtX -> Currentfilter_CSTATE ; if ( ssIsSampleHit ( S , 1 , 0
) ) { _rtB -> B_40_14_0 = _rtDW -> itinit1_PreviousInput ; _rtB -> B_40_15_0
= _rtP -> P_182 * _rtB -> B_40_14_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> Compare_Mode = ( _rtB -> B_40_16_0 > uGrid_1PH_hd_caso3_rtC ( S ) ->
B_40_17_0 ) ; } _rtB -> B_40_19_0 = _rtDW -> Compare_Mode ; _rtB -> B_40_20_0
= _rtDW -> itinit_PreviousInput ; } if ( ssIsMajorTimeStep ( S ) ) {
resetIntg = false ; zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING , & _rtZCE ->
inti_Reset_ZCE , ( _rtB -> B_40_19_0 ) ) ; if ( ( zcEvent != NO_ZCEVENT ) ||
( _rtDW -> inti_IWORK != 0 ) ) { resetIntg = true ; _rtX -> inti_CSTATE =
_rtB -> B_40_20_0 ; } if ( resetIntg ) { ssSetSolverNeedsReset ( S ) ; } if (
_rtX -> inti_CSTATE >= _rtP -> P_187 ) { _rtX -> inti_CSTATE = _rtP -> P_187
; } else { if ( _rtX -> inti_CSTATE <= _rtP -> P_188 ) { _rtX -> inti_CSTATE
= _rtP -> P_188 ; } } } _rtB -> B_40_21_0 = _rtX -> inti_CSTATE ; _rtB ->
B_40_22_0 = _rtP -> P_189 * _rtB -> B_40_21_0 ; if ( ssIsSampleHit ( S , 1 ,
0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> LowerRelop1_Mode = ( _rtB
-> B_40_22_0 > _rtB -> B_40_15_0 ) ; _rtDW -> UpperRelop_Mode = ( _rtB ->
B_40_22_0 < _rtB -> B_40_24_0 ) ; } _rtB -> B_40_23_0 = _rtDW ->
LowerRelop1_Mode ; _rtB -> B_40_25_0 = _rtDW -> UpperRelop_Mode ; } if ( _rtB
-> B_40_23_0 ) { _rtB -> B_40_27_0 = _rtB -> B_40_15_0 ; } else { if ( _rtB
-> B_40_25_0 ) { _rtB -> B_13_0_0 = _rtB -> B_40_24_0 ; } else { _rtB ->
B_13_0_0 = _rtB -> B_40_22_0 ; } _rtB -> B_40_27_0 = _rtB -> B_13_0_0 ; }
_rtB -> B_40_29_0 = 0.0 ; _rtB -> B_40_29_0 += _rtP -> P_193 * _rtX ->
StateSpace_CSTATE ; if ( _rtB -> B_40_30_0 > _rtP -> P_197 ) { _rtB ->
B_40_33_0 = muDoubleScalarExp ( ( 1.0 / _rtB -> B_40_29_0 -
0.0034112229234180458 ) * 0.0 ) ; } else { _rtB -> B_40_33_0 = _rtB ->
B_40_31_0 ; } _rtB -> B_40_34_0 = - 0.0605295518538322 * _rtB -> B_40_14_0 /
( _rtB -> B_40_14_0 - _rtB -> B_40_27_0 ) * _rtB -> B_40_27_0 * _rtB ->
B_40_33_0 ; _rtB -> B_40_36_0 = - _rtB -> B_40_19_0 * 0.0605295518538322 *
_rtB -> B_40_16_0 * _rtB -> B_40_14_0 / ( _rtB -> B_40_14_0 - _rtB ->
B_40_27_0 ) * _rtB -> B_40_33_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> B_40_39_0 = _rtP -> P_200 * _rtB -> B_40_14_0 ; if ( ssIsMajorTimeStep ( S
) ) { _rtDW -> LowerRelop1_Mode_g = ( _rtB -> B_40_22_0 > _rtB -> B_40_39_0 )
; } _rtB -> B_40_40_0 = _rtDW -> LowerRelop1_Mode_g ; _rtB -> B_40_41_0 = -
_rtB -> B_40_39_0 * 0.999 * 0.1 * 0.9999 ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> UpperRelop_Mode_g = ( _rtB -> B_40_22_0 < _rtB -> B_40_41_0 ) ; }
_rtB -> B_40_42_0 = _rtDW -> UpperRelop_Mode_g ; if ( ssIsMajorTimeStep ( S )
) { _rtDW -> Compare_Mode_k = ( _rtB -> B_40_16_0 < uGrid_1PH_hd_caso3_rtC (
S ) -> B_40_45_0 ) ; } _rtB -> B_40_47_0 = _rtDW -> Compare_Mode_k ; } if (
_rtB -> B_40_40_0 ) { _rtB -> B_40_44_0 = _rtB -> B_40_39_0 ; } else { if (
_rtB -> B_40_42_0 ) { _rtB -> B_14_0_0 = _rtB -> B_40_41_0 ; } else { _rtB ->
B_14_0_0 = _rtB -> B_40_22_0 ; } _rtB -> B_40_44_0 = _rtB -> B_14_0_0 ; }
switch ( ( int32_T ) _rtB -> B_40_37_0 ) { case 1 : _rtB -> B_10_0_0 [ 0 ] =
_rtB -> B_40_38_0 * _rtB -> B_40_44_0 ; _rtB -> B_10_0_0 [ 1 ] = _rtB ->
B_40_38_0 * _rtB -> B_40_16_0 ; _rtB -> B_10_0_0 [ 2 ] = _rtB -> B_40_38_0 *
_rtB -> B_40_47_0 ; _rtB -> B_10_0_0 [ 3 ] = _rtB -> B_40_38_0 * _rtB ->
B_40_14_0 ; _rtB -> B_40_55_0 = - _rtB -> B_10_0_0 [ 2 ] * 0.0605295518538322
* _rtB -> B_10_0_0 [ 1 ] * ( 1.0339999999999974 / ( _rtB -> B_10_0_0 [ 0 ] +
0.10339999999999974 ) ) ; break ; case 2 : _rtB -> B_9_0_0 [ 0 ] = _rtB ->
B_40_48_0 * _rtB -> B_40_44_0 ; _rtB -> B_9_0_0 [ 1 ] = _rtB -> B_40_48_0 *
_rtB -> B_40_16_0 ; _rtB -> B_9_0_0 [ 2 ] = _rtB -> B_40_48_0 * _rtB ->
B_40_47_0 ; _rtB -> B_9_0_0 [ 3 ] = _rtB -> B_40_48_0 * _rtB -> B_40_14_0 ;
_rtB -> B_40_55_0 = - _rtB -> B_9_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_9_0_0 [ 1 ] * _rtB -> B_9_0_0 [ 3 ] / ( _rtB -> B_9_0_0 [ 3 ] * 0.1 + _rtB
-> B_9_0_0 [ 0 ] ) ; break ; case 3 : _rtB -> B_8_0_0 [ 0 ] = _rtB ->
B_40_49_0 * _rtB -> B_40_44_0 ; _rtB -> B_8_0_0 [ 1 ] = _rtB -> B_40_49_0 *
_rtB -> B_40_16_0 ; _rtB -> B_8_0_0 [ 2 ] = _rtB -> B_40_49_0 * _rtB ->
B_40_47_0 ; _rtB -> B_8_0_0 [ 3 ] = _rtB -> B_40_49_0 * _rtB -> B_40_14_0 ;
_rtB -> B_40_55_0 = - _rtB -> B_8_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_8_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_8_0_0
[ 0 ] ) + 0.10339999999999974 ) ) ; break ; default : _rtB -> B_7_0_0 [ 0 ] =
_rtB -> B_40_50_0 * _rtB -> B_40_44_0 ; _rtB -> B_7_0_0 [ 1 ] = _rtB ->
B_40_50_0 * _rtB -> B_40_16_0 ; _rtB -> B_7_0_0 [ 2 ] = _rtB -> B_40_50_0 *
_rtB -> B_40_47_0 ; _rtB -> B_7_0_0 [ 3 ] = _rtB -> B_40_50_0 * _rtB ->
B_40_14_0 ; _rtB -> B_40_55_0 = - _rtB -> B_7_0_0 [ 2 ] * 0.0605295518538322
* _rtB -> B_7_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB
-> B_7_0_0 [ 0 ] ) + 0.10339999999999974 ) ) ; break ; } _rtB -> B_40_56_0 =
_rtB -> B_40_55_0 * _rtB -> B_40_33_0 ; _rtB -> B_40_58_0 = _rtX ->
Integrator2_CSTATE ; switch ( ( int32_T ) _rtB -> B_40_57_0 ) { case 1 : _rtB
-> B_40_60_0 = _rtB -> B_40_58_0 ; break ; case 2 : _rtB -> B_40_60_0 =
muDoubleScalarExp ( - 61.061946632469265 * _rtB -> B_40_27_0 ) *
83.400845004248509 ; break ; case 3 : _rtB -> B_40_60_0 = _rtB -> B_40_58_0 ;
break ; default : _rtB -> B_40_60_0 = _rtB -> B_40_58_0 ; break ; } _rtB ->
B_40_66_0 = 0.0 ; _rtB -> B_40_66_0 += _rtP -> P_212 * _rtX ->
Currentfilter1_CSTATE ; if ( _rtB -> B_40_67_0 > _rtP -> P_215 ) { _rtB ->
B_40_70_0 = muDoubleScalarExp ( ( 1.0 / _rtB -> B_40_29_0 -
0.0034112229234180458 ) * 0.0 ) * - _rtB -> B_40_65_0 * _rtB -> B_40_66_0 +
0.05 * _rtB -> B_40_66_0 ; } else { _rtB -> B_40_70_0 = _rtB -> B_40_68_0 ; }
_rtB -> B_40_71_0 = ( ( ( ( _rtB -> B_40_34_0 + _rtB -> B_40_36_0 ) + _rtB ->
B_40_56_0 ) + _rtB -> B_40_60_0 ) + - 0.0 * _rtB -> B_40_27_0 ) + _rtB ->
B_40_70_0 ; if ( _rtB -> B_40_72_0 > _rtP -> P_218 ) { _rtB -> B_40_75_0 = (
_rtB -> B_40_29_0 - 293.15 ) * 0.0 ; } else { _rtB -> B_40_75_0 = _rtB ->
B_40_73_0 ; } _rtB -> B_40_76_0 = ( _rtB -> B_40_11_0 + _rtB -> B_40_71_0 ) +
_rtB -> B_40_75_0 ; _rtB -> B_40_78_0 = _rtP -> P_219 * _rtB -> B_40_16_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> LowerRelop1_Mode_c = ( _rtB -> B_40_76_0 > _rtB -> B_40_7_0 ) ; } _rtB ->
B_40_77_0 = _rtDW -> LowerRelop1_Mode_c ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> UpperRelop_Mode_gu = ( _rtB -> B_40_76_0 < _rtB -> B_40_78_0 ) ; }
_rtB -> B_40_79_0 = _rtDW -> UpperRelop_Mode_gu ; } if ( _rtB -> B_40_77_0 )
{ _rtB -> B_40_81_0 = _rtB -> B_40_7_0 ; } else { if ( _rtB -> B_40_79_0 ) {
_rtB -> B_12_0_0 = _rtB -> B_40_78_0 ; } else { _rtB -> B_12_0_0 = _rtB ->
B_40_76_0 ; } _rtB -> B_40_81_0 = _rtB -> B_12_0_0 ; }
uGrid_1PH_hd_caso3_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S ) ; _rtB
-> B_40_132_0 = _rtP -> P_241 * _rtB ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 . B_0_9_0 ; ssCallAccelRunBlock (
S , 40 , 145 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 146 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_in , ( _rtB -> B_40_146_0 [ 7 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 29 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC = 4 ; } zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING
, & _rtZCE -> Subsystem_Trig_ZCE_k , ( _rtB -> B_40_146_0 [ 9 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 30 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_d = 4 ; } } } _rtB ->
B_40_149_0 = 0.0 ; _rtB -> B_40_149_0 += _rtP -> P_318 * _rtX -> Hw2_CSTATE [
3 ] ; _rtB -> B_40_150_0 = 0.0 ; _rtB -> B_40_150_0 += _rtP -> P_322 * _rtX
-> Hw6_CSTATE [ 3 ] ; _rtB -> B_40_151_0 = 0.0 ; _rtB -> B_40_151_0 += _rtP
-> P_326 * _rtX -> Hw1_CSTATE [ 3 ] ; _rtB -> B_40_152_0 = 0.0 ; _rtB ->
B_40_152_0 += _rtP -> P_330 * _rtX -> Hw3_CSTATE [ 3 ] ; ssCallAccelRunBlock
( S , 40 , 153 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_e , ( _rtB -> B_40_146_0 [ 3 ] ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 27 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_e = 4 ; } }
ssCallAccelRunBlock ( S , 40 , 155 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_at , ( _rtB -> B_40_146_0 [ 1 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 26 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_j = 4 ; } } ssCallAccelRunBlock ( S , 40 , 157
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 158 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_40_159_0 = 0.0 ; _rtB -> B_40_159_0 +=
_rtP -> P_334 * _rtX -> Hw4_CSTATE [ 1 ] ; _rtB -> B_40_160_0 = 0.0 ; _rtB ->
B_40_160_0 += _rtP -> P_338 * _rtX -> Hw1_CSTATE_k [ 1 ] ;
ssCallAccelRunBlock ( S , 40 , 161 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 162 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_40_163_0 = 0.0 ; _rtB -> B_40_163_0 +=
_rtP -> P_342 * _rtX -> Hw7_CSTATE [ 1 ] ; _rtB -> B_40_164_0 = 0.0 ; _rtB ->
B_40_164_0 += _rtP -> P_346 * _rtX -> Hw3_CSTATE_e [ 1 ] ;
ssCallAccelRunBlock ( S , 40 , 165 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 166 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 167 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_40_211_0 = _rtB -> B_40_166_0 [ 0 ] + _rtB
-> B_40_210_0 ; } _rtB -> B_40_168_0 = _rtP -> P_362 * _rtB -> B_40_145_0 [ 6
] ; _rtB -> B_40_172_0 = 0.0 ; _rtB -> B_40_172_0 += _rtP -> P_364 * _rtX ->
TransferFcn_CSTATE_j ; _rtB -> B_40_173_0 = 0.0 ; _rtB -> B_40_173_0 += _rtP
-> P_366 * _rtX -> TransferFcn1_CSTATE ; _rtB -> B_40_174_0 = _rtP -> P_367 *
_rtB -> B_40_145_0 [ 1 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
B_40_225_0 = ( real_T ) ( ( _rtB -> B_40_211_0 != uGrid_1PH_hd_caso3_rtC ( S
) -> B_40_212_0 ) && ( _rtB -> B_40_211_0 >= ( ( muDoubleScalarRem (
ssGetTaskTime ( S , 2 ) + _rtP -> P_374 , _rtP -> P_375 ) * _rtP -> P_376 *
2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_377 ; if ( ssGetTaskTime ( S , 2 )
< _rtP -> P_378 ) { rtb_B_40_397_0 = _rtP -> P_379 ; } else { rtb_B_40_397_0
= _rtP -> P_380 ; } _rtB -> B_40_227_0 = _rtB -> B_40_225_0 * rtb_B_40_397_0
; ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; if (
ssGetTaskTime ( S , 2 ) < _rtP -> P_381 ) { rtb_B_40_397_0 = _rtP -> P_382 ;
} else { rtb_B_40_397_0 = _rtP -> P_383 ; } _rtB -> B_40_230_0 = _rtB ->
B_1_0_1 * rtb_B_40_397_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Step_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_385 ) ; if ( _rtDW ->
Step_MODE == 1 ) { _rtB -> B_40_232_0 = _rtP -> P_387 ; } else { _rtB ->
B_40_232_0 = _rtP -> P_386 ; } } _rtB -> B_40_234_0 = rt_Lookup ( _rtP ->
P_388 , 5 , ssGetT ( S ) , _rtP -> P_389 ) ; if ( _rtB -> B_40_231_0 >= _rtP
-> P_390 ) { _rtB -> B_40_235_0 = _rtB -> B_40_232_0 ; } else { _rtB ->
B_40_235_0 = _rtB -> B_40_234_0 ; } if ( ( _rtDW -> TimeStampA >= ssGetT ( S
) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_40_236_0 = 0.0 ;
} else { rtb_B_40_397_0 = _rtDW -> TimeStampA ; lastU = & _rtDW ->
LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW
-> TimeStampB < ssGetT ( S ) ) { rtb_B_40_397_0 = _rtDW -> TimeStampB ; lastU
= & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S
) ) { rtb_B_40_397_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB
; } } _rtB -> B_40_236_0 = ( _rtB -> B_40_234_0 - * lastU ) / ( ssGetT ( S )
- rtb_B_40_397_0 ) ; } _rtB -> B_40_247_0 = _rtP -> P_392 * _rtB ->
B_40_145_0 [ 10 ] ; _rtB -> B_40_251_0 = 0.0 ; _rtB -> B_40_251_0 += _rtP ->
P_394 * _rtX -> TransferFcn_CSTATE_g ; _rtB -> B_40_252_0 = 0.0 ; _rtB ->
B_40_252_0 += _rtP -> P_396 * _rtX -> TransferFcn1_CSTATE_p ; _rtB ->
B_40_253_0 = _rtP -> P_397 * _rtB -> B_40_145_0 [ 3 ] ; if ( ssIsSampleHit (
S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 290 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_40_291_0 = _rtB -> B_40_290_0 [ 0 ] + _rtB -> B_40_289_0 ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_40_305_0 = ( real_T ) ( ( _rtB ->
B_40_291_0 != uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_292_0 ) && ( _rtB ->
B_40_291_0 >= ( ( muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_418
, _rtP -> P_419 ) * _rtP -> P_420 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP ->
P_421 ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_422 ) { rtb_B_40_397_0 =
_rtP -> P_423 ; } else { rtb_B_40_397_0 = _rtP -> P_424 ; } _rtB ->
B_40_307_0 = _rtB -> B_40_305_0 * rtb_B_40_397_0 ; ssCallAccelRunBlock ( S ,
3 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_425
) { rtb_B_40_397_0 = _rtP -> P_426 ; } else { rtb_B_40_397_0 = _rtP -> P_427
; } _rtB -> B_40_310_0 = _rtB -> B_3_0_1 * rtb_B_40_397_0 ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> Step_MODE_c = ( ssGetTaskTime ( S ,
1 ) >= _rtP -> P_429 ) ; if ( _rtDW -> Step_MODE_c == 1 ) { _rtB ->
B_40_312_0 = _rtP -> P_431 ; } else { _rtB -> B_40_312_0 = _rtP -> P_430 ; }
} _rtB -> B_40_314_0 = rt_Lookup ( _rtP -> P_432 , 5 , ssGetT ( S ) , _rtP ->
P_433 ) ; if ( _rtB -> B_40_311_0 >= _rtP -> P_434 ) { _rtB -> B_40_315_0 =
_rtB -> B_40_312_0 ; } else { _rtB -> B_40_315_0 = _rtB -> B_40_314_0 ; } if
( ( _rtDW -> TimeStampA_k >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_f >=
ssGetT ( S ) ) ) { _rtB -> B_40_316_0 = 0.0 ; } else { rtb_B_40_397_0 = _rtDW
-> TimeStampA_k ; lastU = & _rtDW -> LastUAtTimeA_m ; if ( _rtDW ->
TimeStampA_k < _rtDW -> TimeStampB_f ) { if ( _rtDW -> TimeStampB_f < ssGetT
( S ) ) { rtb_B_40_397_0 = _rtDW -> TimeStampB_f ; lastU = & _rtDW ->
LastUAtTimeB_o ; } } else { if ( _rtDW -> TimeStampA_k >= ssGetT ( S ) ) {
rtb_B_40_397_0 = _rtDW -> TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ;
} } _rtB -> B_40_316_0 = ( _rtB -> B_40_314_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_40_397_0 ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock
( S , 40 , 327 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 328 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 4 , 0 ) ) { _rtB ->
B_40_329_0 [ 0 ] = _rtB -> B_29_0_0 [ 0 ] ; _rtB -> B_40_329_0 [ 1 ] = _rtB
-> B_29_0_0 [ 1 ] ; _rtB -> B_40_330_0 [ 0 ] = _rtB -> B_40_149_0 ; _rtB ->
B_40_330_0 [ 1 ] = _rtB -> B_40_150_0 ; } memcpy ( & _rtB -> B_40_331_0 [ 0 ]
, & _rtDW -> Memory1_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB
-> B_40_332_0 [ 0 ] = _rtDW -> Memory2_PreviousInput [ 0 ] ; _rtB ->
B_40_332_0 [ 1 ] = _rtDW -> Memory2_PreviousInput [ 1 ] ; } if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 336 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 16 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 40 , 338 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 339 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 40 , 340 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 4 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 341 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 343 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 40 , 344 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 345 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 40 , 346 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsSampleHit ( S , 4 , 0 ) ) { _rtB -> B_40_349_0 [ 0 ] = _rtB -> B_30_0_0 [
0 ] ; _rtB -> B_40_349_0 [ 1 ] = _rtB -> B_30_0_0 [ 1 ] ; _rtB -> B_40_350_0
[ 0 ] = _rtB -> B_40_151_0 ; _rtB -> B_40_350_0 [ 1 ] = _rtB -> B_40_152_0 ;
} memcpy ( & _rtB -> B_40_351_0 [ 0 ] , & _rtDW -> Memory3_PreviousInput [ 0
] , 200U * sizeof ( real_T ) ) ; _rtB -> B_40_352_0 [ 0 ] = _rtDW ->
Memory4_PreviousInput [ 0 ] ; _rtB -> B_40_352_0 [ 1 ] = _rtDW ->
Memory4_PreviousInput [ 1 ] ; } if ( ssIsSampleHit ( S , 4 , 0 ) ) {
ssCallAccelRunBlock ( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 40 , 354 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 18 , 0 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_40_357_0 = 0.0 ; _rtB -> B_40_357_0 += _rtP -> P_448 * _rtX -> Hw2_CSTATE_p
[ 1 ] ; _rtB -> B_40_358_0 = _rtP -> P_450 * _rtB -> B_40_145_0 [ 5 ] ;
ssCallAccelRunBlock ( S , 40 , 359 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_40_360_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_452 ;
B_40_361_0 = uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_453 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_40_363_0 = _rtP -> P_454
; _rtB -> B_40_365_0 = _rtDW -> Memory_PreviousInput ; } if ( ssGetT ( S ) >=
_rtB -> B_40_363_0 ) { _rtB -> B_40_367_0 = ( _rtB -> B_40_360_0 - B_40_361_0
) * _rtP -> P_1 ; } else { _rtB -> B_40_367_0 = _rtB -> B_40_365_0 ; } _rtB
-> B_40_368_0 = _rtX -> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_457 ; B_40_369_0 = uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_h . Last , _rtDW ->
TransportDelay_IWORK_h . Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP
-> P_458 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_40_371_0 = _rtP -> P_459 ; _rtB -> B_40_373_0 = _rtDW
-> Memory_PreviousInput_f ; } if ( ssGetT ( S ) >= _rtB -> B_40_371_0 ) {
_rtB -> B_40_375_0 = ( _rtB -> B_40_368_0 - B_40_369_0 ) * _rtP -> P_0 ; }
else { _rtB -> B_40_375_0 = _rtB -> B_40_373_0 ; } rtb_RealImagtoComplex_re =
_rtB -> B_40_367_0 ; rtb_RealImagtoComplex_im = _rtB -> B_40_375_0 ; _rtB ->
B_40_378_0 = _rtX -> integrator_CSTATE_p ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_462 ; B_40_379_0 = uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_463 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S
, 1 , 0 ) ) { _rtB -> B_40_381_0 = _rtP -> P_464 ; _rtB -> B_40_383_0 = _rtDW
-> Memory_PreviousInput_p ; } if ( ssGetT ( S ) >= _rtB -> B_40_381_0 ) {
_rtB -> B_40_385_0 = ( _rtB -> B_40_378_0 - B_40_379_0 ) * _rtP -> P_3 ; }
else { _rtB -> B_40_385_0 = _rtB -> B_40_383_0 ; } _rtB -> B_40_386_0 = _rtX
-> integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_467 ; B_40_387_0 =
uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_468 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_40_389_0 = _rtP -> P_469
; _rtB -> B_40_391_0 = _rtDW -> Memory_PreviousInput_k ; } if ( ssGetT ( S )
>= _rtB -> B_40_389_0 ) { _rtB -> B_40_393_0 = ( _rtB -> B_40_386_0 -
B_40_387_0 ) * _rtP -> P_2 ; } else { _rtB -> B_40_393_0 = _rtB -> B_40_391_0
; } rtb_B_40_397_0 = muDoubleScalarHypot ( rtb_RealImagtoComplex_re ,
rtb_RealImagtoComplex_im ) * muDoubleScalarHypot ( _rtB -> B_40_385_0 , _rtB
-> B_40_393_0 ) * _rtP -> P_471 ; rtb_RealImagtoComplex_re = ( _rtP -> P_472
* muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im , rtb_RealImagtoComplex_re )
- _rtP -> P_473 * muDoubleScalarAtan2 ( _rtB -> B_40_393_0 , _rtB ->
B_40_385_0 ) ) * _rtP -> P_474 ; _rtB -> B_40_403_0 = rtb_B_40_397_0 *
muDoubleScalarCos ( rtb_RealImagtoComplex_re ) ; _rtB -> B_40_405_0 =
rtb_B_40_397_0 * muDoubleScalarSin ( rtb_RealImagtoComplex_re ) ;
ssCallAccelRunBlock ( S , 40 , 406 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_40_407_0 = _rtP -> P_475 * _rtB -> B_40_145_0 [ 0 ] ; ssCallAccelRunBlock (
S , 40 , 408 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_40_410_0 = muDoubleScalarSin
( _rtP -> P_479 * ssGetTaskTime ( S , 0 ) + _rtP -> P_480 ) * _rtP -> P_477 +
_rtP -> P_478 ; if ( ( _rtDW -> TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW ->
TimeStampB_a >= ssGetT ( S ) ) ) { _rtB -> B_40_411_0 = 0.0 ; } else {
rtb_B_40_397_0 = _rtDW -> TimeStampA_b ; lastU = & _rtDW -> LastUAtTimeA_f ;
if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { if ( _rtDW ->
TimeStampB_a < ssGetT ( S ) ) { rtb_B_40_397_0 = _rtDW -> TimeStampB_a ;
lastU = & _rtDW -> LastUAtTimeB_n ; } } else { if ( _rtDW -> TimeStampA_b >=
ssGetT ( S ) ) { rtb_B_40_397_0 = _rtDW -> TimeStampB_a ; lastU = & _rtDW ->
LastUAtTimeB_n ; } } _rtB -> B_40_411_0 = ( _rtB -> B_40_410_0 - * lastU ) /
( ssGetT ( S ) - rtb_B_40_397_0 ) ; } _rtB -> B_40_412_0 = _rtB -> B_40_409_0
* _rtB -> B_40_411_0 ; _rtB -> B_40_413_0 = _rtB -> B_40_357_0 + _rtB ->
B_40_412_0 ; _rtB -> B_40_414_0 = 0.0 ; _rtB -> B_40_414_0 += _rtP -> P_483 *
_rtX -> Hi_Pass1_CSTATE ; _rtB -> B_40_414_0 += _rtP -> P_484 * _rtB ->
B_40_413_0 ; _rtB -> B_40_415_0 = 0.0 ; _rtB -> B_40_415_0 += _rtP -> P_488 *
_rtX -> Hw5_CSTATE [ 1 ] ; _rtB -> B_40_416_0 = _rtB -> B_40_415_0 + _rtB ->
B_40_357_0 ; _rtB -> B_40_417_0 = _rtB -> B_40_414_0 - _rtB -> B_40_416_0 ;
_rtB -> B_40_419_0 = 0.0 ; _rtB -> B_40_419_0 += _rtP -> P_492 [ 0 ] * _rtX
-> TransferFcn1_CSTATE_e [ 0 ] ; _rtB -> B_40_419_0 += _rtP -> P_492 [ 1 ] *
_rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtB -> B_40_422_0 = ( _rtP -> P_490 *
_rtB -> B_40_417_0 + _rtB -> B_40_419_0 ) + _rtB -> B_40_421_0 ;
ssCallAccelRunBlock ( S , 40 , 423 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_40_424_0 = 0.0 ; _rtB -> B_40_424_0 += _rtP -> P_496 * _rtX -> Hw6_CSTATE_f
[ 1 ] ; ssCallAccelRunBlock ( S , 40 , 425 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 426 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 427 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 6 , 0 ) ) { rtb_B_40_397_0
= ssGetTaskTime ( S , 6 ) ; if ( ssGetTNextWasAdjusted ( S , 6 ) ) { _rtDW ->
nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> justEnabled != 0
) { _rtDW -> justEnabled = 0 ; if ( rtb_B_40_397_0 >= _rtP -> P_501 ) {
rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_501 ) / _rtP -> P_499
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_499 + _rtP ->
P_501 ) + _rtP -> P_500 * _rtP -> P_499 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue = 0 ; _rtDW ->
nextTime = ( real_T ) ( numCycles + 1U ) * _rtP -> P_499 + _rtP -> P_501 ; }
} else { _rtDW -> numCompleteCycles = _rtP -> P_501 != 0.0 ? - 1 : 0 ; _rtDW
-> currentValue = 0 ; _rtDW -> nextTime = _rtP -> P_501 ; } } else { if (
_rtDW -> nextTime <= rtb_B_40_397_0 ) { if ( _rtDW -> currentValue == 1 ) {
_rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW ->
numCompleteCycles + 1LL ) * _rtP -> P_499 + _rtP -> P_501 ; } else { _rtDW ->
numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ( _rtP
-> P_500 * _rtP -> P_499 * 0.01 + ( real_T ) _rtDW -> numCompleteCycles *
_rtP -> P_499 ) + _rtP -> P_501 ; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW
-> nextTime ) ; if ( _rtDW -> currentValue == 1 ) { _rtB -> B_40_428_0 = _rtP
-> P_498 ; } else { _rtB -> B_40_428_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1
, 0 ) && ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_i , ( _rtB ->
B_40_428_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 33
, 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_eb = 4 ; } } if
( ssIsSampleHit ( S , 7 , 0 ) ) { rtb_B_40_397_0 = ssGetTaskTime ( S , 7 ) ;
if ( ssGetTNextWasAdjusted ( S , 7 ) ) { _rtDW -> nextTime_e =
_ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW -> justEnabled_l != 0 ) { _rtDW
-> justEnabled_l = 0 ; if ( rtb_B_40_397_0 >= _rtP -> P_509 ) {
rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_509 ) / _rtP -> P_507
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_j = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_507 + _rtP ->
P_509 ) + _rtP -> P_508 * _rtP -> P_507 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_d = 1 ; _rtDW ->
nextTime_e = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_d = 0
; _rtDW -> nextTime_e = ( real_T ) ( numCycles + 1U ) * _rtP -> P_507 + _rtP
-> P_509 ; } } else { _rtDW -> numCompleteCycles_j = _rtP -> P_509 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = _rtP -> P_509 ; }
} else { if ( _rtDW -> nextTime_e <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_d == 1 ) { _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = (
real_T ) ( _rtDW -> numCompleteCycles_j + 1LL ) * _rtP -> P_507 + _rtP ->
P_509 ; } else { _rtDW -> numCompleteCycles_j ++ ; _rtDW -> currentValue_d =
1 ; _rtDW -> nextTime_e = ( _rtP -> P_508 * _rtP -> P_507 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_j * _rtP -> P_507 ) + _rtP -> P_509 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_e ) ; if ( _rtDW ->
currentValue_d == 1 ) { _rtB -> B_40_435_0 = _rtP -> P_506 ; } else { _rtB ->
B_40_435_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_a , ( _rtB -> B_40_435_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 34 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_o = 4 ; } } if ( ssIsSampleHit ( S , 9 , 0 ) ) {
rtb_B_40_397_0 = ssGetTaskTime ( S , 9 ) ; if ( ssGetTNextWasAdjusted ( S , 9
) ) { _rtDW -> nextTime_f = _ssGetVarNextHitTime ( S , 3 ) ; } if ( _rtDW ->
justEnabled_k != 0 ) { _rtDW -> justEnabled_k = 0 ; if ( rtb_B_40_397_0 >=
_rtP -> P_517 ) { rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_517
) / _rtP -> P_515 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_o = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_515 + _rtP ->
P_517 ) + _rtP -> P_516 * _rtP -> P_515 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_a = 1 ; _rtDW ->
nextTime_f = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_a = 0
; _rtDW -> nextTime_f = ( real_T ) ( numCycles + 1U ) * _rtP -> P_515 + _rtP
-> P_517 ; } } else { _rtDW -> numCompleteCycles_o = _rtP -> P_517 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = _rtP -> P_517 ; }
} else { if ( _rtDW -> nextTime_f <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_a == 1 ) { _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = (
real_T ) ( _rtDW -> numCompleteCycles_o + 1LL ) * _rtP -> P_515 + _rtP ->
P_517 ; } else { _rtDW -> numCompleteCycles_o ++ ; _rtDW -> currentValue_a =
1 ; _rtDW -> nextTime_f = ( _rtP -> P_516 * _rtP -> P_515 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_o * _rtP -> P_515 ) + _rtP -> P_517 ; } } }
_ssSetVarNextHitTime ( S , 3 , _rtDW -> nextTime_f ) ; if ( _rtDW ->
currentValue_a == 1 ) { _rtB -> B_40_442_0 = _rtP -> P_514 ; } else { _rtB ->
B_40_442_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_d , ( _rtB -> B_40_442_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 36 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_p = 4 ; } } _rtB -> B_40_449_0 = _rtP -> P_522 * _rtB
-> B_40_145_0 [ 8 ] ; _rtB -> B_40_453_0 = 0.0 ; _rtB -> B_40_453_0 += _rtP
-> P_524 * _rtX -> TransferFcn_CSTATE_m ; _rtB -> B_40_454_0 = 0.0 ; _rtB ->
B_40_454_0 += _rtP -> P_526 * _rtX -> TransferFcn1_CSTATE_l ; _rtB ->
B_40_455_0 = _rtP -> P_527 * _rtB -> B_40_145_0 [ 2 ] ; _rtB -> B_40_459_0 =
_rtP -> P_528 * _rtB -> B_40_145_0 [ 9 ] ; _rtB -> B_40_463_0 = 0.0 ; _rtB ->
B_40_463_0 += _rtP -> P_530 * _rtX -> TransferFcn2_CSTATE ; _rtB ->
B_40_497_0 = _rtB -> B_40_422_0 + _rtB -> B_40_496_0 ; if ( ssIsSampleHit ( S
, 2 , 0 ) ) { _rtB -> B_40_511_0 = ( real_T ) ( ( _rtB -> B_40_497_0 !=
uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_498_0 ) && ( _rtB -> B_40_497_0 >= ( (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_537 , _rtP -> P_538 )
* _rtP -> P_539 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_540 ; if (
ssGetTaskTime ( S , 2 ) < _rtP -> P_541 ) { rtb_B_40_397_0 = _rtP -> P_542 ;
} else { rtb_B_40_397_0 = _rtP -> P_543 ; } _rtB -> B_40_513_0 = _rtB ->
B_40_511_0 * rtb_B_40_397_0 ; ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 2 ) < _rtP -> P_544 ) {
rtb_B_40_397_0 = _rtP -> P_545 ; } else { rtb_B_40_397_0 = _rtP -> P_546 ; }
_rtB -> B_40_516_0 = _rtB -> B_2_0_1 * rtb_B_40_397_0 ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtDW -> Step_MODE_f = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_548 ) ; if ( _rtDW -> Step_MODE_f == 1 ) { _rtB -> B_40_518_0 = _rtP ->
P_550 ; } else { _rtB -> B_40_518_0 = _rtP -> P_549 ; } } _rtB -> B_40_520_0
= rt_Lookup ( _rtP -> P_551 , 5 , ssGetT ( S ) , _rtP -> P_552 ) ; if ( _rtB
-> B_40_517_0 >= _rtP -> P_553 ) { _rtB -> B_40_521_0 = _rtB -> B_40_518_0 ;
} else { _rtB -> B_40_521_0 = _rtB -> B_40_520_0 ; } if ( ( _rtDW ->
TimeStampA_n >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_m >= ssGetT ( S ) ) )
{ _rtB -> B_40_522_0 = 0.0 ; } else { rtb_B_40_397_0 = _rtDW -> TimeStampA_n
; lastU = & _rtDW -> LastUAtTimeA_ma ; if ( _rtDW -> TimeStampA_n < _rtDW ->
TimeStampB_m ) { if ( _rtDW -> TimeStampB_m < ssGetT ( S ) ) { rtb_B_40_397_0
= _rtDW -> TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } else { if (
_rtDW -> TimeStampA_n >= ssGetT ( S ) ) { rtb_B_40_397_0 = _rtDW ->
TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; } } _rtB -> B_40_522_0 = (
_rtB -> B_40_520_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_40_397_0 ) ; } _rtB
-> B_40_537_0 = ( muDoubleScalarSin ( _rtP -> P_557 * ssGetTaskTime ( S , 0 )
+ _rtP -> P_558 ) * _rtP -> P_555 + _rtP -> P_556 ) * _rtB -> B_40_407_0 ;
_rtB -> B_40_539_0 = ( muDoubleScalarSin ( _rtP -> P_561 * ssGetTaskTime ( S
, 0 ) + _rtP -> P_562 ) * _rtP -> P_559 + _rtP -> P_560 ) * _rtB ->
B_40_407_0 ; _rtB -> B_40_541_0 = ( muDoubleScalarSin ( _rtP -> P_565 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_566 ) * _rtP -> P_563 + _rtP -> P_564 ) *
_rtB -> B_40_358_0 ; _rtB -> B_40_543_0 = ( muDoubleScalarSin ( _rtP -> P_569
* ssGetTaskTime ( S , 0 ) + _rtP -> P_570 ) * _rtP -> P_567 + _rtP -> P_568 )
* _rtB -> B_40_358_0 ; ssCallAccelRunBlock ( S , 40 , 544 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 545 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_40_549_0 = _rtP -> P_571 * _rtB ->
B_40_145_0 [ 7 ] ; ssCallAccelRunBlock ( S , 40 , 550 , SS_CALL_MDL_OUTPUTS )
; _rtB -> B_40_552_0 = _rtB -> B_40_81_0 - _rtP -> P_572 * _rtB -> B_40_549_0
; ssCallAccelRunBlock ( S , 40 , 553 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_40_554_0 = _rtP -> P_573 * _rtB ->
B_40_14_0 ; } _rtB -> B_40_555_0 = ( 1.0 - _rtB -> B_40_27_0 / _rtB ->
B_40_554_0 ) * 100.0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_40_555_0 >= _rtP -> P_574 ? 1 : _rtB ->
B_40_555_0 > _rtP -> P_575 ? 0 : - 1 ; } _rtB -> B_40_556_0 = _rtDW ->
Saturation_MODE == 1 ? _rtP -> P_574 : _rtDW -> Saturation_MODE == - 1 ? _rtP
-> P_575 : _rtB -> B_40_555_0 ; ssCallAccelRunBlock ( S , 40 , 557 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 11 , 0 ) ) { rtb_B_40_397_0
= ssGetTaskTime ( S , 11 ) ; if ( ssGetTNextWasAdjusted ( S , 11 ) ) { _rtDW
-> nextTime_i = _ssGetVarNextHitTime ( S , 5 ) ; } if ( _rtDW ->
justEnabled_m != 0 ) { _rtDW -> justEnabled_m = 0 ; if ( rtb_B_40_397_0 >=
_rtP -> P_579 ) { rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_579
) / _rtP -> P_577 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_f = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_577 + _rtP ->
P_579 ) + _rtP -> P_578 * _rtP -> P_577 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_h = 1 ; _rtDW ->
nextTime_i = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_h = 0
; _rtDW -> nextTime_i = ( real_T ) ( numCycles + 1U ) * _rtP -> P_577 + _rtP
-> P_579 ; } } else { _rtDW -> numCompleteCycles_f = _rtP -> P_579 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = _rtP -> P_579 ; }
} else { if ( _rtDW -> nextTime_i <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_h == 1 ) { _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = (
real_T ) ( _rtDW -> numCompleteCycles_f + 1LL ) * _rtP -> P_577 + _rtP ->
P_579 ; } else { _rtDW -> numCompleteCycles_f ++ ; _rtDW -> currentValue_h =
1 ; _rtDW -> nextTime_i = ( _rtP -> P_578 * _rtP -> P_577 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_f * _rtP -> P_577 ) + _rtP -> P_579 ; } } }
_ssSetVarNextHitTime ( S , 5 , _rtDW -> nextTime_i ) ; if ( _rtDW ->
currentValue_h == 1 ) { _rtB -> B_40_558_0 = _rtP -> P_576 ; } else { _rtB ->
B_40_558_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_m , ( _rtB -> B_40_558_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 38 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_m = 4 ; } } if ( ssIsMajorTimeStep ( S ) ) { _rtDW ->
Abs_MODE = ( _rtB -> B_40_549_0 >= 0.0 ) ; } _rtB -> B_40_574_0 = _rtDW ->
Abs_MODE > 0 ? _rtB -> B_40_549_0 : - _rtB -> B_40_549_0 ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_i =
( _rtB -> B_40_549_0 < uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_575_0 ) ; } _rtB
-> B_40_578_0 = _rtP -> P_588 * ( real_T ) _rtDW -> Compare_Mode_i ; } _rtB
-> B_40_579_0 = _rtB -> B_40_578_0 - _rtB -> B_40_58_0 ; _rtB -> B_40_580_0 =
_rtB -> B_40_574_0 * _rtB -> B_40_579_0 ; _rtB -> B_40_581_0 = _rtP -> P_589
* _rtB -> B_40_580_0 ; _rtB -> B_40_585_0 = _rtP -> P_591 * _rtB -> B_40_27_0
; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE_d = ( _rtB -> B_40_66_0
>= 0.0 ) ; } _rtB -> B_40_586_0 = _rtDW -> Abs_MODE_d > 0 ? _rtB -> B_40_66_0
: - _rtB -> B_40_66_0 ; _rtB -> B_40_587_0 = 0.05 * _rtB -> B_40_66_0 + -
_rtB -> B_40_71_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs1_MODE = (
_rtB -> B_40_587_0 >= 0.0 ) ; } _rtB -> B_40_588_0 = _rtDW -> Abs1_MODE > 0 ?
_rtB -> B_40_587_0 : - _rtB -> B_40_587_0 ; if ( ssIsSampleHit ( S , 1 , 0 )
) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Compare_Mode_e = ( _rtB ->
B_40_66_0 < uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_589_0 ) ; } _rtB ->
B_40_592_0 = _rtP -> P_593 * ( real_T ) _rtDW -> Compare_Mode_e ; } _rtB ->
B_40_594_0 = _rtB -> B_40_586_0 * _rtB -> B_40_588_0 ; _rtB -> B_40_595_0 = (
0.0 * _rtB -> B_40_586_0 * _rtB -> B_40_29_0 + _rtB -> B_40_592_0 ) + _rtB ->
B_40_594_0 ; _rtB -> B_40_598_0 = 0.0 ; _rtB -> B_40_598_0 += _rtP -> P_598 *
_rtX -> TransferFcn1_CSTATE_g ; _rtB -> B_40_599_0 = _rtP -> P_599 * _rtB ->
B_40_598_0 ; _rtB -> B_40_600_0 = _rtB -> B_40_583_0 + _rtB -> B_40_599_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S ) ) { zcEvent
= rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_h , ( _rtB ->
B_40_146_0 [ 11 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock (
S , 31 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_k = 4 ; }
} ssCallAccelRunBlock ( S , 19 , 0 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE
-> Subsystem_Trig_ZCE_d4 , ( _rtB -> B_40_146_0 [ 5 ] ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 28 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_l = 4 ; } } _rtB -> B_40_607_0 = _rtP -> P_600
* _rtB -> B_28_0_0 [ 1 ] ; ssCallAccelRunBlock ( S , 21 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 5 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 611 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 40 , 612 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 40 , 613 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 614 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 20 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 5 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 618 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 40 , 619 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 8 , 0 ) ) { rtb_B_40_397_0 = ssGetTaskTime ( S , 8 ) ; if
( ssGetTNextWasAdjusted ( S , 8 ) ) { _rtDW -> nextTime_j =
_ssGetVarNextHitTime ( S , 2 ) ; } if ( _rtDW -> justEnabled_j != 0 ) { _rtDW
-> justEnabled_j = 0 ; if ( rtb_B_40_397_0 >= _rtP -> P_608 ) {
rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_608 ) / _rtP -> P_606
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_h = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_606 + _rtP ->
P_608 ) + _rtP -> P_607 * _rtP -> P_606 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_n = 1 ; _rtDW ->
nextTime_j = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_n = 0
; _rtDW -> nextTime_j = ( real_T ) ( numCycles + 1U ) * _rtP -> P_606 + _rtP
-> P_608 ; } } else { _rtDW -> numCompleteCycles_h = _rtP -> P_608 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = _rtP -> P_608 ; }
} else { if ( _rtDW -> nextTime_j <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_n == 1 ) { _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = (
real_T ) ( _rtDW -> numCompleteCycles_h + 1LL ) * _rtP -> P_606 + _rtP ->
P_608 ; } else { _rtDW -> numCompleteCycles_h ++ ; _rtDW -> currentValue_n =
1 ; _rtDW -> nextTime_j = ( _rtP -> P_607 * _rtP -> P_606 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_h * _rtP -> P_606 ) + _rtP -> P_608 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime_j ) ; if ( _rtDW ->
currentValue_n == 1 ) { _rtB -> B_40_620_0 = _rtP -> P_605 ; } else { _rtB ->
B_40_620_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_o , ( _rtB -> B_40_620_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 35 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_b = 4 ; } } if ( ssIsSampleHit ( S , 10 , 0 ) ) {
rtb_B_40_397_0 = ssGetTaskTime ( S , 10 ) ; if ( ssGetTNextWasAdjusted ( S ,
10 ) ) { _rtDW -> nextTime_l = _ssGetVarNextHitTime ( S , 4 ) ; } if ( _rtDW
-> justEnabled_o != 0 ) { _rtDW -> justEnabled_o = 0 ; if ( rtb_B_40_397_0 >=
_rtP -> P_616 ) { rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_616
) / _rtP -> P_614 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_RealImagtoComplex_re ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles
+ 1U ) - rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re
) { numCycles ++ ; } _rtDW -> numCompleteCycles_hh = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_614 + _rtP ->
P_616 ) + _rtP -> P_615 * _rtP -> P_614 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_f = 1 ; _rtDW ->
nextTime_l = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_f = 0
; _rtDW -> nextTime_l = ( real_T ) ( numCycles + 1U ) * _rtP -> P_614 + _rtP
-> P_616 ; } } else { _rtDW -> numCompleteCycles_hh = _rtP -> P_616 != 0.0 ?
- 1 : 0 ; _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = _rtP -> P_616 ;
} } else { if ( _rtDW -> nextTime_l <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_f == 1 ) { _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = (
real_T ) ( _rtDW -> numCompleteCycles_hh + 1LL ) * _rtP -> P_614 + _rtP ->
P_616 ; } else { _rtDW -> numCompleteCycles_hh ++ ; _rtDW -> currentValue_f =
1 ; _rtDW -> nextTime_l = ( _rtP -> P_615 * _rtP -> P_614 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_hh * _rtP -> P_614 ) + _rtP -> P_616 ; } } }
_ssSetVarNextHitTime ( S , 4 , _rtDW -> nextTime_l ) ; if ( _rtDW ->
currentValue_f == 1 ) { _rtB -> B_40_627_0 = _rtP -> P_613 ; } else { _rtB ->
B_40_627_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep
( S ) ) { zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE ->
Subsystem_Trig_ZCE_f , ( _rtB -> B_40_627_0 ) ) ; if ( zcEvent != NO_ZCEVENT
) { ssCallAccelRunBlock ( S , 37 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_g = 4 ; } } if ( ssIsSampleHit ( S , 5 , 0 ) ) {
ssCallAccelRunBlock ( S , 40 , 634 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 40 , 635 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 40 , 636 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_40_642_0 = 0.0 ; _rtB -> B_40_642_0 += _rtP -> P_624 * _rtX ->
Actuador1_CSTATE ; _rtB -> B_40_643_0 = _rtP -> P_625 * _rtB -> B_40_642_0 ;
{ real_T * * uBuffer = ( real_T * * ) & _rtDW -> MotordeCombustin1_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; real_T tMinusDelay = simTime - _rtP -> P_626 ; _rtB -> B_40_644_0 =
uGrid_1PH_hd_caso3_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Last , _rtDW -> MotordeCombustin1_IWORK . Tail ,
_rtDW -> MotordeCombustin1_IWORK . Head , _rtP -> P_627 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_40_645_0 = _rtB -> B_40_644_0 - _rtB -> B_40_640_0 ; _rtB ->
B_40_646_0 = _rtP -> P_628 * _rtB -> B_40_145_0 [ 4 ] ; _rtB -> B_40_650_0 =
_rtB -> B_40_641_0 - _rtB -> B_40_6_0 ; _rtB -> B_40_651_0 = _rtP -> P_629 *
_rtB -> B_40_650_0 ; _rtB -> B_40_652_0 = _rtX -> Filter_CSTATE ; _rtB ->
B_40_653_0 = _rtB -> B_40_651_0 - _rtB -> B_40_652_0 ; _rtB -> B_40_654_0 =
_rtP -> P_631 * _rtB -> B_40_653_0 ; _rtB -> B_40_655_0 = _rtP -> P_632 *
_rtB -> B_40_650_0 ; _rtB -> B_40_656_0 = _rtX -> Integrator_CSTATE ; _rtB ->
B_40_657_0 = _rtP -> P_634 * _rtB -> B_40_650_0 ; _rtB -> B_40_658_0 = ( _rtB
-> B_40_657_0 + _rtB -> B_40_656_0 ) + _rtB -> B_40_654_0 ; if (
ssIsSampleHit ( S , 12 , 0 ) ) { rtb_B_40_397_0 = ssGetTaskTime ( S , 12 ) ;
if ( ssGetTNextWasAdjusted ( S , 12 ) ) { _rtDW -> nextTime_m =
_ssGetVarNextHitTime ( S , 6 ) ; } if ( _rtDW -> justEnabled_oj != 0 ) {
_rtDW -> justEnabled_oj = 0 ; if ( rtb_B_40_397_0 >= _rtP -> P_638 ) {
rtb_RealImagtoComplex_re = ( rtb_B_40_397_0 - _rtP -> P_638 ) / _rtP -> P_636
; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_RealImagtoComplex_re ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_RealImagtoComplex_re ) < DBL_EPSILON * rtb_RealImagtoComplex_re ) {
numCycles ++ ; } _rtDW -> numCompleteCycles_n = numCycles ;
rtb_RealImagtoComplex_re = ( ( real_T ) numCycles * _rtP -> P_636 + _rtP ->
P_638 ) + _rtP -> P_637 * _rtP -> P_636 / 100.0 ; if ( rtb_B_40_397_0 <
rtb_RealImagtoComplex_re ) { _rtDW -> currentValue_aj = 1 ; _rtDW ->
nextTime_m = rtb_RealImagtoComplex_re ; } else { _rtDW -> currentValue_aj = 0
; _rtDW -> nextTime_m = ( real_T ) ( numCycles + 1U ) * _rtP -> P_636 + _rtP
-> P_638 ; } } else { _rtDW -> numCompleteCycles_n = _rtP -> P_638 != 0.0 ? -
1 : 0 ; _rtDW -> currentValue_aj = 0 ; _rtDW -> nextTime_m = _rtP -> P_638 ;
} } else { if ( _rtDW -> nextTime_m <= rtb_B_40_397_0 ) { if ( _rtDW ->
currentValue_aj == 1 ) { _rtDW -> currentValue_aj = 0 ; _rtDW -> nextTime_m =
( real_T ) ( _rtDW -> numCompleteCycles_n + 1LL ) * _rtP -> P_636 + _rtP ->
P_638 ; } else { _rtDW -> numCompleteCycles_n ++ ; _rtDW -> currentValue_aj =
1 ; _rtDW -> nextTime_m = ( _rtP -> P_637 * _rtP -> P_636 * 0.01 + ( real_T )
_rtDW -> numCompleteCycles_n * _rtP -> P_636 ) + _rtP -> P_638 ; } } }
_ssSetVarNextHitTime ( S , 6 , _rtDW -> nextTime_m ) ; if ( _rtDW ->
currentValue_aj == 1 ) { _rtB -> B_40_662_0 = _rtP -> P_635 ; } else { _rtB
-> B_40_662_0 = 0.0 ; } } if ( ssIsSampleHit ( S , 5 , 0 ) ) { _rtB ->
B_40_668_0 = _rtDW -> NextOutput ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
rtb_B_40_663_0 = _rtB -> B_40_662_0 ; if ( ssIsMajorTimeStep ( S ) ) {
zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE ,
( rtb_B_40_663_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S
, 39 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_pb = 4 ; }
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_p , (
_rtB -> B_40_146_0 [ 13 ] ) ) ; if ( zcEvent != NO_ZCEVENT ) {
ssCallAccelRunBlock ( S , 32 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_g1 = 4 ; } } ssCallAccelRunBlock ( S , 40 , 671 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 40 , 672 ,
SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID13 ( SimStruct * S , int_T tid ) { real_T rtb_B_40_89_0 ; real_T
rtb_B_40_127_0 ; B_uGrid_1PH_hd_caso3_T * _rtB ; P_uGrid_1PH_hd_caso3_T *
_rtP ; _rtP = ( ( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_40_0_0 =
_rtP -> P_165 ; _rtB -> B_40_7_0 = _rtP -> P_173 ; if ( _rtP -> P_177 > _rtP
-> P_178 ) { if ( _rtP -> P_174 > _rtP -> P_175 ) { _rtB -> B_40_11_0 = _rtP
-> P_175 ; } else if ( _rtP -> P_174 < _rtP -> P_176 ) { _rtB -> B_40_11_0 =
_rtP -> P_176 ; } else { _rtB -> B_40_11_0 = _rtP -> P_174 ; } } else { _rtB
-> B_40_11_0 = _rtP -> P_174 ; } _rtB -> B_40_13_0 = _rtP -> P_180 ; _rtB ->
B_40_24_0 = _rtP -> P_190 ; _rtB -> B_40_30_0 = _rtP -> P_195 ; _rtB ->
B_40_31_0 = _rtP -> P_196 ; _rtB -> B_40_37_0 = _rtP -> P_198 ; _rtB ->
B_40_38_0 = _rtP -> P_199 ; _rtB -> B_40_48_0 = _rtP -> P_202 ; _rtB ->
B_40_49_0 = _rtP -> P_203 ; _rtB -> B_40_50_0 = _rtP -> P_204 ; _rtB ->
B_40_57_0 = _rtP -> P_205 ; if ( _rtP -> P_208 > _rtP -> P_210 ) { _rtB ->
B_40_65_0 = _rtP -> P_207 ; } else { _rtB -> B_40_65_0 = _rtP -> P_209 ; }
_rtB -> B_40_67_0 = _rtP -> P_213 ; _rtB -> B_40_68_0 = _rtP -> P_214 ; _rtB
-> B_40_72_0 = _rtP -> P_216 ; _rtB -> B_40_73_0 = _rtP -> P_217 ;
rtb_B_40_89_0 = _rtP -> P_224 + _rtP -> P_225 ; _rtB -> B_40_95_0 = _rtP ->
P_227 ; _rtB -> B_40_96_0 = ( ( rtb_B_40_89_0 - _rtP -> P_226 ) * _rtP ->
P_223 + _rtP -> P_222 ) * ( _rtP -> P_220 / _rtP -> P_221 ) * _rtB ->
B_40_95_0 ; _rtB -> B_40_97_0 = _rtP -> P_228 ; _rtB -> B_40_98_0 = _rtP ->
P_229 ; _rtB -> B_40_99_0 = _rtP -> P_230 ; _rtB -> B_40_100_0 = 0.0 / _rtB
-> B_40_99_0 ; _rtB -> B_40_105_0 = _rtP -> P_232 * rtb_B_40_89_0 / _rtP ->
P_233 * _rtP -> P_231 ; _rtB -> B_40_106_0 = _rtP -> P_234 ; rtb_B_40_127_0 =
rtb_B_40_89_0 / _rtP -> P_226 ; _rtB -> B_40_130_0 = _rtP -> P_222 / (
muDoubleScalarExp ( _rtP -> P_238 * _rtP -> P_233 / ( _rtP -> P_232 * _rtP ->
P_239 * rtb_B_40_89_0 * _rtP -> P_231 ) ) - _rtP -> P_240 ) * (
rtb_B_40_127_0 * rtb_B_40_127_0 * rtb_B_40_127_0 ) * muDoubleScalarExp ( (
_rtP -> P_236 / rtb_B_40_89_0 - _rtP -> P_235 / _rtP -> P_226 ) * ( _rtP ->
P_233 * _rtP -> P_237 / ( _rtP -> P_232 * _rtP -> P_231 ) ) ) ; _rtB ->
B_40_133_0 = _rtP -> P_242 ; _rtB -> B_40_134_0 = _rtP -> P_243 ; _rtB ->
B_40_135_0 = _rtP -> P_244 ; _rtB -> B_40_136_0 = _rtP -> P_245 ; _rtB ->
B_40_137_0 = _rtP -> P_246 ; _rtB -> B_40_138_0 = _rtP -> P_247 ; _rtB ->
B_40_139_0 = _rtP -> P_248 ; _rtB -> B_40_140_0 = _rtP -> P_249 ; _rtB ->
B_40_141_0 = _rtP -> P_250 ; _rtB -> B_40_142_0 = _rtP -> P_251 ; _rtB ->
B_40_143_0 = _rtP -> P_252 ; _rtB -> B_40_144_0 = _rtP -> P_253 ; _rtB ->
B_40_190_0 = _rtP -> P_368 ; _rtB -> B_40_194_0 = _rtP -> P_369 ; _rtB ->
B_40_198_0 = _rtP -> P_370 ; _rtB -> B_40_202_0 = _rtP -> P_371 ; _rtB ->
B_40_210_0 = _rtP -> P_372 ; _rtB -> B_40_231_0 = _rtP -> P_384 ; _rtB ->
B_40_269_0 = _rtP -> P_398 ; _rtB -> B_40_273_0 = _rtP -> P_399 ; _rtB ->
B_40_277_0 = _rtP -> P_400 ; _rtB -> B_40_281_0 = _rtP -> P_401 ; _rtB ->
B_40_289_0 = _rtP -> P_402 ; _rtB -> B_40_311_0 = _rtP -> P_428 ; _rtB ->
B_40_342_0 = _rtP -> P_440 ; memcpy ( & _rtB -> B_40_333_0 [ 0 ] , & _rtP ->
P_438 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_40_334_0 [
0 ] , & _rtP -> P_439 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB
-> B_40_347_0 [ 0 ] , & _rtP -> P_441 [ 0 ] , 40000U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_40_348_0 [ 0 ] , & _rtP -> P_442 [ 0 ] , 40000U * sizeof
( real_T ) ) ; _rtB -> B_40_356_0 = _rtP -> P_445 ; _rtB -> B_40_409_0 = _rtP
-> P_476 ; _rtB -> B_40_421_0 = _rtP -> P_493 ; _rtB -> B_40_430_0 = _rtP ->
P_502 ; _rtB -> B_40_431_0 = _rtP -> P_503 ; _rtB -> B_40_432_0 = _rtP ->
P_504 ; _rtB -> B_40_433_0 = _rtP -> P_505 ; _rtB -> B_40_437_0 = _rtP ->
P_510 ; _rtB -> B_40_438_0 = _rtP -> P_511 ; _rtB -> B_40_439_0 = _rtP ->
P_512 ; _rtB -> B_40_440_0 = _rtP -> P_513 ; _rtB -> B_40_444_0 = _rtP ->
P_518 ; _rtB -> B_40_445_0 = _rtP -> P_519 ; _rtB -> B_40_446_0 = _rtP ->
P_520 ; _rtB -> B_40_447_0 = _rtP -> P_521 ; _rtB -> B_40_476_0 = _rtP ->
P_531 ; _rtB -> B_40_480_0 = _rtP -> P_532 ; _rtB -> B_40_484_0 = _rtP ->
P_533 ; _rtB -> B_40_488_0 = _rtP -> P_534 ; _rtB -> B_40_496_0 = _rtP ->
P_535 ; _rtB -> B_40_517_0 = _rtP -> P_547 ; _rtB -> B_40_560_0 = _rtP ->
P_580 ; _rtB -> B_40_561_0 = _rtP -> P_581 ; _rtB -> B_40_562_0 = _rtP ->
P_582 ; _rtB -> B_40_563_0 = _rtP -> P_583 ; _rtB -> B_40_583_0 = _rtP ->
P_590 + _rtP -> P_586 ; if ( _rtP -> P_584 > _rtP -> P_596 ) { rtb_B_40_89_0
= ( _rtB -> B_40_583_0 - 293.15 ) * 0.0 + 1.0339999999999974 ; if (
rtb_B_40_89_0 > _rtP -> P_594 ) { _rtB -> B_40_597_0 = _rtP -> P_594 ; } else
if ( rtb_B_40_89_0 < _rtP -> P_595 ) { _rtB -> B_40_597_0 = _rtP -> P_595 ; }
else { _rtB -> B_40_597_0 = rtb_B_40_89_0 ; } } else { _rtB -> B_40_597_0 =
_rtP -> P_585 ; } _rtB -> B_40_608_0 [ 0 ] = _rtP -> P_601 [ 0 ] ; _rtB ->
B_40_609_0 [ 0 ] = _rtP -> P_602 [ 0 ] ; _rtB -> B_40_615_0 [ 0 ] = _rtP ->
P_603 [ 0 ] ; _rtB -> B_40_616_0 [ 0 ] = _rtP -> P_604 [ 0 ] ; _rtB ->
B_40_608_0 [ 1 ] = _rtP -> P_601 [ 1 ] ; _rtB -> B_40_609_0 [ 1 ] = _rtP ->
P_602 [ 1 ] ; _rtB -> B_40_615_0 [ 1 ] = _rtP -> P_603 [ 1 ] ; _rtB ->
B_40_616_0 [ 1 ] = _rtP -> P_604 [ 1 ] ; _rtB -> B_40_622_0 = _rtP -> P_609 ;
_rtB -> B_40_623_0 = _rtP -> P_610 ; _rtB -> B_40_624_0 = _rtP -> P_611 ;
_rtB -> B_40_625_0 = _rtP -> P_612 ; _rtB -> B_40_629_0 = _rtP -> P_617 ;
_rtB -> B_40_630_0 = _rtP -> P_618 ; _rtB -> B_40_631_0 = _rtP -> P_619 ;
_rtB -> B_40_632_0 = _rtP -> P_620 ; _rtB -> B_40_640_0 = _rtP -> P_621 ;
_rtB -> B_40_641_0 = _rtP -> P_622 ; _rtB -> B_40_664_0 = _rtP -> P_639 ;
_rtB -> B_40_665_0 = _rtP -> P_640 ; _rtB -> B_40_666_0 = _rtP -> P_641 ;
_rtB -> B_40_667_0 = _rtP -> P_642 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
B_uGrid_1PH_hd_caso3_T * _rtB ; P_uGrid_1PH_hd_caso3_T * _rtP ;
X_uGrid_1PH_hd_caso3_T * _rtX ; DW_uGrid_1PH_hd_caso3_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_caso3_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_uGrid_1PH_hd_caso3_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ; if ( ssIsSampleHit (
S , 1 , 0 ) ) { _rtDW -> itinit1_PreviousInput = _rtB -> B_40_597_0 ; _rtDW
-> itinit_PreviousInput = _rtB -> B_40_585_0 ; } _rtDW -> inti_IWORK = 0 ; if
( _rtX -> inti_CSTATE == _rtP -> P_187 ) { switch ( _rtDW -> inti_MODE ) {
case 3 : if ( _rtB -> B_40_549_0 < 0.0 ) { ssSetSolverNeedsReset ( S ) ;
_rtDW -> inti_MODE = 1 ; } break ; case 1 : if ( _rtB -> B_40_549_0 >= 0.0 )
{ _rtDW -> inti_MODE = 3 ; ssSetSolverNeedsReset ( S ) ; } break ; default :
ssSetSolverNeedsReset ( S ) ; if ( _rtB -> B_40_549_0 < 0.0 ) { _rtDW ->
inti_MODE = 1 ; } else { _rtDW -> inti_MODE = 3 ; } break ; } } else if (
_rtX -> inti_CSTATE == _rtP -> P_188 ) { switch ( _rtDW -> inti_MODE ) { case
4 : if ( _rtB -> B_40_549_0 > 0.0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW ->
inti_MODE = 2 ; } break ; case 2 : if ( _rtB -> B_40_549_0 <= 0.0 ) { _rtDW
-> inti_MODE = 4 ; ssSetSolverNeedsReset ( S ) ; } break ; default :
ssSetSolverNeedsReset ( S ) ; if ( _rtB -> B_40_549_0 > 0.0 ) { _rtDW ->
inti_MODE = 2 ; } else { _rtDW -> inti_MODE = 4 ; } break ; } } else { _rtDW
-> inti_MODE = 0 ; } ssCallAccelRunBlock ( S , 40 , 145 , SS_CALL_MDL_UPDATE
) ; if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT (
S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == (
rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) {
_rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else
{ _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } *
lastU = _rtB -> B_40_234_0 ; if ( _rtDW -> TimeStampA_k == ( rtInf ) ) {
_rtDW -> TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_m ; }
else if ( _rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW -> TimeStampB_f =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_o ; } else if ( _rtDW ->
TimeStampA_k < _rtDW -> TimeStampB_f ) { _rtDW -> TimeStampA_k = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_m ; } else { _rtDW -> TimeStampB_f = ssGetT
( S ) ; lastU = & _rtDW -> LastUAtTimeB_o ; } * lastU = _rtB -> B_40_314_0 ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> Memory2_PreviousInput [ 0 ] =
_rtB -> B_16_0_1 [ 0 ] ; _rtDW -> Memory2_PreviousInput [ 1 ] = _rtB ->
B_16_0_1 [ 1 ] ; memcpy ( & _rtDW -> Memory1_PreviousInput [ 0 ] , & _rtB ->
B_16_0_2 [ 0 ] , 200U * sizeof ( real_T ) ) ; memcpy ( & _rtDW ->
Memory3_PreviousInput [ 0 ] , & _rtB -> B_18_0_2 [ 0 ] , 200U * sizeof (
real_T ) ) ; _rtDW -> Memory4_PreviousInput [ 0 ] = _rtB -> B_18_0_1 [ 0 ] ;
_rtDW -> Memory4_PreviousInput [ 1 ] = _rtB -> B_18_0_1 [ 1 ] ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK . Head < (
_rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_452 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_40_360_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_40_367_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_h . Head =
( ( _rtDW -> TransportDelay_IWORK_h . Head < ( _rtDW ->
TransportDelay_IWORK_h . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_h . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_h . Head == _rtDW -> TransportDelay_IWORK_h . Tail ) {
if ( ! uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_h . CircularBufSize , & _rtDW -> TransportDelay_IWORK_h
. Tail , & _rtDW -> TransportDelay_IWORK_h . Head , & _rtDW ->
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_457 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_40_368_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_f = _rtB -> B_40_375_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_j .
Head = ( ( _rtDW -> TransportDelay_IWORK_j . Head < ( _rtDW ->
TransportDelay_IWORK_j . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_j . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_j . Head == _rtDW -> TransportDelay_IWORK_j . Tail ) {
if ( ! uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_j . CircularBufSize , & _rtDW -> TransportDelay_IWORK_j
. Tail , & _rtDW -> TransportDelay_IWORK_j . Head , & _rtDW ->
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_462 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_40_378_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_p = _rtB -> B_40_385_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_a .
Head = ( ( _rtDW -> TransportDelay_IWORK_a . Head < ( _rtDW ->
TransportDelay_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_a . Head == _rtDW -> TransportDelay_IWORK_a . Tail ) {
if ( ! uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_a . CircularBufSize , & _rtDW -> TransportDelay_IWORK_a
. Tail , & _rtDW -> TransportDelay_IWORK_a . Head , & _rtDW ->
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_467 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_40_386_0 ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput_k = _rtB -> B_40_393_0 ; } if ( _rtDW -> TimeStampA_b ==
( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_f ; } else if ( _rtDW -> TimeStampB_a == ( rtInf ) ) { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } else if (
_rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { _rtDW -> TimeStampA_b =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW ->
TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; } * lastU =
_rtB -> B_40_410_0 ; if ( _rtDW -> TimeStampA_n == ( rtInf ) ) { _rtDW ->
TimeStampA_n = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_ma ; } else if
( _rtDW -> TimeStampB_m == ( rtInf ) ) { _rtDW -> TimeStampB_m = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeB_g ; } else if ( _rtDW -> TimeStampA_n <
_rtDW -> TimeStampB_m ) { _rtDW -> TimeStampA_n = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeA_ma ; } else { _rtDW -> TimeStampB_m = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB_g ; } * lastU = _rtB -> B_40_520_0 ; { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> MotordeCombustin1_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; _rtDW -> MotordeCombustin1_IWORK . Head = ( ( _rtDW ->
MotordeCombustin1_IWORK . Head < ( _rtDW -> MotordeCombustin1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> MotordeCombustin1_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> MotordeCombustin1_IWORK . Head == _rtDW ->
MotordeCombustin1_IWORK . Tail ) { if ( !
uGrid_1PH_hd_caso3_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Tail , & _rtDW -> MotordeCombustin1_IWORK . Head ,
& _rtDW -> MotordeCombustin1_IWORK . Last , simTime - _rtP -> P_626 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
MotordeCombustin1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = _rtB -> B_40_643_0 ; } if ( ssIsSampleHit
( S , 5 , 0 ) ) { _rtDW -> NextOutput = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW
-> RandSeed ) * _rtP -> P_644 + _rtP -> P_643 ; } UNUSED_PARAMETER ( tid ) ;
}
#define MDL_UPDATE
static void mdlUpdateTID13 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_uGrid_1PH_hd_caso3_T * _rtB
; P_uGrid_1PH_hd_caso3_T * _rtP ; X_uGrid_1PH_hd_caso3_T * _rtX ;
XDot_uGrid_1PH_hd_caso3_T * _rtXdot ; XDis_uGrid_1PH_hd_caso3_T * _rtXdis ;
DW_uGrid_1PH_hd_caso3_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_caso3_T * )
ssGetRootDWork ( S ) ) ; _rtXdis = ( ( XDis_uGrid_1PH_hd_caso3_T * )
ssGetContStateDisabled ( S ) ) ; _rtXdot = ( ( XDot_uGrid_1PH_hd_caso3_T * )
ssGetdX ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_caso3_T * ) ssGetContStates ( S )
) ; _rtP = ( ( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Dinmicaeneleje1_CSTATE = 0.0 ; _rtXdot -> Dinmicaeneleje1_CSTATE += _rtP ->
P_166 * _rtX -> Dinmicaeneleje1_CSTATE ; _rtXdot -> Dinmicaeneleje1_CSTATE +=
_rtB -> B_40_645_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_170 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_40_646_0 ; _rtXdot -> Currentfilter_CSTATE =
0.0 ; _rtXdot -> Currentfilter_CSTATE += _rtP -> P_183 * _rtX ->
Currentfilter_CSTATE ; _rtXdot -> Currentfilter_CSTATE += _rtB -> B_40_549_0
; if ( ( _rtDW -> inti_MODE != 3 ) && ( _rtDW -> inti_MODE != 4 ) ) { _rtXdot
-> inti_CSTATE = _rtB -> B_40_549_0 ; _rtXdis -> inti_CSTATE = false ; } else
{ _rtXdot -> inti_CSTATE = 0.0 ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW
-> inti_MODE == 4 ) ) { _rtXdis -> inti_CSTATE = true ; } } _rtXdot ->
StateSpace_CSTATE = 0.0 ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_191 *
_rtX -> StateSpace_CSTATE ; _rtXdot -> StateSpace_CSTATE += _rtP -> P_192 *
_rtB -> B_40_600_0 ; _rtXdot -> Integrator2_CSTATE = _rtB -> B_40_581_0 ;
_rtXdot -> Currentfilter1_CSTATE = 0.0 ; _rtXdot -> Currentfilter1_CSTATE +=
_rtP -> P_211 * _rtX -> Currentfilter1_CSTATE ; _rtXdot ->
Currentfilter1_CSTATE += _rtB -> B_40_549_0 ; ssCallAccelRunBlock ( S , 40 ,
145 , SS_CALL_MDL_DERIVATIVES ) ; _rtXdot -> Hw2_CSTATE [ 0 ] = 0.0 ; _rtXdot
-> Hw6_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_316 [ 0 ] *
_rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_316 [ 1 ]
* _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 1 ] += _rtP -> P_316 [ 2
] * _rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_316 [
3 ] * _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_316
[ 4 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP ->
P_316 [ 5 ] * _rtX -> Hw2_CSTATE [ 3 ] ; _rtXdot -> Hw2_CSTATE [ 3 ] += _rtP
-> P_316 [ 6 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] +=
_rtP -> P_317 * _rtB -> B_40_166_0 [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 0 ] +=
_rtP -> P_320 [ 0 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [ 0 ]
+= _rtP -> P_320 [ 1 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 1
] += _rtP -> P_320 [ 2 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [
2 ] += _rtP -> P_320 [ 3 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE
[ 2 ] += _rtP -> P_320 [ 4 ] * _rtX -> Hw6_CSTATE [ 2 ] ; _rtXdot ->
Hw6_CSTATE [ 2 ] += _rtP -> P_320 [ 5 ] * _rtX -> Hw6_CSTATE [ 3 ] ; _rtXdot
-> Hw6_CSTATE [ 3 ] += _rtP -> P_320 [ 6 ] * _rtX -> Hw6_CSTATE [ 2 ] ;
_rtXdot -> Hw6_CSTATE [ 0 ] += _rtP -> P_321 * _rtB -> B_40_166_0 [ 2 ] ;
_rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_324 [ 0 ] * _rtX -> Hw1_CSTATE [ 0 ]
; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_324 [ 1 ] * _rtX -> Hw1_CSTATE [ 1
] ; _rtXdot -> Hw1_CSTATE [ 1 ] += _rtP -> P_324 [ 2 ] * _rtX -> Hw1_CSTATE [
0 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_324 [ 3 ] * _rtX -> Hw1_CSTATE
[ 1 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_324 [ 4 ] * _rtX ->
Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_324 [ 5 ] * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtXdot -> Hw1_CSTATE [ 3 ] += _rtP -> P_324 [ 6 ] *
_rtX -> Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_325 *
_rtB -> B_40_290_0 [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_328 [ 0 ]
* _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_328 [ 1
] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 1 ] += _rtP -> P_328 [
2 ] * _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP -> P_328
[ 3 ] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP ->
P_328 [ 4 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP
-> P_328 [ 5 ] * _rtX -> Hw3_CSTATE [ 3 ] ; _rtXdot -> Hw3_CSTATE [ 3 ] +=
_rtP -> P_328 [ 6 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 0 ]
+= _rtP -> P_329 * _rtB -> B_40_290_0 [ 2 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] =
0.0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 0 ] = 0.0
; _rtXdot -> Hw3_CSTATE_e [ 0 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw1_CSTATE_k [ 1 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw3_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP ->
P_332 [ 0 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP
-> P_332 [ 1 ] * _rtX -> Hw4_CSTATE [ 1 ] ; _rtXdot -> Hw4_CSTATE [ 1 ] +=
_rtP -> P_332 [ 2 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ]
+= _rtP -> P_333 * _rtB -> B_40_173_0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] += _rtP
-> P_336 [ 0 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot -> Hw1_CSTATE_k [ 0 ]
+= _rtP -> P_336 [ 1 ] * _rtX -> Hw1_CSTATE_k [ 1 ] ; _rtXdot -> Hw1_CSTATE_k
[ 1 ] += _rtP -> P_336 [ 2 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot ->
Hw1_CSTATE_k [ 0 ] += _rtP -> P_337 * _rtB -> B_40_172_0 ; _rtXdot ->
Hw7_CSTATE [ 0 ] += _rtP -> P_340 [ 0 ] * _rtX -> Hw7_CSTATE [ 0 ] ; _rtXdot
-> Hw7_CSTATE [ 0 ] += _rtP -> P_340 [ 1 ] * _rtX -> Hw7_CSTATE [ 1 ] ;
_rtXdot -> Hw7_CSTATE [ 1 ] += _rtP -> P_340 [ 2 ] * _rtX -> Hw7_CSTATE [ 0 ]
; _rtXdot -> Hw7_CSTATE [ 0 ] += _rtP -> P_341 * _rtB -> B_40_251_0 ; _rtXdot
-> Hw3_CSTATE_e [ 0 ] += _rtP -> P_344 [ 0 ] * _rtX -> Hw3_CSTATE_e [ 0 ] ;
_rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_344 [ 1 ] * _rtX -> Hw3_CSTATE_e [
1 ] ; _rtXdot -> Hw3_CSTATE_e [ 1 ] += _rtP -> P_344 [ 2 ] * _rtX ->
Hw3_CSTATE_e [ 0 ] ; _rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_345 * _rtB ->
B_40_252_0 ; _rtXdot -> TransferFcn_CSTATE_j = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_j += _rtP -> P_363 * _rtX -> TransferFcn_CSTATE_j ;
_rtXdot -> TransferFcn_CSTATE_j += _rtB -> B_40_168_0 ; _rtXdot ->
TransferFcn1_CSTATE = 0.0 ; _rtXdot -> TransferFcn1_CSTATE += _rtP -> P_365 *
_rtX -> TransferFcn1_CSTATE ; _rtXdot -> TransferFcn1_CSTATE += _rtB ->
B_40_174_0 ; _rtXdot -> TransferFcn_CSTATE_g = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_g += _rtP -> P_393 * _rtX -> TransferFcn_CSTATE_g ;
_rtXdot -> TransferFcn_CSTATE_g += _rtB -> B_40_247_0 ; _rtXdot ->
TransferFcn1_CSTATE_p = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_p += _rtP ->
P_395 * _rtX -> TransferFcn1_CSTATE_p ; _rtXdot -> TransferFcn1_CSTATE_p +=
_rtB -> B_40_253_0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] = 0.0 ; _rtXdot ->
Hw2_CSTATE_p [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP -> P_446 [ 0
] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP ->
P_446 [ 1 ] * _rtX -> Hw2_CSTATE_p [ 1 ] ; _rtXdot -> Hw2_CSTATE_p [ 1 ] +=
_rtP -> P_446 [ 2 ] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [
0 ] += _rtP -> P_447 * _rtB -> B_40_453_0 ; _rtXdot -> integrator_CSTATE =
_rtB -> B_40_537_0 ; _rtXdot -> integrator_CSTATE_i = _rtB -> B_40_539_0 ;
_rtXdot -> integrator_CSTATE_p = _rtB -> B_40_541_0 ; _rtXdot ->
integrator_CSTATE_l = _rtB -> B_40_543_0 ; _rtXdot -> Hi_Pass1_CSTATE = 0.0 ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_481 * _rtX -> Hi_Pass1_CSTATE ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_482 * _rtB -> B_40_413_0 ; _rtXdot ->
Hw5_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] = 0.0 ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtP -> P_491 [ 0 ] * _rtX ->
TransferFcn1_CSTATE_e [ 0 ] ; _rtXdot -> Hw5_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
TransferFcn1_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] +=
_rtP -> P_491 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtXdot ->
Hw5_CSTATE [ 0 ] += _rtP -> P_486 [ 0 ] * _rtX -> Hw5_CSTATE [ 0 ] ; _rtXdot
-> Hw5_CSTATE [ 0 ] += _rtP -> P_486 [ 1 ] * _rtX -> Hw5_CSTATE [ 1 ] ;
_rtXdot -> Hw5_CSTATE [ 1 ] += _rtP -> P_486 [ 2 ] * _rtX -> Hw5_CSTATE [ 0 ]
; _rtXdot -> Hw5_CSTATE [ 0 ] += _rtP -> P_487 * _rtB -> B_40_463_0 ; _rtXdot
-> TransferFcn1_CSTATE_e [ 1 ] += _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtB -> B_40_417_0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] = 0.0 ; _rtXdot -> Hw6_CSTATE_f [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] += _rtP -> P_494 [ 0 ] * _rtX -> Hw6_CSTATE_f [ 0 ] ;
_rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_494 [ 1 ] * _rtX -> Hw6_CSTATE_f [
1 ] ; _rtXdot -> Hw6_CSTATE_f [ 1 ] += _rtP -> P_494 [ 2 ] * _rtX ->
Hw6_CSTATE_f [ 0 ] ; _rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_495 * _rtB ->
B_40_454_0 ; _rtXdot -> TransferFcn_CSTATE_m = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_m += _rtP -> P_523 * _rtX -> TransferFcn_CSTATE_m ;
_rtXdot -> TransferFcn_CSTATE_m += _rtB -> B_40_449_0 ; _rtXdot ->
TransferFcn1_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_l += _rtP ->
P_525 * _rtX -> TransferFcn1_CSTATE_l ; _rtXdot -> TransferFcn1_CSTATE_l +=
_rtB -> B_40_455_0 ; _rtXdot -> TransferFcn2_CSTATE = 0.0 ; _rtXdot ->
TransferFcn2_CSTATE += _rtP -> P_529 * _rtX -> TransferFcn2_CSTATE ; _rtXdot
-> TransferFcn2_CSTATE += _rtB -> B_40_459_0 ; _rtXdot ->
TransferFcn1_CSTATE_g = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_g += _rtP ->
P_597 * _rtX -> TransferFcn1_CSTATE_g ; _rtXdot -> TransferFcn1_CSTATE_g +=
_rtB -> B_40_595_0 ; _rtXdot -> Actuador1_CSTATE = 0.0 ; _rtXdot ->
Actuador1_CSTATE += _rtP -> P_623 * _rtX -> Actuador1_CSTATE ; _rtXdot ->
Actuador1_CSTATE += _rtB -> B_40_658_0 ; _rtXdot -> Filter_CSTATE = _rtB ->
B_40_654_0 ; _rtXdot -> Integrator_CSTATE = _rtB -> B_40_655_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_uGrid_1PH_hd_caso3_T * _rtB ;
P_uGrid_1PH_hd_caso3_T * _rtP ; DW_uGrid_1PH_hd_caso3_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_caso3_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ; ssCallAccelRunBlock (
S , 40 , 145 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { boolean_T anyStateSaturated
; B_uGrid_1PH_hd_caso3_T * _rtB ; P_uGrid_1PH_hd_caso3_T * _rtP ;
X_uGrid_1PH_hd_caso3_T * _rtX ; ZCV_uGrid_1PH_hd_caso3_T * _rtZCSV ;
DW_uGrid_1PH_hd_caso3_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_caso3_T * )
ssGetRootDWork ( S ) ) ; _rtZCSV = ( ( ZCV_uGrid_1PH_hd_caso3_T * )
ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_caso3_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_caso3_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_40_16_0 - uGrid_1PH_hd_caso3_rtC
( S ) -> B_40_17_0 ; if ( ( _rtDW -> inti_MODE == 1 ) && ( _rtX ->
inti_CSTATE >= _rtP -> P_187 ) ) { _rtZCSV -> inti_IntgUpLimit_ZC = 0.0 ; }
else { _rtZCSV -> inti_IntgUpLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_187 ;
} if ( ( _rtDW -> inti_MODE == 2 ) && ( _rtX -> inti_CSTATE <= _rtP -> P_188
) ) { _rtZCSV -> inti_IntgLoLimit_ZC = 0.0 ; } else { _rtZCSV ->
inti_IntgLoLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_188 ; }
anyStateSaturated = false ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW ->
inti_MODE == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> inti_LeaveSaturate_ZC = _rtB -> B_40_549_0 ; } else { _rtZCSV ->
inti_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB
-> B_40_22_0 - _rtB -> B_40_15_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB
-> B_40_22_0 - _rtB -> B_40_24_0 ; _rtZCSV -> LowerRelop1_RelopInput_ZC_i =
_rtB -> B_40_22_0 - _rtB -> B_40_39_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f
= _rtB -> B_40_22_0 - _rtB -> B_40_41_0 ; _rtZCSV -> Compare_RelopInput_ZC_d
= _rtB -> B_40_16_0 - uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_45_0 ; _rtZCSV ->
LowerRelop1_RelopInput_ZC_a = _rtB -> B_40_76_0 - _rtB -> B_40_7_0 ; _rtZCSV
-> UpperRelop_RelopInput_ZC_g = _rtB -> B_40_76_0 - _rtB -> B_40_78_0 ;
ssCallAccelRunBlock ( S , 40 , 145 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 40 , 146 , SS_CALL_MDL_ZERO_CROSSINGS ) ;
ssCallAccelRunBlock ( S , 40 , 166 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_385 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_40_236_0 - _rtP -> P_391 ;
ssCallAccelRunBlock ( S , 40 , 290 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> Step_StepTime_ZC_d = ssGetT ( S ) - _rtP -> P_429 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_j = _rtB -> B_40_316_0 - _rtP -> P_435 ; _rtZCSV
-> Step_StepTime_ZC_b = ssGetT ( S ) - _rtP -> P_548 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_e = _rtB -> B_40_522_0 - _rtP -> P_554 ; _rtZCSV
-> Saturation_UprLim_ZC = _rtB -> B_40_555_0 - _rtP -> P_574 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_40_555_0 - _rtP -> P_575 ; _rtZCSV ->
Abs_AbsZc_ZC = _rtB -> B_40_549_0 ; _rtZCSV -> Compare_RelopInput_ZC_f = _rtB
-> B_40_549_0 - uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_575_0 ; _rtZCSV ->
Abs_AbsZc_ZC_j = _rtB -> B_40_66_0 ; _rtZCSV -> Abs1_AbsZc_ZC = _rtB ->
B_40_587_0 ; _rtZCSV -> Compare_RelopInput_ZC_b = _rtB -> B_40_66_0 -
uGrid_1PH_hd_caso3_rtC ( S ) -> B_40_589_0 ; } static void mdlInitializeSizes
( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3713999999U ) ;
ssSetChecksumVal ( S , 1 , 1531234698U ) ; ssSetChecksumVal ( S , 2 ,
97506234U ) ; ssSetChecksumVal ( S , 3 , 3700457567U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.9" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_uGrid_1PH_hd_caso3_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_uGrid_1PH_hd_caso3_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_uGrid_1PH_hd_caso3_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & uGrid_1PH_hd_caso3_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
uGrid_1PH_hd_caso3_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; (
( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) -> P_176 = rtMinusInf ; (
( P_uGrid_1PH_hd_caso3_T * ) ssGetModelRtp ( S ) ) -> P_188 = rtMinusInf ; }
static void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS
; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
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
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID13 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
