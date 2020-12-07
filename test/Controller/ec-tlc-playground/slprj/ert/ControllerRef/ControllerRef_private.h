/*
 * File: ControllerRef_private.h
 *
 * Code generated for Simulink model 'ControllerRef'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Dec  4 11:15:03 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ControllerRef_private_h_
#define RTW_HEADER_ControllerRef_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetControllerRef_InstP_ref
# define rtmGetControllerRef_InstP_ref(rtm) ((rtm)->ControllerRef_InstP_ref)
#endif

#ifndef rtmSetControllerRef_InstP_ref
# define rtmSetControllerRef_InstP_ref(rtm, val) ((rtm)->ControllerRef_InstP_ref = (val))
#endif

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

extern Parameters_ControllerRef_T ControllerRef_P;

#endif                                 /* RTW_HEADER_ControllerRef_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
