#pragma once

#include "EquivalenceCheckingManager.hpp"
#include "VerificationExecutor.hpp"

class AlternatingVerificationExecutor : public VerificationExecutor {
public:
  AlternatingVerificationExecutor() = delete;

  explicit AlternatingVerificationExecutor(
      std::unique_ptr<VerificationTask> verificationTask);

  json        executeTask() override;
  std::string getIdentifier() override;

private:
  std::unique_ptr<ec::EquivalenceCheckingManager> mEquivalenceCheckingManager;
};
