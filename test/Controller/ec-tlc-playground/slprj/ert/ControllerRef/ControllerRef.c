/*
 * File: ControllerRef.c
 *
 * Code generated for Simulink model 'ControllerRef'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Jan  8 15:54:48 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ControllerRef.h"
#include "ControllerRef_capi.h"
#include "ControllerRef_private.h"

Parameters_ControllerRef_T ControllerRef_P = {
    /* Expression: 12.3
   * Referenced by: '<Root>/NormalGain'
   */
    12.3
};

/* Output and update for referenced model: 'ControllerRef' */
void ControllerRef(RT_MODEL_ControllerRef_T* const ControllerRef_M, const real_T* rtu_Input, real_T* rty_Output, rtB_ControllerRef_T* localB)
{
    InstP_ControllerRef_T* ControllerRef_InstP_arg = ControllerRef_M->ControllerRef_InstP_ref;
    localB->ConfigGain = ControllerRef_InstP_arg->SubmodelConfig.Gain * *rtu_Input;
    ControllerRefRef(rtu_Input, &localB->Model);
    localB->NormalGain = ControllerRef_P.NormalGain_Gain * *rtu_Input;
    localB->Sum1 = localB->NormalGain + localB->Model;
    *rty_Output = localB->ConfigGain + localB->Sum1;
}

/* Model initialize function */
void ControllerRef_initialize(const char_T** rt_errorStatus,
    RT_MODEL_ControllerRef_T* const ControllerRef_M, rtB_ControllerRef_T* localB,
    rtDW_ControllerRef_T* localDW, rtwCAPI_ModelMappingInfo* rt_ParentMMI, const char_T* rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
    InstP_ControllerRef_T* ControllerRef_InstP_arg = ((InstP_ControllerRef_T*)ControllerRef_M->ControllerRef_InstP_ref);

    (void)memset((void*)ControllerRef_M, 0, sizeof(RT_MODEL_ControllerRef_T));
    ControllerRef_M->ControllerRef_InstP_ref = ControllerRef_InstP_arg;
    rtmSetErrorStatusPointer(ControllerRef_M, rt_errorStatus);
    (void)memset(((void*)localB), 0, sizeof(rtB_ControllerRef_T));
    (void)memset((void*)localDW, 0, sizeof(rtDW_ControllerRef_T));
    ControllerRef_InitializeDataMapInfo(ControllerRef_M, localB);

    /* Model Initialize function for ModelReference Block: '<Root>/Model' */
    ControllerRefRef_initialize(rtmGetErrorStatusPointer(ControllerRef_M),
        &(localDW->Model_InstanceData.rtm),
        &(ControllerRef_M->DataMapInfo.mmi),
        "ControllerRef/Model",
        0,
        -1);

    /* Initialize Parent model MMI */
    if ((rt_ParentMMI != (NULL)) && (rt_ChildPath != (NULL)))
    {
        rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &(ControllerRef_M->DataMapInfo.mmi));
        rtwCAPI_SetPath(ControllerRef_M->DataMapInfo.mmi, rt_ChildPath);
        rtwCAPI_MMISetContStateStartIndex(ControllerRef_M->DataMapInfo.mmi, rt_CSTATEIdx);
    }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
