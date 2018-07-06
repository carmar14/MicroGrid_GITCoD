/*
 * File: genCmotorDiesel.c
 *
 * Code generated for Simulink model 'genCmotorDiesel'.
 *
 * Model version                  : 1.140
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jan 23 10:42:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "genCmotorDiesel.h"
#include "genCmotorDiesel_private.h"

/* Block states (auto storage) */
DW_genCmotorDiesel_T genCmotorDiesel_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_genCmotorDiesel_T genCmotorDiesel_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_genCmotorDiesel_T genCmotorDiesel_Y;

/* Real-time model */
RT_MODEL_genCmotorDiesel_T genCmotorDiesel_M_;
RT_MODEL_genCmotorDiesel_T *const genCmotorDiesel_M = &genCmotorDiesel_M_;

/* Model step function */
void genCmotorDiesel_step(void)
{
  /* local block i/o variables */
  real_T rtb_Generador1;
  real_T rtb_Velocidad;
  real_T denAccum;
  real_T denAccum_0;
  int_T idxDelay;

  /* DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' incorporates:
   *  Delay: '<Root>/Delay Tm=0.01'
   */
  denAccum = genCmotorDiesel_DW.DelayTm001_DSTATE[0] - -0.9231 *
    genCmotorDiesel_DW.ActuadorMotorTm001s_states;
  rtb_Velocidad = 0.04423 * denAccum + 0.04423 *
    genCmotorDiesel_DW.ActuadorMotorTm001s_states;

  /* DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' incorporates:
   *  Inport: '<Root>/Par de Carga'
   *  Sum: '<Root>/Sum2'
   */
  denAccum_0 = (rtb_Velocidad - genCmotorDiesel_U.PardeCarga) - -0.9997 *
    genCmotorDiesel_DW.EjeTm001s_states;
  rtb_Velocidad = 0.00015 * denAccum_0 + 0.00015 *
    genCmotorDiesel_DW.EjeTm001s_states;

  /* Gain: '<Root>/ Generador1' */
  rtb_Generador1 = 0.5 * rtb_Velocidad;

  /* Outport: '<Root>/Out1' */
  genCmotorDiesel_Y.Out1 = rtb_Generador1;

  /* Update for Delay: '<Root>/Delay Tm=0.01' incorporates:
   *  Update for Inport: '<Root>/Actuador'
   */
  for (idxDelay = 0; idxDelay < 49; idxDelay++) {
    genCmotorDiesel_DW.DelayTm001_DSTATE[idxDelay] =
      genCmotorDiesel_DW.DelayTm001_DSTATE[idxDelay + 1];
  }

  genCmotorDiesel_DW.DelayTm001_DSTATE[49] = genCmotorDiesel_U.Actuador;

  /* End of Update for Delay: '<Root>/Delay Tm=0.01' */

  /* Update for DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' incorporates:
   *  DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s'
   */
  genCmotorDiesel_DW.ActuadorMotorTm001s_states = denAccum;

  /* Update for DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' incorporates:
   *  DiscreteTransferFcn: '<Root>/Eje Tm=0.01s'
   */
  genCmotorDiesel_DW.EjeTm001s_states = denAccum_0;

  /* Matfile logging */
  rt_UpdateTXYLogVars(genCmotorDiesel_M->rtwLogInfo,
                      (&genCmotorDiesel_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(genCmotorDiesel_M)!=-1) &&
        !((rtmGetTFinal(genCmotorDiesel_M)-genCmotorDiesel_M->Timing.taskTime0) >
          genCmotorDiesel_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(genCmotorDiesel_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  genCmotorDiesel_M->Timing.taskTime0 =
    (++genCmotorDiesel_M->Timing.clockTick0) *
    genCmotorDiesel_M->Timing.stepSize0;
}

/* Model initialize function */
void genCmotorDiesel_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)genCmotorDiesel_M, 0,
                sizeof(RT_MODEL_genCmotorDiesel_T));
  rtmSetTFinal(genCmotorDiesel_M, 1000.0);
  genCmotorDiesel_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    genCmotorDiesel_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(genCmotorDiesel_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(genCmotorDiesel_M->rtwLogInfo, (NULL));
    rtliSetLogT(genCmotorDiesel_M->rtwLogInfo, "");
    rtliSetLogX(genCmotorDiesel_M->rtwLogInfo, "");
    rtliSetLogXFinal(genCmotorDiesel_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(genCmotorDiesel_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(genCmotorDiesel_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(genCmotorDiesel_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(genCmotorDiesel_M->rtwLogInfo, 1);
    rtliSetLogY(genCmotorDiesel_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(genCmotorDiesel_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(genCmotorDiesel_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&genCmotorDiesel_DW, 0,
                sizeof(DW_genCmotorDiesel_T));

  /* external inputs */
  (void)memset((void *)&genCmotorDiesel_U, 0, sizeof(ExtU_genCmotorDiesel_T));

  /* external outputs */
  genCmotorDiesel_Y.Out1 = 0.0;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(genCmotorDiesel_M->rtwLogInfo, 0.0,
    rtmGetTFinal(genCmotorDiesel_M), genCmotorDiesel_M->Timing.stepSize0,
    (&rtmGetErrorStatus(genCmotorDiesel_M)));
}

/* Model terminate function */
void genCmotorDiesel_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
