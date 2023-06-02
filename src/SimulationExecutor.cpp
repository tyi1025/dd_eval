#include "SimulationExecutor.hpp"

const std::unique_ptr<SimulationTask>& SimulationExecutor::getTask() {
  return mTask;
}

void SimulationExecutor::setTask(std::unique_ptr<SimulationTask>& task) {
  mTask = std::move(task);
}
