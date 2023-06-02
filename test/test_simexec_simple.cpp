#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(DDSIMExecSimpleTest, SimpleCircuit) {
  using namespace qc::literals;
  auto qc = std::make_unique<qc::QuantumComputation>(2U);
  qc->h(0U);
  qc->x(1U, 0_pc);

  auto simulationTask = std::make_unique<SimulationTask>(std::move(qc));
  auto circuitSimulatorExecutor =
      std::make_unique<CircuitSimulatorExecutor>(std::move(simulationTask));
  json const result = circuitSimulatorExecutor->executeTask();
  EXPECT_FALSE(result.contains("01"));
  EXPECT_FALSE(result.contains("10"));
}
