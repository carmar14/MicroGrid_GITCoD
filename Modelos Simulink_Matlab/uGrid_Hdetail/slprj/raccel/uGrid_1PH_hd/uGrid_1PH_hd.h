#include "__cf_uGrid_1PH_hd.h"
#ifndef RTW_HEADER_uGrid_1PH_hd_h_
#define RTW_HEADER_uGrid_1PH_hd_h_
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "rtw_modelmap.h"
#ifndef uGrid_1PH_hd_COMMON_INCLUDES_
#define uGrid_1PH_hd_COMMON_INCLUDES_
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
#include "uGrid_1PH_hd_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_defines.h"
#define MODEL_NAME uGrid_1PH_hd
#define NSAMPLE_TIMES (5) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (142) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (61)   
#elif NCSTATES != 61
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
typedef struct { real_T e3galh2ets ; } nz3ncpxmv0 ; typedef struct { real_T
j4xgvi25fi [ 40000 ] ; real_T hlckmgcf2l [ 40000 ] ; real_T f0ix3jjnpf [ 200
] ; real_T m0fwlvevxl [ 40000 ] ; real_T ntofjobsep [ 200 ] ; real_T
bvdahqrkgv [ 200 ] ; real_T fyq3rr4pxa [ 200 ] ; real_T deyysf5gta [ 200 ] ;
} jawacxuwmc ; typedef struct { real_T p4suqxiggq [ 2 ] ; real_T g1q3oofyrj [
200 ] ; } nzd2crx5th ; typedef struct { real_T mgzovusthk [ 200 ] ; real_T
n1jqioztuc [ 2 ] ; } e325ebrcqg ; typedef struct { real_T eh1uxfdfxk ; real_T
fn4ajroglo ; real_T le51iuyvkp ; real_T aunpobcu44 ; real_T jc05hb1vpg ;
real_T eczkwep1fc ; real_T haih3brbef ; real_T ddj2ljlqar ; real_T fhtkgnfwcd
; real_T mlexdgwnj1 ; real_T izwvjz1tew ; real_T kjzt3xvlg4 ; real_T
fkqc2ypzow ; real_T dmlly3udcf ; real_T bk1xuitdvv ; real_T aqe3urztoo [ 8 ]
; real_T bmqsiz2toy [ 54 ] ; real_T jhuzfee1rx ; real_T d5oxoszzwe ; real_T
ptnr1vtbjm ; real_T puuyej0ojx ; real_T nk2fzzksvb ; real_T gwjcoav1lk ;
real_T b1utvav4hj ; real_T btdi3tstnl ; real_T iq42atba5o ; real_T m1it3g5wdk
; real_T cypxcf4iuh ; real_T cr3o3bcjno ; real_T i0tzocdcou ; real_T
hbd0hneu5u [ 3 ] ; real_T o3zd3lrgcz ; real_T hxnhqtjvzy ; real_T o3l2gemtct
; real_T lmlfl3t04h [ 4 ] ; real_T ewo1cwunpw ; real_T m4dlwah4c3 ; real_T
jvajaeojzw ; real_T jr3vymwmkc ; real_T l2k5p2r0wh ; real_T d4o1qxqtvz ;
real_T obugd5y2ad ; real_T hbhwwpohe0 ; real_T bbzwoxa50q ; real_T cao3opsb5y
; real_T f2y40zjr03 ; real_T jvnydmoxuc ; real_T dbr0navviv ; real_T
hsj4xty3ld ; real_T j1nlrdh0gl ; real_T oe0msxmkyu ; real_T du31rtbcg2 ;
real_T aoljwchi5z ; real_T pfa5sut0yt ; real_T chc3tp5kgw ; real_T pgxj3vimkq
; real_T hchtpl1d3p ; real_T ke5galvxnd ; real_T njnf2oxsm1 ; real_T
bivhyu0fbz ; real_T m1ekwvon4u ; real_T gxoc5j0ev2 [ 3 ] ; real_T czdizqkiy5
; real_T kam4wd2zke ; real_T pzlqwcc3xg ; real_T aeiozt25lb ; real_T
posuhuud3g ; real_T bu3zpefbt0 ; real_T hilnaqgqvk ; real_T cvy5dhiqlw ;
real_T ksmj2ks1ry ; real_T jt50mttmmc ; real_T i3k3ladn4s ; real_T iusqw5vol4
; real_T ioirosbkbv [ 2 ] ; real_T bkz5gblmt2 [ 200 ] ; real_T jbv4oeizoh [ 2
] ; real_T jnz2ccaipm [ 2 ] ; real_T ewsxkq0wzp [ 200 ] ; real_T la0fvqhabk [
2 ] ; real_T cazq3bcp4v [ 200 ] ; real_T el0hi2mpax ; real_T pviaul0ind ;
real_T dvxrwfxmke ; real_T k2r1v43eue [ 200 ] ; real_T ms400ves34 ; real_T
bkld5544on ; real_T hvk4gr05kp ; real_T kyq4ddwnt5 ; real_T katlkd05we ;
real_T e312d3rw1k ; real_T okmcolqmmp ; real_T d3wmvrdgp5 ; real_T orga5rxyo4
; real_T faenhustsh ; real_T c1ucoxgukl ; real_T nnkwaky0vo ; real_T
grqskhisxe ; real_T nwi2u1x5jv ; real_T pgv3a43g3a ; real_T bywih0a2yp ;
real_T gok32izhkr ; real_T pkaciejeq4 ; real_T ahbxhfing1 ; real_T nkt1wwkpxk
; real_T pr32bh5ab0 ; real_T gebkbee1ff ; real_T oashgqc3jo ; real_T
mbhd03n5qp ; real_T ld2pf1geuj ; real_T ngwlyiii4t ; real_T mmhpsmc2xu ;
real_T foapkh0xzh ; real_T fwwgncxyps ; real_T eol02jxukg ; real_T hqdf5p5g5k
; real_T ordb0vcov4 ; real_T ec0lm5oxpo ; real_T jbkeye4siv ; real_T
aj3gcmhe30 ; real_T pakxhumxso ; nzd2crx5th jlxfvkiytb ; nzd2crx5th
mpnopdrqui ; jawacxuwmc csjm5qcu5l ; jawacxuwmc hk2fxt1axd ; nz3ncpxmv0
pncwbu0dto ; nz3ncpxmv0 n4wqmwk0ih ; nz3ncpxmv0 d5gh3z0nbz ; } B ; typedef
struct { real_T hunjvlw225 ; real_T awjkgmzkcd ; real_T hdyfm4w10o ; real_T
or3xy3rhzp ; real_T bmgxo1oskk ; real_T jojdexj25k ; real_T a0h21jsgxr ;
real_T i0isqogxyp ; real_T lpcfsl5mnp [ 200 ] ; real_T msyicwvkh0 [ 2 ] ;
real_T fkh51dxhfd [ 200 ] ; real_T gye4sfowa3 [ 2 ] ; real_T lr5gxlhuv0 ;
real_T fncmzwylce ; real_T kecva0uppz ; real_T h5y1kpt3c4 ; real_T jl0qdrh0vh
; real_T mnsutipu10 ; real_T l5wlqfkerm ; real_T nonseywoew ; real_T
hshq4edjvp [ 2 ] ; void * czgjtdfwfq [ 22 ] ; struct { void * LoggedData [ 2
] ; } gidtjgtmom ; struct { void * LoggedData [ 2 ] ; } jccz1ddyws ; struct {
void * LoggedData [ 2 ] ; } dclcvurcmy ; struct { void * LoggedData ; }
nxjrrg4ysr ; struct { void * LoggedData ; } ocecg4ocie ; struct { void *
LoggedData ; } lspsi4qeub ; struct { void * LoggedData ; } mgssy21dt0 ;
struct { void * LoggedData ; } kh5noeu1rm ; struct { void * LoggedData ; }
cgn3m4t1dq ; struct { void * LoggedData [ 2 ] ; } bqpn4jk0dr ; void *
hjgbl1mg0e [ 8 ] ; void * ft0tza0nlt [ 8 ] ; struct { void * LoggedData [ 2 ]
; } ds4l2typev ; struct { void * LoggedData ; } glvudhqxv5 ; struct { void *
LoggedData [ 2 ] ; } ma225rjwd5 ; struct { void * LoggedData [ 2 ] ; }
fisxfl23bd ; struct { void * LoggedData [ 2 ] ; } n3t2d1e0mr ; int_T
bbj41wyypv [ 23 ] ; int_T ji0mtgeizs [ 28 ] ; int_T ohg4iyas0q ; int_T
peojzkhro0 ; int_T adqiufmg2m ; int_T k4n10av0pz ; int_T l1tbjsdipx ; int_T
kam4r3pt4e ; e325ebrcqg jlxfvkiytb ; e325ebrcqg mpnopdrqui ; } DW ; typedef
struct { real_T jx0idbczpq [ 21 ] ; real_T o2rpnlhogc [ 4 ] ; real_T
a5and4muvl [ 4 ] ; real_T o245a1iahg [ 4 ] ; real_T a1wiorvzgd [ 4 ] ; real_T
hmbvv15kxc [ 2 ] ; real_T hw15qv3d4x [ 2 ] ; real_T ljajmjnqe2 [ 2 ] ; real_T
kgdfli42ke [ 2 ] ; real_T bs0r3mhztf ; real_T gkhfezstmh ; real_T igeyfxj4d3
; real_T l4hu0qjkbj ; real_T eqzkvazvwb [ 2 ] ; real_T p5a2dgn4de ; real_T
cw133mrukf [ 2 ] ; real_T kegs3pqnrg [ 2 ] ; real_T ebefh4121m [ 2 ] ; real_T
kyzdqe5rlf ; real_T dnsndnihyx ; real_T a1dsasyim2 ; } X ; typedef struct {
real_T jx0idbczpq [ 21 ] ; real_T o2rpnlhogc [ 4 ] ; real_T a5and4muvl [ 4 ]
; real_T o245a1iahg [ 4 ] ; real_T a1wiorvzgd [ 4 ] ; real_T hmbvv15kxc [ 2 ]
; real_T hw15qv3d4x [ 2 ] ; real_T ljajmjnqe2 [ 2 ] ; real_T kgdfli42ke [ 2 ]
; real_T bs0r3mhztf ; real_T gkhfezstmh ; real_T igeyfxj4d3 ; real_T
l4hu0qjkbj ; real_T eqzkvazvwb [ 2 ] ; real_T p5a2dgn4de ; real_T cw133mrukf
[ 2 ] ; real_T kegs3pqnrg [ 2 ] ; real_T ebefh4121m [ 2 ] ; real_T kyzdqe5rlf
; real_T dnsndnihyx ; real_T a1dsasyim2 ; } XDot ; typedef struct { boolean_T
jx0idbczpq [ 21 ] ; boolean_T o2rpnlhogc [ 4 ] ; boolean_T a5and4muvl [ 4 ] ;
boolean_T o245a1iahg [ 4 ] ; boolean_T a1wiorvzgd [ 4 ] ; boolean_T
hmbvv15kxc [ 2 ] ; boolean_T hw15qv3d4x [ 2 ] ; boolean_T ljajmjnqe2 [ 2 ] ;
boolean_T kgdfli42ke [ 2 ] ; boolean_T bs0r3mhztf ; boolean_T gkhfezstmh ;
boolean_T igeyfxj4d3 ; boolean_T l4hu0qjkbj ; boolean_T eqzkvazvwb [ 2 ] ;
boolean_T p5a2dgn4de ; boolean_T cw133mrukf [ 2 ] ; boolean_T kegs3pqnrg [ 2
] ; boolean_T ebefh4121m [ 2 ] ; boolean_T kyzdqe5rlf ; boolean_T dnsndnihyx
; boolean_T a1dsasyim2 ; } XDis ; typedef struct { real_T jx0idbczpq [ 21 ] ;
real_T o2rpnlhogc [ 4 ] ; real_T a5and4muvl [ 4 ] ; real_T o245a1iahg [ 4 ] ;
real_T a1wiorvzgd [ 4 ] ; real_T hmbvv15kxc [ 2 ] ; real_T hw15qv3d4x [ 2 ] ;
real_T ljajmjnqe2 [ 2 ] ; real_T kgdfli42ke [ 2 ] ; real_T bs0r3mhztf ;
real_T gkhfezstmh ; real_T igeyfxj4d3 ; real_T l4hu0qjkbj ; real_T eqzkvazvwb
[ 2 ] ; real_T p5a2dgn4de ; real_T cw133mrukf [ 2 ] ; real_T kegs3pqnrg [ 2 ]
; real_T ebefh4121m [ 2 ] ; real_T kyzdqe5rlf ; real_T dnsndnihyx ; real_T
a1dsasyim2 ; } CStateAbsTol ; typedef struct { real_T gaarmsig2l [ 28 ] ;
real_T d0kpyu0clq ; real_T i53t3tzxgv ; real_T esyfjv0amx ; real_T ksf10o1ok5
; real_T e0peb0jrng ; real_T okqtswz5fa ; real_T ganutxcomd ; real_T
ades2rganv ; real_T foxbmngzxi ; real_T bf4cj0ngln ; real_T m25vfldd2c ;
real_T f1mrcksylm ; } ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
DataMapInfo ; struct P_ { real_T G [ 40000 ] ; real_T GF [ 40000 ] ; real_T
DC_2_Amplitude ; real_T DC540V_Amplitude ; real_T DC_1_Amplitude ; real_T
uPh_Inverter_bio_st_time ; real_T uPh_Inverter_diesel_st_time ; real_T
uPh_Inverter_bio1_st_time ; real_T eee_Value ; real_T eee_Value_kjv1lt1rls ;
real_T eee_Value_luohiy4ktt ; real_T eee_Value_la1sxv22ch ; real_T
eee_Value_n2jnc2ydfy ; real_T eee_Value_eahotdmisl ; real_T
eee_Value_lkmzkp31k3 ; real_T eee_Value_akbbszpib5 ; real_T
eee_Value_cnrsszzthq ; real_T eee_Value_gv0u2ahtt0 ; real_T
eee_Value_h3by2pvwt1 ; real_T eee_Value_lskvq5tfxu ; real_T
StateSpace_P1_Size [ 2 ] ; real_T StateSpace_P1 [ 7840 ] ; real_T
StateSpace_P2_Size [ 2 ] ; real_T StateSpace_P2 [ 4 ] ; real_T
StateSpace_P3_Size [ 2 ] ; real_T StateSpace_P3 [ 21 ] ; real_T
StateSpace_P4_Size [ 2 ] ; real_T StateSpace_P4 [ 7000 ] ; real_T
StateSpace_P5_Size [ 2 ] ; real_T StateSpace_P5 [ 54 ] ; real_T
StateSpace_P6_Size [ 2 ] ; real_T StateSpace_P6 [ 27 ] ; real_T
StateSpace_P7_Size [ 2 ] ; real_T StateSpace_P7 [ 27 ] ; real_T
StateSpace_P8_Size [ 2 ] ; real_T StateSpace_P8 [ 27 ] ; real_T
StateSpace_P9_Size [ 2 ] ; real_T StateSpace_P9 ; real_T StateSpace_P10_Size
[ 2 ] ; real_T StateSpace_P10 ; real_T P_lp_bio_Value ; real_T Constant_Value
; real_T Step1_Time ; real_T Step1_Y0 ; real_T Step1_YFinal ; real_T
Step2_Time ; real_T Step2_Y0 ; real_T Step2_YFinal ; real_T Step3_Time ;
real_T Step3_Y0 ; real_T Step3_YFinal ; real_T Constant1_Value ; real_T
Constant5_Value ; real_T P_lp_diesel_Value ; real_T Hw2_A [ 7 ] ; real_T
Hw2_B ; real_T Hw2_C ; real_T Hw2_X0 ; real_T Hw6_A [ 7 ] ; real_T Hw6_B ;
real_T Hw6_C ; real_T Hw6_X0 ; real_T Hw1_A [ 7 ] ; real_T Hw1_B ; real_T
Hw1_C ; real_T Hw1_X0 ; real_T Hw3_A [ 7 ] ; real_T Hw3_B ; real_T Hw3_C ;
real_T Hw3_X0 ; real_T Hw4_A [ 3 ] ; real_T Hw4_B ; real_T Hw4_C ; real_T
Hw4_X0 ; real_T Hw1_A_kbzflcjjyj [ 3 ] ; real_T Hw1_B_o4lzhk3gnx ; real_T
Hw1_C_i3w2ow0rwv ; real_T Hw1_X0_jjtb1pylbl ; real_T Hw7_A [ 3 ] ; real_T
Hw7_B ; real_T Hw7_C ; real_T Hw7_X0 ; real_T Hw3_A_ngyitj1gem [ 3 ] ; real_T
Hw3_B_mskofuv4se ; real_T Hw3_C_mvzrzdbpid ; real_T Hw3_X0_fiftn0ykcd ;
real_T ttkernel_P1_Size [ 2 ] ; real_T ttkernel_P1 [ 8 ] ; real_T
ttkernel_P2_Size [ 2 ] ; real_T ttkernel_P2 ; real_T ttkernel_P3_Size [ 2 ] ;
real_T ttkernel_P3 [ 2 ] ; real_T ttkernel_P4_Size [ 2 ] ; real_T ttkernel_P4
; real_T ttkernel_P5_Size [ 2 ] ; real_T ttkernel_P5 ; real_T
ttkernel_P6_Size [ 2 ] ; real_T ttkernel_P7_Size [ 2 ] ; real_T ttkernel_P7 [
2 ] ; real_T ttkernel_P1_Size_phmcx0huck [ 2 ] ; real_T
ttkernel_P1_kegxebksg2 [ 11 ] ; real_T ttkernel_P2_Size_nfb4tmfvso [ 2 ] ;
real_T ttkernel_P3_Size_ijstpct3xa [ 2 ] ; real_T ttkernel_P3_gqnydskipg [ 2
] ; real_T ttkernel_P4_Size_hjw55qqsby [ 2 ] ; real_T ttkernel_P4_czxg5elx0u
; real_T ttkernel_P5_Size_b1wzcdhzz4 [ 2 ] ; real_T ttkernel_P5_eeyd0jrw1c ;
real_T ttkernel_P6_Size_dgpycuraph [ 2 ] ; real_T ttkernel_P7_Size_f3wuxlprs0
[ 2 ] ; real_T ttkernel_P7_hxqdtrr2zt [ 2 ] ; real_T donotdeletethisgain_Gain
; real_T TransferFcn_A ; real_T TransferFcn_C ; real_T TransferFcn1_A ;
real_T TransferFcn1_C ; real_T donotdeletethisgain_Gain_khgfu0zvf4 ; real_T
gate_Value ; real_T gate_Value_o1atqxnff5 ; real_T gate_Value_ivxretxarq ;
real_T gate_Value_p51ecoshdm ; real_T Constant1_Value_ihao24qd3r ; real_T
Constant_Value_j5zaiux01a ; real_T Constant3_Value ; real_T Constant2_Value ;
real_T uib1_Gain ; real_T Gain_Gain ; real_T Step_Y0 ; real_T Step_YFinal ;
real_T Step_Y0_legsdikta1 ; real_T Step_YFinal_n0k22wxmnl ; real_T C4_Value ;
real_T Step_Y0_p2wkubb2bf ; real_T Step_YFinal_i1efzfr20g ; real_T
LookUpTable_XData [ 5 ] ; real_T LookUpTable_YData [ 5 ] ; real_T
Switch3_Threshold ; real_T HitCrossing_Offset ; real_T
donotdeletethisgain_Gain_aqki2j0pex ; real_T TransferFcn_A_jmuxqs4cyv ;
real_T TransferFcn_C_assnubnh1r ; real_T TransferFcn1_A_gyfo1spe1k ; real_T
TransferFcn1_C_c0ncjvfshw ; real_T donotdeletethisgain_Gain_malkwg3eo0 ;
real_T gate_Value_evjry40iys ; real_T gate_Value_duqg5wmkuu ; real_T
gate_Value_but4pbwkg3 ; real_T gate_Value_jhlex4egqq ; real_T
Constant1_Value_oo43yhpvhj ; real_T ttkernel_P1_Size_i4hx3ztcux [ 2 ] ;
real_T ttkernel_P1_dau5ffdd1u [ 11 ] ; real_T ttkernel_P2_Size_mzxvmttuan [ 2
] ; real_T ttkernel_P3_Size_iim3bl5h1p [ 2 ] ; real_T ttkernel_P3_alumkyzhoh
[ 2 ] ; real_T ttkernel_P4_Size_gchejzj5nn [ 2 ] ; real_T
ttkernel_P4_pykitjxifn ; real_T ttkernel_P5_Size_fql1qn3mk2 [ 2 ] ; real_T
ttkernel_P5_a0o1uqg3oc ; real_T ttkernel_P6_Size_lwwqe3gebn [ 2 ] ; real_T
ttkernel_P7_Size_cn31xdj5c3 [ 2 ] ; real_T ttkernel_P7_gqqekjm05a [ 2 ] ;
real_T Constant_Value_lpxxzcor1x ; real_T Constant3_Value_j5dz1hgiog ; real_T
Constant2_Value_ecraziuear ; real_T uib1_Gain_hysnw5mqld ; real_T
Gain_Gain_mygr3ck4si ; real_T Step_Y0_nw5wkv3ooz ; real_T
Step_YFinal_nmjbi1q1jk ; real_T Step_Y0_efnefifyw2 ; real_T
Step_YFinal_onn4xqhkyw ; real_T C4_Value_aagigtr1s1 ; real_T
Step_Y0_h0xozw0tcv ; real_T Step_YFinal_eksdyefhpg ; real_T
LookUpTable_XData_h2at0lfgy0 [ 5 ] ; real_T LookUpTable_YData_kfsva1ia4o [ 5
] ; real_T Switch3_Threshold_obfdmxriwc ; real_T
HitCrossing_Offset_dtlkzxqizf ; real_T Energy_Value ; real_T
Energy_Value_llumdghwbm ; real_T Memory1_X0 ; real_T Memory2_X0 ; real_T
Memory3_X0 ; real_T Memory4_X0 ; real_T Energy_Value_in0imrdvbj ; real_T
Hw2_A_jjvwx3g4vm [ 3 ] ; real_T Hw2_B_ag4uxupnle ; real_T Hw2_C_c1pm2juzi1 ;
real_T Hw2_X0_dwpd2y1z3s ; real_T donotdeletethisgain_Gain_muoknirdms ;
real_T SwitchingFilterCapacitor1_Value ; real_T SineWave_Amp ; real_T
SineWave_Bias ; real_T SineWave_Freq ; real_T SineWave_Phase ; real_T
Hi_Pass1_A ; real_T Hi_Pass1_B ; real_T Hi_Pass1_C ; real_T Hi_Pass1_D ;
real_T Hi_Pass1_X0 ; real_T Hw5_A [ 3 ] ; real_T Hw5_B ; real_T Hw5_C ;
real_T Hw5_X0 ; real_T Gain2_Gain ; real_T TransferFcn1_A_mhbp45m11f [ 2 ] ;
real_T TransferFcn1_C_d5ieeyryfz [ 2 ] ; real_T Constant2_Value_bnaip2qh1m ;
real_T Hw6_A_ljeu45oawb [ 3 ] ; real_T Hw6_B_ovbhidad3v ; real_T
Hw6_C_i2gbmjev5d ; real_T Hw6_X0_eqbfuwse4i ; real_T
donotdeletethisgain_Gain_pfs1e1lqot ; real_T TransferFcn_A_fo4eivk0cz ;
real_T TransferFcn_C_cidb1uzs1l ; real_T TransferFcn1_A_gbpccbxwkq ; real_T
TransferFcn1_C_iymr30cu1l ; real_T donotdeletethisgain_Gain_gwkq5frpca ;
real_T donotdeletethisgain_Gain_lmwc2zhiza ; real_T TransferFcn2_A ; real_T
TransferFcn2_C ; real_T gate_Value_i5kbinpwee ; real_T gate_Value_bt41vtykjz
; real_T gate_Value_h10hkkwhs2 ; real_T gate_Value_ojlyotiqqk ; real_T
Constant1_Value_cqn15imi2r ; real_T Constant_Value_ohbjm2j0ij ; real_T
Constant3_Value_hzs44l22rj ; real_T Constant2_Value_efe4bfc10e ; real_T
uib1_Gain_buhnycyzrk ; real_T Gain_Gain_bktwk0ibkx ; real_T
Step_Y0_m1xcmpkjwa ; real_T Step_YFinal_h3jz4xlvs5 ; real_T
Step_Y0_flotjz4byv ; real_T Step_YFinal_iajv2qdnwe ; real_T
C4_Value_lgay0qrqwc ; real_T Step_Y0_ji235vnkbb ; real_T
Step_YFinal_jlaji2juh5 ; real_T LookUpTable_XData_djytinpfos [ 5 ] ; real_T
LookUpTable_YData_oewicl1qan [ 5 ] ; real_T Switch3_Threshold_ohskz1p5nh ;
real_T HitCrossing_Offset_ez0hdaiej5 ; } ; extern const real_T
uGrid_1PH_hd_RGND ; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B
rtB ; extern X rtX ; extern DW rtDW ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * uGrid_1PH_hd_GetCAPIStaticMap ( void ) ;
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
