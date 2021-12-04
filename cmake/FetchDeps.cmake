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

function(FetchCleantype)
    include(FetchContent)
    # fetch cleantype
    FetchContent_Declare(cleantype
        GIT_REPOSITORY https://github.com/pthom/cleantype.git)
    FetchContent_GetProperties(cleantype)
    if(NOT cleantype_POPULATED)
        message("Fetching cleantype")
        FetchContent_Populate(cleantype)
        # DO NOT exec add_subdirectory() on this one.
    endif()
    set(CleantypeDir "${cleantype_SOURCE_DIR}/include_all_in_one/include/cleantype")
    add_library(CleanType INTERFACE)
    target_sources(CleanType INTERFACE "${CleantypeDir}/cleantype.hpp")
    target_include_directories(CleanType INTERFACE "${CleantypeDir}")
endfunction()

function(FetchGoogleTest)
  # google test
  include(FetchContent)
  FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0)
  FetchContent_GetProperties(gtest)
  if(NOT gtest_POPULATED)
    message("Fetching googletest")
    FetchContent_Populate(gtest)
    add_subdirectory("${gtest_SOURCE_DIR}" "${gtest_BINARY_DIR}")
  endif()
endfunction()