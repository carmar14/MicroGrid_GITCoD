/*
 * File: control_terciario.h
 *
 * Code generated for Simulink model 'control_terciario'.
 *
 * Model version                  : 1.65
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 11:42:57 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_control_terciario_h_
#define RTW_HEADER_control_terciario_h_
#include <string.h>
#ifndef control_terciario_COMMON_INCLUDES_
# define control_terciario_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* control_terciario_COMMON_INCLUDES_ */

#include "control_terciario_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T soc;                          /* '<Root>/soc' */
  real_T Pm;                           /* '<Root>/Pm' */
  real_T Qm;                           /* '<Root>/Qm' */
} ExtU_control_terciario_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Pb;                           /* '<Root>/Pb' */
  real_T Pd;                           /* '<Root>/Pd' */
  real_T Qb;                           /* '<Root>/Qb' */
  real_T Qd;                           /* '<Root>/Qd' */
} ExtY_control_terciario_T;

/* Real-time Model Data Structure */
struct tag_RTM_control_terciario_T {
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

/* External inputs (root inport signals with auto storage) */
extern ExtU_control_terciario_T control_terciario_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_control_terciario_T control_terciario_Y;

/* Model entry point functions */
extern void control_terciario_initialize(void);
extern void control_terciario_step(void);
extern void control_terciario_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_soc(double);
extern void set_Pm(double);
extern void set_Qm(double);
//-----Funciones para obtener valores de las salidas-------
extern double get_Pb(void);
extern double get_Qb(void);
extern double get_Pd(void);
extern double get_Qd(void);

/* Real-time Model object */
extern RT_MODEL_control_terciario_T *const control_terciario_M;

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
 * '<Root>' : 'control_terciario'
 * '<S1>'   : 'control_terciario/LinearProg Potencia Activa'
 * '<S2>'   : 'control_terciario/LinearProg Potenica Reactiva'
 * '<S3>'   : 'control_terciario/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_control_terciario_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
