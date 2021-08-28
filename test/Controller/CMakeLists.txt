# Copyright (c) 2020-2021, Danish Belal.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software without
#    specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

set(ControllerPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-tlc-playground/Controller_ert_rtw")

set(ControllerSources "${ControllerPath}/Controller.c"
                         "${ControllerPath}/Controller.h"
                         "${ControllerPath}/Controller_types.h"
                         "${ControllerPath}/Controller_private.h"
                         "${ControllerPath}/Controller_data.c"
                         "${ControllerPath}/Controller_capi.h"
                         "${ControllerPath}/Controller_capi.c"
                         "${ControllerPath}/Controller_capi_host.h")

set(ExtraPath "${CMAKE_CURRENT_SOURCE_DIR}/R2020b")
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