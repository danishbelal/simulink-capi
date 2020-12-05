cmake_minimum_required(VERSION 3.11)

project(SimulinkCAPIInterface)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

add_subdirectory(DummyModel/Cpp-Controller)

add_subdirectory(DummyModel/DummyModel2/Controller)

set(LibDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LibSrc "${LibDir}/CapiAccessor.hpp"
           "${LibDir}/AccessorHelper.hpp")

set(ExtDir "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(ExtSources "${ExtDir}/cleantype.hpp"
               "${ExtDir}/icecream.hpp")

set(Sources "src/main.cpp" "${LibSrc}" "${ExtSources}")

add_executable(Demo "${Sources}")
target_include_directories(Demo PUBLIC "${LibDir}" "${ExtDir}")
target_link_libraries(Demo PUBLIC Controller)