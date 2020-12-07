/*
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.61
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Dec  4 11:15:12 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include "Controller_capi.h"
#include "Controller_private.h"

/* Model step function */
void Controller_step(RT_MODEL_Controller_T* const Controller_M,
    ExternalInputs_Controller_T* Controller_U,
    ExternalOutputs_Controller_T* Controller_Y)
{
    BlockIO_Controller_T* Controller_B = ((BlockIO_Controller_T*)
                                              Controller_M->blockIO);
    D_Work_Controller_T* Controller_DWork = ((D_Work_Controller_T*)
                                                 Controller_M->dwork);
    int32_T i;
    int32_T i_0;
    for (i = 0; i < 64; i++)
    {
        /* Outport: '<Root>/X4' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Inport: '<Root>/e'
     *  Product: '<Root>/Product1'
     */
        Controller_Y->X4[i] = Controller_U->e * rtP_X4_DD[i];
    }

    for (i = 0; i < 27; i++)
    {
        /* Outport: '<Root>/X3' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Inport: '<Root>/e'
     *  Product: '<Root>/Product'
     */
        Controller_Y->X3[i] = Controller_U->e * rtP_X3_DD[i];
    }

    /* Gain: '<Root>/MatGain' incorporates:
   *  Constant: '<Root>/Constant'
   */
    for (i = 0; i < 3; i++)
    {
        for (i_0 = 0; i_0 < 3; i_0++)
        {
            Controller_B->MatGain[i_0 + 3 * i] = 0.0;
            Controller_B->MatGain[i_0 + 3 * i] += Controller_P.mMatrix[3 * i] * Controller_P.Constant_Value[i_0];
            Controller_B->MatGain[i_0 + 3 * i] += Controller_P.mMatrix[3 * i + 1] * Controller_P.Constant_Value[i_0 + 3];
            Controller_B->MatGain[i_0 + 3 * i] += Controller_P.mMatrix[3 * i + 2] * Controller_P.Constant_Value[i_0 + 6];
        }
    }

    /* End of Gain: '<Root>/MatGain' */

    /* ModelReference: '<Root>/Model' incorporates:
   *  Inport: '<Root>/e'
   */
    ControllerRef(&(Controller_DWork->Model_InstanceData.rtm), &Controller_U->e,
        &Controller_B->Model, &(Controller_DWork->Model_InstanceData.rtb));

    /* Gain: '<Root>/ConfigDDGain' incorporates:
   *  Inport: '<Root>/e'
   */
    Controller_B->ConfigDDGain = Controller_P.ConfigDDGain_Gain * Controller_U->e;

    /* Gain: '<Root>/ConfigGain' incorporates:
   *  Inport: '<Root>/e'
   */
    Controller_B->ConfigGain = Controller_P.ModelConfig.Gain * Controller_U->e;
    for (i = 0; i < 9; i++)
    {
        /* Sum: '<Root>/Sum4' */
        Controller_B->Sum4[i] = Controller_B->MatGain[i] + Controller_B->Model;

        /* Sum: '<Root>/Sum3' */
        Controller_B->Sum3[i] = Controller_B->ConfigDDGain + Controller_B->Sum4[i];

        /* Outport: '<Root>/ScaledInput' incorporates:
     *  Sum: '<Root>/Sum2'
     */
        Controller_Y->y_m[i] = Controller_B->ConfigGain + Controller_B->Sum3[i];
    }

    /* UnitDelay: '<Root>/AlgebraicLoopBreaker' */
    Controller_B->AlgebraicLoopBreaker = Controller_DWork->AlgebraicLoopBreaker_DSTATE;

    /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/e'
   */
    Controller_B->Sum = Controller_U->e - Controller_B->AlgebraicLoopBreaker;

    /* Gain: '<Root>/SuperDuperGainBlock' */
    Controller_B->SuperDuperGainBlock = Controller_P.SuperDuperGainBlock_Gain * Controller_B->Sum;

    /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
    Controller_B->DiscreteTimeIntegrator = Controller_DWork->DiscreteTimeIntegrator_DSTATE;

    /* Outport: '<Root>/y' incorporates:
   *  Sum: '<Root>/Sum1'
   */
    Controller_Y->y = Controller_B->SuperDuperGainBlock + Controller_B->DiscreteTimeIntegrator;

    /* Update for UnitDelay: '<Root>/AlgebraicLoopBreaker' incorporates:
   *  Outport: '<Root>/y'
   */
    Controller_DWork->AlgebraicLoopBreaker_DSTATE = Controller_Y->y;

    /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
    Controller_DWork->DiscreteTimeIntegrator_DSTATE += Controller_P.DiscreteTimeIntegrator_gainval * Controller_B->SuperDuperGainBlock;
}

/* Model initialize function */
void Controller_initialize(RT_MODEL_Controller_T* const Controller_M,
    ExternalInputs_Controller_T* Controller_U,
    ExternalOutputs_Controller_T* Controller_Y)
{
    D_Work_Controller_T* Controller_DWork = ((D_Work_Controller_T*)Controller_M->dwork);
    BlockIO_Controller_T* Controller_B = ((BlockIO_Controller_T*)Controller_M->blockIO);

    (void)memset(((void*)Controller_B), 0, sizeof(BlockIO_Controller_T));
    (void)memset((void*)Controller_DWork, 0, sizeof(D_Work_Controller_T));

    Controller_U->e = 0.0;

    (void)memset((void*)Controller_Y, 0, sizeof(ExternalOutputs_Controller_T));
    Controller_InitializeDataMapInfo(Controller_M, Controller_M->blockIO);
    Controller_DWork->Model_InstanceData.rtm.ControllerRef_InstP_ref = &Controller_M->Controller_InstP_ref->InstP_Model;
    ControllerRef_initialize(rtmGetErrorStatusPointer(Controller_M),
        &(Controller_DWork->Model_InstanceData.rtm),
        &(Controller_DWork->Model_InstanceData.rtb), &(Controller_M->DataMapInfo.mmi),
        "Controller/Model",
        0,
        -1);

    Controller_DWork->AlgebraicLoopBreaker_DSTATE = Controller_P.AlgebraicLoopBreaker_InitialCon;
    Controller_DWork->DiscreteTimeIntegrator_DSTATE = Controller_P.DiscreteTimeIntegrator_IC;
}

/* Model terminate function */
void Controller_terminate(RT_MODEL_Controller_T* const Controller_M)
{
    /* (no terminate code required) */
    UNUSED_PARAMETER(Controller_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
