/*
 * File: example_SQProblem.h
 *
 * Code generated for Simulink model 'example_SQProblem'.
 *
 * Model version                  : 1.74
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Jun 18 17:38:23 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_example_SQProblem_h_
#define RTW_HEADER_example_SQProblem_h_
#include <stddef.h>
#include <string.h>
#ifndef example_SQProblem_COMMON_INCLUDES_
# define example_SQProblem_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* example_SQProblem_COMMON_INCLUDES_ */

#include "example_SQProblem_types.h"
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
  real_T qpOASES_o1[2];                /* '<Root>/qpOASES' */
  real_T qpOASES_o2;                   /* '<Root>/qpOASES' */
  real_T qpOASES_o3;                   /* '<Root>/qpOASES' */
  real_T qpOASES_o4;                   /* '<Root>/qpOASES' */
} B_example_SQProblem_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *qpOASES_PWORK[8];              /* '<Root>/qpOASES' */
} DW_example_SQProblem_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: [1 1]
   * Referenced by: '<Root>/A'
   */
  real_T A_Value[2];

  /* Expression: zeros(1, 4)
   * Referenced by: '<Root>/H'
   */
  real_T H_Value[4];

  /* Expression: [1 10]
   * Referenced by: '<Root>/f'
   */
  real_T f_Value[2];

  /* Expression: [0 0]
   * Referenced by: '<Root>/lb'
   */
  real_T lb_Value[2];

  /* Expression: [4000]
   * Referenced by: '<Root>/lbA'
   */
  real_T lbA_Value;

  /* Expression: [3500 3500]
   * Referenced by: '<Root>/ub'
   */
  real_T ub_Value[2];

  /* Expression: [7000]
   * Referenced by: '<Root>/ubA'
   */
  real_T ubA_Value;
} ConstP_example_SQProblem_T;

/* Real-time Model Data Structure */
struct tag_RTM_example_SQProblem_T {
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
extern B_example_SQProblem_T example_SQProblem_B;

/* Block states (auto storage) */
extern DW_example_SQProblem_T example_SQProblem_DW;

/* Constant parameters (auto storage) */
extern const ConstP_example_SQProblem_T example_SQProblem_ConstP;

/* Model entry point functions */
extern void example_SQProblem_initialize(void);
extern void example_SQProblem_step(void);
extern void example_SQProblem_terminate(void);

/* Real-time Model object */
extern RT_MODEL_example_SQProblem_T *const example_SQProblem_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/x, fval, exitflag, iter' : Unused code path elimination
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
 * '<Root>' : 'example_SQProblem'
 */
#endif                                 /* RTW_HEADER_example_SQProblem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
