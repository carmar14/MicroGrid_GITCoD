/*
 * File: todo_data.c
 *
 * Code generated for Simulink model 'todo'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Feb 07 10:17:29 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "todo.h"
#include "todo_private.h"

/* Constant parameters (auto storage) */
const ConstP_todo_T todo_ConstP = {
  /* Pooled Parameter (Expression: zeros(8,1))
   * Referenced by:
   *   '<S128>/SwitchCurrents'
   *   '<S132>/SwitchCurrents'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: S.A)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  { -0.93050251249358462, 0.052649611747284331, 0.0, -1.9304857640670928E-5,
    0.99998537510784791, 0.0, 0.0, 0.0, 0.99924271109428242 },

  /* Pooled Parameter (Expression: S.B)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  { -579145.72922012769, -438746.76456070278, 0.0, 579145.72922012769,
    438746.76456070278, 0.0, 579145.72922012769, 438746.76456070278, 0.0,
    -579145.72922012769, -438746.76456070278, 0.0, 579145.72922012769,
    438746.76456070278, 0.0, -579145.72922012769, -438746.76456070278, 0.0,
    -579145.72922012769, -438746.76456070278, 0.0, 579145.72922012769,
    438746.76456070278, 0.0, 0.0, 0.0, 454.37334343051867 },

  /* Pooled Parameter (Expression: S.C)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  { -0.0028957286461006389, 0.0028957286461006389, 0.0028957286461006389,
    -0.0028957286461006389, 0.0028957286461006389, -0.0028957286461006389,
    -0.0028957286461006389, 0.0028957286461006389, 4.9666133748271568E-8,
    0.0057914572922012778, 0.0, 8.0436906836128857E-7, -8.0436906836128857E-7,
    -8.0436906836128857E-7, 8.0436906836128857E-7, -8.0436906836128857E-7,
    8.0436906836128857E-7, 8.0436906836128857E-7, -8.0436906836128857E-7,
    1.666652870518403E-6, -1.6087381367225771E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: S.D)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  { -25868.927949161345, 25868.927949161345, -24131.072050838655,
    24131.072050838655, 25868.927949161345, -25868.927949161345,
    24131.072050838655, -24131.072050838655, -0.413884447902263,
    1737.8558983226903, 0.0, 25868.927949161345, -25868.927949161345,
    24131.072050838655, -24131.072050838655, -25868.927949161345,
    25868.927949161345, -24131.072050838655, 24131.072050838655,
    0.413884447902263, -1737.8558983226903, 0.0, -24131.072050838655,
    24131.072050838655, -25868.927949161345, 25868.927949161345,
    24131.072050838655, -24131.072050838655, 25868.927949161345,
    -25868.927949161345, 0.413884447902263, -1737.8558983226903, 0.0,
    24131.072050838655, -24131.072050838655, 25868.927949161345,
    -25868.927949161345, -24131.072050838655, 24131.072050838655,
    -25868.927949161345, 25868.927949161345, -0.413884447902263,
    1737.8558983226903, 0.0, 25868.927949161345, -25868.927949161345,
    24131.072050838655, -24131.072050838655, -25868.927949161345,
    25868.927949161345, -24131.072050838655, 24131.072050838655,
    0.413884447902263, -1737.8558983226903, 0.0, -25868.927949161345,
    25868.927949161345, -24131.072050838655, 24131.072050838655,
    25868.927949161345, -25868.927949161345, 24131.072050838655,
    -24131.072050838655, -0.413884447902263, 1737.8558983226903, 0.0,
    24131.072050838655, -24131.072050838655, 25868.927949161345,
    -25868.927949161345, -24131.072050838655, 24131.072050838655,
    -25868.927949161345, 25868.927949161345, -0.413884447902263,
    1737.8558983226903, 0.0, -24131.072050838655, 24131.072050838655,
    -25868.927949161345, 25868.927949161345, 24131.072050838655,
    -24131.072050838655, 25868.927949161345, -25868.927949161345,
    0.413884447902263, -1737.8558983226903, 0.0, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5,
    -0.5, -0.5, 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: S.x0)
   * Referenced by:
   *   '<S124>/State-Space'
   *   '<S125>/State-Space'
   */
  { 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: rep_seq_y)
   * Referenced by:
   *   '<S73>/Look-Up Table1'
   *   '<S122>/Look-Up Table1'
   */
  { -10.5, 10.5, -10.5 },

  /* Pooled Parameter (Expression: rep_seq_t - min(rep_seq_t))
   * Referenced by:
   *   '<S73>/Look-Up Table1'
   *   '<S122>/Look-Up Table1'
   */
  { 0.0, 0.0001, 0.0002 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */