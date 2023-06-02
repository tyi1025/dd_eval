#include "SimulationExecutor.hpp"

const std::unique_ptr<SimulationTask>& SimulationExecutor::getMTask() {
  return mTask;
}

void SimulationExecutor::setTask(std::unique_ptr<SimulationTask>& task) {
  mTask = std::move(task);
}
