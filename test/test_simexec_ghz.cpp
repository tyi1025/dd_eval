#include "QuantumComputation.hpp"
#include "algorithms/Entanglement.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/DeterministicNoiseSimExecutor.hpp"
#include "executors/HybridSimulatorAmplitudeExecutor.hpp"
#include "executors/HybridSimulatorDDExecutor.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"
#include "executors/UnitarySimRecursiveExecutor.hpp"
#include "executors/UnitarySimSequentialExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

// Other executors excluded because 128 qubits still have under 1s execution
// time

TEST(SimExecTestGHZ, DeterministicNoiseSimExec) {
  auto deterministicNoiseSimExecutor =
      std::make_unique<DeterministicNoiseSimExecutor>();
  auto                 qc = std::make_unique<qc::Entanglement>(5);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = deterministicNoiseSimExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestGHZ, HybridSimulatorAmplitudeExec) {
  auto hybridSimulatorAmplitudeExecutor =
      std::make_unique<HybridSimulatorAmplitudeExecutor>();
  auto                 qc = std::make_unique<qc::Entanglement>(10);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorAmplitudeExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestGHZ, HybridSimulatorDDExec) {
  auto hybridSimulatorDDExecutor =
      std::make_unique<HybridSimulatorDDExecutor>();
  auto                 qc = std::make_unique<qc::Entanglement>(8);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorDDExecutor->execute(simulationTask);
  std::cout << result << "\n";
}
