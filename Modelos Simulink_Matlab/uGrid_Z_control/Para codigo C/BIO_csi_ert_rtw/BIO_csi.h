/*
 * File: BIO_csi.h
 *
 * Code generated for Simulink model 'BIO_csi'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 31 11:51:47 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_h_
#define RTW_HEADER_BIO_csi_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef BIO_csi_COMMON_INCLUDES_
# define BIO_csi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* BIO_csi_COMMON_INCLUDES_ */

#include "BIO_csi_types.h"
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
  real_T dv0[40000];
  real_T dv1[20200];
  real_T StateSpace_o1[11];            /* '<S67>/State-Space' */
  real_T StateSpace_o2[9];             /* '<S67>/State-Space' */
  real_T Delay90zV;                    /* '<S2>/Delay90(z)V' */
  real_T Step;                         /* '<S45>/Step' */
  real_T Sum2;                         /* '<S1>/Sum2' */
  real_T Product_m;                    /* '<S10>/Product' */
  real_T Product_c;                    /* '<S11>/Product' */
  real_T LookUpTable;                  /* '<S15>/Look-Up Table' */
  real_T Step_a;                       /* '<S1>/Step' */
  real_T Delay90zI;                    /* '<S2>/Delay90(z)I' */
  real_T xk1[14];                      /* '<S51>/optimizer' */
  real_T u[2];                         /* '<S51>/optimizer' */
  real_T p;                            /* '<S2>/PQ_singlePhase' */
  real_T q;                            /* '<S2>/PQ_singlePhase' */
  boolean_T iAout;                     /* '<S51>/optimizer' */
} B_BIO_csi_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[6];         /* '<S67>/State-Space' */
  real_T Delay90zV_states;             /* '<S2>/Delay90(z)V' */
  real_T last_mv_DSTATE[2];            /* '<S51>/last_mv' */
  real_T PRz_states[2];                /* '<S2>/PR(z)' */
  real_T Delay90zI_states;             /* '<S2>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S2>/Delay90(z)V' */
  real_T last_x_PreviousInput[14];     /* '<S51>/last_x' */
  real_T PRz_tmp;                      /* '<S2>/PR(z)' */
  real_T TimeStampA;                   /* '<S15>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S15>/Derivative' */
  real_T TimeStampB;                   /* '<S15>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S15>/Derivative' */
  real_T Delay90zI_tmp;                /* '<S2>/Delay90(z)I' */
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
  } StateSpace_PWORK;                  /* '<S67>/State-Space' */

  int_T StateSpace_IWORK[11];          /* '<S67>/State-Space' */
  boolean_T Memory_PreviousInput;      /* '<S51>/Memory' */
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
   * Referenced by: '<S69>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[9];

  /* Expression: S.A
   * Referenced by: '<S67>/State-Space'
   */
  real_T StateSpace_AS_param[36];

  /* Expression: S.B
   * Referenced by: '<S67>/State-Space'
   */
  real_T StateSpace_BS_param[84];

  /* Expression: S.C
   * Referenced by: '<S67>/State-Space'
   */
  real_T StateSpace_CS_param[66];

  /* Expression: S.D
   * Referenced by: '<S67>/State-Space'
   */
  real_T StateSpace_DS_param[154];

  /* Expression: S.x0
   * Referenced by: '<S67>/State-Space'
   */
  real_T StateSpace_X0_param[6];

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
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
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
    uint32_T clockTick2;
    struct {
      uint32_T TID[4];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
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
 * Block '<S52>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S53>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S54>/Vector Dimension Check' : Unused code path elimination
 * Block '<S55>/Vector Dimension Check' : Unused code path elimination
 * Block '<S56>/Vector Dimension Check' : Unused code path elimination
 * Block '<S57>/Vector Dimension Check' : Unused code path elimination
 * Block '<S58>/Vector Dimension Check' : Unused code path elimination
 * Block '<S59>/Vector Dimension Check' : Unused code path elimination
 * Block '<S60>/Vector Dimension Check' : Unused code path elimination
 * Block '<S61>/Vector Dimension Check' : Unused code path elimination
 * Block '<S62>/Vector Dimension Check' : Unused code path elimination
 * Block '<S63>/Vector Dimension Check' : Unused code path elimination
 * Block '<S64>/Vector Dimension Check' : Unused code path elimination
 * Block '<S65>/Vector Dimension Check' : Unused code path elimination
 * Block '<S51>/constant' : Unused code path elimination
 * Block '<S51>/umin_scale2' : Unused code path elimination
 * Block '<S51>/umin_scale3' : Unused code path elimination
 * Block '<S51>/ym_zero' : Unused code path elimination
 * Block '<S14>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S14>/Switch3' : Eliminated due to constant selection input
 * Block '<S24>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S26>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S30>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S12>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S51>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S51>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S51>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S51>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S51>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S51>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S51>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S51>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S51>/ymin_scale' : Eliminated nontunable gain of 1
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
 * '<S4>'   : 'BIO_csi/MPC Controller'
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
 * '<S51>'  : 'BIO_csi/MPC Controller/MPC'
 * '<S52>'  : 'BIO_csi/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S53>'  : 'BIO_csi/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S54>'  : 'BIO_csi/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S55>'  : 'BIO_csi/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S56>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S57>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S58>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S59>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S60>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S61>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S62>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S63>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S64>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S65>'  : 'BIO_csi/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S66>'  : 'BIO_csi/MPC Controller/MPC/optimizer'
 * '<S67>'  : 'BIO_csi/powergui/EquivalentModel1'
 * '<S68>'  : 'BIO_csi/powergui/EquivalentModel1/Gates'
 * '<S69>'  : 'BIO_csi/powergui/EquivalentModel1/Sources'
 * '<S70>'  : 'BIO_csi/powergui/EquivalentModel1/Status'
 * '<S71>'  : 'BIO_csi/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_BIO_csi_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
