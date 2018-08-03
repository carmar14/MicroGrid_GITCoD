/*
 * File: code_programacion_lineal__private.h
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

#ifndef RTW_HEADER_code_programacion_lineal__private_h_
#define RTW_HEADER_code_programacion_lineal__private_h_
#include "rtwtypes.h"
#include "code_programacion_lineal_.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern void qp_linprog(SimStruct *rts);
extern void LinProg_BuildMatrices_ActivePow(real_T rtu_Pren_max, real_T
  rtu_P_load, real_T rtu_K, real_T rtu_K_j, real_T rtu_Pcsis_max, real_T
  rtu_Pcsis_max_f, real_T rty_H[4], real_T rty_f[2], real_T rty_A[2], real_T
  rty_lb[2], real_T rty_ub[2], real_T *rty_lbA, real_T *rty_ubA);

#endif                                 /* RTW_HEADER_code_programacion_lineal__private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
