#include "AlternatingVerificationExecutor.hpp"

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

void AlternatingVerificationExecutor::setEquivalenceCheckingManager(
    std::unique_ptr<ec::EquivalenceCheckingManager>&
        equivalenceCheckingManager) {
  mEquivalenceCheckingManager = std::move(equivalenceCheckingManager);
}
