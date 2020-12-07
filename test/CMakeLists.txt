# danishbelal/simulink-capi tests

set(TestDir "${CMAKE_CURRENT_SOURCE_DIR}")
set(TestSources "${TestDir}/TestCapiAccessor.cpp")
set(TestIncludes "${TestDir}")

set(ExtDir "${CMAKE_SOURCE_DIR}/external")
set(ExtSources "${ExtDir}/cleantype.hpp"
               "${ExtDir}/icecream.hpp")

if(SLCAPI_RUN_STATIC_ANALYSIS)
    set(CMAKE_CXX_CPPCHECK "cppcheck"
                           "--enable=all")
endif()

add_subdirectory(Controller)

if(SLCAPI_RUNTIME_TYPE_CHECKING)
    # Append cleantypes.hpp to testsources and add its include dir
    # (todo) redo this in a nice way
    list(APPEND TestSources "${CMAKE_SOURCE_DIR}/external/cleantype.hpp")
    list(APPEND TestIncludes "${CMAKE_SOURCE_DIR}/external")
endif()

add_executable(Tests "${TestSources}" "${ExtSources}")
target_include_directories(Tests PUBLIC "${LibDir}" "${ExtDir}")
target_link_libraries(Tests PUBLIC gtest_main Controller SimulinkCAPI)

gtest_discover_tests(Tests)