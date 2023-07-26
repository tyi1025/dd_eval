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
  constructSimulator(const SimulationTask& task) override;

  json runSimulator(
      std::unique_ptr<DeterministicNoiseSimulator<>> simulator) override;
};
