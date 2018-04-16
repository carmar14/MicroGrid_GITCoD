/*
 * File: codeGenTest.h
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

#ifndef RTW_HEADER_codeGenTest_h_
#define RTW_HEADER_codeGenTest_h_
#ifndef codeGenTest_COMMON_INCLUDES_
# define codeGenTest_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* codeGenTest_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T DiscreteStateSpace_DSTATE;    /* '<S1>/Discrete State Space' */
} DW;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T entrada;                      /* '<Root>/entrada' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T salida;                       /* '<Root>/salida' */
} ExtY;

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void codeGenTest_initialize(void);
extern void codeGenTest_step(void);

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
 * '<Root>' : 'codeGenTest'
 * '<S1>'   : 'codeGenTest/Discrete Transfer Fcn (with initial outputs)'
 */
#endif                                 /* RTW_HEADER_codeGenTest_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
