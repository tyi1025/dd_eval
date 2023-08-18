#include "algorithms/BernsteinVazirani.hpp"
#include "algorithms/Entanglement.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/QPE.hpp"
#include "algorithms/WState.hpp"
#include "executors/HybridSimulatorExecutor.hpp"

#include "gtest/gtest.h"

// Failed for RandomCliffordCircuit with error message "Only StandardOperations
// are supported for now."

class HybridSimExecTest : public testing::Test {
protected:
  void TearDown() override {}
  void SetUp() override {}
};

TEST_F(HybridSimExecTest, GHZ) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 5;
  auto                 qc        = std::make_unique<qc::Entanglement>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(HybridSimExecTest, BernsteinVazirani) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 3;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(HybridSimExecTest, QPEExact) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 3;
  auto                 qc        = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(HybridSimExecTest, QPEInexact) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 4;
  auto                 qc        = std::make_unique<qc::QPE>(n, false, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(HybridSimExecTest, Grover) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 2;
  auto                 qc        = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(HybridSimExecTest, WState) {
  auto                 simulator = std::make_unique<HybridSimulatorExecutor>();
  std::size_t const    n         = 6;
  auto                 qc        = std::make_unique<qc::WState>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}
