/*
 * File: carga.c
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

#include "carga.h"
#include "carga_private.h"

/* Block signals (auto storage) */
B_carga_T carga_B;

/* Continuous states */
X_carga_T carga_X;

/* Block states (auto storage) */
DW_carga_T carga_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_carga_T carga_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_carga_T carga_Y;


//Funciones generadas por el programador

void set_I_die(double I_die){
	carga_U.I_die=I_die;
}

void set_I_bio(double I_bio){
	carga_U.I_bio=I_bio;
}

void set_I_pv(double I_pv){
	carga_U.I_pv=I_pv;
}
double get_V_load(void){
	return carga_Y.Corriente_load;
	}
	
double get_P(void){
	return carga_Y.P_meas;
	}
double get_Q(void){
	return carga_Y.Q_meas;
}

/* Real-time model */
RT_MODEL_carga_T carga_M_;
RT_MODEL_carga_T *const carga_M = &carga_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  carga_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  carga_step();
  carga_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  carga_step();
  carga_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  carga_step();
  carga_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = sqrt(y * y + 1.0) * a;
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void carga_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_a;
  real_T rtb_TransportDelay_m;
  real_T rtb_integrator_h;
  real_T rtb_TransportDelay_p;
  real_T rtb_integrator_e;
  real_T rtb_TransportDelay_g;
  real_T rtb_ComplextoMagnitudeAngle_o1;
  real_T rtb_ComplextoMagnitudeAngle_o2;
  if (rtmIsMajorTimeStep(carga_M)) {
    /* set solver stop time */
    if (!(carga_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&carga_M->solverInfo, ((carga_M->Timing.clockTickH0
        + 1) * carga_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&carga_M->solverInfo, ((carga_M->Timing.clockTick0 +
        1) * carga_M->Timing.stepSize0 + carga_M->Timing.clockTickH0 *
        carga_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(carga_M)) {
    carga_M->Timing.t[0] = rtsiGetT(&carga_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(carga_M)) {
    /* Sum: '<Root>/Sum' incorporates:
     *  Inport: '<Root>/I_bio'
     *  Inport: '<Root>/I_die'
     *  Inport: '<Root>/I_pv'
     */
    carga_B.Sum = (carga_U.I_die + carga_U.I_bio) + carga_U.I_pv;

    /* S-Function (sfun_spssw_discc): '<S18>/State-Space' */

    /* S-Function block: <S18>/State-Space */
    {
      real_T accum;

      /*
       * Compute outputs:
       * ---------------
       */
      real_T *Cs = (real_T*)carga_DW.StateSpace_PWORK.CS;
      real_T *Ds = (real_T*)carga_DW.StateSpace_PWORK.DS;
      accum = 0.0;
      accum += *(Cs++) * carga_DW.StateSpace_DSTATE[0];
      accum += *(Cs++) * carga_DW.StateSpace_DSTATE[1];
      accum += *(Ds++) * carga_B.Sum;
      carga_B.StateSpace[0] = accum;
      accum = 0.0;
      accum += *(Cs++) * carga_DW.StateSpace_DSTATE[0];
      accum += *(Cs++) * carga_DW.StateSpace_DSTATE[1];
      accum += *(Ds++) * carga_B.Sum;
      carga_B.StateSpace[1] = accum;
    }

    /* Outport: '<Root>/Corriente_load' */
    carga_Y.Corriente_load = carga_B.StateSpace[1];

    /* Outport: '<Root>/Voltaje_load' */
    carga_Y.Voltaje_load = carga_B.StateSpace[0];
  }

  /* Integrator: '<S12>/integrator' */
  rtb_integrator = carga_X.integrator_CSTATE;

  /* TransportDelay: '<S12>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&carga_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&carga_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = carga_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_DW.TransportDelay_IWORK.CircularBufSize,
      &carga_DW.TransportDelay_IWORK.Last,
      carga_DW.TransportDelay_IWORK.Tail,
      carga_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_M)) {
    /* Memory: '<S12>/Memory' */
    carga_B.Memory = carga_DW.Memory_PreviousInput;
  }

  /* Switch: '<S12>/Switch' incorporates:
   *  Clock: '<S12>/Clock'
   *  Constant: '<S12>/K1'
   *  Gain: '<S12>/Gain'
   *  RelationalOperator: '<S12>/Relational Operator'
   *  Sum: '<S12>/Sum'
   */
  if (carga_M->Timing.t[0] >= 0.016666666666666666) {
    carga_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
  } else {
    carga_B.Switch = carga_B.Memory;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Integrator: '<S11>/integrator' */
  rtb_integrator_a = carga_X.integrator_CSTATE_c;

  /* TransportDelay: '<S11>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
    real_T simTime = carga_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_m = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_DW.TransportDelay_IWORK_e.CircularBufSize,
      &carga_DW.TransportDelay_IWORK_e.Last,
      carga_DW.TransportDelay_IWORK_e.Tail,
      carga_DW.TransportDelay_IWORK_e.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_M)) {
    /* Memory: '<S11>/Memory' */
    carga_B.Memory_l = carga_DW.Memory_PreviousInput_l;
  }

  /* Switch: '<S11>/Switch' incorporates:
   *  Clock: '<S11>/Clock'
   *  Constant: '<S11>/K1'
   *  Gain: '<S11>/Gain'
   *  RelationalOperator: '<S11>/Relational Operator'
   *  Sum: '<S11>/Sum'
   */
  if (carga_M->Timing.t[0] >= 0.016666666666666666) {
    carga_B.Switch_n = (rtb_integrator_a - rtb_TransportDelay_m) * 60.0;
  } else {
    carga_B.Switch_n = carga_B.Memory_l;
  }

  /* End of Switch: '<S11>/Switch' */

  /* Integrator: '<S16>/integrator' */
  rtb_integrator_h = carga_X.integrator_CSTATE_i;

  /* TransportDelay: '<S16>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[1];
    real_T simTime = carga_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_p = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_DW.TransportDelay_IWORK_a.CircularBufSize,
      &carga_DW.TransportDelay_IWORK_a.Last,
      carga_DW.TransportDelay_IWORK_a.Tail,
      carga_DW.TransportDelay_IWORK_a.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_M)) {
    /* Memory: '<S16>/Memory' */
    carga_B.Memory_p = carga_DW.Memory_PreviousInput_o;
  }

  /* Switch: '<S16>/Switch' incorporates:
   *  Clock: '<S16>/Clock'
   *  Constant: '<S16>/K1'
   *  Gain: '<S16>/Gain'
   *  RelationalOperator: '<S16>/Relational Operator'
   *  Sum: '<S16>/Sum'
   */
  if (carga_M->Timing.t[0] >= 0.016666666666666666) {
    carga_B.Switch_nu = (rtb_integrator_h - rtb_TransportDelay_p) * 60.0;
  } else {
    carga_B.Switch_nu = carga_B.Memory_p;
  }

  /* End of Switch: '<S16>/Switch' */

  /* Integrator: '<S15>/integrator' */
  rtb_integrator_e = carga_X.integrator_CSTATE_b;

  /* TransportDelay: '<S15>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs
      [0];
    real_T **tBuffer = (real_T**)&carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs
      [1];
    real_T simTime = carga_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_g = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_DW.TransportDelay_IWORK_c.CircularBufSize,
      &carga_DW.TransportDelay_IWORK_c.Last,
      carga_DW.TransportDelay_IWORK_c.Tail,
      carga_DW.TransportDelay_IWORK_c.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_M)) {
    /* Memory: '<S15>/Memory' */
    carga_B.Memory_o = carga_DW.Memory_PreviousInput_n;
  }

  /* Switch: '<S15>/Switch' incorporates:
   *  Clock: '<S15>/Clock'
   *  Constant: '<S15>/K1'
   *  Gain: '<S15>/Gain'
   *  RelationalOperator: '<S15>/Relational Operator'
   *  Sum: '<S15>/Sum'
   */
  if (carga_M->Timing.t[0] >= 0.016666666666666666) {
    carga_B.Switch_c = (rtb_integrator_e - rtb_TransportDelay_g) * 60.0;
  } else {
    carga_B.Switch_c = carga_B.Memory_o;
  }

  /* End of Switch: '<S15>/Switch' */

  /* Gain: '<S3>/Gain1' incorporates:
   *  ComplexToMagnitudeAngle: '<S7>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S8>/Complex to Magnitude-Angle'
   *  Product: '<S3>/Product'
   *  RealImagToComplex: '<S7>/Real-Imag to Complex'
   *  RealImagToComplex: '<S8>/Real-Imag to Complex'
   */
  rtb_ComplextoMagnitudeAngle_o1 = rt_hypotd_snf(carga_B.Switch,
    carga_B.Switch_n) * rt_hypotd_snf(carga_B.Switch_nu, carga_B.Switch_c) * 0.5;

  /* Gain: '<S3>/Deg->Rad' incorporates:
   *  ComplexToMagnitudeAngle: '<S7>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S8>/Complex to Magnitude-Angle'
   *  Gain: '<S7>/Rad->Deg.'
   *  Gain: '<S8>/Rad->Deg.'
   *  RealImagToComplex: '<S7>/Real-Imag to Complex'
   *  RealImagToComplex: '<S8>/Real-Imag to Complex'
   *  Sum: '<S3>/Sum'
   */
  rtb_ComplextoMagnitudeAngle_o2 = (57.295779513082323 * rt_atan2d_snf
    (carga_B.Switch_n, carga_B.Switch) - 57.295779513082323 * rt_atan2d_snf
    (carga_B.Switch_c, carga_B.Switch_nu)) * 0.017453292519943295;

  /* Outport: '<Root>/P_meas' incorporates:
   *  Product: '<S3>/Product1'
   *  Trigonometry: '<S3>/Trigonometric Function1'
   */
  carga_Y.P_meas = rtb_ComplextoMagnitudeAngle_o1 * cos
    (rtb_ComplextoMagnitudeAngle_o2);

  /* Outport: '<Root>/Q_meas' incorporates:
   *  Product: '<S3>/Product3'
   *  Trigonometry: '<S3>/Trigonometric Function2'
   */
  carga_Y.Q_meas = rtb_ComplextoMagnitudeAngle_o1 * sin
    (rtb_ComplextoMagnitudeAngle_o2);

  /* Product: '<S7>/Product' incorporates:
   *  Sin: '<S7>/sin(wt)'
   */
  carga_B.Product = sin(376.99111843077515 * carga_M->Timing.t[0]) * 2.0 *
    carga_B.StateSpace[0];

  /* Product: '<S7>/Product1' incorporates:
   *  Sin: '<S7>/cos(wt)'
   */
  carga_B.Product1 = sin(376.99111843077515 * carga_M->Timing.t[0] +
    1.5707963267948966) * 2.0 * carga_B.StateSpace[0];

  /* Product: '<S8>/Product' incorporates:
   *  Sin: '<S8>/sin(wt)'
   */
  carga_B.Product_a = sin(376.99111843077515 * carga_M->Timing.t[0]) * 2.0 *
    carga_B.StateSpace[1];

  /* Product: '<S8>/Product1' incorporates:
   *  Sin: '<S8>/cos(wt)'
   */
  carga_B.Product1_a = sin(376.99111843077515 * carga_M->Timing.t[0] +
    1.5707963267948966) * 2.0 * carga_B.StateSpace[1];
  if (rtmIsMajorTimeStep(carga_M)) {
    if (rtmIsMajorTimeStep(carga_M)) {
      /* Update for S-Function (sfun_spssw_discc): '<S18>/State-Space' */

      /* S-Function block: <S18>/State-Space */
      {
        const real_T *As = (real_T*)carga_DW.StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)carga_DW.StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)carga_DW.StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        accum = 0.0;
        accum += *(As++) * carga_DW.StateSpace_DSTATE[0];
        accum += *(As++) * carga_DW.StateSpace_DSTATE[1];
        accum += *(Bs++) * carga_B.Sum;
        xtmp[0] = accum;
        accum = 0.0;
        accum += *(As++) * carga_DW.StateSpace_DSTATE[0];
        accum += *(As++) * carga_DW.StateSpace_DSTATE[1];
        accum += *(Bs++) * carga_B.Sum;
        xtmp[1] = accum;
        carga_DW.StateSpace_DSTATE[0] = xtmp[0];
        carga_DW.StateSpace_DSTATE[1] = xtmp[1];
      }
    }

    /* Update for TransportDelay: '<S12>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&carga_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&carga_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = carga_M->Timing.t[0];
      carga_DW.TransportDelay_IWORK.Head = ((carga_DW.TransportDelay_IWORK.Head <
        (carga_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
        (carga_DW.TransportDelay_IWORK.Head+1) : 0);
      if (carga_DW.TransportDelay_IWORK.Head ==
          carga_DW.TransportDelay_IWORK.Tail) {
        carga_DW.TransportDelay_IWORK.Tail =
          ((carga_DW.TransportDelay_IWORK.Tail <
            (carga_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (carga_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[carga_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[carga_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(carga_M)) {
      /* Update for Memory: '<S12>/Memory' */
      carga_DW.Memory_PreviousInput = carga_B.Switch;
    }

    /* Update for TransportDelay: '<S11>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
      real_T simTime = carga_M->Timing.t[0];
      carga_DW.TransportDelay_IWORK_e.Head =
        ((carga_DW.TransportDelay_IWORK_e.Head <
          (carga_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
         (carga_DW.TransportDelay_IWORK_e.Head+1) : 0);
      if (carga_DW.TransportDelay_IWORK_e.Head ==
          carga_DW.TransportDelay_IWORK_e.Tail) {
        carga_DW.TransportDelay_IWORK_e.Tail =
          ((carga_DW.TransportDelay_IWORK_e.Tail <
            (carga_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
           (carga_DW.TransportDelay_IWORK_e.Tail+1) : 0);
      }

      (*tBuffer)[carga_DW.TransportDelay_IWORK_e.Head] = simTime;
      (*uBuffer)[carga_DW.TransportDelay_IWORK_e.Head] = rtb_integrator_a;
    }

    if (rtmIsMajorTimeStep(carga_M)) {
      /* Update for Memory: '<S11>/Memory' */
      carga_DW.Memory_PreviousInput_l = carga_B.Switch_n;
    }

    /* Update for TransportDelay: '<S16>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[1];
      real_T simTime = carga_M->Timing.t[0];
      carga_DW.TransportDelay_IWORK_a.Head =
        ((carga_DW.TransportDelay_IWORK_a.Head <
          (carga_DW.TransportDelay_IWORK_a.CircularBufSize-1)) ?
         (carga_DW.TransportDelay_IWORK_a.Head+1) : 0);
      if (carga_DW.TransportDelay_IWORK_a.Head ==
          carga_DW.TransportDelay_IWORK_a.Tail) {
        carga_DW.TransportDelay_IWORK_a.Tail =
          ((carga_DW.TransportDelay_IWORK_a.Tail <
            (carga_DW.TransportDelay_IWORK_a.CircularBufSize-1)) ?
           (carga_DW.TransportDelay_IWORK_a.Tail+1) : 0);
      }

      (*tBuffer)[carga_DW.TransportDelay_IWORK_a.Head] = simTime;
      (*uBuffer)[carga_DW.TransportDelay_IWORK_a.Head] = rtb_integrator_h;
    }

    if (rtmIsMajorTimeStep(carga_M)) {
      /* Update for Memory: '<S16>/Memory' */
      carga_DW.Memory_PreviousInput_o = carga_B.Switch_nu;
    }

    /* Update for TransportDelay: '<S15>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs[1];
      real_T simTime = carga_M->Timing.t[0];
      carga_DW.TransportDelay_IWORK_c.Head =
        ((carga_DW.TransportDelay_IWORK_c.Head <
          (carga_DW.TransportDelay_IWORK_c.CircularBufSize-1)) ?
         (carga_DW.TransportDelay_IWORK_c.Head+1) : 0);
      if (carga_DW.TransportDelay_IWORK_c.Head ==
          carga_DW.TransportDelay_IWORK_c.Tail) {
        carga_DW.TransportDelay_IWORK_c.Tail =
          ((carga_DW.TransportDelay_IWORK_c.Tail <
            (carga_DW.TransportDelay_IWORK_c.CircularBufSize-1)) ?
           (carga_DW.TransportDelay_IWORK_c.Tail+1) : 0);
      }

      (*tBuffer)[carga_DW.TransportDelay_IWORK_c.Head] = simTime;
      (*uBuffer)[carga_DW.TransportDelay_IWORK_c.Head] = rtb_integrator_e;
    }

    if (rtmIsMajorTimeStep(carga_M)) {
      /* Update for Memory: '<S15>/Memory' */
      carga_DW.Memory_PreviousInput_n = carga_B.Switch_c;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(carga_M)) {
    rt_ertODEUpdateContinuousStates(&carga_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++carga_M->Timing.clockTick0)) {
      ++carga_M->Timing.clockTickH0;
    }

    carga_M->Timing.t[0] = rtsiGetSolverStopTime(&carga_M->solverInfo);

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
      carga_M->Timing.clockTick1++;
      if (!carga_M->Timing.clockTick1) {
        carga_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void carga_derivatives(void)
{
  XDot_carga_T *_rtXdot;
  _rtXdot = ((XDot_carga_T *) carga_M->derivs);

  /* Derivatives for Integrator: '<S12>/integrator' */
  _rtXdot->integrator_CSTATE = carga_B.Product;

  /* Derivatives for Integrator: '<S11>/integrator' */
  _rtXdot->integrator_CSTATE_c = carga_B.Product1;

  /* Derivatives for Integrator: '<S16>/integrator' */
  _rtXdot->integrator_CSTATE_i = carga_B.Product_a;

  /* Derivatives for Integrator: '<S15>/integrator' */
  _rtXdot->integrator_CSTATE_b = carga_B.Product1_a;
}

/* Model initialize function */
void carga_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)carga_M, 0,
                sizeof(RT_MODEL_carga_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&carga_M->solverInfo, &carga_M->Timing.simTimeStep);
    rtsiSetTPtr(&carga_M->solverInfo, &rtmGetTPtr(carga_M));
    rtsiSetStepSizePtr(&carga_M->solverInfo, &carga_M->Timing.stepSize0);
    rtsiSetdXPtr(&carga_M->solverInfo, &carga_M->derivs);
    rtsiSetContStatesPtr(&carga_M->solverInfo, (real_T **) &carga_M->contStates);
    rtsiSetNumContStatesPtr(&carga_M->solverInfo, &carga_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&carga_M->solverInfo,
      &carga_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&carga_M->solverInfo,
      &carga_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&carga_M->solverInfo,
      &carga_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&carga_M->solverInfo, (&rtmGetErrorStatus(carga_M)));
    rtsiSetRTModelPtr(&carga_M->solverInfo, carga_M);
  }

  rtsiSetSimTimeStep(&carga_M->solverInfo, MAJOR_TIME_STEP);
  carga_M->intgData.y = carga_M->odeY;
  carga_M->intgData.f[0] = carga_M->odeF[0];
  carga_M->intgData.f[1] = carga_M->odeF[1];
  carga_M->intgData.f[2] = carga_M->odeF[2];
  carga_M->intgData.f[3] = carga_M->odeF[3];
  carga_M->contStates = ((X_carga_T *) &carga_X);
  rtsiSetSolverData(&carga_M->solverInfo, (void *)&carga_M->intgData);
  rtsiSetSolverName(&carga_M->solverInfo,"ode4");
  rtmSetTPtr(carga_M, &carga_M->Timing.tArray[0]);
  carga_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  (void) memset(((void *) &carga_B), 0,
                sizeof(B_carga_T));

  /* states (continuous) */
  {
    (void) memset((void *)&carga_X, 0,
                  sizeof(X_carga_T));
  }

  /* states (dwork) */
  (void) memset((void *)&carga_DW, 0,
                sizeof(DW_carga_T));

  /* external inputs */
  (void)memset((void *)&carga_U, 0, sizeof(ExtU_carga_T));

  /* external outputs */
  (void) memset((void *)&carga_Y, 0,
                sizeof(ExtY_carga_T));

  /* Start for S-Function (sfun_spssw_discc): '<S18>/State-Space' */

  /* S-Function block: <S18>/State-Space */
  {
    carga_DW.StateSpace_PWORK.AS = (real_T*)calloc(2 * 2, sizeof(real_T));
    carga_DW.StateSpace_PWORK.BS = (real_T*)calloc(2 * 1, sizeof(real_T));
    carga_DW.StateSpace_PWORK.CS = (real_T*)calloc(2 * 2, sizeof(real_T));
    carga_DW.StateSpace_PWORK.DS = (real_T*)calloc(2 * 1, sizeof(real_T));
    carga_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(2, sizeof(real_T));
    carga_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(1, sizeof(real_T));
    carga_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(2, sizeof(real_T));
    carga_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(2, sizeof(real_T));
    carga_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(2, sizeof(real_T));
  }

  /* Start for TransportDelay: '<S12>/Transport Delay' */
  {
    real_T *pBuffer = &carga_DW.TransportDelay_RWORK.TUbufferArea[0];
    carga_DW.TransportDelay_IWORK.Tail = 0;
    carga_DW.TransportDelay_IWORK.Head = 0;
    carga_DW.TransportDelay_IWORK.Last = 0;
    carga_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_M->Timing.t[0];
    carga_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S11>/Transport Delay' */
  {
    real_T *pBuffer = &carga_DW.TransportDelay_RWORK_a.TUbufferArea[0];
    carga_DW.TransportDelay_IWORK_e.Tail = 0;
    carga_DW.TransportDelay_IWORK_e.Head = 0;
    carga_DW.TransportDelay_IWORK_e.Last = 0;
    carga_DW.TransportDelay_IWORK_e.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_M->Timing.t[0];
    carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S16>/Transport Delay' */
  {
    real_T *pBuffer = &carga_DW.TransportDelay_RWORK_d.TUbufferArea[0];
    carga_DW.TransportDelay_IWORK_a.Tail = 0;
    carga_DW.TransportDelay_IWORK_a.Head = 0;
    carga_DW.TransportDelay_IWORK_a.Last = 0;
    carga_DW.TransportDelay_IWORK_a.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_M->Timing.t[0];
    carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_DW.TransportDelay_PWORK_h.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S15>/Transport Delay' */
  {
    real_T *pBuffer = &carga_DW.TransportDelay_RWORK_l.TUbufferArea[0];
    carga_DW.TransportDelay_IWORK_c.Tail = 0;
    carga_DW.TransportDelay_IWORK_c.Head = 0;
    carga_DW.TransportDelay_IWORK_c.Last = 0;
    carga_DW.TransportDelay_IWORK_c.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_M->Timing.t[0];
    carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_DW.TransportDelay_PWORK_fd.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S18>/State-Space' */
  {
    int32_T i, j;
    real_T *As = (real_T*)carga_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)carga_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)carga_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)carga_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&carga_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 2; i++) {
      X0[i] = (carga_ConstP.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<2; i++) {
      for (j=0; j<2; j++)
        As[i*2 + j] = (carga_ConstP.StateSpace_AS_param[i + j*2]);
      for (j=0; j<1; j++)
        Bs[i*1 + j] = (carga_ConstP.StateSpace_BS_param[i + j*2]);
    }

    /* Copy and transpose C */
    for (i=0; i<2; i++) {
      for (j=0; j<2; j++)
        Cs[i*2 + j] = (carga_ConstP.StateSpace_CS_param[i + j*2]);
    }

    /* Copy and transpose D */
    for (i=0; i<2; i++) {
      for (j=0; j<1; j++)
        Ds[i*1 + j] = (carga_ConstP.StateSpace_DS_param[i + j*2]);
    }
  }

  /* InitializeConditions for Integrator: '<S12>/integrator' */
  carga_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  carga_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S11>/integrator' */
  carga_X.integrator_CSTATE_c = 0.0;

  /* InitializeConditions for Integrator: '<S16>/integrator' */
  carga_X.integrator_CSTATE_i = 0.0;

  /* InitializeConditions for Memory: '<S16>/Memory' */
  carga_DW.Memory_PreviousInput_o = 1.0;

  /* InitializeConditions for Integrator: '<S15>/integrator' */
  carga_X.integrator_CSTATE_b = 0.0;
}

/* Model terminate function */
void carga_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S18>/State-Space' */

  /* S-Function block: <S18>/State-Space */
  {
    /* Free memory */
    free(carga_DW.StateSpace_PWORK.AS);
    free(carga_DW.StateSpace_PWORK.BS);
    free(carga_DW.StateSpace_PWORK.CS);
    free(carga_DW.StateSpace_PWORK.DS);
    free(carga_DW.StateSpace_PWORK.DX_COL);
    free(carga_DW.StateSpace_PWORK.TMP2);
    free(carga_DW.StateSpace_PWORK.BD_COL);
    free(carga_DW.StateSpace_PWORK.TMP1);
    free(carga_DW.StateSpace_PWORK.XTMP);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
