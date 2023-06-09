#include "tasks/VerificationTask.hpp"

#include "QuantumComputation.hpp"

VerificationTask::VerificationTask(
    std::unique_ptr<qc::QuantumComputation> circ1,
    std::unique_ptr<qc::QuantumComputation> circ2)
    : qc1(std::move(circ1)), qc2(std::move(circ2)) {}

std::string VerificationTask::getIdentifier() const {
  return "ver_" + qc1->getName() + "_" + qc2->getName();
}
