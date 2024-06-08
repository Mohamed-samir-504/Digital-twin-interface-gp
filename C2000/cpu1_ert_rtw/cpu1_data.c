/*
 * File: cpu1_data.c
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 5.0
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Jun  6 14:27:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "cpu1.h"

/* Block parameters (default storage) */
P_cpu1_T cpu1_P = {
  /* Mask Parameter: PIDController1_InitialCondition
   * Referenced by: '<S37>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController2_InitialCondition
   * Referenced by: '<S85>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditi_j
   * Referenced by: '<S42>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController2_InitialConditi_o
   * Referenced by: '<S90>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController1_LowerSaturationL
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S35>/DeadZone'
   */
  -2.0F,

  /* Mask Parameter: PIDController2_LowerSaturationL
   * Referenced by: '<S97>/Saturation'
   */
  -2.0F,

  /* Mask Parameter: PIDController1_UpperSaturationL
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S35>/DeadZone'
   */
  2.0F,

  /* Mask Parameter: PIDController2_UpperSaturationL
   * Referenced by: '<S97>/Saturation'
   */
  2.0F,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay'
   */
  0.0,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S37>/Filter'
   */
  0.001,

  /* Expression: 100
   * Referenced by: '<Root>/Constant'
   */
  100.0,

  /* Computed Parameter: Filter_gainval_l
   * Referenced by: '<S85>/Filter'
   */
  0.001,

  /* Expression: 100
   * Referenced by: '<Root>/Constant1'
   */
  100.0,

  /* Expression: 1
   * Referenced by: '<Root>/Constant5'
   */
  1.0,

  /* Computed Parameter: Constant1_Value_b
   * Referenced by: '<S33>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<S7>/Constant'
   */
  2600.0F,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S7>/Constant1'
   */
  440.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S7>/Constant2'
   */
  0.0F,

  /* Computed Parameter: AddConstant2_Bias
   * Referenced by: '<S7>/Add Constant2'
   */
  -0.3005F,

  /* Computed Parameter: Gain8_Gain
   * Referenced by: '<S2>/Gain8'
   */
  100.0F,

  /* Computed Parameter: Gain9_Gain
   * Referenced by: '<S2>/Gain9'
   */
  0.01F,

  /* Computed Parameter: RT_InitialCondition
   * Referenced by: '<Root>/RT'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S42>/Integrator'
   */
  0.001F,

  /* Computed Parameter: Integrator_gainval_k
   * Referenced by: '<S90>/Integrator'
   */
  0.001F,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<Root>/Switch'
   */
  5.0F,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<Root>/Gain'
   */
  1360.79736F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<Root>/Gain1'
   */
  -1.0F,

  /* Computed Parameter: AddConstant1_Bias
   * Referenced by: '<Root>/Add Constant1'
   */
  3401.99341F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<Root>/Gain2'
   */
  0.6F,

  /* Computed Parameter: AddConstant_Bias
   * Referenced by: '<Root>/Add Constant'
   */
  3401.99341F,

  /* Computed Parameter: Gain5_Gain
   * Referenced by: '<Root>/Gain5'
   */
  0.6F,

  /* Computed Parameter: Clamping_zero_Value
   * Referenced by: '<S33>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Gain8_Gain_a
   * Referenced by: '<S1>/Gain8'
   */
  10.0F,

  /* Computed Parameter: Gain9_Gain_n
   * Referenced by: '<S1>/Gain9'
   */
  0.1F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S4>/Constant3'
   */
  4294914079U,

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S33>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S33>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_h
   * Referenced by: '<S33>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S33>/Constant4'
   */
  -1
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
