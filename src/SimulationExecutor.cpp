#include "SimulationExecutor.hpp"

// json SimulationExecutor::executeTask() { return nullptr; }

const std::unique_ptr<Task>& SimulationExecutor::getTask() {
  return std::move(mTask);
}

void SimulationExecutor::setTask(std::unique_ptr<SimulationTask>& task) {
  mTask = std::move(task);
}
