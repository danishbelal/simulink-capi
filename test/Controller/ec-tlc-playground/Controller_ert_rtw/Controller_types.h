/*
 * File: Controller_types.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 3.4
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Aug 25 10:24:31 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_types_h_
#define RTW_HEADER_Controller_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_ConfigBus_
#define DEFINED_TYPEDEF_FOR_ConfigBus_

typedef struct
{
  real_T Gain;
  real_T SomeOtherMember;
}
ConfigBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_TestConfiguration_
#define DEFINED_TYPEDEF_FOR_TestConfiguration_

typedef struct
{
  boolean_T TestModeEnabled;
  real_T Scaling;
}
TestConfiguration;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SignalConfiguration_
#define DEFINED_TYPEDEF_FOR_SignalConfiguration_

typedef struct
{
  real_T Amplitude;
}
SignalConfiguration;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CoreConfiguration_
#define DEFINED_TYPEDEF_FOR_CoreConfiguration_

typedef struct
{
  TestConfiguration Test;
  SignalConfiguration Signal;
}
CoreConfiguration;

#endif

/* Parameters (default storage) */
typedef struct Parameters_Controller_T_ Parameters_Controller_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Controller_T RT_MODEL_Controller_T;

#endif                                 /* RTW_HEADER_Controller_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
