#include "QuantumComputation.hpp"
#include "algorithms/Grover.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/UnitarySimRecursiveExecutor.hpp"
#include "executors/UnitarySimSequentialExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

TEST(SimExecBenchmarkGrover, CircuitSimulatorExec) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 25;
  auto                 qc       = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}

TEST(SimExecBenchmarkGrover, UnitarySimSequentialExec) {
  auto unitarySimSequentialExecutor =
      std::make_unique<UnitarySimSequentialExecutor>();
  std::size_t const    n  = 22;
  auto                 qc = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimSequentialExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}

TEST(SimExecBenchmarkGrover, UnitarySimRecursiveExec) {
  auto unitarySimRecursiveExecutor =
      std::make_unique<UnitarySimRecursiveExecutor>();
  std::size_t const    n  = 22;
  auto                 qc = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimRecursiveExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}
