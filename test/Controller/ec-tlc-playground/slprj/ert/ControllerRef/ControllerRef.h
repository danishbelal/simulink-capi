/*
 * File: ControllerRef.h
 *
 * Code generated for Simulink model 'ControllerRef'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Aug 25 10:24:08 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ControllerRef_h_
#define RTW_HEADER_ControllerRef_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef ControllerRef_COMMON_INCLUDES_
#define ControllerRef_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ControllerRef_COMMON_INCLUDES_ */

#include "ControllerRef_types.h"

/* Child system includes */
#include "ControllerRefRef.h"

/* Block signals for model 'ControllerRef' */
typedef struct
{
  real_T ConfigGain;                   /* '<Root>/ConfigGain' */
  real_T Model;                        /* '<Root>/Model' */
  real_T NormalGain;                   /* '<Root>/NormalGain' */
  real_T Sum1;                         /* '<Root>/Sum1' */
}
rtB_ControllerRef_T;

/* Block states (default storage) for model 'ControllerRef' */
typedef struct
{
  rtMdlrefDWork_ControllerRefRe_T Model_InstanceData;/* '<Root>/Model' */
}
rtDW_ControllerRef_T;

/* instance parameters, for model 'ControllerRef' */
typedef struct
{
  ConfigBus SubmodelConfig;            /* Variable: SubmodelConfig
                                        * Referenced by: synthesized block
                                        */
}
InstP_ControllerRef_T;

/* Parameters (default storage) */
struct Parameters_ControllerRef_T_
{
  real_T NormalGain_Gain;              /* Expression: 12.3
                                        * Referenced by: '<Root>/NormalGain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ControllerRef_T
{
  const char_T **errorStatus;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct
  {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[6];
    int32_T* vardimsAddress[6];
    RTWLoggingFcnPtr loggingPtrs[6];
    rtwCAPI_ModelMappingInfo* childMMI[1];
  }
  DataMapInfo;

  InstP_ControllerRef_T *ControllerRef_InstP_ref;
};

typedef struct
{
  rtB_ControllerRef_T rtb;
  rtDW_ControllerRef_T rtdw;
  RT_MODEL_ControllerRef_T rtm;
}
rtMdlrefDWork_ControllerRef_T;

/* Model reference registration function */
extern void ControllerRef_initialize(const char_T **rt_errorStatus,
  RT_MODEL_ControllerRef_T *const ControllerRef_M, rtB_ControllerRef_T *localB,
  rtDW_ControllerRef_T *localDW, rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  ControllerRef_GetCAPIStaticMap(void);
extern void ControllerRef(RT_MODEL_ControllerRef_T * const ControllerRef_M,
  const real_T *rtu_Input, real_T *rty_Output, rtB_ControllerRef_T *localB);

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
 * '<Root>' : 'ControllerRef'
 */
#endif                                 /* RTW_HEADER_ControllerRef_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
