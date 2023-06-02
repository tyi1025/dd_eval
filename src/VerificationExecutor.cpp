#include "VerificationExecutor.hpp"

const std::unique_ptr<VerificationTask>&
VerificationExecutor::getMTask() const {
  return mTask;
}

void VerificationExecutor::setMTask(std::unique_ptr<VerificationTask>& task) {
  mTask = std::move(task);
}
