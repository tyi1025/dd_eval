#pragma once

#include "Executor.hpp"
#include "VerificationTask.hpp"

class VerificationExecutor : public Executor {
public:
  explicit VerificationExecutor(const std::shared_ptr<VerificationTask>& task) {
    setTask(task);
  };
  json executeTask() override;
};
