#include "executors/AlternatingVerificationExecutor.hpp"

json AlternatingVerificationExecutor::execute(const VerificationTask& task) {
  json result;
  auto start = std::chrono::steady_clock::now();

  auto qc1 = task.getQc1()->clone();
  auto qc2 = task.getQc2()->clone();
  auto equivalenceCheckingManager =
      std::make_unique<ec::EquivalenceCheckingManager>(*task.getQc1(),
                                                       *task.getQc2());
  equivalenceCheckingManager->disableAllCheckers();
  equivalenceCheckingManager->setAlternatingChecker(true);

  equivalenceCheckingManager->run();
  result["check_results"] = equivalenceCheckingManager->getResults().json();
  // Add memory usage
  auto stop = std::chrono::steady_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"] = runtime.count();

  result["executor"] = getIdentifier();
  result["task"]     = task.getIdentifier();

  return result;
}
