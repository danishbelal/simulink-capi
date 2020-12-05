cmake_minimum_required(VERSION 3.11)

project(SimulinkCAPIInterface)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

# google test
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0)
FetchContent_MakeAvailable(gtest)

add_subdirectory(DummyModel/DummyModel2/Controller)

set(LibDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LibSrc "${LibDir}/CapiAccessor.hpp"
           "${LibDir}/AccessorHelper.hpp")

set(ExtDir "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(ExtSources "${ExtDir}/cleantype.hpp"
               "${ExtDir}/icecream.hpp")

set(TestDir "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(TestSources "${TestDir}/TestCapiAccessor.cpp")

set(Sources "${LibSrc}" "${ExtSources}" "${TestSources}")

add_executable(Tests "${Sources}")
target_include_directories(Tests PUBLIC "${LibDir}" "${ExtDir}")
target_link_libraries(Tests PUBLIC gtest_main Controller)