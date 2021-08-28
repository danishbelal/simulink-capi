/*
 * File: ControllerRefRef_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "ControllerRefRef_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "ControllerRefRef.h"
#include "ControllerRefRef_capi.h"
#include "ControllerRefRef_private.h"
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
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static rtwCAPI_BlockParameters rtBlockParameters[] =
{
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  {
    0, TARGET_STRING("ControllerRefRef/Gain"),
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
    0, (NULL), 0, 0, 0
  }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void ControllerRefRef_InitializeDataAddr(void* dataAddr[])
{
  dataAddr[0] = (void*) (&ControllerRefRef_P.Gain_Gain);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void ControllerRefRef_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void ControllerRefRef_InitializeLoggingFunctions(RTWLoggingFcnPtr
  loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] =
{
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  {
    "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0, 0
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
    (NULL), (NULL), 0, 0
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
    rtBlockSignals, 0,
    (NULL), 0,
    (NULL), 0
  },

  {
    rtBlockParameters, 1,
    rtModelParameters, 0
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
    1714127830U,
    3031097576U,
    771115033U,
    3644631290U
  },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  ControllerRefRef_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void ControllerRefRef_InitializeDataMapInfo(RT_MODEL_ControllerRefRef_T *const
  ControllerRefRef_M)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(ControllerRefRef_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(ControllerRefRef_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(ControllerRefRef_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  ControllerRefRef_InitializeDataAddr
    (ControllerRefRef_M->DataMapInfo.dataAddress);
  rtwCAPI_SetDataAddressMap(ControllerRefRef_M->DataMapInfo.mmi,
    ControllerRefRef_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  ControllerRefRef_InitializeVarDimsAddr
    (ControllerRefRef_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(ControllerRefRef_M->DataMapInfo.mmi,
    ControllerRefRef_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(ControllerRefRef_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(ControllerRefRef_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  ControllerRefRef_InitializeLoggingFunctions
    (ControllerRefRef_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(ControllerRefRef_M->DataMapInfo.mmi,
    ControllerRefRef_M->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(ControllerRefRef_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(ControllerRefRef_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(ControllerRefRef_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void ControllerRefRef_host_InitializeDataMapInfo
    (ControllerRefRef_host_DataMapInfo_T *dataMap, const char *path)
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
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
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
