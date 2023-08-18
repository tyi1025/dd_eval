#include "algorithms/BernsteinVazirani.hpp"
#include "algorithms/Entanglement.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/QFT.hpp"
#include "algorithms/QPE.hpp"
#include "algorithms/RandomCliffordCircuit.hpp"
#include "algorithms/WState.hpp"
#include "executors/UnitarySimulatorExecutor.hpp"

#include "gtest/gtest.h"

class UniSimExecTest : public testing::Test {
protected:
  void TearDown() override {}
  void SetUp() override {}
};

TEST_F(UniSimExecTest, GHZ) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 5;
  auto                 qc       = std::make_unique<qc::Entanglement>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, BernsteinVazirani) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 3;
  auto                 qc = std::make_unique<qc::BernsteinVazirani>(n, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, QPEExact) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 3;
  auto                 qc       = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, QPEInexact) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 4;
  auto                 qc       = std::make_unique<qc::QPE>(n, false, false);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, QFT) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 4;
  auto                 qc       = std::make_unique<qc::QFT>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, QFTNonZeroInput) {
  auto unitarySimulatorExecutor  = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const n            = 5;
  auto              statePrepQFT = qc::QuantumComputation(n);
  auto              actualQft    = qc::QFT(n);
  statePrepQFT.emplace_back(actualQft.asCompoundOperation());
  qc::CircuitOptimizer::flattenOperations(statePrepQFT);
  std::unique_ptr<qc::QuantumComputation> qft(
      new qc::QuantumComputation(std::move(statePrepQFT)));
  SimulationTask const simulationTask(std::move(qft));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, Grover) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 7;
  auto                 qc       = std::make_unique<qc::Grover>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, RandomCliffordCircuit) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 7;
  auto                 qc = std::make_unique<qc::RandomCliffordCircuit>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(UniSimExecTest, WState) {
  auto unitarySimulatorExecutor = std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n        = 6;
  auto                 qc       = std::make_unique<qc::WState>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto result = unitarySimulatorExecutor->execute(simulationTask);
  std::cout << result << "\n";
}
