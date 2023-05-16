#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

class VerificationTask : public Task {
public:
  VerificationTask(qc::QuantumComputation qc1, qc::QuantumComputation qc2) {
    this->qc1 = qc1.clone();
    this->qc2 = qc2.clone();
  };

private:
  qc::QuantumComputation qc1;
  qc::QuantumComputation qc2;
};
