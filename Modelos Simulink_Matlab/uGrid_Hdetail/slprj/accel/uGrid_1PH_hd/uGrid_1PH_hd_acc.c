#include "__cf_uGrid_1PH_hd.h"
#include <math.h>
#include "uGrid_1PH_hd_acc.h"
#include "uGrid_1PH_hd_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
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
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
SimStruct * S , void * diag ) { if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) {
_ssSet_slErrMsg ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct * S
, DW_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_T * localDW ) {
ssCallAccelRunBlock ( S , 35 , localDW ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_blkIdxToRun , SS_CALL_MDL_OUTPUTS
) ; } void uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term (
SimStruct * const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid
) { real_T B_35_340_0 ; real_T B_35_348_0 ; real_T B_35_358_0 ; real_T
B_35_366_0 ; ZCEventType zcEvent ; real_T * lastU ; boolean_T rtb_B_35_343_0
; uint32_T numCycles ; real_T rtb_B_35_381_1 ; real_T rtb_B_35_27_0 ; real_T
rtb_B_35_26_0 ; real_T rtb_RealImagtoComplex_re ; real_T
rtb_RealImagtoComplex_im ; int32_T isHit ; B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX ; PrevZCX_uGrid_1PH_hd_T *
_rtZCE ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( ( DW_uGrid_1PH_hd_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_uGrid_1PH_hd_T * )
_ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB ->
B_35_1_0 = 0.0 ; _rtB -> B_35_1_0 += _rtP -> P_144 * _rtX ->
Dinmicaeneleje1_CSTATE ; _rtB -> B_35_2_0 = _rtP -> P_145 * _rtB -> B_35_1_0
; _rtB -> B_35_3_0 = _rtP -> P_146 * _rtB -> B_35_2_0 ; _rtB -> B_35_4_0 =
0.0 ; _rtB -> B_35_4_0 += _rtP -> P_148 * _rtX -> TransferFcn_CSTATE ; _rtB
-> B_35_5_0 = _rtP -> P_149 * _rtB -> B_35_4_0 ; _rtB -> B_35_6_0 = _rtB ->
B_35_3_0 - _rtB -> B_35_5_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_35_9_0 = _rtDW -> itinit1_PreviousInput ; _rtB ->
B_35_10_0 = _rtP -> P_153 * _rtB -> B_35_9_0 ; _rtB -> B_35_11_0 = 1.000001 *
_rtB -> B_35_10_0 * 0.96711798839458663 / 0.9999 ; } _rtB -> B_35_12_0 = 0.0
; _rtB -> B_35_12_0 += _rtP -> P_155 * _rtX -> Currentfilter_CSTATE ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode = ( _rtB -> B_35_12_0 > uGrid_1PH_hd_rtC ( S
) -> B_35_13_0 ) ; } _rtB -> B_35_15_0 = _rtDW -> Compare_Mode ; _rtB ->
B_35_16_0 = _rtDW -> itinit_PreviousInput ; } if ( ssIsMajorTimeStep ( S ) !=
0 ) { rtb_B_35_343_0 = false ; zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING , &
_rtZCE -> inti_Reset_ZCE , _rtB -> B_35_15_0 ) ; if ( ( zcEvent != NO_ZCEVENT
) || ( _rtDW -> inti_IWORK != 0 ) ) { rtb_B_35_343_0 = true ; _rtX ->
inti_CSTATE = _rtB -> B_35_16_0 ; } if ( rtb_B_35_343_0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } if ( _rtX -> inti_CSTATE
>= _rtP -> P_158 ) { _rtX -> inti_CSTATE = _rtP -> P_158 ; } else { if ( _rtX
-> inti_CSTATE <= _rtP -> P_159 ) { _rtX -> inti_CSTATE = _rtP -> P_159 ; } }
} _rtB -> B_35_17_0 = _rtX -> inti_CSTATE ; _rtB -> B_35_18_0 = _rtP -> P_160
* _rtB -> B_35_17_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> LowerRelop1_Mode = ( _rtB ->
B_35_18_0 > _rtB -> B_35_10_0 ) ; _rtDW -> UpperRelop_Mode = ( _rtB ->
B_35_18_0 < _rtB -> B_35_20_0 ) ; } _rtB -> B_35_19_0 = _rtDW ->
LowerRelop1_Mode ; _rtB -> B_35_21_0 = _rtDW -> UpperRelop_Mode ; } if ( _rtB
-> B_35_19_0 ) { _rtB -> B_35_23_0 = _rtB -> B_35_10_0 ; } else { if ( _rtB
-> B_35_21_0 ) { _rtB -> B_10_0_0 = _rtB -> B_35_20_0 ; } else { _rtB ->
B_10_0_0 = _rtB -> B_35_18_0 ; } _rtB -> B_35_23_0 = _rtB -> B_10_0_0 ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator_Mode = ( _rtB ->
B_35_11_0 <= _rtB -> B_35_23_0 ) ; } _rtB -> B_35_24_0 = _rtDW ->
RelationalOperator_Mode ; } if ( _rtB -> B_35_24_0 ) { _rtB -> B_35_25_0 =
_rtB -> B_35_10_0 ; } else { _rtB -> B_35_25_0 = _rtB -> B_35_23_0 ; } isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_30_0 = _rtP
-> P_164 * _rtB -> B_35_9_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
LowerRelop1_Mode_g = ( _rtB -> B_35_18_0 > _rtB -> B_35_30_0 ) ; } _rtB ->
B_35_31_0 = _rtDW -> LowerRelop1_Mode_g ; _rtB -> B_35_32_0 = - _rtB ->
B_35_30_0 * 0.999 * 0.1 * 0.9999 ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> UpperRelop_Mode_g = ( _rtB -> B_35_18_0 < _rtB -> B_35_32_0 ) ; }
_rtB -> B_35_33_0 = _rtDW -> UpperRelop_Mode_g ; } if ( _rtB -> B_35_31_0 ) {
_rtB -> B_35_35_0 = _rtB -> B_35_30_0 ; } else { if ( _rtB -> B_35_33_0 ) {
_rtB -> B_11_0_0 = _rtB -> B_35_32_0 ; } else { _rtB -> B_11_0_0 = _rtB ->
B_35_18_0 ; } _rtB -> B_35_35_0 = _rtB -> B_11_0_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> Compare_Mode_k = ( _rtB -> B_35_12_0 < uGrid_1PH_hd_rtC ( S ) ->
B_35_36_0 ) ; } _rtB -> B_35_38_0 = _rtDW -> Compare_Mode_k ; } switch ( (
int32_T ) _rtB -> B_35_28_0 ) { case 1 : _rtB -> B_7_0_0 [ 0 ] = _rtB ->
B_35_29_0 * _rtB -> B_35_35_0 ; _rtB -> B_7_0_0 [ 1 ] = _rtB -> B_35_29_0 *
_rtB -> B_35_12_0 ; _rtB -> B_7_0_0 [ 2 ] = _rtB -> B_35_29_0 * _rtB ->
B_35_38_0 ; _rtB -> B_7_0_0 [ 3 ] = _rtB -> B_35_29_0 * _rtB -> B_35_9_0 ;
_rtB -> B_35_46_0 = - _rtB -> B_7_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_7_0_0 [ 1 ] * ( 1.0339999999999974 / ( _rtB -> B_7_0_0 [ 0 ] +
0.10339999999999974 ) ) ; break ; case 2 : _rtB -> B_6_0_0 [ 0 ] = _rtB ->
B_35_39_0 * _rtB -> B_35_35_0 ; _rtB -> B_6_0_0 [ 1 ] = _rtB -> B_35_39_0 *
_rtB -> B_35_12_0 ; _rtB -> B_6_0_0 [ 2 ] = _rtB -> B_35_39_0 * _rtB ->
B_35_38_0 ; _rtB -> B_6_0_0 [ 3 ] = _rtB -> B_35_39_0 * _rtB -> B_35_9_0 ;
_rtB -> B_35_46_0 = - _rtB -> B_6_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_6_0_0 [ 1 ] * _rtB -> B_6_0_0 [ 3 ] / ( _rtB -> B_6_0_0 [ 3 ] * 0.1 + _rtB
-> B_6_0_0 [ 0 ] ) ; break ; case 3 : _rtB -> B_5_0_0 [ 0 ] = _rtB ->
B_35_40_0 * _rtB -> B_35_35_0 ; _rtB -> B_5_0_0 [ 1 ] = _rtB -> B_35_40_0 *
_rtB -> B_35_12_0 ; _rtB -> B_5_0_0 [ 2 ] = _rtB -> B_35_40_0 * _rtB ->
B_35_38_0 ; _rtB -> B_5_0_0 [ 3 ] = _rtB -> B_35_40_0 * _rtB -> B_35_9_0 ;
_rtB -> B_35_46_0 = - _rtB -> B_5_0_0 [ 2 ] * 0.0605295518538322 * _rtB ->
B_5_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB -> B_5_0_0
[ 0 ] ) + 0.10339999999999974 ) ) ; break ; default : _rtB -> B_4_0_0 [ 0 ] =
_rtB -> B_35_41_0 * _rtB -> B_35_35_0 ; _rtB -> B_4_0_0 [ 1 ] = _rtB ->
B_35_41_0 * _rtB -> B_35_12_0 ; _rtB -> B_4_0_0 [ 2 ] = _rtB -> B_35_41_0 *
_rtB -> B_35_38_0 ; _rtB -> B_4_0_0 [ 3 ] = _rtB -> B_35_41_0 * _rtB ->
B_35_9_0 ; _rtB -> B_35_46_0 = - _rtB -> B_4_0_0 [ 2 ] * 0.0605295518538322 *
_rtB -> B_4_0_0 [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( _rtB ->
B_4_0_0 [ 0 ] ) + 0.10339999999999974 ) ) ; break ; } _rtB -> B_35_48_0 =
_rtX -> Integrator2_CSTATE ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation_MODE = _rtB -> B_35_25_0 >= _rtP -> P_171 ? 1 : _rtB -> B_35_25_0
> _rtP -> P_172 ? 0 : - 1 ; } _rtB -> B_35_49_0 = _rtDW -> Saturation_MODE ==
1 ? _rtP -> P_171 : _rtDW -> Saturation_MODE == - 1 ? _rtP -> P_172 : _rtB ->
B_35_25_0 ; switch ( ( int32_T ) _rtB -> B_35_47_0 ) { case 1 : _rtB ->
B_35_51_0 = _rtB -> B_35_48_0 ; break ; case 2 : _rtB -> B_35_51_0 =
muDoubleScalarExp ( - 61.061946632469265 * _rtB -> B_35_49_0 ) *
83.400845004248509 ; break ; case 3 : _rtB -> B_35_51_0 = _rtB -> B_35_48_0 ;
break ; default : _rtB -> B_35_51_0 = _rtB -> B_35_48_0 ; break ; } _rtB ->
B_35_53_0 = ( ( ( - _rtB -> B_35_15_0 * 0.0605295518538322 * _rtB ->
B_35_12_0 * _rtB -> B_35_9_0 / ( _rtB -> B_35_9_0 - _rtB -> B_35_25_0 ) + -
0.0605295518538322 * _rtB -> B_35_9_0 / ( _rtB -> B_35_9_0 - _rtB ->
B_35_25_0 ) * _rtB -> B_35_25_0 ) + _rtB -> B_35_46_0 ) + _rtB -> B_35_51_0 )
+ - 0.0 * _rtB -> B_35_25_0 ; _rtB -> B_35_54_0 = _rtB -> B_35_8_0 + _rtB ->
B_35_53_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> LowerRelop1_Mode_c = ( _rtB ->
B_35_54_0 > _rtB -> B_35_7_0 ) ; } _rtB -> B_35_55_0 = _rtDW ->
LowerRelop1_Mode_c ; } _rtB -> B_35_56_0 = 0.0 ; _rtB -> B_35_56_0 += _rtP ->
P_174 * _rtX -> BAL_CSTATE ; _rtB -> B_35_57_0 = _rtP -> P_175 * _rtB ->
B_35_56_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> UpperRelop_Mode_gu = ( _rtB ->
B_35_54_0 < _rtB -> B_35_57_0 ) ; } _rtB -> B_35_58_0 = _rtDW ->
UpperRelop_Mode_gu ; } if ( _rtB -> B_35_55_0 ) { _rtB -> B_35_60_0 = _rtB ->
B_35_7_0 ; } else { if ( _rtB -> B_35_58_0 ) { _rtB -> B_9_0_0 = _rtB ->
B_35_57_0 ; } else { _rtB -> B_9_0_0 = _rtB -> B_35_54_0 ; } _rtB ->
B_35_60_0 = _rtB -> B_9_0_0 ; }
uGrid_1PH_hd_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S , & _rtDW ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ) ; _rtB -> B_35_111_0 = _rtP ->
P_197 * _rtB -> Synthesized_Atomic_Subsystem_For_Alg_Loop_1 . B_0_9_0 ;
ssCallAccelRunBlock ( S , 35 , 124 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 125 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_in ,
_rtB -> B_35_125_0 [ 7 ] ) ; if ( zcEvent != NO_ZCEVENT ) {
ssCallAccelRunBlock ( S , 26 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Subsystem_SubsysRanBC_c = 4 ; } zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_k , _rtB -> B_35_125_0 [ 9 ] ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 27 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_d = 4 ; } } } _rtB -> B_35_128_0 = 0.0 ; _rtB
-> B_35_128_0 += _rtP -> P_274 * _rtX -> Hw2_CSTATE [ 3 ] ; _rtB ->
B_35_129_0 = 0.0 ; _rtB -> B_35_129_0 += _rtP -> P_278 * _rtX -> Hw6_CSTATE [
3 ] ; _rtB -> B_35_130_0 = 0.0 ; _rtB -> B_35_130_0 += _rtP -> P_282 * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtB -> B_35_131_0 = 0.0 ; _rtB -> B_35_131_0 += _rtP
-> P_286 * _rtX -> Hw3_CSTATE [ 3 ] ; ssCallAccelRunBlock ( S , 35 , 132 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn (
ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_e , _rtB -> B_35_125_0 [ 3
] ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 24 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_ep = 4 ; } }
ssCallAccelRunBlock ( S , 35 , 134 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_at , _rtB -> B_35_125_0 [ 1 ] ) ; if ( zcEvent
!= NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 23 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_j = 4 ; } } ssCallAccelRunBlock ( S , 35 , 136
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 137 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_35_138_0 = 0.0 ; _rtB -> B_35_138_0 +=
_rtP -> P_290 * _rtX -> Hw4_CSTATE [ 1 ] ; _rtB -> B_35_139_0 = 0.0 ; _rtB ->
B_35_139_0 += _rtP -> P_294 * _rtX -> Hw1_CSTATE_k [ 1 ] ;
ssCallAccelRunBlock ( S , 35 , 140 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 141 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_35_142_0 = 0.0 ; _rtB ->
B_35_142_0 += _rtP -> P_298 * _rtX -> Hw7_CSTATE [ 1 ] ; _rtB -> B_35_143_0 =
0.0 ; _rtB -> B_35_143_0 += _rtP -> P_302 * _rtX -> Hw3_CSTATE_e [ 1 ] ;
ssCallAccelRunBlock ( S , 35 , 144 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 145 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 146 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_35_147_0 = _rtP -> P_318 * _rtB ->
B_35_124_0 [ 6 ] ; _rtB -> B_35_151_0 = 0.0 ; _rtB -> B_35_151_0 += _rtP ->
P_320 * _rtX -> TransferFcn_CSTATE_j ; _rtB -> B_35_152_0 = 0.0 ; _rtB ->
B_35_152_0 += _rtP -> P_322 * _rtX -> TransferFcn1_CSTATE ; _rtB ->
B_35_153_0 = _rtP -> P_323 * _rtB -> B_35_124_0 [ 1 ] ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_190_0 = _rtB -> B_35_145_0 [
0 ] + _rtB -> B_35_189_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_35_204_0 = ( real_T ) ( ( _rtB -> B_35_190_0 !=
uGrid_1PH_hd_rtC ( S ) -> B_35_191_0 ) && ( _rtB -> B_35_190_0 >= ( (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_330 , _rtP -> P_331 )
* _rtP -> P_332 * 2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_333 ;
rtb_B_35_26_0 = ssGetTaskTime ( S , 2 ) ; if ( rtb_B_35_26_0 < _rtP -> P_334
) { rtb_B_35_26_0 = _rtP -> P_335 ; } else { rtb_B_35_26_0 = _rtP -> P_336 ;
} _rtB -> B_35_206_0 = _rtB -> B_35_204_0 * rtb_B_35_26_0 ;
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; rtb_B_35_26_0 =
ssGetTaskTime ( S , 2 ) ; if ( rtb_B_35_26_0 < _rtP -> P_337 ) {
rtb_B_35_26_0 = _rtP -> P_338 ; } else { rtb_B_35_26_0 = _rtP -> P_339 ; }
_rtB -> B_35_209_0 = _rtB -> B_1_0_1 * rtb_B_35_26_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_35_26_0 =
ssGetTaskTime ( S , 1 ) ; _rtDW -> Step_MODE = ( rtb_B_35_26_0 >= _rtP ->
P_341 ) ; if ( _rtDW -> Step_MODE == 1 ) { _rtB -> B_35_211_0 = _rtP -> P_343
; } else { _rtB -> B_35_211_0 = _rtP -> P_342 ; } } _rtB -> B_35_213_0 =
rt_Lookup ( _rtP -> P_344 , 5 , ssGetT ( S ) , _rtP -> P_345 ) ; if ( _rtB ->
B_35_210_0 >= _rtP -> P_346 ) { _rtB -> B_35_214_0 = _rtB -> B_35_211_0 ; }
else { _rtB -> B_35_214_0 = _rtB -> B_35_213_0 ; } if ( ( _rtDW -> TimeStampA
>= ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB ->
B_35_215_0 = 0.0 ; } else { rtb_B_35_26_0 = _rtDW -> TimeStampA ; lastU = &
_rtDW -> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if
( _rtDW -> TimeStampB < ssGetT ( S ) ) { rtb_B_35_26_0 = _rtDW -> TimeStampB
; lastU = & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >=
ssGetT ( S ) ) { rtb_B_35_26_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } _rtB -> B_35_215_0 = ( _rtB -> B_35_213_0 - * lastU ) / (
ssGetT ( S ) - rtb_B_35_26_0 ) ; } _rtB -> B_35_226_0 = _rtP -> P_348 * _rtB
-> B_35_124_0 [ 7 ] ; _rtB -> B_35_230_0 = 0.0 ; _rtB -> B_35_230_0 += _rtP
-> P_350 * _rtX -> TransferFcn_CSTATE_g ; _rtB -> B_35_231_0 = 0.0 ; _rtB ->
B_35_231_0 += _rtP -> P_352 * _rtX -> TransferFcn1_CSTATE_p ; _rtB ->
B_35_232_0 = _rtP -> P_353 * _rtB -> B_35_124_0 [ 3 ] ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 35 , 269 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_270_0 = _rtB -> B_35_269_0 [ 0 ] + _rtB
-> B_35_268_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_35_284_0 = ( real_T ) ( ( _rtB -> B_35_270_0 != uGrid_1PH_hd_rtC (
S ) -> B_35_271_0 ) && ( _rtB -> B_35_270_0 >= ( ( muDoubleScalarRem (
ssGetTaskTime ( S , 2 ) + _rtP -> P_374 , _rtP -> P_375 ) * _rtP -> P_376 *
2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_377 ; rtb_B_35_26_0 = ssGetTaskTime
( S , 2 ) ; if ( rtb_B_35_26_0 < _rtP -> P_378 ) { rtb_B_35_26_0 = _rtP ->
P_379 ; } else { rtb_B_35_26_0 = _rtP -> P_380 ; } _rtB -> B_35_286_0 = _rtB
-> B_35_284_0 * rtb_B_35_26_0 ; ssCallAccelRunBlock ( S , 3 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; rtb_B_35_26_0 = ssGetTaskTime ( S , 2 ) ; if (
rtb_B_35_26_0 < _rtP -> P_381 ) { rtb_B_35_26_0 = _rtP -> P_382 ; } else {
rtb_B_35_26_0 = _rtP -> P_383 ; } _rtB -> B_35_289_0 = _rtB -> B_3_0_1 *
rtb_B_35_26_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_35_26_0 = ssGetTaskTime ( S , 1 ) ; _rtDW -> Step_MODE_c = (
rtb_B_35_26_0 >= _rtP -> P_385 ) ; if ( _rtDW -> Step_MODE_c == 1 ) { _rtB ->
B_35_291_0 = _rtP -> P_387 ; } else { _rtB -> B_35_291_0 = _rtP -> P_386 ; }
} _rtB -> B_35_293_0 = rt_Lookup ( _rtP -> P_388 , 5 , ssGetT ( S ) , _rtP ->
P_389 ) ; if ( _rtB -> B_35_290_0 >= _rtP -> P_390 ) { _rtB -> B_35_294_0 =
_rtB -> B_35_291_0 ; } else { _rtB -> B_35_294_0 = _rtB -> B_35_293_0 ; } if
( ( _rtDW -> TimeStampA_k >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_f >=
ssGetT ( S ) ) ) { _rtB -> B_35_295_0 = 0.0 ; } else { rtb_B_35_26_0 = _rtDW
-> TimeStampA_k ; lastU = & _rtDW -> LastUAtTimeA_m ; if ( _rtDW ->
TimeStampA_k < _rtDW -> TimeStampB_f ) { if ( _rtDW -> TimeStampB_f < ssGetT
( S ) ) { rtb_B_35_26_0 = _rtDW -> TimeStampB_f ; lastU = & _rtDW ->
LastUAtTimeB_o ; } } else { if ( _rtDW -> TimeStampA_k >= ssGetT ( S ) ) {
rtb_B_35_26_0 = _rtDW -> TimeStampB_f ; lastU = & _rtDW -> LastUAtTimeB_o ; }
} _rtB -> B_35_295_0 = ( _rtB -> B_35_293_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_35_26_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 35 , 306 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 35 , 307 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_308_0 [ 0 ] =
_rtB -> B_26_0_0 [ 0 ] ; _rtB -> B_35_308_0 [ 1 ] = _rtB -> B_26_0_0 [ 1 ] ;
} isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_35_309_0 [ 0 ] = _rtB -> B_35_128_0 ; _rtB -> B_35_309_0 [ 1 ] = _rtB ->
B_35_129_0 ; } memcpy ( & _rtB -> B_35_310_0 [ 0 ] , & _rtDW ->
Memory1_PreviousInput [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtB -> B_35_311_0
[ 0 ] = _rtDW -> Memory2_PreviousInput [ 0 ] ; _rtB -> B_35_311_0 [ 1 ] =
_rtDW -> Memory2_PreviousInput [ 1 ] ; } isHit = ssIsSampleHit ( S , 3 , 0 )
; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 12 , 0 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 35 , 315 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 13 , 0 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 35 , 317 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 318 , SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 35 , 319 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 35 , 320 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 322 , SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 35 , 323 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 35 , 324 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 35 , 325 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { isHit = ssIsSampleHit ( S ,
3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_328_0 [ 0 ] = _rtB -> B_27_0_0 [ 0
] ; _rtB -> B_35_328_0 [ 1 ] = _rtB -> B_27_0_0 [ 1 ] ; } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_329_0 [ 0 ] =
_rtB -> B_35_130_0 ; _rtB -> B_35_329_0 [ 1 ] = _rtB -> B_35_131_0 ; } memcpy
( & _rtB -> B_35_330_0 [ 0 ] , & _rtDW -> Memory3_PreviousInput [ 0 ] , 200U
* sizeof ( real_T ) ) ; _rtB -> B_35_331_0 [ 0 ] = _rtDW ->
Memory4_PreviousInput [ 0 ] ; _rtB -> B_35_331_0 [ 1 ] = _rtDW ->
Memory4_PreviousInput [ 1 ] ; } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 14 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 35 , 333 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 15 , 0 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_35_336_0 = 0.0 ; _rtB -> B_35_336_0 += _rtP -> P_404 * _rtX -> Hw2_CSTATE_p
[ 1 ] ; _rtB -> B_35_337_0 = _rtP -> P_406 * _rtB -> B_35_124_0 [ 5 ] ;
ssCallAccelRunBlock ( S , 35 , 338 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_339_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_408 ;
B_35_340_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_409 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_35_342_0 = _rtP -> P_410 ; } rtb_B_35_343_0 = ( ssGetT ( S ) >= _rtB ->
B_35_342_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_35_344_0 = _rtDW -> Memory_PreviousInput ; } if ( rtb_B_35_343_0 ) {
_rtB -> B_35_346_0 = ( _rtB -> B_35_339_0 - B_35_340_0 ) * _rtP -> P_1 ; }
else { _rtB -> B_35_346_0 = _rtB -> B_35_344_0 ; } _rtB -> B_35_347_0 = _rtX
-> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_413 ; B_35_348_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_h . Last , _rtDW -> TransportDelay_IWORK_h . Tail ,
_rtDW -> TransportDelay_IWORK_h . Head , _rtP -> P_414 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_35_350_0 = _rtP -> P_415 ; } rtb_B_35_343_0 = ( ssGetT ( S ) >= _rtB ->
B_35_350_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_35_352_0 = _rtDW -> Memory_PreviousInput_f ; } if ( rtb_B_35_343_0 ) {
_rtB -> B_35_354_0 = ( _rtB -> B_35_347_0 - B_35_348_0 ) * _rtP -> P_0 ; }
else { _rtB -> B_35_354_0 = _rtB -> B_35_352_0 ; } rtb_RealImagtoComplex_re =
_rtB -> B_35_346_0 ; rtb_RealImagtoComplex_im = _rtB -> B_35_354_0 ; _rtB ->
B_35_357_0 = _rtX -> integrator_CSTATE_p ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_418 ; B_35_358_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_419 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_360_0 = _rtP -> P_420 ; }
rtb_B_35_343_0 = ( ssGetT ( S ) >= _rtB -> B_35_360_0 ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_362_0 = _rtDW
-> Memory_PreviousInput_p ; } if ( rtb_B_35_343_0 ) { _rtB -> B_35_364_0 = (
_rtB -> B_35_357_0 - B_35_358_0 ) * _rtP -> P_3 ; } else { _rtB -> B_35_364_0
= _rtB -> B_35_362_0 ; } _rtB -> B_35_365_0 = _rtX -> integrator_CSTATE_l ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_423 ; B_35_366_0 =
uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_a . Last , _rtDW -> TransportDelay_IWORK_a . Tail ,
_rtDW -> TransportDelay_IWORK_a . Head , _rtP -> P_424 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_35_368_0 = _rtP -> P_425 ; } rtb_B_35_343_0 = ( ssGetT ( S ) >= _rtB ->
B_35_368_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_35_370_0 = _rtDW -> Memory_PreviousInput_k ; } if ( rtb_B_35_343_0 ) {
_rtB -> B_35_372_0 = ( _rtB -> B_35_365_0 - B_35_366_0 ) * _rtP -> P_2 ; }
else { _rtB -> B_35_372_0 = _rtB -> B_35_370_0 ; } rtb_B_35_26_0 =
muDoubleScalarHypot ( rtb_RealImagtoComplex_re , rtb_RealImagtoComplex_im ) *
muDoubleScalarHypot ( _rtB -> B_35_364_0 , _rtB -> B_35_372_0 ) * _rtP ->
P_427 ; muDoubleScalarSinCos ( _rtP -> P_430 * ( _rtP -> P_428 *
muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im , rtb_RealImagtoComplex_re ) -
_rtP -> P_429 * muDoubleScalarAtan2 ( _rtB -> B_35_372_0 , _rtB -> B_35_364_0
) ) , & rtb_B_35_27_0 , & rtb_B_35_381_1 ) ; _rtB -> B_35_382_0 =
rtb_B_35_26_0 * rtb_B_35_381_1 ; _rtB -> B_35_383_0 = rtb_B_35_26_0 *
rtb_B_35_27_0 ; ssCallAccelRunBlock ( S , 35 , 384 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_35_385_0 = _rtP -> P_431 * _rtB -> B_35_124_0 [ 0 ] ;
ssCallAccelRunBlock ( S , 35 , 386 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_35_388_0 = muDoubleScalarSin ( _rtP -> P_435 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_436 ) * _rtP -> P_433 + _rtP -> P_434 ; if ( ( _rtDW ->
TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_a >= ssGetT ( S ) ) )
{ _rtB -> B_35_389_0 = 0.0 ; } else { rtb_B_35_26_0 = _rtDW -> TimeStampA_b ;
lastU = & _rtDW -> LastUAtTimeA_f ; if ( _rtDW -> TimeStampA_b < _rtDW ->
TimeStampB_a ) { if ( _rtDW -> TimeStampB_a < ssGetT ( S ) ) { rtb_B_35_26_0
= _rtDW -> TimeStampB_a ; lastU = & _rtDW -> LastUAtTimeB_n ; } } else { if (
_rtDW -> TimeStampA_b >= ssGetT ( S ) ) { rtb_B_35_26_0 = _rtDW ->
TimeStampB_a ; lastU = & _rtDW -> LastUAtTimeB_n ; } } _rtB -> B_35_389_0 = (
_rtB -> B_35_388_0 - * lastU ) / ( ssGetT ( S ) - rtb_B_35_26_0 ) ; } _rtB ->
B_35_390_0 = _rtB -> B_35_387_0 * _rtB -> B_35_389_0 ; _rtB -> B_35_391_0 =
_rtB -> B_35_336_0 + _rtB -> B_35_390_0 ; _rtB -> B_35_392_0 = 0.0 ; _rtB ->
B_35_392_0 += _rtP -> P_439 * _rtX -> Hi_Pass1_CSTATE ; _rtB -> B_35_392_0 +=
_rtP -> P_440 * _rtB -> B_35_391_0 ; _rtB -> B_35_393_0 = 0.0 ; _rtB ->
B_35_393_0 += _rtP -> P_444 * _rtX -> Hw5_CSTATE [ 1 ] ; _rtB -> B_35_394_0 =
_rtB -> B_35_393_0 + _rtB -> B_35_336_0 ; _rtB -> B_35_395_0 = _rtB ->
B_35_392_0 - _rtB -> B_35_394_0 ; _rtB -> B_35_397_0 = 0.0 ; _rtB ->
B_35_397_0 += _rtP -> P_448 [ 0 ] * _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtB -> B_35_397_0 += _rtP -> P_448 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1
] ; _rtB -> B_35_400_0 = ( _rtP -> P_446 * _rtB -> B_35_395_0 + _rtB ->
B_35_397_0 ) + _rtB -> B_35_399_0 ; ssCallAccelRunBlock ( S , 35 , 401 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_402_0 = 0.0 ; _rtB -> B_35_402_0 += _rtP
-> P_452 * _rtX -> Hw6_CSTATE_f [ 1 ] ; ssCallAccelRunBlock ( S , 35 , 403 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 5 , 0 ) ; if ( isHit != 0
) { rtb_B_35_26_0 = ssGetTaskTime ( S , 5 ) ; if ( ssGetTNextWasAdjusted ( S
, 5 ) != 0 ) { _rtDW -> nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if (
_rtDW -> justEnabled != 0 ) { _rtDW -> justEnabled = 0 ; if ( rtb_B_35_26_0
>= _rtP -> P_457 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP -> P_457 ) / _rtP
-> P_455 ; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_B_35_27_0 ) ;
if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - rtb_B_35_27_0 ) <
DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW -> numCompleteCycles =
numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles * _rtP -> P_455 + _rtP ->
P_457 ) + _rtP -> P_456 * _rtP -> P_455 / 100.0 ; if ( rtb_B_35_26_0 <
rtb_B_35_27_0 ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime =
rtb_B_35_27_0 ; } else { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = (
real_T ) ( numCycles + 1U ) * _rtP -> P_455 + _rtP -> P_457 ; } } else {
_rtDW -> numCompleteCycles = _rtP -> P_457 != 0.0 ? - 1 : 0 ; _rtDW ->
currentValue = 0 ; _rtDW -> nextTime = _rtP -> P_457 ; } } else { if ( _rtDW
-> nextTime <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue == 1 ) { _rtDW ->
currentValue = 0 ; _rtDW -> nextTime = ( real_T ) ( _rtDW ->
numCompleteCycles + 1LL ) * _rtP -> P_455 + _rtP -> P_457 ; } else { _rtDW ->
numCompleteCycles ++ ; _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ( _rtP
-> P_456 * _rtP -> P_455 * 0.01 + ( real_T ) _rtDW -> numCompleteCycles *
_rtP -> P_455 ) + _rtP -> P_457 ; } } } _ssSetVarNextHitTime ( S , 0 , _rtDW
-> nextTime ) ; if ( _rtDW -> currentValue == 1 ) { _rtB -> B_35_404_0 = _rtP
-> P_454 ; } else { _rtB -> B_35_404_0 = 0.0 ; } } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) {
zcEvent = rt_ZCFcn ( FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_i
, _rtB -> B_35_404_0 ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock (
S , 29 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_e = 4 ; }
} isHit = ssIsSampleHit ( S , 6 , 0 ) ; if ( isHit != 0 ) { rtb_B_35_26_0 =
ssGetTaskTime ( S , 6 ) ; if ( ssGetTNextWasAdjusted ( S , 6 ) != 0 ) { _rtDW
-> nextTime_e = _ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW ->
justEnabled_l != 0 ) { _rtDW -> justEnabled_l = 0 ; if ( rtb_B_35_26_0 >=
_rtP -> P_465 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP -> P_465 ) / _rtP ->
P_463 ; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_B_35_27_0 ) ; if (
muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - rtb_B_35_27_0 ) <
DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW -> numCompleteCycles_j
= numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles * _rtP -> P_463 + _rtP
-> P_465 ) + _rtP -> P_464 * _rtP -> P_463 / 100.0 ; if ( rtb_B_35_26_0 <
rtb_B_35_27_0 ) { _rtDW -> currentValue_d = 1 ; _rtDW -> nextTime_e =
rtb_B_35_27_0 ; } else { _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e =
( real_T ) ( numCycles + 1U ) * _rtP -> P_463 + _rtP -> P_465 ; } } else {
_rtDW -> numCompleteCycles_j = _rtP -> P_465 != 0.0 ? - 1 : 0 ; _rtDW ->
currentValue_d = 0 ; _rtDW -> nextTime_e = _rtP -> P_465 ; } } else { if (
_rtDW -> nextTime_e <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue_d == 1 )
{ _rtDW -> currentValue_d = 0 ; _rtDW -> nextTime_e = ( real_T ) ( _rtDW ->
numCompleteCycles_j + 1LL ) * _rtP -> P_463 + _rtP -> P_465 ; } else { _rtDW
-> numCompleteCycles_j ++ ; _rtDW -> currentValue_d = 1 ; _rtDW -> nextTime_e
= ( _rtP -> P_464 * _rtP -> P_463 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_j * _rtP -> P_463 ) + _rtP -> P_465 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_e ) ; if ( _rtDW ->
currentValue_d == 1 ) { _rtB -> B_35_411_0 = _rtP -> P_462 ; } else { _rtB ->
B_35_411_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit !=
0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_a , _rtB -> B_35_411_0
) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 30 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_o = 4 ; } } isHit =
ssIsSampleHit ( S , 8 , 0 ) ; if ( isHit != 0 ) { rtb_B_35_26_0 =
ssGetTaskTime ( S , 8 ) ; if ( ssGetTNextWasAdjusted ( S , 8 ) != 0 ) { _rtDW
-> nextTime_f = _ssGetVarNextHitTime ( S , 3 ) ; } if ( _rtDW ->
justEnabled_k != 0 ) { _rtDW -> justEnabled_k = 0 ; if ( rtb_B_35_26_0 >=
_rtP -> P_473 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP -> P_473 ) / _rtP ->
P_471 ; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_B_35_27_0 ) ; if (
muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - rtb_B_35_27_0 ) <
DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW -> numCompleteCycles_o
= numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles * _rtP -> P_471 + _rtP
-> P_473 ) + _rtP -> P_472 * _rtP -> P_471 / 100.0 ; if ( rtb_B_35_26_0 <
rtb_B_35_27_0 ) { _rtDW -> currentValue_a = 1 ; _rtDW -> nextTime_f =
rtb_B_35_27_0 ; } else { _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f =
( real_T ) ( numCycles + 1U ) * _rtP -> P_471 + _rtP -> P_473 ; } } else {
_rtDW -> numCompleteCycles_o = _rtP -> P_473 != 0.0 ? - 1 : 0 ; _rtDW ->
currentValue_a = 0 ; _rtDW -> nextTime_f = _rtP -> P_473 ; } } else { if (
_rtDW -> nextTime_f <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue_a == 1 )
{ _rtDW -> currentValue_a = 0 ; _rtDW -> nextTime_f = ( real_T ) ( _rtDW ->
numCompleteCycles_o + 1LL ) * _rtP -> P_471 + _rtP -> P_473 ; } else { _rtDW
-> numCompleteCycles_o ++ ; _rtDW -> currentValue_a = 1 ; _rtDW -> nextTime_f
= ( _rtP -> P_472 * _rtP -> P_471 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_o * _rtP -> P_471 ) + _rtP -> P_473 ; } } }
_ssSetVarNextHitTime ( S , 3 , _rtDW -> nextTime_f ) ; if ( _rtDW ->
currentValue_a == 1 ) { _rtB -> B_35_418_0 = _rtP -> P_470 ; } else { _rtB ->
B_35_418_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit !=
0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_d , _rtB -> B_35_418_0
) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 32 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_p = 4 ; } } _rtB ->
B_35_425_0 = _rtP -> P_478 * _rtB -> B_35_124_0 [ 8 ] ; _rtB -> B_35_429_0 =
0.0 ; _rtB -> B_35_429_0 += _rtP -> P_480 * _rtX -> TransferFcn_CSTATE_m ;
_rtB -> B_35_430_0 = 0.0 ; _rtB -> B_35_430_0 += _rtP -> P_482 * _rtX ->
TransferFcn1_CSTATE_l ; _rtB -> B_35_431_0 = _rtP -> P_483 * _rtB ->
B_35_124_0 [ 2 ] ; _rtB -> B_35_435_0 = _rtP -> P_484 * _rtB -> B_35_124_0 [
9 ] ; _rtB -> B_35_439_0 = 0.0 ; _rtB -> B_35_439_0 += _rtP -> P_486 * _rtX
-> TransferFcn2_CSTATE ; _rtB -> B_35_473_0 = _rtB -> B_35_400_0 + _rtB ->
B_35_472_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_35_487_0 = ( real_T ) ( ( _rtB -> B_35_473_0 != uGrid_1PH_hd_rtC ( S )
-> B_35_474_0 ) && ( _rtB -> B_35_473_0 >= ( ( muDoubleScalarRem (
ssGetTaskTime ( S , 2 ) + _rtP -> P_493 , _rtP -> P_494 ) * _rtP -> P_495 *
2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) * _rtP -> P_496 ; rtb_B_35_26_0 = ssGetTaskTime
( S , 2 ) ; if ( rtb_B_35_26_0 < _rtP -> P_497 ) { rtb_B_35_26_0 = _rtP ->
P_498 ; } else { rtb_B_35_26_0 = _rtP -> P_499 ; } _rtB -> B_35_489_0 = _rtB
-> B_35_487_0 * rtb_B_35_26_0 ; ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; rtb_B_35_26_0 = ssGetTaskTime ( S , 2 ) ; if (
rtb_B_35_26_0 < _rtP -> P_500 ) { rtb_B_35_26_0 = _rtP -> P_501 ; } else {
rtb_B_35_26_0 = _rtP -> P_502 ; } _rtB -> B_35_492_0 = _rtB -> B_2_0_1 *
rtb_B_35_26_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
rtb_B_35_26_0 = ssGetTaskTime ( S , 1 ) ; _rtDW -> Step_MODE_f = (
rtb_B_35_26_0 >= _rtP -> P_504 ) ; if ( _rtDW -> Step_MODE_f == 1 ) { _rtB ->
B_35_494_0 = _rtP -> P_506 ; } else { _rtB -> B_35_494_0 = _rtP -> P_505 ; }
} _rtB -> B_35_496_0 = rt_Lookup ( _rtP -> P_507 , 5 , ssGetT ( S ) , _rtP ->
P_508 ) ; if ( _rtB -> B_35_493_0 >= _rtP -> P_509 ) { _rtB -> B_35_497_0 =
_rtB -> B_35_494_0 ; } else { _rtB -> B_35_497_0 = _rtB -> B_35_496_0 ; } if
( ( _rtDW -> TimeStampA_n >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_m >=
ssGetT ( S ) ) ) { _rtB -> B_35_498_0 = 0.0 ; } else { rtb_B_35_26_0 = _rtDW
-> TimeStampA_n ; lastU = & _rtDW -> LastUAtTimeA_ma ; if ( _rtDW ->
TimeStampA_n < _rtDW -> TimeStampB_m ) { if ( _rtDW -> TimeStampB_m < ssGetT
( S ) ) { rtb_B_35_26_0 = _rtDW -> TimeStampB_m ; lastU = & _rtDW ->
LastUAtTimeB_g ; } } else { if ( _rtDW -> TimeStampA_n >= ssGetT ( S ) ) {
rtb_B_35_26_0 = _rtDW -> TimeStampB_m ; lastU = & _rtDW -> LastUAtTimeB_g ; }
} _rtB -> B_35_498_0 = ( _rtB -> B_35_496_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_35_26_0 ) ; } _rtB -> B_35_513_0 = ( muDoubleScalarSin ( _rtP -> P_513
* ssGetTaskTime ( S , 0 ) + _rtP -> P_514 ) * _rtP -> P_511 + _rtP -> P_512 )
* _rtB -> B_35_385_0 ; _rtB -> B_35_515_0 = ( muDoubleScalarSin ( _rtP ->
P_517 * ssGetTaskTime ( S , 0 ) + _rtP -> P_518 ) * _rtP -> P_515 + _rtP ->
P_516 ) * _rtB -> B_35_385_0 ; _rtB -> B_35_517_0 = ( muDoubleScalarSin (
_rtP -> P_521 * ssGetTaskTime ( S , 0 ) + _rtP -> P_522 ) * _rtP -> P_519 +
_rtP -> P_520 ) * _rtB -> B_35_337_0 ; _rtB -> B_35_519_0 = (
muDoubleScalarSin ( _rtP -> P_525 * ssGetTaskTime ( S , 0 ) + _rtP -> P_526 )
* _rtP -> P_523 + _rtP -> P_524 ) * _rtB -> B_35_337_0 ; ssCallAccelRunBlock
( S , 35 , 520 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 521 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_525_0 = _rtP -> P_527 * _rtB ->
B_35_124_0 [ 10 ] ; ssCallAccelRunBlock ( S , 35 , 526 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_35_528_0 = _rtB -> B_35_60_0 - _rtP -> P_528 * _rtB ->
B_35_525_0 ; ssCallAccelRunBlock ( S , 35 , 529 , SS_CALL_MDL_OUTPUTS ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_35_530_0
= _rtP -> P_529 * _rtB -> B_35_9_0 ; } _rtB -> B_35_531_0 = ( 1.0 - _rtB ->
B_35_25_0 / _rtB -> B_35_530_0 ) * 100.0 ; if ( ssIsMajorTimeStep ( S ) != 0
) { _rtDW -> Saturation_MODE_f = _rtB -> B_35_531_0 >= _rtP -> P_530 ? 1 :
_rtB -> B_35_531_0 > _rtP -> P_531 ? 0 : - 1 ; } _rtB -> B_35_532_0 = _rtDW
-> Saturation_MODE_f == 1 ? _rtP -> P_530 : _rtDW -> Saturation_MODE_f == - 1
? _rtP -> P_531 : _rtB -> B_35_531_0 ; ssCallAccelRunBlock ( S , 35 , 533 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 10 , 0 ) ; if ( isHit !=
0 ) { rtb_B_35_26_0 = ssGetTaskTime ( S , 10 ) ; if ( ssGetTNextWasAdjusted (
S , 10 ) != 0 ) { _rtDW -> nextTime_i = _ssGetVarNextHitTime ( S , 5 ) ; } if
( _rtDW -> justEnabled_m != 0 ) { _rtDW -> justEnabled_m = 0 ; if (
rtb_B_35_26_0 >= _rtP -> P_535 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP ->
P_535 ) / _rtP -> P_533 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_B_35_27_0 ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_B_35_27_0 ) < DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW ->
numCompleteCycles_f = numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles *
_rtP -> P_533 + _rtP -> P_535 ) + _rtP -> P_534 * _rtP -> P_533 / 100.0 ; if
( rtb_B_35_26_0 < rtb_B_35_27_0 ) { _rtDW -> currentValue_h = 1 ; _rtDW ->
nextTime_i = rtb_B_35_27_0 ; } else { _rtDW -> currentValue_h = 0 ; _rtDW ->
nextTime_i = ( real_T ) ( numCycles + 1U ) * _rtP -> P_533 + _rtP -> P_535 ;
} } else { _rtDW -> numCompleteCycles_f = _rtP -> P_535 != 0.0 ? - 1 : 0 ;
_rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = _rtP -> P_535 ; } } else
{ if ( _rtDW -> nextTime_i <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue_h
== 1 ) { _rtDW -> currentValue_h = 0 ; _rtDW -> nextTime_i = ( real_T ) (
_rtDW -> numCompleteCycles_f + 1LL ) * _rtP -> P_533 + _rtP -> P_535 ; } else
{ _rtDW -> numCompleteCycles_f ++ ; _rtDW -> currentValue_h = 1 ; _rtDW ->
nextTime_i = ( _rtP -> P_534 * _rtP -> P_533 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_f * _rtP -> P_533 ) + _rtP -> P_535 ; } } }
_ssSetVarNextHitTime ( S , 5 , _rtDW -> nextTime_i ) ; if ( _rtDW ->
currentValue_h == 1 ) { _rtB -> B_35_534_0 = _rtP -> P_532 ; } else { _rtB ->
B_35_534_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit !=
0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE , _rtB -> B_35_534_0 )
; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 34 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC = 4 ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Abs_MODE = ( _rtB -> B_35_525_0 >=
0.0 ) ; } _rtB -> B_35_548_0 = _rtDW -> Abs_MODE > 0 ? _rtB -> B_35_525_0 : -
_rtB -> B_35_525_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_i = ( _rtB ->
B_35_525_0 < uGrid_1PH_hd_rtC ( S ) -> B_35_549_0 ) ; } _rtB -> B_35_552_0 =
_rtP -> P_542 * ( real_T ) _rtDW -> Compare_Mode_i ; } _rtB -> B_35_553_0 =
_rtB -> B_35_552_0 - _rtB -> B_35_48_0 ; _rtB -> B_35_554_0 = _rtB ->
B_35_548_0 * _rtB -> B_35_553_0 ; _rtB -> B_35_555_0 = _rtP -> P_543 * _rtB
-> B_35_554_0 ; _rtB -> B_35_556_0 = _rtP -> P_544 * _rtB -> B_35_25_0 ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , &
_rtZCE -> Subsystem_Trig_ZCE_h , _rtB -> B_35_125_0 [ 11 ] ) ; if ( zcEvent
!= NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 28 , 0 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Subsystem_SubsysRanBC_k = 4 ; } } ssCallAccelRunBlock ( S , 16 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent =
rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_d4 , _rtB ->
B_35_125_0 [ 5 ] ) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S ,
25 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_l = 4 ; } }
_rtB -> B_35_563_0 = _rtP -> P_545 * _rtB -> B_25_0_0 [ 1 ] ;
ssCallAccelRunBlock ( S , 18 , 0 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 567 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 568 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { ssCallAccelRunBlock ( S , 35 , 569 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 35 , 570 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 574 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 575 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 7 , 0 ) ; if ( isHit !=
0 ) { rtb_B_35_26_0 = ssGetTaskTime ( S , 7 ) ; if ( ssGetTNextWasAdjusted (
S , 7 ) != 0 ) { _rtDW -> nextTime_j = _ssGetVarNextHitTime ( S , 2 ) ; } if
( _rtDW -> justEnabled_j != 0 ) { _rtDW -> justEnabled_j = 0 ; if (
rtb_B_35_26_0 >= _rtP -> P_553 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP ->
P_553 ) / _rtP -> P_551 ; numCycles = ( uint32_T ) muDoubleScalarFloor (
rtb_B_35_27_0 ) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) -
rtb_B_35_27_0 ) < DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW ->
numCompleteCycles_h = numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles *
_rtP -> P_551 + _rtP -> P_553 ) + _rtP -> P_552 * _rtP -> P_551 / 100.0 ; if
( rtb_B_35_26_0 < rtb_B_35_27_0 ) { _rtDW -> currentValue_n = 1 ; _rtDW ->
nextTime_j = rtb_B_35_27_0 ; } else { _rtDW -> currentValue_n = 0 ; _rtDW ->
nextTime_j = ( real_T ) ( numCycles + 1U ) * _rtP -> P_551 + _rtP -> P_553 ;
} } else { _rtDW -> numCompleteCycles_h = _rtP -> P_553 != 0.0 ? - 1 : 0 ;
_rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = _rtP -> P_553 ; } } else
{ if ( _rtDW -> nextTime_j <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue_n
== 1 ) { _rtDW -> currentValue_n = 0 ; _rtDW -> nextTime_j = ( real_T ) (
_rtDW -> numCompleteCycles_h + 1LL ) * _rtP -> P_551 + _rtP -> P_553 ; } else
{ _rtDW -> numCompleteCycles_h ++ ; _rtDW -> currentValue_n = 1 ; _rtDW ->
nextTime_j = ( _rtP -> P_552 * _rtP -> P_551 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_h * _rtP -> P_551 ) + _rtP -> P_553 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime_j ) ; if ( _rtDW ->
currentValue_n == 1 ) { _rtB -> B_35_576_0 = _rtP -> P_550 ; } else { _rtB ->
B_35_576_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit !=
0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_o , _rtB -> B_35_576_0
) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 31 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_b = 4 ; } } isHit =
ssIsSampleHit ( S , 9 , 0 ) ; if ( isHit != 0 ) { rtb_B_35_26_0 =
ssGetTaskTime ( S , 9 ) ; if ( ssGetTNextWasAdjusted ( S , 9 ) != 0 ) { _rtDW
-> nextTime_l = _ssGetVarNextHitTime ( S , 4 ) ; } if ( _rtDW ->
justEnabled_o != 0 ) { _rtDW -> justEnabled_o = 0 ; if ( rtb_B_35_26_0 >=
_rtP -> P_561 ) { rtb_B_35_27_0 = ( rtb_B_35_26_0 - _rtP -> P_561 ) / _rtP ->
P_559 ; numCycles = ( uint32_T ) muDoubleScalarFloor ( rtb_B_35_27_0 ) ; if (
muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - rtb_B_35_27_0 ) <
DBL_EPSILON * rtb_B_35_27_0 ) { numCycles ++ ; } _rtDW ->
numCompleteCycles_hh = numCycles ; rtb_B_35_27_0 = ( ( real_T ) numCycles *
_rtP -> P_559 + _rtP -> P_561 ) + _rtP -> P_560 * _rtP -> P_559 / 100.0 ; if
( rtb_B_35_26_0 < rtb_B_35_27_0 ) { _rtDW -> currentValue_f = 1 ; _rtDW ->
nextTime_l = rtb_B_35_27_0 ; } else { _rtDW -> currentValue_f = 0 ; _rtDW ->
nextTime_l = ( real_T ) ( numCycles + 1U ) * _rtP -> P_559 + _rtP -> P_561 ;
} } else { _rtDW -> numCompleteCycles_hh = _rtP -> P_561 != 0.0 ? - 1 : 0 ;
_rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = _rtP -> P_561 ; } } else
{ if ( _rtDW -> nextTime_l <= rtb_B_35_26_0 ) { if ( _rtDW -> currentValue_f
== 1 ) { _rtDW -> currentValue_f = 0 ; _rtDW -> nextTime_l = ( real_T ) (
_rtDW -> numCompleteCycles_hh + 1LL ) * _rtP -> P_559 + _rtP -> P_561 ; }
else { _rtDW -> numCompleteCycles_hh ++ ; _rtDW -> currentValue_f = 1 ; _rtDW
-> nextTime_l = ( _rtP -> P_560 * _rtP -> P_559 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_hh * _rtP -> P_559 ) + _rtP -> P_561 ; } } }
_ssSetVarNextHitTime ( S , 4 , _rtDW -> nextTime_l ) ; if ( _rtDW ->
currentValue_f == 1 ) { _rtB -> B_35_583_0 = _rtP -> P_558 ; } else { _rtB ->
B_35_583_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit !=
0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { zcEvent = rt_ZCFcn (
FALLING_ZERO_CROSSING , & _rtZCE -> Subsystem_Trig_ZCE_f , _rtB -> B_35_583_0
) ; if ( zcEvent != NO_ZCEVENT ) { ssCallAccelRunBlock ( S , 33 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Subsystem_SubsysRanBC_g = 4 ; } } isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
35 , 590 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 35 , 591 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 35 , 592 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_35_598_0 = 0.0 ; _rtB -> B_35_598_0 += _rtP
-> P_569 * _rtX -> Actuador1_CSTATE ; _rtB -> B_35_599_0 = _rtP -> P_570 *
_rtB -> B_35_598_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_571 ; _rtB
-> B_35_600_0 = uGrid_1PH_hd_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> MotordeCombustin1_IWORK . CircularBufSize , &
_rtDW -> MotordeCombustin1_IWORK . Last , _rtDW -> MotordeCombustin1_IWORK .
Tail , _rtDW -> MotordeCombustin1_IWORK . Head , _rtP -> P_572 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_35_601_0 = _rtB -> B_35_600_0 - _rtB ->
B_35_596_0 ; _rtB -> B_35_602_0 = _rtP -> P_573 * _rtB -> B_35_124_0 [ 4 ] ;
_rtB -> B_35_606_0 = _rtB -> B_35_597_0 - _rtB -> B_35_6_0 ; _rtB ->
B_35_607_0 = _rtP -> P_574 * _rtB -> B_35_606_0 ; _rtB -> B_35_608_0 = _rtX
-> Filter_CSTATE ; _rtB -> B_35_609_0 = _rtB -> B_35_607_0 - _rtB ->
B_35_608_0 ; _rtB -> B_35_610_0 = _rtP -> P_576 * _rtB -> B_35_609_0 ; _rtB
-> B_35_611_0 = _rtP -> P_577 * _rtB -> B_35_606_0 ; _rtB -> B_35_612_0 =
_rtX -> Integrator_CSTATE ; _rtB -> B_35_613_0 = _rtP -> P_579 * _rtB ->
B_35_606_0 ; _rtB -> B_35_614_0 = ( _rtB -> B_35_613_0 + _rtB -> B_35_612_0 )
+ _rtB -> B_35_610_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 35 , 618 , SS_CALL_MDL_OUTPUTS ) ; }
UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID11 ( SimStruct * S ,
int_T tid ) { real_T rtb_B_35_68_0 ; real_T rtb_B_35_106_0 ; B_uGrid_1PH_hd_T
* _rtB ; P_uGrid_1PH_hd_T * _rtP ; _rtP = ( ( P_uGrid_1PH_hd_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO (
S ) ) ; _rtB -> B_35_0_0 = _rtP -> P_142 ; _rtB -> B_35_7_0 = _rtP -> P_150 ;
_rtB -> B_35_8_0 = _rtP -> P_151 ; _rtB -> B_35_20_0 = _rtP -> P_161 ; _rtB
-> B_35_28_0 = _rtP -> P_162 ; _rtB -> B_35_29_0 = _rtP -> P_163 ; _rtB ->
B_35_39_0 = _rtP -> P_166 ; _rtB -> B_35_40_0 = _rtP -> P_167 ; _rtB ->
B_35_41_0 = _rtP -> P_168 ; _rtB -> B_35_47_0 = _rtP -> P_169 ; rtb_B_35_68_0
= _rtP -> P_180 + _rtP -> P_181 ; _rtB -> B_35_74_0 = _rtP -> P_183 ; _rtB ->
B_35_75_0 = ( ( rtb_B_35_68_0 - _rtP -> P_182 ) * _rtP -> P_179 + _rtP ->
P_178 ) * ( _rtP -> P_176 / _rtP -> P_177 ) * _rtB -> B_35_74_0 ; _rtB ->
B_35_76_0 = _rtP -> P_184 ; _rtB -> B_35_77_0 = _rtP -> P_185 ; _rtB ->
B_35_78_0 = _rtP -> P_186 ; _rtB -> B_35_79_0 = 0.0 / _rtB -> B_35_78_0 ;
_rtB -> B_35_84_0 = _rtP -> P_188 * rtb_B_35_68_0 / _rtP -> P_189 * _rtP ->
P_187 ; _rtB -> B_35_85_0 = _rtP -> P_190 ; rtb_B_35_106_0 = rtb_B_35_68_0 /
_rtP -> P_182 ; _rtB -> B_35_109_0 = _rtP -> P_178 / ( muDoubleScalarExp (
_rtP -> P_194 * _rtP -> P_189 / ( _rtP -> P_188 * _rtP -> P_195 *
rtb_B_35_68_0 * _rtP -> P_187 ) ) - _rtP -> P_196 ) * ( rtb_B_35_106_0 *
rtb_B_35_106_0 * rtb_B_35_106_0 ) * muDoubleScalarExp ( ( _rtP -> P_192 /
rtb_B_35_68_0 - _rtP -> P_191 / _rtP -> P_182 ) * ( _rtP -> P_189 * _rtP ->
P_193 / ( _rtP -> P_188 * _rtP -> P_187 ) ) ) ; _rtB -> B_35_112_0 = _rtP ->
P_198 ; _rtB -> B_35_113_0 = _rtP -> P_199 ; _rtB -> B_35_114_0 = _rtP ->
P_200 ; _rtB -> B_35_115_0 = _rtP -> P_201 ; _rtB -> B_35_116_0 = _rtP ->
P_202 ; _rtB -> B_35_117_0 = _rtP -> P_203 ; _rtB -> B_35_118_0 = _rtP ->
P_204 ; _rtB -> B_35_119_0 = _rtP -> P_205 ; _rtB -> B_35_120_0 = _rtP ->
P_206 ; _rtB -> B_35_121_0 = _rtP -> P_207 ; _rtB -> B_35_122_0 = _rtP ->
P_208 ; _rtB -> B_35_123_0 = _rtP -> P_209 ; _rtB -> B_35_169_0 = _rtP ->
P_324 ; _rtB -> B_35_173_0 = _rtP -> P_325 ; _rtB -> B_35_177_0 = _rtP ->
P_326 ; _rtB -> B_35_181_0 = _rtP -> P_327 ; _rtB -> B_35_189_0 = _rtP ->
P_328 ; _rtB -> B_35_210_0 = _rtP -> P_340 ; _rtB -> B_35_248_0 = _rtP ->
P_354 ; _rtB -> B_35_252_0 = _rtP -> P_355 ; _rtB -> B_35_256_0 = _rtP ->
P_356 ; _rtB -> B_35_260_0 = _rtP -> P_357 ; _rtB -> B_35_268_0 = _rtP ->
P_358 ; _rtB -> B_35_290_0 = _rtP -> P_384 ; _rtB -> B_35_321_0 = _rtP ->
P_396 ; memcpy ( & _rtB -> B_35_312_0 [ 0 ] , & _rtP -> P_394 [ 0 ] , 40000U
* sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_35_313_0 [ 0 ] , & _rtP -> P_395
[ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_35_326_0 [ 0 ] ,
& _rtP -> P_397 [ 0 ] , 40000U * sizeof ( real_T ) ) ; memcpy ( & _rtB ->
B_35_327_0 [ 0 ] , & _rtP -> P_398 [ 0 ] , 40000U * sizeof ( real_T ) ) ;
_rtB -> B_35_335_0 = _rtP -> P_401 ; _rtB -> B_35_387_0 = _rtP -> P_432 ;
_rtB -> B_35_399_0 = _rtP -> P_449 ; _rtB -> B_35_406_0 = _rtP -> P_458 ;
_rtB -> B_35_407_0 = _rtP -> P_459 ; _rtB -> B_35_408_0 = _rtP -> P_460 ;
_rtB -> B_35_409_0 = _rtP -> P_461 ; _rtB -> B_35_413_0 = _rtP -> P_466 ;
_rtB -> B_35_414_0 = _rtP -> P_467 ; _rtB -> B_35_415_0 = _rtP -> P_468 ;
_rtB -> B_35_416_0 = _rtP -> P_469 ; _rtB -> B_35_420_0 = _rtP -> P_474 ;
_rtB -> B_35_421_0 = _rtP -> P_475 ; _rtB -> B_35_422_0 = _rtP -> P_476 ;
_rtB -> B_35_423_0 = _rtP -> P_477 ; _rtB -> B_35_452_0 = _rtP -> P_487 ;
_rtB -> B_35_456_0 = _rtP -> P_488 ; _rtB -> B_35_460_0 = _rtP -> P_489 ;
_rtB -> B_35_464_0 = _rtP -> P_490 ; _rtB -> B_35_472_0 = _rtP -> P_491 ;
_rtB -> B_35_493_0 = _rtP -> P_503 ; _rtB -> B_35_536_0 = _rtP -> P_536 ;
_rtB -> B_35_537_0 = _rtP -> P_537 ; _rtB -> B_35_538_0 = _rtP -> P_538 ;
_rtB -> B_35_539_0 = _rtP -> P_539 ; _rtB -> B_35_547_0 = _rtP -> P_540 ;
_rtB -> B_35_564_0 [ 0 ] = _rtP -> P_546 [ 0 ] ; _rtB -> B_35_565_0 [ 0 ] =
_rtP -> P_547 [ 0 ] ; _rtB -> B_35_571_0 [ 0 ] = _rtP -> P_548 [ 0 ] ; _rtB
-> B_35_572_0 [ 0 ] = _rtP -> P_549 [ 0 ] ; _rtB -> B_35_564_0 [ 1 ] = _rtP
-> P_546 [ 1 ] ; _rtB -> B_35_565_0 [ 1 ] = _rtP -> P_547 [ 1 ] ; _rtB ->
B_35_571_0 [ 1 ] = _rtP -> P_548 [ 1 ] ; _rtB -> B_35_572_0 [ 1 ] = _rtP ->
P_549 [ 1 ] ; _rtB -> B_35_578_0 = _rtP -> P_554 ; _rtB -> B_35_579_0 = _rtP
-> P_555 ; _rtB -> B_35_580_0 = _rtP -> P_556 ; _rtB -> B_35_581_0 = _rtP ->
P_557 ; _rtB -> B_35_585_0 = _rtP -> P_562 ; _rtB -> B_35_586_0 = _rtP ->
P_563 ; _rtB -> B_35_587_0 = _rtP -> P_564 ; _rtB -> B_35_588_0 = _rtP ->
P_565 ; _rtB -> B_35_596_0 = _rtP -> P_566 ; _rtB -> B_35_597_0 = _rtP ->
P_567 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ;
X_uGrid_1PH_hd_T * _rtX ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( ( X_uGrid_1PH_hd_T *
) ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_35_547_0 ; _rtDW -> itinit_PreviousInput =
_rtB -> B_35_556_0 ; } _rtDW -> inti_IWORK = 0 ; if ( _rtX -> inti_CSTATE ==
_rtP -> P_158 ) { switch ( _rtDW -> inti_MODE ) { case 3 : if ( _rtB ->
B_35_525_0 < 0.0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW
-> inti_MODE = 1 ; } break ; case 1 : if ( _rtB -> B_35_525_0 >= 0.0 ) {
_rtDW -> inti_MODE = 3 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; default : ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; if (
_rtB -> B_35_525_0 < 0.0 ) { _rtDW -> inti_MODE = 1 ; } else { _rtDW ->
inti_MODE = 3 ; } break ; } } else if ( _rtX -> inti_CSTATE == _rtP -> P_159
) { switch ( _rtDW -> inti_MODE ) { case 4 : if ( _rtB -> B_35_525_0 > 0.0 )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW -> inti_MODE = 2 ;
} break ; case 2 : if ( _rtB -> B_35_525_0 <= 0.0 ) { _rtDW -> inti_MODE = 4
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; default :
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; if ( _rtB -> B_35_525_0 >
0.0 ) { _rtDW -> inti_MODE = 2 ; } else { _rtDW -> inti_MODE = 4 ; } break ;
} } else { _rtDW -> inti_MODE = 0 ; } ssCallAccelRunBlock ( S , 35 , 124 ,
SS_CALL_MDL_UPDATE ) ; if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW ->
TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if (
_rtDW -> TimeStampB == ( rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ;
lastU = & _rtDW -> LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW ->
TimeStampB ) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA ; } else { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW
-> LastUAtTimeB ; } * lastU = _rtB -> B_35_213_0 ; if ( _rtDW -> TimeStampA_k
== ( rtInf ) ) { _rtDW -> TimeStampA_k = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA_m ; } else if ( _rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW ->
TimeStampB_f = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_o ; } else if (
_rtDW -> TimeStampA_k < _rtDW -> TimeStampB_f ) { _rtDW -> TimeStampA_k =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_m ; } else { _rtDW ->
TimeStampB_f = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_o ; } * lastU =
_rtB -> B_35_293_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ _rtDW -> Memory2_PreviousInput [ 0 ] = _rtB -> B_13_0_1 [ 0 ] ; _rtDW ->
Memory2_PreviousInput [ 1 ] = _rtB -> B_13_0_1 [ 1 ] ; memcpy ( & _rtDW ->
Memory1_PreviousInput [ 0 ] , & _rtB -> B_13_0_2 [ 0 ] , 200U * sizeof (
real_T ) ) ; memcpy ( & _rtDW -> Memory3_PreviousInput [ 0 ] , & _rtB ->
B_15_0_2 [ 0 ] , 200U * sizeof ( real_T ) ) ; _rtDW -> Memory4_PreviousInput
[ 0 ] = _rtB -> B_15_0_1 [ 0 ] ; _rtDW -> Memory4_PreviousInput [ 1 ] = _rtB
-> B_15_0_1 [ 1 ] ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_408 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_35_339_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> Memory_PreviousInput = _rtB -> B_35_346_0 ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_h . Head = ( ( _rtDW -> TransportDelay_IWORK_h . Head <
( _rtDW -> TransportDelay_IWORK_h . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_h . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_h . Head == _rtDW -> TransportDelay_IWORK_h . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_h . CircularBufSize , & _rtDW -> TransportDelay_IWORK_h
. Tail , & _rtDW -> TransportDelay_IWORK_h . Head , & _rtDW ->
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_413 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_35_347_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> Memory_PreviousInput_f = _rtB -> B_35_354_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_d .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_j . Head = ( ( _rtDW -> TransportDelay_IWORK_j . Head <
( _rtDW -> TransportDelay_IWORK_j . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_j . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_j . Head == _rtDW -> TransportDelay_IWORK_j . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_j . CircularBufSize , & _rtDW -> TransportDelay_IWORK_j
. Tail , & _rtDW -> TransportDelay_IWORK_j . Head , & _rtDW ->
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_418 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_35_357_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> Memory_PreviousInput_p = _rtB -> B_35_364_0 ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_i .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_a . Head = ( ( _rtDW -> TransportDelay_IWORK_a . Head <
( _rtDW -> TransportDelay_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_a . Head == _rtDW -> TransportDelay_IWORK_a . Tail ) {
if ( ! uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_a . CircularBufSize , & _rtDW -> TransportDelay_IWORK_a
. Tail , & _rtDW -> TransportDelay_IWORK_a . Head , & _rtDW ->
TransportDelay_IWORK_a . Last , simTime - _rtP -> P_423 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_a . Head ] = _rtB ->
B_35_365_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtDW -> Memory_PreviousInput_k = _rtB -> B_35_372_0 ; } if ( _rtDW ->
TimeStampA_b == ( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU =
& _rtDW -> LastUAtTimeA_f ; } else if ( _rtDW -> TimeStampB_a == ( rtInf ) )
{ _rtDW -> TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ;
} else if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_a ) { _rtDW ->
TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; } else {
_rtDW -> TimeStampB_a = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_n ; }
* lastU = _rtB -> B_35_388_0 ; if ( _rtDW -> TimeStampA_n == ( rtInf ) ) {
_rtDW -> TimeStampA_n = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_ma ; }
else if ( _rtDW -> TimeStampB_m == ( rtInf ) ) { _rtDW -> TimeStampB_m =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_g ; } else if ( _rtDW ->
TimeStampA_n < _rtDW -> TimeStampB_m ) { _rtDW -> TimeStampA_n = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_ma ; } else { _rtDW -> TimeStampB_m =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_g ; } * lastU = _rtB ->
B_35_496_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
MotordeCombustin1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> MotordeCombustin1_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> MotordeCombustin1_IWORK . Head = ( ( _rtDW
-> MotordeCombustin1_IWORK . Head < ( _rtDW -> MotordeCombustin1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> MotordeCombustin1_IWORK . Head + 1 ) : 0
) ; if ( _rtDW -> MotordeCombustin1_IWORK . Head == _rtDW ->
MotordeCombustin1_IWORK . Tail ) { if ( !
uGrid_1PH_hd_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
MotordeCombustin1_IWORK . CircularBufSize , & _rtDW ->
MotordeCombustin1_IWORK . Tail , & _rtDW -> MotordeCombustin1_IWORK . Head ,
& _rtDW -> MotordeCombustin1_IWORK . Last , simTime - _rtP -> P_571 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
MotordeCombustin1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
MotordeCombustin1_IWORK . Head ] = _rtB -> B_35_599_0 ; } UNUSED_PARAMETER (
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
_rtB -> B_35_601_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_147 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_35_602_0 ; _rtXdot -> Currentfilter_CSTATE =
0.0 ; _rtXdot -> Currentfilter_CSTATE += _rtP -> P_154 * _rtX ->
Currentfilter_CSTATE ; _rtXdot -> Currentfilter_CSTATE += _rtB -> B_35_525_0
; if ( ( _rtDW -> inti_MODE != 3 ) && ( _rtDW -> inti_MODE != 4 ) ) { _rtXdot
-> inti_CSTATE = _rtB -> B_35_525_0 ; _rtXdis -> inti_CSTATE = false ; } else
{ _rtXdot -> inti_CSTATE = 0.0 ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW
-> inti_MODE == 4 ) ) { _rtXdis -> inti_CSTATE = true ; } } _rtXdot ->
Integrator2_CSTATE = _rtB -> B_35_555_0 ; _rtXdot -> BAL_CSTATE = 0.0 ;
_rtXdot -> BAL_CSTATE += _rtP -> P_173 * _rtX -> BAL_CSTATE ; _rtXdot ->
BAL_CSTATE += _rtB -> B_35_525_0 ; ssCallAccelRunBlock ( S , 35 , 124 ,
SS_CALL_MDL_DERIVATIVES ) ; _rtXdot -> Hw2_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 0 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 2 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 2 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw1_CSTATE [ 3 ] = 0.0 ; _rtXdot ->
Hw3_CSTATE [ 3 ] = 0.0 ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_272 [ 0 ] *
_rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] += _rtP -> P_272 [ 1 ]
* _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 1 ] += _rtP -> P_272 [ 2
] * _rtX -> Hw2_CSTATE [ 0 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_272 [
3 ] * _rtX -> Hw2_CSTATE [ 1 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP -> P_272
[ 4 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 2 ] += _rtP ->
P_272 [ 5 ] * _rtX -> Hw2_CSTATE [ 3 ] ; _rtXdot -> Hw2_CSTATE [ 3 ] += _rtP
-> P_272 [ 6 ] * _rtX -> Hw2_CSTATE [ 2 ] ; _rtXdot -> Hw2_CSTATE [ 0 ] +=
_rtP -> P_273 * _rtB -> B_35_145_0 [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 0 ] +=
_rtP -> P_276 [ 0 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [ 0 ]
+= _rtP -> P_276 [ 1 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE [ 1
] += _rtP -> P_276 [ 2 ] * _rtX -> Hw6_CSTATE [ 0 ] ; _rtXdot -> Hw6_CSTATE [
2 ] += _rtP -> P_276 [ 3 ] * _rtX -> Hw6_CSTATE [ 1 ] ; _rtXdot -> Hw6_CSTATE
[ 2 ] += _rtP -> P_276 [ 4 ] * _rtX -> Hw6_CSTATE [ 2 ] ; _rtXdot ->
Hw6_CSTATE [ 2 ] += _rtP -> P_276 [ 5 ] * _rtX -> Hw6_CSTATE [ 3 ] ; _rtXdot
-> Hw6_CSTATE [ 3 ] += _rtP -> P_276 [ 6 ] * _rtX -> Hw6_CSTATE [ 2 ] ;
_rtXdot -> Hw6_CSTATE [ 0 ] += _rtP -> P_277 * _rtB -> B_35_145_0 [ 2 ] ;
_rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_280 [ 0 ] * _rtX -> Hw1_CSTATE [ 0 ]
; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_280 [ 1 ] * _rtX -> Hw1_CSTATE [ 1
] ; _rtXdot -> Hw1_CSTATE [ 1 ] += _rtP -> P_280 [ 2 ] * _rtX -> Hw1_CSTATE [
0 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_280 [ 3 ] * _rtX -> Hw1_CSTATE
[ 1 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_280 [ 4 ] * _rtX ->
Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 2 ] += _rtP -> P_280 [ 5 ] * _rtX
-> Hw1_CSTATE [ 3 ] ; _rtXdot -> Hw1_CSTATE [ 3 ] += _rtP -> P_280 [ 6 ] *
_rtX -> Hw1_CSTATE [ 2 ] ; _rtXdot -> Hw1_CSTATE [ 0 ] += _rtP -> P_281 *
_rtB -> B_35_269_0 [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_284 [ 0 ]
* _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 0 ] += _rtP -> P_284 [ 1
] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 1 ] += _rtP -> P_284 [
2 ] * _rtX -> Hw3_CSTATE [ 0 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP -> P_284
[ 3 ] * _rtX -> Hw3_CSTATE [ 1 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP ->
P_284 [ 4 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 2 ] += _rtP
-> P_284 [ 5 ] * _rtX -> Hw3_CSTATE [ 3 ] ; _rtXdot -> Hw3_CSTATE [ 3 ] +=
_rtP -> P_284 [ 6 ] * _rtX -> Hw3_CSTATE [ 2 ] ; _rtXdot -> Hw3_CSTATE [ 0 ]
+= _rtP -> P_285 * _rtB -> B_35_269_0 [ 2 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] =
0.0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 0 ] = 0.0
; _rtXdot -> Hw3_CSTATE_e [ 0 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw1_CSTATE_k [ 1 ] = 0.0 ; _rtXdot -> Hw7_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> Hw3_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP ->
P_288 [ 0 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ] += _rtP
-> P_288 [ 1 ] * _rtX -> Hw4_CSTATE [ 1 ] ; _rtXdot -> Hw4_CSTATE [ 1 ] +=
_rtP -> P_288 [ 2 ] * _rtX -> Hw4_CSTATE [ 0 ] ; _rtXdot -> Hw4_CSTATE [ 0 ]
+= _rtP -> P_289 * _rtB -> B_35_152_0 ; _rtXdot -> Hw1_CSTATE_k [ 0 ] += _rtP
-> P_292 [ 0 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot -> Hw1_CSTATE_k [ 0 ]
+= _rtP -> P_292 [ 1 ] * _rtX -> Hw1_CSTATE_k [ 1 ] ; _rtXdot -> Hw1_CSTATE_k
[ 1 ] += _rtP -> P_292 [ 2 ] * _rtX -> Hw1_CSTATE_k [ 0 ] ; _rtXdot ->
Hw1_CSTATE_k [ 0 ] += _rtP -> P_293 * _rtB -> B_35_151_0 ; _rtXdot ->
Hw7_CSTATE [ 0 ] += _rtP -> P_296 [ 0 ] * _rtX -> Hw7_CSTATE [ 0 ] ; _rtXdot
-> Hw7_CSTATE [ 0 ] += _rtP -> P_296 [ 1 ] * _rtX -> Hw7_CSTATE [ 1 ] ;
_rtXdot -> Hw7_CSTATE [ 1 ] += _rtP -> P_296 [ 2 ] * _rtX -> Hw7_CSTATE [ 0 ]
; _rtXdot -> Hw7_CSTATE [ 0 ] += _rtP -> P_297 * _rtB -> B_35_230_0 ; _rtXdot
-> Hw3_CSTATE_e [ 0 ] += _rtP -> P_300 [ 0 ] * _rtX -> Hw3_CSTATE_e [ 0 ] ;
_rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_300 [ 1 ] * _rtX -> Hw3_CSTATE_e [
1 ] ; _rtXdot -> Hw3_CSTATE_e [ 1 ] += _rtP -> P_300 [ 2 ] * _rtX ->
Hw3_CSTATE_e [ 0 ] ; _rtXdot -> Hw3_CSTATE_e [ 0 ] += _rtP -> P_301 * _rtB ->
B_35_231_0 ; _rtXdot -> TransferFcn_CSTATE_j = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_j += _rtP -> P_319 * _rtX -> TransferFcn_CSTATE_j ;
_rtXdot -> TransferFcn_CSTATE_j += _rtB -> B_35_147_0 ; _rtXdot ->
TransferFcn1_CSTATE = 0.0 ; _rtXdot -> TransferFcn1_CSTATE += _rtP -> P_321 *
_rtX -> TransferFcn1_CSTATE ; _rtXdot -> TransferFcn1_CSTATE += _rtB ->
B_35_153_0 ; _rtXdot -> TransferFcn_CSTATE_g = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_g += _rtP -> P_349 * _rtX -> TransferFcn_CSTATE_g ;
_rtXdot -> TransferFcn_CSTATE_g += _rtB -> B_35_226_0 ; _rtXdot ->
TransferFcn1_CSTATE_p = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_p += _rtP ->
P_351 * _rtX -> TransferFcn1_CSTATE_p ; _rtXdot -> TransferFcn1_CSTATE_p +=
_rtB -> B_35_232_0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] = 0.0 ; _rtXdot ->
Hw2_CSTATE_p [ 1 ] = 0.0 ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP -> P_402 [ 0
] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [ 0 ] += _rtP ->
P_402 [ 1 ] * _rtX -> Hw2_CSTATE_p [ 1 ] ; _rtXdot -> Hw2_CSTATE_p [ 1 ] +=
_rtP -> P_402 [ 2 ] * _rtX -> Hw2_CSTATE_p [ 0 ] ; _rtXdot -> Hw2_CSTATE_p [
0 ] += _rtP -> P_403 * _rtB -> B_35_429_0 ; _rtXdot -> integrator_CSTATE =
_rtB -> B_35_513_0 ; _rtXdot -> integrator_CSTATE_i = _rtB -> B_35_515_0 ;
_rtXdot -> integrator_CSTATE_p = _rtB -> B_35_517_0 ; _rtXdot ->
integrator_CSTATE_l = _rtB -> B_35_519_0 ; _rtXdot -> Hi_Pass1_CSTATE = 0.0 ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_437 * _rtX -> Hi_Pass1_CSTATE ;
_rtXdot -> Hi_Pass1_CSTATE += _rtP -> P_438 * _rtB -> B_35_391_0 ; _rtXdot ->
Hw5_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] = 0.0 ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtP -> P_447 [ 0 ] * _rtX ->
TransferFcn1_CSTATE_e [ 0 ] ; _rtXdot -> Hw5_CSTATE [ 1 ] = 0.0 ; _rtXdot ->
TransferFcn1_CSTATE_e [ 1 ] = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_e [ 0 ] +=
_rtP -> P_447 [ 1 ] * _rtX -> TransferFcn1_CSTATE_e [ 1 ] ; _rtXdot ->
Hw5_CSTATE [ 0 ] += _rtP -> P_442 [ 0 ] * _rtX -> Hw5_CSTATE [ 0 ] ; _rtXdot
-> Hw5_CSTATE [ 0 ] += _rtP -> P_442 [ 1 ] * _rtX -> Hw5_CSTATE [ 1 ] ;
_rtXdot -> Hw5_CSTATE [ 1 ] += _rtP -> P_442 [ 2 ] * _rtX -> Hw5_CSTATE [ 0 ]
; _rtXdot -> Hw5_CSTATE [ 0 ] += _rtP -> P_443 * _rtB -> B_35_439_0 ; _rtXdot
-> TransferFcn1_CSTATE_e [ 1 ] += _rtX -> TransferFcn1_CSTATE_e [ 0 ] ;
_rtXdot -> TransferFcn1_CSTATE_e [ 0 ] += _rtB -> B_35_395_0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] = 0.0 ; _rtXdot -> Hw6_CSTATE_f [ 1 ] = 0.0 ; _rtXdot ->
Hw6_CSTATE_f [ 0 ] += _rtP -> P_450 [ 0 ] * _rtX -> Hw6_CSTATE_f [ 0 ] ;
_rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_450 [ 1 ] * _rtX -> Hw6_CSTATE_f [
1 ] ; _rtXdot -> Hw6_CSTATE_f [ 1 ] += _rtP -> P_450 [ 2 ] * _rtX ->
Hw6_CSTATE_f [ 0 ] ; _rtXdot -> Hw6_CSTATE_f [ 0 ] += _rtP -> P_451 * _rtB ->
B_35_430_0 ; _rtXdot -> TransferFcn_CSTATE_m = 0.0 ; _rtXdot ->
TransferFcn_CSTATE_m += _rtP -> P_479 * _rtX -> TransferFcn_CSTATE_m ;
_rtXdot -> TransferFcn_CSTATE_m += _rtB -> B_35_425_0 ; _rtXdot ->
TransferFcn1_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn1_CSTATE_l += _rtP ->
P_481 * _rtX -> TransferFcn1_CSTATE_l ; _rtXdot -> TransferFcn1_CSTATE_l +=
_rtB -> B_35_431_0 ; _rtXdot -> TransferFcn2_CSTATE = 0.0 ; _rtXdot ->
TransferFcn2_CSTATE += _rtP -> P_485 * _rtX -> TransferFcn2_CSTATE ; _rtXdot
-> TransferFcn2_CSTATE += _rtB -> B_35_435_0 ; _rtXdot -> Actuador1_CSTATE =
0.0 ; _rtXdot -> Actuador1_CSTATE += _rtP -> P_568 * _rtX -> Actuador1_CSTATE
; _rtXdot -> Actuador1_CSTATE += _rtB -> B_35_614_0 ; _rtXdot ->
Filter_CSTATE = _rtB -> B_35_610_0 ; _rtXdot -> Integrator_CSTATE = _rtB ->
B_35_611_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_uGrid_1PH_hd_T * _rtB ;
P_uGrid_1PH_hd_T * _rtP ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; ssCallAccelRunBlock ( S , 35 , 124 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { boolean_T anyStateSaturated
; B_uGrid_1PH_hd_T * _rtB ; P_uGrid_1PH_hd_T * _rtP ; X_uGrid_1PH_hd_T * _rtX
; ZCV_uGrid_1PH_hd_T * _rtZCSV ; DW_uGrid_1PH_hd_T * _rtDW ; _rtDW = ( (
DW_uGrid_1PH_hd_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_uGrid_1PH_hd_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( (
X_uGrid_1PH_hd_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_uGrid_1PH_hd_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_uGrid_1PH_hd_T * ) _ssGetModelBlockIO
( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_35_12_0 -
uGrid_1PH_hd_rtC ( S ) -> B_35_13_0 ; if ( ( _rtDW -> inti_MODE == 1 ) && (
_rtX -> inti_CSTATE >= _rtP -> P_158 ) ) { _rtZCSV -> inti_IntgUpLimit_ZC =
0.0 ; } else { _rtZCSV -> inti_IntgUpLimit_ZC = _rtX -> inti_CSTATE - _rtP ->
P_158 ; } if ( ( _rtDW -> inti_MODE == 2 ) && ( _rtX -> inti_CSTATE <= _rtP
-> P_159 ) ) { _rtZCSV -> inti_IntgLoLimit_ZC = 0.0 ; } else { _rtZCSV ->
inti_IntgLoLimit_ZC = _rtX -> inti_CSTATE - _rtP -> P_159 ; }
anyStateSaturated = false ; if ( ( _rtDW -> inti_MODE == 3 ) || ( _rtDW ->
inti_MODE == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> inti_LeaveSaturate_ZC = _rtB -> B_35_525_0 ; } else { _rtZCSV ->
inti_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB
-> B_35_18_0 - _rtB -> B_35_10_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB
-> B_35_18_0 - _rtB -> B_35_20_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC = _rtB -> B_35_11_0 - _rtB -> B_35_23_0 ;
_rtZCSV -> LowerRelop1_RelopInput_ZC_i = _rtB -> B_35_18_0 - _rtB ->
B_35_30_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_f = _rtB -> B_35_18_0 - _rtB
-> B_35_32_0 ; _rtZCSV -> Compare_RelopInput_ZC_d = _rtB -> B_35_12_0 -
uGrid_1PH_hd_rtC ( S ) -> B_35_36_0 ; _rtZCSV -> Saturation_UprLim_ZC = _rtB
-> B_35_25_0 - _rtP -> P_171 ; _rtZCSV -> Saturation_LwrLim_ZC = _rtB ->
B_35_25_0 - _rtP -> P_172 ; _rtZCSV -> LowerRelop1_RelopInput_ZC_a = _rtB ->
B_35_54_0 - _rtB -> B_35_7_0 ; _rtZCSV -> UpperRelop_RelopInput_ZC_g = _rtB
-> B_35_54_0 - _rtB -> B_35_57_0 ; ssCallAccelRunBlock ( S , 35 , 124 ,
SS_CALL_MDL_ZERO_CROSSINGS ) ; ssCallAccelRunBlock ( S , 35 , 125 ,
SS_CALL_MDL_ZERO_CROSSINGS ) ; ssCallAccelRunBlock ( S , 35 , 145 ,
SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) -
_rtP -> P_341 ; _rtZCSV -> HitCrossing_HitNoOutput_ZC = _rtB -> B_35_215_0 -
_rtP -> P_347 ; ssCallAccelRunBlock ( S , 35 , 269 ,
SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV -> Step_StepTime_ZC_d = ssGetT ( S ) -
_rtP -> P_385 ; _rtZCSV -> HitCrossing_HitNoOutput_ZC_j = _rtB -> B_35_295_0
- _rtP -> P_391 ; _rtZCSV -> Step_StepTime_ZC_b = ssGetT ( S ) - _rtP ->
P_504 ; _rtZCSV -> HitCrossing_HitNoOutput_ZC_e = _rtB -> B_35_498_0 - _rtP
-> P_510 ; _rtZCSV -> Saturation_UprLim_ZC_i = _rtB -> B_35_531_0 - _rtP ->
P_530 ; _rtZCSV -> Saturation_LwrLim_ZC_l = _rtB -> B_35_531_0 - _rtP ->
P_531 ; _rtZCSV -> Abs_AbsZc_ZC = _rtB -> B_35_525_0 ; _rtZCSV ->
Compare_RelopInput_ZC_f = _rtB -> B_35_525_0 - uGrid_1PH_hd_rtC ( S ) ->
B_35_549_0 ; } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 3917766960U ) ; ssSetChecksumVal ( S , 1 ,
3474030865U ) ; ssSetChecksumVal ( S , 2 , 776553248U ) ; ssSetChecksumVal (
S , 3 , 4178874511U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "9.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
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
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_159 = rtMinusInf ; ( (
P_uGrid_1PH_hd_T * ) ssGetModelRtp ( S ) ) -> P_172 = rtMinusInf ; } static
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
