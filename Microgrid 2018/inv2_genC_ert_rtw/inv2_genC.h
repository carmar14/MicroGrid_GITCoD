/*
 * File: inv2_genC.h
 *
 * Code generated for Simulink model 'inv2_genC'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Sat Apr 21 19:17:20 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_inv2_genC_h_
#define RTW_HEADER_inv2_genC_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef inv2_genC_COMMON_INCLUDES_
# define inv2_genC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* inv2_genC_COMMON_INCLUDES_ */

#include "inv2_genC_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_look.h"
#include "rt_look1d.h"

/* Macros for accessing real-time model data structure */
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

/* Block signals (auto storage) */
typedef struct {
  real_T StateSpace_o1[11];            /* '<S48>/State-Space' */
  real_T StateSpace_o2[9];             /* '<S48>/State-Space' */
  real_T TransferFcn;                  /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1;                 /* '<S1>/Transfer Fcn1' */
  real_T Hw3;                          /* '<Root>/Hw3' */
  real_T Hw7;                          /* '<Root>/Hw7' */
  real_T Product;                      /* '<S11>/Product' */
  real_T Product_c;                    /* '<S12>/Product' */
  real_T LookUpTable;                  /* '<S16>/Look-Up Table' */
  real_T Step;                         /* '<S1>/Step' */
  real_T K2;                           /* '<S5>/K2' */
  real_T p;                            /* '<Root>/PQ_singlePhase1' */
  real_T q;                            /* '<Root>/PQ_singlePhase1' */
} B_inv2_genC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[6];         /* '<S48>/State-Space' */
  real_T TimeStampA;                   /* '<S16>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S16>/Derivative' */
  real_T TimeStampB;                   /* '<S16>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S16>/Derivative' */
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
  } StateSpace_PWORK;                  /* '<S48>/State-Space' */

  int_T StateSpace_IWORK[11];          /* '<S48>/State-Space' */
} DW_inv2_genC_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Hw5_CSTATE[4];                /* '<Root>/Hw5' */
  real_T Hw8_CSTATE[4];                /* '<Root>/Hw8' */
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw3_CSTATE[2];                /* '<Root>/Hw3' */
  real_T PhaseShift3_CSTATE;           /* '<Root>/PhaseShift3' */
  real_T Hw7_CSTATE[2];                /* '<Root>/Hw7' */
  real_T TransferFcn_CSTATE_n[2];      /* '<S5>/Transfer Fcn' */
  real_T PhaseShift4_CSTATE;           /* '<Root>/PhaseShift4' */
} X_inv2_genC_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Hw5_CSTATE[4];                /* '<Root>/Hw5' */
  real_T Hw8_CSTATE[4];                /* '<Root>/Hw8' */
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Hw3_CSTATE[2];                /* '<Root>/Hw3' */
  real_T PhaseShift3_CSTATE;           /* '<Root>/PhaseShift3' */
  real_T Hw7_CSTATE[2];                /* '<Root>/Hw7' */
  real_T TransferFcn_CSTATE_n[2];      /* '<S5>/Transfer Fcn' */
  real_T PhaseShift4_CSTATE;           /* '<Root>/PhaseShift4' */
} XDot_inv2_genC_T;

/* State disabled  */
typedef struct {
  boolean_T Hw5_CSTATE[4];             /* '<Root>/Hw5' */
  boolean_T Hw8_CSTATE[4];             /* '<Root>/Hw8' */
  boolean_T TransferFcn_CSTATE;        /* '<S1>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S1>/Transfer Fcn1' */
  boolean_T Hw3_CSTATE[2];             /* '<Root>/Hw3' */
  boolean_T PhaseShift3_CSTATE;        /* '<Root>/PhaseShift3' */
  boolean_T Hw7_CSTATE[2];             /* '<Root>/Hw7' */
  boolean_T TransferFcn_CSTATE_n[2];   /* '<S5>/Transfer Fcn' */
  boolean_T PhaseShift4_CSTATE;        /* '<Root>/PhaseShift4' */
} XDis_inv2_genC_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: zeros(9,1)
   * Referenced by: '<S50>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[9];

  /* Expression: S.A
   * Referenced by: '<S48>/State-Space'
   */
  real_T StateSpace_AS_param[36];

  /* Expression: S.B
   * Referenced by: '<S48>/State-Space'
   */
  real_T StateSpace_BS_param[84];

  /* Expression: S.C
   * Referenced by: '<S48>/State-Space'
   */
  real_T StateSpace_CS_param[66];

  /* Expression: S.D
   * Referenced by: '<S48>/State-Space'
   */
  real_T StateSpace_DS_param[154];

  /* Expression: S.x0
   * Referenced by: '<S48>/State-Space'
   */
  real_T StateSpace_X0_param[6];

  /* Expression: tv
   * Referenced by: '<S16>/Look-Up Table'
   */
  real_T LookUpTable_XData[5];

  /* Expression: opv
   * Referenced by: '<S16>/Look-Up Table'
   */
  real_T LookUpTable_YData[5];
} ConstP_inv2_genC_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T mpc_Pdie;                     /* '<Root>/mpc_Pdie' */
  real_T mpc_Qdie;                     /* '<Root>/mpc_Qdie' */
} ExtU_inv2_genC_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T pdie_meas;                    /* '<Root>/pdie_meas' */
  real_T qdie_meas;                    /* '<Root>/qdie_meas' */
} ExtY_inv2_genC_T;

/* Real-time Model Data Structure */
struct tag_RTM_inv2_genC_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_inv2_genC_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[18];
  real_T odeF[3][18];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (auto storage) */
extern B_inv2_genC_T inv2_genC_B;

/* Continuous states (auto storage) */
extern X_inv2_genC_T inv2_genC_X;

/* Block states (auto storage) */
extern DW_inv2_genC_T inv2_genC_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_inv2_genC_T inv2_genC_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_inv2_genC_T inv2_genC_Y;

/* Constant parameters (auto storage) */
extern const ConstP_inv2_genC_T inv2_genC_ConstP;

/* Model entry point functions */
extern void inv2_genC_initialize(void);
extern void inv2_genC_step(void);
extern void inv2_genC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_inv2_genC_T *const inv2_genC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S25>/0 1' : Unused code path elimination
 * Block '<S25>/1//Rsw' : Unused code path elimination
 * Block '<S25>/Switch' : Unused code path elimination
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
 * Block '<S33>/Gain' : Unused code path elimination
 * Block '<S33>/Saturation' : Unused code path elimination
 * Block '<S33>/Sum' : Unused code path elimination
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
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<S15>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S15>/Switch3' : Eliminated due to constant selection input
 * Block '<S25>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S29>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S31>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S9>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S13>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S15>/C4' : Unused code path elimination
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
 * '<Root>' : 'inv2_genC'
 * '<S1>'   : 'inv2_genC/3PhaseInverter1'
 * '<S2>'   : 'inv2_genC/DC_2'
 * '<S3>'   : 'inv2_genC/PQ2AlphBetaCurrents_SinglePhase1'
 * '<S4>'   : 'inv2_genC/PQ_singlePhase1'
 * '<S5>'   : 'inv2_genC/PR Controller_0_ref 2'
 * '<S6>'   : 'inv2_genC/powergui'
 * '<S7>'   : 'inv2_genC/3PhaseInverter1/Breaker'
 * '<S8>'   : 'inv2_genC/3PhaseInverter1/H bridge'
 * '<S9>'   : 'inv2_genC/3PhaseInverter1/I sens A'
 * '<S10>'  : 'inv2_genC/3PhaseInverter1/PWM Generator (DC-DC)'
 * '<S11>'  : 'inv2_genC/3PhaseInverter1/Steper1'
 * '<S12>'  : 'inv2_genC/3PhaseInverter1/Steper3'
 * '<S13>'  : 'inv2_genC/3PhaseInverter1/Vsensa1'
 * '<S14>'  : 'inv2_genC/3PhaseInverter1/not_pwm'
 * '<S15>'  : 'inv2_genC/3PhaseInverter1/Breaker/Model'
 * '<S16>'  : 'inv2_genC/3PhaseInverter1/Breaker/Model/Timer'
 * '<S17>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi1'
 * '<S18>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi2'
 * '<S19>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi5'
 * '<S20>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi6'
 * '<S21>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode1'
 * '<S22>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode2'
 * '<S23>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode3'
 * '<S24>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode6'
 * '<S25>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi1/Model'
 * '<S26>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi1/Model/Measurement list'
 * '<S27>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi2/Model'
 * '<S28>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi2/Model/Measurement list'
 * '<S29>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi5/Model'
 * '<S30>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi5/Model/Measurement list'
 * '<S31>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi6/Model'
 * '<S32>'  : 'inv2_genC/3PhaseInverter1/H bridge/ sw_ahi6/Model/Measurement list'
 * '<S33>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode1/Model'
 * '<S34>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode1/Model/Measurement list'
 * '<S35>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode2/Model'
 * '<S36>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode2/Model/Measurement list'
 * '<S37>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode3/Model'
 * '<S38>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode3/Model/Measurement list'
 * '<S39>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode6/Model'
 * '<S40>'  : 'inv2_genC/3PhaseInverter1/H bridge/Diode6/Model/Measurement list'
 * '<S41>'  : 'inv2_genC/3PhaseInverter1/I sens A/Model'
 * '<S42>'  : 'inv2_genC/3PhaseInverter1/PWM Generator (DC-DC)/Compare To Zero'
 * '<S43>'  : 'inv2_genC/3PhaseInverter1/PWM Generator (DC-DC)/Sawtooth Generator'
 * '<S44>'  : 'inv2_genC/3PhaseInverter1/PWM Generator (DC-DC)/Sawtooth Generator/Model'
 * '<S45>'  : 'inv2_genC/3PhaseInverter1/Vsensa1/Model'
 * '<S46>'  : 'inv2_genC/DC_2/Model'
 * '<S47>'  : 'inv2_genC/PR Controller_0_ref 2/Steper6'
 * '<S48>'  : 'inv2_genC/powergui/EquivalentModel1'
 * '<S49>'  : 'inv2_genC/powergui/EquivalentModel1/Gates'
 * '<S50>'  : 'inv2_genC/powergui/EquivalentModel1/Sources'
 * '<S51>'  : 'inv2_genC/powergui/EquivalentModel1/Status'
 * '<S52>'  : 'inv2_genC/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_inv2_genC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
