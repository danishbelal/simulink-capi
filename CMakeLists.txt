cmake_minimum_required(VERSION 3.11)

project(SimulinkCAPIInterface)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(SLCAPI_RUN_STATIC_ANALYSIS "Run static analysis tools" OFF)
option(SLCAPI_RUNTIME_TYPE_CHECKING "Enable runtime type checking" ON)
option(SLCAPI_COMPILE_TESTS "Compile the tests incl. the model" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FetchDeps)

# include contains the actual library
add_subdirectory(include)

if(SLCAPI_RUNTIME_TYPE_CHECKING)
  FetchCleantype()
endif()

# Add the tests to the build.
if(SLCAPI_COMPILE_TESTS)
  include(GoogleTest)
  FetchGoogleTest()
  enable_testing()
  add_subdirectory(test)
endif()