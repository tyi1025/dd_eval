#pragma once

#include "Executor.hpp"
#include "VerificationTask.hpp"

class VerificationExecutor : public Executor {
public:
  VerificationExecutor() = default;

private:
  std::unique_ptr<VerificationTask> mTask;

public:
  const std::unique_ptr<VerificationTask>& getMTask() const;

  void setMTask(std::unique_ptr<VerificationTask>& task);
};
