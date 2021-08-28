/*
 * File: ControllerRef_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "ControllerRef_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "ControllerRef.h"
#include "ControllerRef_capi.h"
#include "ControllerRef_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static rtwCAPI_Signals rtBlockSignals[] =
{
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  {
    0, 1, TARGET_STRING("ControllerRef/ConfigGain"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    1, 1, TARGET_STRING("ControllerRef/NormalGain"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    2, 1, TARGET_STRING("ControllerRef/Model"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    3, 1, TARGET_STRING("ControllerRef/Sum1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static rtwCAPI_BlockParameters rtBlockParameters[] =
{
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  {
    4, TARGET_STRING("ControllerRef/NormalGain"),
    TARGET_STRING("Gain"), 0, 0, 0
  },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Block states information */
static rtwCAPI_States rtBlockStates[] =
{
  /* addrMapIndex, contStateStartIndex, blockPath,
   * stateName, pathAlias, dWorkIndex, dataTypeIndex, dimIndex,
   * fixPtIdx, sTimeIndex, isContinuous, hierInfoIdx, flatElemIdx
   */
  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[] =
{
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  {
    5, TARGET_STRING("SubmodelConfig"), 1, 0, 0
  },

  {
    0, (NULL), 0, 0, 0
  }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void ControllerRef_InitializeDataAddr(void* dataAddr[],
  rtB_ControllerRef_T *localB, InstP_ControllerRef_T *ControllerRef_InstP_arg)
{
  dataAddr[0] = (void*) (&localB->ConfigGain);
  dataAddr[1] = (void*) (&localB->NormalGain);
  dataAddr[2] = (void*) (&localB->Model);
  dataAddr[3] = (void*) (&localB->Sum1);
  dataAddr[4] = (void*) (&ControllerRef_P.NormalGain_Gain);
  dataAddr[5] = (void*) (&ControllerRef_InstP_arg->SubmodelConfig);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void ControllerRef_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void ControllerRef_InitializeLoggingFunctions(RTWLoggingFcnPtr
  loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
  loggingPtrs[1] = (NULL);
  loggingPtrs[2] = (NULL);
  loggingPtrs[3] = (NULL);
  loggingPtrs[4] = (NULL);
  loggingPtrs[5] = (NULL);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] =
{
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  {
    "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0, 0
  },

  {
    "struct", "ConfigBus", 2, 1, sizeof(ConfigBus), SS_STRUCT, 0, 0, 0
  }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] =
{
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  {
    (NULL), 0, 0, 0, 0
  },

  {
    "Gain", rt_offsetof(ConfigBus, Gain), 0, 0, 0
  },

  {
    "SomeOtherMember", rt_offsetof(ConfigBus, SomeOtherMember), 0, 0, 0
  }
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static rtwCAPI_DimensionMap rtDimensionMap[] =
{
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  {
    rtwCAPI_SCALAR, 0, 2, 0
  }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[] =
{
  1,                                   /* 0 */
  1                                    /* 1 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] =
{
  0.01, 0.0
};

/* Fixed Point Map */
static rtwCAPI_FixPtMap rtFixPtMap[] =
{
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  {
    (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0
  },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static rtwCAPI_SampleTimeMap rtSampleTimeMap[] =
{
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  {
    (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    0, 0
  }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic =
{
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  {
    rtBlockSignals, 4,
    (NULL), 0,
    (NULL), 0
  },

  {
    rtBlockParameters, 1,
    rtModelParameters, 1
  },

  {
    rtBlockStates, 0
  },

  {
    rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray
  },
  "float",

  {
    368944127U,
    1245914176U,
    556516747U,
    313082824U
  },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  ControllerRef_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void ControllerRef_InitializeDataMapInfo(RT_MODEL_ControllerRef_T *const
  ControllerRef_M, rtB_ControllerRef_T *localB)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(ControllerRef_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(ControllerRef_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(ControllerRef_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  ControllerRef_InitializeDataAddr(ControllerRef_M->DataMapInfo.dataAddress,
    localB, ControllerRef_M->ControllerRef_InstP_ref);
  rtwCAPI_SetDataAddressMap(ControllerRef_M->DataMapInfo.mmi,
    ControllerRef_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  ControllerRef_InitializeVarDimsAddr
    (ControllerRef_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(ControllerRef_M->DataMapInfo.mmi,
    ControllerRef_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(ControllerRef_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(ControllerRef_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  ControllerRef_InitializeLoggingFunctions
    (ControllerRef_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(ControllerRef_M->DataMapInfo.mmi,
    ControllerRef_M->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(ControllerRef_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(ControllerRef_M->DataMapInfo.mmi,
    ControllerRef_M->DataMapInfo.childMMI);
  rtwCAPI_SetChildMMIArrayLen(ControllerRef_M->DataMapInfo.mmi, 1);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void ControllerRef_host_InitializeDataMapInfo(ControllerRef_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);

    /* Set reference to submodels */
    dataMap->childMMI[0] = &(dataMap->child0.mmi);
    ControllerRefRef_host_InitializeDataMapInfo(&(dataMap->child0),
      "ControllerRef/Model");
    rtwCAPI_SetChildMMIArray(dataMap->mmi, dataMap->childMMI);
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 1);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
