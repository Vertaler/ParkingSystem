include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(ParkingSystem_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(ParkingSystem_setup_options)
  option(ParkingSystem_ENABLE_HARDENING "Enable hardening" ON)
  option(ParkingSystem_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    ParkingSystem_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    ParkingSystem_ENABLE_HARDENING
    OFF)

  ParkingSystem_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR ParkingSystem_PACKAGING_MAINTAINER_MODE)
    option(ParkingSystem_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(ParkingSystem_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(ParkingSystem_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(ParkingSystem_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(ParkingSystem_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(ParkingSystem_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(ParkingSystem_ENABLE_PCH "Enable precompiled headers" OFF)
    option(ParkingSystem_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(ParkingSystem_ENABLE_IPO "Enable IPO/LTO" ON)
    option(ParkingSystem_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(ParkingSystem_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(ParkingSystem_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(ParkingSystem_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(ParkingSystem_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(ParkingSystem_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(ParkingSystem_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(ParkingSystem_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(ParkingSystem_ENABLE_PCH "Enable precompiled headers" OFF)
    option(ParkingSystem_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      ParkingSystem_ENABLE_IPO
      ParkingSystem_WARNINGS_AS_ERRORS
      ParkingSystem_ENABLE_USER_LINKER
      ParkingSystem_ENABLE_SANITIZER_ADDRESS
      ParkingSystem_ENABLE_SANITIZER_LEAK
      ParkingSystem_ENABLE_SANITIZER_UNDEFINED
      ParkingSystem_ENABLE_SANITIZER_THREAD
      ParkingSystem_ENABLE_SANITIZER_MEMORY
      ParkingSystem_ENABLE_UNITY_BUILD
      ParkingSystem_ENABLE_CLANG_TIDY
      ParkingSystem_ENABLE_CPPCHECK
      ParkingSystem_ENABLE_COVERAGE
      ParkingSystem_ENABLE_PCH
      ParkingSystem_ENABLE_CACHE)
  endif()

  ParkingSystem_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (ParkingSystem_ENABLE_SANITIZER_ADDRESS OR ParkingSystem_ENABLE_SANITIZER_THREAD OR ParkingSystem_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(ParkingSystem_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(ParkingSystem_global_options)
  if(ParkingSystem_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    ParkingSystem_enable_ipo()
  endif()

  ParkingSystem_supports_sanitizers()

  if(ParkingSystem_ENABLE_HARDENING AND ParkingSystem_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR ParkingSystem_ENABLE_SANITIZER_UNDEFINED
       OR ParkingSystem_ENABLE_SANITIZER_ADDRESS
       OR ParkingSystem_ENABLE_SANITIZER_THREAD
       OR ParkingSystem_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${ParkingSystem_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${ParkingSystem_ENABLE_SANITIZER_UNDEFINED}")
    ParkingSystem_enable_hardening(ParkingSystem_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(ParkingSystem_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(ParkingSystem_warnings INTERFACE)
  add_library(ParkingSystem_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  ParkingSystem_set_project_warnings(
    ParkingSystem_warnings
    ${ParkingSystem_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(ParkingSystem_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(ParkingSystem_options)
  endif()

  include(cmake/Sanitizers.cmake)
  ParkingSystem_enable_sanitizers(
    ParkingSystem_options
    ${ParkingSystem_ENABLE_SANITIZER_ADDRESS}
    ${ParkingSystem_ENABLE_SANITIZER_LEAK}
    ${ParkingSystem_ENABLE_SANITIZER_UNDEFINED}
    ${ParkingSystem_ENABLE_SANITIZER_THREAD}
    ${ParkingSystem_ENABLE_SANITIZER_MEMORY})

  set_target_properties(ParkingSystem_options PROPERTIES UNITY_BUILD ${ParkingSystem_ENABLE_UNITY_BUILD})

  if(ParkingSystem_ENABLE_PCH)
    target_precompile_headers(
      ParkingSystem_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(ParkingSystem_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    ParkingSystem_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(ParkingSystem_ENABLE_CLANG_TIDY)
    ParkingSystem_enable_clang_tidy(ParkingSystem_options ${ParkingSystem_WARNINGS_AS_ERRORS})
  endif()

  if(ParkingSystem_ENABLE_CPPCHECK)
    ParkingSystem_enable_cppcheck(${ParkingSystem_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(ParkingSystem_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    ParkingSystem_enable_coverage(ParkingSystem_options)
  endif()

  if(ParkingSystem_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(ParkingSystem_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(ParkingSystem_ENABLE_HARDENING AND NOT ParkingSystem_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR ParkingSystem_ENABLE_SANITIZER_UNDEFINED
       OR ParkingSystem_ENABLE_SANITIZER_ADDRESS
       OR ParkingSystem_ENABLE_SANITIZER_THREAD
       OR ParkingSystem_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    ParkingSystem_enable_hardening(ParkingSystem_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
