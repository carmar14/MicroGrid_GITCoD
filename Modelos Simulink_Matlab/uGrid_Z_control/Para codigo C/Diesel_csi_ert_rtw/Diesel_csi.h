/*
 * File: Diesel_csi.h
 *
 * Code generated for Simulink model 'Diesel_csi'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 10 15:58:53 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Diesel_csi_h_
#define RTW_HEADER_Diesel_csi_h_
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef Diesel_csi_COMMON_INCLUDES_
# define Diesel_csi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* Diesel_csi_COMMON_INCLUDES_ */

#include "Diesel_csi_types.h"
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
  real_T OutputDCVoltage;              /* '<Root>/Sum1' */
  real_T StateSpace_o1[12];            /* '<S56>/State-Space' */
  real_T StateSpace_o2[9];             /* '<S56>/State-Space' */
  real_T TransferFcn;                  /* '<S1>/Transfer Fcn' */
  real_T Delay90zV;                    /* '<S2>/Delay90(z)V' */
  real_T rt[2];                        /* '<S5>/rt' */
  real_T rt1[2];                       /* '<S5>/rt1' */
  real_T Memory1[200];                 /* '<S5>/Memory1' */
  real_T Memory2[2];                   /* '<S5>/Memory2' */
  real_T qpOASES_o1[200];              /* '<S5>/qpOASES' */
  real_T qpOASES_o2;                   /* '<S5>/qpOASES' */
  real_T qpOASES_o3;                   /* '<S5>/qpOASES' */
  real_T qpOASES_o4;                   /* '<S5>/qpOASES' */
  real_T Step;                         /* '<S48>/Step' */
  real_T Sum2;                         /* '<S1>/Sum2' */
  real_T Product_m;                    /* '<S13>/Product' */
  real_T Product_c;                    /* '<S14>/Product' */
  real_T LookUpTable;                  /* '<S18>/Look-Up Table' */
  real_T Step_a;                       /* '<S1>/Step' */
  real_T Delay90zI;                    /* '<S2>/Delay90(z)I' */
  real_T Sum2_j;                       /* '<S3>/Sum2' */
  real_T FilterCoefficient;            /* '<S6>/Filter Coefficient' */
  real_T IntegralGain;                 /* '<S6>/Integral Gain' */
  real_T Sum;                          /* '<S6>/Sum' */
  real_T MPCout[2];                    /* '<S5>/MPC_OutLogic' */
  real_T Duv[200];                     /* '<S5>/MPC_OutLogic' */
  real_T Hv[40000];                    /* '<S5>/MPC_MatCalc' */
  real_T F[200];                       /* '<S5>/MPC_MatCalc' */
  real_T A[40000];                     /* '<S5>/MPC_MatCalc' */
  real_T lb[200];                      /* '<S5>/MPC_MatCalc' */
  real_T ub[200];                      /* '<S5>/MPC_MatCalc' */
  real_T lbA[200];                     /* '<S5>/MPC_MatCalc' */
  real_T ubA[200];                     /* '<S5>/MPC_MatCalc' */
  real_T p;                            /* '<S2>/PQ_singlePhase' */
  real_T q;                            /* '<S2>/PQ_singlePhase' */
} B_Diesel_csi_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[6];         /* '<S56>/State-Space' */
  real_T Delay90zV_states;             /* '<S2>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S2>/PR(z)' */
  real_T Delay90zI_states;             /* '<S2>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S2>/Delay90(z)V' */
  real_T Memory1_PreviousInput[200];   /* '<S5>/Memory1' */
  real_T Memory2_PreviousInput[2];     /* '<S5>/Memory2' */
  real_T PRz_tmp;                      /* '<S2>/PR(z)' */
  real_T TimeStampA;                   /* '<S18>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S18>/Derivative' */
  real_T TimeStampB;                   /* '<S18>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S18>/Derivative' */
  real_T Delay90zI_tmp;                /* '<S2>/Delay90(z)I' */
  real_T Du[200];                      /* '<S5>/MPC_OutLogic' */
  real_T out[2];                       /* '<S5>/MPC_OutLogic' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } MotordeCombustin1_RWORK;           /* '<S3>/Motor de Combustión1' */

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
  } StateSpace_PWORK;                  /* '<S56>/State-Space' */

  void *qpOASES_PWORK[8];              /* '<S5>/qpOASES' */
  struct {
    void *TUbufferPtrs[2];
  } MotordeCombustin1_PWORK;           /* '<S3>/Motor de Combustión1' */

  int_T StateSpace_IWORK[11];          /* '<S56>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } MotordeCombustin1_IWORK;           /* '<S3>/Motor de Combustión1' */
} DW_Diesel_csi_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Dinmicaeneleje1_CSTATE;       /* '<S3>/Dinámica en el eje1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw7_CSTATE[2];                /* '<Root>/Hw7' */
  real_T TransferFcn_CSTATE_o;         /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw2_CSTATE[4];                /* '<S2>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S2>/Hw6' */
  real_T Actuador1_CSTATE;             /* '<S3>/Actuador1' */
  real_T Filter_CSTATE;                /* '<S6>/Filter' */
  real_T Integrator_CSTATE;            /* '<S6>/Integrator' */
} X_Diesel_csi_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Dinmicaeneleje1_CSTATE;       /* '<S3>/Dinámica en el eje1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw7_CSTATE[2];                /* '<Root>/Hw7' */
  real_T TransferFcn_CSTATE_o;         /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw2_CSTATE[4];                /* '<S2>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S2>/Hw6' */
  real_T Actuador1_CSTATE;             /* '<S3>/Actuador1' */
  real_T Filter_CSTATE;                /* '<S6>/Filter' */
  real_T Integrator_CSTATE;            /* '<S6>/Integrator' */
} XDot_Diesel_csi_T;

/* State disabled  */
typedef struct {
  boolean_T Dinmicaeneleje1_CSTATE;    /* '<S3>/Dinámica en el eje1' */
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
  boolean_T Hw7_CSTATE[2];             /* '<Root>/Hw7' */
  boolean_T TransferFcn_CSTATE_o;      /* '<S1>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S1>/Transfer Fcn1' */
  boolean_T Hw2_CSTATE[4];             /* '<S2>/Hw2' */
  boolean_T Hw6_CSTATE[4];             /* '<S2>/Hw6' */
  boolean_T Actuador1_CSTATE;          /* '<S3>/Actuador1' */
  boolean_T Filter_CSTATE;             /* '<S6>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S6>/Integrator' */
} XDis_Diesel_csi_T;

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
   * Referenced by: '<S58>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[9];

  /* Expression: S.A
   * Referenced by: '<S56>/State-Space'
   */
  real_T StateSpace_AS_param[36];

  /* Expression: S.B
   * Referenced by: '<S56>/State-Space'
   */
  real_T StateSpace_BS_param[84];

  /* Expression: S.C
   * Referenced by: '<S56>/State-Space'
   */
  real_T StateSpace_CS_param[72];

  /* Expression: S.D
   * Referenced by: '<S56>/State-Space'
   */
  real_T StateSpace_DS_param[168];

  /* Expression: S.x0
   * Referenced by: '<S56>/State-Space'
   */
  real_T StateSpace_X0_param[6];

  /* Expression: G
   * Referenced by: '<S5>/DynMat'
   */
  real_T DynMat_Value[40000];

  /* Expression: GF
   * Referenced by: '<S5>/DynMat_RespLibre'
   */
  real_T DynMat_RespLibre_Value[40000];

  /* Expression: tv
   * Referenced by: '<S18>/Look-Up Table'
   */
  real_T LookUpTable_XData[5];

  /* Expression: opv
   * Referenced by: '<S18>/Look-Up Table'
   */
  real_T LookUpTable_YData[5];
} ConstP_Diesel_csi_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Pdie;                         /* '<Root>/Pdie' */
  real_T Qdie;                         /* '<Root>/Qdie' */
  real_T V_die;                        /* '<Root>/V_die' */
  real_T flujo;                        /* '<Root>/flujo' */
} ExtU_Diesel_csi_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T I_die;                        /* '<Root>/I_die' */
} ExtY_Diesel_csi_T;

/* Real-time Model Data Structure */
struct tag_RTM_Diesel_csi_T {
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

  X_Diesel_csi_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[17];
  real_T odeF[4][17];
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
extern B_Diesel_csi_T Diesel_csi_B;

/* Continuous states (auto storage) */
extern X_Diesel_csi_T Diesel_csi_X;

/* Block states (auto storage) */
extern DW_Diesel_csi_T Diesel_csi_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Diesel_csi_T Diesel_csi_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Diesel_csi_T Diesel_csi_Y;

/* Constant parameters (auto storage) */
extern const ConstP_Diesel_csi_T Diesel_csi_ConstP;

/* Model entry point functions */
extern void Diesel_csi_initialize(void);
extern void Diesel_csi_step(void);
extern void Diesel_csi_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Diesel_csi_T *const Diesel_csi_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S27>/0 1' : Unused code path elimination
 * Block '<S27>/1//Rsw' : Unused code path elimination
 * Block '<S27>/Switch' : Unused code path elimination
 * Block '<S29>/0 1' : Unused code path elimination
 * Block '<S29>/1//Rsw' : Unused code path elimination
 * Block '<S29>/Switch' : Unused code path elimination
 * Block '<S31>/0 1' : Unused code path elimination
 * Block '<S31>/1//Rsw' : Unused code path elimination
 * Block '<S31>/Switch' : Unused code path elimination
 * Block '<S33>/0 1' : Unused code path elimination
 * Block '<S33>/1//Rsw' : Unused code path elimination
 * Block '<S33>/Switch' : Unused code path elimination
 * Block '<S35>/0 1' : Unused code path elimination
 * Block '<S35>/Gain' : Unused code path elimination
 * Block '<S35>/Saturation' : Unused code path elimination
 * Block '<S35>/Sum' : Unused code path elimination
 * Block '<S35>/Switch' : Unused code path elimination
 * Block '<S37>/0 1' : Unused code path elimination
 * Block '<S37>/Gain' : Unused code path elimination
 * Block '<S37>/Saturation' : Unused code path elimination
 * Block '<S37>/Sum' : Unused code path elimination
 * Block '<S37>/Switch' : Unused code path elimination
 * Block '<S39>/0 1' : Unused code path elimination
 * Block '<S39>/Gain' : Unused code path elimination
 * Block '<S39>/Saturation' : Unused code path elimination
 * Block '<S39>/Sum' : Unused code path elimination
 * Block '<S39>/Switch' : Unused code path elimination
 * Block '<S41>/0 1' : Unused code path elimination
 * Block '<S41>/Gain' : Unused code path elimination
 * Block '<S41>/Saturation' : Unused code path elimination
 * Block '<S41>/Sum' : Unused code path elimination
 * Block '<S41>/Switch' : Unused code path elimination
 * Block '<Root>/Scope14' : Unused code path elimination
 * Block '<S17>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S17>/Switch3' : Eliminated due to constant selection input
 * Block '<S27>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S29>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S31>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S33>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S11>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S15>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S4>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S17>/C4' : Unused code path elimination
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
 * '<Root>' : 'Diesel_csi'
 * '<S1>'   : 'Diesel_csi/1Ph_Inverter_diesel'
 * '<S2>'   : 'Diesel_csi/CSI_Control_DIESEL'
 * '<S3>'   : 'Diesel_csi/Diesel Generator'
 * '<S4>'   : 'Diesel_csi/I_sens'
 * '<S5>'   : 'Diesel_csi/MPC_bio1'
 * '<S6>'   : 'Diesel_csi/PID Controller'
 * '<S7>'   : 'Diesel_csi/V_diesel'
 * '<S8>'   : 'Diesel_csi/powergui'
 * '<S9>'   : 'Diesel_csi/1Ph_Inverter_diesel/Breaker'
 * '<S10>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge'
 * '<S11>'  : 'Diesel_csi/1Ph_Inverter_diesel/I sens A'
 * '<S12>'  : 'Diesel_csi/1Ph_Inverter_diesel/PWM Generator (DC-DC)'
 * '<S13>'  : 'Diesel_csi/1Ph_Inverter_diesel/Steper1'
 * '<S14>'  : 'Diesel_csi/1Ph_Inverter_diesel/Steper3'
 * '<S15>'  : 'Diesel_csi/1Ph_Inverter_diesel/Vsensa1'
 * '<S16>'  : 'Diesel_csi/1Ph_Inverter_diesel/not_pwm'
 * '<S17>'  : 'Diesel_csi/1Ph_Inverter_diesel/Breaker/Model'
 * '<S18>'  : 'Diesel_csi/1Ph_Inverter_diesel/Breaker/Model/Timer'
 * '<S19>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi1'
 * '<S20>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi2'
 * '<S21>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi5'
 * '<S22>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi6'
 * '<S23>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode1'
 * '<S24>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode2'
 * '<S25>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode3'
 * '<S26>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode6'
 * '<S27>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi1/Model'
 * '<S28>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi1/Model/Measurement list'
 * '<S29>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi2/Model'
 * '<S30>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi2/Model/Measurement list'
 * '<S31>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi5/Model'
 * '<S32>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi5/Model/Measurement list'
 * '<S33>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi6/Model'
 * '<S34>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/ sw_ahi6/Model/Measurement list'
 * '<S35>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode1/Model'
 * '<S36>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode1/Model/Measurement list'
 * '<S37>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode2/Model'
 * '<S38>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode2/Model/Measurement list'
 * '<S39>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode3/Model'
 * '<S40>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode3/Model/Measurement list'
 * '<S41>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode6/Model'
 * '<S42>'  : 'Diesel_csi/1Ph_Inverter_diesel/H bridge/Diode6/Model/Measurement list'
 * '<S43>'  : 'Diesel_csi/1Ph_Inverter_diesel/I sens A/Model'
 * '<S44>'  : 'Diesel_csi/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Compare To Zero'
 * '<S45>'  : 'Diesel_csi/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Sawtooth Generator'
 * '<S46>'  : 'Diesel_csi/1Ph_Inverter_diesel/PWM Generator (DC-DC)/Sawtooth Generator/Model'
 * '<S47>'  : 'Diesel_csi/1Ph_Inverter_diesel/Vsensa1/Model'
 * '<S48>'  : 'Diesel_csi/CSI_Control_DIESEL/Death_time'
 * '<S49>'  : 'Diesel_csi/CSI_Control_DIESEL/PQ2Iab_PH1'
 * '<S50>'  : 'Diesel_csi/CSI_Control_DIESEL/PQ_singlePhase'
 * '<S51>'  : 'Diesel_csi/CSI_Control_DIESEL/PR Controller_0_ref 1'
 * '<S52>'  : 'Diesel_csi/CSI_Control_DIESEL/PR Controller_0_ref 1/Steper6'
 * '<S53>'  : 'Diesel_csi/I_sens/Model'
 * '<S54>'  : 'Diesel_csi/MPC_bio1/MPC_MatCalc'
 * '<S55>'  : 'Diesel_csi/MPC_bio1/MPC_OutLogic'
 * '<S56>'  : 'Diesel_csi/powergui/EquivalentModel1'
 * '<S57>'  : 'Diesel_csi/powergui/EquivalentModel1/Gates'
 * '<S58>'  : 'Diesel_csi/powergui/EquivalentModel1/Sources'
 * '<S59>'  : 'Diesel_csi/powergui/EquivalentModel1/Status'
 * '<S60>'  : 'Diesel_csi/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_Diesel_csi_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
