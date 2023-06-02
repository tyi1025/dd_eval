#pragma once

#include "CircuitSimulator.hpp"
#include "SimulationExecutor.hpp"

class CircuitSimulatorExecutor : public SimulationExecutor {
public:
  CircuitSimulatorExecutor() = delete;

  explicit CircuitSimulatorExecutor(
      std::unique_ptr<SimulationTask> simulationTask);

  json        executeTask() override;
  std::string getIdentifier() override;

private:
  std::unique_ptr<CircuitSimulator<>> mCircuitSimulator;
};
