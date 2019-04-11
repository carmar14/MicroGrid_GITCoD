/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'carga_sf'.
 *
 * Model version                  : 1.66
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 11:49:54 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "carga_sf.h"                  /* Model's header file */
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
 double i1=0.0;
 double i2=0.0;
 double i3=0.0;

 //------Salidas--------
 double Pm=0.0;
 double Qm=0.0;
 double Vload=0.0;
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(carga_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
  //------- entradas-------------
  i1=34;
  i2=62;
  i3=24;
  
  set_i1(i1);
  set_i2(i2);
  set_i3(i3);
  
  /* Step the model for base rate */
  carga_sf_step();

  /* Get model outputs here */
  //----- salidas-------
  Pm=get_Pm();
  Qm=get_Qm();
  Vload=get_Vload();
  printf("La potencia P medida es: %3.2f \n",Pm);
  printf("La potencia Q medida es: %3.2f \n",Qm);
  printf("La tension medida es: %3.2f \n",Vload);

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
  carga_sf_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(carga_sf_M) == (NULL)) && !rtmGetStopRequested
         (carga_sf_M)) {
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  carga_sf_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
