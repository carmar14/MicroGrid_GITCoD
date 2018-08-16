/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'PV_vsi_sf'.
 *
 * Model version                  : 1.64
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 13:48:18 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "PV_vsi_sf.h"                 /* Model's header file */
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
 double ipv=0.0;
 double vload=0.0;

 //------Salidas--------
 double i3=0.0;
 double soc=0.0;
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(PV_vsi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
    //------Entradas-------
  ipv=500;   //Proveniente de la fuente de generación PV
  vload=123; //Proveniente de la carga
  
  set_Idc_PV(ipv);
  set_Vload(vload);

  /* Step the model for base rate */
  PV_vsi_sf_step();

  /* Get model outputs here */
  
//-------Salidas------
  i3=get_I_pv();
  soc=get_SOC();
  printf("La corriente del inversor 3 es: %3.2f \n",i3);
  printf("El estado de la bateria es: %3.2f \n",soc);

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
  PV_vsi_sf_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(PV_vsi_sf_M) == (NULL)) && !rtmGetStopRequested
         (PV_vsi_sf_M)) {
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  PV_vsi_sf_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
