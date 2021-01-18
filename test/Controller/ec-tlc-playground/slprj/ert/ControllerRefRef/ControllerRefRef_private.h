/*
 * File: ControllerRefRef_private.h
 *
 * Code generated for Simulink model 'ControllerRefRef'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Jan  8 15:54:36 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ControllerRefRef_private_h_
#define RTW_HEADER_ControllerRefRef_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
# define rtmGetErrorStatusPointer(rtm) (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
# define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

extern Parameters_ControllerRefRef_T ControllerRefRef_P;

#endif                              /* RTW_HEADER_ControllerRefRef_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
