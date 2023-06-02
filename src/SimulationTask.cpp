#include "SimulationTask.hpp"

std::string SimulationTask::getIdentifier() { return "sim_" + qc->getName(); }

const std::unique_ptr<qc::QuantumComputation>& SimulationTask::getQc() const {
  return qc;
}
