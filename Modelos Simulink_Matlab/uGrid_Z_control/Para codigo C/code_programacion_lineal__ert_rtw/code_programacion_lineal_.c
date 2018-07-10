/*
 * File: code_programacion_lineal_.c
 *
 * Code generated for Simulink model 'code_programacion_lineal_'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 10 15:52:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "code_programacion_lineal_.h"
#include "code_programacion_lineal__private.h"

/* Block signals (auto storage) */
B_code_programacion_lineal__T code_programacion_lineal__B;

/* Block states (auto storage) */
DW_code_programacion_lineal__T code_programacion_lineal__DW;

/* External inputs (root inport signals with auto storage) */
ExtU_code_programacion_lineal__T code_programacion_lineal__U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_code_programacion_lineal__T code_programacion_lineal__Y;

/* Real-time model */
RT_MODEL_code_programacion_lineal__T code_programacion_lineal__M_;
RT_MODEL_code_programacion_lineal__T *const code_programacion_lineal__M =
  &code_programacion_lineal__M_;

/*
 * Output and update for atomic system:
 *    '<S2>/LinProg_BuildMatrices_ActivePower'
 *    '<S2>/LinProg_BuildMatrices_Reactive_Power'
 */
void LinProg_BuildMatrices_ActivePow(real_T rtu_Pren_max, real_T rtu_P_load,
  real_T rtu_K, real_T rtu_K_j, real_T rtu_Pcsis_max, real_T rtu_Pcsis_max_f,
  real_T rty_H[4], real_T rty_f[2], real_T rty_A[2], real_T rty_lb[2], real_T
  rty_ub[2], real_T *rty_lbA, real_T *rty_ubA)
{
  real_T Pm;
  real_T D;

  /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport4' */
  /*  Pr_max es la potencia maxima que puede suministrar el nodo de energias */
  /*  renovables. */
  /* MATLAB Function 'Optimizador  - Control de tercer nivel/LinProg_BuildMatrices_ActivePower': '<S3>:1' */
  /*  P_load es la potencia que consume la carga. ambas potencias son un vector */
  /*  de 2 componentes donde la primera componenete es la potencia activa y la */
  /*  segunda componenete es la potencia reactiva. */
  /*  Kp y Kq corresponde a un vector con los costos de la energia activa y  */
  /*  reactiva respectivamente para cada uno de los convertidores, en este caso */
  /*  bio y diesel solamente pero pueden agregarse tantas fuentes como se */
  /*  desee. */
  /*  Pin_max Qin_max corresponde a un vector con los valores maximos de */
  /*  potencia activa y reactiva que pueden generar cada una de las otras  */
  /*  fuentes diferentes a energias alternativas. */
  /*  El bloque qpOASES_(linprog) es un bloque que resuelve el problema standar */
  /*  de optimizacion cuadratica : */
  /*  1/2 x' H x + x' f */
  /*  sujeto a unas restricciones. la matriz H corresponde a la parte */
  /*  cuadratica del problema mientras que f corresponde a la parte lineal. es */
  /*  decir que haciendo H = matriz de zeros, es posible reutilizar el bloque */
  /*  para solucionar problemas de programacion lineal, que es justamente lo */
  /*  que se hace en esta parte del modelo. */
  /*  La presente matlab function tiene como tarea formar las matrices f */
  /*  y A de restricciones apropiadas para que el bloque de qp oases realice la */
  /*  funcione de programacion lineal. */
  /* '<S3>:1:33' Pm = sum(Pcsis_max); */
  Pm = rtu_Pcsis_max + rtu_Pcsis_max_f;

  /*  potencia activa maxima que pueden entregar todas las fuentes (en este caso bio y diesel) */
  /* '<S3>:1:36' D = P_load - Pren_max; */
  D = rtu_P_load - rtu_Pren_max;

  /*  diferencia entre la potencia que puede generar */
  /*  renovables con la que consume la carga. */
  /*  % % % % % % % % % % % % % % % % % % % % % % % % % % % %   */
  /*  Formacion de las entradas para la programacion lineal.  % */
  /*  % % % % % % % % % % % % % % % % % % % % % % % % % % % %   */
  /*  parte cuadratica de la funcion de coste que se pone en zeros para */
  /*  transformarlo en un problema de programacion lineal. */
  /* '<S3>:1:46' H = zeros(1, length(K)^2); */
  rty_H[0] = 0.0;
  rty_H[1] = 0.0;
  rty_H[2] = 0.0;
  rty_H[3] = 0.0;

  /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport3' */
  /*  funcion de coste lineal. */
  /* '<S3>:1:49' f = K; */
  rty_f[0] = rtu_K;
  rty_f[1] = rtu_K_j;

  /*  matriz de restricciones. */
  /*  esta formada con la idea de definir que la suma de todas las potencias */
  /*  deben almenos cubrir la cantidad de energia activa y reactiva que no */
  /*  puede suministrar renovables. */
  /* '<S3>:1:55' A = ones(1, length(K)); */
  /* '<S3>:1:57' lb = zeros(1, length(K)); */
  /*  potencia minima que puede generar cada uno de los generadores. */
  /* '<S3>:1:58' ub = [Pcsis_max]; */
  rty_A[0] = 1.0;
  rty_lb[0] = 0.0;

  /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport4' */
  rty_ub[0] = rtu_Pcsis_max;
  rty_A[1] = 1.0;
  rty_lb[1] = 0.0;

  /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport4' */
  rty_ub[1] = rtu_Pcsis_max_f;

  /*  potencia maxima que pueden generar cada uno de los generadores. */
  /* '<S3>:1:60' ubA = [Pm]; */
  *rty_ubA = Pm;

  /*  tambien esta relacionado con la potencia min, es un */
  /*  requerimiento para el blque de programacion lineal. */
  /*  depenediendo la diferencia entre la potencia que pide la carga y la que */
  /*  pueden suministrar energias renovables entonces lbA debe establecerce de */
  /*  manera conveniente para que el problema de programacion lineal tenga */
  /*  solucion. */
  /*  restriccion limite inferior para la potencia activa */
  /* '<S3>:1:69' if(D > 0) */
  if (D > 0.0) {
    /*  en caso de que renovables no baste para alimentar la carga... */
    /* '<S3>:1:70' if(D >= Pm) */
    if (D >= Pm) {
      /* '<S3>:1:71' vp = Pm; */
      D = Pm;
    } else {
      /* '<S3>:1:72' else */
      /* '<S3>:1:73' vp = D(1); */
    }
  } else {
    /* '<S3>:1:75' else */
    /*  si renovables basta para alimentar la carga. es decir D = 0 ó negativo */
    /* '<S3>:1:76' vp = 0; */
    D = 0.0;
  }

  /* '<S3>:1:79' lbA = vp; */
  *rty_lbA = D;
}

/* Model step function */
void code_programacion_lineal__step(void)
{
  int32_T rtb_MaxP;
  int32_T rtb_MaxQ;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/SOC'
   */
  /*   funcion que calcula la potencia maxima que puede suministrar las fuentes */
  /*   renovables deacuerdo a la cantidad de carga que hay almancenada en la */
  /*   bateria. esta va de 0 a 100% */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
  /*  estoc valores que aparecen a continuacion se pusieron de manera */
  /*  arbitraria. corresponde a una persona con especialidad en la parte de */
  /*  potencia electrica determinar el verdadero algoritmo para hallar la */
  /*  potencia que deberia suministrar el nodo de energia renovable deacuerdo a */
  /*  la carga de la bateria. */
  /* '<S1>:1:15' MaxP = 0; */
  rtb_MaxP = 0;

  /* '<S1>:1:16' MaxQ = 0; */
  rtb_MaxQ = 0;

  /* '<S1>:1:18' if( SOC >= 90 ) */
  if (code_programacion_lineal__U.SOC >= 90.0) {
    /* '<S1>:1:19' MaxP = 500; */
    rtb_MaxP = 500;

    /* '<S1>:1:20' MaxQ = 5000; */
    rtb_MaxQ = 5000;
  }

  /* '<S1>:1:23' if( SOC <= 90 ) */
  if (code_programacion_lineal__U.SOC <= 90.0) {
    /* '<S1>:1:24' MaxP = 200; */
    rtb_MaxP = 200;

    /* '<S1>:1:25' MaxQ = 4000; */
    rtb_MaxQ = 4000;
  }

  /* '<S1>:1:28' if( SOC <= 70 ) */
  if (code_programacion_lineal__U.SOC <= 70.0) {
    /* '<S1>:1:29' MaxP = 100; */
    rtb_MaxP = 100;

    /* '<S1>:1:30' MaxQ = 1000; */
    rtb_MaxQ = 1000;
  }

  /* '<S1>:1:33' if( SOC <= 60 ) */
  if (code_programacion_lineal__U.SOC <= 60.0) {
    /* '<S1>:1:34' MaxP = 50; */
    rtb_MaxP = 50;

    /* '<S1>:1:35' MaxQ = 500; */
    rtb_MaxQ = 500;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* MATLAB Function: '<S2>/LinProg_BuildMatrices_ActivePower' incorporates:
   *  Inport: '<Root>/KP1'
   *  Inport: '<Root>/KP2'
   *  Inport: '<Root>/P1_CSI'
   *  Inport: '<Root>/P2_CSI'
   *  Inport: '<Root>/P_Load'
   */
  LinProg_BuildMatrices_ActivePow((real_T)rtb_MaxP,
    code_programacion_lineal__U.P_Load, code_programacion_lineal__U.KP1,
    code_programacion_lineal__U.KP2, code_programacion_lineal__U.P1_CSI,
    code_programacion_lineal__U.P2_CSI, code_programacion_lineal__B.H_e,
    code_programacion_lineal__B.f_c, code_programacion_lineal__B.A_c,
    code_programacion_lineal__B.lb_i, code_programacion_lineal__B.ub_n,
    &code_programacion_lineal__B.lbA_b, &code_programacion_lineal__B.ubA_o);

  /* S-Function (qp_linprog): '<S2>/qpOASES_(linprog)' */

  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* Outport: '<Root>/Pbio' */
  code_programacion_lineal__Y.Pbio =
    code_programacion_lineal__B.qpOASES_linprog_o1[0];

  /* MATLAB Function: '<S2>/LinProg_BuildMatrices_Reactive_Power' incorporates:
   *  Inport: '<Root>/KQ1'
   *  Inport: '<Root>/KQ2'
   *  Inport: '<Root>/Q1_CSI'
   *  Inport: '<Root>/Q2_CSI'
   *  Inport: '<Root>/Q_Load'
   */
  LinProg_BuildMatrices_ActivePow((real_T)rtb_MaxQ,
    code_programacion_lineal__U.Q_Load, code_programacion_lineal__U.KQ1,
    code_programacion_lineal__U.KQ2, code_programacion_lineal__U.Q1_CSI,
    code_programacion_lineal__U.Q2_CSI, code_programacion_lineal__B.H,
    code_programacion_lineal__B.f, code_programacion_lineal__B.A,
    code_programacion_lineal__B.lb, code_programacion_lineal__B.ub,
    &code_programacion_lineal__B.lbA, &code_programacion_lineal__B.ubA);

  /* S-Function (qp_linprog): '<S2>/qpOASES_(linprog)1' */

  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)1' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* Outport: '<Root>/Qbio' */
  code_programacion_lineal__Y.Qbio =
    code_programacion_lineal__B.qpOASES_linprog1_o1[0];

  /* Outport: '<Root>/Pdie' */
  code_programacion_lineal__Y.Pdie =
    code_programacion_lineal__B.qpOASES_linprog_o1[1];

  /* Outport: '<Root>/Qdie' */
  code_programacion_lineal__Y.Qdie =
    code_programacion_lineal__B.qpOASES_linprog1_o1[1];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  code_programacion_lineal__M->Timing.t[0] =
    (++code_programacion_lineal__M->Timing.clockTick0) *
    code_programacion_lineal__M->Timing.stepSize0;
}

/* Model initialize function */
void code_programacion_lineal__initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)code_programacion_lineal__M, 0,
                sizeof(RT_MODEL_code_programacion_lineal__T));
  rtsiSetSolverName(&code_programacion_lineal__M->solverInfo,"FixedStepDiscrete");
  code_programacion_lineal__M->solverInfoPtr =
    (&code_programacion_lineal__M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = code_programacion_lineal__M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    code_programacion_lineal__M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    code_programacion_lineal__M->Timing.sampleTimes =
      (&code_programacion_lineal__M->Timing.sampleTimesArray[0]);
    code_programacion_lineal__M->Timing.offsetTimes =
      (&code_programacion_lineal__M->Timing.offsetTimesArray[0]);

    /* task periods */
    code_programacion_lineal__M->Timing.sampleTimes[0] = (0.1);

    /* task offsets */
    code_programacion_lineal__M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(code_programacion_lineal__M,
             &code_programacion_lineal__M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = code_programacion_lineal__M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    code_programacion_lineal__M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(code_programacion_lineal__M, -1);
  code_programacion_lineal__M->Timing.stepSize0 = 0.1;
  code_programacion_lineal__M->solverInfoPtr =
    (&code_programacion_lineal__M->solverInfo);
  code_programacion_lineal__M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&code_programacion_lineal__M->solverInfo, 0.1);
  rtsiSetSolverMode(&code_programacion_lineal__M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) memset(((void *) &code_programacion_lineal__B), 0,
                sizeof(B_code_programacion_lineal__T));

  /* states (dwork) */
  (void) memset((void *)&code_programacion_lineal__DW, 0,
                sizeof(DW_code_programacion_lineal__T));

  /* external inputs */
  (void)memset((void *)&code_programacion_lineal__U, 0, sizeof
               (ExtU_code_programacion_lineal__T));

  /* external outputs */
  (void) memset((void *)&code_programacion_lineal__Y, 0,
                sizeof(ExtY_code_programacion_lineal__T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo =
      &code_programacion_lineal__M->NonInlinedSFcns.sfcnInfo;
    code_programacion_lineal__M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, ((const char_T **)(&rtmGetErrorStatus
      (code_programacion_lineal__M))));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &code_programacion_lineal__M->Sizes.numSampTimes);
    code_programacion_lineal__M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (code_programacion_lineal__M)[0]);
    rtssSetTPtrPtr(sfcnInfo,
                   code_programacion_lineal__M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(code_programacion_lineal__M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(code_programacion_lineal__M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (code_programacion_lineal__M));
    rtssSetStepSizePtr(sfcnInfo, &code_programacion_lineal__M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (code_programacion_lineal__M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &code_programacion_lineal__M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &code_programacion_lineal__M->zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo,
      &code_programacion_lineal__M->blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo,
                         &code_programacion_lineal__M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &code_programacion_lineal__M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &code_programacion_lineal__M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &code_programacion_lineal__M->solverInfoPtr);
  }

  code_programacion_lineal__M->Sizes.numSFcns = (2);

  /* register each child */
  {
    (void) memset((void *)
                  &code_programacion_lineal__M->NonInlinedSFcns.childSFunctions
                  [0], 0,
                  2*sizeof(SimStruct));
    code_programacion_lineal__M->childSfunctions =
      (&code_programacion_lineal__M->NonInlinedSFcns.childSFunctionPtrs[0]);
    code_programacion_lineal__M->childSfunctions[0] =
      (&code_programacion_lineal__M->NonInlinedSFcns.childSFunctions[0]);
    code_programacion_lineal__M->childSfunctions[1] =
      (&code_programacion_lineal__M->NonInlinedSFcns.childSFunctions[1]);

    /* Level2 S-Function Block: code_programacion_lineal_/<S2>/qpOASES_(linprog) (qp_linprog) */
    {
      SimStruct *rts = code_programacion_lineal__M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &code_programacion_lineal__M->NonInlinedSFcns.blkInfo2
                         [0]);
      }

      ssSetRTWSfcnInfo(rts, code_programacion_lineal__M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods4
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &code_programacion_lineal__M->NonInlinedSFcns.statesInfo2
                         [0]);
        ssSetPeriodicStatesInfo(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 7);
        ssSetPortInfoForInputs(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs0;
          sfcnUPtrs[0] = code_programacion_lineal__B.H_e;
          sfcnUPtrs[1] = &code_programacion_lineal__B.H_e[1];
          sfcnUPtrs[2] = &code_programacion_lineal__B.H_e[2];
          sfcnUPtrs[3] = &code_programacion_lineal__B.H_e[3];
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 4);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs1;
          sfcnUPtrs[0] = code_programacion_lineal__B.f_c;
          sfcnUPtrs[1] = &code_programacion_lineal__B.f_c[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs2;
          sfcnUPtrs[0] = code_programacion_lineal__B.A_c;
          sfcnUPtrs[1] = &code_programacion_lineal__B.A_c[1];
          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 2);
        }

        /* port 3 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs3;
          sfcnUPtrs[0] = code_programacion_lineal__B.lb_i;
          sfcnUPtrs[1] = &code_programacion_lineal__B.lb_i[1];
          ssSetInputPortSignalPtrs(rts, 3, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 2);
        }

        /* port 4 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs4;
          sfcnUPtrs[0] = code_programacion_lineal__B.ub_n;
          sfcnUPtrs[1] = &code_programacion_lineal__B.ub_n[1];
          ssSetInputPortSignalPtrs(rts, 4, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 2);
        }

        /* port 5 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs5;
          sfcnUPtrs[0] = &code_programacion_lineal__B.lbA_b;
          ssSetInputPortSignalPtrs(rts, 5, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidth(rts, 5, 1);
        }

        /* port 6 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.UPtrs6;
          sfcnUPtrs[0] = &code_programacion_lineal__B.ubA_o;
          ssSetInputPortSignalPtrs(rts, 6, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidth(rts, 6, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 4);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            code_programacion_lineal__B.qpOASES_linprog_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog_o4));
        }
      }

      /* path info */
      ssSetModelName(rts, "qpOASES_(linprog)");
      ssSetPath(rts,
                "code_programacion_lineal_/Optimizador  - Control de tercer nivel/qpOASES_(linprog)");
      ssSetRTModel(rts,code_programacion_lineal__M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* work vectors */
      ssSetPWork(rts, (void **)
                 &code_programacion_lineal__DW.qpOASES_linprog_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* PWORK */
        ssSetDWorkWidth(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &code_programacion_lineal__DW.qpOASES_linprog_PWORK[0]);
      }

      /* registration */
      qp_linprog(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.1);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetInputPortWidth(rts, 0, 4);
      ssSetInputPortDataType(rts, 0, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 0, 0);
      ssSetInputPortFrameData(rts, 0, 0);
      ssSetInputPortWidth(rts, 1, 2);
      ssSetInputPortDataType(rts, 1, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 1, 0);
      ssSetInputPortFrameData(rts, 1, 0);
      ssSetInputPortWidth(rts, 2, 2);
      ssSetInputPortDataType(rts, 2, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 2, 0);
      ssSetInputPortFrameData(rts, 2, 0);
      ssSetInputPortWidth(rts, 3, 2);
      ssSetInputPortDataType(rts, 3, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 3, 0);
      ssSetInputPortFrameData(rts, 3, 0);
      ssSetInputPortWidth(rts, 4, 2);
      ssSetInputPortDataType(rts, 4, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 4, 0);
      ssSetInputPortFrameData(rts, 4, 0);
      ssSetInputPortWidth(rts, 5, 1);
      ssSetInputPortDataType(rts, 5, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 5, 0);
      ssSetInputPortFrameData(rts, 5, 0);
      ssSetInputPortWidth(rts, 6, 1);
      ssSetInputPortDataType(rts, 6, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 6, 0);
      ssSetInputPortFrameData(rts, 6, 0);
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 0);
      _ssSetOutputPortConnected(rts, 2, 0);
      _ssSetOutputPortConnected(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
    }

    /* Level2 S-Function Block: code_programacion_lineal_/<S2>/qpOASES_(linprog)1 (qp_linprog) */
    {
      SimStruct *rts = code_programacion_lineal__M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &code_programacion_lineal__M->NonInlinedSFcns.blkInfo2
                         [1]);
      }

      ssSetRTWSfcnInfo(rts, code_programacion_lineal__M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &code_programacion_lineal__M->NonInlinedSFcns.methods4
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &code_programacion_lineal__M->NonInlinedSFcns.statesInfo2
                         [1]);
        ssSetPeriodicStatesInfo(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 7);
        ssSetPortInfoForInputs(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.inputPortInfo[0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs0;
          sfcnUPtrs[0] = code_programacion_lineal__B.H;
          sfcnUPtrs[1] = &code_programacion_lineal__B.H[1];
          sfcnUPtrs[2] = &code_programacion_lineal__B.H[2];
          sfcnUPtrs[3] = &code_programacion_lineal__B.H[3];
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 4);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs1;
          sfcnUPtrs[0] = code_programacion_lineal__B.f;
          sfcnUPtrs[1] = &code_programacion_lineal__B.f[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs2;
          sfcnUPtrs[0] = code_programacion_lineal__B.A;
          sfcnUPtrs[1] = &code_programacion_lineal__B.A[1];
          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 2);
        }

        /* port 3 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs3;
          sfcnUPtrs[0] = code_programacion_lineal__B.lb;
          sfcnUPtrs[1] = &code_programacion_lineal__B.lb[1];
          ssSetInputPortSignalPtrs(rts, 3, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 2);
        }

        /* port 4 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs4;
          sfcnUPtrs[0] = code_programacion_lineal__B.ub;
          sfcnUPtrs[1] = &code_programacion_lineal__B.ub[1];
          ssSetInputPortSignalPtrs(rts, 4, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 2);
        }

        /* port 5 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs5;
          sfcnUPtrs[0] = &code_programacion_lineal__B.lbA;
          ssSetInputPortSignalPtrs(rts, 5, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidth(rts, 5, 1);
        }

        /* port 6 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.UPtrs6;
          sfcnUPtrs[0] = &code_programacion_lineal__B.ubA;
          ssSetInputPortSignalPtrs(rts, 6, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidth(rts, 6, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 4);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            code_programacion_lineal__B.qpOASES_linprog1_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog1_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog1_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &code_programacion_lineal__B.qpOASES_linprog1_o4));
        }
      }

      /* path info */
      ssSetModelName(rts, "qpOASES_(linprog)1");
      ssSetPath(rts,
                "code_programacion_lineal_/Optimizador  - Control de tercer nivel/qpOASES_(linprog)1");
      ssSetRTModel(rts,code_programacion_lineal__M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* work vectors */
      ssSetPWork(rts, (void **)
                 &code_programacion_lineal__DW.qpOASES_linprog1_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &code_programacion_lineal__M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* PWORK */
        ssSetDWorkWidth(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &code_programacion_lineal__DW.qpOASES_linprog1_PWORK
                   [0]);
      }

      /* registration */
      qp_linprog(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.1);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetInputPortWidth(rts, 0, 4);
      ssSetInputPortDataType(rts, 0, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 0, 0);
      ssSetInputPortFrameData(rts, 0, 0);
      ssSetInputPortWidth(rts, 1, 2);
      ssSetInputPortDataType(rts, 1, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 1, 0);
      ssSetInputPortFrameData(rts, 1, 0);
      ssSetInputPortWidth(rts, 2, 2);
      ssSetInputPortDataType(rts, 2, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 2, 0);
      ssSetInputPortFrameData(rts, 2, 0);
      ssSetInputPortWidth(rts, 3, 2);
      ssSetInputPortDataType(rts, 3, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 3, 0);
      ssSetInputPortFrameData(rts, 3, 0);
      ssSetInputPortWidth(rts, 4, 2);
      ssSetInputPortDataType(rts, 4, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 4, 0);
      ssSetInputPortFrameData(rts, 4, 0);
      ssSetInputPortWidth(rts, 5, 1);
      ssSetInputPortDataType(rts, 5, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 5, 0);
      ssSetInputPortFrameData(rts, 5, 0);
      ssSetInputPortWidth(rts, 6, 1);
      ssSetInputPortDataType(rts, 6, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 6, 0);
      ssSetInputPortFrameData(rts, 6, 0);
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 0);
      _ssSetOutputPortConnected(rts, 2, 0);
      _ssSetOutputPortConnected(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
    }
  }

  /* Start for S-Function (qp_linprog): '<S2>/qpOASES_(linprog)' */
  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (qp_linprog): '<S2>/qpOASES_(linprog)1' */
  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)1' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }
}

/* Model terminate function */
void code_programacion_lineal__terminate(void)
{
  /* Terminate for S-Function (qp_linprog): '<S2>/qpOASES_(linprog)' */
  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (qp_linprog): '<S2>/qpOASES_(linprog)1' */
  /* Level2 S-Function Block: '<S2>/qpOASES_(linprog)1' (qp_linprog) */
  {
    SimStruct *rts = code_programacion_lineal__M->childSfunctions[1];
    sfcnTerminate(rts);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
