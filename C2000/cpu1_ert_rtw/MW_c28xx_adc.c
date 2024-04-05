#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "rtwtypes.h"
#include "cpu1.h"
#include "cpu1_private.h"

void config_ADCA_SOC0(void)
{
  EALLOW;
  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 2U;  /* Set SOC0 channel select to ADCIN2*/
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0U;
  AdcaRegs.ADCSOC0CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcaRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correctino Value*/
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
                                /* Late interrupt pulse trips AdcResults latch*/
  AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void InitAdcA(void)
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_A = 1U;
  AdcaRegs.ADCCTL2.bit.PRESCALE = 8U;
  AdcSetMode((uint16_T)ADC_ADCA, (uint16_T)ADC_RESOLUTION_12BIT,(uint16_T)
             ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1U;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}
