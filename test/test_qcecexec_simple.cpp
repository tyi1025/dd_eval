#include "AlternatingVerificationExecutor.hpp"
#include "VerificationTask.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(QCECExecSimpleTest, EmptyCircuits) {
  auto qc1 = std::make_unique<qc::QuantumComputation>(2U);
  auto qc2 = std::make_unique<qc::QuantumComputation>(2U);
  auto verificationTask =
      std::make_unique<VerificationTask>(std::move(qc1), std::move(qc2));
  auto alternatingVerificationExecutor =
      std::make_unique<AlternatingVerificationExecutor>(
          std::move(verificationTask));

  json const result = alternatingVerificationExecutor->executeTask();

  EXPECT_EQ("equivalent", result["equivalence"]);
}
