#include "QuantumComputation.hpp"
#include "algorithms/BernsteinVazirani.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/HybridSimulatorExecutor.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

TEST(SimExecBenchmarkBerstein, HybridSimulatorAmplitudeExec) {
  auto hybridSimulatorAmplitudeExecutor =
      std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n  = 25;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorAmplitudeExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}

TEST(SimExecBenchmarkBerstein, HybridSimulatorDDExec) {
  auto hybridSimulatorDDExecutor = std::make_unique<HybridSimulatorExecutor>();
  hybridSimulatorDDExecutor->setRunAmplitude(false);
  hybridSimulatorDDExecutor->setRunDd(true);
  std::size_t const    n  = 40;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = hybridSimulatorDDExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}

TEST(SimExecBenchmarkBerstein, StochasticNoiseSimulatorExec) {
  auto stochasticNoiseSimulatorExecutor =
      std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n  = 30;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = stochasticNoiseSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() >
              1000000);
  EXPECT_TRUE(result["construction_time"].get<int>() +
                  result["execution_time"].get<int>() <
              300000000);
}

// Gives "C++ exception with description "Unsupported non-unitary functionality
// 'Rst '." thrown in the test body." when run in dynamic
