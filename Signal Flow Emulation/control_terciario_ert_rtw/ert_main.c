/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'control_terciario'.
 *
 * Model version                  : 1.65
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 11:42:57 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "control_terciario.h"         /* Model's header file */
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
 double soc=0.0;
 double Pm=0.0;
 double Qm=0.0;

 //------Salidas--------
 double Pb=0.0;
 double Qb=0.0;
 double Pd=0.0;
 double Qd=0.0;
 
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(control_terciario_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  //-------entradas-------------
  soc=98;
  Pm=1700;
  Qm=3400;
  set_soc(soc);
  set_Pm(Pm);
  set_Qm(Qm);

  /* Step the model for base rate */
  control_terciario_step();

  /* Get model outputs here */
  //-----salidas-------
  Pb=get_Pb();
  Qb=get_Qb();
  Pd=get_Pd();
  Qd=get_Qd();
  printf("La potencia Pb es: %3.2f \n",Pb);
  printf("La potencia Pd es: %3.2f \n",Qb);
  printf("La potencia Qb es: %3.2f \n",Pd);
  printf("La potencia Qd es: %3.2f \n",Qd);

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
  control_terciario_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.0001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(control_terciario_M) == (NULL)) {
    /*  Perform other application tasks here */
    rt_OneStep();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  control_terciario_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
