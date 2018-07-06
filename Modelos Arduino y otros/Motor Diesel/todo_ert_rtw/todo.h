/*
 * File: todo.h
 *
 * Code generated for Simulink model 'todo'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Feb 07 10:17:29 2018
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

/* Block signals for system '<S25>/Automatic Gain Control' */
typedef struct {
  real_T integ1;                       /* '<S31>/integ1' */
  real_T Freq;                         /* '<S31>/To avoid division by zero' */
  real_T Period;                       /* '<S31>/Period' */
  real_T VariableTransportDelay;       /* '<S31>/Variable Transport Delay' */
  real_T Sum1;                         /* '<S31>/Sum1' */
  real_T Integ2;                       /* '<S31>/Integ2' */
  real_T VariableTransportDelay1;      /* '<S31>/Variable Transport Delay1' */
  real_T Sum2;                         /* '<S31>/Sum2' */
  real_T Sum;                          /* '<S31>/Sum' */
  real_T Gain10;                       /* '<S31>/Gain10' */
  real_T Saturation;                   /* '<S31>/Saturation' */
  real_T Product2;                     /* '<S31>/Product2' */
  real_T Product;                      /* '<S31>/Product' */
  real_T Product1;                     /* '<S31>/Product1' */
} B_AutomaticGainControl_todo_T;

/* Block states (auto storage) for system '<S25>/Automatic Gain Control' */
typedef struct {
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK;      /* '<S31>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay1_RWORK;     /* '<S31>/Variable Transport Delay1' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK;      /* '<S31>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay1_PWORK;     /* '<S31>/Variable Transport Delay1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK;      /* '<S31>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay1_IWORK;     /* '<S31>/Variable Transport Delay1' */

  boolean_T AutomaticGainControl_MODE; /* '<S25>/Automatic Gain Control' */
} DW_AutomaticGainControl_todo_T;

/* Continuous states for system '<S25>/Automatic Gain Control' */
typedef struct {
  real_T integ1_CSTATE;                /* '<S31>/integ1' */
  real_T Integ2_CSTATE;                /* '<S31>/Integ2' */
} X_AutomaticGainControl_todo_T;

/* State derivatives for system '<S25>/Automatic Gain Control' */
typedef struct {
  real_T integ1_CSTATE;                /* '<S31>/integ1' */
  real_T Integ2_CSTATE;                /* '<S31>/Integ2' */
} XDot_AutomaticGainControl_tod_T;

/* State Disabled for system '<S25>/Automatic Gain Control' */
typedef struct {
  boolean_T integ1_CSTATE;             /* '<S31>/integ1' */
  boolean_T Integ2_CSTATE;             /* '<S31>/Integ2' */
} XDis_AutomaticGainControl_tod_T;

/* Block signals (auto storage) */
typedef struct {
  real_T Generador2;                   /* '<Root>/ Generador2' */
  real_T StateSpace_o1[11];            /* '<S124>/State-Space' */
  real_T StateSpace_o2[8];             /* '<S124>/State-Space' */
  real_T StateSpace_o1_f[11];          /* '<S125>/State-Space' */
  real_T StateSpace_o2_j[8];           /* '<S125>/State-Space' */
  real_T DiscreteTransferFcn;          /* '<S26>/Discrete Transfer Fcn' */
  real_T DataTypeConversion;           /* '<S49>/Data Type Conversion' */
  real_T DataTypeConversion_o;         /* '<S56>/Data Type Conversion' */
  real_T DataTypeConversion_g;         /* '<S63>/Data Type Conversion' */
  real_T DataTypeConversion_d;         /* '<S70>/Data Type Conversion' */
  real_T Gain;                         /* '<S5>/Gain' */
  real_T Delay;                        /* '<S33>/Number of samples per cycle' */
  real_T VariableTransportDelay;       /* '<S33>/Variable Transport Delay' */
  real_T Integrator_l;                 /* '<S33>/Integrator' */
  real_T Divide;                       /* '<S25>/Divide' */
  real_T Saturation2;                  /* '<S32>/Saturation2' */
  real_T Kp5;                          /* '<S32>/Kp5' */
  real_T Vq;                           /* '<S25>/Product1' */
  real_T RateLimiter;                  /* '<S25>/Rate Limiter' */
  real_T Sum2;                         /* '<S5>/Sum2' */
  real_T DiscreteTransferFcn_c;        /* '<S75>/Discrete Transfer Fcn' */
  real_T DataTypeConversion_e;         /* '<S98>/Data Type Conversion' */
  real_T DataTypeConversion_h;         /* '<S105>/Data Type Conversion' */
  real_T DataTypeConversion_dn;        /* '<S112>/Data Type Conversion' */
  real_T DataTypeConversion_n;         /* '<S119>/Data Type Conversion' */
  real_T Gain_j;                       /* '<S6>/Gain' */
  real_T Delay_m;                      /* '<S82>/Number of samples per cycle' */
  real_T VariableTransportDelay_m;     /* '<S82>/Variable Transport Delay' */
  real_T Integrator_m;                 /* '<S82>/Integrator' */
  real_T Divide_n;                     /* '<S74>/Divide' */
  real_T Saturation2_b;                /* '<S81>/Saturation2' */
  real_T Kp5_p;                        /* '<S81>/Kp5' */
  real_T Vq_k;                         /* '<S74>/Product1' */
  real_T RateLimiter_n;                /* '<S74>/Rate Limiter' */
  real_T Sum2_g;                       /* '<S6>/Sum2' */
  real_T MathFunction;                 /* '<S80>/Math Function' */
  real_T MathFunction_h;               /* '<S31>/Math Function' */
  real_T xk1[6];                       /* '<S9>/optimizer' */
  real_T u[2];                         /* '<S9>/optimizer' */
  boolean_T iAout[6];                  /* '<S9>/optimizer' */
  B_AutomaticGainControl_todo_T AutomaticGainControl_c;/* '<S74>/Automatic Gain Control' */
  B_AutomaticGainControl_todo_T AutomaticGainControl;/* '<S25>/Automatic Gain Control' */
} B_todo_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DelayTm001_DSTATE[50];        /* '<Root>/Delay Tm=0.01' */
  real_T EjeTm001s_states;             /* '<Root>/Eje Tm=0.01s' */
  real_T StateSpace_DSTATE[3];         /* '<S124>/State-Space' */
  real_T ActuadorMotorTm001s_states;   /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T last_mv_DSTATE[2];            /* '<S9>/last_mv' */
  real_T StateSpace_DSTATE_e[3];       /* '<S125>/State-Space' */
  real_T DiscreteTransferFcn_states[2];/* '<S26>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn_states_e[2];/* '<S75>/Discrete Transfer Fcn' */
  real_T EjeTm001s_tmp;                /* '<Root>/Eje Tm=0.01s' */
  real_T ActuadorMotorTm001s_tmp;      /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T last_x_PreviousInput[6];      /* '<S9>/last_x' */
  real_T TimeStampA;                   /* '<S32>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S32>/Derivative' */
  real_T TimeStampB;                   /* '<S32>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S32>/Derivative' */
  real_T PrevYA;                       /* '<S25>/Rate Limiter' */
  real_T PrevYB;                       /* '<S25>/Rate Limiter' */
  real_T LastMajorTimeA;               /* '<S25>/Rate Limiter' */
  real_T LastMajorTimeB;               /* '<S25>/Rate Limiter' */
  real_T TimeStampA_l;                 /* '<S81>/Derivative' */
  real_T LastUAtTimeA_d;               /* '<S81>/Derivative' */
  real_T TimeStampB_m;                 /* '<S81>/Derivative' */
  real_T LastUAtTimeB_f;               /* '<S81>/Derivative' */
  real_T PrevYA_n;                     /* '<S74>/Rate Limiter' */
  real_T PrevYB_m;                     /* '<S74>/Rate Limiter' */
  real_T LastMajorTimeA_c;             /* '<S74>/Rate Limiter' */
  real_T LastMajorTimeB_a;             /* '<S74>/Rate Limiter' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK;      /* '<S33>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK_b;    /* '<S82>/Variable Transport Delay' */

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
  } StateSpace_PWORK;                  /* '<S124>/State-Space' */

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
  } StateSpace_PWORK_p;                /* '<S125>/State-Space' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK;      /* '<S33>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK_a;    /* '<S82>/Variable Transport Delay' */

  int_T StateSpace_IWORK[11];          /* '<S124>/State-Space' */
  int_T StateSpace_IWORK_a[11];        /* '<S125>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK;      /* '<S33>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK_f;    /* '<S82>/Variable Transport Delay' */

  boolean_T Memory_PreviousInput[6];   /* '<S9>/Memory' */
  DW_AutomaticGainControl_todo_T AutomaticGainControl_c;/* '<S74>/Automatic Gain Control' */
  DW_AutomaticGainControl_todo_T AutomaticGainControl;/* '<S25>/Automatic Gain Control' */
} DW_todo_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S30>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S25>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S33>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S32>/Integrator' */
  real_T StateSpace_CSTATE_h[2];       /* '<S79>/State-Space' */
  real_T Integrator_CSTATE_fl;         /* '<S74>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S82>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S81>/Integrator' */
  X_AutomaticGainControl_todo_T AutomaticGainControl_c;/* '<S25>/Automatic Gain Control' */
  X_AutomaticGainControl_todo_T AutomaticGainControl;/* '<S25>/Automatic Gain Control' */
} X_todo_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S30>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S25>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S33>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S32>/Integrator' */
  real_T StateSpace_CSTATE_h[2];       /* '<S79>/State-Space' */
  real_T Integrator_CSTATE_fl;         /* '<S74>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S82>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S81>/Integrator' */
  XDot_AutomaticGainControl_tod_T AutomaticGainControl_c;/* '<S25>/Automatic Gain Control' */
  XDot_AutomaticGainControl_tod_T AutomaticGainControl;/* '<S25>/Automatic Gain Control' */
} XDot_todo_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[2];      /* '<S30>/State-Space' */
  boolean_T Integrator_CSTATE;         /* '<S25>/Integrator' */
  boolean_T Integrator_CSTATE_h;       /* '<S33>/Integrator' */
  boolean_T Integrator_CSTATE_f;       /* '<S32>/Integrator' */
  boolean_T StateSpace_CSTATE_h[2];    /* '<S79>/State-Space' */
  boolean_T Integrator_CSTATE_fl;      /* '<S74>/Integrator' */
  boolean_T Integrator_CSTATE_a;       /* '<S82>/Integrator' */
  boolean_T Integrator_CSTATE_k;       /* '<S81>/Integrator' */
  XDis_AutomaticGainControl_tod_T AutomaticGainControl_c;/* '<S25>/Automatic Gain Control' */
  XDis_AutomaticGainControl_tod_T AutomaticGainControl;/* '<S25>/Automatic Gain Control' */
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
  /* Pooled Parameter (Expression: zeros(8,1))
   * Referenced by:
   *   '<S128>/SwitchCurrents'
   *   '<S132>/SwitchCurrents'
   */
  real_T pooled16[8];

  /* Pooled Parameter (Expression: S.A)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  real_T pooled18[9];

  /* Pooled Parameter (Expression: S.B)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  real_T pooled19[27];

  /* Pooled Parameter (Expression: S.C)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  real_T pooled20[33];

  /* Pooled Parameter (Expression: S.D)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  real_T pooled21[99];

  /* Pooled Parameter (Expression: S.x0)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  real_T pooled22[3];

  /* Pooled Parameter (Expression: rep_seq_y)
   * Referenced by:
   *   '<S73>/Look-Up Table1'
   *   '<S122>/Look-Up Table1'
   */
  real_T pooled25[3];

  /* Pooled Parameter (Expression: rep_seq_t - min(rep_seq_t))
   * Referenced by:
   *   '<S73>/Look-Up Table1'
   *   '<S122>/Look-Up Table1'
   */
  real_T pooled26[3];
} ConstP_todo_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Actuador;                     /* '<Root>/Actuador' */
  real_T Par;                          /* '<Root>/Par' */
  real_T ref1;                         /* '<Root>/ref1' */
  real_T ref2;                         /* '<Root>/ref2' */
} ExtU_todo_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Volt;                         /* '<Root>/Volt' */
  real_T Current;                      /* '<Root>/Current' */
  real_T Flujo;                        /* '<Root>/Flujo' */
  real_T Velocidad;                    /* '<Root>/Velocidad' */
  real_T u2;                           /* '<Root>/u2' */
  real_T u3;                           /* '<Root>/u3' */
  real_T Volt1;                        /* '<Root>/Volt1' */
  real_T Current1;                     /* '<Root>/Current1' */
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
  real_T odeX0[14];
  real_T odeF0[14];
  real_T odeX1START[14];
  real_T odeF1[14];
  real_T odeDELTA[14];
  real_T odeE[4*14];
  real_T odeFAC[14];
  real_T odeDFDX[14*14];
  real_T odeW[14*14];
  int_T odePIVOTS[14];
  real_T odeXTMP[14];
  real_T odeZTMP[14];
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
 * Block '<S10>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S11>/Matrix Dimension Check' : Unused code path elimination
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
 * Block '<S23>/Vector Dimension Check' : Unused code path elimination
 * Block '<S9>/constant' : Unused code path elimination
 * Block '<S9>/umin_scale2' : Unused code path elimination
 * Block '<S9>/umin_scale3' : Unused code path elimination
 * Block '<S9>/ym_zero' : Unused code path elimination
 * Block '<S28>/A_Filtro' : Unused code path elimination
 * Block '<S39>/Add' : Unused code path elimination
 * Block '<S47>/0 1' : Unused code path elimination
 * Block '<S47>/Gain' : Unused code path elimination
 * Block '<S47>/Saturation' : Unused code path elimination
 * Block '<S47>/Sum' : Unused code path elimination
 * Block '<S47>/Switch' : Unused code path elimination
 * Block '<S47>/eee' : Unused code path elimination
 * Block '<S49>/0 1' : Unused code path elimination
 * Block '<S49>/1//Rsw' : Unused code path elimination
 * Block '<S49>/Switch' : Unused code path elimination
 * Block '<S40>/Add' : Unused code path elimination
 * Block '<S54>/0 1' : Unused code path elimination
 * Block '<S54>/Gain' : Unused code path elimination
 * Block '<S54>/Saturation' : Unused code path elimination
 * Block '<S54>/Sum' : Unused code path elimination
 * Block '<S54>/Switch' : Unused code path elimination
 * Block '<S54>/eee' : Unused code path elimination
 * Block '<S56>/0 1' : Unused code path elimination
 * Block '<S56>/1//Rsw' : Unused code path elimination
 * Block '<S56>/Switch' : Unused code path elimination
 * Block '<S41>/Add' : Unused code path elimination
 * Block '<S61>/0 1' : Unused code path elimination
 * Block '<S61>/Gain' : Unused code path elimination
 * Block '<S61>/Saturation' : Unused code path elimination
 * Block '<S61>/Sum' : Unused code path elimination
 * Block '<S61>/Switch' : Unused code path elimination
 * Block '<S61>/eee' : Unused code path elimination
 * Block '<S63>/0 1' : Unused code path elimination
 * Block '<S63>/1//Rsw' : Unused code path elimination
 * Block '<S63>/Switch' : Unused code path elimination
 * Block '<S42>/Add' : Unused code path elimination
 * Block '<S68>/0 1' : Unused code path elimination
 * Block '<S68>/Gain' : Unused code path elimination
 * Block '<S68>/Saturation' : Unused code path elimination
 * Block '<S68>/Sum' : Unused code path elimination
 * Block '<S68>/Switch' : Unused code path elimination
 * Block '<S68>/eee' : Unused code path elimination
 * Block '<S70>/0 1' : Unused code path elimination
 * Block '<S70>/1//Rsw' : Unused code path elimination
 * Block '<S70>/Switch' : Unused code path elimination
 * Block '<S43>/do not delete this gain' : Unused code path elimination
 * Block '<S5>/Ref1' : Unused code path elimination
 * Block '<S29>/Scope1' : Unused code path elimination
 * Block '<S29>/Scope2' : Unused code path elimination
 * Block '<S77>/A_Filtro' : Unused code path elimination
 * Block '<S88>/Add' : Unused code path elimination
 * Block '<S96>/0 1' : Unused code path elimination
 * Block '<S96>/Gain' : Unused code path elimination
 * Block '<S96>/Saturation' : Unused code path elimination
 * Block '<S96>/Sum' : Unused code path elimination
 * Block '<S96>/Switch' : Unused code path elimination
 * Block '<S96>/eee' : Unused code path elimination
 * Block '<S98>/0 1' : Unused code path elimination
 * Block '<S98>/1//Rsw' : Unused code path elimination
 * Block '<S98>/Switch' : Unused code path elimination
 * Block '<S89>/Add' : Unused code path elimination
 * Block '<S103>/0 1' : Unused code path elimination
 * Block '<S103>/Gain' : Unused code path elimination
 * Block '<S103>/Saturation' : Unused code path elimination
 * Block '<S103>/Sum' : Unused code path elimination
 * Block '<S103>/Switch' : Unused code path elimination
 * Block '<S103>/eee' : Unused code path elimination
 * Block '<S105>/0 1' : Unused code path elimination
 * Block '<S105>/1//Rsw' : Unused code path elimination
 * Block '<S105>/Switch' : Unused code path elimination
 * Block '<S90>/Add' : Unused code path elimination
 * Block '<S110>/0 1' : Unused code path elimination
 * Block '<S110>/Gain' : Unused code path elimination
 * Block '<S110>/Saturation' : Unused code path elimination
 * Block '<S110>/Sum' : Unused code path elimination
 * Block '<S110>/Switch' : Unused code path elimination
 * Block '<S110>/eee' : Unused code path elimination
 * Block '<S112>/0 1' : Unused code path elimination
 * Block '<S112>/1//Rsw' : Unused code path elimination
 * Block '<S112>/Switch' : Unused code path elimination
 * Block '<S91>/Add' : Unused code path elimination
 * Block '<S117>/0 1' : Unused code path elimination
 * Block '<S117>/Gain' : Unused code path elimination
 * Block '<S117>/Saturation' : Unused code path elimination
 * Block '<S117>/Sum' : Unused code path elimination
 * Block '<S117>/Switch' : Unused code path elimination
 * Block '<S117>/eee' : Unused code path elimination
 * Block '<S119>/0 1' : Unused code path elimination
 * Block '<S119>/1//Rsw' : Unused code path elimination
 * Block '<S119>/Switch' : Unused code path elimination
 * Block '<S92>/do not delete this gain' : Unused code path elimination
 * Block '<S6>/Ref1' : Unused code path elimination
 * Block '<S78>/Scope1' : Unused code path elimination
 * Block '<S78>/Scope2' : Unused code path elimination
 * Block '<S9>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S9>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S9>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S9>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S9>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/ymin_scale' : Eliminated nontunable gain of 1
 * Block '<S32>/Kp1' : Eliminated nontunable gain of 1
 * Block '<S34>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S35>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S73>/Output' : Eliminate redundant signal conversion block
 * Block '<S81>/Kp1' : Eliminated nontunable gain of 1
 * Block '<S83>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S84>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S122>/Output' : Eliminate redundant signal conversion block
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
 * '<S6>'   : 'todo/Subsystem2'
 * '<S7>'   : 'todo/powergui'
 * '<S8>'   : 'todo/Linear Transformer/Model'
 * '<S9>'   : 'todo/MPC Controller/MPC'
 * '<S10>'  : 'todo/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S11>'  : 'todo/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S12>'  : 'todo/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S13>'  : 'todo/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S14>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S15>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S16>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S17>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S18>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S19>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S20>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S21>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S22>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S23>'  : 'todo/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S24>'  : 'todo/MPC Controller/MPC/optimizer'
 * '<S25>'  : 'todo/Subsystem1/1-phase PLL'
 * '<S26>'  : 'todo/Subsystem1/Control PR'
 * '<S27>'  : 'todo/Subsystem1/Filtro'
 * '<S28>'  : 'todo/Subsystem1/Inversor4'
 * '<S29>'  : 'todo/Subsystem1/SPWM'
 * '<S30>'  : 'todo/Subsystem1/1-phase PLL/2nd-Order Filter'
 * '<S31>'  : 'todo/Subsystem1/1-phase PLL/Automatic Gain Control'
 * '<S32>'  : 'todo/Subsystem1/1-phase PLL/PID Controller'
 * '<S33>'  : 'todo/Subsystem1/1-phase PLL/Variable Frequency Mean value'
 * '<S34>'  : 'todo/Subsystem1/Filtro/Current Measurement'
 * '<S35>'  : 'todo/Subsystem1/Filtro/Vo3'
 * '<S36>'  : 'todo/Subsystem1/Filtro/Current Measurement/Model'
 * '<S37>'  : 'todo/Subsystem1/Filtro/Vo3/Model'
 * '<S38>'  : 'todo/Subsystem1/Inversor4/Controlled Voltage Source2'
 * '<S39>'  : 'todo/Subsystem1/Inversor4/Mosfet'
 * '<S40>'  : 'todo/Subsystem1/Inversor4/Mosfet1'
 * '<S41>'  : 'todo/Subsystem1/Inversor4/Mosfet2'
 * '<S42>'  : 'todo/Subsystem1/Inversor4/Mosfet3'
 * '<S43>'  : 'todo/Subsystem1/Inversor4/Vo4'
 * '<S44>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode'
 * '<S45>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch'
 * '<S46>'  : 'todo/Subsystem1/Inversor4/Mosfet/Measurement list'
 * '<S47>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode/Model'
 * '<S48>'  : 'todo/Subsystem1/Inversor4/Mosfet/Diode/Model/Measurement list'
 * '<S49>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model'
 * '<S50>'  : 'todo/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S51>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode'
 * '<S52>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch'
 * '<S53>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Measurement list'
 * '<S54>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode/Model'
 * '<S55>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Diode/Model/Measurement list'
 * '<S56>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model'
 * '<S57>'  : 'todo/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model/Measurement list'
 * '<S58>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode'
 * '<S59>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch'
 * '<S60>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Measurement list'
 * '<S61>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode/Model'
 * '<S62>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Diode/Model/Measurement list'
 * '<S63>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model'
 * '<S64>'  : 'todo/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model/Measurement list'
 * '<S65>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode'
 * '<S66>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch'
 * '<S67>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Measurement list'
 * '<S68>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode/Model'
 * '<S69>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Diode/Model/Measurement list'
 * '<S70>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model'
 * '<S71>'  : 'todo/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model/Measurement list'
 * '<S72>'  : 'todo/Subsystem1/Inversor4/Vo4/Model'
 * '<S73>'  : 'todo/Subsystem1/SPWM/10V~5KHz'
 * '<S74>'  : 'todo/Subsystem2/1-phase PLL'
 * '<S75>'  : 'todo/Subsystem2/Control PR'
 * '<S76>'  : 'todo/Subsystem2/Filtro'
 * '<S77>'  : 'todo/Subsystem2/Inversor4'
 * '<S78>'  : 'todo/Subsystem2/SPWM'
 * '<S79>'  : 'todo/Subsystem2/1-phase PLL/2nd-Order Filter'
 * '<S80>'  : 'todo/Subsystem2/1-phase PLL/Automatic Gain Control'
 * '<S81>'  : 'todo/Subsystem2/1-phase PLL/PID Controller'
 * '<S82>'  : 'todo/Subsystem2/1-phase PLL/Variable Frequency Mean value'
 * '<S83>'  : 'todo/Subsystem2/Filtro/Current Measurement'
 * '<S84>'  : 'todo/Subsystem2/Filtro/Vo3'
 * '<S85>'  : 'todo/Subsystem2/Filtro/Current Measurement/Model'
 * '<S86>'  : 'todo/Subsystem2/Filtro/Vo3/Model'
 * '<S87>'  : 'todo/Subsystem2/Inversor4/Controlled Voltage Source2'
 * '<S88>'  : 'todo/Subsystem2/Inversor4/Mosfet'
 * '<S89>'  : 'todo/Subsystem2/Inversor4/Mosfet1'
 * '<S90>'  : 'todo/Subsystem2/Inversor4/Mosfet2'
 * '<S91>'  : 'todo/Subsystem2/Inversor4/Mosfet3'
 * '<S92>'  : 'todo/Subsystem2/Inversor4/Vo4'
 * '<S93>'  : 'todo/Subsystem2/Inversor4/Mosfet/Diode'
 * '<S94>'  : 'todo/Subsystem2/Inversor4/Mosfet/Ideal Switch'
 * '<S95>'  : 'todo/Subsystem2/Inversor4/Mosfet/Measurement list'
 * '<S96>'  : 'todo/Subsystem2/Inversor4/Mosfet/Diode/Model'
 * '<S97>'  : 'todo/Subsystem2/Inversor4/Mosfet/Diode/Model/Measurement list'
 * '<S98>'  : 'todo/Subsystem2/Inversor4/Mosfet/Ideal Switch/Model'
 * '<S99>'  : 'todo/Subsystem2/Inversor4/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S100>' : 'todo/Subsystem2/Inversor4/Mosfet1/Diode'
 * '<S101>' : 'todo/Subsystem2/Inversor4/Mosfet1/Ideal Switch'
 * '<S102>' : 'todo/Subsystem2/Inversor4/Mosfet1/Measurement list'
 * '<S103>' : 'todo/Subsystem2/Inversor4/Mosfet1/Diode/Model'
 * '<S104>' : 'todo/Subsystem2/Inversor4/Mosfet1/Diode/Model/Measurement list'
 * '<S105>' : 'todo/Subsystem2/Inversor4/Mosfet1/Ideal Switch/Model'
 * '<S106>' : 'todo/Subsystem2/Inversor4/Mosfet1/Ideal Switch/Model/Measurement list'
 * '<S107>' : 'todo/Subsystem2/Inversor4/Mosfet2/Diode'
 * '<S108>' : 'todo/Subsystem2/Inversor4/Mosfet2/Ideal Switch'
 * '<S109>' : 'todo/Subsystem2/Inversor4/Mosfet2/Measurement list'
 * '<S110>' : 'todo/Subsystem2/Inversor4/Mosfet2/Diode/Model'
 * '<S111>' : 'todo/Subsystem2/Inversor4/Mosfet2/Diode/Model/Measurement list'
 * '<S112>' : 'todo/Subsystem2/Inversor4/Mosfet2/Ideal Switch/Model'
 * '<S113>' : 'todo/Subsystem2/Inversor4/Mosfet2/Ideal Switch/Model/Measurement list'
 * '<S114>' : 'todo/Subsystem2/Inversor4/Mosfet3/Diode'
 * '<S115>' : 'todo/Subsystem2/Inversor4/Mosfet3/Ideal Switch'
 * '<S116>' : 'todo/Subsystem2/Inversor4/Mosfet3/Measurement list'
 * '<S117>' : 'todo/Subsystem2/Inversor4/Mosfet3/Diode/Model'
 * '<S118>' : 'todo/Subsystem2/Inversor4/Mosfet3/Diode/Model/Measurement list'
 * '<S119>' : 'todo/Subsystem2/Inversor4/Mosfet3/Ideal Switch/Model'
 * '<S120>' : 'todo/Subsystem2/Inversor4/Mosfet3/Ideal Switch/Model/Measurement list'
 * '<S121>' : 'todo/Subsystem2/Inversor4/Vo4/Model'
 * '<S122>' : 'todo/Subsystem2/SPWM/10V~5KHz'
 * '<S123>' : 'todo/powergui/EquivalentModel1'
 * '<S124>' : 'todo/powergui/EquivalentModel2'
 * '<S125>' : 'todo/powergui/EquivalentModel3'
 * '<S126>' : 'todo/powergui/EquivalentModel1/Sources'
 * '<S127>' : 'todo/powergui/EquivalentModel2/Gates'
 * '<S128>' : 'todo/powergui/EquivalentModel2/Sources'
 * '<S129>' : 'todo/powergui/EquivalentModel2/Status'
 * '<S130>' : 'todo/powergui/EquivalentModel2/Yout'
 * '<S131>' : 'todo/powergui/EquivalentModel3/Gates'
 * '<S132>' : 'todo/powergui/EquivalentModel3/Sources'
 * '<S133>' : 'todo/powergui/EquivalentModel3/Status'
 * '<S134>' : 'todo/powergui/EquivalentModel3/Yout'
 */
#endif                                 /* RTW_HEADER_todo_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
