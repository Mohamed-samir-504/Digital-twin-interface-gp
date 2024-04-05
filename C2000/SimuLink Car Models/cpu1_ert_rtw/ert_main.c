/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 5.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Mar 28 14:41:11 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "cpu1.h"
#include "rtwtypes.h"
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
boolean_T isRateRunning[2] = { 0, 0 };

boolean_T need2runFlags[2] = { 0, 0 };

void rt_OneStep(void)
{
  boolean_T eventFlags[2];

  /* Check base rate for overrun */
  if (isRateRunning[0]++) {
    IsrOverrun = 1;
    isRateRunning[0]--;                /* allow future iterations to succeed*/
    return;
  }

  /*
   * For a bare-board target (i.e., no operating system), the rates
   * that execute this base step are buffered locally to allow for
   * overlapping preemption.
   */
  cpu1_SetEventsForThisBaseStep(eventFlags);
  enableTimer0Interrupt();
  cpu1_step0();

  /* Get model outputs here */
  disableTimer0Interrupt();
  isRateRunning[0]--;
  if (eventFlags[1]) {
    if (need2runFlags[1]++) {
      IsrOverrun = 1;
      need2runFlags[1]--;              /* allow future iterations to succeed*/
      return;
    }
  }

  if (need2runFlags[1]) {
    if (isRateRunning[1]) {
      /* Yield to higher priority*/
      return;
    }

    isRateRunning[1]++;
    enableTimer0Interrupt();

    /* Step the model for subrate "1" */
    switch (1)
    {
     case 1 :
      cpu1_step1();

      /* Get model outputs here */
      break;

     default :
      break;
    }

    disableTimer0Interrupt();
    need2runFlags[1]--;
    isRateRunning[1]--;
  }
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
  float modelBaseRate = 0.001;
  float systemClock = 200;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  c2000_flash_init();
  init_board();

#if defined(MW_EXEC_PROFILER_ON) || (defined(MW_EXTMODE_RUNNING) && !defined(XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME))

  hardwareTimer1Init();

#endif

  ;
  rtmSetErrorStatus(cpu1_M, 0);
  cpu1_initialize();
  globalInterruptDisable();
  configureTimer0(modelBaseRate, systemClock);
  runModel = rtmGetErrorStatus(cpu1_M) == (NULL);
  enableTimer0Interrupt();
  globalInterruptEnable();
  while (runModel) {
    stopRequested = !(rtmGetErrorStatus(cpu1_M) == (NULL));
  }

  /* Terminate model */
  cpu1_terminate();
  globalInterruptDisable();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
