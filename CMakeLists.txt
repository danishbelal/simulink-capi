cmake_minimum_required(VERSION 3.11)

project(SimulinkCAPIInterface)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(SLCAPI_RUN_STATIC_ANALYSIS "Run static analysis tools" OFF)
option(SLCAPI_RUNTIME_TYPE_CHECKING "Enable runtime type checking" ON)
option(SLCAPI_COMPILE_TESTS "Compile the tests incl. the model" ON)

# Create the Simulink- C-API Library target.
# This is what you want to link against in your
# application.
set(LibDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LibSrc "${LibDir}/CapiAccessor.hpp"
           "${LibDir}/AccessorHelper.hpp")

include(FetchContent)
# fetch cleantype
FetchContent_Declare(cleantype
    GIT_REPOSITORY https://github.com/pthom/cleantype.git)
FetchContent_GetProperties(cleantype)
if(NOT cleantype_POPULATED)
    FetchContent_Populate(cleantype)
    # DO NOT exec add_subdirectory() on this one.
endif()
# Short name for cleantypes include dir
set(CleantypeDir "${cleantype_SOURCE_DIR}/include_all_in_one/include/cleantype")

add_library(SimulinkCAPI INTERFACE)
target_sources(SimulinkCAPI INTERFACE "${LibSrc}")
target_include_directories(SimulinkCAPI INTERFACE "${LibDir}" "${CleantypeDir}")

# Add the tests to the build.
if(SLCAPI_COMPILE_TESTS)
  include(GoogleTest)

  # google test
  FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0)
  FetchContent_GetProperties(gtest)
  if(NOT gtest_POPULATED)
    FetchContent_Populate(gtest)
    add_subdirectory("${gtest_SOURCE_DIR}" "${gtest_BINARY_DIR}")
  endif()

  enable_testing()
  add_subdirectory(test)
endif()