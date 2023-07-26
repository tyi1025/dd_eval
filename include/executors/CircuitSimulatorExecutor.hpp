#pragma once

#include "CircuitSimulator.hpp"
#include "SimulationExecutor.hpp"

class CircuitSimulatorExecutor : public SimulationExecutor<CircuitSimulator<>> {
public:
  [[nodiscard]] std::string getIdentifier() const override {
    return "circuit_simulator";
  };

  std::unique_ptr<CircuitSimulator<>>
  constructSimulator(const SimulationTask& task) override;

  json runSimulator(std::unique_ptr<CircuitSimulator<>> simulator) override;
};
