/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Diesel_csi_sf'.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 11:30:36 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Diesel_csi_sf.h"             /* Model's header file */
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
 //Variables creadas por el programador
 //------Entradas-------
 double Pref_d=0.0;
 double Qref_d=0.0;
 double Vload=0.0;
 double par=0.0;
 double flujo=0.0;

 //------Salidas--------
 double Idie=0.0;
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(Diesel_csi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  //-------entradas-------------
  Pref_d=300;
  Qref_d=1200;
  Vload=124;
  par=1.4;
  flujo=4;
  
  set_Pref_d(Pref_d);
  set_Qref_d(Qref_d);
  set_Vload(Vload);
  set_par(par);
  set_flujo(flujo);

  /* Step the model for base rate */
  Diesel_csi_sf_step();

  /* Get model outputs here */
  //-----salidas-------
  Idie=get_I_die();
  printf("La corriente del inversor 3 es: %3.2f \n",Idie);

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
  Diesel_csi_sf_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(Diesel_csi_sf_M) == (NULL)) && !rtmGetStopRequested
         (Diesel_csi_sf_M)) {
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Diesel_csi_sf_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
