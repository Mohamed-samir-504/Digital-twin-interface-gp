/*
 * File: DSP28xx_SciUtil.h
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 5.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Mar 28 15:14:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DSP28xx_SciUtil_h_
#define RTW_HEADER_DSP28xx_SciUtil_h_
#include "MW_f2837xD_includes.h"
#include "F2837xD_device.h"
#include <string.h>
#include "rtwtypes.h"
#define NOERROR                        0                         /* no error*/
#define TIMEOUT                        1                         /* waiting timeout*/
#define DATAERR                        2                         /* data error (checksum error)*/
#define PRTYERR                        3                         /* parity error*/
#define FRAMERR                        4                         /* frame error*/
#define OVRNERR                        5                         /* overrun error*/
#define BRKDTERR                       6                         /* brake-detect error*/
#define DATANOTAVAILABLE               7                         /* Data not available */
#define PARTIALDATA                    8                         /* Partial Data available */

extern int16_T checkSCITransmitInprogress;
int16_T scia_rcv(uint16_T *rcvBuff, int16_T buffLen, int16_T typeLen);
int16_T scia_rcv_varsize(uint16_T *rcvBuff, int16_T buffLen, int16_T typeLen,
  unsigned char *expTail, int16_T tailsize, int16_T *rcvBufferLen);
int16_T byteswap_L8cmp(uint16_T* outdata, unsigned char* recdata, int16_T
  inportWidth, int16_T typeLen);

#endif                                 /* RTW_HEADER_DSP28xx_SciUtil_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
