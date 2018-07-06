/*
 * File: genCmotorDiesel.h
 *
 * Code generated for Simulink model 'genCmotorDiesel'.
 *
 * Model version                  : 1.140
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jan 23 10:42:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_genCmotorDiesel_h_
#define RTW_HEADER_genCmotorDiesel_h_
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef genCmotorDiesel_COMMON_INCLUDES_
# define genCmotorDiesel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_logging.h"
#endif                                 /* genCmotorDiesel_COMMON_INCLUDES_ */

#include "genCmotorDiesel_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DelayTm001_DSTATE[50];        /* '<Root>/Delay Tm=0.01' */
  real_T ActuadorMotorTm001s_states;   /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T EjeTm001s_states;             /* '<Root>/Eje Tm=0.01s' */
  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<Root>/Scope3' */
} DW_genCmotorDiesel_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Actuador;                     /* '<Root>/Actuador' */
  real_T PardeCarga;                   /* '<Root>/Par de Carga' */
} ExtU_genCmotorDiesel_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
} ExtY_genCmotorDiesel_T;

/* Real-time Model Data Structure */
struct tag_RTM_genCmotorDiesel_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block states (auto storage) */
extern DW_genCmotorDiesel_T genCmotorDiesel_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_genCmotorDiesel_T genCmotorDiesel_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_genCmotorDiesel_T genCmotorDiesel_Y;

/* Model entry point functions */
extern void genCmotorDiesel_initialize(void);
extern void genCmotorDiesel_step(void);
extern void genCmotorDiesel_terminate(void);

/* Real-time Model object */
extern RT_MODEL_genCmotorDiesel_T *const genCmotorDiesel_M;

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
 * '<Root>' : 'genCmotorDiesel'
 */
#endif                                 /* RTW_HEADER_genCmotorDiesel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
