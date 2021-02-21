# Create the Simulink- C-API Library target.
# This is what you want to link against in your
# application.
set(LibDir "${CMAKE_CURRENT_SOURCE_DIR}")
set(LibSrc "${LibDir}/CapiAccessor.hpp"
           "${LibDir}/AccessorHelper.hpp"
           "${LibDir}/ModelTraits.hpp"
           "${LibDir}/BusBuilder.hpp")

add_library(SimulinkCAPI INTERFACE)
target_sources(SimulinkCAPI INTERFACE "${LibSrc}")
target_include_directories(SimulinkCAPI INTERFACE "${LibDir}")

if(SLCAPI_RUNTIME_TYPE_CHECKING)
    target_link_libraries(SimulinkCAPI INTERFACE CleanType)
    target_compile_definitions(SimulinkCAPI INTERFACE ENABLE_RUNTIME_TYPE_CHECKING)
endif()