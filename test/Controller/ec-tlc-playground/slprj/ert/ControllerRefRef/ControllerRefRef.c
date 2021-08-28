/*
 * File: ControllerRefRef.c
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

#include "ControllerRefRef_capi.h"
#include "ControllerRefRef.h"
#include "ControllerRefRef_private.h"

Parameters_ControllerRefRef_T ControllerRefRef_P =
{
  /* Expression: 1.85
   * Referenced by: '<Root>/Gain'
   */
  1.85
};

/* Output and update for referenced model: 'ControllerRefRef' */
void ControllerRefRef(const real_T *rtu_Input, real_T *rty_Output)
{
  /* Gain: '<Root>/Gain' */
  *rty_Output = ControllerRefRef_P.Gain_Gain * *rtu_Input;
}

/* Model initialize function */
void ControllerRefRef_initialize(const char_T **rt_errorStatus,
  RT_MODEL_ControllerRefRef_T *const ControllerRefRef_M,
  rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T *rt_ChildPath, int_T
  rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)ControllerRefRef_M, 0,
                sizeof(RT_MODEL_ControllerRefRef_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(ControllerRefRef_M, rt_errorStatus);

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  {
    ControllerRefRef_InitializeDataMapInfo(ControllerRefRef_M);
  }

  /* Initialize Parent model MMI */
  if ((rt_ParentMMI != (NULL)) && (rt_ChildPath != (NULL)))
  {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx,
                        &(ControllerRefRef_M->DataMapInfo.mmi));
    rtwCAPI_SetPath(ControllerRefRef_M->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex(ControllerRefRef_M->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
