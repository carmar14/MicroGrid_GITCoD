/*
 * File: PV_vsi.c
 *
 * Code generated for Simulink model 'PV_vsi'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jul 31 14:14:34 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PV_vsi.h"
#include "PV_vsi_private.h"

/* Block signals (auto storage) */
B_PV_vsi_T PV_vsi_B;

/* Continuous states */
X_PV_vsi_T PV_vsi_X;

/* Block states (auto storage) */
DW_PV_vsi_T PV_vsi_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_PV_vsi_T PV_vsi_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_PV_vsi_T PV_vsi_Y;

/* Real-time model */
RT_MODEL_PV_vsi_T PV_vsi_M_;
RT_MODEL_PV_vsi_T *const PV_vsi_M = &PV_vsi_M_;

//Funciones creadas por el usuario
void set_I(double I){
	PV_vsi_U.Corriente=I;
}

double get_SOC(void){
	return PV_vsi_Y.SOC;
	}
	
double get_Ivsi(void){
	return PV_vsi_Y.I_vsi;
	}



/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PV_vsi_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  PV_vsi_step();
  PV_vsi_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  PV_vsi_step();
  PV_vsi_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  PV_vsi_step();
  PV_vsi_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

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
void PV_vsi_step(void)
{
  /* local block i/o variables */
  real_T rtb_DataTypeConversion2;
  real_T rtb_Gain2_p;
  if (rtmIsMajorTimeStep(PV_vsi_M)) {
    /* set solver stop time */
    if (!(PV_vsi_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&PV_vsi_M->solverInfo,
                            ((PV_vsi_M->Timing.clockTickH0 + 1) *
        PV_vsi_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&PV_vsi_M->solverInfo, ((PV_vsi_M->Timing.clockTick0
        + 1) * PV_vsi_M->Timing.stepSize0 + PV_vsi_M->Timing.clockTickH0 *
        PV_vsi_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PV_vsi_M)) {
    PV_vsi_M->Timing.t[0] = rtsiGetT(&PV_vsi_M->solverInfo);
  }

  {
    real_T *lastU;
    int32_T a;
    real_T rtb_R4;
    real_T rtb_Switch2;
    real_T rtb_Currentfilter5;
    real_T rtb_Gain;
    real_T rtb_R3;
    if (rtmIsMajorTimeStep(PV_vsi_M)) {
      /* Memory: '<S49>/it init1' */
      rtb_R4 = PV_vsi_DW.itinit1_PreviousInput;

      /* Gain: '<S49>/R2' incorporates:
       *  Memory: '<S49>/it init1'
       */
      rtb_Switch2 = 0.9999 * PV_vsi_DW.itinit1_PreviousInput;

      /* DiscreteTransferFcn: '<S49>/Current filter5' */
      rtb_Currentfilter5 = 0.0002999550044996413 *
        PV_vsi_DW.Currentfilter5_states;

      /* DataTypeConversion: '<S49>/Data Type Conversion2' incorporates:
       *  Constant: '<S52>/Constant'
       *  RelationalOperator: '<S52>/Compare'
       */
      rtb_DataTypeConversion2 = (rtb_Currentfilter5 > 0.0);

      /* DiscreteIntegrator: '<S49>/int(i)' incorporates:
       *  Memory: '<S49>/it init'
       */
      if (PV_vsi_DW.inti_IC_LOADING != 0) {
        PV_vsi_DW.inti_DSTATE = PV_vsi_DW.itinit_PreviousInput;
        if (PV_vsi_DW.inti_DSTATE >= 3722.3999999999905) {
          PV_vsi_DW.inti_DSTATE = 3722.3999999999905;
        } else {
          if (PV_vsi_DW.inti_DSTATE <= (rtMinusInf)) {
            PV_vsi_DW.inti_DSTATE = (rtMinusInf);
          }
        }
      }

      if ((rtb_DataTypeConversion2 > 0.0) && (PV_vsi_DW.inti_PrevResetState <= 0))
      {
        PV_vsi_DW.inti_DSTATE = PV_vsi_DW.itinit_PreviousInput;
        if (PV_vsi_DW.inti_DSTATE >= 3722.3999999999905) {
          PV_vsi_DW.inti_DSTATE = 3722.3999999999905;
        } else {
          if (PV_vsi_DW.inti_DSTATE <= (rtMinusInf)) {
            PV_vsi_DW.inti_DSTATE = (rtMinusInf);
          }
        }
      }

      if (PV_vsi_DW.inti_DSTATE >= 3722.3999999999905) {
        PV_vsi_DW.inti_DSTATE = 3722.3999999999905;
      } else {
        if (PV_vsi_DW.inti_DSTATE <= (rtMinusInf)) {
          PV_vsi_DW.inti_DSTATE = (rtMinusInf);
        }
      }

      /* Gain: '<S49>/Gain' incorporates:
       *  DiscreteIntegrator: '<S49>/int(i)'
       */
      rtb_Gain = 0.00027777777777777778 * PV_vsi_DW.inti_DSTATE;

      /* Switch: '<S59>/Switch2' incorporates:
       *  RelationalOperator: '<S59>/LowerRelop1'
       */
      if (!(rtb_Gain > rtb_Switch2)) {
        /* Switch: '<S59>/Switch' incorporates:
         *  Constant: '<S49>/Constant9'
         *  RelationalOperator: '<S59>/UpperRelop'
         */
        if (rtb_Gain < 0.0) {
          rtb_Switch2 = 0.0;
        } else {
          rtb_Switch2 = rtb_Gain;
        }

        /* End of Switch: '<S59>/Switch' */
      }

      /* End of Switch: '<S59>/Switch2' */

      /* Gain: '<S49>/R3' incorporates:
       *  Memory: '<S49>/it init1'
       */
      rtb_R3 = 0.9999 * PV_vsi_DW.itinit1_PreviousInput;

      /* Switch: '<S60>/Switch2' incorporates:
       *  RelationalOperator: '<S60>/LowerRelop1'
       */
      if (!(rtb_Gain > rtb_R3)) {
        /* Fcn: '<S49>/Fcn6' */
        rtb_R3 = -rtb_R3 * 0.999 * 0.1 * 0.9999;

        /* Switch: '<S60>/Switch' incorporates:
         *  RelationalOperator: '<S60>/UpperRelop'
         */
        if (!(rtb_Gain < rtb_R3)) {
          rtb_R3 = rtb_Gain;
        }

        /* End of Switch: '<S60>/Switch' */
      }

      /* End of Switch: '<S60>/Switch2' */

      /* Sum: '<S49>/Add3' incorporates:
       *  Constant: '<S49>/Constant'
       *  Constant: '<S53>/Constant'
       *  Fcn: '<S49>/E_NL'
       *  Fcn: '<S49>/E_dyn Discharge'
       *  Fcn: '<S49>/Fcn5'
       *  Fcn: '<S54>/Charge Li-Ion'
       *  Fcn: '<S55>/Li-Ion'
       *  Memory: '<S49>/it init1'
       *  Product: '<S54>/Product'
       *  RelationalOperator: '<S53>/Compare'
       *  Sum: '<S49>/Add2'
       */
      rtb_Gain = ((((-rtb_DataTypeConversion2 * 0.0605295518538322 *
                     rtb_Currentfilter5 * PV_vsi_DW.itinit1_PreviousInput /
                     (PV_vsi_DW.itinit1_PreviousInput - rtb_Switch2) +
                     -0.0605295518538322 * PV_vsi_DW.itinit1_PreviousInput /
                     (PV_vsi_DW.itinit1_PreviousInput - rtb_Switch2) *
                     rtb_Switch2) + -(real_T)(rtb_Currentfilter5 < 0.0) *
                    0.0605295518538322 * rtb_Currentfilter5 *
                    PV_vsi_DW.itinit1_PreviousInput /
                    (PV_vsi_DW.itinit1_PreviousInput * 0.1 + rtb_R3)) + exp
                   (-61.061946632469265 * rtb_Switch2) * 83.400845004248509) +
                  -0.0 * rtb_Switch2) + 1206.9850549957514;

      /* Switch: '<S58>/Switch2' incorporates:
       *  Constant: '<S49>/Constant1'
       *  RelationalOperator: '<S58>/LowerRelop1'
       */
      if (rtb_Gain > 2413.9701099915028) {
        PV_vsi_B.Switch2 = 2413.9701099915028;
      } else {
        /* Gain: '<S49>/R1' */
        rtb_Currentfilter5 *= 0.05;

        /* Switch: '<S58>/Switch' incorporates:
         *  RelationalOperator: '<S58>/UpperRelop'
         */
        if (rtb_Gain < rtb_Currentfilter5) {
          PV_vsi_B.Switch2 = rtb_Currentfilter5;
        } else {
          PV_vsi_B.Switch2 = rtb_Gain;
        }

        /* End of Switch: '<S58>/Switch' */
      }

      /* End of Switch: '<S58>/Switch2' */

      /* Gain: '<Root>/Gain' incorporates:
       *  Inport: '<Root>/Corriente'
       */
      PV_vsi_B.Gain = 0.1 * PV_vsi_U.Corriente;

      /* S-Function (sfun_spssw_discc): '<S70>/State-Space' incorporates:
       *  Constant: '<S33>/eee'
       *  Constant: '<S35>/eee'
       *  Constant: '<S37>/eee'
       *  Constant: '<S39>/eee'
       *  Constant: '<S72>/SwitchCurrents'
       */

      /* S-Function block: <S70>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*) PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*) PV_vsi_DW.StateSpace_PWORK.SW_CHG;
        int_T *gState = (int_T*) PV_vsi_DW.StateSpace_PWORK.G_STATE;
        real_T *yswitch = (real_T*)PV_vsi_DW.StateSpace_PWORK.Y_SWITCH;
        int_T *switchTypes = (int_T*) PV_vsi_DW.StateSpace_PWORK.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*) PV_vsi_DW.StateSpace_PWORK.IDX_OUT_SW;
        real_T *DxCol = (real_T*)PV_vsi_DW.StateSpace_PWORK.DX_COL;
        real_T *tmp2 = (real_T*)PV_vsi_DW.StateSpace_PWORK.TMP2;
        real_T *BDcol = (real_T*)PV_vsi_DW.StateSpace_PWORK.BD_COL;
        real_T *tmp1 = (real_T*)PV_vsi_DW.StateSpace_PWORK.TMP1;
        real_T *uswlast = (real_T*)PV_vsi_DW.StateSpace_PWORK.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 9 * sizeof(int_T));
        memcpy(uswlast, &PV_vsi_B.StateSpace_o1[0], 9*sizeof(real_T));
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
            real_T *Cs = (real_T*)PV_vsi_DW.StateSpace_PWORK.CS;
            real_T *Ds = (real_T*)PV_vsi_DW.StateSpace_PWORK.DS;

            {
              int_T i1;
              real_T *y0 = &PV_vsi_B.StateSpace_o1[0];
              for (i1=0; i1 < 13; i1++) {
                accum = 0.0;

                {
                  int_T i2;
                  real_T *xd = &PV_vsi_DW.StateSpace_DSTATE[0];
                  for (i2=0; i2 < 7; i2++) {
                    accum += *(Cs++) * xd[i2];
                  }
                }

                {
                  int_T i2;
                  const real_T *u0 = PV_vsi_ConstP.SwitchCurrents_Value;
                  for (i2=0; i2 < 9; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  accum += *(Ds++) * PV_vsi_B.Switch2;
                  accum += *(Ds++) * PV_vsi_B.Gain;
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
              real_T *y0 = &PV_vsi_B.StateSpace_o1[0];
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
            real_T *As = (real_T*)PV_vsi_DW.StateSpace_PWORK.AS;
            real_T *Cs = (real_T*)PV_vsi_DW.StateSpace_PWORK.CS;
            real_T *Bs = (real_T*)PV_vsi_DW.StateSpace_PWORK.BS;
            real_T *Ds = (real_T*)PV_vsi_DW.StateSpace_PWORK.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 9; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*16]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 13; i2++) {
                      DxCol[i2]= Ds[i2 * 15 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;

                  {
                    int_T i2;
                    for (i2=0; i2 < 7; i2++) {
                      BDcol[i2]= Bs[i2 * 15 + i1]*a1;
                    }
                  }

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 7], 7 * sizeof(real_T));
                  memset(&Cs[i1 * 7], '\0', 7 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 15], 15 * sizeof(real_T));
                  memset(&Ds[i1 * 15], '\0', 15 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 13; i2++) {
                      a1 = DxCol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 7; i3++) {
                          Cs[i2 * 7 + i3] += a1 * tmp1[i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 15; i3++) {
                          Ds[i2 * 15 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 7; i2++) {
                      a1 = BDcol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 7; i3++) {
                          As[i2 * 7 + i3] += a1 * Cs[i1 * 7 + i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 15; i3++) {
                          Bs[i2 * 15 + i3] += a1 * Ds[i1 * 15 + i3];
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
          real_T *Cs = (real_T*)PV_vsi_DW.StateSpace_PWORK.CS;
          real_T *Ds = (real_T*)PV_vsi_DW.StateSpace_PWORK.DS;

          {
            int_T i1;
            real_T *y0 = &PV_vsi_B.StateSpace_o1[0];
            for (i1=0; i1 < 13; i1++) {
              accum = 0.0;

              {
                int_T i2;
                real_T *xd = &PV_vsi_DW.StateSpace_DSTATE[0];
                for (i2=0; i2 < 7; i2++) {
                  accum += *(Cs++) * xd[i2];
                }
              }

              {
                int_T i2;
                const real_T *u0 = PV_vsi_ConstP.SwitchCurrents_Value;
                for (i2=0; i2 < 9; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                accum += *(Ds++) * PV_vsi_B.Switch2;
                accum += *(Ds++) * PV_vsi_B.Gain;
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
          real_T *y1 = &PV_vsi_B.StateSpace_o2[0];
          for (i1=0; i1 < 9; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }
    }

    /* TransferFcn: '<S1>/Transfer Fcn' */
    PV_vsi_B.TransferFcn = 0.0;
    PV_vsi_B.TransferFcn += 1.0E+6 * PV_vsi_X.TransferFcn_CSTATE;

    /* Outport: '<Root>/I_vsi' */
    PV_vsi_Y.I_vsi = PV_vsi_B.TransferFcn;

    /* TransferFcn: '<S1>/Transfer Fcn1' */
    PV_vsi_B.TransferFcn1 = 0.0;
    PV_vsi_B.TransferFcn1 += 1.0E+6 * PV_vsi_X.TransferFcn1_CSTATE;

    /* TransferFcn: '<S1>/Transfer Fcn2' */
    PV_vsi_B.TransferFcn2 = 0.0;
    PV_vsi_B.TransferFcn2 += 1.0E+6 * PV_vsi_X.TransferFcn2_CSTATE;

    /* StateSpace: '<Root>/Hw2' */
    rtb_Gain = 1.0000000000000002 * PV_vsi_X.Hw2_CSTATE[1];

    /* Sin: '<Root>/Sine Wave' */
    PV_vsi_B.Vc_ref = sin(376.99111843077515 * PV_vsi_M->Timing.t[0]) * 170.0;

    /* Derivative: '<S4>/Derivative' */
    if ((PV_vsi_DW.TimeStampA >= PV_vsi_M->Timing.t[0]) && (PV_vsi_DW.TimeStampB
         >= PV_vsi_M->Timing.t[0])) {
      rtb_Currentfilter5 = 0.0;
    } else {
      rtb_Currentfilter5 = PV_vsi_DW.TimeStampA;
      lastU = &PV_vsi_DW.LastUAtTimeA;
      if (PV_vsi_DW.TimeStampA < PV_vsi_DW.TimeStampB) {
        if (PV_vsi_DW.TimeStampB < PV_vsi_M->Timing.t[0]) {
          rtb_Currentfilter5 = PV_vsi_DW.TimeStampB;
          lastU = &PV_vsi_DW.LastUAtTimeB;
        }
      } else {
        if (PV_vsi_DW.TimeStampA >= PV_vsi_M->Timing.t[0]) {
          rtb_Currentfilter5 = PV_vsi_DW.TimeStampB;
          lastU = &PV_vsi_DW.LastUAtTimeB;
        }
      }

      rtb_Currentfilter5 = (PV_vsi_B.Vc_ref - *lastU) / (PV_vsi_M->Timing.t[0] -
        rtb_Currentfilter5);
    }

    /* End of Derivative: '<S4>/Derivative' */

    /* Sum: '<S4>/Sum6' incorporates:
     *  Constant: '<S4>/SwitchingFilterCapacitor1'
     *  Product: '<S4>/Product1'
     */
    PV_vsi_B.Inductor_refCurrent = 0.00061 * rtb_Currentfilter5 + rtb_Gain;

    /* Sum: '<S4>/Sum8' incorporates:
     *  StateSpace: '<Root>/Hw5'
     *  StateSpace: '<S4>/Hi_Pass1'
     *  Sum: '<S4>/Sum7'
     */
    PV_vsi_B.InductorErrorCurrent = (-PV_vsi_X.Hi_Pass1_CSTATE +
      PV_vsi_B.Inductor_refCurrent) - (1.0000000000000002 * PV_vsi_X.Hw5_CSTATE
      [1] + rtb_Gain);

    /* Sum: '<S1>/Sum2' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Constant: '<S4>/Constant2'
     *  Gain: '<S4>/Gain2'
     *  Sum: '<S4>/Sum5'
     *  Sum: '<S4>/Sum9'
     *  TransferFcn: '<S4>/Transfer Fcn1'
     */
    rtb_Gain = (((2.0 * PV_vsi_X.TransferFcn1_CSTATE_h[0] + 0.0 *
                  PV_vsi_X.TransferFcn1_CSTATE_h[1]) + 0.002 *
                 PV_vsi_B.InductorErrorCurrent) + -0.004) + 0.5;
    if (rtmIsMajorTimeStep(PV_vsi_M)) {
      /* Gain: '<S1>/Gain' incorporates:
       *  Constant: '<S43>/Constant'
       *  Constant: '<S45>/Constant2'
       *  DataTypeConversion: '<S10>/Data Type Conversion'
       *  DigitalClock: '<S45>/Digital Clock'
       *  Fcn: '<S10>/Fcn'
       *  Fcn: '<S45>/Fcn'
       *  Gain: '<S45>/1\ib1'
       *  Logic: '<S10>/Logical Operator'
       *  Math: '<S45>/Math Function'
       *  RelationalOperator: '<S10>/Relational Operator'
       *  RelationalOperator: '<S43>/Compare'
       */
      rtb_Gain = (real_T)((rtb_Gain != 0.0) && (rtb_Gain >= ((12000.0 *
        rt_remd_snf((((PV_vsi_M->Timing.clockTick1+PV_vsi_M->Timing.clockTickH1*
                       4294967296.0)) * 1.0E-6), 8.3333333333333331E-5) * 2.0 -
        1.0) + 1.0) * 0.5)) * 15.0;

      /* Product: '<S11>/Product' incorporates:
       *  Step: '<S11>/Step'
       */
      PV_vsi_B.Product = (real_T)!((((PV_vsi_M->Timing.clockTick1+
        PV_vsi_M->Timing.clockTickH1* 4294967296.0)) * 1.0E-6) < 0.0) * rtb_Gain;

      /* MATLAB Function: '<S1>/not_pwm' */
      /* MATLAB Function '1Ph_Inverter_bio1/not_pwm': '<S14>:1' */
      /* '<S14>:1:4' if(u==0 || u<0) */
      if (rtb_Gain == 0.0) {
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
      PV_vsi_B.Product_m = (real_T)!((((PV_vsi_M->Timing.clockTick1+
        PV_vsi_M->Timing.clockTickH1* 4294967296.0)) * 1.0E-6) < 0.0) * (real_T)
        a;

      /* Gain: '<S49>/R4' */
      rtb_R4 *= 0.96711798839458663;

      /* Fcn: '<S49>/Fcn1' */
      rtb_R4 = (1.0 - rtb_Switch2 / rtb_R4) * 100.0;

      /* Saturate: '<S49>/Saturation' */
      if (rtb_R4 > 100.0) {
        /* Outport: '<Root>/SOC' */
        PV_vsi_Y.SOC = 100.0;
      } else if (rtb_R4 < 0.0) {
        /* Outport: '<Root>/SOC' */
        PV_vsi_Y.SOC = 0.0;
      } else {
        /* Outport: '<Root>/SOC' */
        PV_vsi_Y.SOC = rtb_R4;
      }

      /* End of Saturate: '<S49>/Saturation' */

      /* Gain: '<S49>/Gain2' */
      rtb_Gain2_p = 3600.0 * rtb_Switch2;
    }

    /* Lookup: '<S16>/Look-Up Table' incorporates:
     *  Clock: '<S16>/Clock'
     */
    PV_vsi_B.LookUpTable = rt_Lookup(PV_vsi_ConstP.LookUpTable_XData, 5,
      PV_vsi_M->Timing.t[0], PV_vsi_ConstP.LookUpTable_YData);

    /* Step: '<S1>/Step' */
    PV_vsi_B.Step = !(PV_vsi_M->Timing.t[0] < 0.0);
  }

  if (rtmIsMajorTimeStep(PV_vsi_M)) {
    real_T *lastU;
    if (rtmIsMajorTimeStep(PV_vsi_M)) {
      /* Update for Memory: '<S49>/it init1' incorporates:
       *  Constant: '<S49>/Constant12'
       */
      PV_vsi_DW.itinit1_PreviousInput = 1.0339999999999974;

      /* Update for DiscreteTransferFcn: '<S49>/Current filter5' */
      PV_vsi_DW.Currentfilter5_states = PV_vsi_B.StateSpace_o1[10] -
        -0.99970004499550036 * PV_vsi_DW.Currentfilter5_states;

      /* Update for Memory: '<S49>/it init' */
      PV_vsi_DW.itinit_PreviousInput = rtb_Gain2_p;

      /* Update for DiscreteIntegrator: '<S49>/int(i)' */
      PV_vsi_DW.inti_IC_LOADING = 0U;
      PV_vsi_DW.inti_DSTATE += 1.0E-6 * PV_vsi_B.StateSpace_o1[10];
      if (PV_vsi_DW.inti_DSTATE >= 3722.3999999999905) {
        PV_vsi_DW.inti_DSTATE = 3722.3999999999905;
      } else {
        if (PV_vsi_DW.inti_DSTATE <= (rtMinusInf)) {
          PV_vsi_DW.inti_DSTATE = (rtMinusInf);
        }
      }

      if (rtb_DataTypeConversion2 > 0.0) {
        PV_vsi_DW.inti_PrevResetState = 1;
      } else if (rtb_DataTypeConversion2 < 0.0) {
        PV_vsi_DW.inti_PrevResetState = -1;
      } else if (rtb_DataTypeConversion2 == 0.0) {
        PV_vsi_DW.inti_PrevResetState = 0;
      } else {
        PV_vsi_DW.inti_PrevResetState = 2;
      }

      /* End of Update for DiscreteIntegrator: '<S49>/int(i)' */

      /* Update for S-Function (sfun_spssw_discc): '<S70>/State-Space' incorporates:
       *  Constant: '<S33>/eee'
       *  Constant: '<S35>/eee'
       *  Constant: '<S37>/eee'
       *  Constant: '<S39>/eee'
       *  Constant: '<S72>/SwitchCurrents'
       */

      /* S-Function block: <S70>/State-Space */
      {
        const real_T *As = (real_T*)PV_vsi_DW.StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)PV_vsi_DW.StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)PV_vsi_DW.StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        {
          int_T i1;
          real_T *xd = &PV_vsi_DW.StateSpace_DSTATE[0];
          for (i1=0; i1 < 7; i1++) {
            accum = 0.0;

            {
              int_T i2;
              real_T *xd = &PV_vsi_DW.StateSpace_DSTATE[0];
              for (i2=0; i2 < 7; i2++) {
                accum += *(As++) * xd[i2];
              }
            }

            {
              int_T i2;
              const real_T *u0 = PV_vsi_ConstP.SwitchCurrents_Value;
              for (i2=0; i2 < 9; i2++) {
                accum += *(Bs++) * u0[i2];
              }

              accum += *(Bs++) * PV_vsi_B.Switch2;
              accum += *(Bs++) * PV_vsi_B.Gain;
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
          real_T *xd = &PV_vsi_DW.StateSpace_DSTATE[0];
          for (i1=0; i1 < 7; i1++) {
            xd[i1] = xtmp[i1];
          }
        }

        {
          int_T *gState = (int_T*)PV_vsi_DW.StateSpace_PWORK.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T) PV_vsi_B.Product;
          *(gState++) = (int_T) PV_vsi_B.Product_m;
          *(gState++) = (int_T) PV_vsi_B.Product;
          *(gState++) = (int_T) PV_vsi_B.Product_m;
          *(gState++) = (int_T) PV_vsi_B.Step;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }
    }

    /* Update for Derivative: '<S4>/Derivative' */
    if (PV_vsi_DW.TimeStampA == (rtInf)) {
      PV_vsi_DW.TimeStampA = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeA;
    } else if (PV_vsi_DW.TimeStampB == (rtInf)) {
      PV_vsi_DW.TimeStampB = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeB;
    } else if (PV_vsi_DW.TimeStampA < PV_vsi_DW.TimeStampB) {
      PV_vsi_DW.TimeStampA = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeA;
    } else {
      PV_vsi_DW.TimeStampB = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeB;
    }

    *lastU = PV_vsi_B.Vc_ref;

    /* End of Update for Derivative: '<S4>/Derivative' */

    /* Update for Derivative: '<S16>/Derivative' */
    if (PV_vsi_DW.TimeStampA_f == (rtInf)) {
      PV_vsi_DW.TimeStampA_f = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeA_e;
    } else if (PV_vsi_DW.TimeStampB_h == (rtInf)) {
      PV_vsi_DW.TimeStampB_h = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeB_b;
    } else if (PV_vsi_DW.TimeStampA_f < PV_vsi_DW.TimeStampB_h) {
      PV_vsi_DW.TimeStampA_f = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeA_e;
    } else {
      PV_vsi_DW.TimeStampB_h = PV_vsi_M->Timing.t[0];
      lastU = &PV_vsi_DW.LastUAtTimeB_b;
    }

    *lastU = PV_vsi_B.LookUpTable;

    /* End of Update for Derivative: '<S16>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PV_vsi_M)) {
    rt_ertODEUpdateContinuousStates(&PV_vsi_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PV_vsi_M->Timing.clockTick0)) {
      ++PV_vsi_M->Timing.clockTickH0;
    }

    PV_vsi_M->Timing.t[0] = rtsiGetSolverStopTime(&PV_vsi_M->solverInfo);

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
      PV_vsi_M->Timing.clockTick1++;
      if (!PV_vsi_M->Timing.clockTick1) {
        PV_vsi_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PV_vsi_derivatives(void)
{
  XDot_PV_vsi_T *_rtXdot;
  _rtXdot = ((XDot_PV_vsi_T *) PV_vsi_M->derivs);

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -1.0E+6 * PV_vsi_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += PV_vsi_B.StateSpace_o1[11];

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -1.0E+6 * PV_vsi_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += PV_vsi_B.StateSpace_o1[9];

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE = 0.0;
  _rtXdot->TransferFcn2_CSTATE += -1.0E+6 * PV_vsi_X.TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += PV_vsi_B.StateSpace_o1[12];

  /* Derivatives for StateSpace: '<Root>/Hw2' */
  _rtXdot->Hw2_CSTATE[0] = 0.0;
  _rtXdot->Hw2_CSTATE[1] = 0.0;
  _rtXdot->Hw2_CSTATE[0] += -76179.573297837138 * PV_vsi_X.Hw2_CSTATE[0];
  _rtXdot->Hw2_CSTATE[0] += -43982.2971502571 * PV_vsi_X.Hw2_CSTATE[1];
  _rtXdot->Hw2_CSTATE[1] += 43982.297150257094 * PV_vsi_X.Hw2_CSTATE[0];
  _rtXdot->Hw2_CSTATE[0] += 43982.2971502571 * PV_vsi_B.TransferFcn;

  /* Derivatives for StateSpace: '<S4>/Hi_Pass1' */
  _rtXdot->Hi_Pass1_CSTATE = 0.0;
  _rtXdot->Hi_Pass1_CSTATE += -6.2831853071795862 * PV_vsi_X.Hi_Pass1_CSTATE;
  _rtXdot->Hi_Pass1_CSTATE += 6.2831853071795862 * PV_vsi_B.Inductor_refCurrent;

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[0] = 0.0;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_h[0] = 0.0;
  _rtXdot->TransferFcn1_CSTATE_h[0] += -2.0 * PV_vsi_X.TransferFcn1_CSTATE_h[0];

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[1] = 0.0;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_h[1] = 0.0;
  _rtXdot->TransferFcn1_CSTATE_h[0] += -142122.30337568672 *
    PV_vsi_X.TransferFcn1_CSTATE_h[1];

  /* Derivatives for StateSpace: '<Root>/Hw5' */
  _rtXdot->Hw5_CSTATE[0] += -76179.573297837138 * PV_vsi_X.Hw5_CSTATE[0];
  _rtXdot->Hw5_CSTATE[0] += -43982.2971502571 * PV_vsi_X.Hw5_CSTATE[1];
  _rtXdot->Hw5_CSTATE[1] += 43982.297150257094 * PV_vsi_X.Hw5_CSTATE[0];
  _rtXdot->Hw5_CSTATE[0] += 43982.2971502571 * PV_vsi_B.TransferFcn2;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_h[1] += PV_vsi_X.TransferFcn1_CSTATE_h[0];
  _rtXdot->TransferFcn1_CSTATE_h[0] += PV_vsi_B.InductorErrorCurrent;

  /* Derivatives for StateSpace: '<Root>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] = 0.0;
  _rtXdot->Hw6_CSTATE[1] = 0.0;
  _rtXdot->Hw6_CSTATE[0] += -76179.573297837138 * PV_vsi_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += -43982.2971502571 * PV_vsi_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[1] += 43982.297150257094 * PV_vsi_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += 43982.2971502571 * PV_vsi_B.TransferFcn1;
}

/* Model initialize function */
void PV_vsi_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PV_vsi_M, 0,
                sizeof(RT_MODEL_PV_vsi_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PV_vsi_M->solverInfo, &PV_vsi_M->Timing.simTimeStep);
    rtsiSetTPtr(&PV_vsi_M->solverInfo, &rtmGetTPtr(PV_vsi_M));
    rtsiSetStepSizePtr(&PV_vsi_M->solverInfo, &PV_vsi_M->Timing.stepSize0);
    rtsiSetdXPtr(&PV_vsi_M->solverInfo, &PV_vsi_M->derivs);
    rtsiSetContStatesPtr(&PV_vsi_M->solverInfo, (real_T **)
                         &PV_vsi_M->contStates);
    rtsiSetNumContStatesPtr(&PV_vsi_M->solverInfo,
      &PV_vsi_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PV_vsi_M->solverInfo,
      &PV_vsi_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PV_vsi_M->solverInfo,
      &PV_vsi_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PV_vsi_M->solverInfo,
      &PV_vsi_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PV_vsi_M->solverInfo, (&rtmGetErrorStatus(PV_vsi_M)));
    rtsiSetRTModelPtr(&PV_vsi_M->solverInfo, PV_vsi_M);
  }

  rtsiSetSimTimeStep(&PV_vsi_M->solverInfo, MAJOR_TIME_STEP);
  PV_vsi_M->intgData.y = PV_vsi_M->odeY;
  PV_vsi_M->intgData.f[0] = PV_vsi_M->odeF[0];
  PV_vsi_M->intgData.f[1] = PV_vsi_M->odeF[1];
  PV_vsi_M->intgData.f[2] = PV_vsi_M->odeF[2];
  PV_vsi_M->intgData.f[3] = PV_vsi_M->odeF[3];
  PV_vsi_M->contStates = ((X_PV_vsi_T *) &PV_vsi_X);
  rtsiSetSolverData(&PV_vsi_M->solverInfo, (void *)&PV_vsi_M->intgData);
  rtsiSetSolverName(&PV_vsi_M->solverInfo,"ode4");
  rtmSetTPtr(PV_vsi_M, &PV_vsi_M->Timing.tArray[0]);
  PV_vsi_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  (void) memset(((void *) &PV_vsi_B), 0,
                sizeof(B_PV_vsi_T));

  /* states (continuous) */
  {
    (void) memset((void *)&PV_vsi_X, 0,
                  sizeof(X_PV_vsi_T));
  }

  /* states (dwork) */
  (void) memset((void *)&PV_vsi_DW, 0,
                sizeof(DW_PV_vsi_T));

  /* external inputs */
  PV_vsi_U.Corriente = 0.0;

  /* external outputs */
  (void) memset((void *)&PV_vsi_Y, 0,
                sizeof(ExtY_PV_vsi_T));

  /* Start for S-Function (sfun_spssw_discc): '<S70>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S72>/SwitchCurrents'
   */

  /* S-Function block: <S70>/State-Space */
  {
    PV_vsi_DW.StateSpace_PWORK.AS = (real_T*)calloc(7 * 7, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.BS = (real_T*)calloc(7 * 15, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.CS = (real_T*)calloc(13 * 7, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.DS = (real_T*)calloc(13 * 15, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(13, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(15, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(7, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(7, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(7, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS = (int_T*)calloc(9, sizeof(int_T));
    PV_vsi_DW.StateSpace_PWORK.SW_CHG = (int_T*)calloc(9, sizeof(int_T));
    PV_vsi_DW.StateSpace_PWORK.G_STATE = (int_T*)calloc(9, sizeof(int_T));
    PV_vsi_DW.StateSpace_PWORK.Y_SWITCH = (real_T*)calloc(9, sizeof(real_T));
    PV_vsi_DW.StateSpace_PWORK.SWITCH_TYPES = (int_T*)calloc(9, sizeof(int_T));
    PV_vsi_DW.StateSpace_PWORK.IDX_OUT_SW = (int_T*)calloc(9, sizeof(int_T));
    PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS_INIT = (int_T*)calloc(9, sizeof
      (int_T));
    PV_vsi_DW.StateSpace_PWORK.USWLAST = (real_T*)calloc(9, sizeof(real_T));
  }

  /* InitializeConditions for Memory: '<S49>/it init1' */
  PV_vsi_DW.itinit1_PreviousInput = 1.0339999999999974;

  /* InitializeConditions for DiscreteIntegrator: '<S49>/int(i)' */
  PV_vsi_DW.inti_IC_LOADING = 1U;
  PV_vsi_DW.inti_PrevResetState = 2;

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S70>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S72>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)PV_vsi_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)PV_vsi_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)PV_vsi_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)PV_vsi_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&PV_vsi_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 7; i++) {
      X0[i] = (PV_vsi_ConstP.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<7; i++) {
      for (j=0; j<7; j++)
        As[i*7 + j] = (PV_vsi_ConstP.StateSpace_AS_param[i + j*7]);
      for (j=0; j<15; j++)
        Bs[i*15 + j] = (PV_vsi_ConstP.StateSpace_BS_param[i + j*7]);
    }

    /* Copy and transpose C */
    for (i=0; i<13; i++) {
      for (j=0; j<7; j++)
        Cs[i*7 + j] = (PV_vsi_ConstP.StateSpace_CS_param[i + j*13]);
    }

    /* Copy and transpose D */
    for (i=0; i<13; i++) {
      for (j=0; j<15; j++)
        Ds[i*15 + j] = (PV_vsi_ConstP.StateSpace_DS_param[i + j*13]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*) PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)PV_vsi_DW.StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)PV_vsi_DW.StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)PV_vsi_DW.StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)PV_vsi_DW.StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;

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

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
  PV_vsi_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1' */
  PV_vsi_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  PV_vsi_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw2' */
  PV_vsi_X.Hw2_CSTATE[0] = 0.0;
  PV_vsi_X.Hw2_CSTATE[1] = 0.0;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  PV_vsi_DW.TimeStampA = (rtInf);
  PV_vsi_DW.TimeStampB = (rtInf);

  /* InitializeConditions for StateSpace: '<S4>/Hi_Pass1' */
  PV_vsi_X.Hi_Pass1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S16>/Derivative' */
  PV_vsi_DW.TimeStampA_f = (rtInf);
  PV_vsi_DW.TimeStampB_h = (rtInf);

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  PV_vsi_X.Hw5_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn1' */
  PV_vsi_X.TransferFcn1_CSTATE_h[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw6' */
  PV_vsi_X.Hw6_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw5' */
  PV_vsi_X.Hw5_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn1' */
  PV_vsi_X.TransferFcn1_CSTATE_h[1] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Hw6' */
  PV_vsi_X.Hw6_CSTATE[1] = 0.0;
}

/* Model terminate function */
void PV_vsi_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S70>/State-Space' incorporates:
   *  Constant: '<S33>/eee'
   *  Constant: '<S35>/eee'
   *  Constant: '<S37>/eee'
   *  Constant: '<S39>/eee'
   *  Constant: '<S72>/SwitchCurrents'
   */

  /* S-Function block: <S70>/State-Space */
  {
    /* Free memory */
    free(PV_vsi_DW.StateSpace_PWORK.AS);
    free(PV_vsi_DW.StateSpace_PWORK.BS);
    free(PV_vsi_DW.StateSpace_PWORK.CS);
    free(PV_vsi_DW.StateSpace_PWORK.DS);
    free(PV_vsi_DW.StateSpace_PWORK.DX_COL);
    free(PV_vsi_DW.StateSpace_PWORK.TMP2);
    free(PV_vsi_DW.StateSpace_PWORK.BD_COL);
    free(PV_vsi_DW.StateSpace_PWORK.TMP1);
    free(PV_vsi_DW.StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(PV_vsi_DW.StateSpace_PWORK.G_STATE);
    free(PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS);
    free(PV_vsi_DW.StateSpace_PWORK.SW_CHG);
    free(PV_vsi_DW.StateSpace_PWORK.SWITCH_STATUS_INIT);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
