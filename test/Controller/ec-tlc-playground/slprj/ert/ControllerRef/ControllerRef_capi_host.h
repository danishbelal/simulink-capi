#ifndef RTW_HEADER_ControllerRef_cap_host_h_
#define RTW_HEADER_ControllerRef_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
#include "ControllerRefRef_capi_host.h"

typedef struct
{
  rtwCAPI_ModelMappingInfo mmi;
  rtwCAPI_ModelMappingInfo *childMMI[1];
  ControllerRefRef_host_DataMapInfo_T child0;
}
ControllerRef_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C"
{

#endif

  void ControllerRef_host_InitializeDataMapInfo(ControllerRef_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                /* RTW_HEADER_ControllerRef_cap_host_h_ */

/* EOF: ControllerRef_capi_host.h */
