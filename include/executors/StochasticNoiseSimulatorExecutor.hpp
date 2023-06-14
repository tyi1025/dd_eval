#pragma once

#include "Executor.hpp"
#include "tasks/SimulationTask.hpp"

class StochasticNoiseSimulatorExecutor : public Executor<SimulationTask> {
public:
  json execute(const SimulationTask& task) override;

  [[nodiscard]] std::string getIdentifier() const override {
    return "stochastic_noise_simulator";
  };
};
