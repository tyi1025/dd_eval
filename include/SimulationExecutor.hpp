#pragma once

#include "Executor.hpp"
#include "SimulationTask.hpp"

class SimulationExecutor : public Executor {
public:
  SimulationExecutor() = default;

  const std::unique_ptr<SimulationTask>& getMTask();

  void setTask(std::unique_ptr<SimulationTask>& task);

private:
  std::unique_ptr<SimulationTask> mTask;
};
