#pragma once

#include "DeterministicNoiseSimulator.hpp"
#include "SimulationExecutor.hpp"

class DeterministicNoiseSimExecutor
    : public SimulationExecutor<DeterministicNoiseSimulator<>> {
public:
  [[nodiscard]] std::string getIdentifier() const override {
    return "deterministic_noise_simulator";
  }

  std::unique_ptr<DeterministicNoiseSimulator<>>
  constructSimulator(std::unique_ptr<qc::QuantumComputation>& qc) override;

  json runSimulator(
      std::unique_ptr<DeterministicNoiseSimulator<>> simulator) override;
};
