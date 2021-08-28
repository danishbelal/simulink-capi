/*
 * File: ControllerRefRef.h
 *
 * Code generated for Simulink model 'ControllerRefRef'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Aug 25 10:23:45 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ControllerRefRef_h_
#define RTW_HEADER_ControllerRefRef_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef ControllerRefRef_COMMON_INCLUDES_
#define ControllerRefRef_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ControllerRefRef_COMMON_INCLUDES_ */

#include "ControllerRefRef_types.h"

/* Parameters (default storage) */
struct Parameters_ControllerRefRef_T_
{
  real_T Gain_Gain;                    /* Expression: 1.85
                                        * Referenced by: '<Root>/Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ControllerRefRef_T
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
    void* dataAddress[1];
    int32_T* vardimsAddress[1];
    RTWLoggingFcnPtr loggingPtrs[1];
  }
  DataMapInfo;
};

typedef struct
{
  RT_MODEL_ControllerRefRef_T rtm;
}
rtMdlrefDWork_ControllerRefRe_T;

/* Model reference registration function */
extern void ControllerRefRef_initialize(const char_T **rt_errorStatus,
  RT_MODEL_ControllerRefRef_T *const ControllerRefRef_M,
  rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T *rt_ChildPath, int_T
  rt_ChildMMIIdx, int_T rt_CSTATEIdx);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  ControllerRefRef_GetCAPIStaticMap(void);
extern void ControllerRefRef(const real_T *rtu_Input, real_T *rty_Output);

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
 * '<Root>' : 'ControllerRefRef'
 */
#endif                                 /* RTW_HEADER_ControllerRefRef_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
