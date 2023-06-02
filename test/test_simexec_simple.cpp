#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(DDSIMExecSimpleTest, EmptyCircuit) {
  auto qc             = std::make_unique<qc::QuantumComputation>(2U);
  auto simulationTask = std::make_unique<SimulationTask>(std::move(qc));
  auto circuitSimulatorExecutor =
      std::make_unique<CircuitSimulatorExecutor>(std::move(simulationTask));
  json const result = circuitSimulatorExecutor->executeTask();

  EXPECT_EQ(1024, result["00"]);
}
