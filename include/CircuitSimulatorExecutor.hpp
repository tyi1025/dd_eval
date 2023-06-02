#pragma once

#include "CircuitSimulator.hpp"
#include "SimulationExecutor.hpp"

class CircuitSimulatorExecutor : public SimulationExecutor {
public:
  CircuitSimulatorExecutor() = default;
  // simulator and task must be set before use

  json        executeTask() override;
  std::string getIdentifier() override;

private:
  std::unique_ptr<CircuitSimulator<>> mCircuitSimulator;

public:
  void
  setCircuitSimulator(std::unique_ptr<CircuitSimulator<>>& circuitSimulator);
};
