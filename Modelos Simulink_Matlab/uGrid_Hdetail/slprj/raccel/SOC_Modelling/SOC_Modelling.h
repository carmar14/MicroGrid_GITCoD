#include "__cf_SOC_Modelling.h"
#ifndef RTW_HEADER_SOC_Modelling_h_
#define RTW_HEADER_SOC_Modelling_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef SOC_Modelling_COMMON_INCLUDES_
#define SOC_Modelling_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "SOC_Modelling_types.h"
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#define MODEL_NAME SOC_Modelling
#define NSAMPLE_TIMES (3) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (65) 
#define NUM_ZC_EVENTS (1) 
#ifndef NCSTATES
#define NCSTATES (6)   
#elif NCSTATES != 6
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T g2lfefk4ds ; real_T bt2plqj3b5 ; real_T ma1gbsm4cy ;
real_T ebowq5sonn ; real_T fynfg4qnb2 ; real_T dmmlw2nd0d ; real_T bw41kxrfxz
; real_T c5jq2xkgww ; real_T erussgeov3 ; real_T mo54mkczvc ; real_T
a22syqczrq ; real_T je22l4jstn ; real_T mudcvl2ext ; real_T m01gvlvnul ;
real_T elvc342g14 ; real_T hf3fvjualj ; real_T nwsnm0uvqi ; real_T es0vlsy1wt
; real_T mwnu2z0rpd ; real_T pxtchs05eq ; real_T dwvjnb2xhx ; real_T
eyraygkx4f ; real_T elhmuoudrv ; real_T kzdncfvtsn ; real_T ebb4hiezly ;
real_T joc3hf0wo0 ; real_T on5gayhq2w ; real_T lamriwhcak ; real_T ekfsltdwds
; real_T e3bmmc32eb ; real_T fiyfz5l1sl ; real_T j0kccpo40y ; real_T
gxdcwqrrsh ; real_T ij4ybcvdzr ; real_T jafblclliz ; real_T jfiirh11in ;
real_T pttz2gwc5w ; real_T m4wcbi2vcn ; real_T jxnoo5kkuk ; real_T hxxgeb0kvn
; real_T ppixwtawnh ; real_T g2m0yn3eet ; real_T jm4ld54oiu ; real_T
hvx1f2uin3 ; real_T ef1wyi5uxj ; real_T e2tlfskas5 ; real_T pflv2pvbva ;
real_T iluhumf0tr ; real_T nrpzodws0y ; real_T dsh3mckcs4 ; real_T bdsiyxiodl
; real_T j0rbw5nmli ; real_T aacgi45bew ; real_T eladaqt13z ; real_T
il5fz1koxx ; real_T ktmggdomvz [ 4 ] ; real_T hm3jmuqecu [ 4 ] ; real_T
lqsoqxpsum [ 4 ] ; real_T ms1eeflxuz [ 4 ] ; boolean_T a1uqba15nh ; boolean_T
f3rfg1yrey ; boolean_T pydatjc2iu ; boolean_T c0r3d03wfe ; boolean_T
gmzkvvbvj2 ; boolean_T bzzsqio3rp ; } B ; typedef struct { real_T p2ftzle2kh
; real_T lpgkirwqtj ; real_T odqq3mhlpq [ 2 ] ; void * iq0kexwq1k [ 22 ] ;
struct { void * LoggedData ; } pktighfbvb ; struct { void * LoggedData ; }
fqs1qzdhi3 ; struct { void * LoggedData ; } a3eb3o3lyi ; int_T jxsdzjlqos ;
int_T ppp2lay1vj [ 23 ] ; int_T p1jdd10qxn ; int_T b05sp2vsim ; int_T
gyqpteeoex ; int_T bzypwwlvga ; int_T e1543zebxq ; boolean_T oefvsvaz2k ;
boolean_T dklzoi34ek ; boolean_T iwo5yqlhyc ; boolean_T el333hwlaj ;
boolean_T l4j1iptt5t ; boolean_T lwllecwx5p ; boolean_T cjsskodlo5 ;
boolean_T llhrra1e5s ; boolean_T fh54cpx1bp ; boolean_T ndfhbdjwe5 ; } DW ;
typedef struct { real_T dshkbmlloj ; real_T eemn52m32o ; real_T pfkbiwzhvl ;
real_T l22f1dk4yk ; real_T h3gm4jgohe ; real_T j4shijix5f ; } X ; typedef
struct { real_T dshkbmlloj ; real_T eemn52m32o ; real_T pfkbiwzhvl ; real_T
l22f1dk4yk ; real_T h3gm4jgohe ; real_T j4shijix5f ; } XDot ; typedef struct
{ boolean_T dshkbmlloj ; boolean_T eemn52m32o ; boolean_T pfkbiwzhvl ;
boolean_T l22f1dk4yk ; boolean_T h3gm4jgohe ; boolean_T j4shijix5f ; } XDis ;
typedef struct { real_T dshkbmlloj ; real_T eemn52m32o ; real_T pfkbiwzhvl ;
real_T l22f1dk4yk ; real_T h3gm4jgohe ; real_T j4shijix5f ; } CStateAbsTol ;
typedef struct { real_T kh5sfzyces ; real_T lusbgowdat ; real_T oemssfepqm ;
real_T a1p3fnnt3n ; real_T b3gypodet0 ; real_T fj020bzlq2 ; real_T jwfws4akrc
; real_T igtus3zq5w ; real_T an00wpd5gh ; real_T otgh0vs3ux ; real_T
luxwl4cpkj ; real_T pw1yw1yeeq ; real_T obp4gynz5s ; real_T np4le3fy54 ;
real_T h3omoyoiav ; real_T ifuwfokrga ; real_T ioid54ucuy ; real_T plvsoaxz05
; real_T gvg0iwem2e ; } ZCV ; typedef struct { ZCSigState cdbp1wng5n ; }
PrevZCX ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ;
struct P_ { real_T Battery_BatType ; real_T Battery_SOC ; real_T
Constant1_Value ; real_T Constant_Value ; real_T Saturation3_UpperSat ;
real_T Saturation3_LowerSat ; real_T Constant10_Value ; real_T
Switch3_Threshold ; real_T itinit1_X0 ; real_T Constant13_Value ; real_T
Switch5_Threshold ; real_T R2_Gain ; real_T Currentfilter_A ; real_T
Currentfilter_C ; real_T Constant_Value_p2zc2q4ikw ; real_T inti_UpperSat ;
real_T inti_LowerSat ; real_T Gain_Gain ; real_T Constant9_Value ; real_T
StateSpace_A ; real_T StateSpace_B ; real_T StateSpace_C ; real_T
StateSpace_X0 ; real_T Constant5_Value ; real_T Constant4_Value ; real_T
Switch_Threshold ; real_T Constant4_Value_hydcaj2m2n ; real_T R3_Gain ;
real_T Constant_Value_jasz3ij2ce ; real_T Constant1_Value_pwvdqzuhdu ; real_T
Constant3_Value ; real_T Constant2_Value ; real_T Constant14_Value ; real_T
Constant15_Value ; real_T Constant16_Value ; real_T Switch6_Threshold ;
real_T Currentfilter1_A ; real_T Currentfilter1_C ; real_T Constant7_Value ;
real_T Constant6_Value ; real_T Switch2_Threshold ; real_T
Constant3_Value_hnmpswvc50 ; real_T Constant2_Value_fu1vg5kur3 ; real_T
Switch1_Threshold ; real_T R1_Gain ; real_T StateSpace_P1_Size [ 2 ] ; real_T
StateSpace_P1 [ 2 ] ; real_T StateSpace_P2_Size [ 2 ] ; real_T StateSpace_P2
[ 4 ] ; real_T StateSpace_P3_Size [ 2 ] ; real_T StateSpace_P4_Size [ 2 ] ;
real_T StateSpace_P4 [ 76 ] ; real_T R4_Gain ; real_T Saturation_UpperSat ;
real_T Saturation_LowerSat ; real_T donotdeletethisgain_Gain ; real_T R_Gain
; real_T Constant11_Value ; real_T Constant12_Value ; real_T Constant8_Value
; real_T Constant_Value_du0mfnud24 ; real_T Gain4_Gain ; real_T Gain1_Gain ;
real_T Ta_Value ; real_T Gain2_Gain ; real_T Constant_Value_komnaibfv4 ;
real_T Gain_Gain_mjibw0ln1h ; real_T Saturation2_UpperSat ; real_T
Saturation2_LowerSat ; real_T Switch4_Threshold ; real_T TransferFcn1_A ;
real_T TransferFcn1_C ; real_T Gain_Gain_cmwuiiiv5p ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern PrevZCX rtPrevZCX ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * SOC_Modelling_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
size_t gblCurrentSFcnIdx ; extern size_t * gblChildIdxToInfoIdx ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
