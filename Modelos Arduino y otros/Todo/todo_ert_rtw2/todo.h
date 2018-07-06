/*
 * File: todo.h
 *
 * Code generated for Simulink model 'todo'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Feb 06 11:02:51 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_todo_h_
#define RTW_HEADER_todo_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef todo_COMMON_INCLUDES_
# define todo_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* todo_COMMON_INCLUDES_ */

#include "todo_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "rt_matrixlib.h"

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
  real_T StateSpace_o1[11];            /* '<S74>/State-Space' */
  real_T StateSpace_o2[8];             /* '<S74>/State-Space' */
  real_T DiscreteTransferFcn;          /* '<S25>/Discrete Transfer Fcn' */
  real_T DataTypeConversion;           /* '<S48>/Data Type Conversion' */
  real_T DataTypeConversion_o;         /* '<S55>/Data Type Conversion' */
  real_T DataTypeConversion_g;         /* '<S62>/Data Type Conversion' */
  real_T DataTypeConversion_d;         /* '<S69>/Data Type Conversion' */
  real_T Gain;                         /* '<S5>/Gain' */
  real_T Delay;                        /* '<S32>/Number of samples per cycle' */
  real_T VariableTransportDelay;       /* '<S32>/Variable Transport Delay' */
  real_T Integrator_l;                 /* '<S32>/Integrator' */
  real_T Divide;                       /* '<S24>/Divide' */
  real_T Saturation2;                  /* '<S31>/Saturation2' */
  real_T Kp5;                          /* '<S31>/Kp5' */
  real_T Vq;                           /* '<S24>/Product1' */
  real_T RateLimiter;                  /* '<S24>/Rate Limiter' */
  real_T Sum2;                         /* '<S5>/Sum2' */
  real_T integ1;                       /* '<S30>/integ1' */
  real_T Period;                       /* '<S30>/Period' */
  real_T VariableTransportDelay_p;     /* '<S30>/Variable Transport Delay' */
  real_T Integ2;                       /* '<S30>/Integ2' */
  real_T VariableTransportDelay1;      /* '<S30>/Variable Transport Delay1' */
  real_T MathFunction;                 /* '<S30>/Math Function' */
  real_T Product;                      /* '<S30>/Product' */
  real_T Product1;                     /* '<S30>/Product1' */
  real_T xk1[6];                       /* '<S8>/optimizer' */
  real_T u[2];                         /* '<S8>/optimizer' */
  boolean_T iAout[6];                  /* '<S8>/optimizer' */
} B_todo_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[3];         /* '<S74>/State-Space' */
  real_T DiscreteTransferFcn_states[2];/* '<S25>/Discrete Transfer Fcn' */
  real_T ActuadorMotorTm001s_states;   /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T DelayTm001_DSTATE[50];        /* '<Root>/Delay Tm=0.01' */
  real_T EjeTm001s_states;             /* '<Root>/Eje Tm=0.01s' */
  real_T last_mv_DSTATE[2];            /* '<S8>/last_mv' */
  real_T TimeStampA;                   /* '<S31>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S31>/Derivative' */
  real_T TimeStampB;                   /* '<S31>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S31>/Derivative' */
  real_T PrevYA;                       /* '<S24>/Rate Limiter' */
  real_T PrevYB;                       /* '<S24>/Rate Limiter' */
  real_T LastMajorTimeA;               /* '<S24>/Rate Limiter' */
  real_T LastMajorTimeB;               /* '<S24>/Rate Limiter' */
  real_T ActuadorMotorTm001s_tmp;      /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T EjeTm001s_tmp;                /* '<Root>/Eje Tm=0.01s' */
  real_T last_x_PreviousInput[6];      /* '<S8>/last_x' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK;      /* '<S32>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK_m;    /* '<S30>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay1_RWORK;     /* '<S30>/Variable Transport Delay1' */

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
  } StateSpace_PWORK;                  /* '<S74>/State-Space' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK;      /* '<S32>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK_c;    /* '<S30>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay1_PWORK;     /* '<S30>/Variable Transport Delay1' */

  int_T StateSpace_IWORK[11];          /* '<S74>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK;      /* '<S32>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK_e;    /* '<S30>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay1_IWORK;     /* '<S30>/Variable Transport Delay1' */

  boolean_T Memory_PreviousInput[6];   /* '<S8>/Memory' */
  boolean_T AutomaticGainControl_MODE; /* '<S24>/Automatic Gain Control' */
} DW_todo_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S29>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S24>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S32>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S31>/Integrator' */
  real_T integ1_CSTATE;                /* '<S30>/integ1' */
  real_T Integ2_CSTATE;                /* '<S30>/Integ2' */
} X_todo_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S29>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S24>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S32>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S31>/Integrator' */
  real_T integ1_CSTATE;                /* '<S30>/integ1' */
  real_T Integ2_CSTATE;                /* '<S30>/Integ2' */
} XDot_todo_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[2];      /* '<S29>/State-Space' */
  boolean_T Integrator_CSTATE;         /* '<S24>/Integrator' */
  boolean_T Integrator_CSTATE_h;       /* '<S32>/Integrator' */
  boolean_T Integrator_CSTATE_f;       /* '<S31>/Integrator' */
  boolean_T integ1_CSTATE;             /* '<S30>/integ1' */
  boolean_T Integ2_CSTATE;             /* '<S30>/Integ2' */
} XDis_todo_T;

#ifndef ODE14X_INTG
#define ODE14X_INTG

/* ODE14X Integration Data */
typedef struct {
  real_T *x0;
  real_T *f0;
  real_T *x1start;
  real_T *f1;
  real_T *Delta;
  real_T *E;
  real_T *fac;
  real_T *DFDX;
  real_T *W;
  int_T *pivots;
  real_T *xtmp;
  real_T *ztmp;
  real_T *M;
  real_T *M1;
  real_T *Edot;
  real_T *xdot;
  real_T *fminusMxdot;
  boolean_T isFirstStep;
} ODE14X_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: zeros(8,1)
   * Referenced by: '<S77>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[8];

  /* Expression: S.A
   * Referenced by: '<S74>/State-Space'
   */
  real_T StateSpace_AS_param[9];

  /* Expression: S.B
   * Referenced by: '<S74>/State-Space'
   */
  real_T StateSpace_BS_param[27];

  /* Expression: S.C
   * Referenced by: '<S74>/State-Space'
   */
  real_T StateSpace_CS_param[33];

  /* Expression: S.D
   * Referenced by: '<S74>/State-Space'
   */
  real_T StateSpace_DS_param[99];

  /* Expression: S.x0
   * Referenced by: '<S74>/State-Space'
   */
  real_T StateSpace_X0_param[3];

  /* Expression: rep_seq_y
   * Referenced by: '<S72>/Look-Up Table1'
   */
  real_T LookUpTable1_tableData[3];

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S72>/Look-Up Table1'
   */
  real_T LookUpTable1_bp01Data[3];
} ConstP_todo_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vdc;                          /* '<Root>/Vdc' */
  real_T u1;                           /* '<Root>/u1' */
  real_T Actuador;                     /* '<Root>/Actuador' */
  real_T Par;                          /* '<Root>/Par' */
  real_T Corriente1;                   /* '<Root>/Corriente 1' */
  real_T Corriente2;                   /* '<Root>/Corriente 2' */
  real_T ref1;                         /* '<Root>/ref1' */
  real_T ref2;                         /* '<Root>/ref2' */
} ExtU_todo_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Volt;                         /* '<Root>/Volt' */
  real_T Current;                      /* '<Root>/Current' */
  real_T Flujo;                        /* '<Root>/Flujo' */
  real_T Velocidad;                    /* '<Root>/Velocidad' */
  real_T Tensin;                       /* '<Root>/Tensión' */
  real_T u2;                           /* '<Root>/u2' */
  real_T u3;                           /* '<Root>/u3' */
} ExtY_todo_T;

/* Real-time Model Data Structure */
struct tag_RTM_todo_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_todo_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeX0[7];
  real_T odeF0[7];
  real_T odeX1START[7];
  real_T odeF1[7];
  real_T odeDELTA[7];
  real_T odeE[4*7];
  real_T odeFAC[7];
  real_T odeDFDX[7*7];
  real_T odeW[7*7];
  int_T odePIVOTS[7];
  real_T odeXTMP[7];
  real_T odeZTMP[7];
  ODE14X_IntgData intgData;

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
    struct {
      uint16_T TID[4];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[4];
  } Timing;
};

/* Block signals (auto storage) */
extern B_todo_T todo_B;

/* Continuous states (auto storage) */
extern X_todo_T todo_X;

/* Block states (auto storage) */
extern DW_todo_T todo_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_todo_T todo_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_todo_T todo_Y;

/* Constant parameters (auto storage) */
extern const ConstP_todo_T todo_ConstP;

/* Model entry point functions */
extern void todo_initialize(void);
extern void todo_step(void);
extern void todo_terminate(void);

/* Real-time Model object */
extern RT_MODEL_todo_T *const todo_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S9>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S10>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S11>/Vector Dimension Check' : Unused code path elimination
 * Block '<S12>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Vector Dimension Check' : Unused code path elimination
 * Block '<S14>/Vector Dimension Check' : Unused code path elimination
 * Block '<S15>/Vector Dimension Check' : Unused code path elimination
 * Block '<S16>/Vector Dimension Check' : Unused code path elimination
 * Block '<S17>/Vector Dimension Check' : Unused code path elimination
 * Block '<S18>/Vector Dimension Check' : Unused code path elimination
 * Block '<S19>/Vector Dimension Check' : Unused code path elimination
 * Block '<S20>/Vector Dimension Check' : Unused code path elimination
 * Block '<S21>/Vector Dimension Check' : Unused code path elimination
 * Block '<S22>/Vector Dimension Check' : Unused code path elimination
 * Block '<S8>/constant' : Unused code path elimination
 * Block '<S8>/umin_scale2' : Unused code path elimination
 * Block '<S8>/umin_scale3' : Unused code path elimination
 * Block '<S8>/ym_zero' : Unused code path elimination
 * Block '<S27>/A_Filtro' : Unused code path elimination
 * Block '<S38>/Add' : Unused code path elimination
 * Block '<S46>/0 1' : Unused code path elimination
 * Block '<S46>/Gain' : Unused code path elimination
 * Block '<S46>/Saturation' : Unused code path elimination
 * Block '<S46>/Sum' : Unused code path elimination
 * Block '<S46>/Switch' : Unused code path elimination
 * Block '<S46>/eee' : Unused code path elimination
 * Block '<S48>/0 1' : Unused code path elimination
 * Block '<S48>/1//Rsw' : Unused code path elimination
 * Block '<S48>/Switch' : Unused code path elimination
 * Block '<S39>/Add' : Unused code path elimination
 * Block '<S53>/0 1' : Unused code path elimination
 * Block '<S53>/Gain' : Unused code path elimination
 * Block '<S53>/Saturation' : Unused code path elimination
 * Block '<S53>/Sum' : Unused code path elimination
 * Block '<S53>/Switch' : Unused code path elimination
 * Block '<S53>/eee' : Unused code path elimination
 * Block '<S55>/0 1' : Unused code path elimination
 * Block '<S55>/1//Rsw' : Unused code path elimination
 * Block '<S55>/Switch' : Unused code path elimination
 * Block '<S40>/Add' : Unused code path elimination
 * Block '<S60>/0 1' : Unused code path elimination
 * Block '<S60>/Gain' : Unused code path elimination
 * Block '<S60>/Saturation' : Unused code path elimination
 * Block '<S60>/Sum' : Unused code path elimination
 * Block '<S60>/Switch' : Unused code path elimination
 * Block '<S60>/eee' : Unused code path elimination
 * Block '<S62>/0 1' : Unused code path elimination
 * Block '<S62>/1//Rsw' : Unused code path elimination
 * Block '<S62>/Switch' : Unused code path elimination
 * Block '<S41>/Add' : Unused code path elimination
 * Block '<S67>/0 1' : Unused code path elimination
 * Block '<S67>/Gain' : Unused code path elimination
 * Block '<S67>/Saturation' : Unused code path elimination
 * Block '<S67>/Sum' : Unused code path elimination
 * Block '<S67>/Switch' : Unused code path elimination
 * Block '<S67>/eee' : Unused code path elimination
 * Block '<S69>/0 1' : Unused code path elimination
 * Block '<S69>/1//Rsw' : Unused code path elimination
 * Block '<S69>/Switch' : Unused code path elimination
 * Block '<S42>/do not delete this gain' : Unused code path elimination
 * Block '<S5>/Ref1' : Unused code path elimination
 * Block '<S28>/Scope1' : Unused code path elimination
 * Block '<S28>/Scope2' : Unused code path elimination
 * Block '<S8>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S8>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S8>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S8>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/ymin_scale' : Eliminated nontunable gain of 1
 * Block '<S31>/Kp1' : Eliminated nontunable gain of 1
 * Block '<S33>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S34>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S72>/Output' : Eliminate redundant signal conversion block
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
 * '<Root>' : 'todo'
 * '<S1>'   : 'todo/Controlled Current Source'
 * '<S2>'   : 'todo/Controlled Current Source1'
 * '<S3>'   : 'todo/Linear Transformer'
 * '<S4>'   : 'todo/MPC Controller'
 * '<S5>'   : 'todo/Subsystem1'
 * '<S6>'   : 'todo/powergui'
 * '<S7>'   : 'todo/Linear Transformer/Model'
 * '<S8>'   : 'todo/MPC Controller/MPC'
 * '<S9>'   : 'todo/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S10>'  : 'todo/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S11>'  : 'todo/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S12>'  : 'todo/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S13>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S14>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S15>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S16>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S17>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S18>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S19>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S20>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S21>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S22>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S23>'  : 'todo/MPC Controller/MPC/optimizer'
 * '<S24>'  : 'todo/Subsystem1/1-phase PLL'
 * '<S25>'  : 'todo/Subsystem1/Control PR'
 * '<S26>'  : 'todo/Subsystem1/Filtro'
 * '<S27>'  : 'todo/Subsystem1/Inversor4'
 * '<S28>'  : 'todo/Subsystem1/SPWM'
 * '<S29>'  : 'todo/Subsystem1/1-phase PLL/2nd-Order Filter'
 * '<S30>'  : 'todo/Subsystem1/1-phase PLL/Automatic Gain Control'
 * '<S31>'  : 'todo/Subsystem1/1-phase PLL/PID Controller'
 * '<S32>'  : 'todo/Subsystem1/1-phase PLL/Variable Frequency Mean value'
 * '<S33>'  : 'todo/Subsystem1/Filtro/Current Measurement'
 * '<S34>'  : 'todo/Subsystem1/Filtro/Vo3'
 * '<S35>'  : 'todo/Subsystem1/Filtro/Current Measurement/Model'
 * '<S36>'  : 'todo/Subsystem1/Filtro/Vo3/Model'
 * '<S37>'  : 'todo/Subsystem1/Inversor4/Controlled Voltage Source2'
 * '<S38>'  : 'todo/Subsystem1/Inversor4/Mosfet'
 * '<S39>'  : 'todo/Subsystem1/Inversor4/Mosfet1'
 * '<S40>'  : 'todo/Subsystem1/Inversor4/Mosfet2'
 * '<S41>'  : 'todo/Subsystem1/Inversor4/Mosfet3'
 * '<S42>'  : 'todo/Subsystem1/Inversor4/Vo4'
 * '<S43>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode'
 * '<S44>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch'
 * '<S45>'  : 'todo/Subsystem1/Inversor4/Mosfet/Measurement list'
 * '<S46>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode/Model'
 * '<S47>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode/Model/Measurement list'
 * '<S48>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model'
 * '<S49>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S50>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode'
 * '<S51>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch'
 * '<S52>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Measurement list'
 * '<S53>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode/Model'
 * '<S54>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode/Model/Measurement list'
 * '<S55>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model'
 * '<S56>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model/Measurement list'
 * '<S57>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode'
 * '<S58>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch'
 * '<S59>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Measurement list'
 * '<S60>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode/Model'
 * '<S61>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode/Model/Measurement list'
 * '<S62>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model'
 * '<S63>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model/Measurement list'
 * '<S64>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode'
 * '<S65>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch'
 * '<S66>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Measurement list'
 * '<S67>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode/Model'
 * '<S68>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode/Model/Measurement list'
 * '<S69>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model'
 * '<S70>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model/Measurement list'
 * '<S71>'  : 'todo/Subsystem1/Inversor4/Vo4/Model'
 * '<S72>'  : 'todo/Subsystem1/SPWM/10V~5KHz'
 * '<S73>'  : 'todo/powergui/EquivalentModel1'
 * '<S74>'  : 'todo/powergui/EquivalentModel2'
 * '<S75>'  : 'todo/powergui/EquivalentModel1/Sources'
 * '<S76>'  : 'todo/powergui/EquivalentModel2/Gates'
 * '<S77>'  : 'todo/powergui/EquivalentModel2/Sources'
 * '<S78>'  : 'todo/powergui/EquivalentModel2/Status'
 * '<S79>'  : 'todo/powergui/EquivalentModel2/Yout'
 */
#endif                                 /* RTW_HEADER_todo_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
