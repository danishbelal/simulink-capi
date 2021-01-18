/*
 * File: Controller_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Controller_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "Controller.h"
#include "Controller_capi.h"
#include "Controller_private.h"
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
    0, 0, TARGET_STRING("Controller/Discrete-Time Integrator"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    1, 0, TARGET_STRING("Controller/ConfigMW1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    2, 0, TARGET_STRING("Controller/ConfigMW2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    3, 0, TARGET_STRING("Controller/MatGain"),
    TARGET_STRING(""), 0, 0, 1, 0, 0
  },

  {
    4, 0, TARGET_STRING("Controller/SuperDuperGainBlock"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    5, 0, TARGET_STRING("Controller/ModelRef1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    6, 0, TARGET_STRING("Controller/ModelRef2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    7, 0, TARGET_STRING("Controller/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    8, 0, TARGET_STRING("Controller/Sum3"),
    TARGET_STRING(""), 0, 0, 0, 0, 0
  },

  {
    9, 0, TARGET_STRING("Controller/Sum4"),
    TARGET_STRING(""), 0, 0, 1, 0, 0
  },

  {
    10, 0, TARGET_STRING("Controller/Sum5"),
    TARGET_STRING(""), 0, 0, 1, 0, 0
  },

  {
    11, 0, TARGET_STRING("Controller/AlgLoop"),
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
    12, TARGET_STRING("Controller/Constant"),
    TARGET_STRING("Value"), 0, 1, 0
  },

  {
    13, TARGET_STRING("Controller/Discrete-Time Integrator"),
    TARGET_STRING("gainval"), 0, 0, 0
  },

  {
    14, TARGET_STRING("Controller/Discrete-Time Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0
  },

  {
    15, TARGET_STRING("Controller/ConfigMW1"),
    TARGET_STRING("Gain"), 0, 0, 0
  },

  {
    16, TARGET_STRING("Controller/ConfigMW2"),
    TARGET_STRING("Gain"), 0, 0, 0
  },

  {
    17, TARGET_STRING("Controller/SuperDuperGainBlock"),
    TARGET_STRING("Gain"), 0, 0, 0
  },

  {
    18, TARGET_STRING("Controller/ModelRef1"),
    TARGET_STRING("SubmodelConfig"), 1, 0, 0
  },

  {
    19, TARGET_STRING("Controller/ModelRef2"),
    TARGET_STRING("SubmodelConfig"), 1, 0, 0
  },

  {
    20, TARGET_STRING("Controller/AlgLoop"),
    TARGET_STRING("InitialCondition"), 0, 0, 0
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
    21, -1, TARGET_STRING("Controller/Discrete-Time\nIntegrator"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0
  },

  {
    22, -1, TARGET_STRING("Controller/AlgLoop"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0
  },

  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[] =
{
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  {
    23, TARGET_STRING("mMatrix"), 0, 1, 0
  },

  {
    24, TARGET_STRING("X3_DD"), 0, 2, 0
  },

  {
    25, TARGET_STRING("X4_DD"), 0, 3, 0
  },

  {
    0, (NULL), 0, 0, 0
  }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void Controller_InitializeDataAddr(void* dataAddr[],
  RT_MODEL_Controller_T *const Controller_M, BlockIO_Controller_T *Controller_B,
  D_Work_Controller_T *Controller_DWork, InstP_Controller_T* Controller_InstP)
{
  dataAddr[0] = (void*) (&Controller_B->DiscreteTimeIntegrator);
  dataAddr[1] = (void*) (&Controller_B->ConfigMW1);
  dataAddr[2] = (void*) (&Controller_B->ConfigMW2);
  dataAddr[3] = (void*) (&Controller_B->MatGain[0]);
  dataAddr[4] = (void*) (&Controller_B->SuperDuperGainBlock);
  dataAddr[5] = (void*) (&Controller_B->ModelRef1);
  dataAddr[6] = (void*) (&Controller_B->ModelRef2);
  dataAddr[7] = (void*) (&Controller_B->Sum);
  dataAddr[8] = (void*) (&Controller_B->Sum3);
  dataAddr[9] = (void*) (&Controller_B->Sum4[0]);
  dataAddr[10] = (void*) (&Controller_B->Sum5[0]);
  dataAddr[11] = (void*) (&Controller_B->AlgLoop);
  dataAddr[12] = (void*) (&Controller_P.Constant_Value[0]);
  dataAddr[13] = (void*) (&Controller_P.DiscreteTimeIntegrator_gainval);
  dataAddr[14] = (void*) (&Controller_P.DiscreteTimeIntegrator_IC);
  dataAddr[15] = (void*) (&Controller_P.ConfigMW1_Gain);
  dataAddr[16] = (void*) (&Controller_P.ConfigMW2_Gain);
  dataAddr[17] = (void*) (&Controller_P.SuperDuperGainBlock_Gain);
  dataAddr[18] = (void*) (&Controller_M->
    Controller_InstP_ref->InstP_ModelRef1.SubmodelConfig);
  dataAddr[19] = (void*) (&Controller_M->
    Controller_InstP_ref->InstP_ModelRef2.SubmodelConfig);
  dataAddr[20] = (void*) (&Controller_P.AlgLoop_InitialCondition);
  dataAddr[21] = (void*) (&Controller_DWork->DiscreteTimeIntegrator_DSTATE);
  dataAddr[22] = (void*) (&Controller_DWork->AlgLoop_DSTATE);
  dataAddr[23] = (void*) (&Controller_InstP->mMatrix[0]);
  dataAddr[24] = (void*) (rtP_X3_DD);
  dataAddr[25] = (void*) (rtP_X4_DD);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void Controller_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void Controller_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
  loggingPtrs[1] = (NULL);
  loggingPtrs[2] = (NULL);
  loggingPtrs[3] = (NULL);
  loggingPtrs[4] = (NULL);
  loggingPtrs[5] = (NULL);
  loggingPtrs[6] = (NULL);
  loggingPtrs[7] = (NULL);
  loggingPtrs[8] = (NULL);
  loggingPtrs[9] = (NULL);
  loggingPtrs[10] = (NULL);
  loggingPtrs[11] = (NULL);
  loggingPtrs[12] = (NULL);
  loggingPtrs[13] = (NULL);
  loggingPtrs[14] = (NULL);
  loggingPtrs[15] = (NULL);
  loggingPtrs[16] = (NULL);
  loggingPtrs[17] = (NULL);
  loggingPtrs[18] = (NULL);
  loggingPtrs[19] = (NULL);
  loggingPtrs[20] = (NULL);
  loggingPtrs[21] = (NULL);
  loggingPtrs[22] = (NULL);
  loggingPtrs[23] = (NULL);
  loggingPtrs[24] = (NULL);
  loggingPtrs[25] = (NULL);
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
  },

  {
    rtwCAPI_MATRIX_COL_MAJOR, 2, 2, 0
  },

  {
    rtwCAPI_MATRIX_COL_MAJOR_ND, 4, 3, 0
  },

  {
    rtwCAPI_MATRIX_COL_MAJOR_ND, 7, 3, 0
  }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[] =
{
  1,                                   /* 0 */
  1,                                   /* 1 */
  3,                                   /* 2 */
  3,                                   /* 3 */
  3,                                   /* 4 */
  3,                                   /* 5 */
  3,                                   /* 6 */
  4,                                   /* 7 */
  4,                                   /* 8 */
  4                                    /* 9 */
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
    rtBlockSignals, 12,
    (NULL), 0,
    (NULL), 0
  },

  {
    rtBlockParameters, 9,
    rtModelParameters, 2
  },

  {
    rtBlockStates, 2
  },

  {
    rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray
  },
  "float",

  {
    2019395021U,
    3993080173U,
    1208987042U,
    1815444537U
  },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  Controller_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void Controller_InitializeDataMapInfo(RT_MODEL_Controller_T *const Controller_M,
  BlockIO_Controller_T *Controller_B)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(Controller_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(Controller_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(Controller_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  Controller_InitializeDataAddr(Controller_M->DataMapInfo.dataAddress,
    Controller_M, Controller_M->blockIO, Controller_M->dwork,
    Controller_M->Controller_InstP_ref);
  rtwCAPI_SetDataAddressMap(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  Controller_InitializeVarDimsAddr(Controller_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(Controller_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(Controller_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  Controller_InitializeLoggingFunctions(Controller_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(Controller_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.childMMI);
  rtwCAPI_SetChildMMIArrayLen(Controller_M->DataMapInfo.mmi, 2);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void Controller_host_InitializeDataMapInfo(Controller_host_DataMapInfo_T
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
    ControllerRef_host_InitializeDataMapInfo(&(dataMap->child0),
      "Controller/ModelRef1");
    dataMap->childMMI[1] = &(dataMap->child1.mmi);
    ControllerRef_host_InitializeDataMapInfo(&(dataMap->child1),
      "Controller/ModelRef2");
    rtwCAPI_SetChildMMIArray(dataMap->mmi, dataMap->childMMI);
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 2);
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
