#include "algorithms/BernsteinVazirani.hpp"
#include "algorithms/Entanglement.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/QPE.hpp"
#include "algorithms/RandomCliffordCircuit.hpp"
#include "algorithms/WState.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"

#include "gtest/gtest.h"

class CircSimExecTest : public testing::Test {
protected:
  void TearDown() override {}
  void SetUp() override {}
};

TEST_F(CircSimExecTest, GHZ) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 5;
  auto                 qc       = std::make_unique<qc::Entanglement>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, BernsteinVazirani) {
  auto              circSimExec = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const n           = 3;
  auto              qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = circSimExec->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, BernsteinVaziraniDyn) {
  auto circSimExecDyn     = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n  = 4;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, true);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = circSimExecDyn->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, QPEExact) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 3;
  auto                 qc       = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, QPEInexact) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 4;
  auto                 qc       = std::make_unique<qc::QPE>(n, false, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, QPEExactDyn) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 5;
  auto                 qc       = std::make_unique<qc::QPE>(n, true, true);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, QPEInexactDyn) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 4;
  auto                 qc       = std::make_unique<qc::QPE>(n, false, true);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, Grover) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 7;
  auto                 qc       = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, RandomCliffordCircuit) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 7;
  auto                 qc = std::make_unique<qc::RandomCliffordCircuit>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(CircSimExecTest, WState) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 6;
  auto                 qc       = std::make_unique<qc::WState>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}
