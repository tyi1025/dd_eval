#include "CircuitSimulator.hpp"
#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(DDSIMExecSimpleTest, EmptyCircuit) {
  auto qc               = std::make_unique<qc::QuantumComputation>(2U);
  auto clonedQC         = std::make_unique<qc::QuantumComputation>(qc->clone());
  auto simulationTask   = std::make_unique<SimulationTask>(std::move(clonedQC));
  auto circuitSimulator = std::make_unique<CircuitSimulator<>>(std::move(qc));
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  circuitSimulatorExecutor->setCircuitSimulator(circuitSimulator);
  circuitSimulatorExecutor->setTask(simulationTask);
  json const result = circuitSimulatorExecutor->executeTask();

  EXPECT_EQ(1024, result["00"]);
}
