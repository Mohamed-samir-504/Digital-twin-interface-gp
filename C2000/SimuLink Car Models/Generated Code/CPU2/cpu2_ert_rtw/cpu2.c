/*
 * File: cpu2.c
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

#include "cpu2.h"
#include "cpu2_private.h"

/* Block signals (default storage) */
B_cpu2_T cpu2_B;

/* Real-time model */
static RT_MODEL_cpu2_T cpu2_M_;
RT_MODEL_cpu2_T *const cpu2_M = &cpu2_M_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (cpu2_M->Timing.TaskCounters.TID[1])++;
  if ((cpu2_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.1s, 0.0s] */
    cpu2_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void cpu2_step(void)
{
  if (cpu2_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (c28xipc_rx): '<Root>/IPC Receive' */
    MW_IPC_Receive(CHANNEL0, (uint32_t *)&cpu2_B.IPCReceive_o1,
                   &cpu2_B.IPCReceive_o2, 1, 8, 0, 0);

    /* S-Function (c28xsci_tx): '<Root>/SCI Transmit' */
    {
      if (checkSCITransmitInprogress != 1) {
        checkSCITransmitInprogress = 1;
        int16_T errFlgHeader = NOERROR;
        int16_T errFlgData = NOERROR;
        int16_T errFlgTail = NOERROR;
        errFlgData = scib_xmit((unsigned char*)&cpu2_B.IPCReceive_o1, 4, 4);
        checkSCITransmitInprogress = 0;
      }
    }

    /* S-Function (c28xsci_rx): '<Root>/SCI Receive1' */
    {
      int16_T i;
      int16_T errFlg = NOERROR;
      uint16_T isHeadReceived = 1U;

      //get data as uint16 in recBuff
      uint16_T recbuff[2];
      for (i = 0; i < 2; i++) {
        recbuff[i] = 0U;
      }

      errFlg = NOERROR;

      /* Receiving data: For uint32 and uint16, rcvBuff will contain uint16 data */
      if (isHeadReceived) {
        errFlg = scib_rcv(recbuff, 4, 4);
        asm(" NOP");
        if ((errFlg == NOERROR) || (errFlg == PARTIALDATA)) {
          memcpy( &cpu2_B.SCIReceive1, recbuff,2);
        }
      }
    }

    /* S-Function (c28xipc_tx): '<Root>/IPC Transmit' */
    MW_IPC_Transmit(CHANNEL1, (uint32_t *)&cpu2_B.SCIReceive1, 1, 8, 0, 0);
  }

  rate_scheduler();
}

/* Model initialize function */
void cpu2_initialize(void)
{
  /* Start for S-Function (c28xipc_rx): '<Root>/IPC Receive' */
  IPCInit(CHANNEL0, 1, 0);

  /* Start for S-Function (c28xsci_rx): '<Root>/SCI Receive1' */

  /* Initialize out port */
  {
    cpu2_B.SCIReceive1 = (real32_T)0.0;
  }

  /*Configure Timer2 when blocking mode is enabled and Timeout is not inf*/
  {
    /* InitCpuTimers() - CPU Timers are also initialized in
     * MW_c28xx_board.c in the generated code.
     */
    CpuTimer2Regs.PRD.all = 0xFFFFFFFFU;/* max Period*/
    CpuTimer2Regs.TIM.all = 0xFFFFFFFFU;/* set Ctr*/
    CpuTimer2Regs.TPR.all = 0x00U;     /* no prescaler    */
    StartCpuTimer2();
  }

  /* Start for S-Function (c28xipc_tx): '<Root>/IPC Transmit' */
  IPCInit(CHANNEL1, 1, 0);
}

/* Model terminate function */
void cpu2_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
