#include "algorithms/BernsteinVazirani.hpp"
#include "algorithms/Entanglement.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/QPE.hpp"
#include "algorithms/RandomCliffordCircuit.hpp"
#include "algorithms/WState.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"

#include "gtest/gtest.h"

class StochNoiseSimExecTest : public testing::Test {
protected:
  void TearDown() override {}
  void SetUp() override {}
};

TEST_F(StochNoiseSimExecTest, GHZ) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 5;
  auto                 qc = std::make_unique<qc::Entanglement>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, BernsteinVazirani) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 3;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, QPEExact) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 3;
  auto                 qc = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, QPEInexact) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 4;
  auto                 qc = std::make_unique<qc::QPE>(n, false, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, Grover) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 7;
  auto                 qc = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, RandomCliffordCircuit) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 7;
  auto                 qc = std::make_unique<qc::RandomCliffordCircuit>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(StochNoiseSimExecTest, WState) {
  auto simulator         = std::make_unique<StochasticNoiseSimulatorExecutor>();
  std::size_t const    n = 6;
  auto                 qc = std::make_unique<qc::WState>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}
