#include "VerificationExecutor.hpp"

const std::unique_ptr<VerificationTask>& VerificationExecutor::getTask() const {
  return mTask;
}

void VerificationExecutor::setTask(std::unique_ptr<VerificationTask>& task) {
  mTask = std::move(task);
}
