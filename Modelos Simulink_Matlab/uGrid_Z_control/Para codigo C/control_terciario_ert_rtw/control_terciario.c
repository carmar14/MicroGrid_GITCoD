/*
 * File: control_terciario.c
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

#include "control_terciario.h"
#include "control_terciario_private.h"

/* External inputs (root inport signals with auto storage) */
ExtU_control_terciario_T control_terciario_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_control_terciario_T control_terciario_Y;

/* Real-time model */
RT_MODEL_control_terciario_T control_terciario_M_;
RT_MODEL_control_terciario_T *const control_terciario_M = &control_terciario_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (control_terciario_M->Timing.TaskCounters.TID[1])++;
  if ((control_terciario_M->Timing.TaskCounters.TID[1]) > 299) {/* Sample time: [0.03s, 0.0s] */
    control_terciario_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void control_terciario_step(void)
{
  real_T Pb;
  real_T Pd;
  int32_T flagDelt;
  real_T rtb_MaxQ;
  real_T rtb_MaxP;
  if (control_terciario_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
     *  Inport: '<Root>/soc'
     */
    /*   funcion que calcula la potencia maxima que puede suministrar las fuentes */
    /*   renovables deacuerdo a la cantidad de carga que hay almancenada en la */
    /*   bateria. esta va de 0 a 100% */
    /* MATLAB Function 'MATLAB Function1': '<S3>:1' */
    /*  estoc valores que aparecen a continuacion se pusieron de manera */
    /*  arbitraria. corresponde a una persona con especialidad en la parte de */
    /*  potencia electrica determinar el verdadero algoritmo para hallar la */
    /*  potencia que deberia suministrar el nodo de energia renovable deacuerdo a */
    /*  la carga de la bateria. */
    /* '<S3>:1:15' MaxP = 0; */
    rtb_MaxP = 0.0;

    /* '<S3>:1:16' MaxQ = 0; */
    rtb_MaxQ = 0.0;

    /* '<S3>:1:18' if( SOC >= 90 ) */
    if (control_terciario_U.soc >= 90.0) {
      /* '<S3>:1:19' MaxP = 500; */
      rtb_MaxP = 500.0;

      /* '<S3>:1:20' MaxQ = 5000; */
      rtb_MaxQ = 5000.0;
    }

    /* '<S3>:1:23' if( SOC <= 90 ) */
    if (control_terciario_U.soc <= 90.0) {
      /* '<S3>:1:24' MaxP = 200; */
      rtb_MaxP = 200.0;

      /* '<S3>:1:25' MaxQ = 4000; */
      rtb_MaxQ = 4000.0;
    }

    /* '<S3>:1:28' if( SOC <= 70 ) */
    if (control_terciario_U.soc <= 70.0) {
      /* '<S3>:1:29' MaxP = 100; */
      rtb_MaxP = 100.0;

      /* '<S3>:1:30' MaxQ = 1000; */
      rtb_MaxQ = 1000.0;
    }

    /* '<S3>:1:33' if( SOC <= 60 ) */
    if (control_terciario_U.soc <= 60.0) {
      /* '<S3>:1:34' MaxP = 50; */
      rtb_MaxP = 50.0;

      /* '<S3>:1:35' MaxQ = 500; */
      rtb_MaxQ = 500.0;
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function1' */

    /* MATLAB Function: '<Root>/LinearProg Potencia Activa' incorporates:
     *  Constant: '<Root>/Pbmax'
     *  Constant: '<Root>/Pdmax'
     *  Inport: '<Root>/Pm'
     */
    /* , P_e_alt_min) */
    /* MATLAB Function 'LinearProg Potencia Activa': '<S1>:1' */
    /*  P_load es la potencia que se requiere en la carga. */
    /*  P_e_alt es la potencia estimada de generacion de las energias */
    /*  alternativas */
    /*  kb y kd son los pesos de las funcion de costo. */
    /*  las salidas son las potencias optimas para bio y diesel */
    /* '<S1>:1:12' Pb=0; */
    Pb = 0.0;

    /* '<S1>:1:13' Pd=0; */
    Pd = 0.0;

    /* - P_e_alt_min % superaavit de energia alternativa. */
    /* '<S1>:1:15' D_P_e_alt = P_e_alt %- P_e_alt_min % superaavit de energia alternativa. */
    /* '<S1>:1:17' flagDelt = 0; */
    flagDelt = 0;

    /* '<S1>:1:19' if(D_P_e_alt >= P_load) */
    if (rtb_MaxP >= control_terciario_U.Pm) {
      /* '<S1>:1:20' flagDelt = 1; */
      flagDelt = 1;
    }

    /* '<S1>:1:24' if(flagDelt==0) */
    if (flagDelt == 0) {
      /* '<S1>:1:25' P_trad = P_load - D_P_e_alt; */
      rtb_MaxP = control_terciario_U.Pm - rtb_MaxP;

      /*  flag: variable que indica si tiene sentido evaluar los */
      /*  if's que se encuentran mas adelante. es decir, si flag = 0  */
      /*  despues del primer if entonces NO se le esta pidiendo al sistema */
      /*  mas potencia de la que puede generar y portante el problema de  */
      /*  optimizacion lineal tiene sentido. */
      /*  entonces  */
      /* '<S1>:1:32' flag=0; */
      /* '<S1>:1:34' if(P_trad>PdMax+PbMax) */
      if (rtb_MaxP > 1000.0) {
        /* '<S1>:1:35' Pd=PdMax; */
        Pd = 500.0;

        /* '<S1>:1:36' Pb=PbMax; */
        Pb = 500.0;

        /* '<S1>:1:37' flag=1; */
        flagDelt = 1;
      }

      /*  si ambas energias tienen el mismo factor de costo. */
      /* '<S1>:1:41' if(kd==kb && flag==0) */
      if (flagDelt == 0) {
        /* '<S1>:1:42' Pb=P_trad/2; */
        Pb = rtb_MaxP / 2.0;

        /* '<S1>:1:43' Pd=P_trad/2; */
        Pd = rtb_MaxP / 2.0;
      }

      /*  si la energia diesel es mas cara que la biomasa. */
      /* '<S1>:1:47' if(kd>kb && flag==0) */
      /*  si la biomasa es mas cara que la diesel. */
      /* '<S1>:1:58' if(kd<kb && flag==0) */
    }

    /* Outport: '<Root>/Pb' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potencia Activa'
     */
    /* '<S1>:1:69' Pbo=Pb; */
    /* '<S1>:1:70' Pdo=Pd; */
    control_terciario_Y.Pb = Pb;

    /* Outport: '<Root>/Pd' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potencia Activa'
     */
    control_terciario_Y.Pd = Pd;

    /* MATLAB Function: '<Root>/LinearProg Potenica Reactiva' incorporates:
     *  Constant: '<Root>/Pbmax1'
     *  Constant: '<Root>/Pdmax1'
     *  Gain: '<Root>/Gain17'
     *  Inport: '<Root>/Qm'
     */
    /*  Q_load es la potencia que se requiere en la carga. */
    /* MATLAB Function 'LinearProg Potenica Reactiva': '<S2>:1' */
    /*  Q_e_alt es la potencia estimada de generacion de las energias */
    /*  alternativas */
    /*  kb y kd son los pesos de las funcion de costo. */
    /*  las salidas son las potencias optimas para bio y diesel */
    /* '<S2>:1:12' Qb=0; */
    Pb = 0.0;

    /* '<S2>:1:13' Qd=0; */
    Pd = 0.0;

    /* '<S2>:1:15' D_P_e_alt = Q_e_alt ; */
    /* - Q_e_alt_min % superaavit de energia alternativa. */
    /* '<S2>:1:17' flagDelt = 0; */
    flagDelt = 0;

    /* '<S2>:1:19' if(D_P_e_alt >= Q_load) */
    if (rtb_MaxQ >= -control_terciario_U.Qm) {
      /* '<S2>:1:20' flagDelt = 1; */
      flagDelt = 1;
    }

    /* '<S2>:1:24' if(flagDelt==0) */
    if (flagDelt == 0) {
      /* '<S2>:1:25' Q_trad = Q_load - D_P_e_alt; */
      rtb_MaxQ = -control_terciario_U.Qm - rtb_MaxQ;

      /*  flag: variable que indica si tiene sentido evaluar los */
      /*  if's que se encuentran mas adelante. es decir, si flag = 0  */
      /*  despues del primer if entonces NO se le esta pidiendo al sistema */
      /*  mas potencia de la que puede generar y portante el problema de  */
      /*  optimizacion lineal tiene sentido. */
      /*  entonces  */
      /* '<S2>:1:32' flag=0; */
      /* '<S2>:1:34' if(Q_trad>QdMax+QbMax) */
      if (rtb_MaxQ > 7000.0) {
        /* '<S2>:1:35' Qd=QdMax; */
        Pd = 3500.0;

        /* '<S2>:1:36' Qb=QbMax; */
        Pb = 3500.0;

        /* '<S2>:1:37' flag=1; */
        flagDelt = 1;
      }

      /*  si ambas energias tienen el mismo factor de costo. */
      /* '<S2>:1:41' if(kd==kb && flag==0) */
      if (flagDelt == 0) {
        /* '<S2>:1:42' Qb=Q_trad/2; */
        Pb = rtb_MaxQ / 2.0;

        /* '<S2>:1:43' Qd=Q_trad/2; */
        Pd = rtb_MaxQ / 2.0;
      }

      /*  si la energia diesel es mas cara que la biomasa. */
      /* '<S2>:1:47' if(kd>kb && flag==0) */
      /*  si la biomasa es mas cara que la diesel. */
      /* '<S2>:1:58' if(kd<kb && flag==0) */
    }

    /* Outport: '<Root>/Qb' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potenica Reactiva'
     */
    /* '<S2>:1:69' Qbo=Qb; */
    /* '<S2>:1:70' Qdo=Qd; */
    control_terciario_Y.Qb = Pb;

    /* Outport: '<Root>/Qd' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potenica Reactiva'
     */
    control_terciario_Y.Qd = Pd;
  }

  rate_scheduler();
}

/* Model initialize function */
void control_terciario_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)control_terciario_M, 0,
                sizeof(RT_MODEL_control_terciario_T));

  /* external inputs */
  (void)memset((void *)&control_terciario_U, 0, sizeof(ExtU_control_terciario_T));

  /* external outputs */
  (void) memset((void *)&control_terciario_Y, 0,
                sizeof(ExtY_control_terciario_T));
}

/* Model terminate function */
void control_terciario_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
