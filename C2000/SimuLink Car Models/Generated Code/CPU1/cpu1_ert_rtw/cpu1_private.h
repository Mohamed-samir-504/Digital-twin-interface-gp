/*
 * File: cpu1_private.h
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 1.291
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Feb 29 13:40:21 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_cpu1_private_h_
#define RTW_HEADER_cpu1_private_h_
#include "rtwtypes.h"
#include "cpu1_types.h"

void InitAdcA (void);
void config_ADCA_SOC0 (void);
extern uint16_T MW_adcAInitFlag;
extern real32_T rt_roundf_snf(real32_T u);

#endif                                 /* RTW_HEADER_cpu1_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
