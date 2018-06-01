#include "__cf_uGrid_1PH_hd.h"
#ifndef RTW_HEADER_uGrid_1PH_hd_acc_h_
#define RTW_HEADER_uGrid_1PH_hd_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef uGrid_1PH_hd_acc_COMMON_INCLUDES_
#define uGrid_1PH_hd_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "uGrid_1PH_hd_acc_types.h"
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
B_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_T ; typedef struct
{ void * Synthesized_Atomic_Subsystem_For_Alg_Loop_1_AlgLoopData ; }
DW_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_T ; typedef
struct { real_T B_35_0_0 ; real_T B_35_1_0 ; real_T B_35_2_0 ; real_T
B_35_3_0 ; real_T B_35_4_0 ; real_T B_35_5_0 ; real_T B_35_6_0 ; real_T
B_35_7_0 ; real_T B_35_11_0 ; real_T B_35_13_0 ; real_T B_35_14_0 ; real_T
B_35_15_0 ; real_T B_35_16_0 ; real_T B_35_19_0 ; real_T B_35_20_0 ; real_T
B_35_21_0 ; real_T B_35_22_0 ; real_T B_35_24_0 ; real_T B_35_27_0 ; real_T
B_35_29_0 ; real_T B_35_30_0 ; real_T B_35_31_0 ; real_T B_35_33_0 ; real_T
B_35_34_0 ; real_T B_35_36_0 ; real_T B_35_37_0 ; real_T B_35_38_0 ; real_T
B_35_39_0 ; real_T B_35_41_0 ; real_T B_35_44_0 ; real_T B_35_47_0 ; real_T
B_35_48_0 ; real_T B_35_49_0 ; real_T B_35_50_0 ; real_T B_35_55_0 ; real_T
B_35_56_0 ; real_T B_35_57_0 ; real_T B_35_58_0 ; real_T B_35_60_0 ; real_T
B_35_65_0 ; real_T B_35_66_0 ; real_T B_35_67_0 ; real_T B_35_68_0 ; real_T
B_35_70_0 ; real_T B_35_71_0 ; real_T B_35_72_0 ; real_T B_35_73_0 ; real_T
B_35_75_0 ; real_T B_35_76_0 ; real_T B_35_78_0 ; real_T B_35_81_0 ; real_T
B_35_95_0 ; real_T B_35_96_0 ; real_T B_35_97_0 ; real_T B_35_98_0 ; real_T
B_35_99_0 ; real_T B_35_100_0 ; real_T B_35_105_0 ; real_T B_35_106_0 ;
real_T B_35_130_0 ; real_T B_35_132_0 ; real_T B_35_133_0 ; real_T B_35_134_0
; real_T B_35_135_0 ; real_T B_35_136_0 ; real_T B_35_137_0 ; real_T
B_35_138_0 ; real_T B_35_139_0 ; real_T B_35_140_0 ; real_T B_35_141_0 ;
real_T B_35_142_0 ; real_T B_35_143_0 ; real_T B_35_144_0 ; real_T B_35_145_0
[ 11 ] ; real_T B_35_145_1 [ 54 ] ; real_T B_35_146_0 [ 10 ] ; real_T
B_35_146_1 [ 10 ] ; real_T B_35_149_0 ; real_T B_35_150_0 ; real_T B_35_151_0
; real_T B_35_152_0 ; real_T B_35_159_0 ; real_T B_35_160_0 ; real_T
B_35_163_0 ; real_T B_35_164_0 ; real_T B_35_166_0 [ 3 ] ; real_T B_35_166_1
; real_T B_35_166_2 ; real_T B_35_166_3 ; real_T B_35_168_0 ; real_T
B_35_172_0 ; real_T B_35_173_0 ; real_T B_35_174_0 ; real_T B_35_190_0 ;
real_T B_35_194_0 ; real_T B_35_198_0 ; real_T B_35_202_0 ; real_T B_35_210_0
; real_T B_35_211_0 ; real_T B_35_225_0 ; real_T B_35_227_0 ; real_T
B_35_230_0 ; real_T B_35_231_0 ; real_T B_35_232_0 ; real_T B_35_234_0 ;
real_T B_35_235_0 ; real_T B_35_236_0 ; real_T B_35_247_0 ; real_T B_35_251_0
; real_T B_35_252_0 ; real_T B_35_253_0 ; real_T B_35_269_0 ; real_T
B_35_273_0 ; real_T B_35_277_0 ; real_T B_35_281_0 ; real_T B_35_289_0 ;
real_T B_35_290_0 [ 3 ] ; real_T B_35_290_1 ; real_T B_35_290_2 ; real_T
B_35_290_3 ; real_T B_35_291_0 ; real_T B_35_305_0 ; real_T B_35_307_0 ;
real_T B_35_310_0 ; real_T B_35_311_0 ; real_T B_35_312_0 ; real_T B_35_314_0
; real_T B_35_315_0 ; real_T B_35_316_0 ; real_T B_35_329_0 [ 2 ] ; real_T
B_35_330_0 [ 2 ] ; real_T B_35_331_0 [ 200 ] ; real_T B_35_332_0 [ 2 ] ;
real_T B_35_333_0 [ 40000 ] ; real_T B_35_334_0 [ 40000 ] ; real_T B_35_336_0
[ 200 ] ; real_T B_35_336_1 ; real_T B_35_336_2 ; real_T B_35_336_3 ; real_T
B_35_342_0 ; real_T B_35_347_0 [ 40000 ] ; real_T B_35_348_0 [ 40000 ] ;
real_T B_35_349_0 [ 2 ] ; real_T B_35_350_0 [ 2 ] ; real_T B_35_351_0 [ 200 ]
; real_T B_35_352_0 [ 2 ] ; real_T B_35_354_0 [ 200 ] ; real_T B_35_354_1 ;
real_T B_35_354_2 ; real_T B_35_354_3 ; real_T B_35_356_0 ; real_T B_35_357_0
; real_T B_35_358_0 ; real_T B_35_360_0 ; real_T B_35_363_0 ; real_T
B_35_365_0 ; real_T B_35_367_0 ; real_T B_35_368_0 ; real_T B_35_371_0 ;
real_T B_35_373_0 ; real_T B_35_375_0 ; real_T B_35_378_0 ; real_T B_35_381_0
; real_T B_35_383_0 ; real_T B_35_385_0 ; real_T B_35_386_0 ; real_T
B_35_389_0 ; real_T B_35_391_0 ; real_T B_35_393_0 ; real_T B_35_403_0 ;
real_T B_35_405_0 ; real_T B_35_407_0 ; real_T B_35_409_0 ; real_T B_35_410_0
; real_T B_35_411_0 ; real_T B_35_412_0 ; real_T B_35_413_0 ; real_T
B_35_414_0 ; real_T B_35_415_0 ; real_T B_35_416_0 ; real_T B_35_417_0 ;
real_T B_35_419_0 ; real_T B_35_421_0 ; real_T B_35_422_0 ; real_T B_35_424_0
; real_T B_35_426_0 ; real_T B_35_428_0 ; real_T B_35_429_0 ; real_T
B_35_430_0 ; real_T B_35_431_0 ; real_T B_35_433_0 ; real_T B_35_435_0 ;
real_T B_35_436_0 ; real_T B_35_437_0 ; real_T B_35_438_0 ; real_T B_35_440_0
; real_T B_35_442_0 ; real_T B_35_443_0 ; real_T B_35_444_0 ; real_T
B_35_445_0 ; real_T B_35_447_0 ; real_T B_35_451_0 ; real_T B_35_452_0 ;
real_T B_35_453_0 ; real_T B_35_457_0 ; real_T B_35_461_0 ; real_T B_35_474_0
; real_T B_35_478_0 ; real_T B_35_482_0 ; real_T B_35_486_0 ; real_T
B_35_494_0 ; real_T B_35_495_0 ; real_T B_35_509_0 ; real_T B_35_511_0 ;
real_T B_35_514_0 ; real_T B_35_515_0 ; real_T B_35_516_0 ; real_T B_35_518_0
; real_T B_35_519_0 ; real_T B_35_520_0 ; real_T B_35_535_0 ; real_T
B_35_537_0 ; real_T B_35_539_0 ; real_T B_35_541_0 ; real_T B_35_547_0 ;
real_T B_35_550_0 ; real_T B_35_552_0 ; real_T B_35_553_0 ; real_T B_35_554_0
; real_T B_35_565_0 ; real_T B_35_569_0 ; real_T B_35_570_0 ; real_T
B_35_571_0 ; real_T B_35_572_0 ; real_T B_35_574_0 ; real_T B_35_576_0 ;
real_T B_35_577_0 ; real_T B_35_578_0 ; real_T B_35_579_0 ; real_T B_35_583_0
; real_T B_35_585_0 ; real_T B_35_586_0 ; real_T B_35_588_0 ; real_T
B_35_589_0 ; real_T B_35_590_0 ; real_T B_35_591_0 ; real_T B_35_595_0 ;
real_T B_35_597_0 ; real_T B_35_598_0 [ 2 ] ; real_T B_35_599_0 [ 2 ] ;
real_T B_35_601_0 [ 2 ] ; real_T B_35_601_1 ; real_T B_35_601_2 ; real_T
B_35_601_3 ; real_T B_35_604_0 ; real_T B_35_605_0 [ 2 ] ; real_T B_35_606_0
[ 2 ] ; real_T B_35_608_0 [ 2 ] ; real_T B_35_608_1 ; real_T B_35_608_2 ;
real_T B_35_608_3 ; real_T B_35_610_0 ; real_T B_35_612_0 ; real_T B_35_613_0
; real_T B_35_614_0 ; real_T B_35_615_0 ; real_T B_35_617_0 ; real_T
B_35_619_0 ; real_T B_35_620_0 ; real_T B_35_621_0 ; real_T B_35_622_0 ;
real_T B_35_630_0 ; real_T B_35_631_0 ; real_T B_35_632_0 ; real_T B_35_633_0
; real_T B_35_634_0 ; real_T B_35_635_0 ; real_T B_35_636_0 ; real_T
B_35_640_0 ; real_T B_35_641_0 ; real_T B_35_642_0 ; real_T B_35_643_0 ;
real_T B_35_644_0 ; real_T B_35_645_0 ; real_T B_35_646_0 ; real_T B_35_647_0
; real_T B_35_648_0 ; real_T B_34_0_0 ; real_T B_33_0_0 ; real_T B_32_0_0 ;
real_T B_31_0_0 ; real_T B_30_0_0 ; real_T B_29_0_0 [ 2 ] ; real_T B_29_0_1 ;
real_T B_29_0_2 ; real_T B_29_0_3 ; real_T B_29_0_4 ; real_T B_29_0_5 ;
real_T B_29_0_6 ; real_T B_28_0_0 [ 2 ] ; real_T B_28_0_1 ; real_T B_28_0_2 ;
real_T B_28_0_3 ; real_T B_28_0_4 ; real_T B_28_0_5 ; real_T B_28_0_6 ;
real_T B_27_0_0 [ 2 ] ; real_T B_27_0_1 ; real_T B_27_0_2 ; real_T B_27_0_3 ;
real_T B_27_0_4 ; real_T B_27_0_5 ; real_T B_27_0_6 ; real_T B_26_0_0 ;
real_T B_26_0_1 ; real_T B_26_0_2 ; real_T B_26_0_3 ; real_T B_26_0_4 ;
real_T B_26_0_5 ; real_T B_26_0_6 ; real_T B_25_0_0 ; real_T B_25_0_1 ;
real_T B_25_0_2 ; real_T B_25_0_3 ; real_T B_25_0_4 ; real_T B_25_0_5 ;
real_T B_25_0_6 ; real_T B_20_0_1 [ 4 ] ; real_T B_20_0_2 [ 2 ] ; real_T
B_20_0_3 [ 2 ] ; real_T B_20_0_4 [ 2 ] ; real_T B_20_0_5 [ 2 ] ; real_T
B_20_0_6 ; real_T B_20_0_7 ; real_T B_19_0_1 [ 4 ] ; real_T B_19_0_2 [ 2 ] ;
real_T B_19_0_3 [ 2 ] ; real_T B_19_0_4 [ 2 ] ; real_T B_19_0_5 [ 2 ] ;
real_T B_19_0_6 ; real_T B_19_0_7 ; real_T B_18_0_1 [ 2 ] ; real_T B_18_0_2 [
200 ] ; real_T B_17_0_1 [ 40000 ] ; real_T B_17_0_2 [ 200 ] ; real_T B_17_0_3
[ 40000 ] ; real_T B_17_0_4 [ 200 ] ; real_T B_17_0_5 [ 200 ] ; real_T
B_17_0_6 [ 200 ] ; real_T B_17_0_7 [ 200 ] ; real_T B_16_0_1 [ 2 ] ; real_T
B_16_0_2 [ 200 ] ; real_T B_15_0_1 [ 40000 ] ; real_T B_15_0_2 [ 200 ] ;
real_T B_15_0_3 [ 40000 ] ; real_T B_15_0_4 [ 200 ] ; real_T B_15_0_5 [ 200 ]
; real_T B_15_0_6 [ 200 ] ; real_T B_15_0_7 [ 200 ] ; real_T B_14_0_0 ;
real_T B_13_0_0 ; real_T B_12_0_0 ; real_T B_10_0_0 [ 4 ] ; real_T B_9_0_0 [
4 ] ; real_T B_8_0_0 [ 4 ] ; real_T B_7_0_0 [ 4 ] ; real_T B_3_0_1 ; real_T
B_2_0_1 ; real_T B_1_0_1 ; boolean_T B_35_23_0 ; boolean_T B_35_25_0 ;
boolean_T B_35_40_0 ; boolean_T B_35_42_0 ; boolean_T B_35_77_0 ; boolean_T
B_35_79_0 ; char_T pad_B_35_79_0 [ 2 ] ;
B_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ; } B_uGrid_1PH_hd_T ; typedef
struct { real_T itinit1_PreviousInput ; real_T itinit_PreviousInput ; real_T
TimeStampA ; real_T LastUAtTimeA ; real_T TimeStampB ; real_T LastUAtTimeB ;
real_T TimeStampA_k ; real_T LastUAtTimeA_m ; real_T TimeStampB_f ; real_T
LastUAtTimeB_o ; real_T Memory1_PreviousInput [ 200 ] ; real_T
Memory2_PreviousInput [ 2 ] ; real_T Memory3_PreviousInput [ 200 ] ; real_T
Memory4_PreviousInput [ 2 ] ; real_T Memory_PreviousInput ; real_T
Memory_PreviousInput_f ; real_T Memory_PreviousInput_p ; real_T
Memory_PreviousInput_k ; real_T TimeStampA_b ; real_T LastUAtTimeA_f ; real_T
TimeStampB_a ; real_T LastUAtTimeB_n ; real_T nextTime ; real_T nextTime_e ;
real_T nextTime_f ; real_T TimeStampA_n ; real_T LastUAtTimeA_ma ; real_T
TimeStampB_m ; real_T LastUAtTimeB_g ; real_T nextTime_j ; real_T nextTime_l
; int64_T numCompleteCycles ; int64_T numCompleteCycles_j ; int64_T
numCompleteCycles_o ; int64_T numCompleteCycles_h ; int64_T
numCompleteCycles_hh ; real_T StateSpace_RWORK [ 2 ] ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_n ; struct { real_T modelTStart ; }
TransportDelay_RWORK_m ; struct { real_T modelTStart ; }
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
Scope6_PWORK ; void * Scope7_PWORK [ 2 ] ; void * Scope7_PWORK_k [ 2 ] ; void
* Scope8_PWORK [ 2 ] ; void * Scope10_PWORK ; void * Scope11_PWORK ; void *
Scope8_PWORK_i ; void * qpOASES_linprog1_PWORK [ 8 ] ; void * Scope12_PWORK ;
void * Scope16_PWORK [ 2 ] ; void * qpOASES_linprog_PWORK [ 8 ] ; void *
Scope9_PWORK ; void * Scope_PWORK_k ; void * Scope1_PWORK_gi ; void *
Scope14_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
MotordeCombustin1_PWORK ; void * Scope5_PWORK_l ; int32_T justEnabled ;
int32_T currentValue ; int32_T justEnabled_l ; int32_T currentValue_d ;
int32_T justEnabled_k ; int32_T currentValue_a ; int32_T justEnabled_j ;
int32_T currentValue_n ; int32_T justEnabled_o ; int32_T currentValue_f ;
int_T inti_IWORK ; int_T StateSpace_IWORK [ 23 ] ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_h ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_j ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_a ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } MotordeCombustin1_IWORK ;
int_T inti_MODE ; char StateSpace_MODE [ 112 ] ; int_T Step_MODE ; int_T
Step_MODE_c ; int_T Step_MODE_f ; int_T Saturation_MODE ; int_T Abs_MODE ;
int_T Abs_MODE_d ; int_T Abs1_MODE ; int8_T Subsystem_SubsysRanBC ; int8_T
Subsystem_SubsysRanBC_d ; int8_T Subsystem_SubsysRanBC_e ; int8_T
Subsystem_SubsysRanBC_j ; int8_T Subsystem_SubsysRanBC_eb ; int8_T
Subsystem_SubsysRanBC_o ; int8_T Subsystem_SubsysRanBC_p ; int8_T
Subsystem_SubsysRanBC_l ; int8_T Subsystem_SubsysRanBC_b ; int8_T
Subsystem_SubsysRanBC_g ; boolean_T Compare_Mode ; boolean_T LowerRelop1_Mode
; boolean_T UpperRelop_Mode ; boolean_T LowerRelop1_Mode_g ; boolean_T
UpperRelop_Mode_g ; boolean_T Compare_Mode_k ; boolean_T LowerRelop1_Mode_c ;
boolean_T UpperRelop_Mode_gu ; boolean_T Compare_Mode_i ; boolean_T
Compare_Mode_e ;
DW_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_uGrid_1PH_hd_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ; } DW_uGrid_1PH_hd_T ; typedef
struct { real_T Dinmicaeneleje1_CSTATE ; real_T TransferFcn_CSTATE ; real_T
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
real_T Integrator_CSTATE ; } X_uGrid_1PH_hd_T ; typedef struct { real_T
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
real_T Integrator_CSTATE ; } XDot_uGrid_1PH_hd_T ; typedef struct { boolean_T
Dinmicaeneleje1_CSTATE ; boolean_T TransferFcn_CSTATE ; boolean_T
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
XDis_uGrid_1PH_hd_T ; typedef struct { real_T Dinmicaeneleje1_CSTATE ; real_T
TransferFcn_CSTATE ; real_T Currentfilter_CSTATE ; real_T inti_CSTATE ;
real_T StateSpace_CSTATE ; real_T Integrator2_CSTATE ; real_T
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
CStateAbsTol_uGrid_1PH_hd_T ; typedef struct { real_T Compare_RelopInput_ZC ;
real_T inti_Reset_ZC ; real_T inti_IntgUpLimit_ZC ; real_T
inti_IntgLoLimit_ZC ; real_T inti_LeaveSaturate_ZC ; real_T
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
Subsystem_Trig_ZC_p ; real_T Subsystem_Trig_ZC_i ; real_T Subsystem_Trig_ZC_a
; real_T Subsystem_Trig_ZC_b ; real_T Subsystem_Trig_ZC_o ; real_T
Subsystem_Trig_ZC_j ; real_T Subsystem_Trig_ZC_h ; real_T
Subsystem_Trig_ZC_od ; real_T Subsystem_Trig_ZC_iu ; } ZCV_uGrid_1PH_hd_T ;
typedef struct { ZCSigState Compare_RelopInput_ZCE ; ZCSigState
inti_Reset_ZCE ; ZCSigState inti_IntgUpLimit_ZCE ; ZCSigState
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
Subsystem_Trig_ZCE ; ZCSigState Subsystem_Trig_ZCE_d ; ZCSigState
Subsystem_Trig_ZCE_o ; ZCSigState Subsystem_Trig_ZCE_a ; ZCSigState
Subsystem_Trig_ZCE_i ; ZCSigState Subsystem_Trig_ZCE_k ; ZCSigState
Subsystem_Trig_ZCE_in ; ZCSigState Subsystem_Trig_ZCE_d4 ; ZCSigState
Subsystem_Trig_ZCE_e ; ZCSigState Subsystem_Trig_ZCE_at ; }
PrevZCX_uGrid_1PH_hd_T ; typedef struct { const real_T B_35_17_0 ; const
real_T B_35_45_0 ; const real_T B_35_212_0 ; const real_T B_35_292_0 ; const
real_T B_35_496_0 ; const real_T B_35_566_0 ; const real_T B_35_580_0 ; }
ConstB_uGrid_1PH_hd_T ;
#define uGrid_1PH_hd_rtC(S) ((ConstB_uGrid_1PH_hd_T *) _ssGetConstBlockIO(S))
struct P_uGrid_1PH_hd_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3
; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9
; real_T P_10 ; real_T P_11 ; real_T P_12 [ 2 ] ; real_T P_13 ; real_T P_14 [
2 ] ; real_T P_15 ; real_T P_16 [ 2 ] ; real_T P_17 ; real_T P_18 ; real_T
P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ;
real_T P_25 ; real_T P_26 [ 2 ] ; real_T P_27 ; real_T P_28 [ 2 ] ; real_T
P_29 ; real_T P_30 [ 2 ] ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T
P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ;
real_T P_40 [ 2 ] ; real_T P_41 ; real_T P_42 [ 2 ] ; real_T P_43 ; real_T
P_44 [ 2 ] ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T
P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 [
2 ] ; real_T P_55 ; real_T P_56 [ 2 ] ; real_T P_57 ; real_T P_58 [ 2 ] ;
real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T
P_64 ; real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 [ 2 ] ; real_T
P_69 ; real_T P_70 [ 2 ] ; real_T P_71 ; real_T P_72 [ 2 ] ; real_T P_73 ;
real_T P_74 ; real_T P_75 [ 2 ] ; real_T P_76 ; real_T P_77 [ 2 ] ; real_T
P_78 ; real_T P_79 [ 2 ] ; real_T P_80 ; real_T P_81 [ 2 ] ; real_T P_82 ;
real_T P_83 ; real_T P_84 [ 2 ] ; real_T P_85 ; real_T P_86 [ 2 ] ; real_T
P_87 ; real_T P_88 [ 2 ] ; real_T P_89 ; real_T P_90 [ 2 ] ; real_T P_91 ;
real_T P_92 ; real_T P_93 [ 2 ] ; real_T P_94 ; real_T P_95 [ 2 ] ; real_T
P_96 ; real_T P_97 [ 2 ] ; real_T P_98 ; real_T P_99 [ 2 ] ; real_T P_100 ;
real_T P_101 ; real_T P_102 [ 2 ] ; real_T P_103 ; real_T P_104 [ 2 ] ;
real_T P_105 ; real_T P_106 [ 2 ] ; real_T P_107 ; real_T P_108 [ 2 ] ;
real_T P_109 ; real_T P_110 ; real_T P_111 [ 2 ] ; real_T P_112 ; real_T
P_113 [ 2 ] ; real_T P_114 ; real_T P_115 [ 2 ] ; real_T P_116 ; real_T P_117
[ 2 ] ; real_T P_118 ; real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T
P_122 ; real_T P_123 ; real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T
P_127 ; real_T P_128 ; real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T
P_132 ; real_T P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 ; real_T
P_137 ; real_T P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T
P_142 ; real_T P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T
P_147 ; real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T
P_152 ; real_T P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T
P_157 ; real_T P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ; real_T
P_162 ; real_T P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ; real_T
P_167 ; real_T P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T
P_172 ; real_T P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T
P_177 ; real_T P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ; real_T
P_182 ; real_T P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ; real_T
P_187 ; real_T P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ; real_T
P_192 ; real_T P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T
P_197 ; real_T P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ; real_T
P_202 ; real_T P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T
P_207 ; real_T P_208 [ 2 ] ; real_T P_209 [ 8496 ] ; real_T P_210 [ 2 ] ;
real_T P_211 [ 4 ] ; real_T P_212 [ 2 ] ; real_T P_213 [ 21 ] ; real_T P_214
[ 2 ] ; real_T P_215 [ 7200 ] ; real_T P_216 [ 2 ] ; real_T P_217 [ 54 ] ;
real_T P_218 [ 2 ] ; real_T P_219 [ 27 ] ; real_T P_220 [ 2 ] ; real_T P_221
[ 27 ] ; real_T P_222 [ 2 ] ; real_T P_223 [ 27 ] ; real_T P_224 [ 2 ] ;
real_T P_225 ; real_T P_226 [ 2 ] ; real_T P_227 ; real_T P_228 [ 2 ] ;
real_T P_229 ; real_T P_230 [ 2 ] ; real_T P_231 ; real_T P_232 [ 2 ] ;
real_T P_233 ; real_T P_234 [ 2 ] ; real_T P_235 ; real_T P_236 [ 2 ] ;
real_T P_237 ; real_T P_238 [ 2 ] ; real_T P_239 ; real_T P_240 [ 2 ] ;
real_T P_241 [ 2 ] ; real_T P_242 [ 2 ] ; real_T P_243 ; real_T P_244 [ 2 ] ;
real_T P_245 [ 3 ] ; real_T P_246 [ 2 ] ; real_T P_247 ; real_T P_248 [ 2 ] ;
real_T P_249 ; real_T P_250 [ 2 ] ; real_T P_251 ; real_T P_252 [ 2 ] ;
real_T P_253 ; real_T P_254 [ 2 ] ; real_T P_255 ; real_T P_256 [ 2 ] ;
real_T P_257 ; real_T P_258 [ 2 ] ; real_T P_259 ; real_T P_260 [ 2 ] ;
real_T P_261 ; real_T P_262 [ 2 ] ; real_T P_263 ; real_T P_264 [ 2 ] ;
real_T P_265 ; real_T P_266 [ 2 ] ; real_T P_267 ; real_T P_268 [ 2 ] ;
real_T P_269 ; real_T P_270 [ 7 ] ; real_T P_271 ; real_T P_272 ; real_T
P_273 ; real_T P_274 [ 7 ] ; real_T P_275 ; real_T P_276 ; real_T P_277 ;
real_T P_278 [ 7 ] ; real_T P_279 ; real_T P_280 ; real_T P_281 ; real_T
P_282 [ 7 ] ; real_T P_283 ; real_T P_284 ; real_T P_285 ; real_T P_286 [ 3 ]
; real_T P_287 ; real_T P_288 ; real_T P_289 ; real_T P_290 [ 3 ] ; real_T
P_291 ; real_T P_292 ; real_T P_293 ; real_T P_294 [ 3 ] ; real_T P_295 ;
real_T P_296 ; real_T P_297 ; real_T P_298 [ 3 ] ; real_T P_299 ; real_T
P_300 ; real_T P_301 ; real_T P_302 [ 2 ] ; real_T P_303 [ 8 ] ; real_T P_304
[ 2 ] ; real_T P_305 ; real_T P_306 [ 2 ] ; real_T P_307 [ 2 ] ; real_T P_308
[ 2 ] ; real_T P_309 ; real_T P_310 [ 2 ] ; real_T P_311 ; real_T P_312 [ 2 ]
; real_T P_314 [ 2 ] ; real_T P_315 [ 2 ] ; real_T P_316 ; real_T P_317 ;
real_T P_318 ; real_T P_319 ; real_T P_320 ; real_T P_321 ; real_T P_322 ;
real_T P_323 ; real_T P_324 ; real_T P_325 ; real_T P_326 ; real_T P_327 ;
real_T P_328 ; real_T P_329 ; real_T P_330 ; real_T P_331 ; real_T P_332 ;
real_T P_333 ; real_T P_334 ; real_T P_335 ; real_T P_336 ; real_T P_337 ;
real_T P_338 ; real_T P_339 ; real_T P_340 ; real_T P_341 ; real_T P_342 [ 5
] ; real_T P_343 [ 5 ] ; real_T P_344 ; real_T P_345 ; real_T P_346 ; real_T
P_347 ; real_T P_348 ; real_T P_349 ; real_T P_350 ; real_T P_351 ; real_T
P_352 ; real_T P_353 ; real_T P_354 ; real_T P_355 ; real_T P_356 ; real_T
P_357 [ 2 ] ; real_T P_358 [ 11 ] ; real_T P_359 [ 2 ] ; real_T P_361 [ 2 ] ;
real_T P_362 [ 2 ] ; real_T P_363 [ 2 ] ; real_T P_364 ; real_T P_365 [ 2 ] ;
real_T P_366 ; real_T P_367 [ 2 ] ; real_T P_369 [ 2 ] ; real_T P_370 [ 2 ] ;
real_T P_371 ; real_T P_372 ; real_T P_373 ; real_T P_374 ; real_T P_375 ;
real_T P_376 ; real_T P_377 ; real_T P_378 ; real_T P_379 ; real_T P_380 ;
real_T P_381 ; real_T P_382 ; real_T P_383 ; real_T P_384 ; real_T P_385 ;
real_T P_386 [ 5 ] ; real_T P_387 [ 5 ] ; real_T P_388 ; real_T P_389 ;
real_T P_390 ; real_T P_391 ; real_T P_392 [ 40000 ] ; real_T P_393 [ 40000 ]
; real_T P_394 ; real_T P_395 [ 40000 ] ; real_T P_396 [ 40000 ] ; real_T
P_397 ; real_T P_398 ; real_T P_399 ; real_T P_400 [ 3 ] ; real_T P_401 ;
real_T P_402 ; real_T P_403 ; real_T P_404 ; real_T P_405 ; real_T P_406 ;
real_T P_407 ; real_T P_408 ; real_T P_409 ; real_T P_410 ; real_T P_411 ;
real_T P_412 ; real_T P_413 ; real_T P_414 ; real_T P_415 ; real_T P_416 ;
real_T P_417 ; real_T P_418 ; real_T P_419 ; real_T P_420 ; real_T P_421 ;
real_T P_422 ; real_T P_423 ; real_T P_424 ; real_T P_425 ; real_T P_426 ;
real_T P_427 ; real_T P_428 ; real_T P_429 ; real_T P_430 ; real_T P_431 ;
real_T P_432 ; real_T P_433 ; real_T P_434 ; real_T P_435 ; real_T P_436 ;
real_T P_437 ; real_T P_438 ; real_T P_439 ; real_T P_440 [ 3 ] ; real_T
P_441 ; real_T P_442 ; real_T P_443 ; real_T P_444 ; real_T P_445 [ 2 ] ;
real_T P_446 [ 2 ] ; real_T P_447 ; real_T P_448 [ 3 ] ; real_T P_449 ;
real_T P_450 ; real_T P_451 ; real_T P_452 ; real_T P_453 ; real_T P_454 ;
real_T P_455 ; real_T P_456 ; real_T P_457 ; real_T P_458 ; real_T P_459 ;
real_T P_460 ; real_T P_461 ; real_T P_462 ; real_T P_463 ; real_T P_464 ;
real_T P_465 ; real_T P_466 ; real_T P_467 ; real_T P_468 ; real_T P_469 ;
real_T P_470 ; real_T P_471 ; real_T P_472 ; real_T P_473 ; real_T P_474 ;
real_T P_475 ; real_T P_476 ; real_T P_477 ; real_T P_478 ; real_T P_479 ;
real_T P_480 ; real_T P_481 ; real_T P_482 ; real_T P_483 ; real_T P_484 ;
real_T P_485 ; real_T P_486 ; real_T P_487 ; real_T P_488 ; real_T P_489 ;
real_T P_490 ; real_T P_491 ; real_T P_492 ; real_T P_493 ; real_T P_494 ;
real_T P_495 ; real_T P_496 ; real_T P_497 ; real_T P_498 ; real_T P_499 ;
real_T P_500 ; real_T P_501 ; real_T P_502 ; real_T P_503 ; real_T P_504 ;
real_T P_505 [ 5 ] ; real_T P_506 [ 5 ] ; real_T P_507 ; real_T P_508 ;
real_T P_509 ; real_T P_510 ; real_T P_511 ; real_T P_512 ; real_T P_513 ;
real_T P_514 ; real_T P_515 ; real_T P_516 ; real_T P_517 ; real_T P_518 ;
real_T P_519 ; real_T P_520 ; real_T P_521 ; real_T P_522 ; real_T P_523 ;
real_T P_524 ; real_T P_525 ; real_T P_526 ; real_T P_527 ; real_T P_528 ;
real_T P_529 ; real_T P_530 ; real_T P_531 ; real_T P_532 ; real_T P_533 ;
real_T P_534 ; real_T P_535 ; real_T P_536 ; real_T P_537 ; real_T P_538 ;
real_T P_539 ; real_T P_540 ; real_T P_541 ; real_T P_542 ; real_T P_543 ;
real_T P_544 ; real_T P_545 ; real_T P_546 ; real_T P_547 ; real_T P_548 [ 2
] ; real_T P_549 [ 2 ] ; real_T P_550 ; real_T P_551 [ 2 ] ; real_T P_552 [ 2
] ; real_T P_553 ; real_T P_554 ; real_T P_555 ; real_T P_556 ; real_T P_557
; real_T P_558 ; real_T P_559 ; real_T P_560 ; real_T P_561 ; real_T P_562 ;
real_T P_563 ; real_T P_564 ; real_T P_565 ; real_T P_566 ; real_T P_567 ;
real_T P_568 ; real_T P_569 ; real_T P_570 ; real_T P_571 ; real_T P_572 ;
real_T P_573 ; real_T P_574 ; real_T P_575 ; real_T P_576 ; real_T P_577 ;
real_T P_578 ; real_T P_579 ; real_T P_580 ; real_T P_581 ; real_T P_582 ; }
; extern P_uGrid_1PH_hd_T uGrid_1PH_hd_rtDefaultP ; extern const
ConstB_uGrid_1PH_hd_T uGrid_1PH_hd_rtInvariant ;
#endif
