#pragma once

#include "Executor.hpp"
#include "SimulationTask.hpp"

class SimulationExecutor : public Executor {
public:
  SimulationExecutor() = default;

  const std::unique_ptr<SimulationTask>& getTask();

  void setTask(std::unique_ptr<SimulationTask>& task);

protected:
  std::unique_ptr<SimulationTask> mTask;
};
