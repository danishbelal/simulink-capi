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
    GIT_TAG release-1.10.0)
  FetchContent_GetProperties(gtest)
  if(NOT gtest_POPULATED)
    message("Fetching googletest")
    FetchContent_Populate(gtest)
    add_subdirectory("${gtest_SOURCE_DIR}" "${gtest_BINARY_DIR}")
  endif()
endfunction()