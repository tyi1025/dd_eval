#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"
#include "TestHelpers.hpp"

#include "gtest/gtest.h"

struct TestConfigurationDDSIM {
  // given input
  std::string description;
  std::string initialCircuit;

  // expected output
  std::size_t expected11{};
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationDDSIM& test) {
  test.description    = j.at("description").get<std::string>();
  test.initialCircuit = j.at("initial_circuit").get<std::string>();
  test.expected11     = j.at("expected_11").get<std::size_t>();
}

static std::vector<TestConfigurationDDSIM> getTests(const std::string& path) {
  std::ifstream  input(path);
  nlohmann::json j;
  input >> j;
  return j;
}

class DDSIMExecTest : public ::testing::TestWithParam<TestConfigurationDDSIM> {
protected:
  void SetUp() override {
    test = GetParam();

    std::stringstream      ss(test.initialCircuit);
    auto qc = std::make_unique<qc::QuantumComputation>():
    qc->import(ss, qc::Format::OpenQASM);
    std::cout << "Circuit:\n" << qc;

    simulationTask = std::make_unique<SimulationTask>(std::move(qc));
    circuitSimulatorExecutor =
        std::make_unique<CircuitSimulatorExecutor>(std::move(simulationTask));
  }

  void TearDown() override { std::cout << "Tearing down...\n"; }

  std::unique_ptr<qc::QuantumComputation>   qcSim;
  std::unique_ptr<SimulationTask>           simulationTask;
  std::unique_ptr<CircuitSimulatorExecutor> circuitSimulatorExecutor;
  TestConfigurationDDSIM                    test;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, DDSIMExecTest, testing::ValuesIn(getTests("circuits.json")),
    [](const testing::TestParamInfo<DDSIMExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(DDSIMExecTest, TwoQubitCircuitWithTwoXGates) {
  json const result = circuitSimulatorExecutor->executeTask();
  std::cout << "Results:" << std::endl;
  printAll(result);
  EXPECT_EQ(result["11"], test.expected11);
}
