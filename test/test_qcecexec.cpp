#include "AlternatingVerificationExecutor.hpp"
#include "TestHelpers.hpp"
#include "VerificationTask.hpp"

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

    if (test.initialCircuit1.empty() or test.initialCircuit2.empty()) {
      throw std::runtime_error("Circuit missing!");
    }
    std::stringstream      ss1(test.initialCircuit1);
    qc::QuantumComputation qc1{};
    qc1.import(ss1, qc::Format::OpenQASM);
    std::cout << "Circuit 1:\n" << qc1 << std::endl;

    std::stringstream      ss2(test.initialCircuit2);
    qc::QuantumComputation qc2{};
    qc2.import(ss2, qc::Format::OpenQASM);
    std::cout << "Circuit 2:\n" << qc2 << std::endl;

    qc1Ver           = std::make_unique<qc::QuantumComputation>(qc1.clone());
    qc2Ver           = std::make_unique<qc::QuantumComputation>(qc2.clone());
    verificationTask = std::make_unique<VerificationTask>(std::move(qc1Ver),
                                                          std::move(qc2Ver));

    alternatingVerificationExecutor =
        std::make_unique<AlternatingVerificationExecutor>(
            std::move(verificationTask));
  }

  void TearDown() override { std::cout << "Tearing down...\n"; }

  std::unique_ptr<qc::QuantumComputation> qc1Ver;
  std::unique_ptr<qc::QuantumComputation> qc2Ver;
  std::unique_ptr<VerificationTask>       verificationTask;
  std::unique_ptr<AlternatingVerificationExecutor>
                        alternatingVerificationExecutor;
  TestConfigurationQCEC test;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, QCECExecTest, testing::ValuesIn(getTests("equi_circuits.json")),
    [](const testing::TestParamInfo<QCECExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(QCECExecTest, EmptyCircuits) {
  json const result = alternatingVerificationExecutor->executeTask();
  std::cout << "Results:" << std::endl;
  printAll(result);
  EXPECT_EQ(result["equivalence"], test.expectedEquivalence);
}
