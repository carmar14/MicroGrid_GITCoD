/*
 * File: inv2_genC.c
 *
 * Code generated for Simulink model 'inv2_genC'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Sat Apr 21 19:17:20 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "inv2_genC.h"
#include "inv2_genC_private.h"

/* Block signals (auto storage) */
B_inv2_genC_T inv2_genC_B;

/* Continuous states */
X_inv2_genC_T inv2_genC_X;

/* Block states (auto storage) */
DW_inv2_genC_T inv2_genC_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_inv2_genC_T inv2_genC_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_inv2_genC_T inv2_genC_Y;

/* Real-time model */
RT_MODEL_inv2_genC_T inv2_genC_M_;
RT_MODEL_inv2_genC_T *const inv2_genC_M = &inv2_genC_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 18;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  inv2_genC_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  inv2_genC_step();
  inv2_genC_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  inv2_genC_step();
  inv2_genC_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T q;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = (rtNaN);
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

/* Model step function */
void inv2_genC_step(void)
{
  if (rtmIsMajorTimeStep(inv2_genC_M)) {
    /* set solver stop time */
    if (!(inv2_genC_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&inv2_genC_M->solverInfo,
                            ((inv2_genC_M->Timing.clockTickH0 + 1) *
        inv2_genC_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&inv2_genC_M->solverInfo,
                            ((inv2_genC_M->Timing.clockTick0 + 1) *
        inv2_genC_M->Timing.stepSize0 + inv2_genC_M->Timing.clockTickH0 *
        inv2_genC_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(inv2_genC_M)) {
    inv2_genC_M->Timing.t[0] = rtsiGetT(&inv2_genC_M->solverInfo);
  }

  {
    int32_T a;
    real_T rtb_Product;
    real_T rtb_PhaseShift3;
    real_T rtb_PhaseShift4;
    real_T Sum2;
    if (rtmIsMajorTimeStep(inv2_genC_M)) {
      /* S-Function (sfun_spssw_discc): '<S48>/State-Space' incorporates:
       *  Constant: '<S33>/eee'
       *  Constant: '<S35>/eee'
       *  Constant: '<S37>/eee'
       *  Constant: '<S39>/eee'
       *  Constant: '<S46>/DC'
       *  Constant: '<S50>/SwitchCurrents'
       */

      /* S-Function block: <S48>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*)
          inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*) inv2_genC_DW.StateSpace_PWORK.SW_CHG;
        int_T *gState = (int_T*) inv2_genC_DW.StateSpace_PWORK.G_STATE;
        real_T *yswitch = (real_T*)inv2_genC_DW.StateSpace_PWORK.Y_SWITCH;
        int_T *switchTypes = (int_T*) inv2_genC_DW.StateSpace_PWORK.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*) inv2_genC_DW.StateSpace_PWORK.IDX_OUT_SW;
        real_T *DxCol = (real_T*)inv2_genC_DW.StateSpace_PWORK.DX_COL;
        real_T *tmp2 = (real_T*)inv2_genC_DW.StateSpace_PWORK.TMP2;
        real_T *BDcol = (real_T*)inv2_genC_DW.StateSpace_PWORK.BD_COL;
        real_T *tmp1 = (real_T*)inv2_genC_DW.StateSpace_PWORK.TMP1;
        real_T *uswlast = (real_T*)inv2_genC_DW.StateSpace_PWORK.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 9 * sizeof(int_T));
        memcpy(uswlast, &inv2_genC_B.StateSpace_o1[0], 9*sizeof(real_T));
        do {
          if (loopsToDo == 1) {        /* Need to reset some variables: */
            swChanged = 0;

            /* return to the original switch status*/
            {
              int_T i1;
              for (i1=0; i1 < 9; i1++) {
                swChanged = ((SwitchChange[i1] = switch_status_init[i1] -
                              switch_status[i1]) != 0) ? 1 : swChanged;
                switch_status[i1] = switch_status_init[i1];
              }
            }
          } else {
            /*
             * Compute outputs:
             * ---------------
             */
            real_T *Cs = (real_T*)inv2_genC_DW.StateSpace_PWORK.CS;
            real_T *Ds = (real_T*)inv2_genC_DW.StateSpace_PWORK.DS;

            {
              int_T i1;
              real_T *y0 = &inv2_genC_B.StateSpace_o1[0];
              for (i1=0; i1 < 11; i1++) {
                accum = 0.0;

                {
                  int_T i2;
                  real_T *xd = &inv2_genC_DW.StateSpace_DSTATE[0];
                  for (i2=0; i2 < 6; i2++) {
                    accum += *(Cs++) * xd[i2];
                  }
                }

                {
                  int_T i2;
                  const real_T *u0 = inv2_genC_ConstP.SwitchCurrents_Value;
                  for (i2=0; i2 < 9; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  accum += *(Ds++) * 1000.0;
                  accum += *(Ds++) * 0.8;
                  accum += *(Ds++) * 0.8;
                  accum += *(Ds++) * 0.8;
                  accum += *(Ds++) * 0.8;
                }

                y0[i1] = accum;
              }
            }

            swChanged = 0;

            {
              int_T i1;
              real_T *y0 = &inv2_genC_B.StateSpace_o1[0];
              for (i1=0; i1 < 9; i1++) {
                switch (switchTypes[i1]) {
                 case 1 :              /* Ideal switch */
                  newState = gState[i1] > 0 ? 1 : 0;
                  break;

                 case 2 :              /* Breaker */
                  newState = (gState[i1] > 0) ? 1 : ((y0[i1]*uswlast[i1] < 0.0) ?
                    0 : switch_status[i1]);
                  break;

                 case 3 :              /* Diodes */
                  newState = y0[i1] > 0.0 ? 1 : ((y0[i1] < 0.0) ? 0 :
                    switch_status[i1]);
                  break;
                }

                swChanged = ((SwitchChange[i1] = newState - switch_status[i1])
                             != 0) ? 1 : swChanged;
                switch_status[i1] = newState;/* Keep new state */
              }
            }
          }

          /*
           * Compute new As, Bs, Cs and Ds matrixes:
           * --------------------------------------
           */
          if (swChanged) {
            real_T *As = (real_T*)inv2_genC_DW.StateSpace_PWORK.AS;
            real_T *Cs = (real_T*)inv2_genC_DW.StateSpace_PWORK.CS;
            real_T *Bs = (real_T*)inv2_genC_DW.StateSpace_PWORK.BS;
            real_T *Ds = (real_T*)inv2_genC_DW.StateSpace_PWORK.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 9; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*15]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      DxCol[i2]= Ds[i2 * 14 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;

                  {
                    int_T i2;
                    for (i2=0; i2 < 6; i2++) {
                      BDcol[i2]= Bs[i2 * 14 + i1]*a1;
                    }
                  }

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 6], 6 * sizeof(real_T));
                  memset(&Cs[i1 * 6], '\0', 6 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 14], 14 * sizeof(real_T));
                  memset(&Ds[i1 * 14], '\0', 14 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      a1 = DxCol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 6; i3++) {
                          Cs[i2 * 6 + i3] += a1 * tmp1[i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 14; i3++) {
                          Ds[i2 * 14 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 6; i2++) {
                      a1 = BDcol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 6; i3++) {
                          As[i2 * 6 + i3] += a1 * Cs[i1 * 6 + i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 14; i3++) {
                          Bs[i2 * 14 + i3] += a1 * Ds[i1 * 14 + i3];
                        }
                      }
                    }
                  }
                }
              }
            }
          }                            /* if (swChanged) */
        } while (swChanged > 0 && --loopsToDo > 0);

        if (loopsToDo == 0) {
          real_T *Cs = (real_T*)inv2_genC_DW.StateSpace_PWORK.CS;
          real_T *Ds = (real_T*)inv2_genC_DW.StateSpace_PWORK.DS;

          {
            int_T i1;
            real_T *y0 = &inv2_genC_B.StateSpace_o1[0];
            for (i1=0; i1 < 11; i1++) {
              accum = 0.0;

              {
                int_T i2;
                real_T *xd = &inv2_genC_DW.StateSpace_DSTATE[0];
                for (i2=0; i2 < 6; i2++) {
                  accum += *(Cs++) * xd[i2];
                }
              }

              {
                int_T i2;
                const real_T *u0 = inv2_genC_ConstP.SwitchCurrents_Value;
                for (i2=0; i2 < 9; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                accum += *(Ds++) * 1000.0;
                accum += *(Ds++) * 0.8;
                accum += *(Ds++) * 0.8;
                accum += *(Ds++) * 0.8;
                accum += *(Ds++) * 0.8;
              }

              y0[i1] = accum;
            }
          }
        }

        /* Output new switches states */
        {
          int_T i1;
          real_T *y1 = &inv2_genC_B.StateSpace_o2[0];
          for (i1=0; i1 < 9; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }
    }

    /* Outport: '<Root>/pdie_meas' incorporates:
     *  StateSpace: '<Root>/Hw5'
     */
    inv2_genC_Y.pdie_meas = 0.94444980822600488 * inv2_genC_X.Hw5_CSTATE[3];

    /* Outport: '<Root>/qdie_meas' incorporates:
     *  StateSpace: '<Root>/Hw8'
     */
    inv2_genC_Y.qdie_meas = 0.94444980822600488 * inv2_genC_X.Hw8_CSTATE[3];

    /* TransferFcn: '<S1>/Transfer Fcn' */
    inv2_genC_B.TransferFcn = 0.0;
    inv2_genC_B.TransferFcn += 1.0E+6 * inv2_genC_X.TransferFcn_CSTATE;

    /* TransferFcn: '<S1>/Transfer Fcn1' */
    inv2_genC_B.TransferFcn1 = 0.0;
    inv2_genC_B.TransferFcn1 += 1.0E+6 * inv2_genC_X.TransferFcn1_CSTATE;

    /* StateSpace: '<Root>/Hw3' */
    inv2_genC_B.Hw3 = 0.0;
    inv2_genC_B.Hw3 += 1.0000000000000002 * inv2_genC_X.Hw3_CSTATE[1];

    /* TransferFcn: '<Root>/PhaseShift3' */
    rtb_PhaseShift3 = -740.74074074074065 * inv2_genC_X.PhaseShift3_CSTATE +
      0.99999999999999989 * inv2_genC_B.Hw3;

    /* MATLAB Function: '<Root>/PQ2AlphBetaCurrents_SinglePhase1' incorporates:
     *  Inport: '<Root>/mpc_Pdie'
     *  Inport: '<Root>/mpc_Qdie'
     */
    /*  divide by zero protection */
    /* MATLAB Function 'PQ2AlphBetaCurrents_SinglePhase1': '<S3>:1' */
    /* '<S3>:1:5' if(abs((Va^2+Vb^2))<=1000*eps(0)) */
    if (fabs(inv2_genC_B.Hw3 * inv2_genC_B.Hw3 + rtb_PhaseShift3 *
             rtb_PhaseShift3) <= 4.94065645841247E-321) {
      /* '<S3>:1:6' det = 1/eps(0); */
      rtb_Product = (rtInf);
    } else {
      /* '<S3>:1:7' else */
      /* '<S3>:1:8' det = 1/(Va^2+Vb^2); */
      rtb_Product = 1.0 / (inv2_genC_B.Hw3 * inv2_genC_B.Hw3 + rtb_PhaseShift3 *
                           rtb_PhaseShift3);

      /*  constante auxiliar */
    }

    /* det = 1/(Va^2+Vb^2); */
    /* '<S3>:1:12' Mat = det*[Va Vb; Vb -Va]; */
    /* '<S3>:1:13' Iab = Mat*[2*p;2*q]; */
    rtb_Product = rtb_Product * inv2_genC_B.Hw3 * (2.0 * inv2_genC_U.mpc_Pdie) +
      rtb_Product * rtb_PhaseShift3 * (2.0 * inv2_genC_U.mpc_Qdie);

    /* '<S3>:1:15' Iaaux = Iab(1); */
    /* '<S3>:1:16' Ibaux = Iab(2); */
    /* '<S3>:1:18' ilim=1e3; */
    /* '<S3>:1:20' if(Iaaux>ilim) */
    if (rtb_Product > 1000.0) {
      /* '<S3>:1:21' Iaaux=ilim; */
      rtb_Product = 1000.0;
    }

    /* '<S3>:1:23' if(Iaaux<-ilim) */
    if (rtb_Product < -1000.0) {
      /* '<S3>:1:24' Iaaux =-ilim; */
      rtb_Product = -1000.0;
    }

    /* '<S3>:1:27' if(isnan(Iaaux)) */
    if (rtIsNaN(rtb_Product)) {
      /* '<S3>:1:28' Iaaux=0; */
      rtb_Product = 0.0;
    }

    /* StateSpace: '<Root>/Hw7' */
    /* ----------------- */
    /* '<S3>:1:33' if(Ibaux>ilim) */
    /* '<S3>:1:36' if(Ibaux<-ilim) */
    /* '<S3>:1:40' if(isnan(Ibaux)) */
    /* ----------------- */
    /* '<S3>:1:46' Ia = Iaaux; */
    /* '<S3>:1:47' Ib = Ibaux; */
    inv2_genC_B.Hw7 = 0.0;
    inv2_genC_B.Hw7 += 1.0000000000000002 * inv2_genC_X.Hw7_CSTATE[1];

    /* Product: '<S47>/Product' incorporates:
     *  MATLAB Function: '<Root>/PQ2AlphBetaCurrents_SinglePhase1'
     *  Step: '<S47>/Step'
     *  Sum: '<S5>/Sum'
     */
    rtb_Product = (rtb_Product - inv2_genC_B.Hw7) * (real_T)
      !(inv2_genC_M->Timing.t[0] < 0.001);

    /* Sum: '<S1>/Sum2' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Gain: '<S5>/K1'
     *  Sum: '<S5>/Sum1'
     *  TransferFcn: '<S5>/Transfer Fcn'
     */
    Sum2 = ((0.0 * inv2_genC_X.TransferFcn_CSTATE_n[1] +
             inv2_genC_X.TransferFcn_CSTATE_n[0]) + 0.4 * rtb_Product) + 0.5;
    if (rtmIsMajorTimeStep(inv2_genC_M)) {
      /* Gain: '<S1>/Gain' incorporates:
       *  Constant: '<S42>/Constant'
       *  Constant: '<S44>/Constant2'
       *  DataTypeConversion: '<S10>/Data Type Conversion'
       *  DigitalClock: '<S44>/Digital Clock'
       *  Fcn: '<S10>/Fcn'
       *  Fcn: '<S44>/Fcn'
       *  Gain: '<S44>/1\ib1'
       *  Logic: '<S10>/Logical Operator'
       *  Math: '<S44>/Math Function'
       *  RelationalOperator: '<S10>/Relational Operator'
       *  RelationalOperator: '<S42>/Compare'
       */
      Sum2 = (real_T)((Sum2 != 0.0) && (Sum2 >= ((12000.0 * rt_remd_snf
        ((((inv2_genC_M->Timing.clockTick1+inv2_genC_M->Timing.clockTickH1*
            4294967296.0)) * 1.0E-6), 8.3333333333333331E-5) * 2.0 - 1.0) + 1.0)
        * 0.5)) * 15.0;

      /* Product: '<S11>/Product' incorporates:
       *  Step: '<S11>/Step'
       */
      inv2_genC_B.Product = (real_T)!((((inv2_genC_M->Timing.clockTick1+
        inv2_genC_M->Timing.clockTickH1* 4294967296.0)) * 1.0E-6) < 0.001) *
        Sum2;

      /* MATLAB Function: '<S1>/not_pwm' */
      /* MATLAB Function '3PhaseInverter1/not_pwm': '<S14>:1' */
      /* '<S14>:1:4' if(u==0 || u<0) */
      if (Sum2 == 0.0) {
        /* '<S14>:1:5' a=15; */
        a = 15;
      } else {
        /* '<S14>:1:6' else */
        /* '<S14>:1:7' a=0; */
        a = 0;
      }

      /* Product: '<S12>/Product' incorporates:
       *  MATLAB Function: '<S1>/not_pwm'
       *  Step: '<S12>/Step'
       */
      /* '<S14>:1:10' y = a; */
      inv2_genC_B.Product_c = (real_T)!((((inv2_genC_M->Timing.clockTick1+
        inv2_genC_M->Timing.clockTickH1* 4294967296.0)) * 1.0E-6) < 0.001) *
        (real_T)a;
    }

    /* Lookup: '<S16>/Look-Up Table' incorporates:
     *  Clock: '<S16>/Clock'
     */
    inv2_genC_B.LookUpTable = rt_Lookup(inv2_genC_ConstP.LookUpTable_XData, 5,
      inv2_genC_M->Timing.t[0], inv2_genC_ConstP.LookUpTable_YData);

    /* Step: '<S1>/Step' */
    inv2_genC_B.Step = !(inv2_genC_M->Timing.t[0] < 0.001);

    /* TransferFcn: '<Root>/PhaseShift4' */
    rtb_PhaseShift4 = -740.74074074074065 * inv2_genC_X.PhaseShift4_CSTATE +
      0.99999999999999989 * inv2_genC_B.Hw7;

    /* MATLAB Function: '<Root>/PQ_singlePhase1' */
    /*  Esta funcion calcula la potencia activa y reactiva instantanea */
    /*  para el caso mnosofasico. En la revision de 2 papers he observado */
    /*  que una manera de extender la teoria de potencia al caso monofasico */
    /*  es asumiendo la tension o corriente de una fase como la componente */
    /*  alpha y hacer un desfase de 90 grados para obtener una version */
    /*  artificial de beta. */
    /* MATLAB Function 'PQ_singlePhase1': '<S4>:1' */
    /* '<S4>:1:9' paux=va*ia+vb*ib; */
    Sum2 = inv2_genC_B.Hw3 * inv2_genC_B.Hw7 + rtb_PhaseShift3 * rtb_PhaseShift4;

    /* '<S4>:1:10' if(paux > 20e4) */
    if (Sum2 > 200000.0) {
      /* '<S4>:1:11' paux = 20e4; */
      Sum2 = 200000.0;
    }

    /* '<S4>:1:13' if(paux < -20e4) */
    if (Sum2 < -200000.0) {
      /* '<S4>:1:14' paux = -20e-4; */
      Sum2 = -0.002;
    }

    /* '<S4>:1:17' p = paux/2; */
    inv2_genC_B.p = Sum2 / 2.0;

    /*  potencia activa instantanea */
    /* '<S4>:1:19' qaux = vb*ia-va*ib; */
    rtb_PhaseShift3 = rtb_PhaseShift3 * inv2_genC_B.Hw7 - inv2_genC_B.Hw3 *
      rtb_PhaseShift4;

    /* '<S4>:1:21' if(qaux>20e4) */
    if (rtb_PhaseShift3 > 200000.0) {
      /* '<S4>:1:22' qaux=20e4; */
      rtb_PhaseShift3 = 200000.0;
    }

    /* '<S4>:1:24' if(qaux<-20e4) */
    if (rtb_PhaseShift3 < -200000.0) {
      /* '<S4>:1:25' qaux=-20e4; */
      rtb_PhaseShift3 = -200000.0;
    }

    /* '<S4>:1:28' q = qaux/2; */
    inv2_genC_B.q = rtb_PhaseShift3 / 2.0;

    /* End of MATLAB Function: '<Root>/PQ_singlePhase1' */

    /* Gain: '<S5>/K2' */
    /*  potencia reactiva instantanea */
    inv2_genC_B.K2 = 200.0 * rtb_Product;
  }

  if (rtmIsMajorTimeStep(inv2_genC_M)) {
    real_T *lastU;
    if (rtmIsMajorTimeStep(inv2_genC_M)) {
      /* Update for S-Function (sfun_spssw_discc): '<S48>/State-Space' incorporates:
       *  Constant: '<S33>/eee'
       *  Constant: '<S35>/eee'
       *  Constant: '<S37>/eee'
       *  Constant: '<S39>/eee'
       *  Constant: '<S46>/DC'
       *  Constant: '<S50>/SwitchCurrents'
       */

      /* S-Function block: <S48>/State-Space */
      {
        const real_T *As = (real_T*)inv2_genC_DW.StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)inv2_genC_DW.StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)inv2_genC_DW.StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        {
          int_T i1;
          real_T *xd = &inv2_genC_DW.StateSpace_DSTATE[0];
          for (i1=0; i1 < 6; i1++) {
            accum = 0.0;

            {
              int_T i2;
              real_T *xd = &inv2_genC_DW.StateSpace_DSTATE[0];
              for (i2=0; i2 < 6; i2++) {
                accum += *(As++) * xd[i2];
              }
            }

            {
              int_T i2;
              const real_T *u0 = inv2_genC_ConstP.SwitchCurrents_Value;
              for (i2=0; i2 < 9; i2++) {
                accum += *(Bs++) * u0[i2];
              }

              accum += *(Bs++) * 1000.0;
              accum += *(Bs++) * 0.8;
              accum += *(Bs++) * 0.8;
              accum += *(Bs++) * 0.8;
              accum += *(Bs++) * 0.8;
            }

            xtmp[i1] = accum;
          }
        }

        {
          int_T i1;
          real_T *xd = &inv2_genC_DW.StateSpace_DSTATE[0];
          for (i1=0; i1 < 6; i1++) {
            xd[i1] = xtmp[i1];
          }
        }

        {
          int_T *gState = (int_T*)inv2_genC_DW.StateSpace_PWORK.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T) inv2_genC_B.Product;
          *(gState++) = (int_T) inv2_genC_B.Product_c;
          *(gState++) = (int_T) inv2_genC_B.Product;
          *(gState++) = (int_T) inv2_genC_B.Product_c;
          *(gState++) = (int_T) inv2_genC_B.Step;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }
    }

    /* Update for Derivative: '<S16>/Derivative' */
    if (inv2_genC_DW.TimeStampA == (rtInf)) {
      inv2_genC_DW.TimeStampA = inv2_genC_M->Timing.t[0];
      lastU = &inv2_genC_DW.LastUAtTimeA;
    } else if (inv2_genC_DW.TimeStampB == (rtInf)) {
      inv2_genC_DW.TimeStampB = inv2_genC_M->Timing.t[0];
      lastU = &inv2_genC_DW.LastUAtTimeB;
    } else if (inv2_genC_DW.TimeStampA < inv2_genC_DW.TimeStampB) {
      inv2_genC_DW.TimeStampA = inv2_genC_M->Timing.t[0];
      lastU = &inv2_genC_DW.LastUAtTimeA;
    } else {
      inv2_genC_DW.TimeStampB = inv2_genC_M->Timing.t[0];
      lastU = &inv2_genC_DW.LastUAtTimeB;
    }

    *lastU = inv2_genC_B.LookUpTable;

    /* End of Update for Derivative: '<S16>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(inv2_genC_M)) {
    rt_ertODEUpdateContinuousStates(&inv2_genC_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++inv2_genC_M->Timing.clockTick0)) {
      ++inv2_genC_M->Timing.clockTickH0;
    }

    inv2_genC_M->Timing.t[0] = rtsiGetSolverStopTime(&inv2_genC_M->solverInfo);

    {
      /* Update absolute timer for sample time: [1.0E-6s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.0E-6, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      inv2_genC_M->Timing.clockTick1++;
      if (!inv2_genC_M->Timing.clockTick1) {
        inv2_genC_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void inv2_genC_derivatives(void)
{
  XDot_inv2_genC_T *_rtXdot;
  _rtXdot = ((XDot_inv2_genC_T *) inv2_genC_M->derivs);

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[0] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw8' */
  _rtXdot->Hw8_CSTATE[0] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[1] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw8' */
  _rtXdot->Hw8_CSTATE[1] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[2] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw8' */
  _rtXdot->Hw8_CSTATE[2] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[3] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw8' */
  _rtXdot->Hw8_CSTATE[3] = 0.0;

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[0] += -341.08603071128289 * inv2_genC_X.Hw5_CSTATE[0];
  _rtXdot->Hw5_CSTATE[0] += -178.02459475242631 * inv2_genC_X.Hw5_CSTATE[1];
  _rtXdot->Hw5_CSTATE[1] += 178.0245947524264 * inv2_genC_X.Hw5_CSTATE[0];
  _rtXdot->Hw5_CSTATE[2] += 199.58239979893239 * inv2_genC_X.Hw5_CSTATE[1];
  _rtXdot->Hw5_CSTATE[2] += -247.76277465378331 * inv2_genC_X.Hw5_CSTATE[2];
  _rtXdot->Hw5_CSTATE[2] += -199.58239979893239 * inv2_genC_X.Hw5_CSTATE[3];
  _rtXdot->Hw5_CSTATE[3] += 199.58239979893244 * inv2_genC_X.Hw5_CSTATE[2];
  _rtXdot->Hw5_CSTATE[0] += 188.49555921538757 * inv2_genC_B.p;

  /* Derivatives for StateSpace: '<Root>/Hw8' */
  _rtXdot->Hw8_CSTATE[0] += -341.08603071128289 * inv2_genC_X.Hw8_CSTATE[0];
  _rtXdot->Hw8_CSTATE[0] += -178.02459475242631 * inv2_genC_X.Hw8_CSTATE[1];
  _rtXdot->Hw8_CSTATE[1] += 178.0245947524264 * inv2_genC_X.Hw8_CSTATE[0];
  _rtXdot->Hw8_CSTATE[2] += 199.58239979893239 * inv2_genC_X.Hw8_CSTATE[1];
  _rtXdot->Hw8_CSTATE[2] += -247.76277465378331 * inv2_genC_X.Hw8_CSTATE[2];
  _rtXdot->Hw8_CSTATE[2] += -199.58239979893239 * inv2_genC_X.Hw8_CSTATE[3];
  _rtXdot->Hw8_CSTATE[3] += 199.58239979893244 * inv2_genC_X.Hw8_CSTATE[2];
  _rtXdot->Hw8_CSTATE[0] += 188.49555921538757 * inv2_genC_B.q;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -1.0E+6 * inv2_genC_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += inv2_genC_B.StateSpace_o1[10];

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -1.0E+6 * inv2_genC_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += inv2_genC_B.StateSpace_o1[9];

  /* Derivatives for StateSpace: '<Root>/Hw3' */
  _rtXdot->Hw3_CSTATE[0] = 0.0;
  _rtXdot->Hw3_CSTATE[1] = 0.0;
  _rtXdot->Hw3_CSTATE[0] += -76179.573297837138 * inv2_genC_X.Hw3_CSTATE[0];
  _rtXdot->Hw3_CSTATE[0] += -43982.2971502571 * inv2_genC_X.Hw3_CSTATE[1];
  _rtXdot->Hw3_CSTATE[1] += 43982.297150257094 * inv2_genC_X.Hw3_CSTATE[0];
  _rtXdot->Hw3_CSTATE[0] += 43982.2971502571 * inv2_genC_B.TransferFcn1;

  /* Derivatives for TransferFcn: '<Root>/PhaseShift3' */
  _rtXdot->PhaseShift3_CSTATE = 0.0;
  _rtXdot->PhaseShift3_CSTATE += -370.37037037037032 *
    inv2_genC_X.PhaseShift3_CSTATE;
  _rtXdot->PhaseShift3_CSTATE += inv2_genC_B.Hw3;

  /* Derivatives for StateSpace: '<Root>/Hw7' */
  _rtXdot->Hw7_CSTATE[0] = 0.0;

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_n[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE_n[0] += -2.0 * inv2_genC_X.TransferFcn_CSTATE_n[0];

  /* Derivatives for StateSpace: '<Root>/Hw7' */
  _rtXdot->Hw7_CSTATE[1] = 0.0;

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_n[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE_n[0] += -142122.30337568672 *
    inv2_genC_X.TransferFcn_CSTATE_n[1];

  /* Derivatives for StateSpace: '<Root>/Hw7' */
  _rtXdot->Hw7_CSTATE[0] += -76179.573297837138 * inv2_genC_X.Hw7_CSTATE[0];
  _rtXdot->Hw7_CSTATE[0] += -43982.2971502571 * inv2_genC_X.Hw7_CSTATE[1];
  _rtXdot->Hw7_CSTATE[1] += 43982.297150257094 * inv2_genC_X.Hw7_CSTATE[0];
  _rtXdot->Hw7_CSTATE[0] += 43982.2971502571 * inv2_genC_B.TransferFcn;

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_n[1] += inv2_genC_X.TransferFcn_CSTATE_n[0];
  _rtXdot->TransferFcn_CSTATE_n[0] += inv2_genC_B.K2;

  /* Derivatives for TransferFcn: '<Root>/PhaseShift4' */
  _rtXdot->PhaseShift4_CSTATE = 0.0;
  _rtXdot->PhaseShift4_CSTATE += -370.37037037037032 *
    inv2_genC_X.PhaseShift4_CSTATE;
  _rtXdot->PhaseShift4_CSTATE += inv2_genC_B.Hw7;
}

/* Model initialize function */
void inv2_genC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)inv2_genC_M, 0,
                sizeof(RT_MODEL_inv2_genC_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&inv2_genC_M->solverInfo,
                          &inv2_genC_M->Timing.simTimeStep);
    rtsiSetTPtr(&inv2_genC_M->solverInfo, &rtmGetTPtr(inv2_genC_M));
    rtsiSetStepSizePtr(&inv2_genC_M->solverInfo, &inv2_genC_M->Timing.stepSize0);
    rtsiSetdXPtr(&inv2_genC_M->solverInfo, &inv2_genC_M->derivs);
    rtsiSetContStatesPtr(&inv2_genC_M->solverInfo, (real_T **)
                         &inv2_genC_M->contStates);
    rtsiSetNumContStatesPtr(&inv2_genC_M->solverInfo,
      &inv2_genC_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&inv2_genC_M->solverInfo,
      &inv2_genC_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&inv2_genC_M->solverInfo,
      &inv2_genC_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&inv2_genC_M->solverInfo,
      &inv2_genC_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&inv2_genC_M->solverInfo, (&rtmGetErrorStatus
      (inv2_genC_M)));
    rtsiSetRTModelPtr(&inv2_genC_M->solverInfo, inv2_genC_M);
  }

  rtsiSetSimTimeStep(&inv2_genC_M->solverInfo, MAJOR_TIME_STEP);
  inv2_genC_M->intgData.y = inv2_genC_M->odeY;
  inv2_genC_M->intgData.f[0] = inv2_genC_M->odeF[0];
  inv2_genC_M->intgData.f[1] = inv2_genC_M->odeF[1];
  inv2_genC_M->intgData.f[2] = inv2_genC_M->odeF[2];
  inv2_genC_M->contStates = ((X_inv2_genC_T *) &inv2_genC_X);
  rtsiSetSolverData(&inv2_genC_M->solverInfo, (void *)&inv2_genC_M->intgData);
  rtsiSetSolverName(&inv2_genC_M->solverInfo,"ode3");
  rtmSetTPtr(inv2_genC_M, &inv2_genC_M->Timing.tArray[0]);
  inv2_genC_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  (void) memset(((void *) &inv2_genC_B), 0,
                sizeof(B_inv2_genC_T));

  /* states (continuous) */
  {
    (void) memset((void *)&inv2_genC_X, 0,
                  sizeof(X_inv2_genC_T));
  }

  /* states (dwork) */
  (void) memset((void *)&inv2_genC_DW, 0,
                sizeof(DW_inv2_genC_T));

  /* external inputs */
  (void)memset((void *)&inv2_genC_U, 0, sizeof(ExtU_inv2_genC_T));

  /* external outputs */
  (void) memset((void *)&inv2_genC_Y, 0,
                sizeof(ExtY_inv2_genC_T));

  /* Start for S-Function (sfun_spssw_discc): '<S48>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S46>/DC'
   *  Constant: '<S50>/SwitchCurrents'
   */

  /* S-Function block: <S48>/State-Space */
  {
    inv2_genC_DW.StateSpace_PWORK.AS = (real_T*)calloc(6 * 6, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.BS = (real_T*)calloc(6 * 14, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.CS = (real_T*)calloc(11 * 6, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.DS = (real_T*)calloc(11 * 14, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(11, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(14, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(6, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(6, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(6, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS = (int_T*)calloc(9, sizeof(int_T));
    inv2_genC_DW.StateSpace_PWORK.SW_CHG = (int_T*)calloc(9, sizeof(int_T));
    inv2_genC_DW.StateSpace_PWORK.G_STATE = (int_T*)calloc(9, sizeof(int_T));
    inv2_genC_DW.StateSpace_PWORK.Y_SWITCH = (real_T*)calloc(9, sizeof(real_T));
    inv2_genC_DW.StateSpace_PWORK.SWITCH_TYPES = (int_T*)calloc(9, sizeof(int_T));
    inv2_genC_DW.StateSpace_PWORK.IDX_OUT_SW = (int_T*)calloc(9, sizeof(int_T));
    inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS_INIT = (int_T*)calloc(9, sizeof
      (int_T));
    inv2_genC_DW.StateSpace_PWORK.USWLAST = (real_T*)calloc(9, sizeof(real_T));
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S48>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S46>/DC'
   *  Constant: '<S50>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)inv2_genC_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)inv2_genC_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)inv2_genC_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)inv2_genC_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&inv2_genC_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 6; i++) {
      X0[i] = (inv2_genC_ConstP.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<6; i++) {
      for (j=0; j<6; j++)
        As[i*6 + j] = (inv2_genC_ConstP.StateSpace_AS_param[i + j*6]);
      for (j=0; j<14; j++)
        Bs[i*14 + j] = (inv2_genC_ConstP.StateSpace_BS_param[i + j*6]);
    }

    /* Copy and transpose C */
    for (i=0; i<11; i++) {
      for (j=0; j<6; j++)
        Cs[i*6 + j] = (inv2_genC_ConstP.StateSpace_CS_param[i + j*11]);
    }

    /* Copy and transpose D */
    for (i=0; i<11; i++) {
      for (j=0; j<14; j++)
        Ds[i*14 + j] = (inv2_genC_ConstP.StateSpace_DS_param[i + j*11]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*)
        inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)inv2_genC_DW.StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)inv2_genC_DW.StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)inv2_genC_DW.StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)inv2_genC_DW.StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;

      /* Initialize work vectors */
      switch_status[0] = 0;
      switch_status_init[0] = 0;
      gState[0] = (int_T) 0.0;
      yswitch[0] = 1/0.1;
      switchTypes[0] = (int_T)1.0;
      idxOutSw[0] = ((int_T)0.0) - 1;
      switch_status[1] = 0;
      switch_status_init[1] = 0;
      gState[1] = (int_T) 0.0;
      yswitch[1] = 1/0.1;
      switchTypes[1] = (int_T)1.0;
      idxOutSw[1] = ((int_T)0.0) - 1;
      switch_status[2] = 0;
      switch_status_init[2] = 0;
      gState[2] = (int_T) 0.0;
      yswitch[2] = 1/0.1;
      switchTypes[2] = (int_T)1.0;
      idxOutSw[2] = ((int_T)0.0) - 1;
      switch_status[3] = 0;
      switch_status_init[3] = 0;
      gState[3] = (int_T) 0.0;
      yswitch[3] = 1/0.1;
      switchTypes[3] = (int_T)1.0;
      idxOutSw[3] = ((int_T)0.0) - 1;
      switch_status[4] = 0;
      switch_status_init[4] = 0;
      gState[4] = (int_T) 0.0;
      yswitch[4] = 1/0.01;
      switchTypes[4] = (int_T)2.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.2;
      switchTypes[5] = (int_T)3.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.2;
      switchTypes[6] = (int_T)3.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.2;
      switchTypes[7] = (int_T)3.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
      switch_status[8] = 0;
      switch_status_init[8] = 0;
      gState[8] = (int_T) 0.0;
      yswitch[8] = 1/0.2;
      switchTypes[8] = (int_T)3.0;
      idxOutSw[8] = ((int_T)0.0) - 1;
    }
  }

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  inv2_genC_X.Hw5_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw8' */
  inv2_genC_X.Hw8_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  inv2_genC_X.Hw5_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw8' */
  inv2_genC_X.Hw8_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  inv2_genC_X.Hw5_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw8' */
  inv2_genC_X.Hw8_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  inv2_genC_X.Hw5_CSTATE[3] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw8' */
  inv2_genC_X.Hw8_CSTATE[3] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
  inv2_genC_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1' */
  inv2_genC_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw3' */
  inv2_genC_X.Hw3_CSTATE[0] = 0.0;
  inv2_genC_X.Hw3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/PhaseShift3' */
  inv2_genC_X.PhaseShift3_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw7' */
  inv2_genC_X.Hw7_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Transfer Fcn' */
  inv2_genC_X.TransferFcn_CSTATE_n[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw7' */
  inv2_genC_X.Hw7_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Transfer Fcn' */
  inv2_genC_X.TransferFcn_CSTATE_n[1] = 0.0;

  /* InitializeConditions for Derivative: '<S16>/Derivative' */
  inv2_genC_DW.TimeStampA = (rtInf);
  inv2_genC_DW.TimeStampB = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/PhaseShift4' */
  inv2_genC_X.PhaseShift4_CSTATE = 0.0;
}

/* Model terminate function */
void inv2_genC_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S48>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S46>/DC'
   *  Constant: '<S50>/SwitchCurrents'
   */

  /* S-Function block: <S48>/State-Space */
  {
    /* Free memory */
    free(inv2_genC_DW.StateSpace_PWORK.AS);
    free(inv2_genC_DW.StateSpace_PWORK.BS);
    free(inv2_genC_DW.StateSpace_PWORK.CS);
    free(inv2_genC_DW.StateSpace_PWORK.DS);
    free(inv2_genC_DW.StateSpace_PWORK.DX_COL);
    free(inv2_genC_DW.StateSpace_PWORK.TMP2);
    free(inv2_genC_DW.StateSpace_PWORK.BD_COL);
    free(inv2_genC_DW.StateSpace_PWORK.TMP1);
    free(inv2_genC_DW.StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(inv2_genC_DW.StateSpace_PWORK.G_STATE);
    free(inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS);
    free(inv2_genC_DW.StateSpace_PWORK.SW_CHG);
    free(inv2_genC_DW.StateSpace_PWORK.SWITCH_STATUS_INIT);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
