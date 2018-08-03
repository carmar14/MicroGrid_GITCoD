/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'BIO_csi'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 31 11:51:47 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "BIO_csi.h"                   /* Model's header file */
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
 double V_bio=0.0;
 double P_bio=0.0;
 double Q_bio=0.0;
 
 //Salidas
 double I_bio=0.0;
 
 //Variables de prueba
 double r=0.0;
 double i=0.0;
 double g=0.0;
 
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(BIO_csi_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  
  //Leyendo las entradas
  V_bio=123;
  i=i+0.01;
  P_bio=500;
  Q_bio=2340;
  
  set_V_bio(V_bio);
  set_P_bio(P_bio);
  set_Q_bio(Q_bio);
  
  I_bio=BIO_csi_step();
  
  //g=get_V_bio();
  //r=r+i;
  printf("La corriente del biomasa es: %3.2f \n",I_bio);

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
  BIO_csi_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(BIO_csi_M) == (NULL)) && !rtmGetStopRequested
         (BIO_csi_M)) {
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  BIO_csi_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
