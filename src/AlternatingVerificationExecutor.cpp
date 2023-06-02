#include "AlternatingVerificationExecutor.hpp"

AlternatingVerificationExecutor::AlternatingVerificationExecutor(
    std::unique_ptr<VerificationTask> verificationTask) {
  mTask    = std::move(verificationTask);
  auto qc1 = mTask->getQc1()->clone();
  auto qc2 = mTask->getQc2()->clone();
  mEquivalenceCheckingManager =
      std::make_unique<ec::EquivalenceCheckingManager>(qc1, qc2);
  mEquivalenceCheckingManager->setAlternatingChecker(true);
  mEquivalenceCheckingManager->setSimulationChecker(false);
  mEquivalenceCheckingManager->setConstructionChecker(false);
  mEquivalenceCheckingManager->setZXChecker(false);
}

std::string AlternatingVerificationExecutor::getIdentifier() {
  return "alt_ver_exe" + mTask->getIdentifier();
}

json AlternatingVerificationExecutor::executeTask() {
  json result;
  auto start = std::chrono::high_resolution_clock::now();

  mEquivalenceCheckingManager->run();
  result = mEquivalenceCheckingManager->getResults().json();
  // Add memory usage
  auto stop = std::chrono::high_resolution_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"] = runtime.count();
  std::string const identifier =
      this->getTask()->getIdentifier() + "_" + this->getIdentifier();
  result["identifier"] = identifier;

  return result;
}
