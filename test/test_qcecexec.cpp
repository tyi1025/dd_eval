#include "executors/AlternatingVerificationExecutor.hpp"
#include "tasks/VerificationTask.hpp"

#include "gtest/gtest.h"

struct TestConfigurationQCEC {
  // given input
  std::string description;
  std::string circuit1;
  std::string circuit2;

  // expected output
  std::string expectedEquivalence;
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationQCEC& test) {
  test.description         = j.at("description").get<std::string>();
  test.circuit1            = j.at("circuit1").get<std::string>();
  test.circuit2            = j.at("circuit2").get<std::string>();
  test.expectedEquivalence = j.at("expected_equivalence").get<std::string>();
}

namespace {
std::vector<TestConfigurationQCEC> getTests(const std::string& path) {
  std::ifstream  input(path);
  nlohmann::json j;
  input >> j;
  return j;
}
} // namespace

class QCECExecTest : public ::testing::TestWithParam<TestConfigurationQCEC> {
protected:
  void SetUp() override {
    test = GetParam();

    std::stringstream ss1(test.circuit1);
    auto              qc1 = std::make_unique<qc::QuantumComputation>();
    qc1->import(ss1, qc::Format::OpenQASM);
    std::cout << "Circuit 1:\n" << *qc1 << std::endl;

    std::stringstream ss2(test.circuit2);
    auto              qc2 = std::make_unique<qc::QuantumComputation>();
    qc2->import(ss2, qc::Format::OpenQASM);
    std::cout << "Circuit 2:\n" << *qc2 << std::endl;

    verificationTask = VerificationTask(std::move(qc1), std::move(qc2));

    alternatingVerificationExecutor =
        std::make_unique<AlternatingVerificationExecutor>();
  }

  VerificationTask verificationTask;
  std::unique_ptr<AlternatingVerificationExecutor>
                        alternatingVerificationExecutor;
  TestConfigurationQCEC test;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, QCECExecTest, testing::ValuesIn(getTests("ver_circuits.json")),
    [](const testing::TestParamInfo<QCECExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(QCECExecTest, Tests) {
  const auto result =
      alternatingVerificationExecutor->execute(verificationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("check_results"));
  EXPECT_EQ(result["check_results"]["equivalence"], test.expectedEquivalence);

  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}
