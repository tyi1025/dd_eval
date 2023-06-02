#include "SimulationTask.hpp"

std::string SimulationTask::getIdentifier() { return "sim_" + qc->getName(); }
