#include "tasks/SimulationTask.hpp"

#include "QuantumComputation.hpp"

SimulationTask::SimulationTask(std::unique_ptr<qc::QuantumComputation> circ)
    : qc(std::move(circ)) {}

std::string SimulationTask::getIdentifier() const {
  return "sim_" + qc->getName();
}
