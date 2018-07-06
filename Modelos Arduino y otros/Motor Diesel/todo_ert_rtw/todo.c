/*
 * File: todo.c
 *
 * Code generated for Simulink model 'todo'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Feb 07 10:17:29 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "todo.h"
#include "todo_private.h"

/* Named constants for MATLAB Function: '<S9>/optimizer' */
#define todo_ny                        (2.0)

/* Block signals (auto storage) */
B_todo_T todo_B;

/* Continuous states */
X_todo_T todo_X;

/* Block states (auto storage) */
DW_todo_T todo_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_todo_T todo_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_todo_T todo_Y;

/* Real-time model */
RT_MODEL_todo_T todo_M_;
RT_MODEL_todo_T *const todo_M = &todo_M_;

/* Forward declaration for local functions */
static void todo_Unconstrained(const real_T b_Hinv[9], const real_T f[3], real_T
  x[3], int16_T n);
static real_T todo_norm(const real_T x[3]);
static void todo_abs_a(const real_T x[6], real_T y[6]);
static real_T todo_xnrm2(int32_T n, const real_T x[9], int32_T ix0);
static void todo_xgeqrf(real_T b_A[9], real_T tau[3]);
static void todo_qr(const real_T b_A[9], real_T Q[9], real_T R[9]);
static real_T todo_KWIKfactor(const real_T b_Ac[18], const int16_T iC[6],
  int16_T nA, const real_T b_Linv[9], real_T RLinv[9], real_T D[9], real_T b_H[9],
  int16_T n);
static void todo_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T *nA,
  int16_T iC[6]);
static void todo_abs(const real_T x[3], real_T y[3]);
static void todo_qpkwik(const real_T b_Linv[9], const real_T b_Hinv[9], const
  real_T f[3], const real_T b_Ac[18], const real_T b[6], int16_T iA[6], int16_T
  b_maxiter, real_T FeasTol, real_T x[3], real_T lambda[6], real_T *status);
static void rate_scheduler(void);

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

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

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
  (todo_M->Timing.TaskCounters.TID[2])++;
  if ((todo_M->Timing.TaskCounters.TID[2]) > 5999) {/* Sample time: [0.01s, 0.0s] */
    todo_M->Timing.TaskCounters.TID[2] = 0;
  }

  (todo_M->Timing.TaskCounters.TID[3])++;
  if ((todo_M->Timing.TaskCounters.TID[3]) > 59999) {/* Sample time: [0.1s, 0.0s] */
    todo_M->Timing.TaskCounters.TID[3] = 0;
  }
}

/* Simplified version of numjac.cpp, for use with RTW. */
void local_numjac( RTWSolverInfo *si, real_T *y, const real_T *Fty, real_T *fac,
                  real_T *dFdy )
{
  /* constants */
  real_T THRESH = 1e-6;
  real_T EPS = 2.2e-16;                /* utGetEps(); */
  real_T BL = pow(EPS, 0.75);
  real_T BU = pow(EPS, 0.25);
  real_T FACMIN = pow(EPS, 0.78);
  real_T FACMAX = 0.1;
  int_T nx = 14;
  real_T *x = rtsiGetContStates(si);
  real_T del;
  real_T difmax;
  real_T FdelRowmax;
  real_T temp;
  real_T Fdiff;
  real_T maybe;
  real_T xscale;
  real_T fscale;
  real_T *p;
  int_T rowmax;
  int_T i,j;
  if (x != y)
    (void) memcpy(x, y,
                  (uint_T)nx*sizeof(real_T));
  rtsiSetSolverComputingJacobian(si,true);
  for (p = dFdy, j = 0; j < nx; j++, p += nx) {
    /* Select an increment del for a difference approximation to
       column j of dFdy.  The vector fac accounts for experience
       gained in previous calls to numjac. */
    xscale = fabs(x[j]);
    if (xscale < THRESH)
      xscale = THRESH;
    temp = (x[j] + fac[j]*xscale);
    del = temp - y[j];
    while (del == 0.0) {
      if (fac[j] < FACMAX) {
        fac[j] *= 100.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
        temp = (x[j] + fac[j]*xscale);
        del = temp - x[j];
      } else {
        del = THRESH;                  /* thresh is nonzero */
        break;
      }
    }

    /* Keep del pointing into region. */
    if (Fty[j] >= 0.0)
      del = fabs(del);
    else
      del = -fabs(del);

    /* Form a difference approximation to column j of dFdy. */
    temp = x[j];
    x[j] += del;
    todo_step();
    rtsiSetdX(si,p);
    todo_derivatives();
    x[j] = temp;
    difmax = 0.0;
    rowmax = 0;
    FdelRowmax = p[0];
    temp = 1.0 / del;
    for (i = 0; i < nx; i++) {
      Fdiff = p[i] - Fty[i];
      maybe = fabs(Fdiff);
      if (maybe > difmax) {
        difmax = maybe;
        rowmax = i;
        FdelRowmax = p[i];
      }

      p[i] = temp * Fdiff;
    }

    /* Adjust fac for next call to numjac. */
    if (((FdelRowmax != 0.0) && (Fty[rowmax] != 0.0)) || (difmax == 0.0)) {
      fscale = fabs(FdelRowmax);
      if (fscale < fabs(Fty[rowmax]))
        fscale = fabs(Fty[rowmax]);
      if (difmax <= BL*fscale) {
        /* The difference is small, so increase the increment. */
        fac[j] *= 10.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
      } else if (difmax > BU*fscale) {
        /* The difference is large, so reduce the increment. */
        fac[j] *= 0.1;
        if (fac[j] < FACMIN)
          fac[j] = FACMIN;
      }
    }
  }

  rtsiSetSolverComputingJacobian(si,false);
}                                      /* end local_numjac */

/*
 * This function updates continuous states using the ODE14x fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static int_T rt_ODE14x_N[4] = { 12, 8, 6, 4 };

  time_T t0 = rtsiGetT(si);
  time_T t1 = t0;
  time_T h = rtsiGetStepSize(si);
  real_T *x1 = rtsiGetContStates(si);
  int_T order = rtsiGetSolverExtrapolationOrder(si);
  int_T numIter = rtsiGetSolverNumberNewtonIterations(si);
  ODE14X_IntgData *id = (ODE14X_IntgData *)rtsiGetSolverData(si);
  real_T *x0 = id->x0;
  real_T *f0 = id->f0;
  real_T *x1start = id->x1start;
  real_T *f1 = id->f1;
  real_T *Delta = id->Delta;
  real_T *E = id->E;
  real_T *fac = id->fac;
  real_T *dfdx = id->DFDX;
  real_T *W = id->W;
  int_T *pivots = id->pivots;
  real_T *xtmp = id->xtmp;
  real_T *ztmp = id->ztmp;
  int_T *N = &(rt_ODE14x_N[0]);
  int_T i,j,k,iter;
  int_T nx = 14;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(x0, x1,
                (uint_T)nx*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */

  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  todo_derivatives();
  local_numjac(si,x0,f0,fac,dfdx );
  for (j = 0; j < order; j++) {
    real_T *p;
    real_T hN = h/N[j];

    /* Get the iteration matrix and solution at t0 */

    /* [L,U] = lu(M - hN*J) */
    (void) memcpy(W, dfdx,
                  (uint_T)nx*nx*sizeof(real_T));
    for (p = W, i = 0; i < nx*nx; i++, p++) {
      *p *= (-hN);
    }

    for (p = W, i = 0; i < nx; i++, p += (nx+1)) {
      *p += 1.0;
    }

    rt_lu_real(W, nx,
               pivots);

    /* First Newton's iteration at t0. */
    /* rhs = hN*f0 */
    for (i = 0; i < nx; i++) {
      Delta[i] = hN*f0[i];
    }

    /* Delta = (U \ (L \ rhs)) */
    rt_ForwardSubstitutionRR_Dbl(W, Delta,
      f1, nx,
      1, pivots,
      1);
    rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
      Delta, nx,
      1, 0);

    /* ytmp = y0 + Delta
       ztmp = (ytmp-y0)/h
     */
    (void) memcpy(x1, x0,
                  (uint_T)nx*sizeof(real_T));
    for (i = 0; i < nx; i++) {
      x1[i] += Delta[i];
      ztmp[i] = Delta[i]/hN;
    }

    /* Additional Newton's iterations, if desired.
       for iter = 2:NewtIter
       rhs = hN*feval(odefun,tn,ytmp,extraArgs{:}) - M*(ytmp - yn);
       if statedepM   % only for state dep. Mdel ~= 0
       Mdel = M - feval(massfun,tn,ytmp);
       rhs = rhs + Mdel*ztmp*h;
       end
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       ztmp = (ytmp - yn)/h
       end
     */
    rtsiSetT(si, t0);
    rtsiSetdX(si, f1);
    for (iter = 1; iter < numIter; iter++) {
      todo_step();
      todo_derivatives();
      for (i = 0; i < nx; i++) {
        Delta[i] = hN*f1[i];
        xtmp[i] = x1[i] - x0[i];
      }

      /* rhs = hN*f(tn,ytmp) - (ytmp-yn) */
      for (i = 0; i < nx; i++) {
        Delta[i] -= xtmp[i];
      }

      rt_ForwardSubstitutionRR_Dbl(W, Delta,
        f1, nx,
        1, pivots,
        1);
      rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
        Delta, nx,
        1, 0);

      /* ytmp = ytmp + delta
         ztmp = (ytmp - yn)/h
       */
      for (i = 0; i < nx; i++) {
        x1[i] += Delta[i];
        ztmp[i] = (x1[i] - x0[i])/hN;
      }
    }

    /* Steps from t0+hN to t1 -- subintegration of N(j) steps for extrapolation
       ttmp = t0;
       for i = 2:N(j)
       ttmp = ttmp + hN
       ytmp0 = ytmp;
       for iter = 1:NewtIter
       rhs = (ytmp0 - ytmp) + hN*feval(odefun,ttmp,ytmp,extraArgs{:});
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       end
       end
     */
    for (k = 1; k < N[j]; k++) {
      t1 = t0 + k*hN;
      (void) memcpy(x1start, x1,
                    (uint_T)nx*sizeof(real_T));
      rtsiSetT(si, t1);
      rtsiSetdX(si, f1);
      for (iter = 0; iter < numIter; iter++) {
        todo_step();
        todo_derivatives();
        if (iter == 0) {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
          }
        } else {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
            xtmp[i] = (x1[i]-x1start[i]);
          }

          /* rhs = hN*f(tn,ytmp) - M*(ytmp-yn) */
          for (i = 0; i < nx; i++) {
            Delta[i] -= xtmp[i];
          }
        }

        rt_ForwardSubstitutionRR_Dbl(W, Delta,
          f1, nx,
          1, pivots,
          1);
        rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
          Delta, nx,
          1, 0);

        /* ytmp = ytmp + Delta
           ztmp = (ytmp - ytmp0)/h
         */
        for (i = 0; i < nx; i++) {
          x1[i] += Delta[i];
          ztmp[i] = (x1[i] - x1start[i])/hN;
        }
      }
    }

    /* Extrapolate to order j
       E(:,j) = ytmp
       for k = j:-1:2
       coef = N(k-1)/(N(j) - N(k-1))
       E(:,k-1) = E(:,k) + coef*( E(:,k) - E(:,k-1) )
       end
     */
    (void) memcpy(&(E[nx*j]), x1,
                  (uint_T)nx*sizeof(real_T));
    for (k = j; k > 0; k--) {
      real_T coef = (real_T)(N[k-1]) / (N[j]-N[k-1]);
      for (i = 0; i < nx; i++) {
        x1[i] = E[nx*k+i] + coef*(E[nx*k+i] - E[nx*(k-1)+i]);
      }

      (void) memcpy(&(E[nx*(k-1)]), x1,
                    (uint_T)nx*sizeof(real_T));
    }
  }

  /* x1 = E(:,1); */
  (void) memcpy(x1, E,
                (uint_T)nx*sizeof(real_T));

  /* t1 = t0 + h; */
  rtsiSetT(si,rtsiGetSolverStopTime(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * System initialize for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void todo_AutomaticGainControl_Init(real_T *rty_Gain,
  X_AutomaticGainControl_todo_T *localX)
{
  /* InitializeConditions for Integrator: '<S31>/integ1' */
  localX->integ1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S31>/Integ2' */
  localX->Integ2_CSTATE = 0.0;

  /* SystemInitialize for Outport: '<S31>/Gain' */
  *rty_Gain = 1.0;
}

/*
 * Disable for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void to_AutomaticGainControl_Disable(DW_AutomaticGainControl_todo_T *localDW)
{
  localDW->AutomaticGainControl_MODE = false;
}

/*
 * Start for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void todo_AutomaticGainControl_Start(RT_MODEL_todo_T * const todo_M,
  DW_AutomaticGainControl_todo_T *localDW)
{
  /* Start for VariableTransportDelay: '<S31>/Variable Transport Delay' */
  {
    real_T *pBuffer = &localDW->VariableTransportDelay_RWORK.TUbufferArea[0];
    int_T j;
    localDW->VariableTransportDelay_IWORK.Tail = 0;
    localDW->VariableTransportDelay_IWORK.Head = 0;
    localDW->VariableTransportDelay_IWORK.Last = 0;
    localDW->VariableTransportDelay_IWORK.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 1.0;
      pBuffer[8192 + j] = todo_M->Timing.t[0];
    }

    localDW->VariableTransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    localDW->VariableTransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* Start for VariableTransportDelay: '<S31>/Variable Transport Delay1' */
  {
    real_T *pBuffer = &localDW->VariableTransportDelay1_RWORK.TUbufferArea[0];
    int_T j;
    localDW->VariableTransportDelay1_IWORK.Tail = 0;
    localDW->VariableTransportDelay1_IWORK.Head = 0;
    localDW->VariableTransportDelay1_IWORK.Last = 0;
    localDW->VariableTransportDelay1_IWORK.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 0.0;
      pBuffer[8192 + j] = todo_M->Timing.t[0];
    }

    localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }
}

/*
 * Outputs for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void todo_AutomaticGainControl(RT_MODEL_todo_T * const todo_M, real_T rtu_Enable,
  real_T rtu_signal, real_T rtu_Freq, real_T rtu_SinCos, real_T rtu_SinCos_p,
  real_T *rty_Gain, B_AutomaticGainControl_todo_T *localB,
  DW_AutomaticGainControl_todo_T *localDW, X_AutomaticGainControl_todo_T *localX)
{
  real_T u0;

  /* Outputs for Enabled SubSystem: '<S25>/Automatic Gain Control' incorporates:
   *  EnablePort: '<S31>/Enable'
   */
  if ((rtmIsMajorTimeStep(todo_M) &&
       todo_M->Timing.TaskCounters.TID[1] == 0) && rtmIsMajorTimeStep(todo_M)) {
    if (rtu_Enable > 0.0) {
      if (!localDW->AutomaticGainControl_MODE) {
        localDW->AutomaticGainControl_MODE = true;
      }
    } else {
      if (localDW->AutomaticGainControl_MODE) {
        to_AutomaticGainControl_Disable(localDW);
      }
    }
  }

  if (localDW->AutomaticGainControl_MODE) {
    /* Integrator: '<S31>/integ1' */
    localB->integ1 = localX->integ1_CSTATE;

    /* Saturate: '<S31>/To avoid division by zero' */
    if (rtu_Freq > 1.0E+6) {
      localB->Freq = 1.0E+6;
    } else if (rtu_Freq < 1.0E-6) {
      localB->Freq = 1.0E-6;
    } else {
      localB->Freq = rtu_Freq;
    }

    /* End of Saturate: '<S31>/To avoid division by zero' */

    /* Fcn: '<S31>/Period' */
    localB->Period = 1.0 / localB->Freq;

    /* VariableTransportDelay: '<S31>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &localDW->VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &localDW->VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = localB->Period;

      /* For variable time delay, output here */
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      localB->VariableTransportDelay = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        localDW->VariableTransportDelay_IWORK.CircularBufSize,
        &localDW->VariableTransportDelay_IWORK.Last,
        localDW->VariableTransportDelay_IWORK.Tail,
        localDW->VariableTransportDelay_IWORK.Head,
        1.0,
        0,
        0);
    }

    /* Sum: '<S31>/Sum1' */
    localB->Sum1 = localB->integ1 - localB->VariableTransportDelay;

    /* Integrator: '<S31>/Integ2' */
    localB->Integ2 = localX->Integ2_CSTATE;

    /* VariableTransportDelay: '<S31>/Variable Transport Delay1' */
    {
      real_T **uBuffer = (real_T**)
        &localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = localB->Period;

      /* For variable time delay, output here */
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      localB->VariableTransportDelay1 = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        localDW->VariableTransportDelay1_IWORK.CircularBufSize,
        &localDW->VariableTransportDelay1_IWORK.Last,
        localDW->VariableTransportDelay1_IWORK.Tail,
        localDW->VariableTransportDelay1_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* Sum: '<S31>/Sum2' */
    localB->Sum2 = localB->Integ2 - localB->VariableTransportDelay1;

    /* Sum: '<S31>/Sum' incorporates:
     *  Fcn: '<S31>/Fcn'
     *  Fcn: '<S31>/Fcn1'
     */
    localB->Sum = rt_powd_snf(localB->Sum1, 2.0) + rt_powd_snf(localB->Sum2, 2.0);

    /* Gain: '<S31>/Gain10' */
    localB->Gain10 = 2.0 * rtu_Freq;

    /* Fcn: '<S31>/Fcn2' */
    if (localB->Sum < 0.0) {
      u0 = -sqrt(-localB->Sum);
    } else {
      u0 = sqrt(localB->Sum);
    }

    /* End of Fcn: '<S31>/Fcn2' */

    /* Saturate: '<S31>/Saturation' */
    if (u0 > 2.0) {
      localB->Saturation = 2.0;
    } else if (u0 < 0.01) {
      localB->Saturation = 0.01;
    } else {
      localB->Saturation = u0;
    }

    /* End of Saturate: '<S31>/Saturation' */

    /* Math: '<S31>/Math Function'
     *
     * About '<S31>/Math Function':
     *  Operator: reciprocal
     */
    *rty_Gain = 1.0 / localB->Saturation;

    /* Product: '<S31>/Product2' */
    localB->Product2 = rtu_signal * localB->Gain10;

    /* Product: '<S31>/Product' */
    localB->Product = rtu_SinCos * localB->Product2;

    /* Product: '<S31>/Product1' */
    localB->Product1 = localB->Product2 * rtu_SinCos_p;
  }

  /* End of Outputs for SubSystem: '<S25>/Automatic Gain Control' */
}

/*
 * Update for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void tod_AutomaticGainControl_Update(RT_MODEL_todo_T * const todo_M,
  B_AutomaticGainControl_todo_T *localB, DW_AutomaticGainControl_todo_T *localDW)
{
  /* Update for Enabled SubSystem: '<S25>/Automatic Gain Control' incorporates:
   *  Update for EnablePort: '<S31>/Enable'
   */
  if (localDW->AutomaticGainControl_MODE) {
    /* Update for VariableTransportDelay: '<S31>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &localDW->VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &localDW->VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = localB->Period;
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      localDW->VariableTransportDelay_IWORK.Head =
        ((localDW->VariableTransportDelay_IWORK.Head <
          (localDW->VariableTransportDelay_IWORK.CircularBufSize-1)) ?
         (localDW->VariableTransportDelay_IWORK.Head+1) : 0);
      if (localDW->VariableTransportDelay_IWORK.Head ==
          localDW->VariableTransportDelay_IWORK.Tail) {
        localDW->VariableTransportDelay_IWORK.Tail =
          ((localDW->VariableTransportDelay_IWORK.Tail <
            (localDW->VariableTransportDelay_IWORK.CircularBufSize-1)) ?
           (localDW->VariableTransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[localDW->VariableTransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[localDW->VariableTransportDelay_IWORK.Head] = localB->integ1;

      /* when use fixed buffer, reset solver at when buffer is updated
       * to avoid output consistency fail.
       */
    }

    /* Update for VariableTransportDelay: '<S31>/Variable Transport Delay1' */
    {
      real_T **uBuffer = (real_T**)
        &localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &localDW->VariableTransportDelay1_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = localB->Period;
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      localDW->VariableTransportDelay1_IWORK.Head =
        ((localDW->VariableTransportDelay1_IWORK.Head <
          (localDW->VariableTransportDelay1_IWORK.CircularBufSize-1)) ?
         (localDW->VariableTransportDelay1_IWORK.Head+1) : 0);
      if (localDW->VariableTransportDelay1_IWORK.Head ==
          localDW->VariableTransportDelay1_IWORK.Tail) {
        localDW->VariableTransportDelay1_IWORK.Tail =
          ((localDW->VariableTransportDelay1_IWORK.Tail <
            (localDW->VariableTransportDelay1_IWORK.CircularBufSize-1)) ?
           (localDW->VariableTransportDelay1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[localDW->VariableTransportDelay1_IWORK.Head] = simTime;
      (*uBuffer)[localDW->VariableTransportDelay1_IWORK.Head] = localB->Integ2;

      /* when use fixed buffer, reset solver at when buffer is updated
       * to avoid output consistency fail.
       */
    }
  }

  /* End of Update for SubSystem: '<S25>/Automatic Gain Control' */
}

/*
 * Derivatives for enable system:
 *    '<S25>/Automatic Gain Control'
 *    '<S74>/Automatic Gain Control'
 */
void todo_AutomaticGainControl_Deriv(B_AutomaticGainControl_todo_T *localB,
  DW_AutomaticGainControl_todo_T *localDW, XDot_AutomaticGainControl_tod_T
  *localXdot)
{
  if (localDW->AutomaticGainControl_MODE) {
    /* Derivatives for Integrator: '<S31>/integ1' */
    localXdot->integ1_CSTATE = localB->Product;

    /* Derivatives for VariableTransportDelay: '<S31>/Variable Transport Delay' */
    {
    }

    /* Derivatives for Integrator: '<S31>/Integ2' */
    localXdot->Integ2_CSTATE = localB->Product1;

    /* Derivatives for VariableTransportDelay: '<S31>/Variable Transport Delay1' */
    {
    }
  } else {
    {
      real_T *dx;
      int_T i;
      dx = &(localXdot->integ1_CSTATE);
      for (i=0; i < 2; i++) {
        dx[i] = 0.0;
      }
    }
  }
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_Unconstrained(const real_T b_Hinv[9], const real_T f[3], real_T
  x[3], int16_T n)
{
  int16_T i;
  for (i = 1; i <= n; i++) {
    x[i - 1] = (-b_Hinv[i - 1] * f[0] + -b_Hinv[i + 2] * f[1]) + -b_Hinv[i + 5] *
      f[2];
  }
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static real_T todo_norm(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_abs_a(const real_T x[6], real_T y[6])
{
  int32_T k;
  for (k = 0; k < 6; k++) {
    y[k] = fabs(x[k]);
  }
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static real_T todo_xnrm2(int32_T n, const real_T x[9], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
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

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_xgeqrf(real_T b_A[9], real_T tau[3])
{
  real_T work[3];
  real_T b_atmp;
  real_T xnorm;
  int32_T knt;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia;
  int32_T ix;
  real_T b_c;
  int32_T g;
  int32_T b_ia;
  int32_T b_ix;
  int32_T exitg1;
  boolean_T exitg2;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  b_atmp = b_A[0];
  b_c = 0.0;
  xnorm = todo_xnrm2(2, b_A, 2);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[0], xnorm);
    if (b_A[0] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 1; lastc + 1 < 4; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, todo_xnrm2(2, b_A, 2));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 1; lastc + 1 < 4; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[0]) / xnorm;
      b_atmp = 1.0 / (b_A[0] - xnorm);
      for (lastv = 1; lastv + 1 < 4; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[0] = b_c;
  b_A[0] = b_atmp;
  b_atmp = b_A[0];
  b_A[0] = 1.0;
  knt = 3;
  if (b_c != 0.0) {
    lastv = 3;
    lastc = 2;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = (lastc - 1) * 3 + 4;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if (b_A[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      ia = (lastc - 1) * 3 + 4;
      for (b_ix = 4; b_ix <= ia; b_ix += 3) {
        ix = 0;
        b_c = 0.0;
        g = (b_ix + lastv) - 1;
        for (b_ia = b_ix; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
      }
    }

    if (!(-tau[0] == 0.0)) {
      coltop = 0;
      for (ia = 1; ia <= lastc; ia++) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[0];
          b_ix = 0;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 3;
      }
    }
  }

  b_A[0] = b_atmp;
  b_atmp = b_A[4];
  b_c = 0.0;
  xnorm = todo_xnrm2(1, b_A, 6);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[4], xnorm);
    if (b_A[4] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 5; lastc + 1 < 7; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, todo_xnrm2(1, b_A, 6));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 5; lastc + 1 < 7; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[4]) / xnorm;
      b_atmp = 1.0 / (b_A[4] - xnorm);
      for (lastv = 5; lastv + 1 < 7; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[1] = b_c;
  b_A[4] = b_atmp;
  b_atmp = b_A[4];
  b_A[4] = 1.0;
  knt = 7;
  if (b_c != 0.0) {
    lastv = 2;
    lastc = 5;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      ia = 8;
      do {
        exitg1 = 0;
        if (ia <= lastv + 7) {
          if (b_A[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      coltop = 1;
      while (coltop <= 1) {
        work[0] = 0.0;
        coltop = 2;
      }

      coltop = 0;
      b_ix = 8;
      while (b_ix <= 8) {
        ix = 4;
        b_c = 0.0;
        g = lastv + 7;
        for (b_ia = 8; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
        b_ix = 11;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 0;
      ia = 1;
      while (ia <= lastc) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[1];
          b_ix = 4;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 3;
        ia = 2;
      }
    }
  }

  b_A[4] = b_atmp;
  tau[2] = 0.0;
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_qr(const real_T b_A[9], real_T Q[9], real_T R[9])
{
  real_T c_A[9];
  real_T tau[3];
  int32_T d_i;
  real_T work[3];
  int32_T lastc;
  int32_T coltop;
  int32_T ix;
  real_T c;
  int32_T iac;
  int32_T d;
  int32_T b_ia;
  int32_T jy;
  int32_T exitg1;
  boolean_T exitg2;
  memcpy(&c_A[0], &b_A[0], 9U * sizeof(real_T));
  todo_xgeqrf(c_A, tau);
  for (d_i = 0; d_i + 1 < 2; d_i++) {
    R[d_i] = c_A[d_i];
  }

  for (d_i = 1; d_i + 1 < 4; d_i++) {
    R[d_i] = 0.0;
  }

  work[0] = 0.0;
  for (d_i = 0; d_i + 1 < 3; d_i++) {
    R[d_i + 3] = c_A[d_i + 3];
  }

  for (d_i = 2; d_i + 1 < 4; d_i++) {
    R[d_i + 3] = 0.0;
  }

  work[1] = 0.0;
  for (d_i = 0; d_i + 1 < 4; d_i++) {
    R[d_i + 6] = c_A[d_i + 6];
  }

  work[2] = 0.0;
  c_A[8] = 1.0 - tau[2];
  for (d_i = 1; d_i < 3; d_i++) {
    c_A[8 - d_i] = 0.0;
  }

  c_A[4] = 1.0;
  if (tau[1] != 0.0) {
    d_i = 2;
    lastc = 5;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      jy = 5;
      do {
        exitg1 = 0;
        if (jy + 3 <= d_i + 7) {
          if (c_A[jy + 2] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    d_i = 0;
    lastc = 0;
  }

  if (d_i > 0) {
    if (lastc != 0) {
      coltop = 1;
      while (coltop <= 1) {
        work[0] = 0.0;
        coltop = 2;
      }

      coltop = 0;
      iac = 8;
      while (iac <= 8) {
        ix = 5;
        c = 0.0;
        d = d_i + 7;
        for (b_ia = 8; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
        iac = 11;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 7;
      jy = 0;
      iac = 1;
      while (iac <= lastc) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[1];
          ix = 5;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 3;
        iac = 2;
      }
    }
  }

  for (lastc = 5; lastc + 1 < 7; lastc++) {
    c_A[lastc] *= -tau[1];
  }

  c_A[4] = 1.0 - tau[1];
  d_i = 1;
  while (d_i <= 1) {
    c_A[3] = 0.0;
    d_i = 2;
  }

  c_A[0] = 1.0;
  if (tau[0] != 0.0) {
    d_i = 3;
    lastc = 2;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = (lastc - 1) * 3 + 1;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy + 3 <= (coltop + d_i) + 2) {
          if (c_A[jy + 2] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    d_i = 0;
    lastc = 0;
  }

  if (d_i > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      jy = (lastc - 1) * 3 + 4;
      for (iac = 4; iac <= jy; iac += 3) {
        ix = 1;
        c = 0.0;
        d = (iac + d_i) - 1;
        for (b_ia = iac; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
      }
    }

    if (!(-tau[0] == 0.0)) {
      coltop = 3;
      jy = 0;
      for (iac = 1; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[0];
          ix = 1;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 3;
      }
    }
  }

  for (lastc = 1; lastc + 1 < 4; lastc++) {
    c_A[lastc] *= -tau[0];
  }

  c_A[0] = 1.0 - tau[0];
  for (d_i = 0; d_i < 3; d_i++) {
    Q[3 * d_i] = c_A[3 * d_i];
    Q[1 + 3 * d_i] = c_A[3 * d_i + 1];
    Q[2 + 3 * d_i] = c_A[3 * d_i + 2];
  }
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static real_T todo_KWIKfactor(const real_T b_Ac[18], const int16_T iC[6],
  int16_T nA, const real_T b_Linv[9], real_T RLinv[9], real_T D[9], real_T b_H[9],
  int16_T n)
{
  real_T Status;
  real_T TL[9];
  real_T QQ[9];
  real_T RR[9];
  int16_T i;
  int16_T f_i;
  int16_T d_k;
  int32_T iC_0;
  int32_T i_0;
  int32_T i_1;
  int32_T exitg1;
  Status = 1.0;
  memset(&RLinv[0], 0, 9U * sizeof(real_T));
  for (i = 1; i <= nA; i++) {
    RLinv[3 * (i - 1)] = 0.0;
    RLinv[1 + 3 * (i - 1)] = 0.0;
    RLinv[2 + 3 * (i - 1)] = 0.0;
    iC_0 = iC[i - 1];
    i_0 = i - 1;
    for (i_1 = 0; i_1 < 3; i_1++) {
      RLinv[i_1 + 3 * i_0] = 0.0;
      RLinv[i_1 + 3 * i_0] += b_Ac[iC_0 - 1] * b_Linv[i_1];
      RLinv[i_1 + 3 * i_0] += b_Linv[i_1 + 3] * b_Ac[iC_0 + 5];
      RLinv[i_1 + 3 * i_0] += b_Linv[i_1 + 6] * b_Ac[iC_0 + 11];
    }
  }

  todo_qr(RLinv, QQ, RR);
  i = 1;
  do {
    exitg1 = 0;
    if (i <= nA) {
      if (fabs(RR[((i - 1) * 3 + i) - 1]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      for (i = 1; i <= n; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          TL[(i + 3 * (f_i - 1)) - 1] = (b_Linv[(i - 1) * 3 + 1] * QQ[(f_i - 1) *
            3 + 1] + b_Linv[(i - 1) * 3] * QQ[(f_i - 1) * 3]) + b_Linv[(i - 1) *
            3 + 2] * QQ[(f_i - 1) * 3 + 2];
        }
      }

      memset(&RLinv[0], 0, 9U * sizeof(real_T));
      for (i = nA; i > 0; i--) {
        RLinv[(i + 3 * (i - 1)) - 1] = 1.0;
        for (f_i = i; f_i <= nA; f_i++) {
          RLinv[(i + 3 * (f_i - 1)) - 1] /= RR[((i - 1) * 3 + i) - 1];
        }

        if (i > 1) {
          for (f_i = 1; f_i < i; f_i++) {
            for (d_k = i; d_k <= nA; d_k++) {
              RLinv[(f_i + 3 * (d_k - 1)) - 1] -= RR[((i - 1) * 3 + f_i) - 1] *
                RLinv[((d_k - 1) * 3 + i) - 1];
            }
          }
        }
      }

      for (i = 1; i <= n; i++) {
        for (f_i = i; f_i <= n; f_i++) {
          b_H[(i + 3 * (f_i - 1)) - 1] = 0.0;
          for (d_k = (int16_T)(nA + 1); d_k <= n; d_k++) {
            b_H[(i + 3 * (f_i - 1)) - 1] -= TL[((d_k - 1) * 3 + i) - 1] * TL
              [((d_k - 1) * 3 + f_i) - 1];
          }

          b_H[(f_i + 3 * (i - 1)) - 1] = b_H[((f_i - 1) * 3 + i) - 1];
        }
      }

      for (i = 1; i <= nA; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          D[(f_i + 3 * (i - 1)) - 1] = 0.0;
          for (d_k = i; d_k <= nA; d_k++) {
            D[(f_i + 3 * (i - 1)) - 1] += TL[((d_k - 1) * 3 + f_i) - 1] * RLinv
              [((d_k - 1) * 3 + i) - 1];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T *nA,
  int16_T iC[6])
{
  int16_T i;
  int32_T tmp;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    tmp = *nA - 1;
    if (tmp < -32768) {
      tmp = -32768;
    }

    for (i = kDrop; i <= (int16_T)tmp; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  tmp = *nA - 1;
  if (tmp < -32768) {
    tmp = -32768;
  }

  *nA = (int16_T)tmp;
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_abs(const real_T x[3], real_T y[3])
{
  y[0] = fabs(x[0]);
  y[1] = fabs(x[1]);
  y[2] = fabs(x[2]);
}

/* Function for MATLAB Function: '<S9>/optimizer' */
static void todo_qpkwik(const real_T b_Linv[9], const real_T b_Hinv[9], const
  real_T f[3], const real_T b_Ac[18], const real_T b[6], int16_T iA[6], int16_T
  b_maxiter, real_T FeasTol, real_T x[3], real_T lambda[6], real_T *status)
{
  real_T r[3];
  real_T rMin;
  real_T RLinv[9];
  real_T D[9];
  real_T b_H[9];
  real_T U[9];
  real_T cTol[6];
  boolean_T cTolComputed;
  int16_T iC[6];
  int16_T nA;
  real_T Opt[6];
  real_T Rhs[6];
  boolean_T DualFeasible;
  boolean_T ColdReset;
  int16_T kDrop;
  real_T Xnorm0;
  real_T cMin;
  int16_T kNext;
  real_T AcRow[3];
  real_T z[3];
  real_T zTa;
  real_T t;
  int16_T iSave;
  uint16_T q;
  uint16_T b_x;
  int32_T ix;
  int32_T i;
  int32_T tmp;
  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0;
  x[0] = 0.0;
  r[0] = 0.0;
  x[1] = 0.0;
  r[1] = 0.0;
  x[2] = 0.0;
  r[2] = 0.0;
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 6; i++) {
    lambda[i] = 0.0;
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (kNext = 0; kNext < 6; kNext++) {
    if (iA[kNext] == 1) {
      i = nA + 1;
      if (i > 32767) {
        i = 32767;
      }

      nA = (int16_T)i;
      iC[(int16_T)i - 1] = (int16_T)(kNext + 1);
    }
  }

  guard1 = false;
  if (nA > 0) {
    for (i = 0; i < 6; i++) {
      Opt[i] = 0.0;
    }

    Rhs[0] = f[0];
    Rhs[3] = 0.0;
    Rhs[1] = f[1];
    Rhs[4] = 0.0;
    Rhs[2] = f[2];
    Rhs[5] = 0.0;
    DualFeasible = false;
    i = 3 * nA;
    if (i > 32767) {
      i = 32767;
    }

    if ((int16_T)i > 50) {
      kNext = (int16_T)i;
    } else {
      kNext = 50;
    }

    q = (uint16_T)(kNext / 10U);
    b_x = (uint16_T)((uint32_T)kNext - q * 10);
    if ((b_x > 0) && (b_x >= 5)) {
      q++;
    }

    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && ((int32_T)*status <= b_maxiter)) {
        Xnorm0 = todo_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H, 3);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2.0;
            exitg3 = 2;
          } else {
            nA = 0;
            for (i = 0; i < 6; i++) {
              iA[i] = 0;
              iC[i] = 0;
            }

            ColdReset = true;
          }
        } else {
          for (kNext = 1; kNext <= nA; kNext++) {
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Rhs[i - 1] = b[iC[kNext - 1] - 1];
            for (kDrop = kNext; kDrop <= nA; kDrop++) {
              U[(kDrop + 3 * (kNext - 1)) - 1] = 0.0;
              for (iSave = 1; iSave <= nA; iSave++) {
                U[(kDrop + 3 * (kNext - 1)) - 1] += RLinv[((iSave - 1) * 3 +
                  kDrop) - 1] * RLinv[((iSave - 1) * 3 + kNext) - 1];
              }

              U[(kNext + 3 * (kDrop - 1)) - 1] = U[((kNext - 1) * 3 + kDrop) - 1];
            }
          }

          for (kNext = 0; kNext < 3; kNext++) {
            i = kNext + 1;
            Opt[kNext] = (b_H[i - 1] * Rhs[0] + b_H[i + 2] * Rhs[1]) + b_H[i + 5]
              * Rhs[2];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 3 + kDrop;
              if (i > 32767) {
                i = 32767;
              }

              Opt[kNext] += D[(kDrop - 1) * 3 + kNext] * Rhs[i - 1];
            }
          }

          for (kNext = 1; kNext <= nA; kNext++) {
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Opt[i - 1] = (D[(kNext - 1) * 3 + 1] * Rhs[1] + D[(kNext - 1) * 3] *
                          Rhs[0]) + D[(kNext - 1) * 3 + 2] * Rhs[2];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 3 + kNext;
              if (i > 32767) {
                i = 32767;
              }

              ix = 3 + kNext;
              if (ix > 32767) {
                ix = 32767;
              }

              tmp = 3 + kDrop;
              if (tmp > 32767) {
                tmp = 32767;
              }

              Opt[i - 1] = U[((kDrop - 1) * 3 + kNext) - 1] * Rhs[tmp - 1] +
                Opt[ix - 1];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = 0;
          for (kNext = 1; kNext <= nA; kNext++) {
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            lambda[iC[kNext - 1] - 1] = Opt[i - 1];
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            if ((Opt[i - 1] < Xnorm0) && (kNext <= nA)) {
              kDrop = kNext;
              i = 3 + kNext;
              if (i > 32767) {
                i = 32767;
              }

              Xnorm0 = Opt[i - 1];
            }
          }

          if (kDrop <= 0) {
            DualFeasible = true;
            x[0] = Opt[0];
            x[1] = Opt[1];
            x[2] = Opt[2];
          } else {
            (*status)++;
            if ((int32_T)*status > q) {
              nA = 0;
              for (i = 0; i < 6; i++) {
                iA[i] = 0;
                iC[i] = 0;
              }

              ColdReset = true;
            } else {
              lambda[iC[kDrop - 1] - 1] = 0.0;
              todo_DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          for (i = 0; i < 6; i++) {
            lambda[i] = 0.0;
          }

          todo_Unconstrained(b_Hinv, f, x, 3);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    todo_Unconstrained(b_Hinv, f, x, 3);
    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = todo_norm(x);
    do {
      exitg2 = 0;
      if ((int32_T)*status <= b_maxiter) {
        cMin = -FeasTol;
        kNext = 0;
        for (kDrop = 0; kDrop < 6; kDrop++) {
          if (!cTolComputed) {
            i = kDrop + 1;
            z[0] = b_Ac[i - 1] * x[0];
            z[1] = b_Ac[i + 5] * x[1];
            z[2] = b_Ac[i + 11] * x[2];
            todo_abs(z, AcRow);
            i = 1;
            zTa = AcRow[0];
            if (rtIsNaN(AcRow[0])) {
              ix = 2;
              exitg4 = false;
              while ((!exitg4) && (ix < 4)) {
                i = ix;
                if (!rtIsNaN(AcRow[ix - 1])) {
                  zTa = AcRow[ix - 1];
                  exitg4 = true;
                } else {
                  ix++;
                }
              }
            }

            if (i < 3) {
              while (i + 1 < 4) {
                if (AcRow[i] > zTa) {
                  zTa = AcRow[i];
                }

                i++;
              }
            }

            cTol[kDrop] = fmax(cTol[kDrop], zTa);
          }

          if (iA[kDrop] == 0) {
            i = kDrop + 1;
            zTa = (((b_Ac[i - 1] * x[0] + b_Ac[i + 5] * x[1]) + b_Ac[i + 11] *
                    x[2]) - b[kDrop]) / cTol[kDrop];
            if (zTa < cMin) {
              cMin = zTa;
              kNext = (int16_T)(kDrop + 1);
            }
          }
        }

        cTolComputed = true;
        if (kNext <= 0) {
          exitg2 = 1;
        } else {
          do {
            exitg1 = 0;
            if ((kNext > 0) && ((int32_T)*status <= b_maxiter)) {
              guard2 = false;
              if (nA == 0) {
                for (i = 0; i < 3; i++) {
                  z[i] = b_Hinv[i + 6] * b_Ac[kNext + 11] + (b_Hinv[i + 3] *
                    b_Ac[kNext + 5] + b_Ac[kNext - 1] * b_Hinv[i]);
                }

                guard2 = true;
              } else {
                cMin = todo_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H, 3);
                if (cMin <= 0.0) {
                  *status = -2.0;
                  exitg1 = 1;
                } else {
                  for (i = 0; i < 3; i++) {
                    U[3 * i] = -b_H[3 * i];
                    U[1 + 3 * i] = -b_H[3 * i + 1];
                    U[2 + 3 * i] = -b_H[3 * i + 2];
                  }

                  for (i = 0; i < 3; i++) {
                    z[i] = U[i + 6] * b_Ac[kNext + 11] + (U[i + 3] * b_Ac[kNext
                      + 5] + b_Ac[kNext - 1] * U[i]);
                  }

                  for (kDrop = 1; kDrop <= nA; kDrop++) {
                    r[kDrop - 1] = (D[(kDrop - 1) * 3 + 1] * b_Ac[kNext + 5] +
                                    D[(kDrop - 1) * 3] * b_Ac[kNext - 1]) + D
                      [(kDrop - 1) * 3 + 2] * b_Ac[kNext + 11];
                  }

                  guard2 = true;
                }
              }

              if (guard2) {
                kDrop = 0;
                cMin = 0.0;
                DualFeasible = true;
                ColdReset = true;
                if (nA > 0) {
                  iSave = 1;
                  exitg4 = false;
                  while ((!exitg4) && (iSave <= nA)) {
                    if (r[iSave - 1] >= 1.0E-12) {
                      ColdReset = false;
                      exitg4 = true;
                    } else {
                      iSave++;
                    }
                  }
                }

                if (!((nA == 0) || ColdReset)) {
                  for (iSave = 1; iSave <= nA; iSave++) {
                    if (r[iSave - 1] > 1.0E-12) {
                      zTa = lambda[iC[iSave - 1] - 1] / r[iSave - 1];
                      if ((kDrop == 0) || (zTa < rMin)) {
                        rMin = zTa;
                        kDrop = iSave;
                      }
                    }
                  }

                  if (kDrop > 0) {
                    cMin = rMin;
                    DualFeasible = false;
                  }
                }

                zTa = (b_Ac[kNext - 1] * z[0] + b_Ac[kNext + 5] * z[1]) +
                  b_Ac[kNext + 11] * z[2];
                if (zTa <= 0.0) {
                  zTa = 0.0;
                  ColdReset = true;
                } else {
                  zTa = (b[kNext - 1] - ((b_Ac[kNext - 1] * x[0] + b_Ac[kNext +
                           5] * x[1]) + b_Ac[kNext + 11] * x[2])) / zTa;
                  ColdReset = false;
                }

                if (DualFeasible && ColdReset) {
                  *status = -1.0;
                  exitg1 = 1;
                } else {
                  if (ColdReset) {
                    t = cMin;
                  } else if (DualFeasible) {
                    t = zTa;
                  } else {
                    t = fmin(cMin, zTa);
                  }

                  for (iSave = 1; iSave <= nA; iSave++) {
                    lambda[iC[iSave - 1] - 1] -= r[iSave - 1] * t;
                    if ((iC[iSave - 1] <= 6) && (lambda[iC[iSave - 1] - 1] < 0.0))
                    {
                      lambda[iC[iSave - 1] - 1] = 0.0;
                    }
                  }

                  lambda[kNext - 1] += t;
                  if (t == cMin) {
                    todo_DropConstraint(kDrop, iA, &nA, iC);
                  }

                  if (!ColdReset) {
                    x[0] += t * z[0];
                    x[1] += t * z[1];
                    x[2] += t * z[2];
                    if (t == zTa) {
                      if (nA == 3) {
                        *status = -1.0;
                        exitg1 = 1;
                      } else {
                        i = nA + 1;
                        if (i > 32767) {
                          i = 32767;
                        }

                        nA = (int16_T)i;
                        iC[(int16_T)i - 1] = kNext;
                        kDrop = (int16_T)i;
                        while ((kDrop > 1) && (!(iC[kDrop - 1] > iC[kDrop - 2])))
                        {
                          iSave = iC[kDrop - 1];
                          iC[kDrop - 1] = iC[kDrop - 2];
                          iC[kDrop - 2] = iSave;
                          kDrop--;
                        }

                        iA[kNext - 1] = 1;
                        kNext = 0;
                        (*status)++;
                      }
                    } else {
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                }
              }
            } else {
              cMin = todo_norm(x);
              if (fabs(cMin - Xnorm0) > 0.001) {
                Xnorm0 = cMin;
                todo_abs_a(b, Opt);
                for (i = 0; i < 6; i++) {
                  cTol[i] = fmax(Opt[i], 1.0);
                }

                cTolComputed = false;
              }

              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = 1;
          }
        }
      } else {
        *status = 0.0;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
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

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  boolean_T yEq;
  real_T q;
  y = u0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    if (u1 != 0.0) {
      y = (rtNaN);
    }
  } else if (u0 == 0.0) {
    y = u1 * 0.0;
  } else {
    if (u1 != 0.0) {
      y = fmod(u0, u1);
      yEq = (y == 0.0);
      if ((!yEq) && (u1 > floor(u1))) {
        q = fabs(u0 / u1);
        yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
      }

      if (yEq) {
        y = u1 * 0.0;
      } else {
        if ((u0 < 0.0) != (u1 < 0.0)) {
          y += u1;
        }
      }
    }
  }

  return y;
}

/* Model step function */
void todo_step(void)
{
  /* local block i/o variables */
  real_T rtb_u;
  if (rtmIsMajorTimeStep(todo_M)) {
    /* set solver stop time */
    if (!(todo_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&todo_M->solverInfo, ((todo_M->Timing.clockTickH0 +
        1) * todo_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&todo_M->solverInfo, ((todo_M->Timing.clockTick0 + 1)
        * todo_M->Timing.stepSize0 + todo_M->Timing.clockTickH0 *
        todo_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(todo_M)) {
    todo_M->Timing.t[0] = rtsiGetT(&todo_M->solverInfo);
  }

  {
    int32_T k;
    real_T *lastU;
    real_T riseValLimit;
    real_T rseq[6];
    real_T f[3];
    real_T zopt[3];
    int16_T iAnew[6];
    static const real_T b_Linv[9] = { 0.576390417704235, 1.082644094031286E-18,
      0.0, 0.0, 0.57639041770423483, 0.0, 0.0, 0.0, 0.003162277660168379 };

    static const real_T b_Hinv[9] = { 0.33222591362126258,
      6.2402568158371586E-19, 0.0, 6.2402568158371586E-19, 0.3322259136212623,
      0.0, 0.0, 0.0, 9.9999999999999974E-6 };

    static const real_T b_Ac[18] = { -1.0, -0.0, 1.0, 0.0, 1.0, 0.0, -0.0, -1.0,
      0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    static const real_T a[12] = { 0.46587257075478766, -5.3074673088437147E+37,
      -4.1527397320835594E-17, -5.9505912958277258E+37, 0.068254858490424675,
      9.598535600650316E-17, -4.1527397320835594E-17, 2.1066830431907355E+37,
      0.46587257075478777, 5.1969495894995853E+37, 9.5985356006503111E-17,
      0.068254858490424661 };

    static const int8_T b_a[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 };

    static const int8_T b_Mlim[6] = { 20, 20, 20, 20, 100, 100 };

    static const int8_T b_Mu1[12] = { -1, 0, 1, 0, 0, 0, 0, -1, 0, 1, 0, 0 };

    static const real_T b_Kx[12] = { 2.1417677256498697E-108,
      -4.5498998166004214E-110, -7.940051874482339E-108, 1.6867580986889367E-109,
      2.9999999999999996, -1.1996136967492359E-16, -7.9400518744823436E-108,
      1.6867580986889379E-109, 2.9435696044182925E-107, -6.2532209459032658E-109,
      1.1430763459720701E-16, 3.0000000000000009 };

    static const real_T b_Kr[12] = { -0.99999999999999989,
      3.9987123224974528E-17, -0.99999999999999989, 3.9987123224974528E-17,
      -0.99999999999999989, 3.9987123224974528E-17, -3.8102544865735674E-17,
      -1.0000000000000002, -3.8102544865735674E-17, -1.0000000000000002,
      -3.8102544865735674E-17, -1.0000000000000002 };

    static const real_T b_Ku1[4] = { 2.9999999999999991, -5.6537350777166251E-18,
      -5.6537350777166251E-18, 3.0000000000000013 };

    static const real_T c_a[36] = { 2.1417677256498697E-108,
      1.8613226522456278E-106, -7.9400518744823421E-108, -6.900374040091109E-106,
      0.0, 0.0, -4.5498998166004214E-110, 1.1393600860926635E-108,
      1.6867580986889374E-109, -4.2238838875702256E-108, 0.0, 0.0,
      -7.940051874482339E-108, -6.9003740400911051E-106, 2.9435696044182919E-107,
      2.5581358415058804E-105, 0.0, 0.0, 1.6867580986889367E-109,
      -4.22388388757023E-108, -6.2532209459032649E-109, 1.5658960949615331E-107,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

    static const real_T d_a[12] = { 0.99999999999999989, 128.80000000000004,
      -3.9987123224974528E-17, 28.8, 0.0, 0.0, 3.8102544865735674E-17, 28.8,
      1.0000000000000002, 29.800000000000015, 0.0, 0.0 };

    static const real_T e_a[12] = { -7.6223636067132357E-72,
      1.9087490286024214E-70, 2.825794866486067E-71, -7.0761951078856582E-70,
      0.068254858490424675, 9.5985356006503148E-17, 7.8074771293816959E-72,
      -1.9551041062142269E-70, -2.8944209343389549E-71, 7.2480446116742668E-70,
      9.5985356006503111E-17, 0.068254858490424661 };

    real_T rtb_Velocidad;
    real_T rtb_ActuadorMotorTm001s;
    real_T rtb_last_x[6];
    boolean_T rtb_RelationalOperator;
    real_T rtb_Sum2;
    real_T rtb_TmpSignalConversionAtSFun_g[2];
    real_T rtb_xest[6];
    uint8_T rtb_Gain1;
    uint8_T rtb_Gain;
    int32_T i;
    real_T b_Mlim_0[6];
    real_T tmp[2];
    real_T rtb_last_mv_idx_0;
    real_T rtb_last_mv_idx_1;
    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[2] == 0) {
      /* DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' incorporates:
       *  Delay: '<Root>/Delay Tm=0.01'
       *  Inport: '<Root>/Par'
       *  Sum: '<Root>/Sum2'
       */
      todo_DW.EjeTm001s_tmp = (todo_DW.DelayTm001_DSTATE[0] - todo_U.Par) -
        -0.9997 * todo_DW.EjeTm001s_states;
      rtb_Velocidad = 0.00015 * todo_DW.EjeTm001s_tmp + 0.00015 *
        todo_DW.EjeTm001s_states;

      /* Gain: '<Root>/ Generador2' incorporates:
       *  Gain: '<Root>/ Generador1'
       */
      todo_B.Generador2 = 0.5 * rtb_Velocidad * 340.0;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* S-Function (sfun_spssw_discc): '<S124>/State-Space' incorporates:
       *  Constant: '<S128>/SwitchCurrents'
       */

      /* S-Function block: <S124>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*) todo_DW.StateSpace_PWORK.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          todo_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*) todo_DW.StateSpace_PWORK.SW_CHG;
        int_T *gState = (int_T*) todo_DW.StateSpace_PWORK.G_STATE;
        real_T *yswitch = (real_T*)todo_DW.StateSpace_PWORK.Y_SWITCH;
        int_T *switchTypes = (int_T*) todo_DW.StateSpace_PWORK.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*) todo_DW.StateSpace_PWORK.IDX_OUT_SW;
        real_T *DxCol = (real_T*)todo_DW.StateSpace_PWORK.DX_COL;
        real_T *tmp2 = (real_T*)todo_DW.StateSpace_PWORK.TMP2;
        real_T *BDcol = (real_T*)todo_DW.StateSpace_PWORK.BD_COL;
        real_T *tmp1 = (real_T*)todo_DW.StateSpace_PWORK.TMP1;
        real_T *uswlast = (real_T*)todo_DW.StateSpace_PWORK.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 8 * sizeof(int_T));
        memcpy(uswlast, &todo_B.StateSpace_o1[0], 8*sizeof(real_T));
        do {
          if (loopsToDo == 1) {        /* Need to reset some variables: */
            swChanged = 0;

            /* return to the original switch status*/
            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
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
            real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK.CS;
            real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK.DS;

            {
              int_T i1;
              real_T *y0 = &todo_B.StateSpace_o1[0];
              for (i1=0; i1 < 11; i1++) {
                accum = 0.0;
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE[0];
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE[1];
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE[2];

                {
                  int_T i2;
                  const real_T *u0 = todo_ConstP.pooled16;
                  for (i2=0; i2 < 8; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  accum += *(Ds++) * todo_B.Generador2;
                }

                y0[i1] = accum;
              }
            }

            swChanged = 0;

            {
              int_T i1;
              real_T *y0 = &todo_B.StateSpace_o1[0];
              for (i1=0; i1 < 8; i1++) {
                switch (switchTypes[i1]) {
                 case 1 :              /* Ideal switch */
                  newState = gState[i1] > 0 ? 1 : 0;
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
            real_T *As = (real_T*)todo_DW.StateSpace_PWORK.AS;
            real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK.CS;
            real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK.BS;
            real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*10]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      DxCol[i2]= Ds[i2 * 9 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;
                  BDcol[0]= Bs[0 + i1]*a1;
                  BDcol[1]= Bs[9 + i1]*a1;
                  BDcol[2]= Bs[18 + i1]*a1;

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 3], 3 * sizeof(real_T));
                  memset(&Cs[i1 * 3], '\0', 3 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 9], 9 * sizeof(real_T));
                  memset(&Ds[i1 * 9], '\0', 9 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      a1 = DxCol[i2];
                      Cs[i2 * 3 + 0] += a1 * tmp1[0];
                      Cs[i2 * 3 + 1] += a1 * tmp1[1];
                      Cs[i2 * 3 + 2] += a1 * tmp1[2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 9; i3++) {
                          Ds[i2 * 9 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  a1 = BDcol[0];
                  As[0 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[0 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[0 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[0 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[1];
                  As[3 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[3 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[3 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[9 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[2];
                  As[6 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[6 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[6 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[18 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }
                }
              }
            }
          }                            /* if (swChanged) */
        } while (swChanged > 0 && --loopsToDo > 0);

        if (loopsToDo == 0) {
          real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK.CS;
          real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK.DS;

          {
            int_T i1;
            real_T *y0 = &todo_B.StateSpace_o1[0];
            for (i1=0; i1 < 11; i1++) {
              accum = 0.0;
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE[0];
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE[1];
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE[2];

              {
                int_T i2;
                const real_T *u0 = todo_ConstP.pooled16;
                for (i2=0; i2 < 8; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                accum += *(Ds++) * todo_B.Generador2;
              }

              y0[i1] = accum;
            }
          }
        }

        /* Output new switches states */
        {
          int_T i1;
          real_T *y1 = &todo_B.StateSpace_o2[0];
          for (i1=0; i1 < 8; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }

      /* Outport: '<Root>/Volt' */
      todo_Y.Volt = todo_B.StateSpace_o1[8];

      /* Outport: '<Root>/Current' */
      todo_Y.Current = todo_B.StateSpace_o1[10];
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[2] == 0) {
      /* DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' incorporates:
       *  Inport: '<Root>/Actuador'
       */
      todo_DW.ActuadorMotorTm001s_tmp = todo_U.Actuador - -0.92307692307692313 *
        todo_DW.ActuadorMotorTm001s_states;
      rtb_ActuadorMotorTm001s = 0.038461538461538464 *
        todo_DW.ActuadorMotorTm001s_tmp + 0.038461538461538464 *
        todo_DW.ActuadorMotorTm001s_states;

      /* Outport: '<Root>/Flujo' */
      todo_Y.Flujo = rtb_ActuadorMotorTm001s;

      /* Outport: '<Root>/Velocidad' */
      todo_Y.Velocidad = rtb_Velocidad;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[3] == 0) {
      /* Memory: '<S9>/last_x' */
      for (i = 0; i < 6; i++) {
        rtb_last_x[i] = todo_DW.last_x_PreviousInput[i];
      }

      /* End of Memory: '<S9>/last_x' */

      /* UnitDelay: '<S9>/last_mv' */
      rtb_last_mv_idx_0 = todo_DW.last_mv_DSTATE[0];
      rtb_last_mv_idx_1 = todo_DW.last_mv_DSTATE[1];
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* S-Function (sfun_spssw_discc): '<S125>/State-Space' incorporates:
       *  Constant: '<S132>/SwitchCurrents'
       */

      /* S-Function block: <S125>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*) todo_DW.StateSpace_PWORK_p.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          todo_DW.StateSpace_PWORK_p.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*) todo_DW.StateSpace_PWORK_p.SW_CHG;
        int_T *gState = (int_T*) todo_DW.StateSpace_PWORK_p.G_STATE;
        real_T *yswitch = (real_T*)todo_DW.StateSpace_PWORK_p.Y_SWITCH;
        int_T *switchTypes = (int_T*) todo_DW.StateSpace_PWORK_p.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*) todo_DW.StateSpace_PWORK_p.IDX_OUT_SW;
        real_T *DxCol = (real_T*)todo_DW.StateSpace_PWORK_p.DX_COL;
        real_T *tmp2 = (real_T*)todo_DW.StateSpace_PWORK_p.TMP2;
        real_T *BDcol = (real_T*)todo_DW.StateSpace_PWORK_p.BD_COL;
        real_T *tmp1 = (real_T*)todo_DW.StateSpace_PWORK_p.TMP1;
        real_T *uswlast = (real_T*)todo_DW.StateSpace_PWORK_p.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 8 * sizeof(int_T));
        memcpy(uswlast, &todo_B.StateSpace_o1_f[0], 8*sizeof(real_T));
        do {
          if (loopsToDo == 1) {        /* Need to reset some variables: */
            swChanged = 0;

            /* return to the original switch status*/
            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
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
            real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK_p.CS;
            real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK_p.DS;

            {
              int_T i1;
              real_T *y0 = &todo_B.StateSpace_o1_f[0];
              for (i1=0; i1 < 11; i1++) {
                accum = 0.0;
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[0];
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[1];
                accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[2];

                {
                  int_T i2;
                  const real_T *u0 = todo_ConstP.pooled16;
                  for (i2=0; i2 < 8; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  accum += *(Ds++) * todo_B.Generador2;
                }

                y0[i1] = accum;
              }
            }

            swChanged = 0;

            {
              int_T i1;
              real_T *y0 = &todo_B.StateSpace_o1_f[0];
              for (i1=0; i1 < 8; i1++) {
                switch (switchTypes[i1]) {
                 case 1 :              /* Ideal switch */
                  newState = gState[i1] > 0 ? 1 : 0;
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
            real_T *As = (real_T*)todo_DW.StateSpace_PWORK_p.AS;
            real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK_p.CS;
            real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK_p.BS;
            real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK_p.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*10]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      DxCol[i2]= Ds[i2 * 9 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;
                  BDcol[0]= Bs[0 + i1]*a1;
                  BDcol[1]= Bs[9 + i1]*a1;
                  BDcol[2]= Bs[18 + i1]*a1;

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 3], 3 * sizeof(real_T));
                  memset(&Cs[i1 * 3], '\0', 3 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 9], 9 * sizeof(real_T));
                  memset(&Ds[i1 * 9], '\0', 9 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      a1 = DxCol[i2];
                      Cs[i2 * 3 + 0] += a1 * tmp1[0];
                      Cs[i2 * 3 + 1] += a1 * tmp1[1];
                      Cs[i2 * 3 + 2] += a1 * tmp1[2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 9; i3++) {
                          Ds[i2 * 9 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  a1 = BDcol[0];
                  As[0 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[0 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[0 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[0 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[1];
                  As[3 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[3 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[3 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[9 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[2];
                  As[6 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[6 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[6 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[18 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }
                }
              }
            }
          }                            /* if (swChanged) */
        } while (swChanged > 0 && --loopsToDo > 0);

        if (loopsToDo == 0) {
          real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK_p.CS;
          real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK_p.DS;

          {
            int_T i1;
            real_T *y0 = &todo_B.StateSpace_o1_f[0];
            for (i1=0; i1 < 11; i1++) {
              accum = 0.0;
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[0];
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[1];
              accum += *(Cs++) * todo_DW.StateSpace_DSTATE_e[2];

              {
                int_T i2;
                const real_T *u0 = todo_ConstP.pooled16;
                for (i2=0; i2 < 8; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                accum += *(Ds++) * todo_B.Generador2;
              }

              y0[i1] = accum;
            }
          }
        }

        /* Output new switches states */
        {
          int_T i1;
          real_T *y1 = &todo_B.StateSpace_o2_j[0];
          for (i1=0; i1 < 8; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[3] == 0) {
      /* MATLAB Function: '<S9>/optimizer' incorporates:
       *  Inport: '<Root>/ref1'
       *  Inport: '<Root>/ref2'
       */
      /* MATLAB Function 'MPC Controller/MPC/optimizer': '<S24>:1' */
      /* '<S24>:1:13' coder.extrinsic('mpcblock_optimizer_double_mex'); */
      /* '<S24>:1:14' coder.extrinsic('mpcblock_optimizer_single_mex'); */
      /* '<S24>:1:15' coder.extrinsic('mpcblock_refmd_double_mex'); */
      /* '<S24>:1:16' coder.extrinsic('mpcblock_refmd_single_mex'); */
      /*  Parameters */
      /* '<S24>:1:19' isSimulation = coder.target('Sfun') && ~coder.target('RtwForRapid') && ~coder.target('RtwForSim'); */
      /* '<S24>:1:20' isAdaptive = false; */
      /* '<S24>:1:21' isLTV = false; */
      /* '<S24>:1:22' isDouble = isa(ref,'double'); */
      /* '<S24>:1:23' ZERO = zeros('like',ref); */
      /* '<S24>:1:24' ONE = ones('like',ref); */
      /*  Pre-allocate all the MEX block outputs for the simulation mode */
      /* '<S24>:1:29' if isSimulation */
      /*  Get reference and MD signals -- accounting for previewing */
      /* '<S24>:1:43' if isSimulation */
      /* '<S24>:1:50' else */
      /*  When doing code generation, use M code directly */
      /* '<S24>:1:52' [rseq, vseq, v] = mpcblock_refmd(ref,md,nv,ny,p,yoff,voff,no_md,no_ref,openloopflag, Rscale, MDscale); */
      for (i = 0; i < 6; i++) {
        rseq[i] = 0.0;
      }

      for (k = 0; k < 3; k++) {
        rseq[k * (int32_T)todo_ny] = todo_U.ref1;
        rseq[1 + k * (int32_T)todo_ny] = todo_U.ref2;
      }

      /* SignalConversion: '<S24>/TmpSignal ConversionAt SFunction Inport3' incorporates:
       *  MATLAB Function: '<S9>/optimizer'
       */
      /*  External MV override.   */
      /*  NOTE: old_u and ext_mv input signals are dimensionless but include offset */
      /* '<S24>:1:57' old_u = old_u - uoff; */
      /* '<S24>:1:58' if no_mv==ONE */
      /* '<S24>:1:59' delmv = zeros(nu,1,'like',ref); */
      /*  Obtain x[k|k] */
      /* '<S24>:1:67' xk = xk - xoff; */
      /*  Remove offset */
      /* '<S24>:1:68' if CustomEstimation==ONE */
      /* '<S24>:1:71' else */
      /*  Default state estimation.     */
      /*  Scale measured output and remove offset. */
      /* '<S24>:1:74' ym = ym.*Rscale(myindex) - myoff; */
      /*  Correct x(k|k-1) for possible external mv override. */
      /*  NOTE:  Offset was removed from x[k|k-1] at k=0. */
      /* '<S24>:1:77' xk = xk + Bu*delmv; */
      /*  Measurement upate to x(k|k) */
      /* '<S24>:1:79' ym_est = C(myindex,:)*xk + Dv(myindex,:)*v; */
      /* '<S24>:1:80' y_innov = ym - ym_est; */
      tmp[0] = todo_B.StateSpace_o1[10];
      tmp[1] = todo_B.StateSpace_o1_f[10];

      /* MATLAB Function: '<S9>/optimizer' incorporates:
       *  Memory: '<S9>/Memory'
       */
      for (k = 0; k < 2; k++) {
        rtb_Sum2 = 0.0;
        for (i = 0; i < 6; i++) {
          rtb_Sum2 += (real_T)b_a[(i << 1) + k] * rtb_last_x[i];
        }

        rtb_TmpSignalConversionAtSFun_g[k] = tmp[k] - rtb_Sum2;
      }

      /* '<S24>:1:81' xest = xk + M*y_innov; */
      for (k = 0; k < 6; k++) {
        rtb_xest[k] = (a[k + 6] * rtb_TmpSignalConversionAtSFun_g[1] + a[k] *
                       rtb_TmpSignalConversionAtSFun_g[0]) + rtb_last_x[k];
      }

      /*  Real-time MV target override */
      /*  Note: utargetValue is a vector length p*nu.   */
      /* '<S24>:1:86' if no_uref==ONE */
      /*  no external utarget */
      /* '<S24>:1:88' utargetValue = utarget; */
      /* '<S24>:1:96' if isSimulation */
      /* '<S24>:1:121' else */
      /*  When doing code generation, use M code directly */
      /* '<S24>:1:123' [u, cost, useq, status, iAout] = mpcblock_optimizer(... */
      /* '<S24>:1:124'             rseq, vseq, umin, umax, ymin, ymax, switch_in, xest, old_u, iA, ... */
      /* '<S24>:1:125'             isQP, nu, ny, degrees, Hinv, Kx, Ku1, Kut, Kr, Kv, Mlim, ... */
      /* '<S24>:1:126'             Mx, Mu1, Mv, z_degrees, utargetValue, p, uoff, voff, yoff, maxiter, CustomSolver, nxQP, openloopflag, ... */
      /* '<S24>:1:127'             lims_inport, no_umin, no_umax, no_ymin, no_ymax, switch_inport, ... */
      /* '<S24>:1:128'             no_switch, enable_value, return_cost, H, return_sequence, Linv, Ac, ... */
      /* '<S24>:1:129'             ywt, uwt, duwt, rhoeps, no_ywt, no_uwt, no_duwt, no_rhoeps,... */
      /* '<S24>:1:130'             Wy, Wdu, Jm, SuJm, Su1, Sx, Hv, Wu, I1, ... */
      /* '<S24>:1:131'             isAdaptive, isLTV, A, Bu, Bv, C, Dv, ... */
      /* '<S24>:1:132'             Mrows, nCC, Ecc, Fcc, Scc, Gcc); */
      f[0] = 0.0;
      f[1] = 0.0;
      f[2] = 0.0;
      for (i = 0; i < 2; i++) {
        rtb_Sum2 = 0.0;
        rtb_Velocidad = 0.0;
        for (k = 0; k < 6; k++) {
          rtb_Sum2 += b_Kx[6 * i + k] * rtb_xest[k];
          rtb_Velocidad += b_Kr[6 * i + k] * rseq[k];
        }

        f[i] = (b_Ku1[(i << 1) + 1] * rtb_last_mv_idx_1 + b_Ku1[i << 1] *
                rtb_last_mv_idx_0) + (rtb_Sum2 + rtb_Velocidad);
      }

      for (i = 0; i < 6; i++) {
        iAnew[i] = todo_DW.Memory_PreviousInput[i];
        rtb_Sum2 = 0.0;
        for (k = 0; k < 6; k++) {
          rtb_Sum2 += 0.0 * rtb_xest[k];
        }

        b_Mlim_0[i] = -(((real_T)b_Mlim[i] + rtb_Sum2) + ((real_T)b_Mu1[i + 6] *
          rtb_last_mv_idx_1 + (real_T)b_Mu1[i] * rtb_last_mv_idx_0));
      }

      todo_qpkwik(b_Linv, b_Hinv, f, b_Ac, b_Mlim_0, iAnew, 120, 1.0E-6, zopt,
                  rseq, &rtb_Sum2);
      if (rtb_Sum2 <= 0.0) {
        zopt[0] = 0.0;
        zopt[1] = 0.0;
      }

      todo_B.u[0] = rtb_last_mv_idx_0 + zopt[0];
      todo_B.u[1] = rtb_last_mv_idx_1 + zopt[1];

      /* '<S24>:1:135' if CustomEstimation==ONE */
      /* '<S24>:1:137' else */
      /*  update x[k+1|k], assuming that above u and v will be applied. */
      /* '<S24>:1:139' xk1 = A*xk + Bu*(u - uoff) + Bv*v + L*y_innov; */
      /* '<S24>:1:141' xk1 = xk1 + xoff; */
      /*  Updated state must include offset */
      /* '<S24>:1:143' if CustomEstimation==ONE */
      /* '<S24>:1:146' else */
      /* '<S24>:1:147' xest = xest + xoff; */
      for (i = 0; i < 6; i++) {
        todo_B.iAout[i] = (iAnew[i] != 0);
        rseq[i] = 0.0;
        for (k = 0; k < 6; k++) {
          rseq[i] += c_a[6 * k + i] * rtb_last_x[k];
        }

        todo_B.xk1[i] = (e_a[i + 6] * rtb_TmpSignalConversionAtSFun_g[1] + e_a[i]
                         * rtb_TmpSignalConversionAtSFun_g[0]) + (rseq[i] +
          (d_a[i + 6] * todo_B.u[1] + d_a[i] * todo_B.u[0]));
      }

      /* Outport: '<Root>/u2' */
      todo_Y.u2 = todo_B.u[0];

      /* Outport: '<Root>/u3' */
      todo_Y.u3 = todo_B.u[1];
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/Volt1' */
      todo_Y.Volt1 = todo_B.StateSpace_o1_f[8];

      /* Outport: '<Root>/Current1' */
      todo_Y.Current1 = todo_B.StateSpace_o1_f[10];
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[2] == 0) {
      /* Gain: '<Root>/ 1' */
      rtb_u = 1.15 * rtb_ActuadorMotorTm001s;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
      todo_B.DiscreteTransferFcn = 0.001167 *
        todo_DW.DiscreteTransferFcn_states[0] + -0.001167 *
        todo_DW.DiscreteTransferFcn_states[1];

      /* Gain: '<S5>/Gain' */
      todo_B.Gain = 0.00333 * todo_B.StateSpace_o1[8];
    }

    /* RelationalOperator: '<S29>/Relational Operator' incorporates:
     *  Clock: '<S73>/Clock'
     *  Constant: '<S73>/Constant'
     *  Lookup_n-D: '<S73>/Look-Up Table1'
     *  Math: '<S73>/Math Function'
     *  S-Function (sfun_tstart): '<S73>/startTime'
     *  Sum: '<S73>/Sum'
     */
    rtb_RelationalOperator = (look1_binlxpw(rt_remd_snf(todo_M->Timing.t[0] -
      (0.0), 0.0002), todo_ConstP.pooled26, todo_ConstP.pooled25, 2U) >=
      todo_B.DiscreteTransferFcn);

    /* Gain: '<S29>/Gain' */
    rtb_Gain1 = (uint8_T)(rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S49>/Data Type Conversion' */
    todo_B.DataTypeConversion = (real_T)rtb_Gain1 * 0.0625;

    /* Gain: '<S29>/Gain1' incorporates:
     *  Logic: '<S29>/Logical Operator'
     */
    rtb_Gain = (uint8_T)(!rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S56>/Data Type Conversion' */
    todo_B.DataTypeConversion_o = (real_T)rtb_Gain * 0.0625;

    /* DataTypeConversion: '<S63>/Data Type Conversion' */
    todo_B.DataTypeConversion_g = (real_T)rtb_Gain * 0.0625;

    /* DataTypeConversion: '<S70>/Data Type Conversion' */
    todo_B.DataTypeConversion_d = (real_T)rtb_Gain1 * 0.0625;

    /* StateSpace: '<S30>/State-Space' */
    rtb_last_mv_idx_0 = 24674.011002723397 * todo_X.StateSpace_CSTATE[1];

    /* Integrator: '<S25>/Integrator' */
    /* Limited  Integrator  */
    if (todo_X.Integrator_CSTATE >= (rtInf)) {
      todo_X.Integrator_CSTATE = (rtInf);
    } else {
      if (todo_X.Integrator_CSTATE <= (rtMinusInf)) {
        todo_X.Integrator_CSTATE = (rtMinusInf);
      }
    }

    /* Math: '<S25>/Math Function' incorporates:
     *  Constant: '<S25>/Constant4'
     *  Integrator: '<S25>/Integrator'
     */
    rtb_Sum2 = rt_modd_snf(todo_X.Integrator_CSTATE, 6.2831853071795862);

    /* Trigonometry: '<S25>/Trigonometric Function' */
    rtb_ActuadorMotorTm001s = sin(rtb_Sum2);

    /* Trigonometry: '<S25>/Trigonometric Function2' */
    rtb_Sum2 = cos(rtb_Sum2);

    /* Outputs for Enabled SubSystem: '<S25>/Automatic Gain Control' */

    /* Constant: '<S25>/Constant1' */
    todo_AutomaticGainControl(todo_M, 0.0, todo_B.Gain, rtb_last_mv_idx_0,
      rtb_ActuadorMotorTm001s, rtb_Sum2, &todo_B.MathFunction_h,
      &todo_B.AutomaticGainControl, &todo_DW.AutomaticGainControl,
      &todo_X.AutomaticGainControl);

    /* End of Outputs for SubSystem: '<S25>/Automatic Gain Control' */

    /* Saturate: '<S33>/To avoid division by zero' */
    if (rtb_last_mv_idx_0 > 1.0E+6) {
      rtb_Velocidad = 1.0E+6;
    } else if (rtb_last_mv_idx_0 < 1.0E-6) {
      rtb_Velocidad = 1.0E-6;
    } else {
      rtb_Velocidad = rtb_last_mv_idx_0;
    }

    /* End of Saturate: '<S33>/To avoid division by zero' */

    /* Fcn: '<S33>/Number of samples per cycle' */
    todo_B.Delay = 1.0 / rtb_Velocidad;

    /* VariableTransportDelay: '<S33>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = todo_B.Delay;

      /* For variable time delay, output here */
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      todo_B.VariableTransportDelay = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        todo_DW.VariableTransportDelay_IWORK.CircularBufSize,
        &todo_DW.VariableTransportDelay_IWORK.Last,
        todo_DW.VariableTransportDelay_IWORK.Tail,
        todo_DW.VariableTransportDelay_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* Integrator: '<S33>/Integrator' */
    todo_B.Integrator_l = todo_X.Integrator_CSTATE_h;

    /* Switch: '<S33>/Switch' incorporates:
     *  Constant: '<S33>/Constant'
     *  Product: '<S33>/Product'
     *  Step: '<S33>/Step'
     *  Sum: '<S33>/Sum7'
     */
    if (!(todo_M->Timing.t[0] < 0.016666666666666666) >= 0.5) {
      rtb_last_mv_idx_0 *= todo_B.Integrator_l - todo_B.VariableTransportDelay;
    } else {
      rtb_last_mv_idx_0 = 0.0;
    }

    /* End of Switch: '<S33>/Switch' */

    /* Product: '<S25>/Divide' */
    todo_B.Divide = rtb_last_mv_idx_0 * todo_B.MathFunction_h;

    /* Integrator: '<S32>/Integrator' */
    /* Limited  Integrator  */
    if (todo_X.Integrator_CSTATE_f >= 10000.0) {
      todo_X.Integrator_CSTATE_f = 10000.0;
    } else {
      if (todo_X.Integrator_CSTATE_f <= 0.0) {
        todo_X.Integrator_CSTATE_f = 0.0;
      }
    }

    /* Derivative: '<S32>/Derivative' */
    if ((todo_DW.TimeStampA >= todo_M->Timing.t[0]) && (todo_DW.TimeStampB >=
         todo_M->Timing.t[0])) {
      rtb_last_mv_idx_0 = 0.0;
    } else {
      rtb_Velocidad = todo_DW.TimeStampA;
      lastU = &todo_DW.LastUAtTimeA;
      if (todo_DW.TimeStampA < todo_DW.TimeStampB) {
        if (todo_DW.TimeStampB < todo_M->Timing.t[0]) {
          rtb_Velocidad = todo_DW.TimeStampB;
          lastU = &todo_DW.LastUAtTimeB;
        }
      } else {
        if (todo_DW.TimeStampA >= todo_M->Timing.t[0]) {
          rtb_Velocidad = todo_DW.TimeStampB;
          lastU = &todo_DW.LastUAtTimeB;
        }
      }

      rtb_last_mv_idx_0 = (todo_B.Divide - *lastU) / (todo_M->Timing.t[0] -
        rtb_Velocidad);
    }

    /* End of Derivative: '<S32>/Derivative' */

    /* Sum: '<S32>/Sum6' incorporates:
     *  Gain: '<S32>/Kp4'
     *  Integrator: '<S32>/Integrator'
     */
    rtb_Velocidad = (180.0 * todo_B.Divide + todo_X.Integrator_CSTATE_f) +
      rtb_last_mv_idx_0;

    /* Saturate: '<S32>/Saturation2' */
    if (rtb_Velocidad > 10000.0) {
      todo_B.Saturation2 = 10000.0;
    } else if (rtb_Velocidad < 0.0) {
      todo_B.Saturation2 = 0.0;
    } else {
      todo_B.Saturation2 = rtb_Velocidad;
    }

    /* End of Saturate: '<S32>/Saturation2' */

    /* Gain: '<S25>/Gain10' */
    rtb_Velocidad = 0.15915494309189535 * todo_B.Saturation2;

    /* Gain: '<S32>/Kp5' */
    todo_B.Kp5 = 3200.0 * todo_B.Divide;

    /* Product: '<S25>/Product1' */
    todo_B.Vq = todo_B.Gain * rtb_Sum2;

    /* RateLimiter: '<S25>/Rate Limiter' */
    if ((todo_DW.LastMajorTimeA >= todo_M->Timing.t[0]) &&
        (todo_DW.LastMajorTimeB >= todo_M->Timing.t[0])) {
      todo_B.RateLimiter = rtb_Velocidad;
    } else {
      if (((todo_DW.LastMajorTimeA < todo_DW.LastMajorTimeB) &&
           (todo_DW.LastMajorTimeB < todo_M->Timing.t[0])) ||
          ((todo_DW.LastMajorTimeA >= todo_DW.LastMajorTimeB) &&
           (todo_DW.LastMajorTimeA >= todo_M->Timing.t[0]))) {
        rtb_last_mv_idx_1 = todo_M->Timing.t[0] - todo_DW.LastMajorTimeB;
        rtb_last_mv_idx_0 = todo_DW.PrevYB;
      } else {
        rtb_last_mv_idx_1 = todo_M->Timing.t[0] - todo_DW.LastMajorTimeA;
        rtb_last_mv_idx_0 = todo_DW.PrevYA;
      }

      riseValLimit = rtb_last_mv_idx_1 * 12.0;
      rtb_Sum2 = rtb_Velocidad - rtb_last_mv_idx_0;
      if (rtb_Sum2 > riseValLimit) {
        todo_B.RateLimiter = rtb_last_mv_idx_0 + riseValLimit;
      } else {
        rtb_last_mv_idx_1 *= -12.0;
        if (rtb_Sum2 < rtb_last_mv_idx_1) {
          todo_B.RateLimiter = rtb_last_mv_idx_0 + rtb_last_mv_idx_1;
        } else {
          todo_B.RateLimiter = rtb_Velocidad;
        }
      }
    }

    /* End of RateLimiter: '<S25>/Rate Limiter' */

    /* Sum: '<S5>/Sum2' incorporates:
     *  Product: '<S5>/Product'
     */
    todo_B.Sum2 = rtb_ActuadorMotorTm001s * todo_B.u[0] - todo_B.StateSpace_o1
      [10];
    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* DiscreteTransferFcn: '<S75>/Discrete Transfer Fcn' */
      todo_B.DiscreteTransferFcn_c = 0.001167 *
        todo_DW.DiscreteTransferFcn_states_e[0] + -0.001167 *
        todo_DW.DiscreteTransferFcn_states_e[1];

      /* Gain: '<S6>/Gain' */
      todo_B.Gain_j = 0.00333 * todo_B.StateSpace_o1_f[8];
    }

    /* RelationalOperator: '<S78>/Relational Operator' incorporates:
     *  Clock: '<S122>/Clock'
     *  Constant: '<S122>/Constant'
     *  Lookup_n-D: '<S122>/Look-Up Table1'
     *  Math: '<S122>/Math Function'
     *  S-Function (sfun_tstart): '<S122>/startTime'
     *  Sum: '<S122>/Sum'
     */
    rtb_RelationalOperator = (look1_binlxpw(rt_remd_snf(todo_M->Timing.t[0] -
      (0.0), 0.0002), todo_ConstP.pooled26, todo_ConstP.pooled25, 2U) >=
      todo_B.DiscreteTransferFcn_c);

    /* Gain: '<S78>/Gain' */
    rtb_Gain = (uint8_T)(rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S98>/Data Type Conversion' */
    todo_B.DataTypeConversion_e = (real_T)rtb_Gain * 0.0625;

    /* Gain: '<S78>/Gain1' incorporates:
     *  Logic: '<S78>/Logical Operator'
     */
    rtb_Gain1 = (uint8_T)(!rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S105>/Data Type Conversion' */
    todo_B.DataTypeConversion_h = (real_T)rtb_Gain1 * 0.0625;

    /* DataTypeConversion: '<S112>/Data Type Conversion' */
    todo_B.DataTypeConversion_dn = (real_T)rtb_Gain1 * 0.0625;

    /* DataTypeConversion: '<S119>/Data Type Conversion' */
    todo_B.DataTypeConversion_n = (real_T)rtb_Gain * 0.0625;

    /* StateSpace: '<S79>/State-Space' */
    rtb_Velocidad = 24674.011002723397 * todo_X.StateSpace_CSTATE_h[1];

    /* Integrator: '<S74>/Integrator' */
    /* Limited  Integrator  */
    if (todo_X.Integrator_CSTATE_fl >= (rtInf)) {
      todo_X.Integrator_CSTATE_fl = (rtInf);
    } else {
      if (todo_X.Integrator_CSTATE_fl <= (rtMinusInf)) {
        todo_X.Integrator_CSTATE_fl = (rtMinusInf);
      }
    }

    /* Math: '<S74>/Math Function' incorporates:
     *  Constant: '<S74>/Constant4'
     *  Integrator: '<S74>/Integrator'
     */
    rtb_Sum2 = rt_modd_snf(todo_X.Integrator_CSTATE_fl, 6.2831853071795862);

    /* Trigonometry: '<S74>/Trigonometric Function' */
    rtb_ActuadorMotorTm001s = sin(rtb_Sum2);

    /* Trigonometry: '<S74>/Trigonometric Function2' */
    rtb_last_mv_idx_0 = cos(rtb_Sum2);

    /* Outputs for Enabled SubSystem: '<S74>/Automatic Gain Control' */

    /* Constant: '<S74>/Constant1' */
    todo_AutomaticGainControl(todo_M, 0.0, todo_B.Gain_j, rtb_Velocidad,
      rtb_ActuadorMotorTm001s, rtb_last_mv_idx_0, &todo_B.MathFunction,
      &todo_B.AutomaticGainControl_c, &todo_DW.AutomaticGainControl_c,
      &todo_X.AutomaticGainControl_c);

    /* End of Outputs for SubSystem: '<S74>/Automatic Gain Control' */

    /* Saturate: '<S82>/To avoid division by zero' */
    if (rtb_Velocidad > 1.0E+6) {
      rtb_Sum2 = 1.0E+6;
    } else if (rtb_Velocidad < 1.0E-6) {
      rtb_Sum2 = 1.0E-6;
    } else {
      rtb_Sum2 = rtb_Velocidad;
    }

    /* End of Saturate: '<S82>/To avoid division by zero' */

    /* Fcn: '<S82>/Number of samples per cycle' */
    todo_B.Delay_m = 1.0 / rtb_Sum2;

    /* VariableTransportDelay: '<S82>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = todo_B.Delay_m;

      /* For variable time delay, output here */
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      todo_B.VariableTransportDelay_m = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        todo_DW.VariableTransportDelay_IWORK_f.CircularBufSize,
        &todo_DW.VariableTransportDelay_IWORK_f.Last,
        todo_DW.VariableTransportDelay_IWORK_f.Tail,
        todo_DW.VariableTransportDelay_IWORK_f.Head,
        0.0,
        0,
        0);
    }

    /* Integrator: '<S82>/Integrator' */
    todo_B.Integrator_m = todo_X.Integrator_CSTATE_a;

    /* Switch: '<S82>/Switch' incorporates:
     *  Constant: '<S82>/Constant'
     *  Product: '<S82>/Product'
     *  Step: '<S82>/Step'
     *  Sum: '<S82>/Sum7'
     */
    if (!(todo_M->Timing.t[0] < 0.016666666666666666) >= 0.5) {
      rtb_Velocidad *= todo_B.Integrator_m - todo_B.VariableTransportDelay_m;
    } else {
      rtb_Velocidad = 0.0;
    }

    /* End of Switch: '<S82>/Switch' */

    /* Product: '<S74>/Divide' */
    todo_B.Divide_n = rtb_Velocidad * todo_B.MathFunction;

    /* Integrator: '<S81>/Integrator' */
    /* Limited  Integrator  */
    if (todo_X.Integrator_CSTATE_k >= 10000.0) {
      todo_X.Integrator_CSTATE_k = 10000.0;
    } else {
      if (todo_X.Integrator_CSTATE_k <= 0.0) {
        todo_X.Integrator_CSTATE_k = 0.0;
      }
    }

    /* Derivative: '<S81>/Derivative' */
    if ((todo_DW.TimeStampA_l >= todo_M->Timing.t[0]) && (todo_DW.TimeStampB_m >=
         todo_M->Timing.t[0])) {
      rtb_Velocidad = 0.0;
    } else {
      rtb_Velocidad = todo_DW.TimeStampA_l;
      lastU = &todo_DW.LastUAtTimeA_d;
      if (todo_DW.TimeStampA_l < todo_DW.TimeStampB_m) {
        if (todo_DW.TimeStampB_m < todo_M->Timing.t[0]) {
          rtb_Velocidad = todo_DW.TimeStampB_m;
          lastU = &todo_DW.LastUAtTimeB_f;
        }
      } else {
        if (todo_DW.TimeStampA_l >= todo_M->Timing.t[0]) {
          rtb_Velocidad = todo_DW.TimeStampB_m;
          lastU = &todo_DW.LastUAtTimeB_f;
        }
      }

      rtb_Velocidad = (todo_B.Divide_n - *lastU) / (todo_M->Timing.t[0] -
        rtb_Velocidad);
    }

    /* End of Derivative: '<S81>/Derivative' */

    /* Sum: '<S81>/Sum6' incorporates:
     *  Gain: '<S81>/Kp4'
     *  Integrator: '<S81>/Integrator'
     */
    rtb_Velocidad += 180.0 * todo_B.Divide_n + todo_X.Integrator_CSTATE_k;

    /* Saturate: '<S81>/Saturation2' */
    if (rtb_Velocidad > 10000.0) {
      todo_B.Saturation2_b = 10000.0;
    } else if (rtb_Velocidad < 0.0) {
      todo_B.Saturation2_b = 0.0;
    } else {
      todo_B.Saturation2_b = rtb_Velocidad;
    }

    /* End of Saturate: '<S81>/Saturation2' */

    /* Gain: '<S74>/Gain10' */
    rtb_Velocidad = 0.15915494309189535 * todo_B.Saturation2_b;

    /* Gain: '<S81>/Kp5' */
    todo_B.Kp5_p = 3200.0 * todo_B.Divide_n;

    /* Product: '<S74>/Product1' */
    todo_B.Vq_k = todo_B.Gain_j * rtb_last_mv_idx_0;

    /* RateLimiter: '<S74>/Rate Limiter' */
    if ((todo_DW.LastMajorTimeA_c >= todo_M->Timing.t[0]) &&
        (todo_DW.LastMajorTimeB_a >= todo_M->Timing.t[0])) {
      todo_B.RateLimiter_n = rtb_Velocidad;
    } else {
      if (((todo_DW.LastMajorTimeA_c < todo_DW.LastMajorTimeB_a) &&
           (todo_DW.LastMajorTimeB_a < todo_M->Timing.t[0])) ||
          ((todo_DW.LastMajorTimeA_c >= todo_DW.LastMajorTimeB_a) &&
           (todo_DW.LastMajorTimeA_c >= todo_M->Timing.t[0]))) {
        rtb_last_mv_idx_1 = todo_M->Timing.t[0] - todo_DW.LastMajorTimeB_a;
        rtb_last_mv_idx_0 = todo_DW.PrevYB_m;
      } else {
        rtb_last_mv_idx_1 = todo_M->Timing.t[0] - todo_DW.LastMajorTimeA_c;
        rtb_last_mv_idx_0 = todo_DW.PrevYA_n;
      }

      riseValLimit = rtb_last_mv_idx_1 * 12.0;
      rtb_Sum2 = rtb_Velocidad - rtb_last_mv_idx_0;
      if (rtb_Sum2 > riseValLimit) {
        todo_B.RateLimiter_n = rtb_last_mv_idx_0 + riseValLimit;
      } else {
        rtb_last_mv_idx_1 *= -12.0;
        if (rtb_Sum2 < rtb_last_mv_idx_1) {
          todo_B.RateLimiter_n = rtb_last_mv_idx_0 + rtb_last_mv_idx_1;
        } else {
          todo_B.RateLimiter_n = rtb_Velocidad;
        }
      }
    }

    /* End of RateLimiter: '<S74>/Rate Limiter' */

    /* Sum: '<S6>/Sum2' incorporates:
     *  Product: '<S6>/Product'
     */
    todo_B.Sum2_g = rtb_ActuadorMotorTm001s * todo_B.u[1] -
      todo_B.StateSpace_o1_f[10];
  }

  if (rtmIsMajorTimeStep(todo_M)) {
    real_T *lastU;
    real_T denAccum;
    int32_T i;
    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update for Delay: '<Root>/Delay Tm=0.01' */
      for (i = 0; i < 49; i++) {
        todo_DW.DelayTm001_DSTATE[i] = todo_DW.DelayTm001_DSTATE[i + 1];
      }

      todo_DW.DelayTm001_DSTATE[49] = rtb_u;

      /* End of Update for Delay: '<Root>/Delay Tm=0.01' */

      /* Update for DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' */
      todo_DW.EjeTm001s_states = todo_DW.EjeTm001s_tmp;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* Update for S-Function (sfun_spssw_discc): '<S124>/State-Space' incorporates:
       *  Constant: '<S128>/SwitchCurrents'
       */

      /* S-Function block: <S124>/State-Space */
      {
        const real_T *As = (real_T*)todo_DW.StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)todo_DW.StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[0] = accum;
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[1] = accum;
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[2] = accum;
        todo_DW.StateSpace_DSTATE[0] = xtmp[0];
        todo_DW.StateSpace_DSTATE[1] = xtmp[1];
        todo_DW.StateSpace_DSTATE[2] = xtmp[2];

        {
          int_T *gState = (int_T*)todo_DW.StateSpace_PWORK.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T) todo_B.DataTypeConversion;
          *(gState++) = (int_T) todo_B.DataTypeConversion_o;
          *(gState++) = (int_T) todo_B.DataTypeConversion_g;
          *(gState++) = (int_T) todo_B.DataTypeConversion_d;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update for DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' */
      todo_DW.ActuadorMotorTm001s_states = todo_DW.ActuadorMotorTm001s_tmp;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[3] == 0) {
      /* Update for Memory: '<S9>/last_x' */
      for (i = 0; i < 6; i++) {
        todo_DW.last_x_PreviousInput[i] = todo_B.xk1[i];
      }

      /* End of Update for Memory: '<S9>/last_x' */

      /* Update for UnitDelay: '<S9>/last_mv' */
      todo_DW.last_mv_DSTATE[0] = todo_B.u[0];
      todo_DW.last_mv_DSTATE[1] = todo_B.u[1];
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* Update for S-Function (sfun_spssw_discc): '<S125>/State-Space' incorporates:
       *  Constant: '<S132>/SwitchCurrents'
       */

      /* S-Function block: <S125>/State-Space */
      {
        const real_T *As = (real_T*)todo_DW.StateSpace_PWORK_p.AS;
        const real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK_p.BS;
        real_T *xtmp = (real_T*)todo_DW.StateSpace_PWORK_p.XTMP;
        real_T accum;

        /* Calculate new states... */
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[0] = accum;
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[1] = accum;
        accum = 0.0;
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[0];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[1];
        accum += *(As++) * todo_DW.StateSpace_DSTATE_e[2];

        {
          int_T i1;
          const real_T *u0 = todo_ConstP.pooled16;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          accum += *(Bs++) * todo_B.Generador2;
        }

        xtmp[2] = accum;
        todo_DW.StateSpace_DSTATE_e[0] = xtmp[0];
        todo_DW.StateSpace_DSTATE_e[1] = xtmp[1];
        todo_DW.StateSpace_DSTATE_e[2] = xtmp[2];

        {
          int_T *gState = (int_T*)todo_DW.StateSpace_PWORK_p.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T) todo_B.DataTypeConversion_e;
          *(gState++) = (int_T) todo_B.DataTypeConversion_h;
          *(gState++) = (int_T) todo_B.DataTypeConversion_dn;
          *(gState++) = (int_T) todo_B.DataTypeConversion_n;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }

      /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
      denAccum = (todo_B.Sum2 - -2.0 * todo_DW.DiscreteTransferFcn_states[0]) -
        0.9999 * todo_DW.DiscreteTransferFcn_states[1];
      todo_DW.DiscreteTransferFcn_states[1] =
        todo_DW.DiscreteTransferFcn_states[0];
      todo_DW.DiscreteTransferFcn_states[0] = denAccum;
    }

    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[3] == 0) {
      /* Update for Memory: '<S9>/Memory' */
      for (i = 0; i < 6; i++) {
        todo_DW.Memory_PreviousInput[i] = todo_B.iAout[i];
      }

      /* End of Update for Memory: '<S9>/Memory' */
    }

    /* Update for Enabled SubSystem: '<S25>/Automatic Gain Control' */
    tod_AutomaticGainControl_Update(todo_M, &todo_B.AutomaticGainControl,
      &todo_DW.AutomaticGainControl);

    /* End of Update for SubSystem: '<S25>/Automatic Gain Control' */

    /* Update for VariableTransportDelay: '<S33>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = todo_B.Delay;
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      todo_DW.VariableTransportDelay_IWORK.Head =
        ((todo_DW.VariableTransportDelay_IWORK.Head <
          (todo_DW.VariableTransportDelay_IWORK.CircularBufSize-1)) ?
         (todo_DW.VariableTransportDelay_IWORK.Head+1) : 0);
      if (todo_DW.VariableTransportDelay_IWORK.Head ==
          todo_DW.VariableTransportDelay_IWORK.Tail) {
        todo_DW.VariableTransportDelay_IWORK.Tail =
          ((todo_DW.VariableTransportDelay_IWORK.Tail <
            (todo_DW.VariableTransportDelay_IWORK.CircularBufSize-1)) ?
           (todo_DW.VariableTransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[todo_DW.VariableTransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[todo_DW.VariableTransportDelay_IWORK.Head] =
        todo_B.Integrator_l;

      /* when use fixed buffer, reset solver at when buffer is updated
       * to avoid output consistency fail.
       */
    }

    /* Update for Derivative: '<S32>/Derivative' */
    if (todo_DW.TimeStampA == (rtInf)) {
      todo_DW.TimeStampA = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeA;
    } else if (todo_DW.TimeStampB == (rtInf)) {
      todo_DW.TimeStampB = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeB;
    } else if (todo_DW.TimeStampA < todo_DW.TimeStampB) {
      todo_DW.TimeStampA = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeA;
    } else {
      todo_DW.TimeStampB = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeB;
    }

    *lastU = todo_B.Divide;

    /* End of Update for Derivative: '<S32>/Derivative' */

    /* Update for RateLimiter: '<S25>/Rate Limiter' */
    if (todo_DW.LastMajorTimeA == (rtInf)) {
      todo_DW.LastMajorTimeA = todo_M->Timing.t[0];
      todo_DW.PrevYA = todo_B.RateLimiter;
    } else if (todo_DW.LastMajorTimeB == (rtInf)) {
      todo_DW.LastMajorTimeB = todo_M->Timing.t[0];
      todo_DW.PrevYB = todo_B.RateLimiter;
    } else if (todo_DW.LastMajorTimeA < todo_DW.LastMajorTimeB) {
      todo_DW.LastMajorTimeA = todo_M->Timing.t[0];
      todo_DW.PrevYA = todo_B.RateLimiter;
    } else {
      todo_DW.LastMajorTimeB = todo_M->Timing.t[0];
      todo_DW.PrevYB = todo_B.RateLimiter;
    }

    /* End of Update for RateLimiter: '<S25>/Rate Limiter' */
    if (rtmIsMajorTimeStep(todo_M) &&
        todo_M->Timing.TaskCounters.TID[1] == 0) {
      /* Update for DiscreteTransferFcn: '<S75>/Discrete Transfer Fcn' */
      denAccum = (todo_B.Sum2_g - -2.0 * todo_DW.DiscreteTransferFcn_states_e[0])
        - 0.9999 * todo_DW.DiscreteTransferFcn_states_e[1];
      todo_DW.DiscreteTransferFcn_states_e[1] =
        todo_DW.DiscreteTransferFcn_states_e[0];
      todo_DW.DiscreteTransferFcn_states_e[0] = denAccum;
    }

    /* Update for Enabled SubSystem: '<S74>/Automatic Gain Control' */
    tod_AutomaticGainControl_Update(todo_M, &todo_B.AutomaticGainControl_c,
      &todo_DW.AutomaticGainControl_c);

    /* End of Update for SubSystem: '<S74>/Automatic Gain Control' */

    /* Update for VariableTransportDelay: '<S82>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[1];
      real_T simTime = todo_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = todo_B.Delay_m;
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      todo_DW.VariableTransportDelay_IWORK_f.Head =
        ((todo_DW.VariableTransportDelay_IWORK_f.Head <
          (todo_DW.VariableTransportDelay_IWORK_f.CircularBufSize-1)) ?
         (todo_DW.VariableTransportDelay_IWORK_f.Head+1) : 0);
      if (todo_DW.VariableTransportDelay_IWORK_f.Head ==
          todo_DW.VariableTransportDelay_IWORK_f.Tail) {
        todo_DW.VariableTransportDelay_IWORK_f.Tail =
          ((todo_DW.VariableTransportDelay_IWORK_f.Tail <
            (todo_DW.VariableTransportDelay_IWORK_f.CircularBufSize-1)) ?
           (todo_DW.VariableTransportDelay_IWORK_f.Tail+1) : 0);
      }

      (*tBuffer)[todo_DW.VariableTransportDelay_IWORK_f.Head] = simTime;
      (*uBuffer)[todo_DW.VariableTransportDelay_IWORK_f.Head] =
        todo_B.Integrator_m;

      /* when use fixed buffer, reset solver at when buffer is updated
       * to avoid output consistency fail.
       */
    }

    /* Update for Derivative: '<S81>/Derivative' */
    if (todo_DW.TimeStampA_l == (rtInf)) {
      todo_DW.TimeStampA_l = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeA_d;
    } else if (todo_DW.TimeStampB_m == (rtInf)) {
      todo_DW.TimeStampB_m = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeB_f;
    } else if (todo_DW.TimeStampA_l < todo_DW.TimeStampB_m) {
      todo_DW.TimeStampA_l = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeA_d;
    } else {
      todo_DW.TimeStampB_m = todo_M->Timing.t[0];
      lastU = &todo_DW.LastUAtTimeB_f;
    }

    *lastU = todo_B.Divide_n;

    /* End of Update for Derivative: '<S81>/Derivative' */

    /* Update for RateLimiter: '<S74>/Rate Limiter' */
    if (todo_DW.LastMajorTimeA_c == (rtInf)) {
      todo_DW.LastMajorTimeA_c = todo_M->Timing.t[0];
      todo_DW.PrevYA_n = todo_B.RateLimiter_n;
    } else if (todo_DW.LastMajorTimeB_a == (rtInf)) {
      todo_DW.LastMajorTimeB_a = todo_M->Timing.t[0];
      todo_DW.PrevYB_m = todo_B.RateLimiter_n;
    } else if (todo_DW.LastMajorTimeA_c < todo_DW.LastMajorTimeB_a) {
      todo_DW.LastMajorTimeA_c = todo_M->Timing.t[0];
      todo_DW.PrevYA_n = todo_B.RateLimiter_n;
    } else {
      todo_DW.LastMajorTimeB_a = todo_M->Timing.t[0];
      todo_DW.PrevYB_m = todo_B.RateLimiter_n;
    }

    /* End of Update for RateLimiter: '<S74>/Rate Limiter' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(todo_M)) {
    rt_ertODEUpdateContinuousStates(&todo_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++todo_M->Timing.clockTick0)) {
      ++todo_M->Timing.clockTickH0;
    }

    todo_M->Timing.t[0] = rtsiGetSolverStopTime(&todo_M->solverInfo);

    {
      /* Update absolute timer for sample time: [1.6666666666666667E-6s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.6666666666666667E-6, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      todo_M->Timing.clockTick1++;
      if (!todo_M->Timing.clockTick1) {
        todo_M->Timing.clockTickH1++;
      }
    }

    rate_scheduler();
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void todo_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_todo_T *_rtXdot;
  _rtXdot = ((XDot_todo_T *) todo_M->derivs);

  /* Derivatives for StateSpace: '<S30>/State-Space' */
  _rtXdot->StateSpace_CSTATE[0] = 0.0;
  _rtXdot->StateSpace_CSTATE[1] = 0.0;
  _rtXdot->StateSpace_CSTATE[0] += -222.11060060879836 *
    todo_X.StateSpace_CSTATE[0];
  _rtXdot->StateSpace_CSTATE[0] += -24674.011002723397 *
    todo_X.StateSpace_CSTATE[1];
  _rtXdot->StateSpace_CSTATE[1] += todo_X.StateSpace_CSTATE[0];
  _rtXdot->StateSpace_CSTATE[0] += todo_B.RateLimiter;

  /* Derivatives for Integrator: '<S25>/Integrator' */
  lsat = (todo_X.Integrator_CSTATE <= (rtMinusInf));
  usat = (todo_X.Integrator_CSTATE >= (rtInf));
  if (((!lsat) && (!usat)) || (lsat && (todo_B.Saturation2 > 0.0)) || (usat &&
       (todo_B.Saturation2 < 0.0))) {
    _rtXdot->Integrator_CSTATE = todo_B.Saturation2;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S25>/Integrator' */

  /* Derivatives for Enabled SubSystem: '<S25>/Automatic Gain Control' */
  todo_AutomaticGainControl_Deriv(&todo_B.AutomaticGainControl,
    &todo_DW.AutomaticGainControl, &_rtXdot->AutomaticGainControl);

  /* End of Derivatives for SubSystem: '<S25>/Automatic Gain Control' */

  /* Derivatives for VariableTransportDelay: '<S33>/Variable Transport Delay' */
  {
  }

  /* Derivatives for Integrator: '<S33>/Integrator' */
  _rtXdot->Integrator_CSTATE_h = todo_B.Vq;

  /* Derivatives for Integrator: '<S32>/Integrator' */
  lsat = (todo_X.Integrator_CSTATE_f <= 0.0);
  usat = (todo_X.Integrator_CSTATE_f >= 10000.0);
  if (((!lsat) && (!usat)) || (lsat && (todo_B.Kp5 > 0.0)) || (usat &&
       (todo_B.Kp5 < 0.0))) {
    _rtXdot->Integrator_CSTATE_f = todo_B.Kp5;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_f = 0.0;
  }

  /* End of Derivatives for Integrator: '<S32>/Integrator' */

  /* Derivatives for StateSpace: '<S79>/State-Space' */
  _rtXdot->StateSpace_CSTATE_h[0] = 0.0;
  _rtXdot->StateSpace_CSTATE_h[1] = 0.0;
  _rtXdot->StateSpace_CSTATE_h[0] += -222.11060060879836 *
    todo_X.StateSpace_CSTATE_h[0];
  _rtXdot->StateSpace_CSTATE_h[0] += -24674.011002723397 *
    todo_X.StateSpace_CSTATE_h[1];
  _rtXdot->StateSpace_CSTATE_h[1] += todo_X.StateSpace_CSTATE_h[0];
  _rtXdot->StateSpace_CSTATE_h[0] += todo_B.RateLimiter_n;

  /* Derivatives for Integrator: '<S74>/Integrator' */
  lsat = (todo_X.Integrator_CSTATE_fl <= (rtMinusInf));
  usat = (todo_X.Integrator_CSTATE_fl >= (rtInf));
  if (((!lsat) && (!usat)) || (lsat && (todo_B.Saturation2_b > 0.0)) || (usat &&
       (todo_B.Saturation2_b < 0.0))) {
    _rtXdot->Integrator_CSTATE_fl = todo_B.Saturation2_b;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_fl = 0.0;
  }

  /* End of Derivatives for Integrator: '<S74>/Integrator' */

  /* Derivatives for Enabled SubSystem: '<S74>/Automatic Gain Control' */
  todo_AutomaticGainControl_Deriv(&todo_B.AutomaticGainControl_c,
    &todo_DW.AutomaticGainControl_c, &_rtXdot->AutomaticGainControl_c);

  /* End of Derivatives for SubSystem: '<S74>/Automatic Gain Control' */

  /* Derivatives for VariableTransportDelay: '<S82>/Variable Transport Delay' */
  {
  }

  /* Derivatives for Integrator: '<S82>/Integrator' */
  _rtXdot->Integrator_CSTATE_a = todo_B.Vq_k;

  /* Derivatives for Integrator: '<S81>/Integrator' */
  lsat = (todo_X.Integrator_CSTATE_k <= 0.0);
  usat = (todo_X.Integrator_CSTATE_k >= 10000.0);
  if (((!lsat) && (!usat)) || (lsat && (todo_B.Kp5_p > 0.0)) || (usat &&
       (todo_B.Kp5_p < 0.0))) {
    _rtXdot->Integrator_CSTATE_k = todo_B.Kp5_p;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_k = 0.0;
  }

  /* End of Derivatives for Integrator: '<S81>/Integrator' */
}

/* Model initialize function */
void todo_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)todo_M, 0,
                sizeof(RT_MODEL_todo_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&todo_M->solverInfo, &todo_M->Timing.simTimeStep);
    rtsiSetTPtr(&todo_M->solverInfo, &rtmGetTPtr(todo_M));
    rtsiSetStepSizePtr(&todo_M->solverInfo, &todo_M->Timing.stepSize0);
    rtsiSetdXPtr(&todo_M->solverInfo, &todo_M->derivs);
    rtsiSetContStatesPtr(&todo_M->solverInfo, (real_T **) &todo_M->contStates);
    rtsiSetNumContStatesPtr(&todo_M->solverInfo, &todo_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&todo_M->solverInfo,
      &todo_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&todo_M->solverInfo,
      &todo_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&todo_M->solverInfo,
      &todo_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&todo_M->solverInfo, (&rtmGetErrorStatus(todo_M)));
    rtsiSetRTModelPtr(&todo_M->solverInfo, todo_M);
  }

  rtsiSetSimTimeStep(&todo_M->solverInfo, MAJOR_TIME_STEP);
  todo_M->intgData.x0 = todo_M->odeX0;
  todo_M->intgData.f0 = todo_M->odeF0;
  todo_M->intgData.x1start = todo_M->odeX1START;
  todo_M->intgData.f1 = todo_M->odeF1;
  todo_M->intgData.Delta = todo_M->odeDELTA;
  todo_M->intgData.E = todo_M->odeE;
  todo_M->intgData.fac = todo_M->odeFAC;

  /* initialize */
  {
    int_T i;
    real_T *f = todo_M->intgData.fac;
    for (i = 0; i < (int_T)(sizeof(todo_M->odeFAC)/sizeof(real_T)); i++) {
      f[i] = 1.5e-8;
    }
  }

  todo_M->intgData.DFDX = todo_M->odeDFDX;
  todo_M->intgData.W = todo_M->odeW;
  todo_M->intgData.pivots = todo_M->odePIVOTS;
  todo_M->intgData.xtmp = todo_M->odeXTMP;
  todo_M->intgData.ztmp = todo_M->odeZTMP;
  todo_M->intgData.isFirstStep = true;
  rtsiSetSolverExtrapolationOrder(&todo_M->solverInfo, 4);
  rtsiSetSolverNumberNewtonIterations(&todo_M->solverInfo, 1);
  todo_M->contStates = ((X_todo_T *) &todo_X);
  rtsiSetSolverData(&todo_M->solverInfo, (void *)&todo_M->intgData);
  rtsiSetSolverName(&todo_M->solverInfo,"ode14x");
  rtmSetTPtr(todo_M, &todo_M->Timing.tArray[0]);
  todo_M->Timing.stepSize0 = 1.6666666666666667E-6;

  /* block I/O */
  (void) memset(((void *) &todo_B), 0,
                sizeof(B_todo_T));

  /* states (continuous) */
  {
    (void) memset((void *)&todo_X, 0,
                  sizeof(X_todo_T));
  }

  /* states (dwork) */
  (void) memset((void *)&todo_DW, 0,
                sizeof(DW_todo_T));

  /* external inputs */
  (void)memset((void *)&todo_U, 0, sizeof(ExtU_todo_T));

  /* external outputs */
  (void) memset((void *)&todo_Y, 0,
                sizeof(ExtY_todo_T));

  /* Start for S-Function (sfun_spssw_discc): '<S124>/State-Space' incorporates:
   *  Constant: '<S128>/SwitchCurrents'
   */

  /* S-Function block: <S124>/State-Space */
  {
    todo_DW.StateSpace_PWORK.AS = (real_T*)calloc(3 * 3, sizeof(real_T));
    todo_DW.StateSpace_PWORK.BS = (real_T*)calloc(3 * 9, sizeof(real_T));
    todo_DW.StateSpace_PWORK.CS = (real_T*)calloc(11 * 3, sizeof(real_T));
    todo_DW.StateSpace_PWORK.DS = (real_T*)calloc(11 * 9, sizeof(real_T));
    todo_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(11, sizeof(real_T));
    todo_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(9, sizeof(real_T));
    todo_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK.SWITCH_STATUS = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.SW_CHG = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.G_STATE = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.Y_SWITCH = (real_T*)calloc(8, sizeof(real_T));
    todo_DW.StateSpace_PWORK.SWITCH_TYPES = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.IDX_OUT_SW = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.SWITCH_STATUS_INIT = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK.USWLAST = (real_T*)calloc(8, sizeof(real_T));
  }

  /* Start for S-Function (sfun_spssw_discc): '<S125>/State-Space' incorporates:
   *  Constant: '<S132>/SwitchCurrents'
   */

  /* S-Function block: <S125>/State-Space */
  {
    todo_DW.StateSpace_PWORK_p.AS = (real_T*)calloc(3 * 3, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.BS = (real_T*)calloc(3 * 9, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.CS = (real_T*)calloc(11 * 3, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.DS = (real_T*)calloc(11 * 9, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.DX_COL = (real_T*)calloc(11, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.TMP2 = (real_T*)calloc(9, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.BD_COL = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.TMP1 = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.XTMP = (real_T*)calloc(3, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.SWITCH_STATUS = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK_p.SW_CHG = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK_p.G_STATE = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK_p.Y_SWITCH = (real_T*)calloc(8, sizeof(real_T));
    todo_DW.StateSpace_PWORK_p.SWITCH_TYPES = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK_p.IDX_OUT_SW = (int_T*)calloc(8, sizeof(int_T));
    todo_DW.StateSpace_PWORK_p.SWITCH_STATUS_INIT = (int_T*)calloc(8, sizeof
      (int_T));
    todo_DW.StateSpace_PWORK_p.USWLAST = (real_T*)calloc(8, sizeof(real_T));
  }

  /* Start for Enabled SubSystem: '<S25>/Automatic Gain Control' */
  todo_AutomaticGainControl_Start(todo_M, &todo_DW.AutomaticGainControl);

  /* End of Start for SubSystem: '<S25>/Automatic Gain Control' */

  /* Start for VariableTransportDelay: '<S33>/Variable Transport Delay' */
  {
    real_T *pBuffer = &todo_DW.VariableTransportDelay_RWORK.TUbufferArea[0];
    int_T j;
    todo_DW.VariableTransportDelay_IWORK.Tail = 0;
    todo_DW.VariableTransportDelay_IWORK.Head = 0;
    todo_DW.VariableTransportDelay_IWORK.Last = 0;
    todo_DW.VariableTransportDelay_IWORK.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 0.0;
      pBuffer[8192 + j] = todo_M->Timing.t[0];
    }

    todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    todo_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* Start for Enabled SubSystem: '<S74>/Automatic Gain Control' */
  todo_AutomaticGainControl_Start(todo_M, &todo_DW.AutomaticGainControl_c);

  /* End of Start for SubSystem: '<S74>/Automatic Gain Control' */

  /* Start for VariableTransportDelay: '<S82>/Variable Transport Delay' */
  {
    real_T *pBuffer = &todo_DW.VariableTransportDelay_RWORK_b.TUbufferArea[0];
    int_T j;
    todo_DW.VariableTransportDelay_IWORK_f.Tail = 0;
    todo_DW.VariableTransportDelay_IWORK_f.Head = 0;
    todo_DW.VariableTransportDelay_IWORK_f.Last = 0;
    todo_DW.VariableTransportDelay_IWORK_f.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 0.0;
      pBuffer[8192 + j] = todo_M->Timing.t[0];
    }

    todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[0] = (void *) &pBuffer[0];
    todo_DW.VariableTransportDelay_PWORK_a.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S124>/State-Space' incorporates:
   *  Constant: '<S128>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)todo_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&todo_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 3; i++) {
      X0[i] = (todo_ConstP.pooled22[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++)
        As[i*3 + j] = (todo_ConstP.pooled18[i + j*3]);
      for (j=0; j<9; j++)
        Bs[i*9 + j] = (todo_ConstP.pooled19[i + j*3]);
    }

    /* Copy and transpose C */
    for (i=0; i<11; i++) {
      for (j=0; j<3; j++)
        Cs[i*3 + j] = (todo_ConstP.pooled20[i + j*11]);
    }

    /* Copy and transpose D */
    for (i=0; i<11; i++) {
      for (j=0; j<9; j++)
        Ds[i*9 + j] = (todo_ConstP.pooled21[i + j*11]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*) todo_DW.StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)todo_DW.StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)todo_DW.StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)todo_DW.StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)todo_DW.StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        todo_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;

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
      switchTypes[4] = (int_T)3.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.01;
      switchTypes[5] = (int_T)3.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.01;
      switchTypes[6] = (int_T)3.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.01;
      switchTypes[7] = (int_T)3.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
    }
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S125>/State-Space' incorporates:
   *  Constant: '<S132>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)todo_DW.StateSpace_PWORK_p.AS;
    real_T *Bs = (real_T*)todo_DW.StateSpace_PWORK_p.BS;
    real_T *Cs = (real_T*)todo_DW.StateSpace_PWORK_p.CS;
    real_T *Ds = (real_T*)todo_DW.StateSpace_PWORK_p.DS;
    real_T *X0 = (real_T*)&todo_DW.StateSpace_DSTATE_e[0];
    for (i = 0; i < 3; i++) {
      X0[i] = (todo_ConstP.pooled22[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++)
        As[i*3 + j] = (todo_ConstP.pooled18[i + j*3]);
      for (j=0; j<9; j++)
        Bs[i*9 + j] = (todo_ConstP.pooled19[i + j*3]);
    }

    /* Copy and transpose C */
    for (i=0; i<11; i++) {
      for (j=0; j<3; j++)
        Cs[i*3 + j] = (todo_ConstP.pooled20[i + j*11]);
    }

    /* Copy and transpose D */
    for (i=0; i<11; i++) {
      for (j=0; j<9; j++)
        Ds[i*9 + j] = (todo_ConstP.pooled21[i + j*11]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*) todo_DW.StateSpace_PWORK_p.SWITCH_STATUS;
      int_T *gState = (int_T*)todo_DW.StateSpace_PWORK_p.G_STATE;
      real_T *yswitch = (real_T*)todo_DW.StateSpace_PWORK_p.Y_SWITCH;
      int_T *switchTypes = (int_T*)todo_DW.StateSpace_PWORK_p.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)todo_DW.StateSpace_PWORK_p.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        todo_DW.StateSpace_PWORK_p.SWITCH_STATUS_INIT;

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
      switchTypes[4] = (int_T)3.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.01;
      switchTypes[5] = (int_T)3.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.01;
      switchTypes[6] = (int_T)3.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.01;
      switchTypes[7] = (int_T)3.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
    }
  }

  /* InitializeConditions for StateSpace: '<S30>/State-Space' */
  todo_X.StateSpace_CSTATE[0] = 0.0;
  todo_X.StateSpace_CSTATE[1] = 0.0024317084074161064;

  /* InitializeConditions for Integrator: '<S25>/Integrator' */
  todo_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S33>/Integrator' */
  todo_X.Integrator_CSTATE_h = 0.0;

  /* InitializeConditions for Integrator: '<S32>/Integrator' */
  todo_X.Integrator_CSTATE_f = 376.99111843077515;

  /* InitializeConditions for Derivative: '<S32>/Derivative' */
  todo_DW.TimeStampA = (rtInf);
  todo_DW.TimeStampB = (rtInf);

  /* InitializeConditions for RateLimiter: '<S25>/Rate Limiter' */
  todo_DW.LastMajorTimeA = (rtInf);
  todo_DW.LastMajorTimeB = (rtInf);

  /* InitializeConditions for StateSpace: '<S79>/State-Space' */
  todo_X.StateSpace_CSTATE_h[0] = 0.0;
  todo_X.StateSpace_CSTATE_h[1] = 0.0024317084074161064;

  /* InitializeConditions for Integrator: '<S74>/Integrator' */
  todo_X.Integrator_CSTATE_fl = 0.0;

  /* InitializeConditions for Integrator: '<S82>/Integrator' */
  todo_X.Integrator_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S81>/Integrator' */
  todo_X.Integrator_CSTATE_k = 376.99111843077515;

  /* InitializeConditions for Derivative: '<S81>/Derivative' */
  todo_DW.TimeStampA_l = (rtInf);
  todo_DW.TimeStampB_m = (rtInf);

  /* InitializeConditions for RateLimiter: '<S74>/Rate Limiter' */
  todo_DW.LastMajorTimeA_c = (rtInf);
  todo_DW.LastMajorTimeB_a = (rtInf);

  /* SystemInitialize for Enabled SubSystem: '<S25>/Automatic Gain Control' */
  todo_AutomaticGainControl_Init(&todo_B.MathFunction_h,
    &todo_X.AutomaticGainControl);

  /* End of SystemInitialize for SubSystem: '<S25>/Automatic Gain Control' */

  /* SystemInitialize for Enabled SubSystem: '<S74>/Automatic Gain Control' */
  todo_AutomaticGainControl_Init(&todo_B.MathFunction,
    &todo_X.AutomaticGainControl_c);

  /* End of SystemInitialize for SubSystem: '<S74>/Automatic Gain Control' */
}

/* Model terminate function */
void todo_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S124>/State-Space' incorporates:
   *  Constant: '<S128>/SwitchCurrents'
   */

  /* S-Function block: <S124>/State-Space */
  {
    /* Free memory */
    free(todo_DW.StateSpace_PWORK.AS);
    free(todo_DW.StateSpace_PWORK.BS);
    free(todo_DW.StateSpace_PWORK.CS);
    free(todo_DW.StateSpace_PWORK.DS);
    free(todo_DW.StateSpace_PWORK.DX_COL);
    free(todo_DW.StateSpace_PWORK.TMP2);
    free(todo_DW.StateSpace_PWORK.BD_COL);
    free(todo_DW.StateSpace_PWORK.TMP1);
    free(todo_DW.StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(todo_DW.StateSpace_PWORK.G_STATE);
    free(todo_DW.StateSpace_PWORK.SWITCH_STATUS);
    free(todo_DW.StateSpace_PWORK.SW_CHG);
    free(todo_DW.StateSpace_PWORK.SWITCH_STATUS_INIT);
  }

  /* Terminate for S-Function (sfun_spssw_discc): '<S125>/State-Space' incorporates:
   *  Constant: '<S132>/SwitchCurrents'
   */

  /* S-Function block: <S125>/State-Space */
  {
    /* Free memory */
    free(todo_DW.StateSpace_PWORK_p.AS);
    free(todo_DW.StateSpace_PWORK_p.BS);
    free(todo_DW.StateSpace_PWORK_p.CS);
    free(todo_DW.StateSpace_PWORK_p.DS);
    free(todo_DW.StateSpace_PWORK_p.DX_COL);
    free(todo_DW.StateSpace_PWORK_p.TMP2);
    free(todo_DW.StateSpace_PWORK_p.BD_COL);
    free(todo_DW.StateSpace_PWORK_p.TMP1);
    free(todo_DW.StateSpace_PWORK_p.XTMP);

    /*
     * Circuit has switches*/
    free(todo_DW.StateSpace_PWORK_p.G_STATE);
    free(todo_DW.StateSpace_PWORK_p.SWITCH_STATUS);
    free(todo_DW.StateSpace_PWORK_p.SW_CHG);
    free(todo_DW.StateSpace_PWORK_p.SWITCH_STATUS_INIT);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
