#pragma once

#include "SimulationExecutor.hpp"
#include "StochasticNoiseSimulator.hpp"

class StochasticNoiseSimulatorExecutor
    : public SimulationExecutor<StochasticNoiseSimulator<>> {
public:
  [[nodiscard]] std::string getIdentifier() const override {
    return "stochastic_noise_simulator";
  };

  std::unique_ptr<StochasticNoiseSimulator<>>
  constructSimulator(const SimulationTask& task) override;

  json
  runSimulator(std::unique_ptr<StochasticNoiseSimulator<>> simulator) override;
};
