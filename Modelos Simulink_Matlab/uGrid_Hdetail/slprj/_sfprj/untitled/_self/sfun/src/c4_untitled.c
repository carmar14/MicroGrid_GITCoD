/* Include files */

#include "untitled_sfun.h"
#include "c4_untitled.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "untitled_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c4_debug_family_names[16] = { "Pm", "D", "vp", "nargin",
  "nargout", "Pren_max", "P_load", "K", "Pcsis_max", "H", "f", "A", "lb", "ub",
  "lbA", "ubA" };

/* Function Declarations */
static void initialize_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void initialize_params_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance);
static void enable_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void disable_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance);
static void set_sim_state_c4_untitled(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void sf_gateway_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void mdl_start_c4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void initSimStructsc4_untitled(SFc4_untitledInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_ubA, const char_T *c4_identifier);
static real_T c4_b_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_ub, const char_T *c4_identifier, real_T c4_y[2]);
static void c4_d_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_e_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_lb, const char_T *c4_identifier, real_T c4_y[2]);
static void c4_f_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_g_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_H, const char_T *c4_identifier, real_T c4_y[4]);
static void c4_h_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[4]);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_i_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_j_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_untitled, const char_T *c4_identifier);
static uint8_T c4_k_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_untitledInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_untitledInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc4_untitled(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_is_active_c4_untitled = 0U;
}

static void initialize_params_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_untitled(SFc4_untitledInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  const mxArray *c4_b_y = NULL;
  const mxArray *c4_c_y = NULL;
  const mxArray *c4_d_y = NULL;
  const mxArray *c4_e_y = NULL;
  real_T c4_hoistedGlobal;
  const mxArray *c4_f_y = NULL;
  const mxArray *c4_g_y = NULL;
  real_T c4_b_hoistedGlobal;
  const mxArray *c4_h_y = NULL;
  uint8_T c4_c_hoistedGlobal;
  const mxArray *c4_i_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(8, 1), false);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", *chartInstance->c4_A, 0, 0U, 1U, 0U,
    2, 1, 2), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", *chartInstance->c4_H, 0, 0U, 1U, 0U,
    2, 1, 4), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", *chartInstance->c4_f, 0, 0U, 1U, 0U,
    1, 2), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", *chartInstance->c4_lb, 0, 0U, 1U, 0U,
    2, 1, 2), false);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_hoistedGlobal = *chartInstance->c4_lbA;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c4_y, 4, c4_f_y);
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", *chartInstance->c4_ub, 0, 0U, 1U, 0U,
    1, 2), false);
  sf_mex_setcell(c4_y, 5, c4_g_y);
  c4_b_hoistedGlobal = *chartInstance->c4_ubA;
  c4_h_y = NULL;
  sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c4_y, 6, c4_h_y);
  c4_c_hoistedGlobal = chartInstance->c4_is_active_c4_untitled;
  c4_i_y = NULL;
  sf_mex_assign(&c4_i_y, sf_mex_create("y", &c4_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c4_y, 7, c4_i_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_untitled(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[2];
  int32_T c4_i0;
  real_T c4_dv1[4];
  int32_T c4_i1;
  real_T c4_dv2[2];
  int32_T c4_i2;
  real_T c4_dv3[2];
  int32_T c4_i3;
  real_T c4_dv4[2];
  int32_T c4_i4;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("A", c4_u, 0)),
                        "A", c4_dv0);
  for (c4_i0 = 0; c4_i0 < 2; c4_i0++) {
    (*chartInstance->c4_A)[c4_i0] = c4_dv0[c4_i0];
  }

  c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("H", c4_u, 1)),
                        "H", c4_dv1);
  for (c4_i1 = 0; c4_i1 < 4; c4_i1++) {
    (*chartInstance->c4_H)[c4_i1] = c4_dv1[c4_i1];
  }

  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("f", c4_u, 2)),
                        "f", c4_dv2);
  for (c4_i2 = 0; c4_i2 < 2; c4_i2++) {
    (*chartInstance->c4_f)[c4_i2] = c4_dv2[c4_i2];
  }

  c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("lb", c4_u, 3)),
                        "lb", c4_dv3);
  for (c4_i3 = 0; c4_i3 < 2; c4_i3++) {
    (*chartInstance->c4_lb)[c4_i3] = c4_dv3[c4_i3];
  }

  *chartInstance->c4_lbA = c4_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("lbA", c4_u, 4)), "lbA");
  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("ub", c4_u, 5)),
                        "ub", c4_dv4);
  for (c4_i4 = 0; c4_i4 < 2; c4_i4++) {
    (*chartInstance->c4_ub)[c4_i4] = c4_dv4[c4_i4];
  }

  *chartInstance->c4_ubA = c4_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ubA", c4_u, 6)), "ubA");
  chartInstance->c4_is_active_c4_untitled = c4_j_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c4_untitled", c4_u, 7)),
    "is_active_c4_untitled");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_untitled(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  int32_T c4_i5;
  int32_T c4_i6;
  real_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_b_Pren_max;
  real_T c4_b_P_load;
  int32_T c4_i7;
  int32_T c4_i8;
  real_T c4_b_K[2];
  uint32_T c4_debug_family_var_map[16];
  real_T c4_b_Pcsis_max[2];
  real_T c4_Pm;
  real_T c4_D;
  real_T c4_vp;
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 7.0;
  real_T c4_b_H[4];
  real_T c4_b_f[2];
  real_T c4_b_A[2];
  real_T c4_b_lb[2];
  real_T c4_b_ub[2];
  real_T c4_b_lbA;
  real_T c4_b_ubA;
  int32_T c4_i9;
  real_T c4_x[2];
  int32_T c4_i10;
  int32_T c4_i11;
  int32_T c4_i12;
  int32_T c4_i13;
  int32_T c4_i14;
  int32_T c4_i15;
  int32_T c4_i16;
  int32_T c4_i17;
  int32_T c4_i18;
  int32_T c4_i19;
  int32_T c4_i20;
  int32_T c4_i21;
  int32_T c4_i22;
  int32_T c4_i23;
  int32_T c4_i24;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  for (c4_i5 = 0; c4_i5 < 2; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_Pcsis_max)[c4_i5], 3U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i6 = 0; c4_i6 < 2; c4_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_K)[c4_i6], 2U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_P_load, 1U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_Pren_max, 0U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *chartInstance->c4_Pren_max;
  c4_b_hoistedGlobal = *chartInstance->c4_P_load;
  c4_b_Pren_max = c4_hoistedGlobal;
  c4_b_P_load = c4_b_hoistedGlobal;
  for (c4_i7 = 0; c4_i7 < 2; c4_i7++) {
    c4_b_K[c4_i7] = (*chartInstance->c4_K)[c4_i7];
  }

  for (c4_i8 = 0; c4_i8 < 2; c4_i8++) {
    c4_b_Pcsis_max[c4_i8] = (*chartInstance->c4_Pcsis_max)[c4_i8];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_Pm, 0U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_D, 1U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_vp, 2U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 3U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 4U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_Pren_max, 5U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_P_load, 6U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_K, 7U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_Pcsis_max, 8U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_H, 9U, c4_d_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_f, 10U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_A, 11U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_lb, 12U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_ub, 13U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_lbA, 14U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_ubA, 15U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
  for (c4_i9 = 0; c4_i9 < 2; c4_i9++) {
    c4_x[c4_i9] = c4_b_Pcsis_max[c4_i9];
  }

  c4_Pm = c4_x[0];
  c4_Pm += c4_x[1];
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 36);
  c4_D = c4_b_P_load - c4_b_Pren_max;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
  for (c4_i10 = 0; c4_i10 < 4; c4_i10++) {
    c4_b_H[c4_i10] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 49);
  for (c4_i11 = 0; c4_i11 < 2; c4_i11++) {
    c4_b_f[c4_i11] = c4_b_K[c4_i11];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 55);
  for (c4_i12 = 0; c4_i12 < 2; c4_i12++) {
    c4_b_A[c4_i12] = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 57);
  for (c4_i13 = 0; c4_i13 < 2; c4_i13++) {
    c4_b_lb[c4_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 58);
  for (c4_i14 = 0; c4_i14 < 2; c4_i14++) {
    c4_b_ub[c4_i14] = c4_b_Pcsis_max[c4_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 60);
  c4_b_ubA = c4_Pm;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 69);
  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c4_D, 0.0, -1, 4U, c4_D >
        0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 70);
    if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 1, c4_D, c4_Pm, -1, 5U,
          c4_D >= c4_Pm))) {
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 71);
      c4_vp = c4_Pm;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 73);
      c4_vp = c4_D;
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 76);
    c4_vp = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 79);
  c4_b_lbA = c4_vp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -79);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i15 = 0; c4_i15 < 4; c4_i15++) {
    (*chartInstance->c4_H)[c4_i15] = c4_b_H[c4_i15];
  }

  for (c4_i16 = 0; c4_i16 < 2; c4_i16++) {
    (*chartInstance->c4_f)[c4_i16] = c4_b_f[c4_i16];
  }

  for (c4_i17 = 0; c4_i17 < 2; c4_i17++) {
    (*chartInstance->c4_A)[c4_i17] = c4_b_A[c4_i17];
  }

  for (c4_i18 = 0; c4_i18 < 2; c4_i18++) {
    (*chartInstance->c4_lb)[c4_i18] = c4_b_lb[c4_i18];
  }

  for (c4_i19 = 0; c4_i19 < 2; c4_i19++) {
    (*chartInstance->c4_ub)[c4_i19] = c4_b_ub[c4_i19];
  }

  *chartInstance->c4_lbA = c4_b_lbA;
  *chartInstance->c4_ubA = c4_b_ubA;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_untitledMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c4_i20 = 0; c4_i20 < 4; c4_i20++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_H)[c4_i20], 4U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i21 = 0; c4_i21 < 2; c4_i21++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_f)[c4_i21], 5U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i22 = 0; c4_i22 < 2; c4_i22++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_A)[c4_i22], 6U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i23 = 0; c4_i23 < 2; c4_i23++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_lb)[c4_i23], 7U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i24 = 0; c4_i24 < 2; c4_i24++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_ub)[c4_i24], 8U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_lbA, 9U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_ubA, 10U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
}

static void mdl_start_c4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc4_untitled(SFc4_untitledInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)(c4_machineNumber);
  (void)(c4_chartNumber);
  (void)(c4_instanceNumber);
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_ubA, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_ubA), &c4_thisId);
  sf_mex_destroy(&c4_b_ubA);
  return c4_y;
}

static real_T c4_b_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_ubA;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_b_ubA = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_ubA), &c4_thisId);
  sf_mex_destroy(&c4_b_ubA);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int32_T c4_i25;
  const mxArray *c4_y = NULL;
  real_T c4_u[2];
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  for (c4_i25 = 0; c4_i25 < 2; c4_i25++) {
    c4_u[c4_i25] = (*(real_T (*)[2])c4_inData)[c4_i25];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_ub, const char_T *c4_identifier, real_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_ub), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_ub);
}

static void c4_d_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2])
{
  real_T c4_dv5[2];
  int32_T c4_i26;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv5, 1, 0, 0U, 1, 0U, 1, 2);
  for (c4_i26 = 0; c4_i26 < 2; c4_i26++) {
    c4_y[c4_i26] = c4_dv5[c4_i26];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_ub;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i27;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_b_ub = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_ub), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_ub);
  for (c4_i27 = 0; c4_i27 < 2; c4_i27++) {
    (*(real_T (*)[2])c4_outData)[c4_i27] = c4_y[c4_i27];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int32_T c4_i28;
  const mxArray *c4_y = NULL;
  real_T c4_u[2];
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  for (c4_i28 = 0; c4_i28 < 2; c4_i28++) {
    c4_u[c4_i28] = (*(real_T (*)[2])c4_inData)[c4_i28];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_e_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_lb, const char_T *c4_identifier, real_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_lb), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_lb);
}

static void c4_f_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2])
{
  real_T c4_dv6[2];
  int32_T c4_i29;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv6, 1, 0, 0U, 1, 0U, 2, 1, 2);
  for (c4_i29 = 0; c4_i29 < 2; c4_i29++) {
    c4_y[c4_i29] = c4_dv6[c4_i29];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_lb;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i30;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_b_lb = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_lb), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_lb);
  for (c4_i30 = 0; c4_i30 < 2; c4_i30++) {
    (*(real_T (*)[2])c4_outData)[c4_i30] = c4_y[c4_i30];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int32_T c4_i31;
  const mxArray *c4_y = NULL;
  real_T c4_u[4];
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  for (c4_i31 = 0; c4_i31 < 4; c4_i31++) {
    c4_u[c4_i31] = (*(real_T (*)[4])c4_inData)[c4_i31];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 1, 4), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_g_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_H, const char_T *c4_identifier, real_T c4_y[4])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_H), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_H);
}

static void c4_h_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[4])
{
  real_T c4_dv7[4];
  int32_T c4_i32;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv7, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c4_i32 = 0; c4_i32 < 4; c4_i32++) {
    c4_y[c4_i32] = c4_dv7[c4_i32];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_H;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[4];
  int32_T c4_i33;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_b_H = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_H), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_H);
  for (c4_i33 = 0; c4_i33 < 4; c4_i33++) {
    (*(real_T (*)[4])c4_outData)[c4_i33] = c4_y[c4_i33];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_untitled_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c4_nameCaptureInfo;
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_i_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i34;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i34, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i34;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_j_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_untitled, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_untitled), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_untitled);
  return c4_y;
}

static uint8_T c4_k_emlrt_marshallIn(SFc4_untitledInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_untitledInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_untitledInstanceStruct *chartInstance)
{
  chartInstance->c4_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c4_H = (real_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_Pren_max = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_f = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_P_load = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_K = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_A = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c4_lb = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c4_ub = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c4_lbA = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c4_ubA = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c4_Pcsis_max = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c4_untitled_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2226993291U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(301779701U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(831012217U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1637015793U);
}

mxArray* sf_c4_untitled_get_post_codegen_info(void);
mxArray *sf_c4_untitled_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("DiGZc95RbdhEXWDDZqx7o");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c4_untitled_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_untitled_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_untitled_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c4_untitled_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_untitled_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c4_untitled(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[9],T\"A\",},{M[1],M[16],T\"H\",},{M[1],M[5],T\"f\",},{M[1],M[10],T\"lb\",},{M[1],M[12],T\"lbA\",},{M[1],M[11],T\"ub\",},{M[1],M[13],T\"ubA\",},{M[8],M[0],T\"is_active_c4_untitled\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_untitled_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_untitledInstanceStruct *chartInstance = (SFc4_untitledInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _untitledMachineNumber_,
           4,
           1,
           1,
           0,
           11,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_untitledMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_untitledMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _untitledMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Pren_max");
          _SFD_SET_DATA_PROPS(1,1,1,0,"P_load");
          _SFD_SET_DATA_PROPS(2,1,1,0,"K");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Pcsis_max");
          _SFD_SET_DATA_PROPS(4,2,0,1,"H");
          _SFD_SET_DATA_PROPS(5,2,0,1,"f");
          _SFD_SET_DATA_PROPS(6,2,0,1,"A");
          _SFD_SET_DATA_PROPS(7,2,0,1,"lb");
          _SFD_SET_DATA_PROPS(8,2,0,1,"ub");
          _SFD_SET_DATA_PROPS(9,2,0,1,"lbA");
          _SFD_SET_DATA_PROPS(10,2,0,1,"ubA");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3094);
        _SFD_CV_INIT_EML_IF(0,1,0,2845,2854,2988,3081);
        _SFD_CV_INIT_EML_IF(0,1,1,2923,2934,2956,2987);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,2848,2853,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,2926,2933,-1,5);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_d_sf_marshallOut,(MexInFcnForType)
            c4_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)
            c4_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)
            c4_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _untitledMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_untitledInstanceStruct *chartInstance = (SFc4_untitledInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c4_H);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c4_Pren_max);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c4_f);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c4_P_load);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c4_K);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c4_A);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c4_lb);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c4_ub);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c4_lbA);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c4_ubA);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c4_Pcsis_max);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sAs9Ep18OjkYGYLDOquNdSG";
}

static void sf_opaque_initialize_c4_untitled(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_untitledInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
  initialize_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_untitled(void *chartInstanceVar)
{
  enable_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_untitled(void *chartInstanceVar)
{
  disable_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_untitled(void *chartInstanceVar)
{
  sf_gateway_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_untitled(SimStruct* S)
{
  return get_sim_state_c4_untitled((SFc4_untitledInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_untitled(SimStruct* S, const mxArray *st)
{
  set_sim_state_c4_untitled((SFc4_untitledInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c4_untitled(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_untitledInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_untitled_optimization_info();
    }

    finalize_c4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_untitled((SFc4_untitledInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_untitled(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_untitled((SFc4_untitledInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c4_untitled(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_untitled_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 4);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,7);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=7; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2748267051U));
  ssSetChecksum1(S,(3371531952U));
  ssSetChecksum2(S,(1589117586U));
  ssSetChecksum3(S,(1962113180U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_untitled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_untitled(SimStruct *S)
{
  SFc4_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc4_untitledInstanceStruct *)utMalloc(sizeof
    (SFc4_untitledInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc4_untitledInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_untitled;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_untitled;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_untitled;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_untitled;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_untitled;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_untitled;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_untitled;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_untitled;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_untitled;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_untitled;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_untitled;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c4_untitled(chartInstance);
}

void c4_untitled_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_untitled(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_untitled(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_untitled(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_untitled_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
