/*
 * File: untitled.c
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Feb 22 14:55:35 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"

/* Block signals (default storage) */
B_untitled_T untitled_B;

/* Real-time model */
static RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  /* S-Function (c28xsci_rx): '<Root>/SCI Receive' */
  {
    int16_T i;
    int16_T errFlg = NOERROR;
    uint16_T isHeadReceived = 1U;
    uint16_T recbuff[1];
    for (i = 0; i < 1; i++) {
      recbuff[i] = 0U;
    }

    /* Getting Data Head */
    {
      uint16_T recHead = 0;
      uint16_T cnt = 0;
      int16_T headIndex = 0;
      unsigned char *expHead = "S";
      while (headIndex < 1) {
        scia_rcv(&recHead, 1, 1);
        if (recHead == expHead[headIndex]) {
          headIndex++;
        } else {
          headIndex = 0;
        }

        if (cnt++ > 16U) {
          errFlg = TIMEOUT;
          isHeadReceived = 0U;
          asm(" NOP");
          break;
        }
      }
    }

    /* End of Getting Data Head */
    errFlg = NOERROR;

    /* Receiving data: For uint32 and uint16, rcvBuff will contain uint16 data */
    if (isHeadReceived) {
      errFlg = scia_rcv(recbuff, 1, 1);
      asm(" NOP");

      /* Getting Data Tail */
      {
        int16_T tailIndex;
        unsigned char *expTail = "E";
        uint16_T recTail[1];
        int16_T recTailCnt;
        for (recTailCnt = 0; recTailCnt < 1; recTailCnt++) {
          recTail[recTailCnt] = 0;
        }

        scia_rcv(recTail, 1, 1);
        for (tailIndex = 0; tailIndex< 1; tailIndex++) {
          if (expTail[tailIndex] != recTail[tailIndex]) {
            errFlg = DATAERR;
            asm(" NOP");
            break;
          }
        }
      }

      /* End of Getting Data Tail */
      if ((errFlg == NOERROR) || (errFlg == PARTIALDATA)) {
        memcpy( &untitled_B.SCIReceive, recbuff, 1);
      }
    }
  }

  /* S-Function (c28xsci_tx): '<Root>/SCI Transmit' */
  {
    if (checkSCITransmitInprogress != 1) {
      checkSCITransmitInprogress = 1;
      int16_T errFlgHeader = NOERROR;
      int16_T errFlgData = NOERROR;
      int16_T errFlgTail = NOERROR;

      /* Send additional data header */
      {
        unsigned char *String = "S";
        errFlgHeader = scib_xmit(String, 1, 1);
      }

      errFlgData = scib_xmit((unsigned char*)&untitled_B.SCIReceive, 1, 1);

      /* Send additional data terminator */
      {
        unsigned char *String = "E";
        errFlgTail = scib_xmit(String, 1, 1);
      }

      checkSCITransmitInprogress = 0;
    }
  }
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(untitled_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &untitled_B), 0,
                sizeof(B_untitled_T));

  /* Start for S-Function (c28xsci_rx): '<Root>/SCI Receive' */

  /* Initialize out port */
  {
    untitled_B.SCIReceive = (uint16_T)0.0;
  }
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
