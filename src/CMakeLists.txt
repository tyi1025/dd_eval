# add MQT::ddsim library
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/ddsim" "extern/ddsim"
                 EXCLUDE_FROM_ALL)

# add MQT::qcec library
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/qcec" "extern/qcec"
                 EXCLUDE_FROM_ALL)

if(NOT TARGET ${PROJECT_NAME})
  add_library(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/include/Executor.hpp
    ${PROJECT_SOURCE_DIR}/include/Results.hpp
    ${PROJECT_SOURCE_DIR}/include/SimulationTask.hpp
    ${PROJECT_SOURCE_DIR}/include/Task.hpp
    ${PROJECT_SOURCE_DIR}/include/VerificationTask.hpp
    Result.cpp
    SimulationTask.cpp
    VerificationTask.cpp
    Executor.cpp
    CircuitSimulatorExecutor.cpp
    ../include/CircuitSimulatorExecutor.hpp
    VerificationExecutor.cpp
    ../include/VerificationExecutor.hpp
    AlternatingVerificationExecutor.cpp
    ../include/AlternatingVerificationExecutor.hpp)

  # set include directories
  target_include_directories(
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_BINARY_DIR}/include)

  # link to the MQT libraries
  target_link_libraries(${PROJECT_NAME} PUBLIC MQT::ddsim MQT::qcec)

  # add MQT alias
  add_library(MQT::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
endif()
