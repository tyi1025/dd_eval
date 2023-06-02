#include "SimulationExecutor.hpp"

const std::unique_ptr<SimulationTask>& SimulationExecutor::getTask() {
  return mTask;
}
