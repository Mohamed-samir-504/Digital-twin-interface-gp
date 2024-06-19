/*
 * File: cpu1.h
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 5.3
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Apr 18 15:00:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_cpu1_h_
#define RTW_HEADER_cpu1_h_
#ifndef cpu1_COMMON_INCLUDES_
#define cpu1_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "MW_c28xIPC.h"
#include "can_message.h"
#include "F2837xD_device.h"
#include "DSP28xx_SciUtil.h"
#include "MW_c2000DAC.h"
#endif                                 /* cpu1_COMMON_INCLUDES_ */

#include "cpu1_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

extern void init_eCAN_B ( uint16_T bitRatePrescaler, uint16_T timeSeg1, uint16_T
  timeSeg2, uint16_T sbg, uint16_T sjw, uint16_T sam);
extern void init_SCI(void);
extern void init_SCI_GPIO(void);

/* user code (top of export header file) */
#include "can_message.h"

/* Block signals (default storage) */

typedef struct {
  real_T kd;                           /* '<Root>/ready' */
  real_T reset;                        /* '<Root>/ready' */
  real_T sat;                          /* '<Root>/Chart4' */
  real_T kp;                           /* '<Root>/Chart4' */
  real_T ki;                           /* '<Root>/Chart4' */
  real_T kd_l;                         /* '<Root>/Chart4' */
  real_T reset_f;                      /* '<Root>/Chart4' */
  real32_T ADC2;                       /* '<S7>/ADC2' */
  real32_T Gain9;                      /* '<S2>/Gain9' */
  real32_T IPCReceive_o1;              /* '<Root>/IPC Receive' */
  real32_T RT_l;                       /* '<Root>/RT' */
  union type_uni
  {
      float f;
      uint32_t i;
  } SCIReceive[2];              /* '<Root>/SCI Receive' */
  real32_T MovingAverage;              /* '<Root>/Moving Average' */
  int32_T DigitalInput1[3];            /* '<S7>/Digital Input1' */
  int32_T DigitalInput4[6];            /* '<S7>/Digital Input4' */
  uint16_T IPCReceive_o2;              /* '<Root>/IPC Receive' */
  uint16_T BytePack[4];                /* '<Root>/Byte Pack' */
} B_cpu1_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_MedianFilter_c_j_T obj; /* '<Root>/Median Filter1' */
  dsp_simulink_MedianFilter_j1_T obj_l;/* '<S7>/Median Filter' */
  dsp_simulink_MedianFilter_cpu_T obj_h;/* '<Root>/Median Filter' */
  dsp_simulink_MovingAverage_cp_T obj_g;/* '<Root>/Moving Average' */
  real_T Delay_DSTATE[100];            /* '<Root>/Delay' */
  real_T Filter_DSTATE;                /* '<S37>/Filter' */
  real_T Filter_DSTATE_o;              /* '<S85>/Filter' */
  real_T f15;                          /* '<Root>/Chart4' */
  real_T f20;                          /* '<Root>/Chart4' */
  real_T f10;                          /* '<Root>/Chart4' */
  real32_T Integrator_DSTATE;          /* '<S42>/Integrator' */
  real32_T Integrator_DSTATE_j;        /* '<S90>/Integrator' */
  real32_T RT_Buffer0;                 /* '<Root>/RT' */
  int16_T Integrator_PrevResetState;   /* '<S42>/Integrator' */
  int16_T Filter_PrevResetState;       /* '<S37>/Filter' */
  int16_T Integrator_PrevResetState_e; /* '<S90>/Integrator' */
  int16_T Filter_PrevResetState_d;     /* '<S85>/Filter' */
  uint16_T is_c16_cpu1;                /* '<Root>/ready' */
  uint16_T is_active_c16_cpu1;         /* '<Root>/ready' */
  uint16_T is_c18_cpu1;                /* '<Root>/Chart4' */
  uint16_T is_active_c18_cpu1;         /* '<Root>/Chart4' */
} DW_cpu1_T;

/* Parameters (default storage) */
struct P_cpu1_T_ {
  real_T PIDController1_InitialCondition;
                              /* Mask Parameter: PIDController1_InitialCondition
                               * Referenced by: '<S37>/Filter'
                               */
  real_T PIDController2_InitialCondition;
                              /* Mask Parameter: PIDController2_InitialCondition
                               * Referenced by: '<S85>/Filter'
                               */
  real32_T PIDController1_InitialConditi_j;
                              /* Mask Parameter: PIDController1_InitialConditi_j
                               * Referenced by: '<S42>/Integrator'
                               */
  real32_T PIDController2_InitialConditi_o;
                              /* Mask Parameter: PIDController2_InitialConditi_o
                               * Referenced by: '<S90>/Integrator'
                               */
  real32_T PIDController1_LowerSaturationL;
                              /* Mask Parameter: PIDController1_LowerSaturationL
                               * Referenced by:
                               *   '<S49>/Saturation'
                               *   '<S35>/DeadZone'
                               */
  real32_T PIDController2_LowerSaturationL;
                              /* Mask Parameter: PIDController2_LowerSaturationL
                               * Referenced by: '<S97>/Saturation'
                               */
  real32_T PIDController1_UpperSaturationL;
                              /* Mask Parameter: PIDController1_UpperSaturationL
                               * Referenced by:
                               *   '<S49>/Saturation'
                               *   '<S35>/DeadZone'
                               */
  real32_T PIDController2_UpperSaturationL;
                              /* Mask Parameter: PIDController2_UpperSaturationL
                               * Referenced by: '<S97>/Saturation'
                               */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<Root>/Delay'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S37>/Filter'
                                        */
  real_T Constant_Value;               /* Expression: 100
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Filter_gainval_l;             /* Computed Parameter: Filter_gainval_l
                                        * Referenced by: '<S85>/Filter'
                                        */
  real_T Constant1_Value;              /* Expression: 100
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Constant5_Value;              /* Expression: 1
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real32_T Constant1_Value_b;          /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S33>/Constant1'
                                        */
  real32_T Constant_Value_f;           /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S7>/Constant'
                                        */
  real32_T Constant1_Value_g;          /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S7>/Constant1'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S7>/Constant2'
                                        */
  real32_T AddConstant2_Bias;          /* Computed Parameter: AddConstant2_Bias
                                        * Referenced by: '<S7>/Add Constant2'
                                        */
  real32_T Gain8_Gain;                 /* Computed Parameter: Gain8_Gain
                                        * Referenced by: '<S2>/Gain8'
                                        */
  real32_T Gain9_Gain;                 /* Computed Parameter: Gain9_Gain
                                        * Referenced by: '<S2>/Gain9'
                                        */
  real32_T RT_InitialCondition;       /* Computed Parameter: RT_InitialCondition
                                       * Referenced by: '<Root>/RT'
                                       */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S42>/Integrator'
                                        */
  real32_T Integrator_gainval_k;     /* Computed Parameter: Integrator_gainval_k
                                      * Referenced by: '<S90>/Integrator'
                                      */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<Root>/Switch'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<Root>/Gain'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T AddConstant1_Bias;          /* Computed Parameter: AddConstant1_Bias
                                        * Referenced by: '<Root>/Add Constant1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real32_T AddConstant_Bias;           /* Computed Parameter: AddConstant_Bias
                                        * Referenced by: '<Root>/Add Constant'
                                        */
  real32_T Gain5_Gain;                 /* Computed Parameter: Gain5_Gain
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real32_T Clamping_zero_Value;       /* Computed Parameter: Clamping_zero_Value
                                       * Referenced by: '<S33>/Clamping_zero'
                                       */
  real32_T Gain8_Gain_a;               /* Computed Parameter: Gain8_Gain_a
                                        * Referenced by: '<S1>/Gain8'
                                        */
  real32_T Gain9_Gain_n;               /* Computed Parameter: Gain9_Gain_n
                                        * Referenced by: '<S1>/Gain9'
                                        */
  uint32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S4>/Constant3'
                                        */
  int16_T Constant_Value_l;            /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S33>/Constant'
                                        */
  int16_T Constant2_Value_g;           /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S33>/Constant2'
                                        */
  int16_T Constant3_Value_h;           /* Computed Parameter: Constant3_Value_h
                                        * Referenced by: '<S33>/Constant3'
                                        */
  int16_T Constant4_Value;             /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S33>/Constant4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_cpu1_T {
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

    struct {
      boolean_T TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block parameters (default storage) */
extern P_cpu1_T cpu1_P;

/* Block signals (default storage) */
extern B_cpu1_T cpu1_B;

/* Block states (default storage) */
extern DW_cpu1_T cpu1_DW;

/* External function called from main */
extern void cpu1_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void cpu1_initialize(void);
extern void cpu1_step0(void);
extern void cpu1_step1(void);
extern void cpu1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_cpu1_T *const cpu1_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Constant' : Unused code path elimination
 * Block '<S4>/Constant1' : Unused code path elimination
 * Block '<S4>/Counter1' : Unused code path elimination
 * Block '<S4>/Display' : Unused code path elimination
 * Block '<S4>/Display10' : Unused code path elimination
 * Block '<Root>/RT1' : Eliminated since input and output rates are identical
 */

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
 * '<Root>' : 'cpu1'
 * '<S1>'   : 'cpu1/ Approximation1'
 * '<S2>'   : 'cpu1/ Approximation3'
 * '<S3>'   : 'cpu1/Chart4'
 * '<S4>'   : 'cpu1/If Action Subsystem'
 * '<S5>'   : 'cpu1/PID Controller1'
 * '<S6>'   : 'cpu1/PID Controller2'
 * '<S7>'   : 'cpu1/Subsystem1'
 * '<S8>'   : 'cpu1/ready'
 * '<S9>'   : 'cpu1/PID Controller1/Anti-windup'
 * '<S10>'  : 'cpu1/PID Controller1/D Gain'
 * '<S11>'  : 'cpu1/PID Controller1/Filter'
 * '<S12>'  : 'cpu1/PID Controller1/Filter ICs'
 * '<S13>'  : 'cpu1/PID Controller1/I Gain'
 * '<S14>'  : 'cpu1/PID Controller1/Ideal P Gain'
 * '<S15>'  : 'cpu1/PID Controller1/Ideal P Gain Fdbk'
 * '<S16>'  : 'cpu1/PID Controller1/Integrator'
 * '<S17>'  : 'cpu1/PID Controller1/Integrator ICs'
 * '<S18>'  : 'cpu1/PID Controller1/N Copy'
 * '<S19>'  : 'cpu1/PID Controller1/N Gain'
 * '<S20>'  : 'cpu1/PID Controller1/P Copy'
 * '<S21>'  : 'cpu1/PID Controller1/Parallel P Gain'
 * '<S22>'  : 'cpu1/PID Controller1/Reset Signal'
 * '<S23>'  : 'cpu1/PID Controller1/Saturation'
 * '<S24>'  : 'cpu1/PID Controller1/Saturation Fdbk'
 * '<S25>'  : 'cpu1/PID Controller1/Sum'
 * '<S26>'  : 'cpu1/PID Controller1/Sum Fdbk'
 * '<S27>'  : 'cpu1/PID Controller1/Tracking Mode'
 * '<S28>'  : 'cpu1/PID Controller1/Tracking Mode Sum'
 * '<S29>'  : 'cpu1/PID Controller1/Tsamp - Integral'
 * '<S30>'  : 'cpu1/PID Controller1/Tsamp - Ngain'
 * '<S31>'  : 'cpu1/PID Controller1/postSat Signal'
 * '<S32>'  : 'cpu1/PID Controller1/preSat Signal'
 * '<S33>'  : 'cpu1/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S34>'  : 'cpu1/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S35>'  : 'cpu1/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S36>'  : 'cpu1/PID Controller1/D Gain/External Parameters'
 * '<S37>'  : 'cpu1/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S38>'  : 'cpu1/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S39>'  : 'cpu1/PID Controller1/I Gain/External Parameters'
 * '<S40>'  : 'cpu1/PID Controller1/Ideal P Gain/Passthrough'
 * '<S41>'  : 'cpu1/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S42>'  : 'cpu1/PID Controller1/Integrator/Discrete'
 * '<S43>'  : 'cpu1/PID Controller1/Integrator ICs/Internal IC'
 * '<S44>'  : 'cpu1/PID Controller1/N Copy/Disabled'
 * '<S45>'  : 'cpu1/PID Controller1/N Gain/External Parameters'
 * '<S46>'  : 'cpu1/PID Controller1/P Copy/Disabled'
 * '<S47>'  : 'cpu1/PID Controller1/Parallel P Gain/External Parameters'
 * '<S48>'  : 'cpu1/PID Controller1/Reset Signal/External Reset'
 * '<S49>'  : 'cpu1/PID Controller1/Saturation/Enabled'
 * '<S50>'  : 'cpu1/PID Controller1/Saturation Fdbk/Disabled'
 * '<S51>'  : 'cpu1/PID Controller1/Sum/Sum_PID'
 * '<S52>'  : 'cpu1/PID Controller1/Sum Fdbk/Disabled'
 * '<S53>'  : 'cpu1/PID Controller1/Tracking Mode/Disabled'
 * '<S54>'  : 'cpu1/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'cpu1/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S56>'  : 'cpu1/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'cpu1/PID Controller1/postSat Signal/Forward_Path'
 * '<S58>'  : 'cpu1/PID Controller1/preSat Signal/Forward_Path'
 * '<S59>'  : 'cpu1/PID Controller2/Anti-windup'
 * '<S60>'  : 'cpu1/PID Controller2/D Gain'
 * '<S61>'  : 'cpu1/PID Controller2/Filter'
 * '<S62>'  : 'cpu1/PID Controller2/Filter ICs'
 * '<S63>'  : 'cpu1/PID Controller2/I Gain'
 * '<S64>'  : 'cpu1/PID Controller2/Ideal P Gain'
 * '<S65>'  : 'cpu1/PID Controller2/Ideal P Gain Fdbk'
 * '<S66>'  : 'cpu1/PID Controller2/Integrator'
 * '<S67>'  : 'cpu1/PID Controller2/Integrator ICs'
 * '<S68>'  : 'cpu1/PID Controller2/N Copy'
 * '<S69>'  : 'cpu1/PID Controller2/N Gain'
 * '<S70>'  : 'cpu1/PID Controller2/P Copy'
 * '<S71>'  : 'cpu1/PID Controller2/Parallel P Gain'
 * '<S72>'  : 'cpu1/PID Controller2/Reset Signal'
 * '<S73>'  : 'cpu1/PID Controller2/Saturation'
 * '<S74>'  : 'cpu1/PID Controller2/Saturation Fdbk'
 * '<S75>'  : 'cpu1/PID Controller2/Sum'
 * '<S76>'  : 'cpu1/PID Controller2/Sum Fdbk'
 * '<S77>'  : 'cpu1/PID Controller2/Tracking Mode'
 * '<S78>'  : 'cpu1/PID Controller2/Tracking Mode Sum'
 * '<S79>'  : 'cpu1/PID Controller2/Tsamp - Integral'
 * '<S80>'  : 'cpu1/PID Controller2/Tsamp - Ngain'
 * '<S81>'  : 'cpu1/PID Controller2/postSat Signal'
 * '<S82>'  : 'cpu1/PID Controller2/preSat Signal'
 * '<S83>'  : 'cpu1/PID Controller2/Anti-windup/Passthrough'
 * '<S84>'  : 'cpu1/PID Controller2/D Gain/External Parameters'
 * '<S85>'  : 'cpu1/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S86>'  : 'cpu1/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S87>'  : 'cpu1/PID Controller2/I Gain/External Parameters'
 * '<S88>'  : 'cpu1/PID Controller2/Ideal P Gain/Passthrough'
 * '<S89>'  : 'cpu1/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S90>'  : 'cpu1/PID Controller2/Integrator/Discrete'
 * '<S91>'  : 'cpu1/PID Controller2/Integrator ICs/Internal IC'
 * '<S92>'  : 'cpu1/PID Controller2/N Copy/Disabled'
 * '<S93>'  : 'cpu1/PID Controller2/N Gain/External Parameters'
 * '<S94>'  : 'cpu1/PID Controller2/P Copy/Disabled'
 * '<S95>'  : 'cpu1/PID Controller2/Parallel P Gain/External Parameters'
 * '<S96>'  : 'cpu1/PID Controller2/Reset Signal/External Reset'
 * '<S97>'  : 'cpu1/PID Controller2/Saturation/Enabled'
 * '<S98>'  : 'cpu1/PID Controller2/Saturation Fdbk/Disabled'
 * '<S99>'  : 'cpu1/PID Controller2/Sum/Sum_PID'
 * '<S100>' : 'cpu1/PID Controller2/Sum Fdbk/Disabled'
 * '<S101>' : 'cpu1/PID Controller2/Tracking Mode/Disabled'
 * '<S102>' : 'cpu1/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S103>' : 'cpu1/PID Controller2/Tsamp - Integral/Passthrough'
 * '<S104>' : 'cpu1/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S105>' : 'cpu1/PID Controller2/postSat Signal/Forward_Path'
 * '<S106>' : 'cpu1/PID Controller2/preSat Signal/Forward_Path'
 * '<S107>' : 'cpu1/Subsystem1/MATLAB Function'
 * '<S108>' : 'cpu1/Subsystem1/MATLAB Function1'
 * '<S109>' : 'cpu1/Subsystem1/MATLAB Function2'
 * '<S110>' : 'cpu1/Subsystem1/Steering Ratio (polo)'
 * '<S111>' : 'cpu1/Subsystem1/map_angle1'
 */
#endif                                 /* RTW_HEADER_cpu1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
