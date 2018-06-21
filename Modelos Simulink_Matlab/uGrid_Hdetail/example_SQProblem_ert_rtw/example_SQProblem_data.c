/*
 * File: example_SQProblem_data.c
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

#include "example_SQProblem.h"
#include "example_SQProblem_private.h"

/* Constant parameters (auto storage) */
const ConstP_example_SQProblem_T example_SQProblem_ConstP = {
  /* Expression: [1 1]
   * Referenced by: '<Root>/A'
   */
  { 1.0, 1.0 },

  /* Expression: zeros(1, 4)
   * Referenced by: '<Root>/H'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Expression: [1 10]
   * Referenced by: '<Root>/f'
   */
  { 1.0, 10.0 },

  /* Expression: [0 0]
   * Referenced by: '<Root>/lb'
   */
  { 0.0, 0.0 },

  /* Expression: [4000]
   * Referenced by: '<Root>/lbA'
   */
  4000.0,

  /* Expression: [3500 3500]
   * Referenced by: '<Root>/ub'
   */
  { 3500.0, 3500.0 },

  /* Expression: [7000]
   * Referenced by: '<Root>/ubA'
   */
  7000.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
