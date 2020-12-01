cmake_minimum_required(VERSION 3.11)

project(SimulinkCAPIInterface)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# std::thread is required
find_package(Threads REQUIRED)

add_subdirectory(DummyModel/Cpp-Controller)

set(LibDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LibSrc "${LibDir}/CapiAccessor.hpp"
           "${LibDir}/AccessorHelper.hpp"
           "${LibDir}/cleantype.hpp")

set(Sources "src/main.cpp" "src/icecream.hpp" "${LibSrc}")

add_executable(Demo "${Sources}")
target_include_directories(Demo PUBLIC "${LibDir}" "${CppControllerInclude}")
target_link_libraries(Demo CppController)