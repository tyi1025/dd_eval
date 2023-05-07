# set required cmake version
cmake_minimum_required(VERSION 3.19)

# This avoids googletest complaining that this (IPO) policy is not set
cmake_policy(SET CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

project(
  DDEval
  LANGUAGES CXX
  DESCRIPTION "Evaluating the performance of the MQT DD Package")

# check whether `modulename` is correctly cloned in the `extern` directory.
macro(CHECK_SUBMODULE_PRESENT modulename)
  if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/${modulename}/CMakeLists.txt")
    message(
      FATAL_ERROR
        "${modulename} submodule not cloned properly. \
        Please run `git submodule update --init --recursive` \
        from the main project directory")
  endif()
endmacro()

check_submodule_present(ddsim)
check_submodule_present(qcec)

# add main library code
add_subdirectory(src)

# add test code
option(BUILD_DD_EVAL_TESTS "Also build tests for DDEval project")
if(BUILD_DD_EVAL_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(test)
endif()
