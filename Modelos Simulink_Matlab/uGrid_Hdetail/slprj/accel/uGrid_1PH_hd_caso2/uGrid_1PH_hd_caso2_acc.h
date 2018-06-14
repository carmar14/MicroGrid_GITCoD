#include "__cf_uGrid_1PH_hd_caso2.h"
#ifndef RTW_HEADER_uGrid_1PH_hd_caso2_acc_h_
#define RTW_HEADER_uGrid_1PH_hd_caso2_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef uGrid_1PH_hd_caso2_acc_COMMON_INCLUDES_
#define uGrid_1PH_hd_caso2_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "uGrid_1PH_hd_caso2_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_zcfcn.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_defines.h"
typedef struct { real_T B_0_0_0 ; real_T B_0_1_0 ; real_T B_0_2_0 ; real_T
B_0_3_0 ; real_T B_0_4_0 ; real_T B_0_5_0 ; real_T B_0_6_0 ; real_T B_0_7_0 ;
real_T B_0_8_0 ; real_T B_0_9_0 ; }
B_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_caso2_T ; typedef
struct { void * Synthesized_Atomic_Subsystem_For_Alg_Loop_1_AlgLoopData ; }
DW_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_caso2_T ; typedef
struct { real_T B_38_0_0 ; real_T B_38_1_0 ; real_T B_38_2_0 ; real_T
B_38_3_0 ; real_T B_38_4_0 ; real_T B_38_5_0 ; real_T B_38_6_0 ; real_T
B_38_7_0 ; real_T B_38_11_0 ; real_T B_38_13_0 ; real_T B_38_14_0 ; real_T
B_38_15_0 ; real_T B_38_16_0 ; real_T B_38_19_0 ; real_T B_38_20_0 ; real_T
B_38_21_0 ; real_T B_38_22_0 ; real_T B_38_24_0 ; real_T B_38_27_0 ; real_T
B_38_29_0 ; real_T B_38_30_0 ; real_T B_38_31_0 ; real_T B_38_33_0 ; real_T
B_38_34_0 ; real_T B_38_36_0 ; real_T B_38_37_0 ; real_T B_38_38_0 ; real_T
B_38_39_0 ; real_T B_38_41_0 ; real_T B_38_44_0 ; real_T B_38_47_0 ; real_T
B_38_48_0 ; real_T B_38_49_0 ; real_T B_38_50_0 ; real_T B_38_55_0 ; real_T
B_38_56_0 ; real_T B_38_57_0 ; real_T B_38_58_0 ; real_T B_38_60_0 ; real_T
B_38_65_0 ; real_T B_38_66_0 ; real_T B_38_67_0 ; real_T B_38_68_0 ; real_T
B_38_70_0 ; real_T B_38_71_0 ; real_T B_38_72_0 ; real_T B_38_73_0 ; real_T
B_38_75_0 ; real_T B_38_76_0 ; real_T B_38_78_0 ; real_T B_38_81_0 ; real_T
B_38_95_0 ; real_T B_38_96_0 ; real_T B_38_97_0 ; real_T B_38_98_0 ; real_T
B_38_99_0 ; real_T B_38_100_0 ; real_T B_38_105_0 ; real_T B_38_106_0 ;
real_T B_38_130_0 ; real_T B_38_132_0 ; real_T B_38_133_0 ; real_T B_38_134_0
; real_T B_38_135_0 ; real_T B_38_136_0 ; real_T B_38_137_0 ; real_T
B_38_138_0 ; real_T B_38_139_0 ; real_T B_38_140_0 ; real_T B_38_141_0 ;
real_T B_38_142_0 ; real_T B_38_143_0 ; real_T B_38_144_0 ; real_T B_38_145_0
[ 11 ] ; real_T B_38_145_1 [ 54 ] ; real_T B_38_146_0 [ 12 ] ; real_T
B_38_146_1 [ 12 ] ; real_T B_38_149_0 ; real_T B_38_150_0 ; real_T B_38_151_0
; real_T B_38_152_0 ; real_T B_38_159_0 ; real_T B_38_160_0 ; real_T
B_38_163_0 ; real_T B_38_164_0 ; real_T B_38_166_0 [ 3 ] ; real_T B_38_166_1
; real_T B_38_166_2 ; real_T B_38_166_3 ; real_T B_38_168_0 ; real_T
B_38_172_0 ; real_T B_38_173_0 ; real_T B_38_174_0 ; real_T B_38_190_0 ;
real_T B_38_194_0 ; real_T B_38_198_0 ; real_T B_38_202_0 ; real_T B_38_210_0
; real_T B_38_211_0 ; real_T B_38_225_0 ; real_T B_38_227_0 ; real_T
B_38_230_0 ; real_T B_38_231_0 ; real_T B_38_232_0 ; real_T B_38_234_0 ;
real_T B_38_235_0 ; real_T B_38_236_0 ; real_T B_38_247_0 ; real_T B_38_251_0
; real_T B_38_252_0 ; real_T B_38_253_0 ; real_T B_38_269_0 ; real_T
B_38_273_0 ; real_T B_38_277_0 ; real_T B_38_281_0 ; real_T B_38_289_0 ;
real_T B_38_290_0 [ 3 ] ; real_T B_38_290_1 ; real_T B_38_290_2 ; real_T
B_38_290_3 ; real_T B_38_291_0 ; real_T B_38_305_0 ; real_T B_38_307_0 ;
real_T B_38_310_0 ; real_T B_38_311_0 ; real_T B_38_312_0 ; real_T B_38_314_0
; real_T B_38_315_0 ; real_T B_38_316_0 ; real_T B_38_329_0 [ 2 ] ; real_T
B_38_330_0 [ 2 ] ; real_T B_38_331_0 [ 200 ] ; real_T B_38_332_0 [ 2 ] ;
real_T B_38_333_0 [ 40000 ] ; real_T B_38_334_0 [ 40000 ] ; real_T B_38_336_0
[ 200 ] ; real_T B_38_336_1 ; real_T B_38_336_2 ; real_T B_38_336_3 ; real_T
B_38_342_0 ; real_T B_38_347_0 [ 40000 ] ; real_T B_38_348_0 [ 40000 ] ;
real_T B_38_349_0 [ 2 ] ; real_T B_38_350_0 [ 2 ] ; real_T B_38_351_0 [ 200 ]
; real_T B_38_352_0 [ 2 ] ; real_T B_38_354_0 [ 200 ] ; real_T B_38_354_1 ;
real_T B_38_354_2 ; real_T B_38_354_3 ; real_T B_38_356_0 ; real_T B_38_357_0
; real_T B_38_358_0 ; real_T B_38_360_0 ; real_T B_38_363_0 ; real_T
B_38_365_0 ; real_T B_38_367_0 ; real_T B_38_368_0 ; real_T B_38_371_0 ;
real_T B_38_373_0 ; real_T B_38_375_0 ; real_T B_38_378_0 ; real_T B_38_381_0
; real_T B_38_383_0 ; real_T B_38_385_0 ; real_T B_38_386_0 ; real_T
B_38_389_0 ; real_T B_38_391_0 ; real_T B_38_393_0 ; real_T B_38_403_0 ;
real_T B_38_405_0 ; real_T B_38_407_0 ; real_T B_38_409_0 ; real_T B_38_410_0
; real_T B_38_411_0 ; real_T B_38_412_0 ; real_T B_38_413_0 ; real_T
B_38_414_0 ; real_T B_38_415_0 ; real_T B_38_416_0 ; real_T B_38_417_0 ;
real_T B_38_419_0 ; real_T B_38_421_0 ; real_T B_38_422_0 ; real_T B_38_424_0
; real_T B_38_428_0 ; real_T B_38_430_0 ; real_T B_38_431_0 ; real_T
B_38_432_0 ; real_T B_38_433_0 ; real_T B_38_435_0 ; real_T B_38_437_0 ;
real_T B_38_438_0 ; real_T B_38_439_0 ; real_T B_38_440_0 ; real_T B_38_442_0
; real_T B_38_444_0 ; real_T B_38_445_0 ; real_T B_38_446_0 ; real_T
B_38_447_0 ; real_T B_38_449_0 ; real_T B_38_453_0 ; real_T B_38_454_0 ;
real_T B_38_455_0 ; real_T B_38_459_0 ; real_T B_38_463_0 ; real_T B_38_476_0
; real_T B_38_480_0 ; real_T B_38_484_0 ; real_T B_38_488_0 ; real_T
B_38_496_0 ; real_T B_38_497_0 ; real_T B_38_511_0 ; real_T B_38_513_0 ;
real_T B_38_516_0 ; real_T B_38_517_0 ; real_T B_38_518_0 ; real_T B_38_520_0
; real_T B_38_521_0 ; real_T B_38_522_0 ; real_T B_38_537_0 ; real_T
B_38_539_0 ; real_T B_38_541_0 ; real_T B_38_543_0 ; real_T B_38_549_0 ;
real_T B_38_552_0 ; real_T B_38_554_0 ; real_T B_38_555_0 ; real_T B_38_556_0
; real_T B_38_558_0 ; real_T B_38_560_0 ; real_T B_38_561_0 ; real_T
B_38_562_0 ; real_T B_38_563_0 ; real_T B_38_574_0 ; real_T B_38_578_0 ;
real_T B_38_579_0 ; real_T B_38_580_0 ; real_T B_38_581_0 ; real_T B_38_583_0
; real_T B_38_585_0 ; real_T B_38_586_0 ; real_T B_38_587_0 ; real_T
B_38_588_0 ; real_T B_38_592_0 ; real_T B_38_594_0 ; real_T B_38_595_0 ;
real_T B_38_597_0 ; real_T B_38_598_0 ; real_T B_38_599_0 ; real_T B_38_600_0
; real_T B_38_607_0 ; real_T B_38_608_0 [ 2 ] ; real_T B_38_609_0 [ 2 ] ;
real_T B_38_611_0 [ 2 ] ; real_T B_38_611_1 ; real_T B_38_611_2 ; real_T
B_38_611_3 ; real_T B_38_615_0 [ 2 ] ; real_T B_38_616_0 [ 2 ] ; real_T
B_38_618_0 [ 2 ] ; real_T B_38_618_1 ; real_T B_38_618_2 ; real_T B_38_618_3
; real_T B_38_620_0 ; real_T B_38_622_0 ; real_T B_38_623_0 ; real_T
B_38_624_0 ; real_T B_38_625_0 ; real_T B_38_627_0 ; real_T B_38_629_0 ;
real_T B_38_630_0 ; real_T B_38_631_0 ; real_T B_38_632_0 ; real_T B_38_640_0
; real_T B_38_641_0 ; real_T B_38_642_0 ; real_T B_38_643_0 ; real_T
B_38_644_0 ; real_T B_38_645_0 ; real_T B_38_646_0 ; real_T B_38_650_0 ;
real_T B_38_651_0 ; real_T B_38_652_0 ; real_T B_38_653_0 ; real_T B_38_654_0
; real_T B_38_655_0 ; real_T B_38_656_0 ; real_T B_38_657_0 ; real_T
B_38_658_0 ; real_T B_37_0_0 ; real_T B_36_0_0 ; real_T B_35_0_0 ; real_T
B_34_0_0 ; real_T B_33_0_0 ; real_T B_32_0_0 ; real_T B_31_0_0 ; real_T
B_31_0_1 ; real_T B_31_0_2 ; real_T B_31_0_3 ; real_T B_31_0_4 ; real_T
B_31_0_5 ; real_T B_31_0_6 ; real_T B_30_0_0 [ 2 ] ; real_T B_30_0_1 ; real_T
B_30_0_2 ; real_T B_30_0_3 ; real_T B_30_0_4 ; real_T B_30_0_5 ; real_T
B_30_0_6 ; real_T B_29_0_0 [ 2 ] ; real_T B_29_0_1 ; real_T B_29_0_2 ; real_T
B_29_0_3 ; real_T B_29_0_4 ; real_T B_29_0_5 ; real_T B_29_0_6 ; real_T
B_28_0_0 [ 2 ] ; real_T B_28_0_1 ; real_T B_28_0_2 ; real_T B_28_0_3 ; real_T
B_28_0_4 ; real_T B_28_0_5 ; real_T B_28_0_6 ; real_T B_27_0_0 ; real_T
B_27_0_1 ; real_T B_27_0_2 ; real_T B_27_0_3 ; real_T B_27_0_4 ; real_T
B_27_0_5 ; real_T B_27_0_6 ; real_T B_26_0_0 ; real_T B_26_0_1 ; real_T
B_26_0_2 ; real_T B_26_0_3 ; real_T B_26_0_4 ; real_T B_26_0_5 ; real_T
B_26_0_6 ; real_T B_21_0_1 [ 4 ] ; real_T B_21_0_2 [ 2 ] ; real_T B_21_0_3 [
2 ] ; real_T B_21_0_4 [ 2 ] ; real_T B_21_0_5 [ 2 ] ; real_T B_21_0_6 ;
real_T B_21_0_7 ; real_T B_20_0_1 [ 4 ] ; real_T B_20_0_2 [ 2 ] ; real_T
B_20_0_3 [ 2 ] ; real_T B_20_0_4 [ 2 ] ; real_T B_20_0_5 [ 2 ] ; real_T
B_20_0_6 ; real_T B_20_0_7 ; real_T B_19_0_1 ; real_T B_19_0_2 ; real_T
B_18_0_1 [ 2 ] ; real_T B_18_0_2 [ 200 ] ; real_T B_17_0_1 [ 40000 ] ; real_T
B_17_0_2 [ 200 ] ; real_T B_17_0_3 [ 40000 ] ; real_T B_17_0_4 [ 200 ] ;
real_T B_17_0_5 [ 200 ] ; real_T B_17_0_6 [ 200 ] ; real_T B_17_0_7 [ 200 ] ;
real_T B_16_0_1 [ 2 ] ; real_T B_16_0_2 [ 200 ] ; real_T B_15_0_1 [ 40000 ] ;
real_T B_15_0_2 [ 200 ] ; real_T B_15_0_3 [ 40000 ] ; real_T B_15_0_4 [ 200 ]
; real_T B_15_0_5 [ 200 ] ; real_T B_15_0_6 [ 200 ] ; real_T B_15_0_7 [ 200 ]
; real_T B_14_0_0 ; real_T B_13_0_0 ; real_T B_12_0_0 ; real_T B_10_0_0 [ 4 ]
; real_T B_9_0_0 [ 4 ] ; real_T B_8_0_0 [ 4 ] ; real_T B_7_0_0 [ 4 ] ; real_T
B_3_0_1 ; real_T B_2_0_1 ; real_T B_1_0_1 ; boolean_T B_38_23_0 ; boolean_T
B_38_25_0 ; boolean_T B_38_40_0 ; boolean_T B_38_42_0 ; boolean_T B_38_77_0 ;
boolean_T B_38_79_0 ; char_T pad_B_38_79_0 [ 2 ] ;
B_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_caso2_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ; } B_uGrid_1PH_hd_caso2_T ;
typedef struct { real_T itinit1_PreviousInput ; real_T itinit_PreviousInput ;
real_T TimeStampA ; real_T LastUAtTimeA ; real_T TimeStampB ; real_T
LastUAtTimeB ; real_T TimeStampA_k ; real_T LastUAtTimeA_m ; real_T
TimeStampB_f ; real_T LastUAtTimeB_o ; real_T Memory1_PreviousInput [ 200 ] ;
real_T Memory2_PreviousInput [ 2 ] ; real_T Memory3_PreviousInput [ 200 ] ;
real_T Memory4_PreviousInput [ 2 ] ; real_T Memory_PreviousInput ; real_T
Memory_PreviousInput_f ; real_T Memory_PreviousInput_p ; real_T
Memory_PreviousInput_k ; real_T TimeStampA_b ; real_T LastUAtTimeA_f ; real_T
TimeStampB_a ; real_T LastUAtTimeB_n ; real_T nextTime ; real_T nextTime_e ;
real_T nextTime_f ; real_T TimeStampA_n ; real_T LastUAtTimeA_ma ; real_T
TimeStampB_m ; real_T LastUAtTimeB_g ; real_T nextTime_i ; real_T nextTime_j
; real_T nextTime_l ; int64_T numCompleteCycles ; int64_T numCompleteCycles_j
; int64_T numCompleteCycles_o ; int64_T numCompleteCycles_f ; int64_T
numCompleteCycles_h ; int64_T numCompleteCycles_hh ; real_T StateSpace_RWORK
[ 2 ] ; struct { real_T modelTStart ; } TransportDelay_RWORK ; struct {
real_T modelTStart ; } TransportDelay_RWORK_n ; struct { real_T modelTStart ;
} TransportDelay_RWORK_m ; struct { real_T modelTStart ; }
TransportDelay_RWORK_i ; struct { real_T modelTStart ; }
MotordeCombustin1_RWORK ; void * StateSpace_PWORK [ 22 ] ; void * Scope_PWORK
[ 2 ] ; void * Scope13_PWORK ; void * Scope15_PWORK ; void * Scope19_PWORK ;
void * Scope2_PWORK [ 2 ] ; void * Scope20_PWORK ; void * Scope3_PWORK [ 2 ]
; void * Scope4_PWORK ; void * Scope_PWORK_m ; void * Scope1_PWORK ; void *
qpOASES_PWORK [ 8 ] ; void * Scope2_PWORK_k ; void * Scope3_PWORK_j [ 2 ] ;
void * Scope4_PWORK_k ; void * Scope5_PWORK [ 2 ] ; void * Scope_PWORK_a ;
void * Scope1_PWORK_g ; void * Scope2_PWORK_b ; void * Scope3_PWORK_e [ 2 ] ;
void * qpOASES1_PWORK [ 8 ] ; void * Scope1_PWORK_m [ 2 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay_PWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_d ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_i ; void * Scope17_PWORK ; void * Scope18_PWORK ; void *
Scope6_PWORK ; void * Scope7_PWORK [ 2 ] ; void * ToWorkspace_PWORK ; void *
ToWorkspace1_PWORK ; void * Scope7_PWORK_k [ 2 ] ; void * Scope8_PWORK [ 2 ]
; void * Scope10_PWORK ; void * Scope11_PWORK ; void * Scope8_PWORK_i ; void
* qpOASES_linprog1_PWORK [ 8 ] ; void * Scope12_PWORK ; void * Scope16_PWORK
[ 2 ] ; void * Scope21_PWORK ; void * qpOASES_linprog_PWORK [ 8 ] ; void *
Scope9_PWORK ; void * Scope_PWORK_k ; void * Scope1_PWORK_gi ; void *
Scope14_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
MotordeCombustin1_PWORK ; void * Scope5_PWORK_l ; int32_T justEnabled ;
int32_T currentValue ; int32_T justEnabled_l ; int32_T currentValue_d ;
int32_T justEnabled_k ; int32_T currentValue_a ; int32_T justEnabled_m ;
int32_T currentValue_h ; int32_T justEnabled_j ; int32_T currentValue_n ;
int32_T justEnabled_o ; int32_T currentValue_f ; int_T inti_IWORK ; int_T
StateSpace_IWORK [ 23 ] ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct
{ int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_h ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_j ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_a ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } MotordeCombustin1_IWORK ; int_T inti_MODE ; char
StateSpace_MODE [ 112 ] ; int_T Step_MODE ; int_T Step_MODE_c ; int_T
Step_MODE_f ; int_T Saturation_MODE ; int_T Abs_MODE ; int_T Abs_MODE_d ;
int_T Abs1_MODE ; int8_T Subsystem_SubsysRanBC ; int8_T
Subsystem_SubsysRanBC_d ; int8_T Subsystem_SubsysRanBC_e ; int8_T
Subsystem_SubsysRanBC_j ; int8_T Subsystem_SubsysRanBC_eb ; int8_T
Subsystem_SubsysRanBC_o ; int8_T Subsystem_SubsysRanBC_p ; int8_T
Subsystem_SubsysRanBC_m ; int8_T Subsystem_SubsysRanBC_k ; int8_T
Subsystem_SubsysRanBC_l ; int8_T Subsystem_SubsysRanBC_b ; int8_T
Subsystem_SubsysRanBC_g ; boolean_T Compare_Mode ; boolean_T LowerRelop1_Mode
; boolean_T UpperRelop_Mode ; boolean_T LowerRelop1_Mode_g ; boolean_T
UpperRelop_Mode_g ; boolean_T Compare_Mode_k ; boolean_T LowerRelop1_Mode_c ;
boolean_T UpperRelop_Mode_gu ; boolean_T Compare_Mode_i ; boolean_T
Compare_Mode_e ; char_T pad_Compare_Mode_e [ 6 ] ;
DW_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_caso2_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ; } DW_uGrid_1PH_hd_caso2_T ;
typedef struct { real_T Dinmicaeneleje1_CSTATE ; real_T TransferFcn_CSTATE ;
real_T Currentfilter_CSTATE ; real_T inti_CSTATE ; real_T StateSpace_CSTATE ;
real_T Integrator2_CSTATE ; real_T Currentfilter1_CSTATE ; real_T
StateSpace_CSTATE_p [ 21 ] ; real_T Hw2_CSTATE [ 4 ] ; real_T Hw6_CSTATE [ 4
] ; real_T Hw1_CSTATE [ 4 ] ; real_T Hw3_CSTATE [ 4 ] ; real_T Hw4_CSTATE [ 2
] ; real_T Hw1_CSTATE_k [ 2 ] ; real_T Hw7_CSTATE [ 2 ] ; real_T Hw3_CSTATE_e
[ 2 ] ; real_T TransferFcn_CSTATE_j ; real_T TransferFcn1_CSTATE ; real_T
TransferFcn_CSTATE_g ; real_T TransferFcn1_CSTATE_p ; real_T Hw2_CSTATE_p [ 2
] ; real_T integrator_CSTATE ; real_T integrator_CSTATE_i ; real_T
integrator_CSTATE_p ; real_T integrator_CSTATE_l ; real_T Hi_Pass1_CSTATE ;
real_T Hw5_CSTATE [ 2 ] ; real_T TransferFcn1_CSTATE_e [ 2 ] ; real_T
Hw6_CSTATE_f [ 2 ] ; real_T TransferFcn_CSTATE_m ; real_T
TransferFcn1_CSTATE_l ; real_T TransferFcn2_CSTATE ; real_T
TransferFcn1_CSTATE_g ; real_T Actuador1_CSTATE ; real_T Filter_CSTATE ;
real_T Integrator_CSTATE ; } X_uGrid_1PH_hd_caso2_T ; typedef struct { real_T
Dinmicaeneleje1_CSTATE ; real_T TransferFcn_CSTATE ; real_T
Currentfilter_CSTATE ; real_T inti_CSTATE ; real_T StateSpace_CSTATE ; real_T
Integrator2_CSTATE ; real_T Currentfilter1_CSTATE ; real_T
StateSpace_CSTATE_p [ 21 ] ; real_T Hw2_CSTATE [ 4 ] ; real_T Hw6_CSTATE [ 4
] ; real_T Hw1_CSTATE [ 4 ] ; real_T Hw3_CSTATE [ 4 ] ; real_T Hw4_CSTATE [ 2
] ; real_T Hw1_CSTATE_k [ 2 ] ; real_T Hw7_CSTATE [ 2 ] ; real_T Hw3_CSTATE_e
[ 2 ] ; real_T TransferFcn_CSTATE_j ; real_T TransferFcn1_CSTATE ; real_T
TransferFcn_CSTATE_g ; real_T TransferFcn1_CSTATE_p ; real_T Hw2_CSTATE_p [ 2
] ; real_T integrator_CSTATE ; real_T integrator_CSTATE_i ; real_T
integrator_CSTATE_p ; real_T integrator_CSTATE_l ; real_T Hi_Pass1_CSTATE ;
real_T Hw5_CSTATE [ 2 ] ; real_T TransferFcn1_CSTATE_e [ 2 ] ; real_T
Hw6_CSTATE_f [ 2 ] ; real_T TransferFcn_CSTATE_m ; real_T
TransferFcn1_CSTATE_l ; real_T TransferFcn2_CSTATE ; real_T
TransferFcn1_CSTATE_g ; real_T Actuador1_CSTATE ; real_T Filter_CSTATE ;
real_T Integrator_CSTATE ; } XDot_uGrid_1PH_hd_caso2_T ; typedef struct {
boolean_T Dinmicaeneleje1_CSTATE ; boolean_T TransferFcn_CSTATE ; boolean_T
Currentfilter_CSTATE ; boolean_T inti_CSTATE ; boolean_T StateSpace_CSTATE ;
boolean_T Integrator2_CSTATE ; boolean_T Currentfilter1_CSTATE ; boolean_T
StateSpace_CSTATE_p [ 21 ] ; boolean_T Hw2_CSTATE [ 4 ] ; boolean_T
Hw6_CSTATE [ 4 ] ; boolean_T Hw1_CSTATE [ 4 ] ; boolean_T Hw3_CSTATE [ 4 ] ;
boolean_T Hw4_CSTATE [ 2 ] ; boolean_T Hw1_CSTATE_k [ 2 ] ; boolean_T
Hw7_CSTATE [ 2 ] ; boolean_T Hw3_CSTATE_e [ 2 ] ; boolean_T
TransferFcn_CSTATE_j ; boolean_T TransferFcn1_CSTATE ; boolean_T
TransferFcn_CSTATE_g ; boolean_T TransferFcn1_CSTATE_p ; boolean_T
Hw2_CSTATE_p [ 2 ] ; boolean_T integrator_CSTATE ; boolean_T
integrator_CSTATE_i ; boolean_T integrator_CSTATE_p ; boolean_T
integrator_CSTATE_l ; boolean_T Hi_Pass1_CSTATE ; boolean_T Hw5_CSTATE [ 2 ]
; boolean_T TransferFcn1_CSTATE_e [ 2 ] ; boolean_T Hw6_CSTATE_f [ 2 ] ;
boolean_T TransferFcn_CSTATE_m ; boolean_T TransferFcn1_CSTATE_l ; boolean_T
TransferFcn2_CSTATE ; boolean_T TransferFcn1_CSTATE_g ; boolean_T
Actuador1_CSTATE ; boolean_T Filter_CSTATE ; boolean_T Integrator_CSTATE ; }
XDis_uGrid_1PH_hd_caso2_T ; typedef struct { real_T Dinmicaeneleje1_CSTATE ;
real_T TransferFcn_CSTATE ; real_T Currentfilter_CSTATE ; real_T inti_CSTATE
; real_T StateSpace_CSTATE ; real_T Integrator2_CSTATE ; real_T
Currentfilter1_CSTATE ; real_T StateSpace_CSTATE_p [ 21 ] ; real_T Hw2_CSTATE
[ 4 ] ; real_T Hw6_CSTATE [ 4 ] ; real_T Hw1_CSTATE [ 4 ] ; real_T Hw3_CSTATE
[ 4 ] ; real_T Hw4_CSTATE [ 2 ] ; real_T Hw1_CSTATE_k [ 2 ] ; real_T
Hw7_CSTATE [ 2 ] ; real_T Hw3_CSTATE_e [ 2 ] ; real_T TransferFcn_CSTATE_j ;
real_T TransferFcn1_CSTATE ; real_T TransferFcn_CSTATE_g ; real_T
TransferFcn1_CSTATE_p ; real_T Hw2_CSTATE_p [ 2 ] ; real_T integrator_CSTATE
; real_T integrator_CSTATE_i ; real_T integrator_CSTATE_p ; real_T
integrator_CSTATE_l ; real_T Hi_Pass1_CSTATE ; real_T Hw5_CSTATE [ 2 ] ;
real_T TransferFcn1_CSTATE_e [ 2 ] ; real_T Hw6_CSTATE_f [ 2 ] ; real_T
TransferFcn_CSTATE_m ; real_T TransferFcn1_CSTATE_l ; real_T
TransferFcn2_CSTATE ; real_T TransferFcn1_CSTATE_g ; real_T Actuador1_CSTATE
; real_T Filter_CSTATE ; real_T Integrator_CSTATE ; }
CStateAbsTol_uGrid_1PH_hd_caso2_T ; typedef struct { real_T
Compare_RelopInput_ZC ; real_T inti_Reset_ZC ; real_T inti_IntgUpLimit_ZC ;
real_T inti_IntgLoLimit_ZC ; real_T inti_LeaveSaturate_ZC ; real_T
LowerRelop1_RelopInput_ZC ; real_T UpperRelop_RelopInput_ZC ; real_T
LowerRelop1_RelopInput_ZC_i ; real_T UpperRelop_RelopInput_ZC_f ; real_T
Compare_RelopInput_ZC_d ; real_T LowerRelop1_RelopInput_ZC_a ; real_T
UpperRelop_RelopInput_ZC_g ; real_T StateSpace_Sf0_ZC [ 28 ] ; real_T
ttnetwork_Sf0_ZC ; real_T ttkernel_Sf0_ZC ; real_T Step_StepTime_ZC ; real_T
HitCrossing_HitNoOutput_ZC ; real_T ttkernel_Sf0_ZC_j ; real_T
Step_StepTime_ZC_d ; real_T HitCrossing_HitNoOutput_ZC_j ; real_T
Step_StepTime_ZC_b ; real_T HitCrossing_HitNoOutput_ZC_e ; real_T
Saturation_UprLim_ZC ; real_T Saturation_LwrLim_ZC ; real_T Abs_AbsZc_ZC ;
real_T Compare_RelopInput_ZC_f ; real_T Abs_AbsZc_ZC_j ; real_T Abs1_AbsZc_ZC
; real_T Compare_RelopInput_ZC_b ; real_T Subsystem_Trig_ZC ; real_T
Subsystem_Trig_ZC_o ; real_T Subsystem_Trig_ZC_p ; real_T Subsystem_Trig_ZC_i
; real_T Subsystem_Trig_ZC_a ; real_T Subsystem_Trig_ZC_b ; real_T
Subsystem_Trig_ZC_i1 ; real_T Subsystem_Trig_ZC_om ; real_T
Subsystem_Trig_ZC_j ; real_T Subsystem_Trig_ZC_h ; real_T
Subsystem_Trig_ZC_od ; real_T Subsystem_Trig_ZC_iu ; }
ZCV_uGrid_1PH_hd_caso2_T ; typedef struct { ZCSigState Compare_RelopInput_ZCE
; ZCSigState inti_Reset_ZCE ; ZCSigState inti_IntgUpLimit_ZCE ; ZCSigState
inti_IntgLoLimit_ZCE ; ZCSigState inti_LeaveSaturate_ZCE ; ZCSigState
LowerRelop1_RelopInput_ZCE ; ZCSigState UpperRelop_RelopInput_ZCE ;
ZCSigState LowerRelop1_RelopInput_ZCE_d ; ZCSigState
UpperRelop_RelopInput_ZCE_l ; ZCSigState Compare_RelopInput_ZCE_c ;
ZCSigState LowerRelop1_RelopInput_ZCE_g ; ZCSigState
UpperRelop_RelopInput_ZCE_a ; ZCSigState StateSpace_Sf0_ZCE [ 28 ] ;
ZCSigState ttnetwork_Sf0_ZCE ; ZCSigState ttkernel_Sf0_ZCE ; ZCSigState
Step_StepTime_ZCE ; ZCSigState HitCrossing_HitNoOutput_ZCE ; ZCSigState
ttkernel_Sf0_ZCE_j ; ZCSigState Step_StepTime_ZCE_j ; ZCSigState
HitCrossing_HitNoOutput_ZCE_c ; ZCSigState Step_StepTime_ZCE_l ; ZCSigState
HitCrossing_HitNoOutput_ZCE_c4 ; ZCSigState Saturation_UprLim_ZCE ;
ZCSigState Saturation_LwrLim_ZCE ; ZCSigState Abs_AbsZc_ZCE ; ZCSigState
Compare_RelopInput_ZCE_cy ; ZCSigState Abs_AbsZc_ZCE_m ; ZCSigState
Abs1_AbsZc_ZCE ; ZCSigState Compare_RelopInput_ZCE_p ; ZCSigState
Subsystem_Trig_ZCE ; ZCSigState Subsystem_Trig_ZCE_f ; ZCSigState
Subsystem_Trig_ZCE_d ; ZCSigState Subsystem_Trig_ZCE_o ; ZCSigState
Subsystem_Trig_ZCE_a ; ZCSigState Subsystem_Trig_ZCE_i ; ZCSigState
Subsystem_Trig_ZCE_h ; ZCSigState Subsystem_Trig_ZCE_k ; ZCSigState
Subsystem_Trig_ZCE_in ; ZCSigState Subsystem_Trig_ZCE_d4 ; ZCSigState
Subsystem_Trig_ZCE_e ; ZCSigState Subsystem_Trig_ZCE_at ; }
PrevZCX_uGrid_1PH_hd_caso2_T ; typedef struct { const real_T B_38_17_0 ;
const real_T B_38_45_0 ; const real_T B_38_212_0 ; const real_T B_38_292_0 ;
const real_T B_38_498_0 ; const real_T B_38_575_0 ; const real_T B_38_589_0 ;
} ConstB_uGrid_1PH_hd_caso2_T ;
#define uGrid_1PH_hd_caso2_rtC(S) ((ConstB_uGrid_1PH_hd_caso2_T *) _ssGetConstBlockIO(S))
struct P_uGrid_1PH_hd_caso2_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ;
real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 [ 2 ] ; real_T P_13 ;
real_T P_14 [ 2 ] ; real_T P_15 ; real_T P_16 [ 2 ] ; real_T P_17 ; real_T
P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ;
real_T P_24 ; real_T P_25 ; real_T P_26 [ 2 ] ; real_T P_27 ; real_T P_28 [ 2
] ; real_T P_29 ; real_T P_30 [ 2 ] ; real_T P_31 ; real_T P_32 ; real_T P_33
; real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ;
real_T P_39 ; real_T P_40 [ 2 ] ; real_T P_41 ; real_T P_42 [ 2 ] ; real_T
P_43 ; real_T P_44 [ 2 ] ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T
P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ;
real_T P_54 [ 2 ] ; real_T P_55 ; real_T P_56 [ 2 ] ; real_T P_57 ; real_T
P_58 [ 2 ] ; real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T
P_63 ; real_T P_64 ; real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 [
2 ] ; real_T P_69 ; real_T P_70 [ 2 ] ; real_T P_71 ; real_T P_72 [ 2 ] ;
real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 ; real_T P_77 ; real_T
P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ; real_T P_82 [ 2 ] ; real_T
P_83 ; real_T P_84 [ 2 ] ; real_T P_85 ; real_T P_86 [ 2 ] ; real_T P_87 ;
real_T P_88 ; real_T P_89 [ 2 ] ; real_T P_90 ; real_T P_91 [ 2 ] ; real_T
P_92 ; real_T P_93 [ 2 ] ; real_T P_94 ; real_T P_95 [ 2 ] ; real_T P_96 ;
real_T P_97 ; real_T P_98 [ 2 ] ; real_T P_99 ; real_T P_100 [ 2 ] ; real_T
P_101 ; real_T P_102 [ 2 ] ; real_T P_103 ; real_T P_104 [ 2 ] ; real_T P_105
; real_T P_106 ; real_T P_107 [ 2 ] ; real_T P_108 ; real_T P_109 [ 2 ] ;
real_T P_110 ; real_T P_111 [ 2 ] ; real_T P_112 ; real_T P_113 [ 2 ] ;
real_T P_114 ; real_T P_115 ; real_T P_116 [ 2 ] ; real_T P_117 ; real_T
P_118 [ 2 ] ; real_T P_119 ; real_T P_120 [ 2 ] ; real_T P_121 ; real_T P_122
[ 2 ] ; real_T P_123 ; real_T P_124 ; real_T P_125 [ 2 ] ; real_T P_126 ;
real_T P_127 [ 2 ] ; real_T P_128 ; real_T P_129 [ 2 ] ; real_T P_130 ;
real_T P_131 [ 2 ] ; real_T P_132 ; real_T P_133 ; real_T P_134 [ 2 ] ;
real_T P_135 ; real_T P_136 [ 2 ] ; real_T P_137 ; real_T P_138 [ 2 ] ;
real_T P_139 ; real_T P_140 [ 2 ] ; real_T P_141 ; real_T P_142 ; real_T
P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ; real_T
P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ; real_T
P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T P_157 ; real_T
P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ; real_T P_162 ; real_T
P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ; real_T P_167 ; real_T
P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T P_172 ; real_T
P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T P_177 ; real_T
P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ; real_T P_182 ; real_T
P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ; real_T P_187 ; real_T
P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ; real_T P_192 ; real_T
P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T P_197 ; real_T
P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ; real_T P_202 ; real_T
P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T P_207 ; real_T
P_208 ; real_T P_209 ; real_T P_210 ; real_T P_211 ; real_T P_212 ; real_T
P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ; real_T P_217 ; real_T
P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ; real_T P_222 ; real_T
P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ; real_T P_227 ; real_T
P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 [ 2 ] ; real_T P_232 [
8496 ] ; real_T P_233 [ 2 ] ; real_T P_234 [ 4 ] ; real_T P_235 [ 2 ] ;
real_T P_236 [ 21 ] ; real_T P_237 [ 2 ] ; real_T P_238 [ 7200 ] ; real_T
P_239 [ 2 ] ; real_T P_240 [ 54 ] ; real_T P_241 [ 2 ] ; real_T P_242 [ 27 ]
; real_T P_243 [ 2 ] ; real_T P_244 [ 27 ] ; real_T P_245 [ 2 ] ; real_T
P_246 [ 27 ] ; real_T P_247 [ 2 ] ; real_T P_248 ; real_T P_249 [ 2 ] ;
real_T P_250 ; real_T P_251 [ 2 ] ; real_T P_252 ; real_T P_253 [ 2 ] ;
real_T P_254 ; real_T P_255 [ 2 ] ; real_T P_256 ; real_T P_257 [ 2 ] ;
real_T P_258 ; real_T P_259 [ 2 ] ; real_T P_260 ; real_T P_261 [ 2 ] ;
real_T P_262 ; real_T P_263 [ 2 ] ; real_T P_264 [ 2 ] ; real_T P_265 [ 2 ] ;
real_T P_266 ; real_T P_267 [ 2 ] ; real_T P_268 [ 3 ] ; real_T P_269 [ 2 ] ;
real_T P_270 ; real_T P_271 [ 2 ] ; real_T P_272 ; real_T P_273 [ 2 ] ;
real_T P_274 ; real_T P_275 [ 2 ] ; real_T P_276 ; real_T P_277 [ 2 ] ;
real_T P_278 ; real_T P_279 [ 2 ] ; real_T P_280 ; real_T P_281 [ 2 ] ;
real_T P_282 ; real_T P_283 [ 2 ] ; real_T P_284 ; real_T P_285 [ 2 ] ;
real_T P_286 ; real_T P_287 [ 2 ] ; real_T P_288 ; real_T P_289 [ 2 ] ;
real_T P_290 ; real_T P_291 [ 2 ] ; real_T P_292 ; real_T P_293 [ 7 ] ;
real_T P_294 ; real_T P_295 ; real_T P_296 ; real_T P_297 [ 7 ] ; real_T
P_298 ; real_T P_299 ; real_T P_300 ; real_T P_301 [ 7 ] ; real_T P_302 ;
real_T P_303 ; real_T P_304 ; real_T P_305 [ 7 ] ; real_T P_306 ; real_T
P_307 ; real_T P_308 ; real_T P_309 [ 3 ] ; real_T P_310 ; real_T P_311 ;
real_T P_312 ; real_T P_313 [ 3 ] ; real_T P_314 ; real_T P_315 ; real_T
P_316 ; real_T P_317 [ 3 ] ; real_T P_318 ; real_T P_319 ; real_T P_320 ;
real_T P_321 [ 3 ] ; real_T P_322 ; real_T P_323 ; real_T P_324 ; real_T
P_325 [ 2 ] ; real_T P_326 [ 8 ] ; real_T P_327 [ 2 ] ; real_T P_329 [ 2 ] ;
real_T P_330 [ 2 ] ; real_T P_331 [ 2 ] ; real_T P_332 ; real_T P_333 [ 2 ] ;
real_T P_334 ; real_T P_335 [ 2 ] ; real_T P_337 [ 2 ] ; real_T P_338 [ 2 ] ;
real_T P_339 ; real_T P_340 ; real_T P_341 ; real_T P_342 ; real_T P_343 ;
real_T P_344 ; real_T P_345 ; real_T P_346 ; real_T P_347 ; real_T P_348 ;
real_T P_349 ; real_T P_350 ; real_T P_351 ; real_T P_352 ; real_T P_353 ;
real_T P_354 ; real_T P_355 ; real_T P_356 ; real_T P_357 ; real_T P_358 ;
real_T P_359 ; real_T P_360 ; real_T P_361 ; real_T P_362 ; real_T P_363 ;
real_T P_364 ; real_T P_365 [ 5 ] ; real_T P_366 [ 5 ] ; real_T P_367 ;
real_T P_368 ; real_T P_369 ; real_T P_370 ; real_T P_371 ; real_T P_372 ;
real_T P_373 ; real_T P_374 ; real_T P_375 ; real_T P_376 ; real_T P_377 ;
real_T P_378 ; real_T P_379 ; real_T P_380 [ 2 ] ; real_T P_381 [ 11 ] ;
real_T P_382 [ 2 ] ; real_T P_384 [ 2 ] ; real_T P_385 [ 2 ] ; real_T P_386 [
2 ] ; real_T P_387 ; real_T P_388 [ 2 ] ; real_T P_389 ; real_T P_390 [ 2 ] ;
real_T P_392 [ 2 ] ; real_T P_393 [ 2 ] ; real_T P_394 ; real_T P_395 ;
real_T P_396 ; real_T P_397 ; real_T P_398 ; real_T P_399 ; real_T P_400 ;
real_T P_401 ; real_T P_402 ; real_T P_403 ; real_T P_404 ; real_T P_405 ;
real_T P_406 ; real_T P_407 ; real_T P_408 ; real_T P_409 [ 5 ] ; real_T
P_410 [ 5 ] ; real_T P_411 ; real_T P_412 ; real_T P_413 ; real_T P_414 ;
real_T P_415 [ 40000 ] ; real_T P_416 [ 40000 ] ; real_T P_417 ; real_T P_418
[ 40000 ] ; real_T P_419 [ 40000 ] ; real_T P_420 ; real_T P_421 ; real_T
P_422 ; real_T P_423 [ 3 ] ; real_T P_424 ; real_T P_425 ; real_T P_426 ;
real_T P_427 ; real_T P_428 ; real_T P_429 ; real_T P_430 ; real_T P_431 ;
real_T P_432 ; real_T P_433 ; real_T P_434 ; real_T P_435 ; real_T P_436 ;
real_T P_437 ; real_T P_438 ; real_T P_439 ; real_T P_440 ; real_T P_441 ;
real_T P_442 ; real_T P_443 ; real_T P_444 ; real_T P_445 ; real_T P_446 ;
real_T P_447 ; real_T P_448 ; real_T P_449 ; real_T P_450 ; real_T P_451 ;
real_T P_452 ; real_T P_453 ; real_T P_454 ; real_T P_455 ; real_T P_456 ;
real_T P_457 ; real_T P_458 ; real_T P_459 ; real_T P_460 ; real_T P_461 ;
real_T P_462 ; real_T P_463 [ 3 ] ; real_T P_464 ; real_T P_465 ; real_T
P_466 ; real_T P_467 ; real_T P_468 [ 2 ] ; real_T P_469 [ 2 ] ; real_T P_470
; real_T P_471 [ 3 ] ; real_T P_472 ; real_T P_473 ; real_T P_474 ; real_T
P_475 ; real_T P_476 ; real_T P_477 ; real_T P_478 ; real_T P_479 ; real_T
P_480 ; real_T P_481 ; real_T P_482 ; real_T P_483 ; real_T P_484 ; real_T
P_485 ; real_T P_486 ; real_T P_487 ; real_T P_488 ; real_T P_489 ; real_T
P_490 ; real_T P_491 ; real_T P_492 ; real_T P_493 ; real_T P_494 ; real_T
P_495 ; real_T P_496 ; real_T P_497 ; real_T P_498 ; real_T P_499 ; real_T
P_500 ; real_T P_501 ; real_T P_502 ; real_T P_503 ; real_T P_504 ; real_T
P_505 ; real_T P_506 ; real_T P_507 ; real_T P_508 ; real_T P_509 ; real_T
P_510 ; real_T P_511 ; real_T P_512 ; real_T P_513 ; real_T P_514 ; real_T
P_515 ; real_T P_516 ; real_T P_517 ; real_T P_518 ; real_T P_519 ; real_T
P_520 ; real_T P_521 ; real_T P_522 ; real_T P_523 ; real_T P_524 ; real_T
P_525 ; real_T P_526 ; real_T P_527 ; real_T P_528 [ 5 ] ; real_T P_529 [ 5 ]
; real_T P_530 ; real_T P_531 ; real_T P_532 ; real_T P_533 ; real_T P_534 ;
real_T P_535 ; real_T P_536 ; real_T P_537 ; real_T P_538 ; real_T P_539 ;
real_T P_540 ; real_T P_541 ; real_T P_542 ; real_T P_543 ; real_T P_544 ;
real_T P_545 ; real_T P_546 ; real_T P_547 ; real_T P_548 ; real_T P_549 ;
real_T P_550 ; real_T P_551 ; real_T P_552 ; real_T P_553 ; real_T P_554 ;
real_T P_555 ; real_T P_556 ; real_T P_557 ; real_T P_558 ; real_T P_559 ;
real_T P_560 ; real_T P_561 ; real_T P_562 ; real_T P_563 ; real_T P_564 ;
real_T P_565 ; real_T P_566 ; real_T P_567 ; real_T P_568 ; real_T P_569 ;
real_T P_570 ; real_T P_571 ; real_T P_572 ; real_T P_573 ; real_T P_574 ;
real_T P_575 ; real_T P_576 ; real_T P_577 ; real_T P_578 [ 2 ] ; real_T
P_579 [ 2 ] ; real_T P_580 [ 2 ] ; real_T P_581 [ 2 ] ; real_T P_582 ; real_T
P_583 ; real_T P_584 ; real_T P_585 ; real_T P_586 ; real_T P_587 ; real_T
P_588 ; real_T P_589 ; real_T P_590 ; real_T P_591 ; real_T P_592 ; real_T
P_593 ; real_T P_594 ; real_T P_595 ; real_T P_596 ; real_T P_597 ; real_T
P_598 ; real_T P_599 ; real_T P_600 ; real_T P_601 ; real_T P_602 ; real_T
P_603 ; real_T P_604 ; real_T P_605 ; real_T P_606 ; real_T P_607 ; real_T
P_608 ; real_T P_609 ; real_T P_610 ; real_T P_611 ; } ; extern
P_uGrid_1PH_hd_caso2_T uGrid_1PH_hd_caso2_rtDefaultP ; extern const
ConstB_uGrid_1PH_hd_caso2_T uGrid_1PH_hd_caso2_rtInvariant ;
#endif
