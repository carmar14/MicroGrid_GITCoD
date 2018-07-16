/*
 * File: rt_look1d.c
 *
 * Code generated for Simulink model 'BIO_csi'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Jul 16 17:23:26 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rt_look1d.h"

/* 1D lookup routine for data type of real_T. */
real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y)
{
  int_T idx = rt_GetLookupIndex(x, xlen, u);
  real_T num = y[idx+1] - y[idx];
  real_T den = x[idx+1] - x[idx];

  /* Due to the way the binary search is implemented
     in rt_look.c (rt_GetLookupIndex), den cannot be
     0.  Equivalently, m cannot be inf or nan. */
  real_T m = num/den;
  return (y[idx] + (m * (u - x[idx])));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
