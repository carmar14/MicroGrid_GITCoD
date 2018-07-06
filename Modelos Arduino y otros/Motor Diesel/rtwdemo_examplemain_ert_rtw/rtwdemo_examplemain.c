/*
 * File: rtwdemo_examplemain.c
 *
 * Code generated for Simulink model 'rtwdemo_examplemain'.
 *
 * Model version                  : 1.138
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Jan 22 10:51:49 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtwdemo_examplemain.h"
#include "rtwdemo_examplemain_private.h"

/* Block signals (auto storage) */
BlockIO rtB;

/* Block states (auto storage) */
D_Work rtDWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function for TID0 */
void rtwdemo_examplemain_step0(void)   /* Sample time: [1.0s, 0.0s] */
{
  /* Update the flag to indicate when data transfers from
   *  Sample time: [1.0s, 0.0s] to Sample time: [2.0s, 0.0s]  */
  (rtM->Timing.RateInteraction.TID0_1)++;
  if ((rtM->Timing.RateInteraction.TID0_1) > 1) {
    rtM->Timing.RateInteraction.TID0_1 = 0;
  }

  /* RateTransition: '<Root>/RateTransition' */
  if (rtM->Timing.RateInteraction.TID0_1 == 1) {
    rtB.RateTransition = rtDWork.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<Root>/RateTransition' */

  /* Outputs for Atomic SubSystem: '<Root>/SS2' */
  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<S2>/Gain'
   *  Inport: '<Root>/In1_1s'
   */
  rtY.Out2 = 2.0 * rtB.RateTransition + rtU.In1_1s;

  /* End of Outputs for SubSystem: '<Root>/SS2' */

  /* Outputs for Atomic SubSystem: '<Root>/SS1' */
  /* Outport: '<Root>/Out1' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Inport: '<Root>/In1_1s'
   *  Sum: '<Root>/Sum'
   *  Sum: '<S1>/Sum'
   */
  rtY.Out1 = (3.0 * rtB.RateTransition + rtU.In1_1s) * 5.0 + rtY.Out2;

  /* End of Outputs for SubSystem: '<Root>/SS1' */
}

/* Model step function for TID1 */
void rtwdemo_examplemain_step1(void)   /* Sample time: [2.0s, 0.0s] */
{
  /* Update for RateTransition: '<Root>/RateTransition' */
  rtDWork.RateTransition_Buffer0 = rtDWork.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<Root>/Integrator' incorporates:
   *  Update for Inport: '<Root>/In2_2s'
   */
  rtDWork.Integrator_DSTATE += 2.0 * rtU.In2_2s;
}

/* Model initialize function */
void rtwdemo_examplemain_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
