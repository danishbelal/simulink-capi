# I really need to script this task...

set(ControllerPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-tlc-playground/Controller_ert_rtw")

set(ControllerSources "${ControllerPath}/Controller.c"
                         "${ControllerPath}/Controller.h"
                         "${ControllerPath}/Controller_types.h"
                         "${ControllerPath}/Controller_private.h"
                         "${ControllerPath}/Controller_data.c"
                         "${ControllerPath}/Controller_capi.h"
                         "${ControllerPath}/Controller_capi.c"
                         "${ControllerPath}/Controller_capi_host.h")

set(ExtraPath "${CMAKE_CURRENT_SOURCE_DIR}/R2019b")
set(ExtraSources "${ExtraPath}/rtw/c/src/rtw_capi.h"
                 "${ExtraPath}/rtw/c/src/rtw_modelmap_logging.h"
                 "${ExtraPath}/rtw/c/src/rtw_modelmap.h"
                 "${ExtraPath}/simulink/include/sysran_types.h")

# Submodel Sources
set(ControllerRefPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-tlc-playground/slprj/ert/ControllerRef")
set(ControllerRefSources "${ControllerRefPath}/ControllerRef.c"
                         "${ControllerRefPath}/ControllerRef.h"
                         "${ControllerRefPath}/ControllerRef_private.h"
                         "${ControllerRefPath}/ControllerRef_types.h"
                         "${ControllerRefPath}/ControllerRef_capi.c"
                         "${ControllerRefPath}/ControllerRef_capi.h"
                         "${ControllerRefPath}/ControllerRef_capi_host.h")

set(ControllerRefRefPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-tlc-playground/slprj/ert/ControllerRefRef")
set(ControllerRefRefSources "${ControllerRefRefPath}/ControllerRefRef.c"
                            "${ControllerRefRefPath}/ControllerRefRef.h"
                            "${ControllerRefRefPath}/ControllerRefRef_capi.c"
                            "${ControllerRefRefPath}/ControllerRefRef_capi.h"
                            "${ControllerRefRefPath}/ControllerRefRef_capi_host.h"
                            "${ControllerRefRefPath}/ControllerRefRef_private.h"
                            "${ControllerRefRefPath}/ControllerRefRef_types.h")

# Shared Sources
set(SharedPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-tlc-playground/slprj/ert/_sharedutils")
set(SharedSouces "${SharedPath}/builtin_typeid_types.h"
                 "${SharedPath}/rt_defines.h"
                 "${SharedPath}/rtwtypes.h")

set(AllIncludes "${ControllerPath}"
                "${ControllerRefPath}"
                "${ControllerRefRefPath}"
                "${ExtraPath}"
                "${SharedPath}"
                "${ExtraPath}/rtw/c/src/"
                "${ExtraPath}/simulink/include")

set(AllSources "${ControllerSources}"
               "${ControllerRefSources}"
               "${ControllerRefRefSources}"
               "${SharedSources}")
#set(CControllerInclude "${AllIncludes}" PARENT_SCOPE)

add_library(Controller "${AllSources}")
target_include_directories(Controller PUBLIC "${AllIncludes}")