#include "VerificationTask.hpp"

std::string VerificationTask::getIdentifier() {
  return "ver_" + qc1->getName() + "_" + qc2->getName();
}
