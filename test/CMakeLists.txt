# danishbelal/simulink-capi tests

set(TestDir "${CMAKE_CURRENT_SOURCE_DIR}")
set(TestSources "${TestDir}/TestCapiAccessor.cpp"
                "${TestDir}/TestCapiAccessorRef.cpp"
                "${TestDir}/TestCapiAccessorBase.cpp"
                "${TestDir}/TestCapiAccessorBase.hpp"
                "${TestDir}/TestCapiAccessorNoExceptions.cpp"
                "${TestDir}/TestBusBuilder.cpp")
set(TestIncludes "${TestDir}")

if(SLCAPI_RUN_STATIC_ANALYSIS)
    set(CMAKE_CXX_CPPCHECK "cppcheck"
                           "--enable=all")
endif()

add_subdirectory(Controller)

add_executable(Tests "${TestSources}")
target_include_directories(Tests PUBLIC "${LibDir}")
target_link_libraries(Tests PUBLIC gtest_main Controller SimulinkCAPI)

gtest_discover_tests(Tests)