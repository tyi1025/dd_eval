#pragma once

#include "Executor.hpp"
#include "tasks/SimulationTask.hpp"

class UnitarySimSequentialExecutor : public Executor<SimulationTask> {
public:
  json execute(const SimulationTask& task) override;

  [[nodiscard]] std::string getIdentifier() const override {
    return "unitary_simulator_sequential";
  };
};
