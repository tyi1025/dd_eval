#include "QuantumComputation.hpp"
#include "algorithms/BernsteinVazirani.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/HybridSimulatorAmplitudeExecutor.hpp"
#include "executors/HybridSimulatorDDExecutor.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

TEST(SimExecTestBerstein, HybridSimulatorAmplitudeExec) {
  auto hybridSimulatorAmplitudeExecutor =
      std::make_unique<HybridSimulatorAmplitudeExecutor>();
  std::size_t const    n  = 3;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorAmplitudeExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestBerstein, HybridSimulatorDDExec) {
  auto hybridSimulatorDDExecutor =
      std::make_unique<HybridSimulatorDDExecutor>();
  std::size_t const    n  = 8;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorDDExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST(SimExecTestBerstein, StochasticNoiseSimulatorExec) {
  auto stochasticNoiseSimulatorExecutor =
      std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n  = 5;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = stochasticNoiseSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

// Gives "C++ exception with description "Unsupported non-unitary functionality
// 'Rst '." thrown in the test body." when run in dynamic
