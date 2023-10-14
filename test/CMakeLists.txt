if(NOT TARGET gtest OR NOT TARGET gmock)
  # Prevent overriding the parent project's compiler/linker settings on Windows
  set(gtest_force_shared_crt # cmake-lint: disable=C0103
      ON
      CACHE BOOL "" FORCE)

  # store path to googletest in variable
  set(GTEST_PATH "extern/qcec/extern/mqt-core/extern/googletest")
  add_subdirectory("${PROJECT_SOURCE_DIR}/${GTEST_PATH}" "${GTEST_PATH}"
                   EXCLUDE_FROM_ALL)
endif()
configure_file(${CMAKE_SOURCE_DIR}/test/sim_circuits.json
               ${CMAKE_CURRENT_BINARY_DIR}/sim_circuits.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/test/ver_circuits.json
               ${CMAKE_CURRENT_BINARY_DIR}/ver_circuits.json COPYONLY)
package_add_test(
  ${PROJECT_NAME}_sim_test
  ${PROJECT_NAME}
  test_simexec_simple.cpp
  test_circ_sim_exec.cpp
  test_deter_noise_sim_exec.cpp
  test_stoch_noise_sim_exec.cpp
  test_hybrid_sim_exec.cpp
  test_hybrid_sim_exec_dd.cpp
  test_uni_sim_exec.cpp
  test_uni_sim_exec_seq.cpp)
package_add_test(${PROJECT_NAME}_ver_test ${PROJECT_NAME} test_qcecexec.cpp)
