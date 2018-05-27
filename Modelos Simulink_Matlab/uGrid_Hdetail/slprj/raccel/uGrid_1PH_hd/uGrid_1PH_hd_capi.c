#include "__cf_uGrid_1PH_hd.h"
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "uGrid_1PH_hd_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "uGrid_1PH_hd.h"
#include "uGrid_1PH_hd_capi.h"
#include "uGrid_1PH_hd_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 4 , TARGET_STRING (
"uGrid_1PH_hd/LinearProg" ) , TARGET_STRING ( "bio" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 1 , 4 , TARGET_STRING ( "uGrid_1PH_hd/LinearProg" ) , TARGET_STRING ( "die"
) , 1 , 0 , 0 , 0 , 0 } , { 2 , 0 , TARGET_STRING ( "uGrid_1PH_hd/P_lp_bio" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 3 , 0 , TARGET_STRING (
"uGrid_1PH_hd/P_lp_diesel" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , {
4 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Sine Wave" ) , TARGET_STRING ( "Vc_ref"
) , 0 , 0 , 0 , 0 , 2 } , { 5 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Hw1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 6 , 0 , TARGET_STRING (
"uGrid_1PH_hd/Hw2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 7 , 0 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
2 } , { 8 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Hw4" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 2 } , { 9 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Hw5" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 10 , 0 , TARGET_STRING (
"uGrid_1PH_hd/Hw6" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 11 , 0
, TARGET_STRING ( "uGrid_1PH_hd/Hw7" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 2 } , { 12 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Step1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 3 } , { 13 , 0 , TARGET_STRING ( "uGrid_1PH_hd/Step2"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 14 , 0 , TARGET_STRING (
"uGrid_1PH_hd/Step3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 15 ,
1 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio/not_pwm" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 4 } , { 16 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Step" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 3 } , { 17 , 0 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio/Sum2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 18 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 19 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 20 , 2 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/not_pwm" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 4 } , { 21 , 0 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio1/Step"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 22 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 2 } , { 23 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 24 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 25 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn2" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 2 } , { 26 , 3 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/not_pwm" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 4 } , { 27 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Step" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 3 } , { 28 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 3 } , { 29 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 30 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn1" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 31 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/Hw2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
2 } , { 32 , 0 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_BIO/Hw6" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 33 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/Hw1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 2 } , { 34 , 0 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_DIESEL/Hw3" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 35 , 0 , TARGET_STRING (
"uGrid_1PH_hd/I sens A/do not delete this gain" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 2 } , { 36 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 0 , 0 ,
1 , 0 , 0 } , { 37 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 1 , 0 ,
2 , 0 , 0 } , { 38 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 2 , 0 ,
1 , 0 , 0 } , { 39 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 3 , 0 ,
2 , 0 , 0 } , { 40 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 4 , 0 ,
2 , 0 , 0 } , { 41 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 5 , 0 ,
2 , 0 , 0 } , { 42 , 5 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc" ) , TARGET_STRING ( "" ) , 6 , 0 ,
2 , 0 , 0 } , { 43 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 0 , 0 ,
1 , 0 , 0 } , { 44 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 1 , 0 ,
2 , 0 , 0 } , { 45 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 2 , 0 ,
1 , 0 , 0 } , { 46 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 3 , 0 ,
2 , 0 , 0 } , { 47 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 4 , 0 ,
2 , 0 , 0 } , { 48 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 5 , 0 ,
2 , 0 , 0 } , { 49 , 6 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_MatCalc1" ) , TARGET_STRING ( "" ) , 6 , 0 ,
2 , 0 , 0 } , { 50 , 7 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_OutLogic" ) , TARGET_STRING (
"mpc__out_biogen" ) , 0 , 0 , 3 , 0 , 0 } , { 51 , 7 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_OutLogic" ) , TARGET_STRING (
"Delta_U_bio_gen" ) , 1 , 0 , 4 , 0 , 0 } , { 52 , 8 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_OutLogic1" ) , TARGET_STRING ( "mpc__out" )
, 0 , 0 , 3 , 0 , 0 } , { 53 , 8 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/MPC_OutLogic1" ) , TARGET_STRING ( "Delta_U" ) ,
1 , 0 , 4 , 0 , 0 } , { 54 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/Memory1" ) , TARGET_STRING ( "" ) , 0 , 0 , 4 ,
0 , 3 } , { 55 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/Memory2" )
, TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 3 } , { 56 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/Memory3" ) , TARGET_STRING ( "" ) , 0 , 0 , 4 ,
0 , 3 } , { 57 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/Memory4" )
, TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 3 } , { 58 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/rt1" ) , TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 ,
0 } , { 59 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/rt3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 0 } , { 60 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/qpOASES" ) , TARGET_STRING ( "" ) , 0 , 0 , 4 ,
0 , 0 } , { 61 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/qpOASES" )
, TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 62 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/qpOASES" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 ,
0 , 0 } , { 63 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/qpOASES" )
, TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 , 0 } , { 64 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/qpOASES1" ) , TARGET_STRING ( "" ) , 0 , 0 , 4 ,
0 , 0 } , { 65 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/qpOASES1" )
, TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 66 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/qpOASES1" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 ,
0 , 0 } , { 67 , 0 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/qpOASES1" )
, TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 , 0 } , { 68 , 0 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Derivative" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 2 } , { 69 , 0 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Product1"
) , TARGET_STRING ( "Capacitor_ref_current" ) , 0 , 0 , 0 , 0 , 2 } , { 70 ,
0 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 2 } , { 71 , 0 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Sum6" ) , TARGET_STRING ( "Inductor_refCurrent"
) , 0 , 0 , 0 , 0 , 2 } , { 72 , 0 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Sum7" ) , TARGET_STRING (
"Measured_Inductor_Current" ) , 0 , 0 , 0 , 0 , 2 } , { 73 , 0 ,
TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Sum8" ) , TARGET_STRING (
"InductorErrorCurrent" ) , 0 , 0 , 0 , 0 , 2 } , { 74 , 0 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Sum9" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
2 } , { 75 , 0 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Transfer Fcn1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 76 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 77 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper1/Product" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 4 } , { 78 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper3/Product" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 4 } , { 79 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 80 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 81 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/I sens A1/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 82 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper1/Product" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 4 } , { 83 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper3/Product" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 4 } , { 84 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 85 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 86 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper1/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 4 } , { 87 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper3/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 4 } , { 88 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 89 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/Energy" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 90 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "" )
, 0 , 0 , 5 , 0 , 3 } , { 91 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "" )
, 1 , 0 , 0 , 0 , 3 } , { 92 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "" )
, 2 , 0 , 0 , 0 , 3 } , { 93 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "" )
, 3 , 0 , 0 , 0 , 3 } , { 94 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/Energy" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 95 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "" ) , 0 , 0 , 5 , 0 , 3 } , { 96 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "" ) , 1 , 0 , 0 , 0 , 3 } , { 97 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "" ) , 2 , 0 , 0 , 0 , 3 } , { 98 , 0 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "" ) , 3 , 0 , 0 , 0 , 3 } , { 99 , 0 , TARGET_STRING (
"uGrid_1PH_hd/DC 540V/Model/DC" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1
} , { 100 , 0 , TARGET_STRING ( "uGrid_1PH_hd/DC_1/Model/DC" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 101 , 0 , TARGET_STRING (
"uGrid_1PH_hd/DC_2/Model/DC" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } ,
{ 102 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/Energy" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 103 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING ( ""
) , 0 , 0 , 6 , 0 , 3 } , { 104 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 3 } , { 105 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 3 } , { 106 , 0 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING ( ""
) , 3 , 0 , 0 , 0 , 3 } , { 107 , 0 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "" )
, 0 , 0 , 7 , 0 , 2 } , { 108 , 0 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "" )
, 1 , 0 , 8 , 0 , 2 } , { 109 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Switch3" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 2 } , { 110 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Switch3" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 2 } , { 111 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Switch3" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 2 } , { 112 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Timer/Derivative" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 113 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 114 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 115 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode1/Model/eee" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 116 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 117 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode2/Model/eee" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 118 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 119 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode3/Model/eee" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 120 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 121 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode6/Model/eee" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 122 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Timer/Derivative" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 123 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 124 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 125 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode1/Model/eee" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 126 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 127 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode2/Model/eee" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 128 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 129 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode3/Model/eee" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 130 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 131 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode6/Model/eee" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 132 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Timer/Derivative" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 133 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 134 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 135 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode1/Model/eee" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 136 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 137 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode2/Model/eee" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 138 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 139 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode3/Model/eee" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 140 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 141 , 0 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode6/Model/eee" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 142 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio" ) , TARGET_STRING ( "st_time" ) , 0 , 0 , 0 }
, { 143 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio1" ) , TARGET_STRING
( "st_time" ) , 0 , 0 , 0 } , { 144 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel" ) , TARGET_STRING ( "st_time" ) , 0 , 0 ,
0 } , { 145 , TARGET_STRING ( "uGrid_1PH_hd/DC 540V" ) , TARGET_STRING (
"Amplitude" ) , 0 , 0 , 0 } , { 146 , TARGET_STRING ( "uGrid_1PH_hd/DC_1" ) ,
TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 147 , TARGET_STRING (
"uGrid_1PH_hd/DC_2" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 148 ,
TARGET_STRING ( "uGrid_1PH_hd/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 149 , TARGET_STRING ( "uGrid_1PH_hd/Constant1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 150 , TARGET_STRING ( "uGrid_1PH_hd/Constant5" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 151 , TARGET_STRING (
"uGrid_1PH_hd/P_lp_bio" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 152 ,
TARGET_STRING ( "uGrid_1PH_hd/P_lp_diesel" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 153 , TARGET_STRING ( "uGrid_1PH_hd/Sine Wave" ) ,
TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 154 , TARGET_STRING (
"uGrid_1PH_hd/Sine Wave" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 155 ,
TARGET_STRING ( "uGrid_1PH_hd/Sine Wave" ) , TARGET_STRING ( "Frequency" ) ,
0 , 0 , 0 } , { 156 , TARGET_STRING ( "uGrid_1PH_hd/Sine Wave" ) ,
TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 157 , TARGET_STRING (
"uGrid_1PH_hd/Hw1" ) , TARGET_STRING ( "A" ) , 0 , 5 , 0 } , { 158 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw1" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 159 , TARGET_STRING ( "uGrid_1PH_hd/Hw1" ) , TARGET_STRING ( "C" ) , 0 , 0
, 0 } , { 160 , TARGET_STRING ( "uGrid_1PH_hd/Hw1" ) , TARGET_STRING ( "X0" )
, 0 , 0 , 0 } , { 161 , TARGET_STRING ( "uGrid_1PH_hd/Hw2" ) , TARGET_STRING
( "A" ) , 0 , 5 , 0 } , { 162 , TARGET_STRING ( "uGrid_1PH_hd/Hw2" ) ,
TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 163 , TARGET_STRING (
"uGrid_1PH_hd/Hw2" ) , TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 164 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw2" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0 } ,
{ 165 , TARGET_STRING ( "uGrid_1PH_hd/Hw3" ) , TARGET_STRING ( "A" ) , 0 , 5
, 0 } , { 166 , TARGET_STRING ( "uGrid_1PH_hd/Hw3" ) , TARGET_STRING ( "B" )
, 0 , 0 , 0 } , { 167 , TARGET_STRING ( "uGrid_1PH_hd/Hw3" ) , TARGET_STRING
( "C" ) , 0 , 0 , 0 } , { 168 , TARGET_STRING ( "uGrid_1PH_hd/Hw3" ) ,
TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 169 , TARGET_STRING (
"uGrid_1PH_hd/Hw4" ) , TARGET_STRING ( "A" ) , 0 , 5 , 0 } , { 170 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw4" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 171 , TARGET_STRING ( "uGrid_1PH_hd/Hw4" ) , TARGET_STRING ( "C" ) , 0 , 0
, 0 } , { 172 , TARGET_STRING ( "uGrid_1PH_hd/Hw4" ) , TARGET_STRING ( "X0" )
, 0 , 0 , 0 } , { 173 , TARGET_STRING ( "uGrid_1PH_hd/Hw5" ) , TARGET_STRING
( "A" ) , 0 , 5 , 0 } , { 174 , TARGET_STRING ( "uGrid_1PH_hd/Hw5" ) ,
TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 175 , TARGET_STRING (
"uGrid_1PH_hd/Hw5" ) , TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 176 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw5" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0 } ,
{ 177 , TARGET_STRING ( "uGrid_1PH_hd/Hw6" ) , TARGET_STRING ( "A" ) , 0 , 5
, 0 } , { 178 , TARGET_STRING ( "uGrid_1PH_hd/Hw6" ) , TARGET_STRING ( "B" )
, 0 , 0 , 0 } , { 179 , TARGET_STRING ( "uGrid_1PH_hd/Hw6" ) , TARGET_STRING
( "C" ) , 0 , 0 , 0 } , { 180 , TARGET_STRING ( "uGrid_1PH_hd/Hw6" ) ,
TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 181 , TARGET_STRING (
"uGrid_1PH_hd/Hw7" ) , TARGET_STRING ( "A" ) , 0 , 5 , 0 } , { 182 ,
TARGET_STRING ( "uGrid_1PH_hd/Hw7" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 183 , TARGET_STRING ( "uGrid_1PH_hd/Hw7" ) , TARGET_STRING ( "C" ) , 0 , 0
, 0 } , { 184 , TARGET_STRING ( "uGrid_1PH_hd/Hw7" ) , TARGET_STRING ( "X0" )
, 0 , 0 , 0 } , { 185 , TARGET_STRING ( "uGrid_1PH_hd/Step1" ) ,
TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , { 186 , TARGET_STRING (
"uGrid_1PH_hd/Step1" ) , TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 187 ,
TARGET_STRING ( "uGrid_1PH_hd/Step1" ) , TARGET_STRING ( "After" ) , 0 , 0 ,
0 } , { 188 , TARGET_STRING ( "uGrid_1PH_hd/Step2" ) , TARGET_STRING ( "Time"
) , 0 , 0 , 0 } , { 189 , TARGET_STRING ( "uGrid_1PH_hd/Step2" ) ,
TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 190 , TARGET_STRING (
"uGrid_1PH_hd/Step2" ) , TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 191 ,
TARGET_STRING ( "uGrid_1PH_hd/Step3" ) , TARGET_STRING ( "Time" ) , 0 , 0 , 0
} , { 192 , TARGET_STRING ( "uGrid_1PH_hd/Step3" ) , TARGET_STRING ( "Before"
) , 0 , 0 , 0 } , { 193 , TARGET_STRING ( "uGrid_1PH_hd/Step3" ) ,
TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 194 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Constant1" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 195 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 196 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Step" ) , TARGET_STRING ( "Before" ) , 0 , 0 ,
0 } , { 197 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio/Step" ) ,
TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 198 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 ,
0 , 0 } , { 199 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn" ) , TARGET_STRING ( "C" ) , 0 ,
0 , 0 } , { 200 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn1" ) , TARGET_STRING ( "A" ) , 0 ,
0 , 0 } , { 201 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Transfer Fcn1" ) , TARGET_STRING ( "C" ) , 0 ,
0 , 0 } , { 202 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio1/Constant1"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 203 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Gain" ) , TARGET_STRING ( "Gain" ) , 0 , 0 ,
0 } , { 204 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio1/Step" ) ,
TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 205 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Step" ) , TARGET_STRING ( "After" ) , 0 , 0 ,
0 } , { 206 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn" )
, TARGET_STRING ( "A" ) , 0 , 0 , 0 } , { 207 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn" ) , TARGET_STRING ( "C" ) , 0 ,
0 , 0 } , { 208 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn1" ) , TARGET_STRING ( "A" ) , 0
, 0 , 0 } , { 209 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn1" ) , TARGET_STRING ( "C" ) , 0
, 0 , 0 } , { 210 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn2" ) , TARGET_STRING ( "A" ) , 0
, 0 , 0 } , { 211 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Transfer Fcn2" ) , TARGET_STRING ( "C" ) , 0
, 0 , 0 } , { 212 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Constant1" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 213 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_diesel/Gain"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 214 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Step" ) , TARGET_STRING ( "Before" ) , 0 ,
0 , 0 } , { 215 , TARGET_STRING ( "uGrid_1PH_hd/1Ph_Inverter_diesel/Step" ) ,
TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 216 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0
, 0 , 0 } , { 217 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn" ) , TARGET_STRING ( "C" ) , 0
, 0 , 0 } , { 218 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn1" ) , TARGET_STRING ( "A" ) ,
0 , 0 , 0 } , { 219 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Transfer Fcn1" ) , TARGET_STRING ( "C" ) ,
0 , 0 , 0 } , { 220 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_BIO/Hw2" ) ,
TARGET_STRING ( "A" ) , 0 , 9 , 0 } , { 221 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/Hw2" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 222 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_BIO/Hw2" ) , TARGET_STRING
( "C" ) , 0 , 0 , 0 } , { 223 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/Hw2" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0 } ,
{ 224 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_BIO/Hw6" ) , TARGET_STRING
( "A" ) , 0 , 9 , 0 } , { 225 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/Hw6" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } ,
{ 226 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_BIO/Hw6" ) , TARGET_STRING
( "C" ) , 0 , 0 , 0 } , { 227 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/Hw6" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0 } ,
{ 228 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_DIESEL/Hw1" ) ,
TARGET_STRING ( "A" ) , 0 , 9 , 0 } , { 229 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/Hw1" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 }
, { 230 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_DIESEL/Hw1" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 231 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/Hw1" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0
} , { 232 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_DIESEL/Hw3" ) ,
TARGET_STRING ( "A" ) , 0 , 9 , 0 } , { 233 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/Hw3" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0 }
, { 234 , TARGET_STRING ( "uGrid_1PH_hd/CSI_Control_DIESEL/Hw3" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 235 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/Hw3" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0
} , { 236 , TARGET_STRING ( "uGrid_1PH_hd/I sens A/do not delete this gain" )
, TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 237 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/Memory1" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0
} , { 238 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/Memory2" ) ,
TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 239 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/Memory3" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0
} , { 240 , TARGET_STRING ( "uGrid_1PH_hd/MPC Controller/Memory4" ) ,
TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 241 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 242 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/SwitchingFilterCapacitor1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 243 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Gain2" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0
} , { 244 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) ,
TARGET_STRING ( "A" ) , 0 , 0 , 0 } , { 245 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) , TARGET_STRING ( "B" ) , 0 , 0 , 0
} , { 246 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) ,
TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 247 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) , TARGET_STRING ( "D" ) , 0 , 0 , 0
} , { 248 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Hi_Pass1" ) ,
TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 249 , TARGET_STRING (
"uGrid_1PH_hd/VSI_Controller/Transfer Fcn1" ) , TARGET_STRING ( "A" ) , 0 , 3
, 0 } , { 250 , TARGET_STRING ( "uGrid_1PH_hd/VSI_Controller/Transfer Fcn1" )
, TARGET_STRING ( "C" ) , 0 , 10 , 0 } , { 251 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 252 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper1/Step" ) , TARGET_STRING ( "Before" ) ,
0 , 0 , 0 } , { 253 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper1/Step" ) , TARGET_STRING ( "After" ) ,
0 , 0 , 0 } , { 254 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper3/Step" ) , TARGET_STRING ( "Before" ) ,
0 , 0 , 0 } , { 255 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Steper3/Step" ) , TARGET_STRING ( "After" ) ,
0 , 0 , 0 } , { 256 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 257 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 258 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/I sens A1/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 259 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper1/Step" ) , TARGET_STRING ( "Before" )
, 0 , 0 , 0 } , { 260 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper1/Step" ) , TARGET_STRING ( "After" ) ,
0 , 0 , 0 } , { 261 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper3/Step" ) , TARGET_STRING ( "Before" )
, 0 , 0 , 0 } , { 262 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Steper3/Step" ) , TARGET_STRING ( "After" ) ,
0 , 0 , 0 } , { 263 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 264 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/I sens A/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 265 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper1/Step" ) , TARGET_STRING ( "Before"
) , 0 , 0 , 0 } , { 266 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper1/Step" ) , TARGET_STRING ( "After" )
, 0 , 0 , 0 } , { 267 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper3/Step" ) , TARGET_STRING ( "Before"
) , 0 , 0 , 0 } , { 268 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Steper3/Step" ) , TARGET_STRING ( "After" )
, 0 , 0 , 0 } , { 269 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Vsensa1/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 270 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/Energy" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 271 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P1"
) , 0 , 11 , 0 } , { 272 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P2"
) , 0 , 0 , 0 } , { 273 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P3"
) , 0 , 10 , 0 } , { 274 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P4"
) , 0 , 0 , 0 } , { 275 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P5"
) , 0 , 0 , 0 } , { 276 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_BIO/TTKernel_BIO/ttkernel" ) , TARGET_STRING ( "P7"
) , 0 , 10 , 0 } , { 277 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/Energy" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 278 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "P1" ) , 0 , 12 , 0 } , { 279 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "P3" ) , 0 , 10 , 0 } , { 280 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "P4" ) , 0 , 0 , 0 } , { 281 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "P5" ) , 0 , 0 , 0 } , { 282 , TARGET_STRING (
"uGrid_1PH_hd/CSI_Control_DIESEL/TTKernel_DIESEL/ttkernel" ) , TARGET_STRING
( "P7" ) , 0 , 10 , 0 } , { 283 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/Energy" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 284 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING (
"P1" ) , 0 , 12 , 0 } , { 285 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING (
"P3" ) , 0 , 10 , 0 } , { 286 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING (
"P4" ) , 0 , 0 , 0 } , { 287 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING (
"P5" ) , 0 , 0 , 0 } , { 288 , TARGET_STRING (
"uGrid_1PH_hd/MPC Controller/TrueTime Kernel/ttkernel" ) , TARGET_STRING (
"P7" ) , 0 , 10 , 0 } , { 289 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P1"
) , 0 , 13 , 0 } , { 290 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P2"
) , 0 , 14 , 0 } , { 291 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P3"
) , 0 , 15 , 0 } , { 292 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P4"
) , 0 , 16 , 0 } , { 293 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P5"
) , 0 , 17 , 0 } , { 294 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P6"
) , 0 , 18 , 0 } , { 295 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P7"
) , 0 , 19 , 0 } , { 296 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P8"
) , 0 , 18 , 0 } , { 297 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "P9"
) , 0 , 0 , 0 } , { 298 , TARGET_STRING (
"uGrid_1PH_hd/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P10" ) , 0 , 0 , 0 } , { 299 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/C4" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 300 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Switch3" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 301 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/PWM Generator (DC-DC)/Compare To Zero/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 302 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/C4" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 303 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Switch3" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 304 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Compare To Zero/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 305 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/C4" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 306 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Switch3" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 307 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Compare To Zero/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 308 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Timer/Hit  Crossing" ) ,
TARGET_STRING ( "HitCrossingOffset" ) , 0 , 0 , 0 } , { 309 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "InputValues" ) , 0 , 20 , 0 } , { 310 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "Table" ) , 0 , 20 , 0 } , { 311 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 312 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode1/Model/eee" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 313 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 314 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode2/Model/eee" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 315 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 316 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode3/Model/eee" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 317 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 318 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio/H bridge/Diode6/Model/eee" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 319 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant2"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 320 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant3"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 321 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio/PWM Generator (DC-DC)/Sawtooth Generator/Model/1\\ib1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 322 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Timer/Hit  Crossing" ) ,
TARGET_STRING ( "HitCrossingOffset" ) , 0 , 0 , 0 } , { 323 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "InputValues" ) , 0 , 20 , 0 } , { 324 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "Table" ) , 0 , 20 , 0 } , { 325 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 326 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode1/Model/eee" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 327 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 328 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode2/Model/eee" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 329 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 330 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode3/Model/eee" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 331 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 332 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_bio1/H bridge/Diode6/Model/eee" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 333 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant2"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 334 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant3"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 335 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Sawtooth Generator/Model/1\\ib1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 336 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Timer/Hit  Crossing" ) ,
TARGET_STRING ( "HitCrossingOffset" ) , 0 , 0 , 0 } , { 337 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "InputValues" ) , 0 , 20 , 0 } , { 338 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/Breaker/Model/Timer/Look-Up Table" ) ,
TARGET_STRING ( "Table" ) , 0 , 20 , 0 } , { 339 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode1/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 340 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode1/Model/eee" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 341 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode2/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 342 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode2/Model/eee" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 343 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode3/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 344 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode3/Model/eee" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 345 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode6/Model/(gate)" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 346 , TARGET_STRING (
"uGrid_1PH_hd/1Ph_Inverter_diesel/H bridge/Diode6/Model/eee" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 347 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant2"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 348 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Sawtooth Generator/Model/Constant3"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 349 , TARGET_STRING (
 "uGrid_1PH_hd/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Sawtooth Generator/Model/1\\ib1"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 ,
0 , 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [ ] = { {
350 , TARGET_STRING ( "G" ) , 0 , 21 , 0 } , { 351 , TARGET_STRING ( "GF" ) ,
0 , 21 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . aj3gcmhe30 , & rtB . pakxhumxso ,
& rtB . jhuzfee1rx , & rtB . nk2fzzksvb , & rtB . okmcolqmmp , & rtB .
cypxcf4iuh , & rtB . katlkd05we , & rtB . i0tzocdcou , & rtB . m1it3g5wdk , &
rtB . nnkwaky0vo , & rtB . gok32izhkr , & rtB . cr3o3bcjno , & rtB .
d5oxoszzwe , & rtB . ptnr1vtbjm , & rtB . puuyej0ojx , & rtB . d5gh3z0nbz .
e3galh2ets , & rtB . j1nlrdh0gl , & rtB . jvnydmoxuc , & rtB . l2k5p2r0wh , &
rtB . d4o1qxqtvz , & rtB . n4wqmwk0ih . e3galh2ets , & rtB . hqdf5p5g5k , &
rtB . foapkh0xzh , & rtB . ahbxhfing1 , & rtB . nkt1wwkpxk , & rtB .
oashgqc3jo , & rtB . pncwbu0dto . e3galh2ets , & rtB . hilnaqgqvk , & rtB .
aeiozt25lb , & rtB . chc3tp5kgw , & rtB . pgxj3vimkq , & rtB . gwjcoav1lk , &
rtB . b1utvav4hj , & rtB . btdi3tstnl , & rtB . iq42atba5o , & rtB .
e312d3rw1k , & rtB . hk2fxt1axd . j4xgvi25fi [ 0 ] , & rtB . hk2fxt1axd .
f0ix3jjnpf [ 0 ] , & rtB . hk2fxt1axd . m0fwlvevxl [ 0 ] , & rtB . hk2fxt1axd
. ntofjobsep [ 0 ] , & rtB . hk2fxt1axd . bvdahqrkgv [ 0 ] , & rtB .
hk2fxt1axd . fyq3rr4pxa [ 0 ] , & rtB . hk2fxt1axd . deyysf5gta [ 0 ] , & rtB
. csjm5qcu5l . j4xgvi25fi [ 0 ] , & rtB . csjm5qcu5l . f0ix3jjnpf [ 0 ] , &
rtB . csjm5qcu5l . m0fwlvevxl [ 0 ] , & rtB . csjm5qcu5l . ntofjobsep [ 0 ] ,
& rtB . csjm5qcu5l . bvdahqrkgv [ 0 ] , & rtB . csjm5qcu5l . fyq3rr4pxa [ 0 ]
, & rtB . csjm5qcu5l . deyysf5gta [ 0 ] , & rtB . mpnopdrqui . p4suqxiggq [ 0
] , & rtB . mpnopdrqui . g1q3oofyrj [ 0 ] , & rtB . jlxfvkiytb . p4suqxiggq [
0 ] , & rtB . jlxfvkiytb . g1q3oofyrj [ 0 ] , & rtB . bkz5gblmt2 [ 0 ] , &
rtB . jbv4oeizoh [ 0 ] , & rtB . ewsxkq0wzp [ 0 ] , & rtB . la0fvqhabk [ 0 ]
, & rtB . ioirosbkbv [ 0 ] , & rtB . jnz2ccaipm [ 0 ] , & rtB . cazq3bcp4v [
0 ] , & rtB . el0hi2mpax , & rtB . pviaul0ind , & rtB . dvxrwfxmke , & rtB .
k2r1v43eue [ 0 ] , & rtB . ms400ves34 , & rtB . bkld5544on , & rtB .
hvk4gr05kp , & rtB . d3wmvrdgp5 , & rtB . orga5rxyo4 , & rtB . c1ucoxgukl , &
rtB . faenhustsh , & rtB . grqskhisxe , & rtB . nwi2u1x5jv , & rtB .
bywih0a2yp , & rtB . pgv3a43g3a , & rtB . jr3vymwmkc , & rtB . dbr0navviv , &
rtB . hsj4xty3ld , & rtB . obugd5y2ad , & rtB . pkaciejeq4 , & rtB .
gebkbee1ff , & rtB . fwwgncxyps , & rtB . eol02jxukg , & rtB . pr32bh5ab0 , &
rtB . pfa5sut0yt , & rtB . posuhuud3g , & rtB . bu3zpefbt0 , & rtB .
hchtpl1d3p , & rtB . i3k3ladn4s , & rtB . hbd0hneu5u [ 0 ] , & rtB .
o3zd3lrgcz , & rtB . hxnhqtjvzy , & rtB . o3l2gemtct , & rtB . iusqw5vol4 , &
rtB . gxoc5j0ev2 [ 0 ] , & rtB . czdizqkiy5 , & rtB . kam4wd2zke , & rtB .
pzlqwcc3xg , & rtB . fn4ajroglo , & rtB . le51iuyvkp , & rtB . eh1uxfdfxk , &
rtB . kyq4ddwnt5 , & rtB . lmlfl3t04h [ 0 ] , & rtB . ewo1cwunpw , & rtB .
m4dlwah4c3 , & rtB . jvajaeojzw , & rtB . aqe3urztoo [ 0 ] , & rtB .
bmqsiz2toy [ 0 ] , & rtB . du31rtbcg2 , & rtB . ec0lm5oxpo , & rtB .
ksmj2ks1ry , & rtB . aoljwchi5z , & rtB . oe0msxmkyu , & rtB . hbhwwpohe0 , &
rtB . aunpobcu44 , & rtB . bbzwoxa50q , & rtB . jc05hb1vpg , & rtB .
cao3opsb5y , & rtB . eczkwep1fc , & rtB . f2y40zjr03 , & rtB . haih3brbef , &
rtB . jbkeye4siv , & rtB . ordb0vcov4 , & rtB . mbhd03n5qp , & rtB .
kjzt3xvlg4 , & rtB . ld2pf1geuj , & rtB . ddj2ljlqar , & rtB . ngwlyiii4t , &
rtB . fhtkgnfwcd , & rtB . mmhpsmc2xu , & rtB . fkqc2ypzow , & rtB .
jt50mttmmc , & rtB . cvy5dhiqlw , & rtB . ke5galvxnd , & rtB . dmlly3udcf , &
rtB . njnf2oxsm1 , & rtB . mlexdgwnj1 , & rtB . bivhyu0fbz , & rtB .
izwvjz1tew , & rtB . m1ekwvon4u , & rtB . bk1xuitdvv , & rtP .
uPh_Inverter_bio_st_time , & rtP . uPh_Inverter_bio1_st_time , & rtP .
uPh_Inverter_diesel_st_time , & rtP . DC540V_Amplitude , & rtP .
DC_1_Amplitude , & rtP . DC_2_Amplitude , & rtP . Constant_Value , & rtP .
Constant1_Value , & rtP . Constant5_Value , & rtP . P_lp_bio_Value , & rtP .
P_lp_diesel_Value , & rtP . SineWave_Amp , & rtP . SineWave_Bias , & rtP .
SineWave_Freq , & rtP . SineWave_Phase , & rtP . Hw1_A_kbzflcjjyj [ 0 ] , &
rtP . Hw1_B_o4lzhk3gnx , & rtP . Hw1_C_i3w2ow0rwv , & rtP . Hw1_X0_jjtb1pylbl
, & rtP . Hw2_A_jjvwx3g4vm [ 0 ] , & rtP . Hw2_B_ag4uxupnle , & rtP .
Hw2_C_c1pm2juzi1 , & rtP . Hw2_X0_dwpd2y1z3s , & rtP . Hw3_A_ngyitj1gem [ 0 ]
, & rtP . Hw3_B_mskofuv4se , & rtP . Hw3_C_mvzrzdbpid , & rtP .
Hw3_X0_fiftn0ykcd , & rtP . Hw4_A [ 0 ] , & rtP . Hw4_B , & rtP . Hw4_C , &
rtP . Hw4_X0 , & rtP . Hw5_A [ 0 ] , & rtP . Hw5_B , & rtP . Hw5_C , & rtP .
Hw5_X0 , & rtP . Hw6_A_ljeu45oawb [ 0 ] , & rtP . Hw6_B_ovbhidad3v , & rtP .
Hw6_C_i2gbmjev5d , & rtP . Hw6_X0_eqbfuwse4i , & rtP . Hw7_A [ 0 ] , & rtP .
Hw7_B , & rtP . Hw7_C , & rtP . Hw7_X0 , & rtP . Step1_Time , & rtP .
Step1_Y0 , & rtP . Step1_YFinal , & rtP . Step2_Time , & rtP . Step2_Y0 , &
rtP . Step2_YFinal , & rtP . Step3_Time , & rtP . Step3_Y0 , & rtP .
Step3_YFinal , & rtP . Constant1_Value_ihao24qd3r , & rtP . Gain_Gain , & rtP
. Step_Y0_p2wkubb2bf , & rtP . Step_YFinal_i1efzfr20g , & rtP . TransferFcn_A
, & rtP . TransferFcn_C , & rtP . TransferFcn1_A , & rtP . TransferFcn1_C , &
rtP . Constant1_Value_cqn15imi2r , & rtP . Gain_Gain_bktwk0ibkx , & rtP .
Step_Y0_ji235vnkbb , & rtP . Step_YFinal_jlaji2juh5 , & rtP .
TransferFcn_A_fo4eivk0cz , & rtP . TransferFcn_C_cidb1uzs1l , & rtP .
TransferFcn1_A_gbpccbxwkq , & rtP . TransferFcn1_C_iymr30cu1l , & rtP .
TransferFcn2_A , & rtP . TransferFcn2_C , & rtP . Constant1_Value_oo43yhpvhj
, & rtP . Gain_Gain_mygr3ck4si , & rtP . Step_Y0_h0xozw0tcv , & rtP .
Step_YFinal_eksdyefhpg , & rtP . TransferFcn_A_jmuxqs4cyv , & rtP .
TransferFcn_C_assnubnh1r , & rtP . TransferFcn1_A_gyfo1spe1k , & rtP .
TransferFcn1_C_c0ncjvfshw , & rtP . Hw2_A [ 0 ] , & rtP . Hw2_B , & rtP .
Hw2_C , & rtP . Hw2_X0 , & rtP . Hw6_A [ 0 ] , & rtP . Hw6_B , & rtP . Hw6_C
, & rtP . Hw6_X0 , & rtP . Hw1_A [ 0 ] , & rtP . Hw1_B , & rtP . Hw1_C , &
rtP . Hw1_X0 , & rtP . Hw3_A [ 0 ] , & rtP . Hw3_B , & rtP . Hw3_C , & rtP .
Hw3_X0 , & rtP . donotdeletethisgain_Gain_muoknirdms , & rtP . Memory1_X0 , &
rtP . Memory2_X0 , & rtP . Memory3_X0 , & rtP . Memory4_X0 , & rtP .
Constant2_Value_bnaip2qh1m , & rtP . SwitchingFilterCapacitor1_Value , & rtP
. Gain2_Gain , & rtP . Hi_Pass1_A , & rtP . Hi_Pass1_B , & rtP . Hi_Pass1_C ,
& rtP . Hi_Pass1_D , & rtP . Hi_Pass1_X0 , & rtP . TransferFcn1_A_mhbp45m11f
[ 0 ] , & rtP . TransferFcn1_C_d5ieeyryfz [ 0 ] , & rtP .
donotdeletethisgain_Gain , & rtP . Step_Y0 , & rtP . Step_YFinal , & rtP .
Step_Y0_legsdikta1 , & rtP . Step_YFinal_n0k22wxmnl , & rtP .
donotdeletethisgain_Gain_khgfu0zvf4 , & rtP .
donotdeletethisgain_Gain_pfs1e1lqot , & rtP .
donotdeletethisgain_Gain_lmwc2zhiza , & rtP . Step_Y0_m1xcmpkjwa , & rtP .
Step_YFinal_h3jz4xlvs5 , & rtP . Step_Y0_flotjz4byv , & rtP .
Step_YFinal_iajv2qdnwe , & rtP . donotdeletethisgain_Gain_gwkq5frpca , & rtP
. donotdeletethisgain_Gain_aqki2j0pex , & rtP . Step_Y0_nw5wkv3ooz , & rtP .
Step_YFinal_nmjbi1q1jk , & rtP . Step_Y0_efnefifyw2 , & rtP .
Step_YFinal_onn4xqhkyw , & rtP . donotdeletethisgain_Gain_malkwg3eo0 , & rtP
. Energy_Value , & rtP . ttkernel_P1 [ 0 ] , & rtP . ttkernel_P2 , & rtP .
ttkernel_P3 [ 0 ] , & rtP . ttkernel_P4 , & rtP . ttkernel_P5 , & rtP .
ttkernel_P7 [ 0 ] , & rtP . Energy_Value_llumdghwbm , & rtP .
ttkernel_P1_dau5ffdd1u [ 0 ] , & rtP . ttkernel_P3_alumkyzhoh [ 0 ] , & rtP .
ttkernel_P4_pykitjxifn , & rtP . ttkernel_P5_a0o1uqg3oc , & rtP .
ttkernel_P7_gqqekjm05a [ 0 ] , & rtP . Energy_Value_in0imrdvbj , & rtP .
ttkernel_P1_kegxebksg2 [ 0 ] , & rtP . ttkernel_P3_gqnydskipg [ 0 ] , & rtP .
ttkernel_P4_czxg5elx0u , & rtP . ttkernel_P5_eeyd0jrw1c , & rtP .
ttkernel_P7_hxqdtrr2zt [ 0 ] , & rtP . StateSpace_P1 [ 0 ] , & rtP .
StateSpace_P2 [ 0 ] , & rtP . StateSpace_P3 [ 0 ] , & rtP . StateSpace_P4 [ 0
] , & rtP . StateSpace_P5 [ 0 ] , & rtP . StateSpace_P6 [ 0 ] , & rtP .
StateSpace_P7 [ 0 ] , & rtP . StateSpace_P8 [ 0 ] , & rtP . StateSpace_P9 , &
rtP . StateSpace_P10 , & rtP . C4_Value , & rtP . Switch3_Threshold , & rtP .
Constant_Value_j5zaiux01a , & rtP . C4_Value_lgay0qrqwc , & rtP .
Switch3_Threshold_ohskz1p5nh , & rtP . Constant_Value_ohbjm2j0ij , & rtP .
C4_Value_aagigtr1s1 , & rtP . Switch3_Threshold_obfdmxriwc , & rtP .
Constant_Value_lpxxzcor1x , & rtP . HitCrossing_Offset , & rtP .
LookUpTable_XData [ 0 ] , & rtP . LookUpTable_YData [ 0 ] , & rtP .
gate_Value , & rtP . eee_Value , & rtP . gate_Value_o1atqxnff5 , & rtP .
eee_Value_kjv1lt1rls , & rtP . gate_Value_ivxretxarq , & rtP .
eee_Value_luohiy4ktt , & rtP . gate_Value_p51ecoshdm , & rtP .
eee_Value_la1sxv22ch , & rtP . Constant2_Value , & rtP . Constant3_Value , &
rtP . uib1_Gain , & rtP . HitCrossing_Offset_ez0hdaiej5 , & rtP .
LookUpTable_XData_djytinpfos [ 0 ] , & rtP . LookUpTable_YData_oewicl1qan [ 0
] , & rtP . gate_Value_i5kbinpwee , & rtP . eee_Value_cnrsszzthq , & rtP .
gate_Value_bt41vtykjz , & rtP . eee_Value_n2jnc2ydfy , & rtP .
gate_Value_h10hkkwhs2 , & rtP . eee_Value_eahotdmisl , & rtP .
gate_Value_ojlyotiqqk , & rtP . eee_Value_gv0u2ahtt0 , & rtP .
Constant2_Value_efe4bfc10e , & rtP . Constant3_Value_hzs44l22rj , & rtP .
uib1_Gain_buhnycyzrk , & rtP . HitCrossing_Offset_dtlkzxqizf , & rtP .
LookUpTable_XData_h2at0lfgy0 [ 0 ] , & rtP . LookUpTable_YData_kfsva1ia4o [ 0
] , & rtP . gate_Value_evjry40iys , & rtP . eee_Value_h3by2pvwt1 , & rtP .
gate_Value_duqg5wmkuu , & rtP . eee_Value_lkmzkp31k3 , & rtP .
gate_Value_but4pbwkg3 , & rtP . eee_Value_akbbszpib5 , & rtP .
gate_Value_jhlex4egqq , & rtP . eee_Value_lskvq5tfxu , & rtP .
Constant2_Value_ecraziuear , & rtP . Constant3_Value_j5dz1hgiog , & rtP .
uib1_Gain_hysnw5mqld , & rtP . G [ 0 ] , & rtP . GF [ 0 ] , } ; static
int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 2 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_VECTOR , 8 , 2 , 0 } , { rtwCAPI_VECTOR , 10 , 2 , 0 } , {
rtwCAPI_VECTOR , 12 , 2 , 0 } , { rtwCAPI_VECTOR , 14 , 2 , 0 } , {
rtwCAPI_VECTOR , 16 , 2 , 0 } , { rtwCAPI_VECTOR , 18 , 2 , 0 } , {
rtwCAPI_VECTOR , 20 , 2 , 0 } , { rtwCAPI_VECTOR , 22 , 2 , 0 } , {
rtwCAPI_VECTOR , 24 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 26 , 2 , 0 } , {
rtwCAPI_VECTOR , 28 , 2 , 0 } , { rtwCAPI_VECTOR , 30 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 32 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 34 , 2
, 0 } , { rtwCAPI_VECTOR , 36 , 2 , 0 } , { rtwCAPI_VECTOR , 38 , 2 , 0 } , {
rtwCAPI_VECTOR , 40 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 42 , 2 , 0 } } ;
static const uint_T rtDimensionArray [ ] = { 1 , 1 , 1 , 40000 , 1 , 200 , 2
, 1 , 200 , 1 , 3 , 1 , 4 , 1 , 8 , 1 , 54 , 1 , 7 , 1 , 1 , 2 , 1 , 8 , 1 ,
11 , 140 , 56 , 1 , 4 , 21 , 1 , 140 , 50 , 2 , 27 , 1 , 27 , 27 , 1 , 1 , 5
, 200 , 200 } ; static const real_T rtcapiStoredFloats [ ] = { 0.001 , 0.0 ,
1.0 , 1.0E-6 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL )
, ( NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 3 ,
0 } , { ( NULL ) , ( NULL ) , 4 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 0 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) &
rtcapiStoredFloats [ 2 ] , 1 , 0 } , { ( const void * ) & rtcapiStoredFloats
[ 3 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 2 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 142 , ( NULL
) , 0 , ( NULL ) , 0 } , { rtBlockParameters , 208 , rtModelParameters , 2 }
, { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap ,
rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" , { 771051142U
, 3907438473U , 2959251210U , 1793715238U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * uGrid_1PH_hd_GetCAPIStaticMap ( ) { return &
mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void uGrid_1PH_hd_InitializeDataMapInfo ( ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void uGrid_1PH_hd_host_InitializeDataMapInfo (
uGrid_1PH_hd_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
