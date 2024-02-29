#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "rtwtypes.h"
#include "cpu2.h"
#include "cpu2_private.h"

extern void configureInputXBar(uint32_T gpioNumber, uint32_T inputXbarNumber);
void enableExtInterrupt (void);
void disableWatchdog(void)
{
  int *WatchdogWDCR = (void *) 0x7029;
  asm(" EALLOW ");
  *WatchdogWDCR = 0x0068;
  asm(" EDIS ");
}

int16_T checkSCITransmitInprogress;
void init_SCI(void)
{
  // to prevent re-entrancy in SCI transmit function
  checkSCITransmitInprogress = 0;

  /* initialize SCI & FIFO registers */
  EALLOW;

  /*
   * Initialize SCI_B with following parameters:
   *    BaudRate              : 115207
   *    CharacterLengthBits   : 8
   *    EnableLoopBack        : 0
   *    NumberOfStopBits      : 1
   *    ParityMode            : None
   *    SuspensionMode        : Free_run
   *    CommMode              : Raw_data
   */
  CpuSysRegs.PCLKCR7.bit.SCI_B = 1U;
  asm(" NOP");
  ScibRegs.SCICCR.bit.STOPBITS = 0U;
                    /*Number of stop bits. (0: One stop bit, 1: Two stop bits)*/
  ScibRegs.SCICCR.bit.PARITY = 0U;
                                 /*Parity mode (0: Odd parity, 1: Even parity)*/
  ScibRegs.SCICCR.bit.PARITYENA = 0U;  /*Enable Pary Mode */
  ScibRegs.SCICCR.bit.LOOPBKENA = 0U;  /*Loop Back enable*/
  ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0U;/*ADDR/IDLE Mode control*/
  ScibRegs.SCICCR.bit.SCICHAR = 7U;    /*Character length*/
  ScibRegs.SCICTL1.bit.RXERRINTENA = 0U;/*Disable receive error interrupt*/
  ScibRegs.SCICTL1.bit.SWRESET = 1U;   /*Software reset*/
  ScibRegs.SCICTL1.bit.TXENA = 1U;     /* SCI transmitter enable*/
  ScibRegs.SCICTL1.bit.RXENA = 1U;     /* SCI receiver enable*/
  ScibRegs.SCIHBAUD.bit.BAUD = 0U;
  ScibRegs.SCILBAUD.bit.BAUD = 216U;

  /*Free run, continue SCI operation regardless of suspend*/
  ScibRegs.SCIPRI.bit.FREESOFT = 3U;
  ScibRegs.SCIFFCT.bit.ABDCLR = 0U;
  ScibRegs.SCIFFCT.bit.CDC = 0U;
  ScibRegs.SCIFFTX.bit.SCIRST = 1U;    /* SCI reset rx/tx channels*/
  ScibRegs.SCIFFTX.bit.SCIFFENA = 1U;  /* SCI FIFO enhancements are enabled.*/
  ScibRegs.SCIFFTX.bit.TXFIFORESET = 1U;/* Re-enable transmit FIFO operation.*/
  ScibRegs.SCIFFRX.bit.RXFIFORESET = 1U;/* Re-enable receive FIFO operation.*/
  EDIS;
}

void init_SCI_GPIO(void)
{
  EALLOW;
  configureCPU2Peripherals(19, 0, 2);
  configureCPU2Peripherals(18, 0, 2);
  EDIS;
}
