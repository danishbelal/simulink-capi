/*
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.74
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Jan  8 15:55:01 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller_capi.h"
#include "Controller.h"
#include "Controller_private.h"

/* Model step function */
void Controller_step(RT_MODEL_Controller_T *const Controller_M,
                     ExternalInputs_Controller_T *Controller_U,
                     ExternalOutputs_Controller_T *Controller_Y)
{
  BlockIO_Controller_T *Controller_B = ((BlockIO_Controller_T *)
    Controller_M->blockIO);
  D_Work_Controller_T *Controller_DWork = ((D_Work_Controller_T *)
    Controller_M->dwork);
  InstP_Controller_T *Controller_InstP = Controller_M->Controller_InstP_ref;
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
      Controller_B->MatGain[i_0 + 3 * i] += Controller_InstP->mMatrix[3 * i] *
        Controller_P.Constant_Value[i_0];
      Controller_B->MatGain[i_0 + 3 * i] += Controller_InstP->mMatrix[3 * i + 1]
        * Controller_P.Constant_Value[i_0 + 3];
      Controller_B->MatGain[i_0 + 3 * i] += Controller_InstP->mMatrix[3 * i + 2]
        * Controller_P.Constant_Value[i_0 + 6];
    }
  }

  /* End of Gain: '<Root>/MatGain' */

  /* ModelReference: '<Root>/ModelRef1' incorporates:
   *  Inport: '<Root>/e'
   */
  ControllerRef(&(Controller_DWork->ModelRef1_InstanceData.rtm),
                &Controller_U->e, &Controller_B->ModelRef1,
                &(Controller_DWork->ModelRef1_InstanceData.rtb));

  /* ModelReference: '<Root>/ModelRef2' incorporates:
   *  Inport: '<Root>/e'
   */
  ControllerRef(&(Controller_DWork->ModelRef2_InstanceData.rtm),
                &Controller_U->e, &Controller_B->ModelRef2,
                &(Controller_DWork->ModelRef2_InstanceData.rtb));

  /* Sum: '<Root>/Sum3' */
  Controller_B->Sum3 = Controller_B->ModelRef1 + Controller_B->ModelRef2;

  /* Gain: '<Root>/ConfigMW2' incorporates:
   *  Inport: '<Root>/e'
   */
  Controller_B->ConfigMW2 = Controller_P.ConfigMW2_Gain * Controller_U->e;

  /* Gain: '<Root>/ConfigMW1' incorporates:
   *  Inport: '<Root>/e'
   */
  Controller_B->ConfigMW1 = Controller_P.ConfigMW1_Gain * Controller_U->e;
  for (i = 0; i < 9; i++)
  {
    /* Sum: '<Root>/Sum4' */
    Controller_B->Sum4[i] = Controller_B->MatGain[i] + Controller_B->Sum3;

    /* Sum: '<Root>/Sum5' */
    Controller_B->Sum5[i] = Controller_B->ConfigMW2 + Controller_B->Sum4[i];

    /* Outport: '<Root>/ScaledInput' incorporates:
     *  Sum: '<Root>/Sum2'
     */
    Controller_Y->y_m[i] = Controller_B->ConfigMW1 + Controller_B->Sum5[i];
  }

  /* UnitDelay: '<Root>/AlgLoop' */
  Controller_B->AlgLoop = Controller_DWork->AlgLoop_DSTATE;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/e'
   */
  Controller_B->Sum = Controller_U->e - Controller_B->AlgLoop;

  /* Gain: '<Root>/SuperDuperGainBlock' */
  Controller_B->SuperDuperGainBlock = Controller_P.SuperDuperGainBlock_Gain *
    Controller_B->Sum;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  Controller_B->DiscreteTimeIntegrator =
    Controller_DWork->DiscreteTimeIntegrator_DSTATE;

  /* Outport: '<Root>/y' incorporates:
   *  Sum: '<Root>/Sum1'
   */
  Controller_Y->y = Controller_B->SuperDuperGainBlock +
    Controller_B->DiscreteTimeIntegrator;

  /* Update for UnitDelay: '<Root>/AlgLoop' incorporates:
   *  Outport: '<Root>/y'
   */
  Controller_DWork->AlgLoop_DSTATE = Controller_Y->y;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  Controller_DWork->DiscreteTimeIntegrator_DSTATE +=
    Controller_P.DiscreteTimeIntegrator_gainval *
    Controller_B->SuperDuperGainBlock;
}

/* Model initialize function */
void Controller_initialize(RT_MODEL_Controller_T *const Controller_M,
  ExternalInputs_Controller_T *Controller_U, ExternalOutputs_Controller_T
  *Controller_Y)
{
  D_Work_Controller_T *Controller_DWork = ((D_Work_Controller_T *)
    Controller_M->dwork);
  BlockIO_Controller_T *Controller_B = ((BlockIO_Controller_T *)
    Controller_M->blockIO);
  InstP_Controller_T *Controller_InstP = Controller_M->Controller_InstP_ref;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) Controller_B), 0,
                sizeof(BlockIO_Controller_T));

  /* states (dwork) */
  (void) memset((void *)Controller_DWork, 0,
                sizeof(D_Work_Controller_T));

  /* external inputs */
  Controller_U->e = 0.0;

  /* external outputs */
  (void) memset((void *)Controller_Y, 0,
                sizeof(ExternalOutputs_Controller_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Controller_InitializeDataMapInfo(Controller_M, Controller_M->blockIO);

  /* Assign pointer for instance parameters, Block: '<Root>/ModelRef1' */
  Controller_DWork->ModelRef1_InstanceData.rtm.ControllerRef_InstP_ref =
    &Controller_M->Controller_InstP_ref->InstP_ModelRef1;

  /* Assign pointer for instance parameters, Block: '<Root>/ModelRef2' */
  Controller_DWork->ModelRef2_InstanceData.rtm.ControllerRef_InstP_ref =
    &Controller_M->Controller_InstP_ref->InstP_ModelRef2;

  /* Model Initialize function for ModelReference Block: '<Root>/ModelRef1' */
  ControllerRef_initialize(rtmGetErrorStatusPointer(Controller_M),
    &(Controller_DWork->ModelRef1_InstanceData.rtm),
    &(Controller_DWork->ModelRef1_InstanceData.rtb),
    &(Controller_DWork->ModelRef1_InstanceData.rtdw),
    &(Controller_M->DataMapInfo.mmi), "Controller/ModelRef1", 0, -1);

  /* Model Initialize function for ModelReference Block: '<Root>/ModelRef2' */
  ControllerRef_initialize(rtmGetErrorStatusPointer(Controller_M),
    &(Controller_DWork->ModelRef2_InstanceData.rtm),
    &(Controller_DWork->ModelRef2_InstanceData.rtb),
    &(Controller_DWork->ModelRef2_InstanceData.rtdw),
    &(Controller_M->DataMapInfo.mmi), "Controller/ModelRef2", 1, -1);

  /* InitializeConditions for UnitDelay: '<Root>/AlgLoop' */
  Controller_DWork->AlgLoop_DSTATE = Controller_P.AlgLoop_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  Controller_DWork->DiscreteTimeIntegrator_DSTATE =
    Controller_P.DiscreteTimeIntegrator_IC;
}

/* Model terminate function */
void Controller_terminate(RT_MODEL_Controller_T *const Controller_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(Controller_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
