/*
 * File: cpu1_private.h
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

#ifndef RTW_HEADER_cpu1_private_h_
#define RTW_HEADER_cpu1_private_h_
#include "rtwtypes.h"
#include "cpu1_types.h"
#include "can_message.h"
#include "can_message.h"
#include "can_message.h"
#include "can_message.h"
#include "MW_f2837xD_includes.h"

void InitAdcA (void);
void config_ADCA_SOC0 (void);
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern uint16_T MW_adcAInitFlag;
extern real32_T rt_roundf_snf(real32_T u);

#endif                                 /* RTW_HEADER_cpu1_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
