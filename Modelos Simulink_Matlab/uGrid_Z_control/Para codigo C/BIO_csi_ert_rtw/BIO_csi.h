/*
 * File: BIO_csi.h
 *
 * Code generated for Simulink model 'BIO_csi'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Fri Jul 27 10:56:30 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_h_
#define RTW_HEADER_BIO_csi_h_
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>
#ifndef BIO_csi_COMMON_INCLUDES_
# define BIO_csi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* BIO_csi_COMMON_INCLUDES_ */

#include "BIO_csi_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_look.h"
#include "rt_look1d.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T dv0[40000];
  int32_T f_data[40000];
  real_T StateSpace_o1[11];            /* '<S53>/State-Space' */
  real_T StateSpace_o2[9];             /* '<S53>/State-Space' */
  real_T Delay90zV;                    /* '<S2>/Delay90(z)V' */
  real_T rt[2];                        /* '<S4>/rt' */
  real_T rt1[2];                       /* '<S4>/rt1' */
  real_T Memory1[200];                 /* '<S4>/Memory1' */
  real_T Memory2[2];                   /* '<S4>/Memory2' */
  real_T qpOASES_o1[200];              /* '<S4>/qpOASES' */
  real_T qpOASES_o2;                   /* '<S4>/qpOASES' */
  real_T qpOASES_o3;                   /* '<S4>/qpOASES' */
  real_T qpOASES_o4;                   /* '<S4>/qpOASES' */
  real_T Step;                         /* '<S45>/Step' */
  real_T Sum2;                         /* '<S1>/Sum2' */
  real_T Product_m;                    /* '<S10>/Product' */
  real_T Product_c;                    /* '<S11>/Product' */
  real_T LookUpTable;                  /* '<S15>/Look-Up Table' */
  real_T Step_a;                       /* '<S1>/Step' */
  real_T Delay90zI;                    /* '<S2>/Delay90(z)I' */
  real_T MPCout[2];                    /* '<S4>/MPC_OutLogic' */
  real_T Duv[200];                     /* '<S4>/MPC_OutLogic' */
  real_T Hv[40000];                    /* '<S4>/MPC_MatCalc' */
  real_T F[200];                       /* '<S4>/MPC_MatCalc' */
  real_T A[40000];                     /* '<S4>/MPC_MatCalc' */
  real_T lb[200];                      /* '<S4>/MPC_MatCalc' */
  real_T ub[200];                      /* '<S4>/MPC_MatCalc' */
  real_T lbA[200];                     /* '<S4>/MPC_MatCalc' */
  real_T ubA[200];                     /* '<S4>/MPC_MatCalc' */
  real_T p;                            /* '<S2>/PQ_singlePhase' */
  real_T q;                            /* '<S2>/PQ_singlePhase' */
} B_BIO_csi_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[6];         /* '<S53>/State-Space' */
  real_T Delay90zV_states;             /* '<S2>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S2>/PR(z)' */
  real_T Delay90zI_states;             /* '<S2>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S2>/Delay90(z)V' */
  real_T Memory1_PreviousInput[200];   /* '<S4>/Memory1' */
  real_T Memory2_PreviousInput[2];     /* '<S4>/Memory2' */
  real_T PRz_tmp;                      /* '<S2>/PR(z)' */
  real_T TimeStampA;                   /* '<S15>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S15>/Derivative' */
  real_T TimeStampB;                   /* '<S15>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S15>/Derivative' */
  real_T Delay90zI_tmp;                /* '<S2>/Delay90(z)I' */
  real_T Du[200];                      /* '<S4>/MPC_OutLogic' */
  real_T out[2];                       /* '<S4>/MPC_OutLogic' */
  struct {
    void *AS;
    void *BS;
    void *CS;
    void *DS;
    void *DX_COL;
    void *BD_COL;
    void *TMP1;
    void *TMP2;
    void *XTMP;
    void *SWITCH_STATUS;
    void *SWITCH_STATUS_INIT;
    void *SW_CHG;
    void *G_STATE;
    void *USWLAST;
    void *XKM12;
    void *XKP12;
    void *XLAST;
    void *ULAST;
    void *IDX_SW_CHG;
    void *Y_SWITCH;
    void *SWITCH_TYPES;
    void *IDX_OUT_SW;
    void *SWITCH_TOPO_SAVED_IDX;
    void *SWITCH_MAP;
  } StateSpace_PWORK;                  /* '<S53>/State-Space' */

  void *qpOASES_PWORK[8];              /* '<S4>/qpOASES' */
  int_T StateSpace_IWORK[11];          /* '<S53>/State-Space' */
} DW_BIO_csi_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw2_CSTATE[4];                /* '<S2>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S2>/Hw6' */
} X_BIO_csi_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw2_CSTATE[4];                /* '<S2>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S2>/Hw6' */
} XDot_BIO_csi_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S1>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S1>/Transfer Fcn1' */
  boolean_T Hw2_CSTATE[4];             /* '<S2>/Hw2' */
  boolean_T Hw6_CSTATE[4];             /* '<S2>/Hw6' */
} XDis_BIO_csi_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: zeros(9,1)
   * Referenced by: '<S55>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[9];

  /* Expression: S.A
   * Referenced by: '<S53>/State-Space'
   */
  real_T StateSpace_AS_param[36];

  /* Expression: S.B
   * Referenced by: '<S53>/State-Space'
   */
  real_T StateSpace_BS_param[84];

  /* Expression: S.C
   * Referenced by: '<S53>/State-Space'
   */
  real_T StateSpace_CS_param[66];

  /* Expression: S.D
   * Referenced by: '<S53>/State-Space'
   */
  real_T StateSpace_DS_param[154];

  /* Expression: S.x0
   * Referenced by: '<S53>/State-Space'
   */
  real_T StateSpace_X0_param[6];

  /* Expression: G
   * Referenced by: '<S4>/DynMat'
   */
  real_T DynMat_Value[40000];

  /* Expression: GF
   * Referenced by: '<S4>/DynMat_RespLibre'
   */
  real_T DynMat_RespLibre_Value[40000];

  /* Expression: tv
   * Referenced by: '<S15>/Look-Up Table'
   */
  real_T LookUpTable_XData[5];

  /* Expression: opv
   * Referenced by: '<S15>/Look-Up Table'
   */
  real_T LookUpTable_YData[5];
} ConstP_BIO_csi_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Pbio;                         /* '<Root>/Pbio' */
  real_T Qbio;                         /* '<Root>/Qbio' */
  real_T V_bio;                        /* '<Root>/V_bio' */
} ExtU_BIO_csi_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T I_bio;                        /* '<Root>/I_bio' */
} ExtY_BIO_csi_T;

/* Real-time Model Data Structure */
struct tag_RTM_BIO_csi_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[4];
    SimStruct childSFunctions[1];
    SimStruct *childSFunctionPtrs[1];
    struct _ssBlkInfo2 blkInfo2[1];
    struct _ssSFcnModelMethods2 methods2[1];
    struct _ssSFcnModelMethods3 methods3[1];
    struct _ssSFcnModelMethods4 methods4[1];
    struct _ssStatesInfo2 statesInfo2[1];
    ssPeriodicStatesInfo periodicStatesInfo[1];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[7];
      real_T const *UPtrs0[40000];
      real_T const *UPtrs1[200];
      real_T const *UPtrs2[40000];
      real_T const *UPtrs3[200];
      real_T const *UPtrs4[200];
      real_T const *UPtrs5[200];
      real_T const *UPtrs6[200];
      struct _ssPortOutputs outputPortInfo[4];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;
  } NonInlinedSFcns;

  X_BIO_csi_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[10];
  real_T odeF[4][10];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    uint32_T clockTick2;
    uint32_T clockTick3;
    time_T stepSize3;
    struct {
      uint16_T TID[4];
    } TaskCounters;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[4];
    time_T offsetTimesArray[4];
    int_T sampleTimeTaskIDArray[4];
    int_T sampleHitArray[4];
    int_T perTaskSampleHitsArray[16];
    time_T tArray[4];
  } Timing;
};

/* Block signals (auto storage) */
extern B_BIO_csi_T BIO_csi_B;

/* Continuous states (auto storage) */
extern X_BIO_csi_T BIO_csi_X;

/* Block states (auto storage) */
extern DW_BIO_csi_T BIO_csi_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_BIO_csi_T BIO_csi_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_BIO_csi_T BIO_csi_Y;

/* Constant parameters (auto storage) */
extern const ConstP_BIO_csi_T BIO_csi_ConstP;

/* Model entry point functions */
extern void BIO_csi_initialize(void);
extern void BIO_csi_step(void);
extern void BIO_csi_terminate(void);

/* Real-time Model object */
extern RT_MODEL_BIO_csi_T *const BIO_csi_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S24>/0 1' : Unused code path elimination
 * Block '<S24>/1//Rsw' : Unused code path elimination
 * Block '<S24>/Switch' : Unused code path elimination
 * Block '<S26>/0 1' : Unused code path elimination
 * Block '<S26>/1//Rsw' : Unused code path elimination
 * Block '<S26>/Switch' : Unused code path elimination
 * Block '<S28>/0 1' : Unused code path elimination
 * Block '<S28>/1//Rsw' : Unused code path elimination
 * Block '<S28>/Switch' : Unused code path elimination
 * Block '<S30>/0 1' : Unused code path elimination
 * Block '<S30>/1//Rsw' : Unused code path elimination
 * Block '<S30>/Switch' : Unused code path elimination
 * Block '<S32>/0 1' : Unused code path elimination
 * Block '<S32>/Gain' : Unused code path elimination
 * Block '<S32>/Saturation' : Unused code path elimination
 * Block '<S32>/Sum' : Unused code path elimination
 * Block '<S32>/Switch' : Unused code path elimination
 * Block '<S34>/0 1' : Unused code path elimination
 * Block '<S34>/Gain' : Unused code path elimination
 * Block '<S34>/Saturation' : Unused code path elimination
 * Block '<S34>/Sum' : Unused code path elimination
 * Block '<S34>/Switch' : Unused code path elimination
 * Block '<S36>/0 1' : Unused code path elimination
 * Block '<S36>/Gain' : Unused code path elimination
 * Block '<S36>/Saturation' : Unused code path elimination
 * Block '<S36>/Sum' : Unused code path elimination
 * Block '<S36>/Switch' : Unused code path elimination
 * Block '<S38>/0 1' : Unused code path elimination
 * Block '<S38>/Gain' : Unused code path elimination
 * Block '<S38>/Saturation' : Unused code path elimination
 * Block '<S38>/Sum' : Unused code path elimination
 * Block '<S38>/Switch' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S14>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S14>/Switch3' : Eliminated due to constant selection input
 * Block '<S24>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S30>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S12>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S14>/C4' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BIO_csi'
 * '<S1>'   : 'BIO_csi/1Ph_Inverter_bio'
 * '<S2>'   : 'BIO_csi/CSI_Control_BIO'
 * '<S3>'   : 'BIO_csi/DC 500V'
 * '<S4>'   : 'BIO_csi/MPC_bio'
 * '<S5>'   : 'BIO_csi/powergui'
 * '<S6>'   : 'BIO_csi/1Ph_Inverter_bio/Breaker'
 * '<S7>'   : 'BIO_csi/1Ph_Inverter_bio/H bridge'
 * '<S8>'   : 'BIO_csi/1Ph_Inverter_bio/I sens A'
 * '<S9>'   : 'BIO_csi/1Ph_Inverter_bio/PWM Generator (DC-DC)'
 * '<S10>'  : 'BIO_csi/1Ph_Inverter_bio/Steper1'
 * '<S11>'  : 'BIO_csi/1Ph_Inverter_bio/Steper3'
 * '<S12>'  : 'BIO_csi/1Ph_Inverter_bio/Vsensa1'
 * '<S13>'  : 'BIO_csi/1Ph_Inverter_bio/not_pwm'
 * '<S14>'  : 'BIO_csi/1Ph_Inverter_bio/Breaker/Model'
 * '<S15>'  : 'BIO_csi/1Ph_Inverter_bio/Breaker/Model/Timer'
 * '<S16>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi1'
 * '<S17>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi2'
 * '<S18>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi5'
 * '<S19>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi6'
 * '<S20>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode1'
 * '<S21>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode2'
 * '<S22>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode3'
 * '<S23>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode6'
 * '<S24>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi1/Model'
 * '<S25>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi1/Model/Measurement list'
 * '<S26>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi2/Model'
 * '<S27>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi2/Model/Measurement list'
 * '<S28>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi5/Model'
 * '<S29>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi5/Model/Measurement list'
 * '<S30>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi6/Model'
 * '<S31>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/ sw_ahi6/Model/Measurement list'
 * '<S32>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode1/Model'
 * '<S33>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode1/Model/Measurement list'
 * '<S34>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode2/Model'
 * '<S35>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode2/Model/Measurement list'
 * '<S36>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode3/Model'
 * '<S37>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode3/Model/Measurement list'
 * '<S38>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode6/Model'
 * '<S39>'  : 'BIO_csi/1Ph_Inverter_bio/H bridge/Diode6/Model/Measurement list'
 * '<S40>'  : 'BIO_csi/1Ph_Inverter_bio/I sens A/Model'
 * '<S41>'  : 'BIO_csi/1Ph_Inverter_bio/PWM Generator (DC-DC)/Compare To Zero'
 * '<S42>'  : 'BIO_csi/1Ph_Inverter_bio/PWM Generator (DC-DC)/Sawtooth Generator'
 * '<S43>'  : 'BIO_csi/1Ph_Inverter_bio/PWM Generator (DC-DC)/Sawtooth Generator/Model'
 * '<S44>'  : 'BIO_csi/1Ph_Inverter_bio/Vsensa1/Model'
 * '<S45>'  : 'BIO_csi/CSI_Control_BIO/Death_time'
 * '<S46>'  : 'BIO_csi/CSI_Control_BIO/PQ2Iab_PH1'
 * '<S47>'  : 'BIO_csi/CSI_Control_BIO/PQ_singlePhase'
 * '<S48>'  : 'BIO_csi/CSI_Control_BIO/PR Controller_0_ref 1'
 * '<S49>'  : 'BIO_csi/CSI_Control_BIO/PR Controller_0_ref 1/Steper6'
 * '<S50>'  : 'BIO_csi/DC 500V/Model'
 * '<S51>'  : 'BIO_csi/MPC_bio/MPC_MatCalc'
 * '<S52>'  : 'BIO_csi/MPC_bio/MPC_OutLogic'
 * '<S53>'  : 'BIO_csi/powergui/EquivalentModel1'
 * '<S54>'  : 'BIO_csi/powergui/EquivalentModel1/Gates'
 * '<S55>'  : 'BIO_csi/powergui/EquivalentModel1/Sources'
 * '<S56>'  : 'BIO_csi/powergui/EquivalentModel1/Status'
 * '<S57>'  : 'BIO_csi/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_BIO_csi_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
