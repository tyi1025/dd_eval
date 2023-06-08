#pragma once

#include "EquivalenceCheckingManager.hpp"
#include "Executor.hpp"
#include "tasks/VerificationTask.hpp"

class AlternatingVerificationExecutor : public Executor<VerificationTask> {
public:
  AlternatingVerificationExecutor() = default;

  json                      execute(const VerificationTask& task) override;
  [[nodiscard]] std::string getIdentifier() const override {
    return "alternating_verification";
  }
};
