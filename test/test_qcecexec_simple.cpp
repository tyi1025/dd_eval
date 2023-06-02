#include "AlternatingVerificationExecutor.hpp"
#include "EquivalenceCheckingManager.hpp"
#include "VerificationTask.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(QCECExecSimpleTest, EmptyCircuits) {
  auto qc        = std::make_unique<qc::QuantumComputation>(2U);
  auto clonedQC  = std::make_unique<qc::QuantumComputation>(qc->clone());
  auto clonedQC2 = qc->clone();
  auto clonedQC3 = qc->clone();
  auto verificationTask =
      std::make_unique<VerificationTask>(std::move(qc), std::move(clonedQC));
  auto config                             = ec::Configuration{};
  config.execution.runAlternatingChecker  = true;
  config.execution.runSimulationChecker   = false;
  config.execution.runConstructionChecker = false;
  config.execution.runZXChecker           = false;
  auto equivalenceCheckingManager =
      std::make_unique<ec::EquivalenceCheckingManager>(clonedQC2, clonedQC3,
                                                       config);
  auto alternatingVerificationExecutor =
      std::make_unique<AlternatingVerificationExecutor>();
  alternatingVerificationExecutor->setTask(verificationTask);
  alternatingVerificationExecutor->setEquivalenceCheckingManager(
      equivalenceCheckingManager);

  json const result = alternatingVerificationExecutor->executeTask();

  EXPECT_EQ("equivalent", result["equivalence"]);
}
