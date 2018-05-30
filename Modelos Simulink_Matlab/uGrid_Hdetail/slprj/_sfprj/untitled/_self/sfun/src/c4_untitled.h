#ifndef __c4_untitled_h__
#define __c4_untitled_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc4_untitledInstanceStruct
#define typedef_SFc4_untitledInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_untitled;
  void *c4_fEmlrtCtx;
  real_T (*c4_H)[4];
  real_T *c4_Pren_max;
  real_T (*c4_f)[2];
  real_T *c4_P_load;
  real_T (*c4_K)[2];
  real_T (*c4_A)[2];
  real_T (*c4_lb)[2];
  real_T (*c4_ub)[2];
  real_T *c4_lbA;
  real_T *c4_ubA;
  real_T (*c4_Pcsis_max)[2];
} SFc4_untitledInstanceStruct;

#endif                                 /*typedef_SFc4_untitledInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_untitled_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_untitled_get_check_sum(mxArray *plhs[]);
extern void c4_untitled_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
