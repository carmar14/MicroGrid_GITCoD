/*
 * File: code_programacion_lineal_.h
 *
 * Code generated for Simulink model 'code_programacion_lineal_'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 10 15:52:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_code_programacion_lineal__h_
#define RTW_HEADER_code_programacion_lineal__h_
#include <stddef.h>
#include <string.h>
#ifndef code_programacion_lineal__COMMON_INCLUDES_
# define code_programacion_lineal__COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* code_programacion_lineal__COMMON_INCLUDES_ */

#include "code_programacion_lineal__types.h"
#include "rt_nonfinite.h"

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
  real_T qpOASES_linprog_o1[2];        /* '<S2>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o2;           /* '<S2>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o3;           /* '<S2>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o4;           /* '<S2>/qpOASES_(linprog)' */
  real_T qpOASES_linprog1_o1[2];       /* '<S2>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o2;          /* '<S2>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o3;          /* '<S2>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o4;          /* '<S2>/qpOASES_(linprog)1' */
  real_T H[4];                         /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T f[2];                         /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T A[2];                         /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T lb[2];                        /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T ub[2];                        /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T lbA;                          /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T ubA;                          /* '<S2>/LinProg_BuildMatrices_Reactive_Power' */
  real_T H_e[4];                       /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T f_c[2];                       /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T A_c[2];                       /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T lb_i[2];                      /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T ub_n[2];                      /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T lbA_b;                        /* '<S2>/LinProg_BuildMatrices_ActivePower' */
  real_T ubA_o;                        /* '<S2>/LinProg_BuildMatrices_ActivePower' */
} B_code_programacion_lineal__T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *qpOASES_linprog_PWORK[8];      /* '<S2>/qpOASES_(linprog)' */
  void *qpOASES_linprog1_PWORK[8];     /* '<S2>/qpOASES_(linprog)1' */
} DW_code_programacion_lineal__T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T P_Load;                       /* '<Root>/P_Load' */
  real_T KP1;                          /* '<Root>/KP1' */
  real_T KP2;                          /* '<Root>/KP2' */
  real_T P1_CSI;                       /* '<Root>/P1_CSI' */
  real_T P2_CSI;                       /* '<Root>/P2_CSI' */
  real_T KQ1;                          /* '<Root>/KQ1' */
  real_T KQ2;                          /* '<Root>/KQ2' */
  real_T Q1_CSI;                       /* '<Root>/Q1_CSI' */
  real_T Q2_CSI;                       /* '<Root>/Q2_CSI' */
  real_T Q_Load;                       /* '<Root>/Q_Load' */
  real_T SOC;                          /* '<Root>/SOC' */
} ExtU_code_programacion_lineal__T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Pbio;                         /* '<Root>/Pbio' */
  real_T Qbio;                         /* '<Root>/Qbio' */
  real_T Pdie;                         /* '<Root>/Pdie' */
  real_T Qdie;                         /* '<Root>/Qdie' */
} ExtY_code_programacion_lineal__T;

/* Real-time Model Data Structure */
struct tag_RTM_code_programacion_lineal__T {
  struct SimStruct_tag * *childSfunctions;
  const char_T * volatile errorStatus;
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
    time_T *taskTimePtrs[1];
    SimStruct childSFunctions[2];
    SimStruct *childSFunctionPtrs[2];
    struct _ssBlkInfo2 blkInfo2[2];
    struct _ssSFcnModelMethods2 methods2[2];
    struct _ssSFcnModelMethods3 methods3[2];
    struct _ssSFcnModelMethods4 methods4[2];
    struct _ssStatesInfo2 statesInfo2[2];
    ssPeriodicStatesInfo periodicStatesInfo[2];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[7];
      real_T const *UPtrs0[4];
      real_T const *UPtrs1[2];
      real_T const *UPtrs2[2];
      real_T const *UPtrs3[2];
      real_T const *UPtrs4[2];
      real_T const *UPtrs5[1];
      real_T const *UPtrs6[1];
      struct _ssPortOutputs outputPortInfo[4];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[7];
      real_T const *UPtrs0[4];
      real_T const *UPtrs1[2];
      real_T const *UPtrs2[2];
      real_T const *UPtrs3[2];
      real_T const *UPtrs4[2];
      real_T const *UPtrs5[1];
      real_T const *UPtrs6[1];
      struct _ssPortOutputs outputPortInfo[4];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn1;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
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
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block signals (auto storage) */
extern B_code_programacion_lineal__T code_programacion_lineal__B;

/* Block states (auto storage) */
extern DW_code_programacion_lineal__T code_programacion_lineal__DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_code_programacion_lineal__T code_programacion_lineal__U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_code_programacion_lineal__T code_programacion_lineal__Y;

/* Model entry point functions */
extern void code_programacion_lineal__initialize(void);
extern void code_programacion_lineal__step(void);
extern void code_programacion_lineal__terminate(void);

/* Real-time Model object */
extern RT_MODEL_code_programacion_lineal__T *const code_programacion_lineal__M;

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
 * '<Root>' : 'code_programacion_lineal_'
 * '<S1>'   : 'code_programacion_lineal_/MATLAB Function'
 * '<S2>'   : 'code_programacion_lineal_/Optimizador  - Control de tercer nivel'
 * '<S3>'   : 'code_programacion_lineal_/Optimizador  - Control de tercer nivel/LinProg_BuildMatrices_ActivePower'
 * '<S4>'   : 'code_programacion_lineal_/Optimizador  - Control de tercer nivel/LinProg_BuildMatrices_Reactive_Power'
 */
#endif                                 /* RTW_HEADER_code_programacion_lineal__h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
