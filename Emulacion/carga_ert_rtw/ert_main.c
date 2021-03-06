/*
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "carga.h"                     /* Model's header file */
#include "rtwtypes.h"

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
 
//Entradas
double I_die=0.0;
double I_bio=0.0;
double I_pv=0.0;

//Salidas
double V_load=0.0;
double P=0.0;
double Q=0.0;

void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(carga_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
  //Entradas
  I_die=2.0;
  I_bio=1.50;
  I_pv=4.0;
  
  set_I_die(I_die);
  set_I_bio(I_bio);
  set_I_pv(I_pv);

  /* Step the model for base rate */
  carga_step();
  
  V_load=get_V_load();
  P=get_P();
  Q=get_Q();
  

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  carga_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(carga_M) == (NULL)) && !rtmGetStopRequested(carga_M))
  {
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  carga_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
