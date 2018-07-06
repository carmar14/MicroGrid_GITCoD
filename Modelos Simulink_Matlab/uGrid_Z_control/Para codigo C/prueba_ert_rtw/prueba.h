/*
 * File: prueba.h
 *
 * Code generated for Simulink model 'prueba'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Thu Jul 05 11:00:52 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_prueba_h_
#define RTW_HEADER_prueba_h_
#include <stddef.h>
#include <string.h>
#ifndef prueba_COMMON_INCLUDES_
# define prueba_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                                 /* prueba_COMMON_INCLUDES_ */

#include "prueba_types.h"
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
  real_T dv0[40000];
  int32_T f_data[40000];
  real_T qpOASES_linprog_o1[2];        /* '<S3>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o2;           /* '<S3>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o3;           /* '<S3>/qpOASES_(linprog)' */
  real_T qpOASES_linprog_o4;           /* '<S3>/qpOASES_(linprog)' */
  real_T qpOASES_linprog1_o1[2];       /* '<S3>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o2;          /* '<S3>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o3;          /* '<S3>/qpOASES_(linprog)1' */
  real_T qpOASES_linprog1_o4;          /* '<S3>/qpOASES_(linprog)1' */
  real_T qpOASES_o1[200];              /* '<S2>/qpOASES' */
  real_T qpOASES_o2;                   /* '<S2>/qpOASES' */
  real_T qpOASES_o3;                   /* '<S2>/qpOASES' */
  real_T qpOASES_o4;                   /* '<S2>/qpOASES' */
  real_T H[4];                         /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T f[2];                         /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T A[2];                         /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T lb[2];                        /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T ub[2];                        /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T lbA;                          /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T ubA;                          /* '<S3>/LinProg_BuildMatrices_Reactive_Power' */
  real_T H_l[4];                       /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T f_d[2];                       /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T A_i[2];                       /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T lb_p[2];                      /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T ub_m[2];                      /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T lbA_j;                        /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T ubA_i;                        /* '<S3>/LinProg_BuildMatrices_ActivePower' */
  real_T Hv[40000];                    /* '<S2>/MPC_MatCalc' */
  real_T F[200];                       /* '<S2>/MPC_MatCalc' */
  real_T A_f[40000];                   /* '<S2>/MPC_MatCalc' */
  real_T lb_f[200];                    /* '<S2>/MPC_MatCalc' */
  real_T ub_e[200];                    /* '<S2>/MPC_MatCalc' */
  real_T lbA_l[200];                   /* '<S2>/MPC_MatCalc' */
  real_T ubA_m[200];                   /* '<S2>/MPC_MatCalc' */
} B_prueba_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Memory1_PreviousInput[200];   /* '<S2>/Memory1' */
  real_T Memory2_PreviousInput[2];     /* '<S2>/Memory2' */
  real_T Du[200];                      /* '<S2>/MPC_OutLogic' */
  real_T out[2];                       /* '<S2>/MPC_OutLogic' */
  void *qpOASES_linprog_PWORK[8];      /* '<S3>/qpOASES_(linprog)' */
  void *qpOASES_linprog1_PWORK[8];     /* '<S3>/qpOASES_(linprog)1' */
  void *qpOASES_PWORK[8];              /* '<S2>/qpOASES' */
} DW_prueba_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const real_T Gain1;                  /* '<Root>/Gain1' */
} ConstB_prueba_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: G
   * Referenced by: '<S2>/DynMat'
   */
  real_T DynMat_Value[40000];

  /* Expression: GF
   * Referenced by: '<S2>/DynMat_RespLibre'
   */
  real_T DynMat_RespLibre_Value[40000];
} ConstP_prueba_T;

/* Real-time Model Data Structure */
struct tag_RTM_prueba_T {
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
    time_T *taskTimePtrs[2];
    SimStruct childSFunctions[3];
    SimStruct *childSFunctionPtrs[3];
    struct _ssBlkInfo2 blkInfo2[3];
    struct _ssSFcnModelMethods2 methods2[3];
    struct _ssSFcnModelMethods3 methods3[3];
    struct _ssSFcnModelMethods4 methods4[3];
    struct _ssStatesInfo2 statesInfo2[3];
    ssPeriodicStatesInfo periodicStatesInfo[3];
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
    } Sfcn2;
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
    uint32_T clockTick1;
    time_T stepSize1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

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
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

/* Block signals (auto storage) */
extern B_prueba_T prueba_B;

/* Block states (auto storage) */
extern DW_prueba_T prueba_DW;
extern const ConstB_prueba_T prueba_ConstB;/* constant block i/o */

/* Constant parameters (auto storage) */
extern const ConstP_prueba_T prueba_ConstP;

/* Model entry point functions */
extern void prueba_initialize(void);
extern void prueba_step(void);
extern void prueba_terminate(void);

/* Real-time Model object */
extern RT_MODEL_prueba_T *const prueba_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S2>/rt' : Eliminated since input and output rates are identical
 * Block '<S2>/rt1' : Eliminated since input and output rates are identical
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
 * '<Root>' : 'prueba'
 * '<S1>'   : 'prueba/MATLAB Function'
 * '<S2>'   : 'prueba/MPC_bio'
 * '<S3>'   : 'prueba/Optimizador  - Control de tercer nivel'
 * '<S4>'   : 'prueba/MPC_bio/MPC_MatCalc'
 * '<S5>'   : 'prueba/MPC_bio/MPC_OutLogic'
 * '<S6>'   : 'prueba/Optimizador  - Control de tercer nivel/LinProg_BuildMatrices_ActivePower'
 * '<S7>'   : 'prueba/Optimizador  - Control de tercer nivel/LinProg_BuildMatrices_Reactive_Power'
 */
#endif                                 /* RTW_HEADER_prueba_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
