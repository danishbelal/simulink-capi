/*
 * File: Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <string.h>
#include "rtw_modelmap.h"
#ifndef Controller_COMMON_INCLUDES_
# define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

#include "Controller_types.h"

/* Child system includes */
#include "ControllerRef.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
# define rtmGetErrorStatusPointer(rtm) ((const char_T **)(&((rtm)->errorStatus)))
#endif

/* Block signals (default storage) */
typedef struct
{
  real_T MatGain[9];                   /* '<Root>/MatGain' */
  real_T Model;                        /* '<Root>/Model' */
  real_T Sum4[9];                      /* '<Root>/Sum4' */
  real_T ConfigDDGain;                 /* '<Root>/ConfigDDGain' */
  real_T Sum3[9];                      /* '<Root>/Sum3' */
  real_T ConfigGain;                   /* '<Root>/ConfigGain' */
  real_T AlgebraicLoopBreaker;         /* '<Root>/AlgebraicLoopBreaker' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T SuperDuperGainBlock;          /* '<Root>/SuperDuperGainBlock' */
  real_T DiscreteTimeIntegrator;       /* '<Root>/Discrete-Time Integrator' */
}
BlockIO_Controller_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  real_T AlgebraicLoopBreaker_DSTATE;  /* '<Root>/AlgebraicLoopBreaker' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  rtMdlrefDWork_ControllerRef_T Model_InstanceData;/* '<Root>/Model' */
}
D_Work_Controller_T;

/* instance parameters, for system '<Root>' */
typedef struct
{
  InstP_ControllerRef_T InstP_Model;   /* '<Root>/Model' */
}
InstP_Controller_T;

/* External inputs (root inport signals with default storage) */
typedef struct
{
  real_T e;                            /* '<Root>/e' */
}
ExternalInputs_Controller_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
  real_T y;                            /* '<Root>/y' */
  real_T y_m[9];                       /* '<Root>/ScaledInput' */
  real_T X3[27];                       /* '<Root>/X3' */
  real_T X4[64];                       /* '<Root>/X4' */
}
ExternalOutputs_Controller_T;

/* Parameters (default storage) */
struct Parameters_Controller_T_
{
  ConfigBus ModelConfig;               /* Variable: ModelConfig
                                        * Referenced by: '<Root>/ConfigGain'
                                        */
  real_T mMatrix[9];                   /* Variable: mMatrix
                                        * Referenced by: '<Root>/MatGain'
                                        */
  real_T Constant_Value[9];            /* Expression: eye(3)
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T ConfigDDGain_Gain;            /* Expression: Config3_DD(3,3,3).Gain
                                        * Referenced by: '<Root>/ConfigDDGain'
                                        */
  real_T AlgebraicLoopBreaker_InitialCon;/* Expression: 0
                                          * Referenced by: '<Root>/AlgebraicLoopBreaker'
                                          */
  real_T SuperDuperGainBlock_Gain;     /* Expression: 2
                                        * Referenced by: '<Root>/SuperDuperGainBlock'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<Root>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T
{
  const char_T * volatile errorStatus;
  BlockIO_Controller_T *blockIO;
  D_Work_Controller_T *dwork;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct
  {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[23];
    int32_T* vardimsAddress[23];
    RTWLoggingFcnPtr loggingPtrs[23];
    rtwCAPI_ModelMappingInfo* childMMI[1];
  }
  DataMapInfo;

  InstP_Controller_T *Controller_InstP_ref;
};

/* Block parameters (default storage) */
extern Parameters_Controller_T Controller_P;

/* Model block global parameters (default storage) */
extern real_T rtP_X3_DD[27];           /* Variable: X3_DD
                                        * Referenced by: '<Root>/Constant1'
                                        */
extern real_T rtP_X4_DD[64];           /* Variable: X4_DD
                                        * Referenced by: '<Root>/Constant2'
                                        */

/* Model entry point functions */
extern void Controller_initialize(RT_MODEL_Controller_T *const Controller_M,
  ExternalInputs_Controller_T *Controller_U, ExternalOutputs_Controller_T
  *Controller_Y);
extern void Controller_step(RT_MODEL_Controller_T *const Controller_M,
  ExternalInputs_Controller_T *Controller_U, ExternalOutputs_Controller_T
  *Controller_Y);
extern void Controller_terminate(RT_MODEL_Controller_T *const Controller_M);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Controller_GetCAPIStaticMap(void);

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
 * '<Root>' : 'Controller'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
