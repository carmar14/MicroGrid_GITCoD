/*
 * File: carga.h
 *
 * Code generated for Simulink model 'carga'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Fri Jul 06 11:12:23 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_carga_h_
#define RTW_HEADER_carga_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef carga_COMMON_INCLUDES_
# define carga_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* carga_COMMON_INCLUDES_ */

#include "carga_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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
  real_T Sum;                          /* '<Root>/Sum' */
  real_T StateSpace[2];                /* '<S18>/State-Space' */
  real_T Memory;                       /* '<S12>/Memory' */
  real_T Switch;                       /* '<S12>/Switch' */
  real_T Memory_l;                     /* '<S11>/Memory' */
  real_T Switch_n;                     /* '<S11>/Switch' */
  real_T Memory_p;                     /* '<S16>/Memory' */
  real_T Switch_nu;                    /* '<S16>/Switch' */
  real_T Memory_o;                     /* '<S15>/Memory' */
  real_T Switch_c;                     /* '<S15>/Switch' */
  real_T Product;                      /* '<S7>/Product' */
  real_T Product1;                     /* '<S7>/Product1' */
  real_T Product_a;                    /* '<S8>/Product' */
  real_T Product1_a;                   /* '<S8>/Product1' */
} B_carga_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[2];         /* '<S18>/State-Space' */
  real_T Memory_PreviousInput;         /* '<S12>/Memory' */
  real_T Memory_PreviousInput_l;       /* '<S11>/Memory' */
  real_T Memory_PreviousInput_o;       /* '<S16>/Memory' */
  real_T Memory_PreviousInput_n;       /* '<S15>/Memory' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S12>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_a;            /* '<S11>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_d;            /* '<S16>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_l;            /* '<S15>/Transport Delay' */

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
  } StateSpace_PWORK;                  /* '<S18>/State-Space' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S12>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_f;            /* '<S11>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_h;            /* '<S16>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_fd;           /* '<S15>/Transport Delay' */

  int_T StateSpace_IWORK[11];          /* '<S18>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S12>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_e;            /* '<S11>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_a;            /* '<S16>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_c;            /* '<S15>/Transport Delay' */
} DW_carga_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S12>/integrator' */
  real_T integrator_CSTATE_c;          /* '<S11>/integrator' */
  real_T integrator_CSTATE_i;          /* '<S16>/integrator' */
  real_T integrator_CSTATE_b;          /* '<S15>/integrator' */
} X_carga_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S12>/integrator' */
  real_T integrator_CSTATE_c;          /* '<S11>/integrator' */
  real_T integrator_CSTATE_i;          /* '<S16>/integrator' */
  real_T integrator_CSTATE_b;          /* '<S15>/integrator' */
} XDot_carga_T;

/* State disabled  */
typedef struct {
  boolean_T integrator_CSTATE;         /* '<S12>/integrator' */
  boolean_T integrator_CSTATE_c;       /* '<S11>/integrator' */
  boolean_T integrator_CSTATE_i;       /* '<S16>/integrator' */
  boolean_T integrator_CSTATE_b;       /* '<S15>/integrator' */
} XDis_carga_T;

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
  /* Expression: S.A
   * Referenced by: '<S18>/State-Space'
   */
  real_T StateSpace_AS_param[4];

  /* Expression: S.B
   * Referenced by: '<S18>/State-Space'
   */
  real_T StateSpace_BS_param[2];

  /* Expression: S.C
   * Referenced by: '<S18>/State-Space'
   */
  real_T StateSpace_CS_param[4];

  /* Expression: S.D
   * Referenced by: '<S18>/State-Space'
   */
  real_T StateSpace_DS_param[2];

  /* Expression: S.x0
   * Referenced by: '<S18>/State-Space'
   */
  real_T StateSpace_X0_param[2];
} ConstP_carga_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T I_die;                        /* '<Root>/I_die' */
  real_T I_bio;                        /* '<Root>/I_bio' */
  real_T I_pv;                         /* '<Root>/I_pv' */
} ExtU_carga_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Corriente_load;               /* '<Root>/Corriente_load' */
  real_T Voltaje_load;                 /* '<Root>/Voltaje_load' */
  real_T P_meas;                       /* '<Root>/P_meas' */
  real_T Q_meas;                       /* '<Root>/Q_meas' */
} ExtY_carga_T;

/* Real-time Model Data Structure */
struct tag_RTM_carga_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_carga_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[4];
  real_T odeF[4][4];
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
extern B_carga_T carga_B;

/* Continuous states (auto storage) */
extern X_carga_T carga_X;

/* Block states (auto storage) */
extern DW_carga_T carga_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_carga_T carga_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_carga_T carga_Y;

/* Constant parameters (auto storage) */
extern const ConstP_carga_T carga_ConstP;

/* Model entry point functions */
extern void carga_initialize(void);
extern void carga_step(void);
extern void carga_terminate(void);

/* Real-time Model object */
extern RT_MODEL_carga_T *const carga_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S4>/do not delete this gain' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'carga'
 * '<S1>'   : 'carga/Controlled Current Source'
 * '<S2>'   : 'carga/I sens A'
 * '<S3>'   : 'carga/Power'
 * '<S4>'   : 'carga/Vmeas'
 * '<S5>'   : 'carga/powergui'
 * '<S6>'   : 'carga/I sens A/Model'
 * '<S7>'   : 'carga/Power/Fourier'
 * '<S8>'   : 'carga/Power/Fourier1'
 * '<S9>'   : 'carga/Power/Fourier/Mean'
 * '<S10>'  : 'carga/Power/Fourier/Mean value1'
 * '<S11>'  : 'carga/Power/Fourier/Mean/Model'
 * '<S12>'  : 'carga/Power/Fourier/Mean value1/Model'
 * '<S13>'  : 'carga/Power/Fourier1/Mean'
 * '<S14>'  : 'carga/Power/Fourier1/Mean value1'
 * '<S15>'  : 'carga/Power/Fourier1/Mean/Model'
 * '<S16>'  : 'carga/Power/Fourier1/Mean value1/Model'
 * '<S17>'  : 'carga/Vmeas/Model'
 * '<S18>'  : 'carga/powergui/EquivalentModel1'
 * '<S19>'  : 'carga/powergui/EquivalentModel1/Sources'
 * '<S20>'  : 'carga/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_carga_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
