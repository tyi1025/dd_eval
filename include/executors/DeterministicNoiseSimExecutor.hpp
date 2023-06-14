#pragma once

#include "Executor.hpp"
#include "tasks/SimulationTask.hpp"

class DeterministicNoiseSimExecutor : public Executor<SimulationTask> {
public:
  json execute(const SimulationTask& task) override;

  [[nodiscard]] std::string getIdentifier() const override {
    return "deterministic_noise_simulator";
  };
};
