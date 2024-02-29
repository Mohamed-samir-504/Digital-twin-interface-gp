/*
 * File: cpu1_types.h
 *
 * Code generated for Simulink model 'cpu1'.
 *
 * Model version                  : 1.291
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Feb 29 19:35:49 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_cpu1_types_h_
#define RTW_HEADER_cpu1_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_mJwWZQsvJAXvgRMjJItCbG
#define struct_tag_mJwWZQsvJAXvgRMjJItCbG

struct tag_mJwWZQsvJAXvgRMjJItCbG
{
  int32_T isInitialized;
};

#endif                                 /* struct_tag_mJwWZQsvJAXvgRMjJItCbG */

#ifndef typedef_codertarget_tic2000_blocks_DA_T
#define typedef_codertarget_tic2000_blocks_DA_T

typedef struct tag_mJwWZQsvJAXvgRMjJItCbG codertarget_tic2000_blocks_DA_T;

#endif                             /* typedef_codertarget_tic2000_blocks_DA_T */

#ifndef struct_tag_HNdtgWxo5MKrgMXWKCOF7F
#define struct_tag_HNdtgWxo5MKrgMXWKCOF7F

struct tag_HNdtgWxo5MKrgMXWKCOF7F
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pWinLen;
  real32_T pBuf[3];
  real32_T pHeap[3];
  real32_T pMidHeap;
  real32_T pIdx;
  real32_T pPos[3];
  real32_T pMinHeapLength;
  real32_T pMaxHeapLength;
};

#endif                                 /* struct_tag_HNdtgWxo5MKrgMXWKCOF7F */

#ifndef typedef_c_dsp_internal_MedianFilterCG_T
#define typedef_c_dsp_internal_MedianFilterCG_T

typedef struct tag_HNdtgWxo5MKrgMXWKCOF7F c_dsp_internal_MedianFilterCG_T;

#endif                             /* typedef_c_dsp_internal_MedianFilterCG_T */

#ifndef struct_tag_sTp1qtfVN7hWfqQGtc75C
#define struct_tag_sTp1qtfVN7hWfqQGtc75C

struct tag_sTp1qtfVN7hWfqQGtc75C
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pWinLen;
  real32_T pBuf[28];
  real32_T pHeap[28];
  real32_T pMidHeap;
  real32_T pIdx;
  real32_T pPos[28];
  real32_T pMinHeapLength;
  real32_T pMaxHeapLength;
};

#endif                                 /* struct_tag_sTp1qtfVN7hWfqQGtc75C */

#ifndef typedef_c_dsp_internal_MedianFilter_j_T
#define typedef_c_dsp_internal_MedianFilter_j_T

typedef struct tag_sTp1qtfVN7hWfqQGtc75C c_dsp_internal_MedianFilter_j_T;

#endif                             /* typedef_c_dsp_internal_MedianFilter_j_T */

#ifndef struct_tag_wpRH6j2fSBbvjvb2g0IdMF
#define struct_tag_wpRH6j2fSBbvjvb2g0IdMF

struct tag_wpRH6j2fSBbvjvb2g0IdMF
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pCumSum;
  real32_T pCumSumRev;
  real32_T pCumRevIndex;
  real32_T pModValueRev;
};

#endif                                 /* struct_tag_wpRH6j2fSBbvjvb2g0IdMF */

#ifndef typedef_g_dsp_internal_SlidingWindowA_T
#define typedef_g_dsp_internal_SlidingWindowA_T

typedef struct tag_wpRH6j2fSBbvjvb2g0IdMF g_dsp_internal_SlidingWindowA_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindowA_T */

#ifndef struct_tag_9hFTYXcLfRLcb1MbGkAXqE
#define struct_tag_9hFTYXcLfRLcb1MbGkAXqE

struct tag_9hFTYXcLfRLcb1MbGkAXqE
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pWinLen;
  real32_T pBuf[5];
  real32_T pHeap[5];
  real32_T pMidHeap;
  real32_T pIdx;
  real32_T pPos[5];
  real32_T pMinHeapLength;
  real32_T pMaxHeapLength;
};

#endif                                 /* struct_tag_9hFTYXcLfRLcb1MbGkAXqE */

#ifndef typedef_c_dsp_internal_MedianFilte_j1_T
#define typedef_c_dsp_internal_MedianFilte_j1_T

typedef struct tag_9hFTYXcLfRLcb1MbGkAXqE c_dsp_internal_MedianFilte_j1_T;

#endif                             /* typedef_c_dsp_internal_MedianFilte_j1_T */

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_cpu1_T
#define typedef_cell_wrap_cpu1_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_cpu1_T;

#endif                                 /* typedef_cell_wrap_cpu1_T */

#ifndef struct_tag_mcbtZQekP5m7MFZuVcv6xB
#define struct_tag_mcbtZQekP5m7MFZuVcv6xB

struct tag_mcbtZQekP5m7MFZuVcv6xB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_cpu1_T inputVarSize;
  int32_T NumChannels;
  c_dsp_internal_MedianFilterCG_T pMID;
};

#endif                                 /* struct_tag_mcbtZQekP5m7MFZuVcv6xB */

#ifndef typedef_dsp_simulink_MedianFilter_cpu_T
#define typedef_dsp_simulink_MedianFilter_cpu_T

typedef struct tag_mcbtZQekP5m7MFZuVcv6xB dsp_simulink_MedianFilter_cpu_T;

#endif                             /* typedef_dsp_simulink_MedianFilter_cpu_T */

#ifndef struct_tag_jIh4HCY8yhWJeWqi0g3j1G
#define struct_tag_jIh4HCY8yhWJeWqi0g3j1G

struct tag_jIh4HCY8yhWJeWqi0g3j1G
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_cpu1_T inputVarSize;
  int32_T NumChannels;
  c_dsp_internal_MedianFilter_j_T pMID;
};

#endif                                 /* struct_tag_jIh4HCY8yhWJeWqi0g3j1G */

#ifndef typedef_dsp_simulink_MedianFilter_c_j_T
#define typedef_dsp_simulink_MedianFilter_c_j_T

typedef struct tag_jIh4HCY8yhWJeWqi0g3j1G dsp_simulink_MedianFilter_c_j_T;

#endif                             /* typedef_dsp_simulink_MedianFilter_c_j_T */

#ifndef struct_tag_SOkmgxdMaVwUgzSiGxpZRD
#define struct_tag_SOkmgxdMaVwUgzSiGxpZRD

struct tag_SOkmgxdMaVwUgzSiGxpZRD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_cpu1_T inputVarSize;
  g_dsp_internal_SlidingWindowA_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindowA_T _pobj0;
};

#endif                                 /* struct_tag_SOkmgxdMaVwUgzSiGxpZRD */

#ifndef typedef_dsp_simulink_MovingAverage_cp_T
#define typedef_dsp_simulink_MovingAverage_cp_T

typedef struct tag_SOkmgxdMaVwUgzSiGxpZRD dsp_simulink_MovingAverage_cp_T;

#endif                             /* typedef_dsp_simulink_MovingAverage_cp_T */

#ifndef struct_tag_UUX9eJX7hXsJyB0G5SLluF
#define struct_tag_UUX9eJX7hXsJyB0G5SLluF

struct tag_UUX9eJX7hXsJyB0G5SLluF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_cpu1_T inputVarSize;
  int32_T NumChannels;
  c_dsp_internal_MedianFilte_j1_T pMID;
};

#endif                                 /* struct_tag_UUX9eJX7hXsJyB0G5SLluF */

#ifndef typedef_dsp_simulink_MedianFilter_j1_T
#define typedef_dsp_simulink_MedianFilter_j1_T

typedef struct tag_UUX9eJX7hXsJyB0G5SLluF dsp_simulink_MedianFilter_j1_T;

#endif                              /* typedef_dsp_simulink_MedianFilter_j1_T */

/* Parameters (default storage) */
typedef struct P_cpu1_T_ P_cpu1_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_cpu1_T RT_MODEL_cpu1_T;

#endif                                 /* RTW_HEADER_cpu1_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
