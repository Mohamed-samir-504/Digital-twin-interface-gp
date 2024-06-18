/*
 * File: cpu1.c
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

#include "cpu1.h"
#include "rtwtypes.h"
#include "cpu1_types.h"
#include <math.h>
#include "cpu1_private.h"
#include "rt_nonfinite.h"
#include "CONFIGURATION.h"
#define cpu1_IN_NO_ACTIVE_CHILD        (0U)
#define cpu1_IN_else                   (1U)
#define cpu1_IN_higherthan15           (2U)
#define cpu1_IN_init                   (2U)
#define cpu1_IN_init_j                 (3U)
#define cpu1_IN_lowerthan15            (4U)
#define cpu1_IN_state1                 (3U)
#define cpu1_IN_state10                (4U)
#define cpu1_IN_state11                (5U)
#define cpu1_IN_state12                (6U)
#define cpu1_IN_state13                (7U)
#define cpu1_IN_state8                 (8U)
#define cpu1_IN_state9                 (9U)

uint32_T counter = 0;
uint16_t transmit_rate = DEFAULT_TRASNMIT_RATE;
#define READ_SWITCH() GpioDataRegs.GPBDAT.bit.GPIO61


/* Block signals (default storage) */
B_cpu1_T cpu1_B;

/* Block states (default storage) */
DW_cpu1_T cpu1_DW;

/* Real-time model */
static RT_MODEL_cpu1_T cpu1_M_;
RT_MODEL_cpu1_T *const cpu1_M = &cpu1_M_;

/* Forward declaration for local functions */
static void cpu_MedianFilterCG_resetImpl_j1(c_dsp_internal_MedianFilte_j1_T *obj);
static void MedianFilterCG_trickleDownMa_j1(c_dsp_internal_MedianFilte_j1_T *obj,
  real32_T i);
static void MedianFilterCG_trickleDownMi_j1(c_dsp_internal_MedianFilte_j1_T *obj,
  real32_T i);
static void cpu1_enter_atomic_state11(const real32_T *Sum);
static void cpu1_enter_atomic_state10(const real32_T *Sum);
static void cpu1_enter_atomic_state8(const real32_T *Sum);
static void cpu1_state9(const real32_T *Sum);
static void cpu1_else(const real32_T *Sum);
static void cpu1_init(const real32_T *Sum);
static void cpu1_state10(const real32_T *Sum);
static void cpu1_state11(const real32_T *Sum);
static void cpu1_state13(const real32_T *Sum);
static void cpu1_state8(const real32_T *Sum);
static void cpu1_MedianFilterCG_resetImpl_j(c_dsp_internal_MedianFilter_j_T *obj);
static void MedianFilterCG_trickleDownMax_j(c_dsp_internal_MedianFilter_j_T *obj,
  real32_T i);
static void MedianFilterCG_trickleDownMin_j(c_dsp_internal_MedianFilter_j_T *obj,
  real32_T i);
static void cpu1_MedianFilterCG_resetImpl(c_dsp_internal_MedianFilterCG_T *obj);
static void c_MedianFilterCG_trickleDownMax(c_dsp_internal_MedianFilterCG_T *obj,
  real32_T i);
static void c_MedianFilterCG_trickleDownMin(c_dsp_internal_MedianFilterCG_T *obj,
  real32_T i);
static void cpu1_SystemCore_setup(dsp_simulink_MovingAverage_cp_T *obj);
static void rate_monotonic_scheduler(void);

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcAInitFlag = 0;

#endif

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void cpu1_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(cpu1_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rate: 1 */
  cpu1_M->Timing.RateInteraction.TID0_1 = (cpu1_M->Timing.TaskCounters.TID[1] ==
    0);

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (cpu1_M->Timing.TaskCounters.TID[1])++;
  if ((cpu1_M->Timing.TaskCounters.TID[1]) > 99) {/* Sample time: [0.1s, 0.0s] */
    cpu1_M->Timing.TaskCounters.TID[1] = 0;
  }
}

static void cpu_MedianFilterCG_resetImpl_j1(c_dsp_internal_MedianFilte_j1_T *obj)
{
  real32_T cnt1;
  real32_T cnt2;
  int16_T i;
  for (i = 0; i < 5; i++) {
    obj->pBuf[i] = 0.0F;
    obj->pPos[i] = 0.0F;
    obj->pHeap[i] = 0.0F;
  }

  obj->pWinLen = 5.0F;
  obj->pIdx = obj->pWinLen;
  obj->pMidHeap = (real32_T)ceil((obj->pWinLen + 1.0F) / 2.0F);
  cnt1 = (obj->pWinLen - 1.0F) / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMinHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMinHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = obj->pWinLen / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMaxHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMaxHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = 1.0F;
  cnt2 = obj->pWinLen;
  for (i = 0; i < 5; i++) {
    if ((int16_T)(real32_T)fmod(5.0F - (real32_T)i, 2.0) == 0) {
      obj->pPos[4 - i] = cnt1;
      cnt1++;
    } else {
      obj->pPos[4 - i] = cnt2;
      cnt2--;
    }

    obj->pHeap[(int16_T)obj->pPos[4 - i] - 1] = 5.0F - (real32_T)i;
  }
}

static void MedianFilterCG_trickleDownMa_j1(c_dsp_internal_MedianFilte_j1_T *obj,
  real32_T i)
{
  real32_T ind2;
  real32_T temp_tmp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i >= -obj->pMaxHeapLength)) {
    if ((i < -1.0F) && (i > -obj->pMaxHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1] < obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i - 1.0F) + obj->pMidHeap) - 1] - 1])) {
      i--;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp_tmp = (real32_T)ceil(u_tmp);
    } else {
      temp_tmp = (real32_T)floor(u_tmp);
    }

    ind2 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind2 - 1];
    if (!(obj->pBuf[(int16_T)obj->pHeap[(int16_T)(temp_tmp + obj->pMidHeap) - 1]
          - 1] < obj->pBuf[(int16_T)tmp - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp_tmp = (real32_T)ceil(u_tmp);
      } else {
        temp_tmp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp_tmp + obj->pMidHeap;
      temp_tmp = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pHeap[(int16_T)ind2 - 1] = temp_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
      i *= 2.0F;
    }
  }
}

static void MedianFilterCG_trickleDownMi_j1(c_dsp_internal_MedianFilte_j1_T *obj,
  real32_T i)
{
  real32_T ind1;
  real32_T temp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i <= obj->pMinHeapLength)) {
    if ((i > 1.0F) && (i < obj->pMinHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i + 1.0F) + obj->pMidHeap) - 1] - 1] < obj->pBuf
         [(int16_T)obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1])) {
      i++;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp = (real32_T)ceil(u_tmp);
    } else {
      temp = (real32_T)floor(u_tmp);
    }

    ind1 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind1 - 1];
    if (!(obj->pBuf[(int16_T)tmp - 1] < obj->pBuf[(int16_T)obj->pHeap[(int16_T)
          (temp + obj->pMidHeap) - 1] - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp = (real32_T)ceil(u_tmp);
      } else {
        temp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp + obj->pMidHeap;
      obj->pHeap[(int16_T)ind1 - 1] = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind1 - 1] - 1] = ind1;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      i *= 2.0F;
    }
  }
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if (fabsf(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_enter_atomic_state11(const real32_T *Sum)
{
  if (*Sum > 0.0F) {
    cpu1_B.sat = 2.0;
  } else {
    cpu1_B.sat = -2.0;
  }

  if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0)) {
    cpu1_B.kp = 0.15;
  } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0))
  {
    cpu1_B.kp = 0.2;
  } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 0.0) && (cpu1_DW.f10 == 1.0))
  {
    cpu1_B.kp = 0.2;
  } else {
    cpu1_B.kp = 0.22;
  }

  cpu1_B.reset_f = 0.0;
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_enter_atomic_state10(const real32_T *Sum)
{
  if (*Sum > 0.0F) {
    cpu1_B.sat = 5.0;
  } else {
    cpu1_B.sat = -5.0;
  }

  if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0)) {
    cpu1_B.kp = 0.07;
  } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0))
  {
    cpu1_B.kp = 0.08;
  } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 0.0) && (cpu1_DW.f10 == 1.0))
  {
    cpu1_B.kp = 0.08;
  } else {
    cpu1_B.kp = 0.09;
  }

  cpu1_B.reset_f = 0.0;
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_enter_atomic_state8(const real32_T *Sum)
{
  if (*Sum > 0.0F) {
    cpu1_B.sat = 10.0;
  } else {
    cpu1_B.sat = -10.0;
  }

  if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0)) {
    cpu1_B.kp = 0.04;
  } else if ((cpu1_DW.f15 == 1.0) && (cpu1_DW.f20 == 0.0)) {
    cpu1_B.kp = 0.045;
  } else {
    cpu1_B.kp = 0.05;
  }

  cpu1_DW.f10 = 1.0;
  cpu1_B.reset_f = 0.0;
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_state9(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if ((tmp >= 10.0F) && (tmp < 15.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
    cpu1_enter_atomic_state8(Sum);
  } else if (tmp >= 20.0F) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
    cpu1_enter_atomic_state10(Sum);
  } else if (tmp < 0.04) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
    cpu1_enter_atomic_state11(Sum);
  } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((fabsf(*Sum) >= 0.04) && (tmp < 1.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  } else {
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    if (cpu1_DW.f20 == 1.0) {
      cpu1_B.kp = 0.03;
    } else {
      cpu1_B.kp = 0.04;
    }

    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_else(const real32_T *Sum)
{
  real32_T tmp;
  boolean_T guard1 = false;
  tmp = fabsf(*Sum);
  guard1 = false;
  if (!(tmp < 0.04)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.reset_f = 0.0;
    if (tmp >= 20.0F) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
      if (*Sum > 0.0F) {
        cpu1_B.sat = 20.0;
      } else {
        cpu1_B.sat = -20.0;
      }

      cpu1_B.kp = 0.025;
      cpu1_DW.f20 = 1.0;
    } else if ((tmp >= 10.0F) && (tmp < 15.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
      cpu1_enter_atomic_state8(Sum);
    } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
      if (*Sum > 0.0F) {
        cpu1_B.sat = 15.0;
      } else {
        cpu1_B.sat = -15.0;
      }

      cpu1_B.kp = 0.04;
      cpu1_DW.f15 = 1.0;
    } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
      cpu1_enter_atomic_state10(Sum);
    } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
      cpu1_enter_atomic_state11(Sum);
    } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
      if (*Sum > 0.0F) {
        cpu1_B.sat = 1.0;
      } else {
        cpu1_B.sat = -1.0;
      }

      cpu1_B.kp = 0.25;
    } else if ((fabsf(*Sum) >= 0.04) && (tmp < 1.0F)) {
      cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
      cpu1_B.sat = *Sum;
      cpu1_B.kp = 0.3;
      if (tmp <= 0.5F) {
        cpu1_B.ki = 0.18;
      } else {
        cpu1_B.ki = 0.12;
      }

      cpu1_B.reset_f = 1.0;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_init(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if (tmp >= 20.0F) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 10.0F) && (tmp < 15.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
    cpu1_enter_atomic_state8(Sum);
  } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    if (cpu1_DW.f20 == 1.0) {
      cpu1_B.kp = 0.03;
    } else {
      cpu1_B.kp = 0.04;
    }

    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
    cpu1_enter_atomic_state10(Sum);
  } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
    cpu1_enter_atomic_state11(Sum);
  } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 0.04) && (tmp < 1.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  } else {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.kp = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_B.kd_l = 0.0;
    cpu1_B.sat = 0.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_state10(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if ((tmp >= 10.0F) && (tmp < 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
    cpu1_enter_atomic_state8(Sum);
  } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    cpu1_B.kp = 0.04;
    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if (tmp >= 20.0F) {
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if (tmp < 0.04) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
    cpu1_enter_atomic_state11(Sum);
  } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((fabsf(*Sum) >= 0.04) && (tmp < 1.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  } else {
    if (*Sum > 0.0F) {
      cpu1_B.sat = 5.0;
    } else {
      cpu1_B.sat = -5.0;
    }

    if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0)) {
      cpu1_B.kp = 0.07;
    } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 ==
                1.0)) {
      cpu1_B.kp = 0.08;
    } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 0.0) && (cpu1_DW.f10 ==
                1.0)) {
      cpu1_B.kp = 0.08;
    } else {
      cpu1_B.kp = 0.09;
    }

    cpu1_B.reset_f = 0.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_state11(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if (tmp < 0.04) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
    cpu1_enter_atomic_state10(Sum);
  } else if ((tmp >= 10.0F) && (tmp < 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
    cpu1_enter_atomic_state8(Sum);
  } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    cpu1_B.kp = 0.04;
    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if (tmp >= 20.0F) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((fabsf(*Sum) >= 0.04) && (tmp < 1.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  } else {
    if (*Sum > 0.0F) {
      cpu1_B.sat = 2.0;
    } else {
      cpu1_B.sat = -2.0;
    }

    if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 == 1.0)) {
      cpu1_B.kp = 0.15;
    } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 1.0) && (cpu1_DW.f10 ==
                1.0)) {
      cpu1_B.kp = 0.2;
    } else if ((cpu1_DW.f20 == 0.0) && (cpu1_DW.f15 == 0.0) && (cpu1_DW.f10 ==
                1.0)) {
      cpu1_B.kp = 0.2;
    } else {
      cpu1_B.kp = 0.22;
    }

    cpu1_B.reset_f = 0.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_state13(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
    cpu1_enter_atomic_state11(Sum);
  } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
    cpu1_enter_atomic_state10(Sum);
  } else if ((tmp >= 10.0F) && (tmp < 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
    cpu1_enter_atomic_state8(Sum);
  } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    cpu1_B.kp = 0.04;
    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if (tmp >= 20.0F) {
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if (tmp < 0.04) {
    cpu1_B.ki = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  } else {
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  }
}

/* Function for Chart: '<Root>/Chart4' */
static void cpu1_state8(const real32_T *Sum)
{
  real32_T tmp;
  tmp = fabsf(*Sum);
  if (tmp >= 20.0F) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 20.0;
    } else {
      cpu1_B.sat = -20.0;
    }

    cpu1_B.kp = 0.025;
    cpu1_DW.f20 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp < 20.0F) && (tmp >= 15.0F)) {
    cpu1_DW.f20 = 0.0;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 15.0;
    } else {
      cpu1_B.sat = -15.0;
    }

    cpu1_B.kp = 0.04;
    cpu1_DW.f15 = 1.0;
    cpu1_B.reset_f = 0.0;
  } else if ((tmp >= 5.0F) && (tmp < 10.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
    cpu1_enter_atomic_state10(Sum);
  } else if (tmp < 0.04) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
    cpu1_B.kp = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.reset_f = 1.0;
  } else if ((tmp >= 2.0F) && (tmp < 5.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
    cpu1_enter_atomic_state11(Sum);
  } else if ((tmp >= 1.0F) && (tmp < 2.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
    if (*Sum > 0.0F) {
      cpu1_B.sat = 1.0;
    } else {
      cpu1_B.sat = -1.0;
    }

    cpu1_B.kp = 0.25;
    cpu1_B.reset_f = 0.0;
  } else if ((fabsf(*Sum) >= 0.04) && (tmp < 1.0F)) {
    cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
    cpu1_B.sat = *Sum;
    cpu1_B.kp = 0.3;
    if (tmp <= 0.5F) {
      cpu1_B.ki = 0.18;
    } else {
      cpu1_B.ki = 0.12;
    }

    cpu1_B.reset_f = 1.0;
  } else {
    if (*Sum > 0.0F) {
      cpu1_B.sat = 10.0;
    } else {
      cpu1_B.sat = -10.0;
    }

    if ((cpu1_DW.f20 == 1.0) && (cpu1_DW.f15 == 1.0)) {
      cpu1_B.kp = 0.04;
    } else if ((cpu1_DW.f15 == 1.0) && (cpu1_DW.f20 == 0.0)) {
      cpu1_B.kp = 0.045;
    } else {
      cpu1_B.kp = 0.05;
    }

    cpu1_DW.f10 = 1.0;
    cpu1_B.reset_f = 0.0;
  }
}

static void cpu1_MedianFilterCG_resetImpl_j(c_dsp_internal_MedianFilter_j_T *obj)
{
  real32_T cnt1;
  real32_T cnt2;
  int16_T i;
  for (i = 0; i < 28; i++) {
    obj->pBuf[i] = 0.0F;
    obj->pPos[i] = 0.0F;
    obj->pHeap[i] = 0.0F;
  }

  obj->pWinLen = 28.0F;
  obj->pIdx = obj->pWinLen;
  obj->pMidHeap = (real32_T)ceil((obj->pWinLen + 1.0F) / 2.0F);
  cnt1 = (obj->pWinLen - 1.0F) / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMinHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMinHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = obj->pWinLen / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMaxHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMaxHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = 1.0F;
  cnt2 = obj->pWinLen;
  for (i = 0; i < 28; i++) {
    if ((int16_T)(real32_T)fmod(28.0F - (real32_T)i, 2.0) == 0) {
      obj->pPos[27 - i] = cnt1;
      cnt1++;
    } else {
      obj->pPos[27 - i] = cnt2;
      cnt2--;
    }

    obj->pHeap[(int16_T)obj->pPos[27 - i] - 1] = 28.0F - (real32_T)i;
  }
}

static void MedianFilterCG_trickleDownMax_j(c_dsp_internal_MedianFilter_j_T *obj,
  real32_T i)
{
  real32_T ind2;
  real32_T temp_tmp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i >= -obj->pMaxHeapLength)) {
    if ((i < -1.0F) && (i > -obj->pMaxHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1] < obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i - 1.0F) + obj->pMidHeap) - 1] - 1])) {
      i--;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp_tmp = (real32_T)ceil(u_tmp);
    } else {
      temp_tmp = (real32_T)floor(u_tmp);
    }

    ind2 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind2 - 1];
    if (!(obj->pBuf[(int16_T)obj->pHeap[(int16_T)(temp_tmp + obj->pMidHeap) - 1]
          - 1] < obj->pBuf[(int16_T)tmp - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp_tmp = (real32_T)ceil(u_tmp);
      } else {
        temp_tmp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp_tmp + obj->pMidHeap;
      temp_tmp = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pHeap[(int16_T)ind2 - 1] = temp_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
      i *= 2.0F;
    }
  }
}

static void MedianFilterCG_trickleDownMin_j(c_dsp_internal_MedianFilter_j_T *obj,
  real32_T i)
{
  real32_T ind1;
  real32_T temp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i <= obj->pMinHeapLength)) {
    if ((i > 1.0F) && (i < obj->pMinHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i + 1.0F) + obj->pMidHeap) - 1] - 1] < obj->pBuf
         [(int16_T)obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1])) {
      i++;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp = (real32_T)ceil(u_tmp);
    } else {
      temp = (real32_T)floor(u_tmp);
    }

    ind1 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind1 - 1];
    if (!(obj->pBuf[(int16_T)tmp - 1] < obj->pBuf[(int16_T)obj->pHeap[(int16_T)
          (temp + obj->pMidHeap) - 1] - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp = (real32_T)ceil(u_tmp);
      } else {
        temp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp + obj->pMidHeap;
      obj->pHeap[(int16_T)ind1 - 1] = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind1 - 1] - 1] = ind1;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      i *= 2.0F;
    }
  }
}

static void cpu1_MedianFilterCG_resetImpl(c_dsp_internal_MedianFilterCG_T *obj)
{
  real32_T cnt2;
  obj->pBuf[0] = 0.0F;
  obj->pPos[0] = 0.0F;
  obj->pHeap[0] = 0.0F;
  obj->pBuf[1] = 0.0F;
  obj->pPos[1] = 0.0F;
  obj->pHeap[1] = 0.0F;
  obj->pBuf[2] = 0.0F;
  obj->pPos[2] = 0.0F;
  obj->pHeap[2] = 0.0F;
  obj->pWinLen = 3.0F;
  obj->pIdx = obj->pWinLen;
  obj->pMidHeap = (real32_T)ceil((obj->pWinLen + 1.0F) / 2.0F);
  cnt2 = (obj->pWinLen - 1.0F) / 2.0F;
  if (cnt2 < 0.0F) {
    obj->pMinHeapLength = (real32_T)ceil(cnt2);
  } else {
    obj->pMinHeapLength = (real32_T)floor(cnt2);
  }

  cnt2 = obj->pWinLen / 2.0F;
  if (cnt2 < 0.0F) {
    obj->pMaxHeapLength = (real32_T)ceil(cnt2);
  } else {
    obj->pMaxHeapLength = (real32_T)floor(cnt2);
  }

  cnt2 = obj->pWinLen;
  obj->pPos[2] = obj->pWinLen;
  obj->pHeap[(int16_T)obj->pPos[2] - 1] = 3.0F;
  obj->pPos[1] = 1.0F;
  obj->pHeap[(int16_T)obj->pPos[1] - 1] = 2.0F;
  obj->pPos[0] = cnt2 - 1.0F;
  obj->pHeap[(int16_T)obj->pPos[0] - 1] = 1.0F;
}

static void c_MedianFilterCG_trickleDownMax(c_dsp_internal_MedianFilterCG_T *obj,
  real32_T i)
{
  real32_T ind2;
  real32_T temp_tmp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i >= -obj->pMaxHeapLength)) {
    if ((i < -1.0F) && (i > -obj->pMaxHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1] < obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i - 1.0F) + obj->pMidHeap) - 1] - 1])) {
      i--;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp_tmp = (real32_T)ceil(u_tmp);
    } else {
      temp_tmp = (real32_T)floor(u_tmp);
    }

    ind2 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind2 - 1];
    if (!(obj->pBuf[(int16_T)obj->pHeap[(int16_T)(temp_tmp + obj->pMidHeap) - 1]
          - 1] < obj->pBuf[(int16_T)tmp - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp_tmp = (real32_T)ceil(u_tmp);
      } else {
        temp_tmp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp_tmp + obj->pMidHeap;
      temp_tmp = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pHeap[(int16_T)ind2 - 1] = temp_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
      i *= 2.0F;
    }
  }
}

static void c_MedianFilterCG_trickleDownMin(c_dsp_internal_MedianFilterCG_T *obj,
  real32_T i)
{
  real32_T ind1;
  real32_T temp;
  real32_T tmp;
  real32_T u_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i <= obj->pMinHeapLength)) {
    if ((i > 1.0F) && (i < obj->pMinHeapLength) && (obj->pBuf[(int16_T)
         obj->pHeap[(int16_T)((i + 1.0F) + obj->pMidHeap) - 1] - 1] < obj->pBuf
         [(int16_T)obj->pHeap[(int16_T)(i + obj->pMidHeap) - 1] - 1])) {
      i++;
    }

    u_tmp = i / 2.0F;
    if (u_tmp < 0.0F) {
      temp = (real32_T)ceil(u_tmp);
    } else {
      temp = (real32_T)floor(u_tmp);
    }

    ind1 = i + obj->pMidHeap;
    tmp = obj->pHeap[(int16_T)ind1 - 1];
    if (!(obj->pBuf[(int16_T)tmp - 1] < obj->pBuf[(int16_T)obj->pHeap[(int16_T)
          (temp + obj->pMidHeap) - 1] - 1])) {
      exitg1 = true;
    } else {
      if (u_tmp < 0.0F) {
        temp = (real32_T)ceil(u_tmp);
      } else {
        temp = (real32_T)floor(u_tmp);
      }

      u_tmp = temp + obj->pMidHeap;
      obj->pHeap[(int16_T)ind1 - 1] = obj->pHeap[(int16_T)u_tmp - 1];
      obj->pHeap[(int16_T)u_tmp - 1] = tmp;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)ind1 - 1] - 1] = ind1;
      obj->pPos[(int16_T)obj->pHeap[(int16_T)u_tmp - 1] - 1] = u_tmp;
      i *= 2.0F;
    }
  }
}

static void cpu1_SystemCore_setup(dsp_simulink_MovingAverage_cp_T *obj)
{
  obj->isSetupComplete = false;
  obj->isInitialized = 1L;
  obj->NumChannels = 1L;
  obj->FrameLength = 1L;
  obj->_pobj0.isInitialized = 0L;
  obj->_pobj0.isInitialized = 0L;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* Model step function for TID0 */
void cpu1_step0(void)                  /* Sample time: [0.001s, 0.0s] */
{
  c_dsp_internal_MedianFilte_j1_T *obj;
  c_dsp_internal_MedianFilter_j_T *obj_0;
  real_T rtb_NProdOut;
  real_T rtb_ki;
  real_T rtb_kp;
  int32_T rtb_TmpSignalConversionAtSFunct[9];
  int32_T e;
  real32_T distances[2];
  real32_T ind2;
  real32_T p;
  real32_T rtb_Gain;
  real32_T rtb_sat;
  real32_T rtb_y_e;
  real32_T temp;
  real32_T vprev;
  int16_T transition[2];
  int16_T i;
  int16_T tmp;
  boolean_T exitg1;
  boolean_T flag;
  boolean_T guard1 = false;

  {                                    /* Sample time: [0.001s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (c280xgpio_di): '<S7>/Digital Input1' */
  {
    cpu1_B.DigitalInput1[0] = GpioDataRegs.GPADAT.bit.GPIO5;
    cpu1_B.DigitalInput1[1] = GpioDataRegs.GPADAT.bit.GPIO6;
    cpu1_B.DigitalInput1[2] = GpioDataRegs.GPADAT.bit.GPIO7;
  }

  /* S-Function (c280xgpio_di): '<S7>/Digital Input4' */
  {
    cpu1_B.DigitalInput4[0] = GpioDataRegs.GPADAT.bit.GPIO8;
    cpu1_B.DigitalInput4[1] = GpioDataRegs.GPADAT.bit.GPIO9;
    cpu1_B.DigitalInput4[2] = GpioDataRegs.GPADAT.bit.GPIO10;
    cpu1_B.DigitalInput4[3] = GpioDataRegs.GPADAT.bit.GPIO11;
    cpu1_B.DigitalInput4[4] = GpioDataRegs.GPADAT.bit.GPIO14;
    cpu1_B.DigitalInput4[5] = GpioDataRegs.GPADAT.bit.GPIO15;
  }

  /* SignalConversion generated from: '<S108>/ SFunction ' incorporates:
   *  MATLAB Function: '<S7>/MATLAB Function1'
   */
  rtb_TmpSignalConversionAtSFunct[0] = cpu1_B.DigitalInput1[0];
  rtb_TmpSignalConversionAtSFunct[1] = cpu1_B.DigitalInput1[1];
  rtb_TmpSignalConversionAtSFunct[2] = cpu1_B.DigitalInput1[2];
  for (i = 0; i < 6; i++) {
    rtb_TmpSignalConversionAtSFunct[i + 3] = cpu1_B.DigitalInput4[i];
  }

  /* End of SignalConversion generated from: '<S108>/ SFunction ' */

  /* MATLAB Function: '<S7>/MATLAB Function1' */
  e = rtb_TmpSignalConversionAtSFunct[8];
  for (i = 7; i >= 0; i--) {
    e = (((int16_T)e & 1) ^ rtb_TmpSignalConversionAtSFunct[i]) | e << 1;
  }

  /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
   *  DataTypeConversion: '<S7>/Cast To Double3'
   *  MATLAB Function: '<S7>/MATLAB Function1'
   */
  rtb_y_e = (real32_T)e * 359.0F / 511.0F - 179.0F;

  /* S-Function (c2802xadc): '<S7>/ADC2' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1U;

    /* Wait for the period of Sampling window and EOC result to be latched after trigger */
#ifndef __TMS320C28XX_CLA__

    asm(" RPT #75|| NOP");

#endif

#ifdef __TMS320C28XX_CLA__

    float wait_index;
    for (wait_index= 12; wait_index > 0; wait_index--)
      __mnop();

#endif

    cpu1_B.ADC2 = (AdcaResultRegs.ADCRESULT0);
  }

  /* MATLABSystem: '<S7>/Median Filter' */
  obj = &cpu1_DW.obj_l.pMID;
  if (cpu1_DW.obj_l.pMID.isInitialized != 1L) {
    cpu1_DW.obj_l.pMID.isInitialized = 1L;
    cpu1_DW.obj_l.pMID.isSetupComplete = true;
    cpu_MedianFilterCG_resetImpl_j1(&cpu1_DW.obj_l.pMID);
  }

  vprev = cpu1_DW.obj_l.pMID.pBuf[(int16_T)cpu1_DW.obj_l.pMID.pIdx - 1];
  cpu1_DW.obj_l.pMID.pBuf[(int16_T)cpu1_DW.obj_l.pMID.pIdx - 1] = cpu1_B.ADC2;
  p = cpu1_DW.obj_l.pMID.pPos[(int16_T)cpu1_DW.obj_l.pMID.pIdx - 1];
  cpu1_DW.obj_l.pMID.pIdx++;
  if (cpu1_DW.obj_l.pMID.pWinLen + 1.0F == cpu1_DW.obj_l.pMID.pIdx) {
    cpu1_DW.obj_l.pMID.pIdx = 1.0F;
  }

  if (p > cpu1_DW.obj_l.pMID.pMidHeap) {
    if (vprev < cpu1_B.ADC2) {
      vprev = p - cpu1_DW.obj_l.pMID.pMidHeap;
      MedianFilterCG_trickleDownMi_j1(&cpu1_DW.obj_l.pMID, vprev * 2.0F);
    } else {
      vprev = p - cpu1_DW.obj_l.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev > 0.0F)) {
        flag = (obj->pBuf[(int16_T)obj->pHeap[(int16_T)(vprev + obj->pMidHeap) -
                1] - 1] < obj->pBuf[(int16_T)obj->pHeap[(int16_T)((real32_T)
                 floor(vprev / 2.0F) + obj->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          rtb_Gain = vprev + obj->pMidHeap;
          ind2 = (real32_T)floor(vprev / 2.0F) + obj->pMidHeap;
          temp = obj->pHeap[(int16_T)rtb_Gain - 1];
          obj->pHeap[(int16_T)rtb_Gain - 1] = obj->pHeap[(int16_T)ind2 - 1];
          obj->pHeap[(int16_T)ind2 - 1] = temp;
          obj->pPos[(int16_T)obj->pHeap[(int16_T)rtb_Gain - 1] - 1] = rtb_Gain;
          obj->pPos[(int16_T)obj->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          vprev = (real32_T)floor(vprev / 2.0F);
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMa_j1(&cpu1_DW.obj_l.pMID, -1.0F);
      }
    }
  } else if (p < cpu1_DW.obj_l.pMID.pMidHeap) {
    if (cpu1_B.ADC2 < vprev) {
      vprev = p - cpu1_DW.obj_l.pMID.pMidHeap;
      MedianFilterCG_trickleDownMa_j1(&cpu1_DW.obj_l.pMID, vprev * 2.0F);
    } else {
      vprev = p - cpu1_DW.obj_l.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev < 0.0F)) {
        p = vprev / 2.0F;
        if (p < 0.0F) {
          rtb_Gain = (real32_T)ceil(p);
        } else {
          rtb_Gain = -0.0F;
        }

        flag = (obj->pBuf[(int16_T)obj->pHeap[(int16_T)(rtb_Gain + obj->pMidHeap)
                - 1] - 1] < obj->pBuf[(int16_T)obj->pHeap[(int16_T)(vprev +
                 obj->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          if (p < 0.0F) {
            rtb_Gain = (real32_T)ceil(p);
          } else {
            rtb_Gain = -0.0F;
          }

          rtb_Gain += obj->pMidHeap;
          ind2 = vprev + obj->pMidHeap;
          temp = obj->pHeap[(int16_T)rtb_Gain - 1];
          obj->pHeap[(int16_T)rtb_Gain - 1] = obj->pHeap[(int16_T)ind2 - 1];
          obj->pHeap[(int16_T)ind2 - 1] = temp;
          obj->pPos[(int16_T)obj->pHeap[(int16_T)rtb_Gain - 1] - 1] = rtb_Gain;
          obj->pPos[(int16_T)obj->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          if (p < 0.0F) {
            vprev = (real32_T)ceil(p);
          } else {
            vprev = -0.0F;
          }
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMi_j1(&cpu1_DW.obj_l.pMID, 1.0F);
      }
    }
  } else {
    if (cpu1_DW.obj_l.pMID.pMaxHeapLength != 0.0F) {
      MedianFilterCG_trickleDownMa_j1(&cpu1_DW.obj_l.pMID, -1.0F);
    }

    if (cpu1_DW.obj_l.pMID.pMinHeapLength > 0.0F) {
      MedianFilterCG_trickleDownMi_j1(&cpu1_DW.obj_l.pMID, 1.0F);
    }
  }

  rtb_sat = cpu1_DW.obj_l.pMID.pBuf[(int16_T)cpu1_DW.obj_l.pMID.pHeap[(int16_T)
    cpu1_DW.obj_l.pMID.pMidHeap - 1] - 1];

  /* MATLAB Function: '<S7>/MATLAB Function2' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/Constant1'
   *  Constant: '<S7>/Constant2'
   *  MATLABSystem: '<S7>/Median Filter'
   */
  vprev = cpu1_P.Constant_Value_f + cpu1_P.Constant2_Value;
  if (rtb_sat < vprev - 2.0F * cpu1_P.Constant1_Value_g) {
    i = -2;
  } else {
    guard1 = false;
    if (rtb_sat < vprev - cpu1_P.Constant1_Value_g) {
      transition[0] = -2;
      transition[1] = -1;
      guard1 = true;
    } else if (rtb_sat < vprev) {
      transition[0] = -1;
      transition[1] = 0;
      guard1 = true;
    } else if (rtb_sat < vprev + cpu1_P.Constant1_Value_g) {
      transition[0] = 0;
      transition[1] = 1;
      guard1 = true;
    } else if (rtb_sat < 2.0F * cpu1_P.Constant1_Value_g + vprev) {
      transition[0] = 1;
      transition[1] = 2;
      guard1 = true;
    } else {
      i = 2;
    }

    if (guard1) {
      distances[0] = fabsf(((real32_T)transition[0] * cpu1_P.Constant1_Value_g +
                            vprev) - rtb_sat);
      distances[1] = fabsf(((real32_T)transition[1] * cpu1_P.Constant1_Value_g +
                            vprev) - rtb_sat);
      i = !(distances[0] <= distances[1]);
      if (distances[i] < 130.0F) {
        i = transition[i];
      } else if (rtb_y_e > 0.0F) {
        i = transition[0];
      } else {
        i = transition[1];
      }
    }
  }

  /* End of MATLAB Function: '<S7>/MATLAB Function2' */

  /* MATLAB Function: '<S7>/map_angle1' */
  if (i == -2) {
    rtb_y_e -= 720.0F;
  } else if (i == -1) {
    rtb_y_e -= 360.0F;
  } else if (i != 0) {
    if (i == 1) {
      rtb_y_e += 360.0F;
    } else {
      rtb_y_e += 720.0F;
    }
  }

  /* End of MATLAB Function: '<S7>/map_angle1' */

  /* DataTypeConversion: '<S2>/Cast To Single1' incorporates:
   *  Bias: '<S7>/Add Constant2'
   *  Gain: '<S2>/Gain8'
   *  MATLAB Function: '<S7>/Steering Ratio (polo)'
   *  Rounding: '<S2>/Round'
   */
  rtb_Gain = rt_roundf_snf((((rtb_y_e * rtb_y_e * -3.78193909E-6F + 0.0579F *
    rtb_y_e) + 0.1094F) + cpu1_P.AddConstant2_Bias) * cpu1_P.Gain8_Gain);
  if (rtIsNaNF(rtb_Gain) || rtIsInfF(rtb_Gain)) {
    rtb_Gain = 0.0F;
  } else {
    rtb_Gain = (real32_T)fmod(rtb_Gain, 4.294967296E+9);
  }

  /* Gain: '<S2>/Gain9' incorporates:
   *  DataTypeConversion: '<S2>/Cast To Single'
   *  DataTypeConversion: '<S2>/Cast To Single1'
   */
  cpu1_B.Gain9 = (real32_T)(rtb_Gain < 0.0F ? -(int32_T)(uint32_T)-rtb_Gain :
    (int32_T)(uint32_T)rtb_Gain) * cpu1_P.Gain9_Gain;

  /* S-Function (c28xipc_rx): '<Root>/IPC Receive' */
  MW_IPC_Receive(CHANNEL1, (uint32_t *)&cpu1_B.IPCReceive_o1,
                 &cpu1_B.IPCReceive_o2, 1, 8, 0, 0);

  /* S-Function (any2byte_svd): '<Root>/Byte Pack' */

  /* Pack: <Root>/Byte Pack */
  {
    uint32_T MW_outputPortOffset = 0;
    uint32_T MW_inputPortWidth = 0;
    uint32_T MW_remainder1 = 0;

    /* Packed output data type - uint16_T */
    /* Packing the values of Input 1 */
    /* Input data type - real32_T, size - 1 */
    {
      MW_inputPortWidth = 1 * sizeof(real32_T);
      memcpy((uint8_T*)&cpu1_B.BytePack[0] + MW_outputPortOffset, (uint8_T*)
             &cpu1_B.IPCReceive_o1, MW_inputPortWidth);
    }

    /* Offset calculations based on alignemnt for packing next input */
    MW_remainder1 = MW_inputPortWidth % 2;
    if (MW_remainder1 == 0) {
      MW_outputPortOffset = MW_outputPortOffset + MW_inputPortWidth;
    } else {
      MW_outputPortOffset = MW_outputPortOffset + MW_inputPortWidth + (2 -
        MW_remainder1);
    }

    /* Packing the values of Input 2 */
    /* Input data type - real32_T, size - 1 */
    {
      MW_inputPortWidth = 1 * sizeof(real32_T);
      memcpy((uint8_T*)&cpu1_B.BytePack[0] + MW_outputPortOffset, (uint8_T*)
             &cpu1_B.Gain9, MW_inputPortWidth);
    }
  }

  /* S-Function (c280xcanxmt): '<Root>/eCAN Transmit' */
  {
      if(READ_SWITCH()){
          counter++;
          uint8_t ucTXMsgData[8];

          if(counter%transmit_rate==0){
              ucTXMsgData[0] = (cpu1_B.BytePack[0] & 0xFF);
              ucTXMsgData[1] = (cpu1_B.BytePack[0] >> 8);
              ucTXMsgData[2] = (cpu1_B.BytePack[1] & 0xFF);
              ucTXMsgData[3] = (cpu1_B.BytePack[1] >> 8);
              ucTXMsgData[4] = (cpu1_B.BytePack[2] & 0xFF);
              ucTXMsgData[5] = (cpu1_B.BytePack[2] >> 8);
              ucTXMsgData[6] = (cpu1_B.BytePack[3] & 0xFF);
              ucTXMsgData[7] = (cpu1_B.BytePack[3] >> 8);

              CAN_sendMessage(CANB_BASE, 2, 8,(uint16_t *)ucTXMsgData);
          }
       }


      else if(!READ_SWITCH()){

          if (checkSCITransmitInprogress != 1) {
              checkSCITransmitInprogress = 1;
             // int16_T errFlgHeader = NOERROR;
              int16_T errFlgData = NOERROR;
             // int16_T errFlgTail = NOERROR;
              errFlgData = scia_xmit((unsigned char*)&cpu1_B.BytePack[0], 8, 2);
              checkSCITransmitInprogress = 0;
          }
      }
  }

  /* RateTransition: '<Root>/RT' */
  if (cpu1_M->Timing.RateInteraction.TID0_1) {
    /* RateTransition: '<Root>/RT' */
    cpu1_B.RT_l = cpu1_DW.RT_Buffer0;
  }

  /* End of RateTransition: '<Root>/RT' */

  /* Sum: '<Root>/Sum' */
  vprev = cpu1_B.RT_l - cpu1_B.Gain9;

  /* Chart: '<Root>/ready' */
  if (cpu1_DW.is_active_c16_cpu1 == 0U) {
    cpu1_DW.is_active_c16_cpu1 = 1U;
    cpu1_DW.is_c16_cpu1 = cpu1_IN_init_j;
    rtb_kp = 0.0;
    rtb_ki = 0.0;
    cpu1_B.kd = 0.0;
    rtb_sat = 0.0F;
  } else {
    switch (cpu1_DW.is_c16_cpu1) {
     case cpu1_IN_else:
      rtb_Gain = fabsf(vprev);
      if (rtb_Gain > 5.0F) {
        if (rtb_Gain > 10.0F) {
          cpu1_DW.is_c16_cpu1 = cpu1_IN_higherthan15;
          rtb_ki = 0.0;
          cpu1_B.reset = 0.0;
          if (vprev > 0.0F) {
            rtb_sat = 10.0F;
          } else {
            rtb_sat = -10.0F;
          }

          rtb_kp = 0.035;
          cpu1_B.kd = 0.0032;
        } else {
          cpu1_DW.is_c16_cpu1 = cpu1_IN_lowerthan15;
          rtb_sat = vprev;
          rtb_kp = 0.035;
          cpu1_B.kd = 0.0032;
          rtb_ki = 0.1;
          cpu1_B.reset = 1.0;
        }
      } else {
        rtb_sat = 0.0F;
        cpu1_B.reset = 1.0;
        rtb_kp = 0.0;
        rtb_ki = 0.0;
      }
      break;

     case cpu1_IN_higherthan15:
      rtb_Gain = fabsf(vprev);
      if ((rtb_Gain <= 10.0F) && (rtb_Gain > 1.0F)) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_lowerthan15;
        rtb_sat = vprev;
        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
        rtb_ki = 0.1;
        cpu1_B.reset = 1.0;
      } else if (rtb_Gain <= 5.0F) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_else;
        rtb_sat = 0.0F;
        cpu1_B.reset = 1.0;
        rtb_kp = 0.0;
        rtb_ki = 0.0;
      } else {
        rtb_ki = 0.0;
        cpu1_B.reset = 0.0;
        if (vprev > 0.0F) {
          rtb_sat = 10.0F;
        } else {
          rtb_sat = -10.0F;
        }

        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
      }
      break;

     case cpu1_IN_init_j:
      rtb_Gain = fabsf(vprev);
      if (rtb_Gain > 10.0F) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_higherthan15;
        rtb_ki = 0.0;
        cpu1_B.reset = 0.0;
        if (vprev > 0.0F) {
          rtb_sat = 10.0F;
        } else {
          rtb_sat = -10.0F;
        }

        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
      } else if ((rtb_Gain <= 10.0F) && (rtb_Gain > 1.0F)) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_lowerthan15;
        rtb_sat = vprev;
        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
        rtb_ki = 0.1;
        cpu1_B.reset = 1.0;
      } else if (rtb_Gain <= 5.0F) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_else;
        rtb_sat = 0.0F;
        cpu1_B.reset = 1.0;
        rtb_kp = 0.0;
        rtb_ki = 0.0;
      } else {
        rtb_kp = 0.0;
        rtb_ki = 0.0;
        cpu1_B.kd = 0.0;
        rtb_sat = 0.0F;
      }
      break;

     default:
      /* case IN_lowerthan15: */
      rtb_Gain = fabsf(vprev);
      if (rtb_Gain > 10.0F) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_higherthan15;
        rtb_ki = 0.0;
        cpu1_B.reset = 0.0;
        if (vprev > 0.0F) {
          rtb_sat = 10.0F;
        } else {
          rtb_sat = -10.0F;
        }

        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
      } else if (rtb_Gain <= 5.0F) {
        cpu1_DW.is_c16_cpu1 = cpu1_IN_else;
        rtb_sat = 0.0F;
        cpu1_B.reset = 1.0;
        rtb_kp = 0.0;
        rtb_ki = 0.0;
      } else {
        rtb_sat = vprev;
        rtb_kp = 0.035;
        cpu1_B.kd = 0.0032;
        rtb_ki = 0.1;
        cpu1_B.reset = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/ready' */

  /* DiscreteIntegrator: '<S42>/Integrator' */
  if ((cpu1_B.reset <= 0.0) && (cpu1_DW.Integrator_PrevResetState == 1)) {
    cpu1_DW.Integrator_DSTATE = cpu1_P.PIDController1_InitialConditi_j;
  }

  /* DiscreteIntegrator: '<S37>/Filter' */
  if ((cpu1_B.reset <= 0.0) && (cpu1_DW.Filter_PrevResetState == 1)) {
    cpu1_DW.Filter_DSTATE = cpu1_P.PIDController1_InitialCondition;
  }

  /* Product: '<S45>/NProd Out' incorporates:
   *  Constant: '<Root>/Constant'
   *  DiscreteIntegrator: '<S37>/Filter'
   *  Product: '<S36>/DProd Out'
   *  Sum: '<S37>/SumD'
   */
  rtb_NProdOut = ((real32_T)(rtb_sat * cpu1_B.kd) - cpu1_DW.Filter_DSTATE) *
    cpu1_P.Constant_Value;

  /* Sum: '<S51>/Sum' incorporates:
   *  DiscreteIntegrator: '<S42>/Integrator'
   *  Product: '<S47>/PProd Out'
   */
  rtb_y_e = (real32_T)(((real_T)(real32_T)(rtb_sat * rtb_kp) +
                        cpu1_DW.Integrator_DSTATE) + rtb_NProdOut);

  /* Chart: '<Root>/Chart4' */
  if (cpu1_DW.is_active_c18_cpu1 == 0U) {
    cpu1_DW.is_active_c18_cpu1 = 1U;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_init;
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.kp = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_B.kd_l = 0.0;
    cpu1_B.sat = 0.0;
  } else {
    switch (cpu1_DW.is_c18_cpu1) {
     case cpu1_IN_else:
      cpu1_else(&vprev);
      break;

     case cpu1_IN_init:
      cpu1_init(&vprev);
      break;

     case cpu1_IN_state1:
      rtb_Gain = fabsf(vprev);
      if ((rtb_Gain < 20.0F) && (rtb_Gain >= 15.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
        if (vprev > 0.0F) {
          cpu1_B.sat = 15.0;
        } else {
          cpu1_B.sat = -15.0;
        }

        if (cpu1_DW.f20 == 1.0) {
          cpu1_B.kp = 0.03;
        } else {
          cpu1_B.kp = 0.04;
        }

        cpu1_DW.f15 = 1.0;
        cpu1_B.reset_f = 0.0;
      } else if ((rtb_Gain >= 10.0F) && (rtb_Gain < 15.0F)) {
        cpu1_DW.f20 = 0.0;
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
        cpu1_enter_atomic_state8(&vprev);
      } else if ((rtb_Gain >= 5.0F) && (rtb_Gain < 10.0F)) {
        cpu1_DW.f20 = 0.0;
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
        cpu1_enter_atomic_state10(&vprev);
      } else if (rtb_Gain < 0.04) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
        cpu1_B.kp = 0.0;
        cpu1_B.sat = 0.0;
        cpu1_B.reset_f = 1.0;
      } else if ((rtb_Gain >= 2.0F) && (rtb_Gain < 5.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
        cpu1_enter_atomic_state11(&vprev);
      } else if ((rtb_Gain >= 1.0F) && (rtb_Gain < 2.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state12;
        if (vprev > 0.0F) {
          cpu1_B.sat = 1.0;
        } else {
          cpu1_B.sat = -1.0;
        }

        cpu1_B.kp = 0.25;
        cpu1_B.reset_f = 0.0;
      } else {
        if (vprev > 0.0F) {
          cpu1_B.sat = 20.0;
        } else {
          cpu1_B.sat = -20.0;
        }

        cpu1_B.kp = 0.025;
        cpu1_DW.f20 = 1.0;
        cpu1_B.reset_f = 0.0;
      }
      break;

     case cpu1_IN_state10:
      cpu1_state10(&vprev);
      break;

     case cpu1_IN_state11:
      cpu1_state11(&vprev);
      break;

     case cpu1_IN_state12:
      p = fabsf(vprev);
      if ((p >= 2.0F) && (p < 5.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state11;
        cpu1_enter_atomic_state11(&vprev);
      } else if ((p >= 5.0F) && (p < 10.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state10;
        cpu1_enter_atomic_state10(&vprev);
      } else if ((p >= 10.0F) && (p < 15.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state8;
        cpu1_enter_atomic_state8(&vprev);
      } else if ((p < 20.0F) && (p >= 15.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state9;
        if (vprev > 0.0F) {
          cpu1_B.sat = 15.0;
        } else {
          cpu1_B.sat = -15.0;
        }

        if (cpu1_DW.f20 == 1.0) {
          cpu1_B.kp = 0.03;
        } else {
          cpu1_B.kp = 0.04;
        }

        cpu1_DW.f15 = 1.0;
        cpu1_B.reset_f = 0.0;
      } else if (p >= 20.0F) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state1;
        if (vprev > 0.0F) {
          cpu1_B.sat = 20.0;
        } else {
          cpu1_B.sat = -20.0;
        }

        cpu1_B.kp = 0.025;
        cpu1_DW.f20 = 1.0;
        cpu1_B.reset_f = 0.0;
      } else if (p < 0.04) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_else;
        cpu1_B.kp = 0.0;
        cpu1_B.sat = 0.0;
        cpu1_B.reset_f = 1.0;
      } else if ((p >= 0.04) && (p < 1.0F)) {
        cpu1_DW.is_c18_cpu1 = cpu1_IN_state13;
        cpu1_B.sat = vprev;
        cpu1_B.kp = 0.3;
        if (fabsf(vprev) <= 0.5F) {
          cpu1_B.ki = 0.18;
        } else {
          cpu1_B.ki = 0.12;
        }

        cpu1_B.reset_f = 1.0;
      } else {
        if (vprev > 0.0F) {
          cpu1_B.sat = 1.0;
        } else {
          cpu1_B.sat = -1.0;
        }

        cpu1_B.kp = 0.25;
        cpu1_B.reset_f = 0.0;
      }
      break;

     case cpu1_IN_state13:
      cpu1_state13(&vprev);
      break;

     case cpu1_IN_state8:
      cpu1_state8(&vprev);
      break;

     default:
      /* case IN_state9: */
      cpu1_state9(&vprev);
      break;
    }
  }

  /* End of Chart: '<Root>/Chart4' */

  /* DiscreteIntegrator: '<S90>/Integrator' */
  if ((cpu1_B.reset_f <= 0.0) && (cpu1_DW.Integrator_PrevResetState_e == 1)) {
    cpu1_DW.Integrator_DSTATE_j = cpu1_P.PIDController2_InitialConditi_o;
  }

  /* DiscreteIntegrator: '<S85>/Filter' */
  if ((cpu1_B.reset_f <= 0.0) && (cpu1_DW.Filter_PrevResetState_d == 1)) {
    cpu1_DW.Filter_DSTATE_o = cpu1_P.PIDController2_InitialCondition;
  }

  /* Product: '<S93>/NProd Out' incorporates:
   *  Constant: '<Root>/Constant1'
   *  DiscreteIntegrator: '<S85>/Filter'
   *  Product: '<S84>/DProd Out'
   *  Sum: '<S85>/SumD'
   */
  rtb_kp = ((real32_T)(cpu1_B.sat * cpu1_B.kd_l) - cpu1_DW.Filter_DSTATE_o) *
    cpu1_P.Constant1_Value;

  /* Switch: '<Root>/Switch' incorporates:
   *  Abs: '<Root>/Abs'
   */
  if (fabsf(vprev) > cpu1_P.Switch_Threshold) {
    /* Saturate: '<S49>/Saturation' */
    if (rtb_y_e > cpu1_P.PIDController1_UpperSaturationL) {
      vprev = cpu1_P.PIDController1_UpperSaturationL;
    } else if (rtb_y_e < cpu1_P.PIDController1_LowerSaturationL) {
      vprev = cpu1_P.PIDController1_LowerSaturationL;
    } else {
      vprev = rtb_y_e;
    }

    /* End of Saturate: '<S49>/Saturation' */
  } else {
    /* Sum: '<S99>/Sum' incorporates:
     *  DiscreteIntegrator: '<S90>/Integrator'
     *  Product: '<S95>/PProd Out'
     */
    vprev = (real32_T)(((real_T)(real32_T)(cpu1_B.sat * cpu1_B.kp) +
                        cpu1_DW.Integrator_DSTATE_j) + rtb_kp);

    /* Saturate: '<S97>/Saturation' */
    if (vprev > cpu1_P.PIDController2_UpperSaturationL) {
      vprev = cpu1_P.PIDController2_UpperSaturationL;
    } else if (vprev < cpu1_P.PIDController2_LowerSaturationL) {
      vprev = cpu1_P.PIDController2_LowerSaturationL;
    }

    /* End of Saturate: '<S97>/Saturation' */
  }

  /* Gain: '<Root>/Gain' incorporates:
   *  Switch: '<Root>/Switch'
   */
  rtb_Gain = cpu1_P.Gain_Gain * vprev;

  /* MATLABSystem: '<Root>/Median Filter1' */
  obj_0 = &cpu1_DW.obj.pMID;
  if (cpu1_DW.obj.pMID.isInitialized != 1L) {
    cpu1_DW.obj.pMID.isInitialized = 1L;
    cpu1_DW.obj.pMID.isSetupComplete = true;
    cpu1_MedianFilterCG_resetImpl_j(&cpu1_DW.obj.pMID);
  }

  vprev = cpu1_DW.obj.pMID.pBuf[(int16_T)cpu1_DW.obj.pMID.pIdx - 1];
  cpu1_DW.obj.pMID.pBuf[(int16_T)cpu1_DW.obj.pMID.pIdx - 1] = rtb_Gain;
  p = cpu1_DW.obj.pMID.pPos[(int16_T)cpu1_DW.obj.pMID.pIdx - 1];
  cpu1_DW.obj.pMID.pIdx++;
  if (cpu1_DW.obj.pMID.pWinLen + 1.0F == cpu1_DW.obj.pMID.pIdx) {
    cpu1_DW.obj.pMID.pIdx = 1.0F;
  }

  if (p > cpu1_DW.obj.pMID.pMidHeap) {
    if (vprev < rtb_Gain) {
      vprev = p - cpu1_DW.obj.pMID.pMidHeap;
      MedianFilterCG_trickleDownMin_j(&cpu1_DW.obj.pMID, vprev * 2.0F);
    } else {
      vprev = p - cpu1_DW.obj.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev > 0.0F)) {
        flag = (obj_0->pBuf[(int16_T)obj_0->pHeap[(int16_T)(vprev +
                 obj_0->pMidHeap) - 1] - 1] < obj_0->pBuf[(int16_T)obj_0->pHeap
                [(int16_T)((real32_T)floor(vprev / 2.0F) + obj_0->pMidHeap) - 1]
                - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          rtb_Gain = vprev + obj_0->pMidHeap;
          ind2 = (real32_T)floor(vprev / 2.0F) + obj_0->pMidHeap;
          temp = obj_0->pHeap[(int16_T)rtb_Gain - 1];
          obj_0->pHeap[(int16_T)rtb_Gain - 1] = obj_0->pHeap[(int16_T)ind2 - 1];
          obj_0->pHeap[(int16_T)ind2 - 1] = temp;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)rtb_Gain - 1] - 1] =
            rtb_Gain;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          vprev = (real32_T)floor(vprev / 2.0F);
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMax_j(&cpu1_DW.obj.pMID, -1.0F);
      }
    }
  } else if (p < cpu1_DW.obj.pMID.pMidHeap) {
    if (rtb_Gain < vprev) {
      vprev = p - cpu1_DW.obj.pMID.pMidHeap;
      MedianFilterCG_trickleDownMax_j(&cpu1_DW.obj.pMID, vprev * 2.0F);
    } else {
      vprev = p - cpu1_DW.obj.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev < 0.0F)) {
        p = vprev / 2.0F;
        if (p < 0.0F) {
          rtb_Gain = (real32_T)ceil(p);
        } else {
          rtb_Gain = -0.0F;
        }

        flag = (obj_0->pBuf[(int16_T)obj_0->pHeap[(int16_T)(rtb_Gain +
                 obj_0->pMidHeap) - 1] - 1] < obj_0->pBuf[(int16_T)obj_0->pHeap
                [(int16_T)(vprev + obj_0->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          if (p < 0.0F) {
            rtb_Gain = (real32_T)ceil(p);
          } else {
            rtb_Gain = -0.0F;
          }

          rtb_Gain += obj_0->pMidHeap;
          ind2 = vprev + obj_0->pMidHeap;
          temp = obj_0->pHeap[(int16_T)rtb_Gain - 1];
          obj_0->pHeap[(int16_T)rtb_Gain - 1] = obj_0->pHeap[(int16_T)ind2 - 1];
          obj_0->pHeap[(int16_T)ind2 - 1] = temp;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)rtb_Gain - 1] - 1] =
            rtb_Gain;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          if (p < 0.0F) {
            vprev = (real32_T)ceil(p);
          } else {
            vprev = -0.0F;
          }
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMin_j(&cpu1_DW.obj.pMID, 1.0F);
      }
    }
  } else {
    if (cpu1_DW.obj.pMID.pMaxHeapLength != 0.0F) {
      MedianFilterCG_trickleDownMax_j(&cpu1_DW.obj.pMID, -1.0F);
    }

    if (cpu1_DW.obj.pMID.pMinHeapLength > 0.0F) {
      MedianFilterCG_trickleDownMin_j(&cpu1_DW.obj.pMID, 1.0F);
    }
  }

  rtb_Gain = cpu1_DW.obj.pMID.pBuf[(int16_T)cpu1_DW.obj.pMID.pHeap[(int16_T)
    cpu1_DW.obj.pMID.pMidHeap - 1] - 1];
  vprev = cpu1_DW.obj.pMID.pBuf[(int16_T)cpu1_DW.obj.pMID.pHeap[(int16_T)
    (cpu1_DW.obj.pMID.pMidHeap - 1.0F) - 1] - 1] + rtb_Gain;
  vprev /= 2.0F;

  /* End of MATLABSystem: '<Root>/Median Filter1' */

  /* MATLABSystem: '<Root>/DAC' incorporates:
   *  Bias: '<Root>/Add Constant1'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   */
  MW_C2000DACSat(0U, cpu1_P.Gain2_Gain * (cpu1_P.Gain1_Gain * vprev +
    cpu1_P.AddConstant1_Bias));

  /* MATLABSystem: '<Root>/DAC2' incorporates:
   *  Bias: '<Root>/Add Constant'
   *  Gain: '<Root>/Gain5'
   */
  MW_C2000DACSat(1U, cpu1_P.Gain5_Gain * (vprev + cpu1_P.AddConstant_Bias));

  /* DeadZone: '<S35>/DeadZone' */
  if (rtb_y_e > cpu1_P.PIDController1_UpperSaturationL) {
    rtb_y_e -= cpu1_P.PIDController1_UpperSaturationL;
  } else if (rtb_y_e >= cpu1_P.PIDController1_LowerSaturationL) {
    rtb_y_e = 0.0F;
  } else {
    rtb_y_e -= cpu1_P.PIDController1_LowerSaturationL;
  }

  /* End of DeadZone: '<S35>/DeadZone' */

  /* Product: '<S39>/IProd Out' */
  rtb_sat = (real32_T)(rtb_sat * rtb_ki);

  /* Update for Delay: '<Root>/Delay' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  for (i = 0; i < 99; i++) {
    cpu1_DW.Delay_DSTATE[i] = cpu1_DW.Delay_DSTATE[i + 1];
  }

  cpu1_DW.Delay_DSTATE[99] = cpu1_P.Constant5_Value;

  /* End of Update for Delay: '<Root>/Delay' */

  /* Switch: '<S33>/Switch1' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S33>/Constant2'
   *  RelationalOperator: '<S33>/fix for DT propagation issue'
   */
  if (rtb_y_e > cpu1_P.Clamping_zero_Value) {
    i = cpu1_P.Constant_Value_l;
  } else {
    i = cpu1_P.Constant2_Value_g;
  }

  /* Switch: '<S33>/Switch2' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant3'
   *  Constant: '<S33>/Constant4'
   *  RelationalOperator: '<S33>/fix for DT propagation issue1'
   */
  if (rtb_sat > cpu1_P.Clamping_zero_Value) {
    tmp = cpu1_P.Constant3_Value_h;
  } else {
    tmp = cpu1_P.Constant4_Value;
  }

  /* Switch: '<S33>/Switch' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant1'
   *  Logic: '<S33>/AND3'
   *  RelationalOperator: '<S33>/Equal1'
   *  RelationalOperator: '<S33>/Relational Operator'
   *  Switch: '<S33>/Switch1'
   *  Switch: '<S33>/Switch2'
   */
  if ((cpu1_P.Clamping_zero_Value != rtb_y_e) && (i == tmp)) {
    rtb_sat = cpu1_P.Constant1_Value_b;
  }

  /* Update for DiscreteIntegrator: '<S42>/Integrator' incorporates:
   *  Switch: '<S33>/Switch'
   */
  cpu1_DW.Integrator_DSTATE += cpu1_P.Integrator_gainval * rtb_sat;
  if (cpu1_B.reset > 0.0) {
    cpu1_DW.Integrator_PrevResetState = 1;
  } else if (cpu1_B.reset < 0.0) {
    cpu1_DW.Integrator_PrevResetState = -1;
  } else if (cpu1_B.reset == 0.0) {
    cpu1_DW.Integrator_PrevResetState = 0;
  } else {
    cpu1_DW.Integrator_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S42>/Integrator' */

  /* Update for DiscreteIntegrator: '<S37>/Filter' */
  cpu1_DW.Filter_DSTATE += cpu1_P.Filter_gainval * rtb_NProdOut;
  if (cpu1_B.reset > 0.0) {
    cpu1_DW.Filter_PrevResetState = 1;
  } else if (cpu1_B.reset < 0.0) {
    cpu1_DW.Filter_PrevResetState = -1;
  } else if (cpu1_B.reset == 0.0) {
    cpu1_DW.Filter_PrevResetState = 0;
  } else {
    cpu1_DW.Filter_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S37>/Filter' */

  /* Update for DiscreteIntegrator: '<S90>/Integrator' incorporates:
   *  Product: '<S87>/IProd Out'
   */
  cpu1_DW.Integrator_DSTATE_j += (real32_T)(cpu1_B.sat * cpu1_B.ki) *
    cpu1_P.Integrator_gainval_k;
  if (cpu1_B.reset_f > 0.0) {
    cpu1_DW.Integrator_PrevResetState_e = 1;
  } else if (cpu1_B.reset_f < 0.0) {
    cpu1_DW.Integrator_PrevResetState_e = -1;
  } else if (cpu1_B.reset_f == 0.0) {
    cpu1_DW.Integrator_PrevResetState_e = 0;
  } else {
    cpu1_DW.Integrator_PrevResetState_e = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S90>/Integrator' */

  /* Update for DiscreteIntegrator: '<S85>/Filter' */
  cpu1_DW.Filter_DSTATE_o += cpu1_P.Filter_gainval_l * rtb_kp;
  if (cpu1_B.reset_f > 0.0) {
    cpu1_DW.Filter_PrevResetState_d = 1;
  } else if (cpu1_B.reset_f < 0.0) {
    cpu1_DW.Filter_PrevResetState_d = -1;
  } else if (cpu1_B.reset_f == 0.0) {
    cpu1_DW.Filter_PrevResetState_d = 0;
  } else {
    cpu1_DW.Filter_PrevResetState_d = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S85>/Filter' */
}

/* Model step function for TID1 */
void cpu1_step1(void)                  /* Sample time: [0.1s, 0.0s] */
{
  c_dsp_internal_MedianFilterCG_T *obj_0;
  g_dsp_internal_SlidingWindowA_T *obj;
  real32_T csum;
  real32_T csumrev;
  real32_T ind2;
  real32_T modValueRev;
  real32_T temp;
  boolean_T exitg1;
  boolean_T flag;


  /* S-Function (c28xsci_rx): '<Root>/SCI Receive' */
  {

    if(READ_SWITCH()){
    /* Receiving data: For uint32 and uint16, rcvBuff will contain uint16 data */

        if(((HWREGH(CANB_BASE + CAN_O_ES) & CAN_ES_RXOK)) == CAN_ES_RXOK)
        {
             //get data as uint16 in recBuff
             uint8_t recbuff[8];
             uint8_t ratebuff[4];

             int16_T i;
             for (i = 0; i < 8; i++) {
                  recbuff[i] = 0;
                  ratebuff[i]=0;

             }

             CAN_readMessage(CANB_BASE, RX_MSG_OBJ1_ID, (uint16_T*)recbuff);

             CAN_readMessage(CANB_BASE, RX_MSG_OBJ2_ID, (uint16_T*)ratebuff);


             cpu1_B.SCIReceive[0] = (union type_uni) ((((uint32_t)recbuff[0])) | (((uint32_t)recbuff[1]) << 8) |
                     (((uint32_t)recbuff[2]) << 16) | (((uint32_t)recbuff[3]) << 24));

             cpu1_B.SCIReceive[1] = (union type_uni) ((((uint32_t)recbuff[4])) | (((uint32_t)recbuff[5]) << 8) |
                     (((uint32_t)recbuff[6]) << 16) | (((uint32_t)recbuff[7]) << 24));

             transmit_rate =  ((((uint32_t)ratebuff[0])) | (((uint32_t)ratebuff[1]) << 8) |
                              (((uint32_t)ratebuff[2]) << 16) | (((uint32_t)ratebuff[3]) << 24));

         }

    }
    else if(!READ_SWITCH()){
        int16_T i;
        int16_T errFlg = NOERROR;
        uint16_T isHeadReceived = 1U;

        //get data as uint16 in recBuff
        uint16_T recbuff[4];
        for (i = 0; i < 4; i++) {
            recbuff[i] = 0U;
        }

        errFlg = NOERROR;

        /* Receiving data: For uint32 and uint16, rcvBuff will contain uint16 data */
        if (isHeadReceived) {
            errFlg = scia_rcv(recbuff, 8, 4);
            asm(" NOP");
            if ((errFlg == NOERROR) || (errFlg == PARTIALDATA)) {
                memcpy( &cpu1_B.SCIReceive[0], recbuff,4);


            }
        }
    }

  }


  /* MATLABSystem: '<Root>/Moving Average' */
  if (cpu1_DW.obj_g.TunablePropsChanged) {
    cpu1_DW.obj_g.TunablePropsChanged = false;
  }

  obj = cpu1_DW.obj_g.pStatistic;
  if (obj->isInitialized != 1L) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1L;
    obj->pCumSum = 0.0F;
    obj->pCumSumRev = 0.0F;
    obj->pCumRevIndex = 1.0F;
    obj->pModValueRev = 0.0F;
    obj->isSetupComplete = true;
    obj->pCumSum = 0.0F;
    obj->pCumSumRev = 0.0F;
    obj->pCumRevIndex = 1.0F;
    obj->pModValueRev = 0.0F;
  }

  csum = obj->pCumSum;
  csumrev = obj->pCumSumRev;
  modValueRev = obj->pModValueRev;

  /* MATLABSystem: '<Root>/Moving Average' */
  cpu1_B.MovingAverage = 0.0F;

  /* MATLABSystem: '<Root>/Moving Average' */
  csum += cpu1_B.SCIReceive[0].f;
  if (modValueRev == 0.0F) {
    /* MATLABSystem: '<Root>/Moving Average' */
    cpu1_B.MovingAverage = (csum + csumrev) / 2.0F;
  }

  obj->pCumSum = 0.0F;
  obj->pCumSumRev = cpu1_B.SCIReceive[0].f;
  obj->pCumRevIndex = 1.0F;
  if (modValueRev > 0.0F) {
    obj->pModValueRev = modValueRev - 1.0F;
  } else {
    obj->pModValueRev = 0.0F;
  }

  /* S-Function (c28xipc_tx): '<Root>/IPC Transmit' */
  MW_IPC_Transmit(CHANNEL0, (uint32_t *)&cpu1_B.MovingAverage, 1, 8, 0, 0);

  /* MATLABSystem: '<Root>/Median Filter' */
  obj_0 = &cpu1_DW.obj_h.pMID;
  if (cpu1_DW.obj_h.pMID.isInitialized != 1L) {
    cpu1_DW.obj_h.pMID.isInitialized = 1L;
    cpu1_DW.obj_h.pMID.isSetupComplete = true;
    cpu1_MedianFilterCG_resetImpl(&cpu1_DW.obj_h.pMID);
  }

  csum = cpu1_DW.obj_h.pMID.pBuf[(int16_T)cpu1_DW.obj_h.pMID.pIdx - 1];
  cpu1_DW.obj_h.pMID.pBuf[(int16_T)cpu1_DW.obj_h.pMID.pIdx - 1] =
    cpu1_B.SCIReceive[1].f;
  csumrev = cpu1_DW.obj_h.pMID.pPos[(int16_T)cpu1_DW.obj_h.pMID.pIdx - 1];
  cpu1_DW.obj_h.pMID.pIdx++;
  if (cpu1_DW.obj_h.pMID.pWinLen + 1.0F == cpu1_DW.obj_h.pMID.pIdx) {
    cpu1_DW.obj_h.pMID.pIdx = 1.0F;
  }

  if (csumrev > cpu1_DW.obj_h.pMID.pMidHeap) {
    if (csum < cpu1_B.SCIReceive[1].f) {
      csum = csumrev - cpu1_DW.obj_h.pMID.pMidHeap;
      c_MedianFilterCG_trickleDownMin(&cpu1_DW.obj_h.pMID, csum * 2.0F);
    } else {
      csum = csumrev - cpu1_DW.obj_h.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (csum > 0.0F)) {
        flag = (obj_0->pBuf[(int16_T)obj_0->pHeap[(int16_T)(csum +
                 obj_0->pMidHeap) - 1] - 1] < obj_0->pBuf[(int16_T)obj_0->pHeap
                [(int16_T)((real32_T)floor(csum / 2.0F) + obj_0->pMidHeap) - 1]
                - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          modValueRev = csum + obj_0->pMidHeap;
          ind2 = (real32_T)floor(csum / 2.0F) + obj_0->pMidHeap;
          temp = obj_0->pHeap[(int16_T)modValueRev - 1];
          obj_0->pHeap[(int16_T)modValueRev - 1] = obj_0->pHeap[(int16_T)ind2 -
            1];
          obj_0->pHeap[(int16_T)ind2 - 1] = temp;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)modValueRev - 1] - 1] =
            modValueRev;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          csum = (real32_T)floor(csum / 2.0F);
        }
      }

      if (csum == 0.0F) {
        c_MedianFilterCG_trickleDownMax(&cpu1_DW.obj_h.pMID, -1.0F);
      }
    }
  } else if (csumrev < cpu1_DW.obj_h.pMID.pMidHeap) {
    if (cpu1_B.SCIReceive[1].f < csum) {
      csum = csumrev - cpu1_DW.obj_h.pMID.pMidHeap;
      c_MedianFilterCG_trickleDownMax(&cpu1_DW.obj_h.pMID, csum * 2.0F);
    } else {
      csum = csumrev - cpu1_DW.obj_h.pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (csum < 0.0F)) {
        csumrev = csum / 2.0F;
        if (csumrev < 0.0F) {
          modValueRev = (real32_T)ceil(csumrev);
        } else {
          modValueRev = -0.0F;
        }

        flag = (obj_0->pBuf[(int16_T)obj_0->pHeap[(int16_T)(modValueRev +
                 obj_0->pMidHeap) - 1] - 1] < obj_0->pBuf[(int16_T)obj_0->pHeap
                [(int16_T)(csum + obj_0->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          if (csumrev < 0.0F) {
            modValueRev = (real32_T)ceil(csumrev);
          } else {
            modValueRev = -0.0F;
          }

          modValueRev += obj_0->pMidHeap;
          ind2 = csum + obj_0->pMidHeap;
          temp = obj_0->pHeap[(int16_T)modValueRev - 1];
          obj_0->pHeap[(int16_T)modValueRev - 1] = obj_0->pHeap[(int16_T)ind2 -
            1];
          obj_0->pHeap[(int16_T)ind2 - 1] = temp;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)modValueRev - 1] - 1] =
            modValueRev;
          obj_0->pPos[(int16_T)obj_0->pHeap[(int16_T)ind2 - 1] - 1] = ind2;
          if (csumrev < 0.0F) {
            csum = (real32_T)ceil(csumrev);
          } else {
            csum = -0.0F;
          }
        }
      }

      if (csum == 0.0F) {
        c_MedianFilterCG_trickleDownMin(&cpu1_DW.obj_h.pMID, 1.0F);
      }
    }
  } else {
    if (cpu1_DW.obj_h.pMID.pMaxHeapLength != 0.0F) {
      c_MedianFilterCG_trickleDownMax(&cpu1_DW.obj_h.pMID, -1.0F);
    }

    if (cpu1_DW.obj_h.pMID.pMinHeapLength > 0.0F) {
      c_MedianFilterCG_trickleDownMin(&cpu1_DW.obj_h.pMID, 1.0F);
    }
  }

  csum = cpu1_DW.obj_h.pMID.pBuf[(int16_T)cpu1_DW.obj_h.pMID.pHeap[(int16_T)
    cpu1_DW.obj_h.pMID.pMidHeap - 1] - 1];

  /* DataTypeConversion: '<S1>/Cast To Single1' incorporates:
   *  Gain: '<S1>/Gain8'
   *  MATLABSystem: '<Root>/Median Filter'
   *  Rounding: '<S1>/Round'
   */
  modValueRev = rt_roundf_snf(cpu1_P.Gain8_Gain_a * csum);
  if (rtIsNaNF(modValueRev) || rtIsInfF(modValueRev)) {
    modValueRev = 0.0F;
  } else {
    modValueRev = (real32_T)fmod(modValueRev, 4.294967296E+9);
  }

  /* RateTransition: '<Root>/RT' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Single'
   *  DataTypeConversion: '<S1>/Cast To Single1'
   *  Gain: '<S1>/Gain9'
   */
  cpu1_DW.RT_Buffer0 = (real32_T)(modValueRev < 0.0F ? -(int32_T)(uint32_T)
    -modValueRev : (int32_T)(uint32_T)modValueRev) * cpu1_P.Gain9_Gain_n;
}

/* Model initialize function */
void cpu1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)cpu1_M, 0,
                sizeof(RT_MODEL_cpu1_T));

  /* block I/O */
  (void) memset(((void *) &cpu1_B), 0,
                sizeof(B_cpu1_T));

  /* states (dwork) */
  (void) memset((void *)&cpu1_DW, 0,
                sizeof(DW_cpu1_T));

  {
    g_dsp_internal_SlidingWindowA_T *obj;
    int16_T i;

    /* Start for S-Function (c280xgpio_di): '<S7>/Digital Input1' */
    EALLOW;
    //GpioDataRegs.GPADAT.all = 0U;
    GpioCtrlRegs.GPAMUX1.all &= 0xFFFF03FFU;
    GpioCtrlRegs.GPADIR.all &= ~0xFFFFFF1FU;

    //for switching between uart and can

    //enable pin as gpio (put 00 in bits number 26,27)
    GpioCtrlRegs.GPBMUX2.all &= 0xF3FFFFFFU;
    //enable pull up resistor on gpio61
    GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;
    //set gpio61 as input pin
    GpioCtrlRegs.GPBDIR.bit.GPIO61 = 0;

    EDIS;

    /* Start for S-Function (c280xgpio_di): '<S7>/Digital Input4' */
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all &= 0xF00FFFFU;
    GpioCtrlRegs.GPADIR.all &= 0xFFFF30FFU;


    EDIS;

    /* Start for S-Function (c2802xadc): '<S7>/ADC2' */
    if (MW_adcAInitFlag == 0U) {
      InitAdcA();
      MW_adcAInitFlag = 1U;
    }

    config_ADCA_SOC0 ();

    /* Start for S-Function (c28xipc_rx): '<Root>/IPC Receive' */
    IPCInit(CHANNEL1, 1, 0);

    /* Start for S-Function (c280xcanxmt): '<Root>/eCAN Transmit' */
    CAN_setupMessageObject(CANB_BASE, 2, 0x1C7, CAN_MSG_FRAME_STD,
      CAN_MSG_OBJ_TYPE_TX, 0, CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH_TX);

    // for receiving steering and speed
    CAN_setupMessageObject(CANB_BASE, RX_MSG_OBJ1_ID, CAN_RECIEVE_SETPOINT_MSG_ID,
                                   CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0xFFFF,
                                   CAN_MSG_OBJ_USE_ID_FILTER, MSG_DATA_LENGTH_RX);

    // for receiving command to change transmit rate
   CAN_setupMessageObject(CANB_BASE, RX_MSG_OBJ2_ID, CAN_RECIEVE_RATE_MSG_ID,
                                  CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0xFFFF,
                                   CAN_MSG_OBJ_USE_ID_FILTER, MSG_DATA_LENGTH_RX);



    /* Start for RateTransition: '<Root>/RT' */
    cpu1_B.RT_l = cpu1_P.RT_InitialCondition;

    /* Start for S-Function (c28xsci_rx): '<Root>/SCI Receive' */

    /* Initialize out port */
    {
      cpu1_B.SCIReceive[0].f = (real32_T)0.0;
      cpu1_B.SCIReceive[1].f = (real32_T)0.0;
    }

    /* Start for S-Function (c28xipc_tx): '<Root>/IPC Transmit' */
    IPCInit(CHANNEL0, 1, 0);

    /* InitializeConditions for Delay: '<Root>/Delay' */
    for (i = 0; i < 100; i++) {
      cpu1_DW.Delay_DSTATE[i] = cpu1_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay' */

    /* InitializeConditions for RateTransition: '<Root>/RT' */
    cpu1_DW.RT_Buffer0 = cpu1_P.RT_InitialCondition;

    /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
    cpu1_DW.Integrator_DSTATE = cpu1_P.PIDController1_InitialConditi_j;
    cpu1_DW.Integrator_PrevResetState = 2;

    /* InitializeConditions for DiscreteIntegrator: '<S37>/Filter' */
    cpu1_DW.Filter_DSTATE = cpu1_P.PIDController1_InitialCondition;
    cpu1_DW.Filter_PrevResetState = 2;

    /* InitializeConditions for DiscreteIntegrator: '<S90>/Integrator' */
    cpu1_DW.Integrator_DSTATE_j = cpu1_P.PIDController2_InitialConditi_o;
    cpu1_DW.Integrator_PrevResetState_e = 2;

    /* InitializeConditions for DiscreteIntegrator: '<S85>/Filter' */
    cpu1_DW.Filter_DSTATE_o = cpu1_P.PIDController2_InitialCondition;
    cpu1_DW.Filter_PrevResetState_d = 2;

    /* SystemInitialize for Chart: '<Root>/Chart4' */
    cpu1_DW.is_active_c18_cpu1 = 0U;
    cpu1_DW.is_c18_cpu1 = cpu1_IN_NO_ACTIVE_CHILD;
    cpu1_DW.f15 = 0.0;
    cpu1_DW.f20 = 0.0;
    cpu1_DW.f10 = 0.0;
    cpu1_B.sat = 0.0;
    cpu1_B.kp = 0.0;
    cpu1_B.ki = 0.0;
    cpu1_B.kd_l = 0.0;
    cpu1_B.reset_f = 0.0;

    /* SystemInitialize for Chart: '<Root>/ready' */
    cpu1_DW.is_active_c16_cpu1 = 0U;
    cpu1_DW.is_c16_cpu1 = cpu1_IN_NO_ACTIVE_CHILD;
    cpu1_B.kd = 0.0;
    cpu1_B.reset = 0.0;

    /* Start for MATLABSystem: '<S7>/Median Filter' */
    cpu1_DW.obj_l.matlabCodegenIsDeleted = false;
    cpu1_DW.obj_l.isInitialized = 1L;
    cpu1_DW.obj_l.NumChannels = 1L;
    cpu1_DW.obj_l.pMID.isInitialized = 0L;
    cpu1_DW.obj_l.isSetupComplete = true;

    /* InitializeConditions for MATLABSystem: '<S7>/Median Filter' */
    if (cpu1_DW.obj_l.pMID.isInitialized == 1L) {
      cpu_MedianFilterCG_resetImpl_j1(&cpu1_DW.obj_l.pMID);
    }

    /* End of InitializeConditions for MATLABSystem: '<S7>/Median Filter' */

    /* Start for MATLABSystem: '<Root>/Median Filter1' */
    cpu1_DW.obj.matlabCodegenIsDeleted = false;
    cpu1_DW.obj.isInitialized = 1L;
    cpu1_DW.obj.NumChannels = 1L;
    cpu1_DW.obj.pMID.isInitialized = 0L;
    cpu1_DW.obj.isSetupComplete = true;

    /* InitializeConditions for MATLABSystem: '<Root>/Median Filter1' */
    if (cpu1_DW.obj.pMID.isInitialized == 1L) {
      cpu1_MedianFilterCG_resetImpl_j(&cpu1_DW.obj.pMID);
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Median Filter1' */

    /* Start for MATLABSystem: '<Root>/DAC' */
    MW_ConfigureDACA();

    /* Start for MATLABSystem: '<Root>/DAC2' */
    MW_ConfigureDACB();

    /* Start for MATLABSystem: '<Root>/Moving Average' */
    cpu1_DW.obj_g.isInitialized = 0L;
    cpu1_DW.obj_g.NumChannels = -1L;
    cpu1_DW.obj_g.FrameLength = -1L;
    cpu1_DW.obj_g.matlabCodegenIsDeleted = false;
    cpu1_SystemCore_setup(&cpu1_DW.obj_g);

    /* InitializeConditions for MATLABSystem: '<Root>/Moving Average' */
    obj = cpu1_DW.obj_g.pStatistic;
    if (obj->isInitialized == 1L) {
      obj->pCumSum = 0.0F;
      obj->pCumSumRev = 0.0F;
      obj->pCumRevIndex = 1.0F;
      obj->pModValueRev = 0.0F;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average' */

    /* Start for MATLABSystem: '<Root>/Median Filter' */
    cpu1_DW.obj_h.matlabCodegenIsDeleted = false;
    cpu1_DW.obj_h.isInitialized = 1L;
    cpu1_DW.obj_h.NumChannels = 1L;
    cpu1_DW.obj_h.pMID.isInitialized = 0L;
    cpu1_DW.obj_h.isSetupComplete = true;

    /* InitializeConditions for MATLABSystem: '<Root>/Median Filter' */
    if (cpu1_DW.obj_h.pMID.isInitialized == 1L) {
      cpu1_MedianFilterCG_resetImpl(&cpu1_DW.obj_h.pMID);
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Median Filter' */

    /* ConstCode for IfAction SubSystem: '<Root>/If Action Subsystem' */
    /* ConstCode for S-Function (memorycopy): '<S4>/Memory Copy' incorporates:
     *  Constant: '<S4>/Constant3'
     */
    {
      uint32_T *memindsrc1 = (uint32_T *) (&cpu1_P.Constant3_Value);
      uint32_T *meminddst1 = (uint32_T *) (31756U);
      EALLOW;
      *(uint32_T *) (meminddst1) = *(uint32_T *) (memindsrc1);
      EDIS;
    }

    /* End of ConstCode for SubSystem: '<Root>/If Action Subsystem' */
  }
}

/* Model terminate function */
void cpu1_terminate(void)
{
  g_dsp_internal_SlidingWindowA_T *obj;

  /* Terminate for MATLABSystem: '<S7>/Median Filter' */
  if (!cpu1_DW.obj_l.matlabCodegenIsDeleted) {
    cpu1_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((cpu1_DW.obj_l.isInitialized == 1L) && cpu1_DW.obj_l.isSetupComplete) {
      cpu1_DW.obj_l.NumChannels = -1L;
      if (cpu1_DW.obj_l.pMID.isInitialized == 1L) {
        cpu1_DW.obj_l.pMID.isInitialized = 2L;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S7>/Median Filter' */
  /* Terminate for MATLABSystem: '<Root>/Median Filter1' */
  if (!cpu1_DW.obj.matlabCodegenIsDeleted) {
    cpu1_DW.obj.matlabCodegenIsDeleted = true;
    if ((cpu1_DW.obj.isInitialized == 1L) && cpu1_DW.obj.isSetupComplete) {
      cpu1_DW.obj.NumChannels = -1L;
      if (cpu1_DW.obj.pMID.isInitialized == 1L) {
        cpu1_DW.obj.pMID.isInitialized = 2L;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Median Filter1' */

  /* Terminate for MATLABSystem: '<Root>/Moving Average' */
  if (!cpu1_DW.obj_g.matlabCodegenIsDeleted) {
    cpu1_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((cpu1_DW.obj_g.isInitialized == 1L) && cpu1_DW.obj_g.isSetupComplete) {
      obj = cpu1_DW.obj_g.pStatistic;
      if (obj->isInitialized == 1L) {
        obj->isInitialized = 2L;
      }

      cpu1_DW.obj_g.NumChannels = -1L;
      cpu1_DW.obj_g.FrameLength = -1L;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Average' */
  /* Terminate for MATLABSystem: '<Root>/Median Filter' */
  if (!cpu1_DW.obj_h.matlabCodegenIsDeleted) {
    cpu1_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((cpu1_DW.obj_h.isInitialized == 1L) && cpu1_DW.obj_h.isSetupComplete) {
      cpu1_DW.obj_h.NumChannels = -1L;
      if (cpu1_DW.obj_h.pMID.isInitialized == 1L) {
        cpu1_DW.obj_h.pMID.isInitialized = 2L;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Median Filter' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
