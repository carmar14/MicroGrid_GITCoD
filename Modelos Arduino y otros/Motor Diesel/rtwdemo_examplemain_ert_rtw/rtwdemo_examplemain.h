/*
 * File: rtwdemo_examplemain.h
 *
 * Code generated for Simulink model 'rtwdemo_examplemain'.
 *
 * Model version                  : 1.138
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Jan 22 10:51:49 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rtwdemo_examplemain_h_
#define RTW_HEADER_rtwdemo_examplemain_h_
#ifndef rtwdemo_examplemain_COMMON_INCLUDES_
# define rtwdemo_examplemain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* rtwdemo_examplemain_COMMON_INCLUDES_ */

#include "rtwdemo_examplemain_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T RateTransition;               /* '<Root>/RateTransition' */
} BlockIO;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<Root>/Integrator' */
  real_T RateTransition_Buffer0;       /* '<Root>/RateTransition' */
} D_Work;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T In1_1s;                       /* '<Root>/In1_1s' */
  real_T In2_2s;                       /* '<Root>/In2_2s' */
} ExternalInputs;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
  real_T Out2;                         /* '<Root>/Out2' */
} ExternalOutputs;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block signals (auto storage) */
extern BlockIO rtB;

/* Block states (auto storage) */
extern D_Work rtDWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs rtY;

/* Model entry point functions */
extern void rtwdemo_examplemain_initialize(void);
extern void rtwdemo_examplemain_step0(void);
extern void rtwdemo_examplemain_step1(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * '<Root>' : 'rtwdemo_examplemain'
 * '<S1>'   : 'rtwdemo_examplemain/SS1'
 * '<S2>'   : 'rtwdemo_examplemain/SS2'
 */
#endif                                 /* RTW_HEADER_rtwdemo_examplemain_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
