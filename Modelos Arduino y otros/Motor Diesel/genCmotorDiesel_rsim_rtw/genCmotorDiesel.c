/*
 * genCmotorDiesel.c
 *
 * Code generation for model "genCmotorDiesel".
 *
 * Model version              : 1.141
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Mon Jan 22 09:54:00 2018
 *
 * Target selection: rsim.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <math.h>
#include "genCmotorDiesel.h"
#include "genCmotorDiesel_private.h"
#include "genCmotorDiesel_dt.h"

/* user code (top of parameter file) */
const int_T gblNumToFiles = 0;
const int_T gblNumFrFiles = 0;
const int_T gblNumFrWksBlocks = 0;
const char *gblSlvrJacPatternFileName =
  "genCmotorDiesel_rsim_rtw\\genCmotorDiesel_Jpattern.mat";

/* Root inports information  */
const int_T gblNumRootInportBlks = 0;
const int_T gblNumModelInputs = 0;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
const int_T gblInportDataTypeIdx[] = { -1 };

const int_T gblInportDims[] = { -1 } ;

const int_T gblInportComplex[] = { -1 };

const int_T gblInportInterpoFlag[] = { -1 };

const int_T gblInportContinuous[] = { -1 };

#include "simstruc.h"
#include "fixedpoint.h"

/* Block signals (auto storage) */
B rtB;

/* Block states (auto storage) */
DW rtDW;

/* Parent Simstruct */
static SimStruct model_S;
SimStruct *const rtS = &model_S;

/* System initialize for root system: '<Root>' */
void MdlInitialize(void)
{
  /* InitializeConditions for Delay: '<Root>/Delay Tm=0.01' */
  memset(&rtDW.DelayTm001_DSTATE[0], 0, 50U * sizeof(real_T));

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' */
  rtDW.ActuadorMotorTm001s_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' */
  rtDW.EjeTm001s_states = 0.0;
}

/* Start for root system: '<Root>' */
void MdlStart(void)
{
  MdlInitialize();
}

/* Outputs for root system: '<Root>' */
void MdlOutputs(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Pardecarga1;
  real_T currentTime;
  if (ssIsSampleHit(rtS, 1, 0)) {
    /* DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' incorporates:
     *  Delay: '<Root>/Delay Tm=0.01'
     */
    rtDW.ActuadorMotorTm001s_tmp = rtDW.DelayTm001_DSTATE[0] - -0.9231 *
      rtDW.ActuadorMotorTm001s_states;
    rtB.ActuadorMotorTm001s = 0.04423 * rtDW.ActuadorMotorTm001s_tmp + 0.04423 *
      rtDW.ActuadorMotorTm001s_states;
  }

  if (ssIsSampleHit(rtS, 0, 0)) {
    /* Step: '<Root>/Acción Actuador1' */
    currentTime = ssGetTaskTime(rtS,0);
    rtDW.AccinActuador1_MODE = (currentTime >= 0.0);
    rtB.AccinActuador1 = (rtDW.AccinActuador1_MODE == 1);

    /* Step: '<Root>/Par de carga1' */
    currentTime = ssGetTaskTime(rtS,0);
    rtDW.Pardecarga1_MODE = (currentTime >= 300.0);
    if (rtDW.Pardecarga1_MODE == 1) {
      rtb_Pardecarga1 = 1.0;
    } else {
      rtb_Pardecarga1 = 0.1;
    }

    /* End of Step: '<Root>/Par de carga1' */

    /* Sum: '<Root>/Sum2' */
    rtB.Sum2 = rtB.ActuadorMotorTm001s - rtb_Pardecarga1;
  }

  if (ssIsSampleHit(rtS, 1, 0)) {
    /* DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' */
    rtDW.EjeTm001s_tmp = rtB.Sum2 - -0.9997 * rtDW.EjeTm001s_states;
    rtB.Velocidad = 0.00015 * rtDW.EjeTm001s_tmp + 0.00015 *
      rtDW.EjeTm001s_states;

    /* Gain: '<Root>/ Generador1' */
    rtB.Generador1 = 0.5 * rtB.Velocidad;
  }

  if (ssIsSampleHit(rtS, 0, 0)) {
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
void MdlUpdate(int_T tid)
{
  int32_T idxDelay;
  if (ssIsSampleHit(rtS, 1, 0)) {
    /* Update for Delay: '<Root>/Delay Tm=0.01' */
    for (idxDelay = 0; idxDelay < 49; idxDelay++) {
      rtDW.DelayTm001_DSTATE[(uint32_T)idxDelay] =
        rtDW.DelayTm001_DSTATE[idxDelay + 1U];
    }

    rtDW.DelayTm001_DSTATE[49] = rtB.AccinActuador1;

    /* End of Update for Delay: '<Root>/Delay Tm=0.01' */

    /* Update for DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' */
    rtDW.ActuadorMotorTm001s_states = rtDW.ActuadorMotorTm001s_tmp;

    /* Update for DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' */
    rtDW.EjeTm001s_states = rtDW.EjeTm001s_tmp;
  }

  UNUSED_PARAMETER(tid);
}

/* ZeroCrossings for root system: '<Root>' */
void MdlZeroCrossings(void)
{
  /* ZeroCrossings for Step: '<Root>/Acción Actuador1' */
  ((ZCV *) ssGetSolverZcSignalVector(rtS))->AccinActuador1_StepTime_ZC = ssGetT
    (rtS);

  /* ZeroCrossings for Step: '<Root>/Par de carga1' */
  ((ZCV *) ssGetSolverZcSignalVector(rtS))->Pardecarga1_StepTime_ZC = ssGetT(rtS)
    - 300.0;
}

/* Termination for root system: '<Root>' */
void MdlTerminate(void)
{
}

/* Function to initialize sizes */
void MdlInitializeSizes(void)
{
  ssSetNumContStates(rtS, 0);          /* Number of continuous states */
  ssSetNumY(rtS, 0);                   /* Number of model outputs */
  ssSetNumU(rtS, 0);                   /* Number of model inputs */
  ssSetDirectFeedThrough(rtS, 0);      /* The model is not direct feedthrough */
  ssSetNumSampleTimes(rtS, 2);         /* Number of sample times */
  ssSetNumBlocks(rtS, 8);              /* Number of blocks */
  ssSetNumBlockIO(rtS, 6);             /* Number of block outputs */
}

/* Function to initialize sample times. */
void MdlInitializeSampleTimes(void)
{
  /* task periods */
  ssSetSampleTime(rtS, 0, 0.0);
  ssSetSampleTime(rtS, 1, 0.01);

  /* task offsets */
  ssSetOffsetTime(rtS, 0, 1.0);
  ssSetOffsetTime(rtS, 1, 0.0);
}

/* Function to register the model */
SimStruct * genCmotorDiesel(void)
{
  static struct _ssMdlInfo mdlInfo;
  (void) memset((char *)rtS, 0,
                sizeof(SimStruct));
  (void) memset((char *)&mdlInfo, 0,
                sizeof(struct _ssMdlInfo));
  ssSetMdlInfoPtr(rtS, &mdlInfo);

  /* timing info */
  {
    static time_T mdlPeriod[NSAMPLE_TIMES];
    static time_T mdlOffset[NSAMPLE_TIMES];
    static time_T mdlTaskTimes[NSAMPLE_TIMES];
    static int_T mdlTsMap[NSAMPLE_TIMES];
    static int_T mdlSampleHits[NSAMPLE_TIMES];
    static boolean_T mdlTNextWasAdjustedPtr[NSAMPLE_TIMES];
    static int_T mdlPerTaskSampleHits[NSAMPLE_TIMES * NSAMPLE_TIMES];
    static time_T mdlTimeOfNextSampleHit[NSAMPLE_TIMES];

    {
      int_T i;
      for (i = 0; i < NSAMPLE_TIMES; i++) {
        mdlPeriod[i] = 0.0;
        mdlOffset[i] = 0.0;
        mdlTaskTimes[i] = 0.0;
        mdlTsMap[i] = i;
        mdlSampleHits[i] = 1;
      }
    }

    ssSetSampleTimePtr(rtS, &mdlPeriod[0]);
    ssSetOffsetTimePtr(rtS, &mdlOffset[0]);
    ssSetSampleTimeTaskIDPtr(rtS, &mdlTsMap[0]);
    ssSetTPtr(rtS, &mdlTaskTimes[0]);
    ssSetSampleHitPtr(rtS, &mdlSampleHits[0]);
    ssSetTNextWasAdjustedPtr(rtS, &mdlTNextWasAdjustedPtr[0]);
    ssSetPerTaskSampleHitsPtr(rtS, &mdlPerTaskSampleHits[0]);
    ssSetTimeOfNextSampleHitPtr(rtS, &mdlTimeOfNextSampleHit[0]);
  }

  ssSetSolverMode(rtS, SOLVER_MODE_SINGLETASKING);

  /*
   * initialize model vectors and cache them in SimStruct
   */

  /* block I/O */
  {
    ssSetBlockIO(rtS, ((void *) &rtB));
    (void) memset(((void *) &rtB), 0,
                  sizeof(B));
  }

  /* states (dwork) */
  {
    void *dwork = (void *) &rtDW;
    ssSetRootDWork(rtS, dwork);
    (void) memset(dwork, 0,
                  sizeof(DW));
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ssSetModelMappingInfo(rtS, &dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;
  }

  /* Model specific registration */
  ssSetRootSS(rtS, rtS);
  ssSetVersion(rtS, SIMSTRUCT_VERSION_LEVEL2);
  ssSetModelName(rtS, "genCmotorDiesel");
  ssSetPath(rtS, "genCmotorDiesel");
  ssSetTStart(rtS, 0.0);
  ssSetTFinal(rtS, 1000.0);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    ssSetRTWLogInfo(rtS, &rt_DataLoggingInfo);
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogXSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogT(ssGetRTWLogInfo(rtS), "");
    rtliSetLogX(ssGetRTWLogInfo(rtS), "");
    rtliSetLogXFinal(ssGetRTWLogInfo(rtS), "");
    rtliSetLogVarNameModifier(ssGetRTWLogInfo(rtS), "rt_");
    rtliSetLogFormat(ssGetRTWLogInfo(rtS), 0);
    rtliSetLogMaxRows(ssGetRTWLogInfo(rtS), 1000);
    rtliSetLogDecimation(ssGetRTWLogInfo(rtS), 1);
    rtliSetLogY(ssGetRTWLogInfo(rtS), "");
    rtliSetLogYSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogYSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
  }

  {
    static ssSolverInfo slvrInfo;
    static uint8_T zcAttributes[2] = { (ZC_EVENT_ALL_UP), (ZC_EVENT_ALL_UP) };

    ssSetStepSize(rtS, 0.01);
    ssSetMinStepSize(rtS, 0.0);
    ssSetMaxNumMinSteps(rtS, -1);
    ssSetMinStepViolatedError(rtS, 0);
    ssSetMaxStepSize(rtS, 0.01);
    ssSetSolverMaxOrder(rtS, -1);
    ssSetSolverRefineFactor(rtS, 1);
    ssSetOutputTimes(rtS, (NULL));
    ssSetNumOutputTimes(rtS, 0);
    ssSetOutputTimesOnly(rtS, 0);
    ssSetOutputTimesIndex(rtS, 0);
    ssSetZCCacheNeedsReset(rtS, 0);
    ssSetDerivCacheNeedsReset(rtS, 0);
    ssSetNumNonContDerivSigInfos(rtS, 0);
    ssSetNonContDerivSigInfos(rtS, (NULL));
    ssSetSolverInfo(rtS, &slvrInfo);
    ssSetSolverName(rtS, "VariableStepDiscrete");
    ssSetVariableStepSolver(rtS, 1);
    ssSetSolverConsistencyChecking(rtS, 0);
    ssSetSolverAdaptiveZcDetection(rtS, 0);
    ssSetSolverRobustResetMethod(rtS, 0);
    ssSetSolverStateProjection(rtS, 0);
    ssSetSolverMassMatrixType(rtS, (ssMatrixType)0);
    ssSetSolverMassMatrixNzMax(rtS, 0);
    ssSetModelOutputs(rtS, MdlOutputs);
    ssSetModelLogData(rtS, rt_UpdateTXYLogVars);
    ssSetModelLogDataIfInInterval(rtS, rt_UpdateTXXFYLogVars);
    ssSetModelUpdate(rtS, MdlUpdate);
    ssSetSolverZcSignalAttrib(rtS, zcAttributes);
    ssSetSolverNumZcSignals(rtS, 2);
    ssSetModelZeroCrossings(rtS, MdlZeroCrossings);
    ssSetSolverConsecutiveZCsStepRelTol(rtS, 2.8421709430404007E-13);
    ssSetSolverMaxConsecutiveZCs(rtS, 1000);
    ssSetSolverConsecutiveZCsError(rtS, 2);
    ssSetSolverMaskedZcDiagnostic(rtS, 1);
    ssSetSolverIgnoredZcDiagnostic(rtS, 1);
    ssSetTNextTid(rtS, INT_MIN);
    ssSetTNext(rtS, rtMinusInf);
    ssSetSolverNeedsReset(rtS);
    ssSetNumNonsampledZCs(rtS, 2);
  }

  ssSetChecksumVal(rtS, 0, 2137253190U);
  ssSetChecksumVal(rtS, 1, 2687928775U);
  ssSetChecksumVal(rtS, 2, 1213103890U);
  ssSetChecksumVal(rtS, 3, 3377271405U);
  return rtS;
}
