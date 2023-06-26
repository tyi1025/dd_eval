#include "QuantumComputation.hpp"
#include "algorithms/Grover.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/UnitarySimRecursiveExecutor.hpp"
#include "executors/UnitarySimSequentialExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

TEST(SimExecTestGrover, CircuitSimulatorExec) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 7;
  auto                 qc       = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestGrover, UnitarySimSequentialExec) {
  auto unitarySimSequentialExecutor =
      std::make_unique<UnitarySimSequentialExecutor>();
  std::size_t const    n  = 3;
  auto                 qc = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimSequentialExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestGrover, UnitarySimRecursiveExec) {
  auto unitarySimRecursiveExecutor =
      std::make_unique<UnitarySimRecursiveExecutor>();
  std::size_t const    n  = 4;
  auto                 qc = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimRecursiveExecutor->execute(simulationTask);
  std::cout << result << "\n";
}
