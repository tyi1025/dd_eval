#pragma once

#include "Executor.hpp"
#include "SimulationTask.hpp"

class SimulationExecutor : public Executor {
public:
  SimulationExecutor() = default;
  explicit SimulationExecutor(std::unique_ptr<SimulationTask>& task) {
    setTask(task);
  }

  const std::unique_ptr<Task>& getTask();

  void setTask(std::unique_ptr<SimulationTask>& task);

private:
  std::unique_ptr<SimulationTask> mTask;
};
