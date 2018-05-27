#include "__cf_SOC_Modelling.h"
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "SOC_Modelling_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "SOC_Modelling.h"
#include "SOC_Modelling_capi.h"
#include "SOC_Modelling_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Data Type Conversion1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 2 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Data Type Conversion2" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 3 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Fcn1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 4 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Fcn6" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Gain" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 6 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Gain2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 7 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/R1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0
} , { 8 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/R2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 9 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/R3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1
} , { 10 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/R4" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 11 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/int(i)" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 0 } , { 12 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/it init" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 13 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Product" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 0 } , { 14 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Product1" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 15 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Product2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 0 } , { 16 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Saturation"
) , TARGET_STRING ( "SOC (%)" ) , 0 , 0 , 0 , 0 , 0 } , { 17 , 0 ,
TARGET_STRING ( "SOC_Modelling/Battery/Model/Add" ) , TARGET_STRING (
"Voltage (V)" ) , 0 , 0 , 0 , 0 , 0 } , { 18 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Add2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 19 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Add3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 20 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
2 } , { 21 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 22 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 0 } , { 23 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch2" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 24 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 2 } , { 25 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch4" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 26 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch5" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 1 } , { 27 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch6" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 28 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 0 } , { 29 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 0 } , { 30 , 0 , TARGET_STRING (
"SOC_Modelling/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 31 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Multiport Switch1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 32 , 6 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 1 , 0 , 0 } , { 33 , 4 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Product1" ) , TARGET_STRING ( "" )
, 0 , 0 , 1 , 0 , 0 } , { 34 , 5 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Product2" ) , TARGET_STRING ( "" )
, 0 , 0 , 1 , 0 , 0 } , { 35 , 7 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Product3" ) , TARGET_STRING ( "" )
, 0 , 0 , 1 , 0 , 0 } , { 36 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 0 } , { 37 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Exp/Gain1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 38 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Gain4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 39 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Integrator2" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 0 } , { 40 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Multiport Switch1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 41 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Divide" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 42 , 0 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Exp/Add3"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 43 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Abs" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 44 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Abs1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 45 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Fcn3" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 46 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Gain" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 47 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Product" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 48 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Add" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 49 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic/LowerRelop1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 50 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic/UpperRelop" ) , TARGET_STRING
( "" ) , 0 , 1 , 0 , 0 , 1 } , { 51 , 9 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic/Switch" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 52 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic/Switch2" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 53 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic1/LowerRelop1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 54 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic1/UpperRelop" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 55 , 10 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic1/Switch" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 56 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic1/Switch2" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 57 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic2/LowerRelop1" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 58 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic2/UpperRelop" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , { 59 , 11 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic2/Switch" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 60 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation Dynamic2/Switch2" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 61 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Gain" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 62 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Sum" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 63 , 0 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 64 , 0 , TARGET_STRING (
 "SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn (with initial outputs)/State Space"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 65 , TARGET_STRING ( "SOC_Modelling/Battery" ) ,
TARGET_STRING ( "BatType" ) , 0 , 0 , 0 } , { 66 , TARGET_STRING (
"SOC_Modelling/Battery" ) , TARGET_STRING ( "SOC" ) , 0 , 0 , 0 } , { 67 ,
TARGET_STRING ( "SOC_Modelling/Battery/Ta" ) , TARGET_STRING ( "Value" ) , 0
, 0 , 0 } , { 68 , TARGET_STRING (
"SOC_Modelling/Battery/Current Measurement/do not delete this gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 69 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 70 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 71 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant10" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 72 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant11" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 73 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant12" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 74 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant13" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 75 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant14" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 76 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant15" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 77 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant16" ) , TARGET_STRING ( "Value" ) , 0 ,
0 , 0 } , { 78 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 79 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant3" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 80 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant4" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 81 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant5" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 82 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant6" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 83 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant7" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 84 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Constant8" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 85 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Constant9" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 86 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 87 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Gain2" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0
} , { 88 , TARGET_STRING ( "SOC_Modelling/Battery/Model/R" ) , TARGET_STRING
( "Gain" ) , 0 , 0 , 0 } , { 89 , TARGET_STRING (
"SOC_Modelling/Battery/Model/R1" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } ,
{ 90 , TARGET_STRING ( "SOC_Modelling/Battery/Model/R2" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 91 , TARGET_STRING (
"SOC_Modelling/Battery/Model/R3" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } ,
{ 92 , TARGET_STRING ( "SOC_Modelling/Battery/Model/R4" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 93 , TARGET_STRING (
"SOC_Modelling/Battery/Model/int(i)" ) , TARGET_STRING (
"UpperSaturationLimit" ) , 0 , 0 , 0 } , { 94 , TARGET_STRING (
"SOC_Modelling/Battery/Model/int(i)" ) , TARGET_STRING (
"LowerSaturationLimit" ) , 0 , 0 , 0 } , { 95 , TARGET_STRING (
"SOC_Modelling/Battery/Model/it init1" ) , TARGET_STRING ( "X0" ) , 0 , 0 , 0
} , { 96 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 97 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation" ) , TARGET_STRING ( "LowerLimit" ) ,
0 , 0 , 0 } , { 98 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation2" ) , TARGET_STRING ( "UpperLimit" )
, 0 , 0 , 0 } , { 99 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation2" ) , TARGET_STRING ( "LowerLimit" )
, 0 , 0 , 0 } , { 100 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation3" ) , TARGET_STRING ( "UpperLimit" )
, 0 , 0 , 0 } , { 101 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Saturation3" ) , TARGET_STRING ( "LowerLimit" )
, 0 , 0 , 0 } , { 102 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch"
) , TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 103 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch1" ) , TARGET_STRING ( "Threshold" ) , 0 ,
0 , 0 } , { 104 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch2" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 105 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch3" ) , TARGET_STRING ( "Threshold" ) , 0 ,
0 , 0 } , { 106 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch4" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 107 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Switch5" ) , TARGET_STRING ( "Threshold" ) , 0 ,
0 , 0 } , { 108 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Switch6" ) ,
TARGET_STRING ( "Threshold" ) , 0 , 0 , 0 } , { 109 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter" ) , TARGET_STRING ( "A" ) , 0 ,
0 , 0 } , { 110 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter" ) , TARGET_STRING ( "C" ) , 0 ,
0 , 0 } , { 111 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter1" ) , TARGET_STRING ( "A" ) , 0 ,
0 , 0 } , { 112 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Current filter1" ) , TARGET_STRING ( "C" ) , 0 ,
0 , 0 } , { 113 , TARGET_STRING (
"SOC_Modelling/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P1" ) , 0 , 2 , 0 } , { 114 , TARGET_STRING (
"SOC_Modelling/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P2" ) , 0 , 3 , 0 } , { 115 , TARGET_STRING (
"SOC_Modelling/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING (
"P4" ) , 0 , 4 , 0 } , { 116 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Compare To Zero/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 117 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Compare To Zero2/Constant" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 118 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Constant1" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 119 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Constant2" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 120 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Constant3" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 121 , TARGET_STRING (
"SOC_Modelling/Battery/Model/E_dyn Charge/Constant4" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 122 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Gain1" ) , TARGET_STRING ( "Gain" ) , 0 , 0
, 0 } , { 123 , TARGET_STRING ( "SOC_Modelling/Battery/Model/Exp/Gain4" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 124 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Gain" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 125 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Gain" ) , TARGET_STRING ( "Gain" )
, 0 , 0 , 0 } , { 126 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn1" ) , TARGET_STRING (
"A" ) , 0 , 0 , 0 } , { 127 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn1" ) , TARGET_STRING (
"C" ) , 0 , 0 , 0 } , { 128 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Exp/Compare To Zero2/Constant" ) , TARGET_STRING
( "Value" ) , 0 , 0 , 0 } , { 129 , TARGET_STRING (
"SOC_Modelling/Battery/Model/Power loss estimation/Compare To Zero2/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 130 , TARGET_STRING (
 "SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn (with initial outputs)/State Space"
) , TARGET_STRING ( "A" ) , 0 , 0 , 0 } , { 131 , TARGET_STRING (
 "SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn (with initial outputs)/State Space"
) , TARGET_STRING ( "B" ) , 0 , 0 , 0 } , { 132 , TARGET_STRING (
 "SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn (with initial outputs)/State Space"
) , TARGET_STRING ( "C" ) , 0 , 0 , 0 } , { 133 , TARGET_STRING (
 "SOC_Modelling/Battery/Model/Thermal Model/Transfer Fcn (with initial outputs)/State Space"
) , TARGET_STRING ( "X0" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0
, 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0
, ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . ij4ybcvdzr , & rtB . nwsnm0uvqi ,
& rtB . fynfg4qnb2 , & rtB . j0kccpo40y , & rtB . elvc342g14 , & rtB .
c5jq2xkgww , & rtB . g2m0yn3eet , & rtB . lamriwhcak , & rtB . ma1gbsm4cy , &
rtB . m01gvlvnul , & rtB . fiyfz5l1sl , & rtB . bw41kxrfxz , & rtB .
dmmlw2nd0d , & rtB . mudcvl2ext , & rtB . je22l4jstn , & rtB . mwnu2z0rpd , &
rtB . gxdcwqrrsh , & rtB . jafblclliz , & rtB . ebb4hiezly , & rtB .
on5gayhq2w , & rtB . ppixwtawnh , & rtB . a22syqczrq , & rtB . joc3hf0wo0 , &
rtB . kzdncfvtsn , & rtB . g2lfefk4ds , & rtB . nrpzodws0y , & rtB .
bt2plqj3b5 , & rtB . eyraygkx4f , & rtB . ebowq5sonn , & rtB . elhmuoudrv , &
rtB . e3bmmc32eb , & rtB . es0vlsy1wt , & rtB . hm3jmuqecu [ 0 ] , & rtB .
ms1eeflxuz [ 0 ] , & rtB . lqsoqxpsum [ 0 ] , & rtB . ktmggdomvz [ 0 ] , &
rtB . jfiirh11in , & rtB . hxxgeb0kvn , & rtB . pttz2gwc5w , & rtB .
pxtchs05eq , & rtB . dwvjnb2xhx , & rtB . jxnoo5kkuk , & rtB . m4wcbi2vcn , &
rtB . jm4ld54oiu , & rtB . ef1wyi5uxj , & rtB . hvx1f2uin3 , & rtB .
e2tlfskas5 , & rtB . pflv2pvbva , & rtB . iluhumf0tr , & rtB . gmzkvvbvj2 , &
rtB . bzzsqio3rp , & rtB . il5fz1koxx , & rtB . ekfsltdwds , & rtB .
a1uqba15nh , & rtB . f3rfg1yrey , & rtB . eladaqt13z , & rtB . erussgeov3 , &
rtB . pydatjc2iu , & rtB . c0r3d03wfe , & rtB . aacgi45bew , & rtB .
hf3fvjualj , & rtB . bdsiyxiodl , & rtB . j0rbw5nmli , & rtB . dsh3mckcs4 , &
rtB . mo54mkczvc , & rtP . Battery_BatType , & rtP . Battery_SOC , & rtP .
Ta_Value , & rtP . donotdeletethisgain_Gain , & rtP . Constant_Value , & rtP
. Constant1_Value , & rtP . Constant10_Value , & rtP . Constant11_Value , &
rtP . Constant12_Value , & rtP . Constant13_Value , & rtP . Constant14_Value
, & rtP . Constant15_Value , & rtP . Constant16_Value , & rtP .
Constant2_Value_fu1vg5kur3 , & rtP . Constant3_Value_hnmpswvc50 , & rtP .
Constant4_Value , & rtP . Constant5_Value , & rtP . Constant6_Value , & rtP .
Constant7_Value , & rtP . Constant8_Value , & rtP . Constant9_Value , & rtP .
Gain_Gain , & rtP . Gain2_Gain , & rtP . R_Gain , & rtP . R1_Gain , & rtP .
R2_Gain , & rtP . R3_Gain , & rtP . R4_Gain , & rtP . inti_UpperSat , & rtP .
inti_LowerSat , & rtP . itinit1_X0 , & rtP . Saturation_UpperSat , & rtP .
Saturation_LowerSat , & rtP . Saturation2_UpperSat , & rtP .
Saturation2_LowerSat , & rtP . Saturation3_UpperSat , & rtP .
Saturation3_LowerSat , & rtP . Switch_Threshold , & rtP . Switch1_Threshold ,
& rtP . Switch2_Threshold , & rtP . Switch3_Threshold , & rtP .
Switch4_Threshold , & rtP . Switch5_Threshold , & rtP . Switch6_Threshold , &
rtP . Currentfilter_A , & rtP . Currentfilter_C , & rtP . Currentfilter1_A ,
& rtP . Currentfilter1_C , & rtP . StateSpace_P1 [ 0 ] , & rtP .
StateSpace_P2 [ 0 ] , & rtP . StateSpace_P4 [ 0 ] , & rtP .
Constant_Value_p2zc2q4ikw , & rtP . Constant_Value_jasz3ij2ce , & rtP .
Constant1_Value_pwvdqzuhdu , & rtP . Constant2_Value , & rtP .
Constant3_Value , & rtP . Constant4_Value_hydcaj2m2n , & rtP . Gain1_Gain , &
rtP . Gain4_Gain , & rtP . Gain_Gain_mjibw0ln1h , & rtP .
Gain_Gain_cmwuiiiv5p , & rtP . TransferFcn1_A , & rtP . TransferFcn1_C , &
rtP . Constant_Value_du0mfnud24 , & rtP . Constant_Value_komnaibfv4 , & rtP .
StateSpace_A , & rtP . StateSpace_B , & rtP . StateSpace_C , & rtP .
StateSpace_X0 , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 } , {
"unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) , SS_BOOLEAN , 0
, 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 8 , 2 , 0 } } ; static const uint_T
rtDimensionArray [ ] = { 1 , 1 , 4 , 1 , 2 , 1 , 1 , 4 , 2 , 38 } ; static
const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 } ; static const
rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const rtwCAPI_SampleTimeMap
rtSampleTimeMap [ ] = { { ( const void * ) & rtcapiStoredFloats [ 0 ] , (
const void * ) & rtcapiStoredFloats [ 0 ] , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 1 ,
0 } , { ( NULL ) , ( NULL ) , 2 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 65 , ( NULL )
, 0 , ( NULL ) , 0 } , { rtBlockParameters , 69 , rtModelParameters , 0 } , {
( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap
, rtSampleTimeMap , rtDimensionArray } , "float" , { 1145925490U ,
2449178161U , 666433519U , 3057029575U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * SOC_Modelling_GetCAPIStaticMap ( ) { return
& mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void SOC_Modelling_InitializeDataMapInfo ( ) { rtwCAPI_SetVersion ( ( *
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
void SOC_Modelling_host_InitializeDataMapInfo (
SOC_Modelling_host_DataMapInfo_T * dataMap , const char * path ) {
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
