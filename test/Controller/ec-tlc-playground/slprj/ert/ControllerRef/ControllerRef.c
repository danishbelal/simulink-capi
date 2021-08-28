/*
 * File: ControllerRef.c
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

#include "ControllerRef_capi.h"
#include "ControllerRef.h"
#include "ControllerRef_private.h"

Parameters_ControllerRef_T ControllerRef_P =
{
  /* Expression: 12.3
   * Referenced by: '<Root>/NormalGain'
   */
  12.3
};

/* Output and update for referenced model: 'ControllerRef' */
void ControllerRef(RT_MODEL_ControllerRef_T * const ControllerRef_M, const
                   real_T *rtu_Input, real_T *rty_Output, rtB_ControllerRef_T
                   *localB)
{
  InstP_ControllerRef_T *ControllerRef_InstP_arg =
    ControllerRef_M->ControllerRef_InstP_ref;

  /* Gain: '<Root>/ConfigGain' */
  localB->ConfigGain = ControllerRef_InstP_arg->SubmodelConfig.Gain * *rtu_Input;

  /* ModelReference: '<Root>/Model' */
  ControllerRefRef(rtu_Input, &localB->Model);

  /* Gain: '<Root>/NormalGain' */
  localB->NormalGain = ControllerRef_P.NormalGain_Gain * *rtu_Input;

  /* Sum: '<Root>/Sum1' */
  localB->Sum1 = localB->NormalGain + localB->Model;

  /* Sum: '<Root>/Sum' */
  *rty_Output = localB->ConfigGain + localB->Sum1;
}

/* Model initialize function */
void ControllerRef_initialize(const char_T **rt_errorStatus,
  RT_MODEL_ControllerRef_T *const ControllerRef_M, rtB_ControllerRef_T *localB,
  rtDW_ControllerRef_T *localDW, rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  InstP_ControllerRef_T *ControllerRef_InstP_arg = ((InstP_ControllerRef_T *)
    ControllerRef_M->ControllerRef_InstP_ref);

  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)ControllerRef_M, 0,
                sizeof(RT_MODEL_ControllerRef_T));

  /* Restore pointers to storage classes */
  ControllerRef_M->ControllerRef_InstP_ref = ControllerRef_InstP_arg;

  /* initialize error status */
  rtmSetErrorStatusPointer(ControllerRef_M, rt_errorStatus);

  /* block I/O */
  (void) memset(((void *) localB), 0,
                sizeof(rtB_ControllerRef_T));

  /* states (dwork) */
  (void) memset((void *)localDW, 0,
                sizeof(rtDW_ControllerRef_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  {
    ControllerRef_InitializeDataMapInfo(ControllerRef_M, localB);
  }

  /* Model Initialize function for ModelReference Block: '<Root>/Model' */
  ControllerRefRef_initialize(rtmGetErrorStatusPointer(ControllerRef_M),
    &(localDW->Model_InstanceData.rtm), &(ControllerRef_M->DataMapInfo.mmi),
    "ControllerRef/Model", 0, -1);

  /* Initialize Parent model MMI */
  if ((rt_ParentMMI != (NULL)) && (rt_ChildPath != (NULL)))
  {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx,
                        &(ControllerRef_M->DataMapInfo.mmi));
    rtwCAPI_SetPath(ControllerRef_M->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex(ControllerRef_M->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
