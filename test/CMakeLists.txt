if(NOT TARGET gtest OR NOT TARGET gmock)
  # Prevent overriding the parent project's compiler/linker settings on Windows
  set(gtest_force_shared_crt # cmake-lint: disable=C0103
      ON
      CACHE BOOL "" FORCE)

  # store path to googletest in variable
  set(GTEST_PATH "extern/qcec/extern/qfr/extern/dd_package/extern/googletest")
  add_subdirectory("${PROJECT_SOURCE_DIR}/${GTEST_PATH}" "${GTEST_PATH}"
                   EXCLUDE_FROM_ALL)
endif()
configure_file(${CMAKE_SOURCE_DIR}/test/sim_circuits.json
               ${CMAKE_CURRENT_BINARY_DIR}/sim_circuits.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/test/ver_circuits.json
               ${CMAKE_CURRENT_BINARY_DIR}/ver_circuits.json COPYONLY)
package_add_test(${PROJECT_NAME}_sim_test ${PROJECT_NAME} test_simexec.cpp)
package_add_test(${PROJECT_NAME}_ver_test ${PROJECT_NAME} test_qcecexec.cpp
                 test_qcecexec_circs.cpp)
