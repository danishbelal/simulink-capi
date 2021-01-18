#ifndef RTW_HEADER_Controller_cap_host_h_
#define RTW_HEADER_Controller_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
#include "ControllerRef_capi_host.h"
#include "ControllerRef_capi_host.h"

typedef struct
{
  rtwCAPI_ModelMappingInfo mmi;
  rtwCAPI_ModelMappingInfo *childMMI[2];
  ControllerRef_host_DataMapInfo_T child0;
  ControllerRef_host_DataMapInfo_T child1;
}
Controller_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C"
{

#endif

  void Controller_host_InitializeDataMapInfo(Controller_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_Controller_cap_host_h_ */

/* EOF: Controller_capi_host.h */
