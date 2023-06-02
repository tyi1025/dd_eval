#include "VerificationExecutor.hpp"

const std::unique_ptr<VerificationTask>& VerificationExecutor::getTask() const {
  return mTask;
}
