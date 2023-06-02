#pragma once

#include "EquivalenceCheckingManager.hpp"
#include "VerificationExecutor.hpp"

class AlternatingVerificationExecutor : public VerificationExecutor {
public:
  AlternatingVerificationExecutor() = default;
  // checker and task must be set before use

  json        executeTask() override;
  std::string getIdentifier() override;

private:
  std::unique_ptr<ec::EquivalenceCheckingManager> mEquivalenceCheckingManager;

public:
  const std::unique_ptr<ec::EquivalenceCheckingManager>&
  getEquivalenceCheckingManager();

  void
  setEquivalenceCheckingManager(std::unique_ptr<ec::EquivalenceCheckingManager>&
                                    equivalenceCheckingManager);
};
