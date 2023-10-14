#pragma once

#include "CircuitSimulator.hpp"
#include "SimulationExecutor.hpp"

class CircuitSimulatorExecutor : public SimulationExecutor<CircuitSimulator<>> {
public:
  [[nodiscard]] std::string getIdentifier() const override {
    return "circuit_simulator";
  };

  std::unique_ptr<CircuitSimulator<>>
  constructSimulator(std::unique_ptr<qc::QuantumComputation>& qc) override;

  json runSimulator(std::unique_ptr<CircuitSimulator<>> simulator) override;
};
