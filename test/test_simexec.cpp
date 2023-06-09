#include "executors/CircuitSimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

struct TestConfigurationDDSIM {
  // given input
  std::string description;
  std::string initialCircuit;

  // expected output
  json expectedResults{};
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationDDSIM& test) {
  test.description     = j.at("description").get<std::string>();
  test.initialCircuit  = j.at("initial_circuit").get<std::string>();
  test.expectedResults = j.at("expected_meas_results").get<json>();
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

    std::stringstream ss(test.initialCircuit);
    auto              qc = std::make_unique<qc::QuantumComputation>();
    qc->import(ss, qc::Format::OpenQASM);
    std::cout << "Circuit:\n" << *qc;

    simulationTask           = SimulationTask(std::move(qc));
    circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();

    result = circuitSimulatorExecutor->execute(simulationTask);
    std::cout << "Results:" << std::endl;
    std::cout << result.dump(2U) << std::endl;
  }

  void TearDown() override { std::cout << "Tearing down...\n"; }

  SimulationTask                            simulationTask;
  std::unique_ptr<CircuitSimulatorExecutor> circuitSimulatorExecutor;
  TestConfigurationDDSIM                    test;
  json                                      result;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, DDSIMExecTest, testing::ValuesIn(getTests("circuits.json")),
    [](const testing::TestParamInfo<DDSIMExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(DDSIMExecTest, MeasResults) {
  EXPECT_EQ(result["measurement_results"], test.expectedResults);
}

TEST_P(DDSIMExecTest, Entries) {
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}
