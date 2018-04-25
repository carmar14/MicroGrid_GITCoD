/*
 * File: mpc_genC.h
 *
 * Code generated for Simulink model 'mpc_genC'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Sat Apr 21 19:01:00 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mpc_genC_h_
#define RTW_HEADER_mpc_genC_h_
#include <string.h>
#ifndef mpc_genC_COMMON_INCLUDES_
# define mpc_genC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* mpc_genC_COMMON_INCLUDES_ */

#include "mpc_genC_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE[4];            /* '<S2>/last_mv' */
  real_T last_x_PreviousInput[8];      /* '<S2>/last_x' */
} DW_mpc_genC_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T pbio_meas;                    /* '<Root>/pbio_meas' */
  real_T qbio_meas;                    /* '<Root>/qbio_meas' */
  real_T pdie_meas;                    /* '<Root>/pdie_meas' */
  real_T qdie_meas;                    /* '<Root>/qdie_meas' */
} ExtU_mpc_genC_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T mpc_Pbio;                     /* '<Root>/mpc_Pbio' */
  real_T mpc_Qbio;                     /* '<Root>/mpc_Qbio' */
  real_T mpc_Pdie;                     /* '<Root>/mpc_Pdie' */
  real_T mpc_Qdie;                     /* '<Root>/mpc_Qdie' */
} ExtY_mpc_genC_T;

/* Real-time Model Data Structure */
struct tag_RTM_mpc_genC_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block states (auto storage) */
extern DW_mpc_genC_T mpc_genC_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_mpc_genC_T mpc_genC_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_mpc_genC_T mpc_genC_Y;

/* Model entry point functions */
extern void mpc_genC_initialize(void);
extern void mpc_genC_step(void);
extern void mpc_genC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mpc_genC_T *const mpc_genC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S4>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S5>/Vector Dimension Check' : Unused code path elimination
 * Block '<S6>/Vector Dimension Check' : Unused code path elimination
 * Block '<S7>/Vector Dimension Check' : Unused code path elimination
 * Block '<S8>/Vector Dimension Check' : Unused code path elimination
 * Block '<S9>/Vector Dimension Check' : Unused code path elimination
 * Block '<S10>/Vector Dimension Check' : Unused code path elimination
 * Block '<S11>/Vector Dimension Check' : Unused code path elimination
 * Block '<S12>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Vector Dimension Check' : Unused code path elimination
 * Block '<S14>/Vector Dimension Check' : Unused code path elimination
 * Block '<S15>/Vector Dimension Check' : Unused code path elimination
 * Block '<S16>/Vector Dimension Check' : Unused code path elimination
 * Block '<S2>/constant' : Unused code path elimination
 * Block '<S2>/umin_scale2' : Unused code path elimination
 * Block '<S2>/umin_scale3' : Unused code path elimination
 * Block '<S2>/ym_zero' : Unused code path elimination
 * Block '<S2>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S2>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S2>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S2>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ymin_scale' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mpc_genC'
 * '<S1>'   : 'mpc_genC/MPC Controller'
 * '<S2>'   : 'mpc_genC/MPC Controller/MPC'
 * '<S3>'   : 'mpc_genC/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S4>'   : 'mpc_genC/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S5>'   : 'mpc_genC/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S6>'   : 'mpc_genC/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S7>'   : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S8>'   : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S9>'   : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S10>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S11>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S12>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S13>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S14>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S15>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S16>'  : 'mpc_genC/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S17>'  : 'mpc_genC/MPC Controller/MPC/optimizer'
 */
#endif                                 /* RTW_HEADER_mpc_genC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
