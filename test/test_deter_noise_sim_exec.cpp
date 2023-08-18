#include "algorithms/BernsteinVazirani.hpp"
#include "algorithms/Entanglement.hpp"
#include "algorithms/RandomCliffordCircuit.hpp"
#include "algorithms/WState.hpp"
#include "executors/DeterministicNoiseSimExecutor.hpp"

#include "gtest/gtest.h"

// Failed for BV, QPE and Grover with error message "Unsupported non-unitary
// functionality: "meas""

class DeterNoiseSimExecTest : public testing::Test {
protected:
  void TearDown() override {}
  void SetUp() override {}
};

TEST_F(DeterNoiseSimExecTest, GHZ) {
  auto simulator          = std::make_unique<DeterministicNoiseSimExecutor>();
  std::size_t const    n  = 5;
  auto                 qc = std::make_unique<qc::Entanglement>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(DeterNoiseSimExecTest, RandomCliffordCircuit) {
  auto simulator          = std::make_unique<DeterministicNoiseSimExecutor>();
  std::size_t const    n  = 7;
  auto                 qc = std::make_unique<qc::RandomCliffordCircuit>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}

TEST_F(DeterNoiseSimExecTest, WState) {
  auto simulator          = std::make_unique<DeterministicNoiseSimExecutor>();
  std::size_t const    n  = 6;
  auto                 qc = std::make_unique<qc::WState>(n);
  SimulationTask const simulationTask(std::move(qc));
  const auto           result = simulator->execute(simulationTask);
  std::cout << result << "\n";
}
