#pragma once

#include "Executor.hpp"
#include "SimulationTask.hpp"

class SimulationExecutor : public Executor {
public:
  explicit SimulationExecutor(const std::shared_ptr<SimulationTask>& task) {
    setTask(task);
  };
  json executeTask() override;
};
