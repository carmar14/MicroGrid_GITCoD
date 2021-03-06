/*
 * File: BIO_csi_sf_private.h
 *
 * Code generated for Simulink model 'BIO_csi_sf'.
 *
 * Model version                  : 1.63
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Aug 14 16:25:22 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_sf_private_h_
#define RTW_HEADER_BIO_csi_sf_private_h_
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* private model entry point functions */
extern void BIO_csi_sf_derivatives(void);

#endif                                 /* RTW_HEADER_BIO_csi_sf_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
