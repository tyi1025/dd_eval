#pragma once

#include "Task.hpp"
#include "QuantumComputation.hpp"

class SimulationTask : public Task {
public:
    explicit SimulationTask(qc::QuantumComputation qc) {
        this->qc = qc.clone();
    };
private:
    qc::QuantumComputation qc;
};
