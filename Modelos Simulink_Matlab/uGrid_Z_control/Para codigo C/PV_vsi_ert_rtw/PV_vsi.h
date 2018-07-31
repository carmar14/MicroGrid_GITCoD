/*
 * File: PV_vsi.h
 *
 * Code generated for Simulink model 'PV_vsi'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 31 14:14:34 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PV_vsi_h_
#define RTW_HEADER_PV_vsi_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef PV_vsi_COMMON_INCLUDES_
# define PV_vsi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* PV_vsi_COMMON_INCLUDES_ */

#include "PV_vsi_types.h"
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
  real_T Switch2;                      /* '<S58>/Switch2' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T StateSpace_o1[13];            /* '<S70>/State-Space' */
  real_T StateSpace_o2[9];             /* '<S70>/State-Space' */
  real_T TransferFcn;                  /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1;                 /* '<S1>/Transfer Fcn1' */
  real_T TransferFcn2;                 /* '<S1>/Transfer Fcn2' */
  real_T Vc_ref;                       /* '<Root>/Sine Wave' */
  real_T Inductor_refCurrent;          /* '<S4>/Sum6' */
  real_T InductorErrorCurrent;         /* '<S4>/Sum8' */
  real_T Product;                      /* '<S11>/Product' */
  real_T Product_m;                    /* '<S12>/Product' */
  real_T LookUpTable;                  /* '<S16>/Look-Up Table' */
  real_T Step;                         /* '<S1>/Step' */
} B_PV_vsi_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Currentfilter5_states;        /* '<S49>/Current filter5' */
  real_T inti_DSTATE;                  /* '<S49>/int(i)' */
  real_T StateSpace_DSTATE[7];         /* '<S70>/State-Space' */
  real_T itinit1_PreviousInput;        /* '<S49>/it init1' */
  real_T itinit_PreviousInput;         /* '<S49>/it init' */
  real_T TimeStampA;                   /* '<S4>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S4>/Derivative' */
  real_T TimeStampB;                   /* '<S4>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S4>/Derivative' */
  real_T TimeStampA_f;                 /* '<S16>/Derivative' */
  real_T LastUAtTimeA_e;               /* '<S16>/Derivative' */
  real_T TimeStampB_h;                 /* '<S16>/Derivative' */
  real_T LastUAtTimeB_b;               /* '<S16>/Derivative' */
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
  } StateSpace_PWORK;                  /* '<S70>/State-Space' */

  int_T StateSpace_IWORK[11];          /* '<S70>/State-Space' */
  int8_T inti_PrevResetState;          /* '<S49>/int(i)' */
  uint8_T inti_IC_LOADING;             /* '<S49>/int(i)' */
} DW_PV_vsi_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S1>/Transfer Fcn2' */
  real_T Hw2_CSTATE[2];                /* '<Root>/Hw2' */
  real_T Hi_Pass1_CSTATE;              /* '<S4>/Hi_Pass1' */
  real_T Hw5_CSTATE[2];                /* '<Root>/Hw5' */
  real_T TransferFcn1_CSTATE_h[2];     /* '<S4>/Transfer Fcn1' */
  real_T Hw6_CSTATE[2];                /* '<Root>/Hw6' */
} X_PV_vsi_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S1>/Transfer Fcn2' */
  real_T Hw2_CSTATE[2];                /* '<Root>/Hw2' */
  real_T Hi_Pass1_CSTATE;              /* '<S4>/Hi_Pass1' */
  real_T Hw5_CSTATE[2];                /* '<Root>/Hw5' */
  real_T TransferFcn1_CSTATE_h[2];     /* '<S4>/Transfer Fcn1' */
  real_T Hw6_CSTATE[2];                /* '<Root>/Hw6' */
} XDot_PV_vsi_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S1>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S1>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S1>/Transfer Fcn2' */
  boolean_T Hw2_CSTATE[2];             /* '<Root>/Hw2' */
  boolean_T Hi_Pass1_CSTATE;           /* '<S4>/Hi_Pass1' */
  boolean_T Hw5_CSTATE[2];             /* '<Root>/Hw5' */
  boolean_T TransferFcn1_CSTATE_h[2];  /* '<S4>/Transfer Fcn1' */
  boolean_T Hw6_CSTATE[2];             /* '<Root>/Hw6' */
} XDis_PV_vsi_T;

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
   * Referenced by: '<S72>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[9];

  /* Expression: S.A
   * Referenced by: '<S70>/State-Space'
   */
  real_T StateSpace_AS_param[49];

  /* Expression: S.B
   * Referenced by: '<S70>/State-Space'
   */
  real_T StateSpace_BS_param[105];

  /* Expression: S.C
   * Referenced by: '<S70>/State-Space'
   */
  real_T StateSpace_CS_param[91];

  /* Expression: S.D
   * Referenced by: '<S70>/State-Space'
   */
  real_T StateSpace_DS_param[195];

  /* Expression: S.x0
   * Referenced by: '<S70>/State-Space'
   */
  real_T StateSpace_X0_param[7];

  /* Expression: tv
   * Referenced by: '<S16>/Look-Up Table'
   */
  real_T LookUpTable_XData[5];

  /* Expression: opv
   * Referenced by: '<S16>/Look-Up Table'
   */
  real_T LookUpTable_YData[5];
} ConstP_PV_vsi_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Corriente;                    /* '<Root>/Corriente' */
} ExtU_PV_vsi_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T I_vsi;                        /* '<Root>/I_vsi' */
  real_T SOC;                          /* '<Root>/SOC' */
} ExtY_PV_vsi_T;

/* Real-time Model Data Structure */
struct tag_RTM_PV_vsi_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_PV_vsi_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[12];
  real_T odeF[4][12];
  ODE4_IntgData intgData;

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
extern B_PV_vsi_T PV_vsi_B;

/* Continuous states (auto storage) */
extern X_PV_vsi_T PV_vsi_X;

/* Block states (auto storage) */
extern DW_PV_vsi_T PV_vsi_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_PV_vsi_T PV_vsi_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_PV_vsi_T PV_vsi_Y;

/* Constant parameters (auto storage) */
extern const ConstP_PV_vsi_T PV_vsi_ConstP;

/* Model entry point functions */
extern void PV_vsi_initialize(void);
extern void PV_vsi_step(void);
extern void PV_vsi_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PV_vsi_T *const PV_vsi_M;

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
 * Block '<S49>/Add' : Unused code path elimination
 * Block '<S56>/Constant' : Unused code path elimination
 * Block '<S49>/R' : Unused code path elimination
 * Block '<S58>/Data Type Duplicate' : Unused code path elimination
 * Block '<S58>/Data Type Propagation' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Propagation' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Scope7' : Unused code path elimination
 * Block '<S4>/Scope8' : Unused code path elimination
 * Block '<S15>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S15>/Switch3' : Eliminated due to constant selection input
 * Block '<S25>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S29>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S31>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S9>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S13>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S48>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S54>/Multiport Switch1' : Eliminated due to constant selection input
 * Block '<S55>/Multiport Switch1' : Eliminated due to constant selection input
 * Block '<S49>/Switch' : Eliminated due to constant selection input
 * Block '<S49>/Switch1' : Eliminated due to constant selection input
 * Block '<S49>/Switch2' : Eliminated due to constant selection input
 * Block '<S49>/Switch3' : Eliminated due to constant selection input
 * Block '<S49>/Switch4' : Eliminated due to constant selection input
 * Block '<S49>/Switch5' : Eliminated due to constant selection input
 * Block '<S49>/Switch6' : Eliminated due to constant selection input
 * Block '<S15>/C4' : Unused code path elimination
 * Block '<S49>/Constant10' : Unused code path elimination
 * Block '<S49>/Constant11' : Unused code path elimination
 * Block '<S49>/Constant13' : Unused code path elimination
 * Block '<S49>/Constant14' : Unused code path elimination
 * Block '<S49>/Constant15' : Unused code path elimination
 * Block '<S49>/Constant16' : Unused code path elimination
 * Block '<S49>/Constant3' : Unused code path elimination
 * Block '<S49>/Constant5' : Unused code path elimination
 * Block '<S49>/Constant7' : Unused code path elimination
 * Block '<S49>/Constant8' : Unused code path elimination
 * Block '<S49>/Current filter3' : Unused code path elimination
 * Block '<S54>/Charge Lead-Acid' : Unused code path elimination
 * Block '<S54>/Charge NiCD' : Unused code path elimination
 * Block '<S54>/Charge NiMH' : Unused code path elimination
 * Block '<S54>/Constant' : Unused code path elimination
 * Block '<S54>/Constant2' : Unused code path elimination
 * Block '<S54>/Constant3' : Unused code path elimination
 * Block '<S54>/Constant4' : Unused code path elimination
 * Block '<S54>/Product1' : Unused code path elimination
 * Block '<S54>/Product2' : Unused code path elimination
 * Block '<S54>/Product3' : Unused code path elimination
 * Block '<S55>/Abs' : Unused code path elimination
 * Block '<S55>/Add3' : Unused code path elimination
 * Block '<S62>/Compare' : Unused code path elimination
 * Block '<S62>/Constant' : Unused code path elimination
 * Block '<S55>/Constant' : Unused code path elimination
 * Block '<S55>/Data Type Conversion1' : Unused code path elimination
 * Block '<S55>/Discrete-Time Integrator' : Unused code path elimination
 * Block '<S55>/Divide' : Unused code path elimination
 * Block '<S55>/Gain1' : Unused code path elimination
 * Block '<S55>/Gain4' : Unused code path elimination
 * Block '<S49>/Fcn2' : Unused code path elimination
 * Block '<S49>/Fcn3' : Unused code path elimination
 * Block '<S49>/Fcn4' : Unused code path elimination
 * Block '<S49>/Fcn7' : Unused code path elimination
 * Block '<S57>/Abs' : Unused code path elimination
 * Block '<S57>/Abs1' : Unused code path elimination
 * Block '<S57>/Add' : Unused code path elimination
 * Block '<S63>/Compare' : Unused code path elimination
 * Block '<S63>/Constant' : Unused code path elimination
 * Block '<S57>/Data Type Conversion1' : Unused code path elimination
 * Block '<S57>/Fcn1' : Unused code path elimination
 * Block '<S57>/Fcn3' : Unused code path elimination
 * Block '<S57>/Gain' : Unused code path elimination
 * Block '<S57>/Product' : Unused code path elimination
 * Block '<S49>/Saturation2' : Unused code path elimination
 * Block '<S49>/Saturation3' : Unused code path elimination
 * Block '<S49>/Sum' : Unused code path elimination
 * Block '<S64>/Discrete State Space' : Unused code path elimination
 * Block '<S65>/Discrete State Space' : Unused code path elimination
 * Block '<S61>/Gain' : Unused code path elimination
 * Block '<S61>/Sum' : Unused code path elimination
 * Block '<S2>/Ta' : Unused code path elimination
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
 * '<Root>' : 'PV_vsi'
 * '<S1>'   : 'PV_vsi/1Ph_Inverter_bio1'
 * '<S2>'   : 'PV_vsi/Battery'
 * '<S3>'   : 'PV_vsi/Controlled Current Source'
 * '<S4>'   : 'PV_vsi/VSI_Controller'
 * '<S5>'   : 'PV_vsi/powergui'
 * '<S6>'   : 'PV_vsi/1Ph_Inverter_bio1/Breaker'
 * '<S7>'   : 'PV_vsi/1Ph_Inverter_bio1/H bridge'
 * '<S8>'   : 'PV_vsi/1Ph_Inverter_bio1/I sens A'
 * '<S9>'   : 'PV_vsi/1Ph_Inverter_bio1/I sens A1'
 * '<S10>'  : 'PV_vsi/1Ph_Inverter_bio1/PWM Generator (DC-DC)'
 * '<S11>'  : 'PV_vsi/1Ph_Inverter_bio1/Steper1'
 * '<S12>'  : 'PV_vsi/1Ph_Inverter_bio1/Steper3'
 * '<S13>'  : 'PV_vsi/1Ph_Inverter_bio1/Vsensa1'
 * '<S14>'  : 'PV_vsi/1Ph_Inverter_bio1/not_pwm'
 * '<S15>'  : 'PV_vsi/1Ph_Inverter_bio1/Breaker/Model'
 * '<S16>'  : 'PV_vsi/1Ph_Inverter_bio1/Breaker/Model/Timer'
 * '<S17>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi1'
 * '<S18>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi2'
 * '<S19>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi5'
 * '<S20>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi6'
 * '<S21>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode1'
 * '<S22>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode2'
 * '<S23>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode3'
 * '<S24>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode6'
 * '<S25>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi1/Model'
 * '<S26>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi1/Model/Measurement list'
 * '<S27>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi2/Model'
 * '<S28>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi2/Model/Measurement list'
 * '<S29>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi5/Model'
 * '<S30>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi5/Model/Measurement list'
 * '<S31>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi6/Model'
 * '<S32>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/ sw_ahi6/Model/Measurement list'
 * '<S33>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode1/Model'
 * '<S34>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode1/Model/Measurement list'
 * '<S35>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode2/Model'
 * '<S36>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode2/Model/Measurement list'
 * '<S37>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode3/Model'
 * '<S38>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode3/Model/Measurement list'
 * '<S39>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode6/Model'
 * '<S40>'  : 'PV_vsi/1Ph_Inverter_bio1/H bridge/Diode6/Model/Measurement list'
 * '<S41>'  : 'PV_vsi/1Ph_Inverter_bio1/I sens A/Model'
 * '<S42>'  : 'PV_vsi/1Ph_Inverter_bio1/I sens A1/Model'
 * '<S43>'  : 'PV_vsi/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Compare To Zero'
 * '<S44>'  : 'PV_vsi/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Sawtooth Generator'
 * '<S45>'  : 'PV_vsi/1Ph_Inverter_bio1/PWM Generator (DC-DC)/Sawtooth Generator/Model'
 * '<S46>'  : 'PV_vsi/1Ph_Inverter_bio1/Vsensa1/Model'
 * '<S47>'  : 'PV_vsi/Battery/Controlled Voltage Source'
 * '<S48>'  : 'PV_vsi/Battery/Current Measurement'
 * '<S49>'  : 'PV_vsi/Battery/Model'
 * '<S50>'  : 'PV_vsi/Battery/Output'
 * '<S51>'  : 'PV_vsi/Battery/Current Measurement/Model'
 * '<S52>'  : 'PV_vsi/Battery/Model/Compare To Zero'
 * '<S53>'  : 'PV_vsi/Battery/Model/Compare To Zero2'
 * '<S54>'  : 'PV_vsi/Battery/Model/E_dyn Charge'
 * '<S55>'  : 'PV_vsi/Battery/Model/Exp'
 * '<S56>'  : 'PV_vsi/Battery/Model/No Aging Model'
 * '<S57>'  : 'PV_vsi/Battery/Model/Power loss estimation'
 * '<S58>'  : 'PV_vsi/Battery/Model/Saturation Dynamic'
 * '<S59>'  : 'PV_vsi/Battery/Model/Saturation Dynamic1'
 * '<S60>'  : 'PV_vsi/Battery/Model/Saturation Dynamic2'
 * '<S61>'  : 'PV_vsi/Battery/Model/Thermal Model'
 * '<S62>'  : 'PV_vsi/Battery/Model/Exp/Compare To Zero2'
 * '<S63>'  : 'PV_vsi/Battery/Model/Power loss estimation/Compare To Zero2'
 * '<S64>'  : 'PV_vsi/Battery/Model/Thermal Model/Discrete Transfer Fcn (with initial outputs)'
 * '<S65>'  : 'PV_vsi/Battery/Model/Thermal Model/Discrete Transfer Fcn (with initial outputs)1'
 * '<S66>'  : 'PV_vsi/Battery/Output/Output with Age'
 * '<S67>'  : 'PV_vsi/Battery/Output/Output with T'
 * '<S68>'  : 'PV_vsi/Battery/Output/Output with T and Age'
 * '<S69>'  : 'PV_vsi/Battery/Output/Output without T and Age'
 * '<S70>'  : 'PV_vsi/powergui/EquivalentModel1'
 * '<S71>'  : 'PV_vsi/powergui/EquivalentModel1/Gates'
 * '<S72>'  : 'PV_vsi/powergui/EquivalentModel1/Sources'
 * '<S73>'  : 'PV_vsi/powergui/EquivalentModel1/Status'
 * '<S74>'  : 'PV_vsi/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_PV_vsi_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
