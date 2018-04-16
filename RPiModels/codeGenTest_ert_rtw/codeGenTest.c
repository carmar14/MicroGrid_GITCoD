/*
 * File: codeGenTest.c
 *
 * Code generated for Simulink model 'codeGenTest'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Sat Apr 14 11:44:11 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "codeGenTest.h"

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Model step function */
void codeGenTest_step(void)
{
  /* DiscreteStateSpace: '<S1>/Discrete State Space' incorporates:
   *  Inport: '<Root>/entrada'
   *  Outport: '<Root>/salida'
   */
  {
    rtY.salida = 0.0009995*rtDW.DiscreteStateSpace_DSTATE;
  }

  /* Update for DiscreteStateSpace: '<S1>/Discrete State Space' incorporates:
   *  Update for Inport: '<Root>/entrada'
   *  Update for Outport: '<Root>/salida'
   */
  {
    rtDW.DiscreteStateSpace_DSTATE = rtU.entrada + 0.999*
      rtDW.DiscreteStateSpace_DSTATE;
  }
}

/* Model initialize function */
void codeGenTest_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
