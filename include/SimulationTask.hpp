#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

class SimulationTask : public Task {
public:
  explicit SimulationTask(qc::QuantumComputation qc) { this->qc = qc.clone(); };

private:
  qc::QuantumComputation qc;
};
