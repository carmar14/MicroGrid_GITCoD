/*
 * genCmotorDiesel.h
 *
 * Code generation for model "genCmotorDiesel".
 *
 * Model version              : 1.141
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Mon Jan 22 09:54:00 2018
 *
 * Target selection: rsim.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_genCmotorDiesel_h_
#define RTW_HEADER_genCmotorDiesel_h_
#include <string.h>
#include <stddef.h>
#ifndef genCmotorDiesel_COMMON_INCLUDES_
# define genCmotorDiesel_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rsim.h"
#include "rt_logging.h"
#include "dt_info.h"
#endif                                 /* genCmotorDiesel_COMMON_INCLUDES_ */

#include "genCmotorDiesel_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME                     genCmotorDiesel
#define NSAMPLE_TIMES                  (2)                       /* Number of sample times */
#define NINPUTS                        (0)                       /* Number of model inputs */
#define NOUTPUTS                       (0)                       /* Number of model outputs */
#define NBLOCKIO                       (6)                       /* Number of data output port signals */
#define NUM_ZC_EVENTS                  (0)                       /* Number of zero-crossing events */
#ifndef NCSTATES
# define NCSTATES                      (0)                       /* Number of continuous states */
#elif NCSTATES != 0
# error Invalid specification of NCSTATES defined in compiler command
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        (NULL)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T AccinActuador1;               /* '<Root>/Acción Actuador1' */
  real_T ActuadorMotorTm001s;          /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T Velocidad;                    /* '<Root>/Eje Tm=0.01s' */
  real_T Generador1;                   /* '<Root>/ Generador1' */
} B;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DelayTm001_DSTATE[50];        /* '<Root>/Delay Tm=0.01' */
  real_T ActuadorMotorTm001s_states;   /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T EjeTm001s_states;             /* '<Root>/Eje Tm=0.01s' */
  real_T ActuadorMotorTm001s_tmp;      /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T EjeTm001s_tmp;                /* '<Root>/Eje Tm=0.01s' */
  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<Root>/Scope3' */

  int_T AccinActuador1_MODE;           /* '<Root>/Acción Actuador1' */
  int_T Pardecarga1_MODE;              /* '<Root>/Par de carga1' */
} DW;

/* Zero-crossing (trigger) state */
typedef struct {
  real_T AccinActuador1_StepTime_ZC;   /* '<Root>/Acción Actuador1' */
  real_T Pardecarga1_StepTime_ZC;      /* '<Root>/Par de carga1' */
} ZCV;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern B rtB;                          /* block i/o */
extern DW rtDW;                        /* states (dwork) */

/* Simulation Structure */
extern SimStruct *const rtS;

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

/* user code (bottom of header file) */
extern const int_T gblNumToFiles;
extern const int_T gblNumFrFiles;
extern const int_T gblNumFrWksBlocks;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
extern const int_T gblNumRootInportBlks;
extern const int_T gblNumModelInputs;
extern const int_T gblInportDataTypeIdx[];
extern const int_T gblInportDims[];
extern const int_T gblInportComplex[];
extern const int_T gblInportInterpoFlag[];
extern const int_T gblInportContinuous[];

#endif                                 /* RTW_HEADER_genCmotorDiesel_h_ */
