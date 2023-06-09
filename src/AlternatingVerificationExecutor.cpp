#include "executors/AlternatingVerificationExecutor.hpp"

#include "EquivalenceCheckingManager.hpp"

json AlternatingVerificationExecutor::execute(const VerificationTask& task) {
  json       result;
  auto const constructionStart = std::chrono::steady_clock::now();

  auto equivalenceCheckingManager =
      std::make_unique<ec::EquivalenceCheckingManager>(*task.getQc1(),
                                                       *task.getQc2());
  equivalenceCheckingManager->disableAllCheckers();
  equivalenceCheckingManager->setAlternatingChecker(true);

  auto const executionStart = std::chrono::steady_clock::now();

  equivalenceCheckingManager->run();
  result["check_results"] = equivalenceCheckingManager->getResults().json();
  // Add memory usage
  auto const executionStop = std::chrono::steady_clock::now();
  auto const constructionTime =
      std::chrono::duration_cast<std::chrono::microseconds>(executionStart -
                                                            constructionStart);
  auto const execTime = std::chrono::duration_cast<std::chrono::microseconds>(
      executionStop - executionStart);
  result["construction_time"] = constructionTime.count();
  result["execution_time"]    = execTime.count();

  result["executor"] = getIdentifier();
  result["task"]     = task.getIdentifier();

  return result;
}
