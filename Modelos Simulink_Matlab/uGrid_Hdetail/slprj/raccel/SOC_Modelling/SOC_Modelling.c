#include "__cf_SOC_Modelling.h"
#include "rt_logging_mmi.h"
#include "SOC_Modelling_capi.h"
#include <math.h>
#include "SOC_Modelling.h"
#include "SOC_Modelling_private.h"
#include "SOC_Modelling_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 2 , & stopRequested ) ; }
rtExtModeShutdown ( 2 ) ; } const int_T gblNumToFiles = 0 ; const int_T
gblNumFrFiles = 0 ; const int_T gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 3 ; const char_T
* gbl_raccel_Version = "8.12 (R2017a) 16-Feb-2017" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj\\raccel\\SOC_Modelling\\SOC_Modelling_Jpattern.mat" ; const int_T
gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
const int_T gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [
] = { - 1 } ; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; DW rtDW ; PrevZCX rtPrevZCX ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; void MdlInitialize ( void ) { rtDW .
p2ftzle2kh = rtP . itinit1_X0 ; rtX . dshkbmlloj = 0.0 ; rtDW . lpgkirwqtj =
( 1.0 - rtP . Battery_SOC / 100.0 ) * 1.0339999999999974 / 1.0339999999999974
* 3600.0 ; if ( ssIsFirstInitCond ( rtS ) ) { rtX . eemn52m32o = 0.0 ; } rtDW
. jxsdzjlqos = 1 ; rtX . pfkbiwzhvl = rtP . StateSpace_X0 ; rtX . l22f1dk4yk
= muDoubleScalarExp ( ( 1.0 - rtP . Battery_SOC / 100.0 ) * -
61.061946632469265 * 1.0339999999999974 ) * 83.400845004248509 ; rtX .
h3gm4jgohe = 0.0 ; { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ;
sfcnInitializeConditions ( rts ) ; if ( ssGetErrorStatus ( rts ) != ( NULL )
) return ; } rtX . j4shijix5f = 0.0 ; } void MdlStart ( void ) { { void * *
slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2 = ( NULL ) ; void *
* pOSigstreamManagerAddr = ( NULL ) ; const char *
errorCreatingOSigstreamManager = ( NULL ) ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ) ; if (
errorCreatingOSigstreamManager != ( NULL ) ) { * pOSigstreamManagerAddr = (
NULL ) ; ssSetErrorStatus ( rtS , errorCreatingOSigstreamManager ) ; return ;
} } { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; sfcnStart ( rts ) ; if (
ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } MdlInitialize ( ) ; { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } } void MdlOutputs ( int_T tid ) {
boolean_T resetIntg ; ZCEventType zcEvent ; rtB . ebowq5sonn = 0.0 ; rtB .
ebowq5sonn += rtP . Currentfilter_C * rtX . dshkbmlloj ; if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { rtB . bt2plqj3b5 = rtDW . p2ftzle2kh ; rtB . ma1gbsm4cy =
rtP . R2_Gain * rtB . bt2plqj3b5 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
oefvsvaz2k = ( rtB . ebowq5sonn > rtP . Constant_Value_p2zc2q4ikw ) ; } rtB .
fynfg4qnb2 = rtDW . oefvsvaz2k ; rtB . dmmlw2nd0d = rtDW . lpgkirwqtj ; } if
( ssIsMajorTimeStep ( rtS ) ) { resetIntg = false ; zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & rtPrevZCX . cdbp1wng5n , ( rtB . fynfg4qnb2 ) ) ; if
( ( zcEvent != NO_ZCEVENT ) || ( rtDW . jxsdzjlqos != 0 ) ) { resetIntg =
true ; rtX . eemn52m32o = rtB . dmmlw2nd0d ; } if ( resetIntg ) {
ssSetSolverNeedsReset ( rtS ) ; } if ( rtX . eemn52m32o >= rtP .
inti_UpperSat ) { rtX . eemn52m32o = rtP . inti_UpperSat ; } else { if ( rtX
. eemn52m32o <= rtP . inti_LowerSat ) { rtX . eemn52m32o = rtP .
inti_LowerSat ; } } } rtB . bw41kxrfxz = rtX . eemn52m32o ; rtB . c5jq2xkgww
= rtP . Gain_Gain * rtB . bw41kxrfxz ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . dklzoi34ek = ( rtB . c5jq2xkgww >
rtB . ma1gbsm4cy ) ; rtDW . iwo5yqlhyc = ( rtB . c5jq2xkgww < rtP .
Constant9_Value ) ; } rtB . a1uqba15nh = rtDW . dklzoi34ek ; rtB . f3rfg1yrey
= rtDW . iwo5yqlhyc ; } if ( rtB . a1uqba15nh ) { rtB . erussgeov3 = rtB .
ma1gbsm4cy ; } else { if ( rtB . f3rfg1yrey ) { rtB . eladaqt13z = rtP .
Constant9_Value ; } else { rtB . eladaqt13z = rtB . c5jq2xkgww ; } rtB .
erussgeov3 = rtB . eladaqt13z ; } rtB . mo54mkczvc = 0.0 ; rtB . mo54mkczvc
+= rtP . StateSpace_C * rtX . pfkbiwzhvl ; if ( rtP . Constant5_Value > rtP .
Switch_Threshold ) { rtB . a22syqczrq = muDoubleScalarExp ( ( 1.0 / rtB .
mo54mkczvc - 0.0034112229234180458 ) * 0.0 ) ; } else { rtB . a22syqczrq =
rtP . Constant4_Value ; } rtB . je22l4jstn = - 0.0605295518538322 * rtB .
bt2plqj3b5 / ( rtB . bt2plqj3b5 - rtB . erussgeov3 ) * rtB . erussgeov3 * rtB
. a22syqczrq ; rtB . mudcvl2ext = - rtB . fynfg4qnb2 * 0.0605295518538322 *
rtB . ebowq5sonn * rtB . bt2plqj3b5 / ( rtB . bt2plqj3b5 - rtB . erussgeov3 )
* rtB . a22syqczrq ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . m01gvlvnul
= rtP . R3_Gain * rtB . bt2plqj3b5 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW
. el333hwlaj = ( rtB . c5jq2xkgww > rtB . m01gvlvnul ) ; } rtB . pydatjc2iu =
rtDW . el333hwlaj ; rtB . elvc342g14 = - rtB . m01gvlvnul * 0.999 * 0.1 *
0.9999 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . l4j1iptt5t = ( rtB .
c5jq2xkgww < rtB . elvc342g14 ) ; } rtB . c0r3d03wfe = rtDW . l4j1iptt5t ; if
( ssIsMajorTimeStep ( rtS ) ) { rtDW . lwllecwx5p = ( rtB . ebowq5sonn < rtP
. Constant_Value_jasz3ij2ce ) ; } rtB . nwsnm0uvqi = rtDW . lwllecwx5p ; } if
( rtB . pydatjc2iu ) { rtB . hf3fvjualj = rtB . m01gvlvnul ; } else { if (
rtB . c0r3d03wfe ) { rtB . aacgi45bew = rtB . elvc342g14 ; } else { rtB .
aacgi45bew = rtB . c5jq2xkgww ; } rtB . hf3fvjualj = rtB . aacgi45bew ; }
switch ( ( int32_T ) rtP . Battery_BatType ) { case 1 : rtB . ktmggdomvz [ 0
] = rtP . Constant4_Value_hydcaj2m2n * rtB . hf3fvjualj ; rtB . ktmggdomvz [
1 ] = rtP . Constant4_Value_hydcaj2m2n * rtB . ebowq5sonn ; rtB . ktmggdomvz
[ 2 ] = rtP . Constant4_Value_hydcaj2m2n * rtB . nwsnm0uvqi ; rtB .
ktmggdomvz [ 3 ] = rtP . Constant4_Value_hydcaj2m2n * rtB . bt2plqj3b5 ; rtB
. es0vlsy1wt = - rtB . ktmggdomvz [ 2 ] * 0.0605295518538322 * rtB .
ktmggdomvz [ 1 ] * ( 1.0339999999999974 / ( rtB . ktmggdomvz [ 0 ] +
0.10339999999999974 ) ) ; break ; case 2 : rtB . hm3jmuqecu [ 0 ] = rtP .
Constant1_Value_pwvdqzuhdu * rtB . hf3fvjualj ; rtB . hm3jmuqecu [ 1 ] = rtP
. Constant1_Value_pwvdqzuhdu * rtB . ebowq5sonn ; rtB . hm3jmuqecu [ 2 ] =
rtP . Constant1_Value_pwvdqzuhdu * rtB . nwsnm0uvqi ; rtB . hm3jmuqecu [ 3 ]
= rtP . Constant1_Value_pwvdqzuhdu * rtB . bt2plqj3b5 ; rtB . es0vlsy1wt = -
rtB . hm3jmuqecu [ 2 ] * 0.0605295518538322 * rtB . hm3jmuqecu [ 1 ] * rtB .
hm3jmuqecu [ 3 ] / ( rtB . hm3jmuqecu [ 3 ] * 0.1 + rtB . hm3jmuqecu [ 0 ] )
; break ; case 3 : rtB . lqsoqxpsum [ 0 ] = rtP . Constant3_Value * rtB .
hf3fvjualj ; rtB . lqsoqxpsum [ 1 ] = rtP . Constant3_Value * rtB .
ebowq5sonn ; rtB . lqsoqxpsum [ 2 ] = rtP . Constant3_Value * rtB .
nwsnm0uvqi ; rtB . lqsoqxpsum [ 3 ] = rtP . Constant3_Value * rtB .
bt2plqj3b5 ; rtB . es0vlsy1wt = - rtB . lqsoqxpsum [ 2 ] * 0.0605295518538322
* rtB . lqsoqxpsum [ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( rtB .
lqsoqxpsum [ 0 ] ) + 0.10339999999999974 ) ) ; break ; default : rtB .
ms1eeflxuz [ 0 ] = rtP . Constant2_Value * rtB . hf3fvjualj ; rtB .
ms1eeflxuz [ 1 ] = rtP . Constant2_Value * rtB . ebowq5sonn ; rtB .
ms1eeflxuz [ 2 ] = rtP . Constant2_Value * rtB . nwsnm0uvqi ; rtB .
ms1eeflxuz [ 3 ] = rtP . Constant2_Value * rtB . bt2plqj3b5 ; rtB .
es0vlsy1wt = - rtB . ms1eeflxuz [ 2 ] * 0.0605295518538322 * rtB . ms1eeflxuz
[ 1 ] * ( 1.0339999999999974 / ( muDoubleScalarAbs ( rtB . ms1eeflxuz [ 0 ] )
+ 0.10339999999999974 ) ) ; break ; } rtB . mwnu2z0rpd = rtB . es0vlsy1wt *
rtB . a22syqczrq ; rtB . pxtchs05eq = rtX . l22f1dk4yk ; switch ( ( int32_T )
rtP . Battery_BatType ) { case 1 : rtB . dwvjnb2xhx = rtB . pxtchs05eq ;
break ; case 2 : rtB . dwvjnb2xhx = muDoubleScalarExp ( - 61.061946632469265
* rtB . erussgeov3 ) * 83.400845004248509 ; break ; case 3 : rtB . dwvjnb2xhx
= rtB . pxtchs05eq ; break ; default : rtB . dwvjnb2xhx = rtB . pxtchs05eq ;
break ; } rtB . elhmuoudrv = 0.0 ; rtB . elhmuoudrv += rtP . Currentfilter1_C
* rtX . h3gm4jgohe ; if ( rtP . Constant7_Value > rtP . Switch2_Threshold ) {
rtB . kzdncfvtsn = muDoubleScalarExp ( ( 1.0 / rtB . mo54mkczvc -
0.0034112229234180458 ) * 0.0 ) * - rtB . eyraygkx4f * rtB . elhmuoudrv +
0.001 * rtB . elhmuoudrv ; } else { rtB . kzdncfvtsn = rtP . Constant6_Value
; } rtB . ebb4hiezly = ( ( ( ( rtB . je22l4jstn + rtB . mudcvl2ext ) + rtB .
mwnu2z0rpd ) + rtB . dwvjnb2xhx ) + - 0.0 * rtB . erussgeov3 ) + rtB .
kzdncfvtsn ; if ( rtP . Constant3_Value_hnmpswvc50 > rtP . Switch1_Threshold
) { rtB . joc3hf0wo0 = ( rtB . mo54mkczvc - 293.15 ) * 0.0 ; } else { rtB .
joc3hf0wo0 = rtP . Constant2_Value_fu1vg5kur3 ; } rtB . on5gayhq2w = ( rtB .
g2lfefk4ds + rtB . ebb4hiezly ) + rtB . joc3hf0wo0 ; rtB . lamriwhcak = rtP .
R1_Gain * rtB . ebowq5sonn ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . cjsskodlo5 = ( rtB . on5gayhq2w > rtP .
Constant1_Value ) ; } rtB . gmzkvvbvj2 = rtDW . cjsskodlo5 ; if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . llhrra1e5s = ( rtB . on5gayhq2w < rtB .
lamriwhcak ) ; } rtB . bzzsqio3rp = rtDW . llhrra1e5s ; } if ( rtB .
gmzkvvbvj2 ) { rtB . ekfsltdwds = rtP . Constant1_Value ; } else { if ( rtB .
bzzsqio3rp ) { rtB . il5fz1koxx = rtB . lamriwhcak ; } else { rtB .
il5fz1koxx = rtB . on5gayhq2w ; } rtB . ekfsltdwds = rtB . il5fz1koxx ; } {
SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; sfcnOutputs ( rts , 0 ) ; } if
( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . fiyfz5l1sl = rtP . R4_Gain * rtB .
bt2plqj3b5 ; } rtB . j0kccpo40y = ( 1.0 - rtB . erussgeov3 / rtB . fiyfz5l1sl
) * 100.0 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . b05sp2vsim = rtB .
j0kccpo40y >= rtP . Saturation_UpperSat ? 1 : rtB . j0kccpo40y > rtP .
Saturation_LowerSat ? 0 : - 1 ; } rtB . gxdcwqrrsh = rtDW . b05sp2vsim == 1 ?
rtP . Saturation_UpperSat : rtDW . b05sp2vsim == - 1 ? rtP .
Saturation_LowerSat : rtB . j0kccpo40y ; rtB . ij4ybcvdzr = rtP .
donotdeletethisgain_Gain * rtB . e3bmmc32eb ; rtB . jafblclliz = rtB .
ekfsltdwds - rtP . R_Gain * rtB . ij4ybcvdzr ; if ( ssIsMajorTimeStep ( rtS )
) { rtDW . gyqpteeoex = ( rtB . ij4ybcvdzr >= 0.0 ) ; } rtB . jfiirh11in =
rtDW . gyqpteeoex > 0 ? rtB . ij4ybcvdzr : - rtB . ij4ybcvdzr ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
fh54cpx1bp = ( rtB . ij4ybcvdzr < rtP . Constant_Value_du0mfnud24 ) ; } rtB .
pttz2gwc5w = rtP . Gain4_Gain * ( real_T ) rtDW . fh54cpx1bp ; } rtB .
m4wcbi2vcn = rtB . pttz2gwc5w - rtB . pxtchs05eq ; rtB . jxnoo5kkuk = rtB .
jfiirh11in * rtB . m4wcbi2vcn ; rtB . hxxgeb0kvn = rtP . Gain1_Gain * rtB .
jxnoo5kkuk ; rtB . g2m0yn3eet = rtP . Gain2_Gain * rtB . erussgeov3 ; if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . bzypwwlvga = ( rtB . elhmuoudrv >= 0.0 )
; } rtB . jm4ld54oiu = rtDW . bzypwwlvga > 0 ? rtB . elhmuoudrv : - rtB .
elhmuoudrv ; rtB . hvx1f2uin3 = 0.001 * rtB . elhmuoudrv + - rtB . ebb4hiezly
; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . e1543zebxq = ( rtB . hvx1f2uin3
>= 0.0 ) ; } rtB . ef1wyi5uxj = rtDW . e1543zebxq > 0 ? rtB . hvx1f2uin3 : -
rtB . hvx1f2uin3 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . ndfhbdjwe5 = ( rtB . elhmuoudrv < rtP .
Constant_Value_komnaibfv4 ) ; } rtB . e2tlfskas5 = rtP . Gain_Gain_mjibw0ln1h
* ( real_T ) rtDW . ndfhbdjwe5 ; } rtB . pflv2pvbva = rtB . jm4ld54oiu * rtB
. ef1wyi5uxj ; rtB . iluhumf0tr = ( 0.0 * rtB . jm4ld54oiu * rtB . mo54mkczvc
+ rtB . e2tlfskas5 ) + rtB . pflv2pvbva ; rtB . dsh3mckcs4 = 0.0 ; rtB .
dsh3mckcs4 += rtP . TransferFcn1_C * rtX . j4shijix5f ; rtB . bdsiyxiodl =
rtP . Gain_Gain_cmwuiiiv5p * rtB . dsh3mckcs4 ; rtB . j0rbw5nmli = rtB .
ppixwtawnh + rtB . bdsiyxiodl ; UNUSED_PARAMETER ( tid ) ; } void
MdlOutputsTID2 ( int_T tid ) { real_T u0 ; if ( rtP . Constant10_Value > rtP
. Switch3_Threshold ) { if ( rtP . Constant_Value > rtP .
Saturation3_UpperSat ) { rtB . g2lfefk4ds = rtP . Saturation3_UpperSat ; }
else if ( rtP . Constant_Value < rtP . Saturation3_LowerSat ) { rtB .
g2lfefk4ds = rtP . Saturation3_LowerSat ; } else { rtB . g2lfefk4ds = rtP .
Constant_Value ; } } else { rtB . g2lfefk4ds = rtP . Constant_Value ; } if (
rtP . Constant15_Value > rtP . Switch6_Threshold ) { rtB . eyraygkx4f = rtP .
Constant14_Value ; } else { rtB . eyraygkx4f = rtP . Constant16_Value ; } rtB
. ppixwtawnh = rtP . Ta_Value + rtP . Constant8_Value ; if ( rtP .
Constant11_Value > rtP . Switch4_Threshold ) { u0 = ( rtB . ppixwtawnh -
293.15 ) * 0.0 + 1.0339999999999974 ; if ( u0 > rtP . Saturation2_UpperSat )
{ rtB . nrpzodws0y = rtP . Saturation2_UpperSat ; } else if ( u0 < rtP .
Saturation2_LowerSat ) { rtB . nrpzodws0y = rtP . Saturation2_LowerSat ; }
else { rtB . nrpzodws0y = u0 ; } } else { rtB . nrpzodws0y = rtP .
Constant12_Value ; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid
) { if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . p2ftzle2kh = rtB .
nrpzodws0y ; rtDW . lpgkirwqtj = rtB . g2m0yn3eet ; } rtDW . jxsdzjlqos = 0 ;
if ( rtX . eemn52m32o == rtP . inti_UpperSat ) { switch ( rtDW . p1jdd10qxn )
{ case 3 : if ( rtB . ij4ybcvdzr < 0.0 ) { ssSetSolverNeedsReset ( rtS ) ;
rtDW . p1jdd10qxn = 1 ; } break ; case 1 : if ( rtB . ij4ybcvdzr >= 0.0 ) {
rtDW . p1jdd10qxn = 3 ; ssSetSolverNeedsReset ( rtS ) ; } break ; default :
ssSetSolverNeedsReset ( rtS ) ; if ( rtB . ij4ybcvdzr < 0.0 ) { rtDW .
p1jdd10qxn = 1 ; } else { rtDW . p1jdd10qxn = 3 ; } break ; } } else if ( rtX
. eemn52m32o == rtP . inti_LowerSat ) { switch ( rtDW . p1jdd10qxn ) { case 4
: if ( rtB . ij4ybcvdzr > 0.0 ) { ssSetSolverNeedsReset ( rtS ) ; rtDW .
p1jdd10qxn = 2 ; } break ; case 2 : if ( rtB . ij4ybcvdzr <= 0.0 ) { rtDW .
p1jdd10qxn = 4 ; ssSetSolverNeedsReset ( rtS ) ; } break ; default :
ssSetSolverNeedsReset ( rtS ) ; if ( rtB . ij4ybcvdzr > 0.0 ) { rtDW .
p1jdd10qxn = 2 ; } else { rtDW . p1jdd10qxn = 4 ; } break ; } } else { rtDW .
p1jdd10qxn = 0 ; } { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ;
sfcnUpdate ( rts , 0 ) ; if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ;
} UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID2 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ;
XDis * _rtXdis ; _rtXdis = ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot -> dshkbmlloj = 0.0 ;
_rtXdot -> dshkbmlloj += rtP . Currentfilter_A * rtX . dshkbmlloj ; _rtXdot
-> dshkbmlloj += rtB . ij4ybcvdzr ; if ( ( rtDW . p1jdd10qxn != 3 ) && ( rtDW
. p1jdd10qxn != 4 ) ) { _rtXdot -> eemn52m32o = rtB . ij4ybcvdzr ; _rtXdis ->
eemn52m32o = false ; } else { _rtXdot -> eemn52m32o = 0.0 ; if ( ( rtDW .
p1jdd10qxn == 3 ) || ( rtDW . p1jdd10qxn == 4 ) ) { _rtXdis -> eemn52m32o =
true ; } } _rtXdot -> pfkbiwzhvl = 0.0 ; _rtXdot -> pfkbiwzhvl += rtP .
StateSpace_A * rtX . pfkbiwzhvl ; _rtXdot -> pfkbiwzhvl += rtP . StateSpace_B
* rtB . j0rbw5nmli ; _rtXdot -> l22f1dk4yk = rtB . hxxgeb0kvn ; _rtXdot ->
h3gm4jgohe = 0.0 ; _rtXdot -> h3gm4jgohe += rtP . Currentfilter1_A * rtX .
h3gm4jgohe ; _rtXdot -> h3gm4jgohe += rtB . ij4ybcvdzr ; _rtXdot ->
j4shijix5f = 0.0 ; _rtXdot -> j4shijix5f += rtP . TransferFcn1_A * rtX .
j4shijix5f ; _rtXdot -> j4shijix5f += rtB . iluhumf0tr ; } void MdlProjection
( void ) { } void MdlZeroCrossings ( void ) { boolean_T anyStateSaturated ;
ZCV * _rtZCSV ; _rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ;
_rtZCSV -> kh5sfzyces = rtB . ebowq5sonn - rtP . Constant_Value_p2zc2q4ikw ;
if ( ( rtDW . p1jdd10qxn == 1 ) && ( rtX . eemn52m32o >= rtP . inti_UpperSat
) ) { _rtZCSV -> oemssfepqm = 0.0 ; } else { _rtZCSV -> oemssfepqm = rtX .
eemn52m32o - rtP . inti_UpperSat ; } if ( ( rtDW . p1jdd10qxn == 2 ) && ( rtX
. eemn52m32o <= rtP . inti_LowerSat ) ) { _rtZCSV -> a1p3fnnt3n = 0.0 ; }
else { _rtZCSV -> a1p3fnnt3n = rtX . eemn52m32o - rtP . inti_LowerSat ; }
anyStateSaturated = false ; if ( ( rtDW . p1jdd10qxn == 3 ) || ( rtDW .
p1jdd10qxn == 4 ) ) { anyStateSaturated = true ; } if ( anyStateSaturated ) {
_rtZCSV -> b3gypodet0 = rtB . ij4ybcvdzr ; } else { _rtZCSV -> b3gypodet0 =
0.0 ; } _rtZCSV -> fj020bzlq2 = rtB . c5jq2xkgww - rtB . ma1gbsm4cy ; _rtZCSV
-> jwfws4akrc = rtB . c5jq2xkgww - rtP . Constant9_Value ; _rtZCSV ->
igtus3zq5w = rtB . c5jq2xkgww - rtB . m01gvlvnul ; _rtZCSV -> an00wpd5gh =
rtB . c5jq2xkgww - rtB . elvc342g14 ; _rtZCSV -> otgh0vs3ux = rtB .
ebowq5sonn - rtP . Constant_Value_jasz3ij2ce ; _rtZCSV -> luxwl4cpkj = rtB .
on5gayhq2w - rtP . Constant1_Value ; _rtZCSV -> pw1yw1yeeq = rtB . on5gayhq2w
- rtB . lamriwhcak ; _rtZCSV -> obp4gynz5s = rtB . j0kccpo40y - rtP .
Saturation_UpperSat ; _rtZCSV -> np4le3fy54 = rtB . j0kccpo40y - rtP .
Saturation_LowerSat ; _rtZCSV -> h3omoyoiav = rtB . ij4ybcvdzr ; _rtZCSV ->
ifuwfokrga = rtB . ij4ybcvdzr - rtP . Constant_Value_du0mfnud24 ; _rtZCSV ->
ioid54ucuy = rtB . elhmuoudrv ; _rtZCSV -> plvsoaxz05 = rtB . hvx1f2uin3 ;
_rtZCSV -> gvg0iwem2e = rtB . elhmuoudrv - rtP . Constant_Value_komnaibfv4 ;
} void MdlTerminate ( void ) { { SimStruct * rts = ssGetSFunction ( rtS , 0 )
; sfcnTerminate ( rts ) ; } { if ( rt_slioCatalogue ( ) != ( NULL ) ) { void
* * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ;
rtwCreateSigstreamSlioClient ( rt_GetOSigstreamManager ( ) ,
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
rtwSaveDatasetsToMatFile ( rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( )
) , rt_GetMatSigstreamLoggingFileName ( ) ) ;
rtwOSigstreamManagerDestroyInstance ( rt_GetOSigstreamManager ( ) ) ;
rtwTerminateSlioCatalogue ( slioCatalogueAddr ) ; * slioCatalogueAddr = (
NULL ) ; } } } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
6 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ;
ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 2 ) ; ssSetNumBlocks ( rtS , 141 ) ;
ssSetNumBlockIO ( rtS , 65 ) ; ssSetNumBlockParams ( rtS , 156 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; } void raccel_set_checksum ( SimStruct *
rtS ) { ssSetChecksumVal ( rtS , 0 , 1145925490U ) ; ssSetChecksumVal ( rtS ,
1 , 2449178161U ) ; ssSetChecksumVal ( rtS , 2 , 666433519U ) ;
ssSetChecksumVal ( rtS , 3 , 3057029575U ) ; } SimStruct *
raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo ; ( void )
memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( (
char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr (
rtS , & mdlInfo ) ; { static time_T mdlPeriod [ NSAMPLE_TIMES ] ; static
time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T mdlTaskTimes [
NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ; static int_T
mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T mdlTNextWasAdjustedPtr [
NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits [ NSAMPLE_TIMES *
NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [ NSAMPLE_TIMES ] ; {
int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) { mdlPeriod [ i ] = 0.0 ;
mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ; mdlTsMap [ i ] = i ;
mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS , & mdlPeriod [ 0 ] )
; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , & mdlTaskTimes [ 0 ] ) ;
ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ; ssSetTNextWasAdjustedPtr
( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ; ssSetPerTaskSampleHitsPtr ( rtS ,
& mdlPerTaskSampleHits [ 0 ] ) ; ssSetTimeOfNextSampleHitPtr ( rtS , &
mdlTimeOfNextSampleHit [ 0 ] ) ; } ssSetSolverMode ( rtS ,
SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS , ( ( void * ) & rtB ) ) ;
( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof ( B ) ) ; }
ssSetDefaultParam ( rtS , ( real_T * ) & rtP ) ; { real_T * x = ( real_T * )
& rtX ; ssSetContStates ( rtS , x ) ; ( void ) memset ( ( void * ) x , 0 ,
sizeof ( X ) ) ; } { void * dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS
, dwork ) ; ( void ) memset ( dwork , 0 , sizeof ( DW ) ) ; } { static
DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T * ) & dtInfo , 0 ,
sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo .
numDataTypes = 14 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo
. dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = &
rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; }
SOC_Modelling_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS
, true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "SOC_Modelling" ) ;
ssSetPath ( rtS , "SOC_Modelling" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal
( rtS , 100.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo
. loggingInterval = NULL ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; }
{ rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogXSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogT (
ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 6 ] ; static
real_T absTol [ 6 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 }
; static uint8_T absTolControl [ 6 ] = { 0U , 0U , 0U , 0U , 0U , 0U } ;
static uint8_T zcAttributes [ 19 ] = { ( ZC_EVENT_ALL ) , ( 0xc0 |
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) } ; static
ssNonContDerivSigInfo nonContDerivSigInfo [ 14 ] = { { 1 * sizeof ( real_T )
, ( char * ) ( & rtB . e2tlfskas5 ) , ( NULL ) } , { 1 * sizeof ( real_T ) ,
( char * ) ( & rtB . pttz2gwc5w ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) ,
( char * ) ( & rtB . bzzsqio3rp ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) ,
( char * ) ( & rtB . gmzkvvbvj2 ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . nwsnm0uvqi ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) , (
char * ) ( & rtB . c0r3d03wfe ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . elvc342g14 ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) , (
char * ) ( & rtB . pydatjc2iu ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . m01gvlvnul ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) , (
char * ) ( & rtB . f3rfg1yrey ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) , (
char * ) ( & rtB . a1uqba15nh ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . fynfg4qnb2 ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . ma1gbsm4cy ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . bt2plqj3b5 ) , ( NULL ) } } ; ssSetSolverRelTol ( rtS ,
0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ;
ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 0.0001 ) ; ssSetSolverMaxOrder ( rtS , 5 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
14 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode15s" ) ;
ssSetVariableStepSolver ( rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol )
; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetSolverStateProjection ( rtS , 0 ) ; ssSetSolverMassMatrixType ( rtS , (
ssMatrixType ) 0 ) ; ssSetSolverMassMatrixNzMax ( rtS , 0 ) ;
ssSetModelOutputs ( rtS , MdlOutputs ) ; ssSetModelLogData ( rtS ,
rt_UpdateTXYLogVars ) ; ssSetModelLogDataIfInInterval ( rtS ,
rt_UpdateTXXFYLogVars ) ; ssSetModelUpdate ( rtS , MdlUpdate ) ;
ssSetModelDerivatives ( rtS , MdlDerivatives ) ; ssSetSolverZcSignalAttrib (
rtS , zcAttributes ) ; ssSetSolverNumZcSignals ( rtS , 19 ) ;
ssSetModelZeroCrossings ( rtS , MdlZeroCrossings ) ;
ssSetSolverConsecutiveZCsStepRelTol ( rtS , 2.8421709430404007E-13 ) ;
ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ; ssSetSolverConsecutiveZCsError
( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic ( rtS , 1 ) ;
ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ; ssSetSolverMaxConsecutiveMinStep
( rtS , 1 ) ; ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid (
rtS , INT_MIN ) ; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset (
rtS ) ; ssSetNumNonsampledZCs ( rtS , 18 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; } {
ZCSigState * zc = ( ZCSigState * ) & rtPrevZCX ; ssSetPrevZCSigState ( rtS ,
zc ) ; } { rtPrevZCX . cdbp1wng5n = UNINITIALIZED_ZCSIG ; } ssSetChecksumVal
( rtS , 0 , 1145925490U ) ; ssSetChecksumVal ( rtS , 1 , 2449178161U ) ;
ssSetChecksumVal ( rtS , 2 , 666433519U ) ; ssSetChecksumVal ( rtS , 3 ,
3057029575U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 12 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = & rtAlwaysEnabled ;
systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = & rtAlwaysEnabled ;
systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = & rtAlwaysEnabled ;
systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = & rtAlwaysEnabled ;
systemRan [ 8 ] = & rtAlwaysEnabled ; systemRan [ 9 ] = & rtAlwaysEnabled ;
systemRan [ 10 ] = & rtAlwaysEnabled ; systemRan [ 11 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } rtP . Saturation3_LowerSat = rtMinusInf ; rtP .
inti_LowerSat = rtMinusInf ; ssSetNumSFunctions ( rtS , 1 ) ; { static
SimStruct childSFunctions [ 1 ] ; static SimStruct * childSFunctionPtrs [ 1 ]
; ( void ) memset ( ( void * ) & childSFunctions [ 0 ] , 0 , sizeof (
childSFunctions ) ) ; ssSetSFunctions ( rtS , & childSFunctionPtrs [ 0 ] ) ;
ssSetSFunction ( rtS , 0 , & childSFunctions [ 0 ] ) ; { SimStruct * rts =
ssGetSFunction ( rtS , 0 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T
sfcnOffset [ 1 ] ; static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void *
) sfcnPeriod , 0 , sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * )
sfcnOffset , 0 , sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , &
sfcnPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rts , sfcnTsMap ) ; ssSetMdlInfoPtr ( rts ,
ssGetMdlInfoPtr ( rtS ) ) ; { static struct _ssSFcnModelMethods2 methods2 ;
ssSetModelMethods2 ( rts , & methods2 ) ; } { static struct
_ssSFcnModelMethods3 methods3 ; ssSetModelMethods3 ( rts , & methods3 ) ; } {
static struct _ssSFcnModelMethods4 methods4 ; ssSetModelMethods4 ( rts , &
methods4 ) ; } { static struct _ssStatesInfo2 statesInfo2 ; static
ssPeriodicStatesInfo periodicStatesInfo ; ssSetStatesInfo2 ( rts , &
statesInfo2 ) ; ssSetPeriodicStatesInfo ( rts , & periodicStatesInfo ) ; } {
static struct _ssPortInputs inputPortInfo [ 1 ] ; _ssSetNumInputPorts ( rts ,
1 ) ; ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static
real_T const * sfcnUPtrs [ 1 ] ; sfcnUPtrs [ 0 ] = & rtB . ekfsltdwds ;
ssSetInputPortSignalPtrs ( rts , 0 , ( InputPtrsType ) & sfcnUPtrs [ 0 ] ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidth ( rts , 0
, 1 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 1 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 1 ) ; { _ssSetOutputPortNumDimensions ( rts , 0
, 1 ) ; ssSetOutputPortWidth ( rts , 0 , 1 ) ; ssSetOutputPortSignal ( rts ,
0 , ( ( real_T * ) & rtB . e3bmmc32eb ) ) ; } } ssSetModelName ( rts ,
"State-Space" ) ; ssSetPath ( rts ,
"SOC_Modelling/powergui/EquivalentModel1/State-Space" ) ; if ( ssGetRTModel (
rtS ) == ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts ,
ssGetRootSS ( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) )
; ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; }
ssSetVersion ( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray *
sfcnParams [ 4 ] ; ssSetSFcnParamsCount ( rts , 4 ) ; ssSetSFcnParamsPtr (
rts , & sfcnParams [ 0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP .
StateSpace_P1_Size ) ; ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP .
StateSpace_P2_Size ) ; ssSetSFcnParam ( rts , 2 , ( mxArray * ) rtP .
StateSpace_P3_Size ) ; ssSetSFcnParam ( rts , 3 , ( mxArray * ) rtP .
StateSpace_P4_Size ) ; } ssSetRWork ( rts , ( real_T * ) & rtDW . odqq3mhlpq
[ 0 ] ) ; ssSetIWork ( rts , ( int_T * ) & rtDW . ppp2lay1vj [ 0 ] ) ;
ssSetPWork ( rts , ( void * * ) & rtDW . iq0kexwq1k [ 0 ] ) ; { static struct
_ssDWorkRecord dWorkRecord [ 3 ] ; static struct _ssDWorkAuxRecord
dWorkAuxRecord [ 3 ] ; ssSetSFcnDWork ( rts , dWorkRecord ) ;
ssSetSFcnDWorkAux ( rts , dWorkAuxRecord ) ; _ssSetNumDWork ( rts , 3 ) ;
ssSetDWorkWidth ( rts , 0 , 2 ) ; ssSetDWorkDataType ( rts , 0 , SS_DOUBLE )
; ssSetDWorkComplexSignal ( rts , 0 , 0 ) ; ssSetDWork ( rts , 0 , & rtDW .
odqq3mhlpq [ 0 ] ) ; ssSetDWorkWidth ( rts , 1 , 23 ) ; ssSetDWorkDataType (
rts , 1 , SS_INTEGER ) ; ssSetDWorkComplexSignal ( rts , 1 , 0 ) ; ssSetDWork
( rts , 1 , & rtDW . ppp2lay1vj [ 0 ] ) ; ssSetDWorkWidth ( rts , 2 , 22 ) ;
ssSetDWorkDataType ( rts , 2 , SS_POINTER ) ; ssSetDWorkComplexSignal ( rts ,
2 , 0 ) ; ssSetDWork ( rts , 2 , & rtDW . iq0kexwq1k [ 0 ] ) ; }
sfun_spid_contc ( rts ) ; sfcnInitializeSizes ( rts ) ;
sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.0 ) ;
ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 0 ;
ssSetNumNonsampledZCs ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 , 1 )
; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortBeingMerged (
rts , 0 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } } return
rtS ; } const int_T gblParameterTuningTid = 2 ; void
MdlOutputsParameterSampleTime ( int_T tid ) { MdlOutputsTID2 ( tid ) ; }
