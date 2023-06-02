#pragma once

#include "Executor.hpp"
#include "VerificationTask.hpp"

class VerificationExecutor : public Executor {
public:
  VerificationExecutor() = default;

protected:
  std::unique_ptr<VerificationTask> mTask;

public:
  [[nodiscard]] const std::unique_ptr<VerificationTask>& getTask() const;

  void setTask(std::unique_ptr<VerificationTask>& task);
};
