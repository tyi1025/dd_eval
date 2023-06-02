#include "VerificationTask.hpp"

std::string VerificationTask::getIdentifier() {
  return "ver_" + qc1->getName() + "_" + qc2->getName();
}

const std::unique_ptr<qc::QuantumComputation>&
VerificationTask::getQc1() const {
  return qc1;
}

const std::unique_ptr<qc::QuantumComputation>&
VerificationTask::getQc2() const {
  return qc2;
}
