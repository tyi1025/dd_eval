#include "executors/AlternatingVerificationExecutor.hpp"
#include "tasks/VerificationTask.hpp"

#include "gtest/gtest.h"

struct TestConfigurationQCEC {
  // given input
  std::string description;
  std::string initialCircuit1;
  std::string initialCircuit2;

  // expected output
  std::string expectedEquivalence;
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationQCEC& test) {
  test.description         = j.at("description").get<std::string>();
  test.initialCircuit1     = j.at("initial_circuit1").get<std::string>();
  test.initialCircuit2     = j.at("initial_circuit2").get<std::string>();
  test.expectedEquivalence = j.at("expected_equivalence").get<std::string>();
}

static std::vector<TestConfigurationQCEC> getTests(const std::string& path) {
  std::ifstream  input(path);
  nlohmann::json j;
  input >> j;
  return j;
}

class QCECExecTest : public ::testing::TestWithParam<TestConfigurationQCEC> {
protected:
  void SetUp() override {
    test = GetParam();

    std::stringstream ss1(test.initialCircuit1);
    auto              qc1 = std::make_unique<qc::QuantumComputation>();
    qc1->import(ss1, qc::Format::OpenQASM);
    std::cout << "Circuit 1:\n" << *qc1 << std::endl;

    std::stringstream ss2(test.initialCircuit2);
    auto              qc2 = std::make_unique<qc::QuantumComputation>();
    qc2->import(ss2, qc::Format::OpenQASM);
    std::cout << "Circuit 2:\n" << *qc2 << std::endl;

    verificationTask = VerificationTask(std::move(qc1), std::move(qc2));

    alternatingVerificationExecutor =
        std::make_unique<AlternatingVerificationExecutor>();

    result = alternatingVerificationExecutor->execute(verificationTask);
    std::cout << "Results:" << std::endl;
    std::cout << result.dump(2U) << std::endl;
  }

  void TearDown() override { std::cout << "Tearing down...\n"; }

  VerificationTask verificationTask;
  std::unique_ptr<AlternatingVerificationExecutor>
                        alternatingVerificationExecutor;
  TestConfigurationQCEC test;
  json                  result;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, QCECExecTest, testing::ValuesIn(getTests("equi_circuits.json")),
    [](const testing::TestParamInfo<QCECExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(QCECExecTest, Equivalence) {
  EXPECT_EQ(result["check_results"]["equivalence"], test.expectedEquivalence);
}

TEST_P(QCECExecTest, Entries) {
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}
