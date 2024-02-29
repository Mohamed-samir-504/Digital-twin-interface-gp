/*
 * File: cpu2.h
 *
 * Code generated for Simulink model 'cpu2'.
 *
 * Model version                  : 5.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Feb 29 14:02:37 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_cpu2_h_
#define RTW_HEADER_cpu2_h_
#ifndef cpu2_COMMON_INCLUDES_
#define cpu2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "MW_c28xIPC.h"
#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "DSP28xx_SciUtil.h"
#endif                                 /* cpu2_COMMON_INCLUDES_ */

#include "cpu2_types.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

extern void configureCPU2Peripherals(uint32_T gpioNumber, uint32_T gpGRegValA,
  uint32_T gpRegValA);
extern void init_SCI(void);
extern void init_SCI_GPIO(void);

/* Block signals (default storage) */
typedef struct {
  real32_T IPCReceive_o1;              /* '<Root>/IPC Receive' */
  real32_T SCIReceive1;                /* '<Root>/SCI Receive1' */
  uint16_T IPCReceive_o2;              /* '<Root>/IPC Receive' */
} B_cpu2_T;

/* Real-time Model Data Structure */
struct tag_RTM_cpu2_T {
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

/* Block signals (default storage) */
extern B_cpu2_T cpu2_B;

/* Model entry point functions */
extern void cpu2_initialize(void);
extern void cpu2_step(void);
extern void cpu2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_cpu2_T *const cpu2_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
 * '<Root>' : 'cpu2'
 */
#endif                                 /* RTW_HEADER_cpu2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
