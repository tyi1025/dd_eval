#include "executors/CircuitSimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

struct TestConfigurationDDSIM {
  // given input
  std::string description;
  std::string circuit;

  // expected output
  json expectedResults{};
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationDDSIM& test) {
  test.description     = j.at("description").get<std::string>();
  test.circuit         = j.at("circuit").get<std::string>();
  test.expectedResults = j.at("expected_meas_results").get<json>();
}

namespace {
std::vector<TestConfigurationDDSIM> getTests(const std::string& path) {
  std::ifstream  input(path);
  nlohmann::json j;
  input >> j;
  return j;
}
} // namespace

class DDSIMExecTest : public ::testing::TestWithParam<TestConfigurationDDSIM> {
protected:
  void SetUp() override {
    test = GetParam();
    std::stringstream ss(test.circuit);

    auto qc = std::make_unique<qc::QuantumComputation>();
    qc->import(ss, qc::Format::OpenQASM);
    std::cout << "Circuit:\n" << *qc;

    simulationTask           = SimulationTask(std::move(qc));
    circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  }

  SimulationTask                            simulationTask;
  std::unique_ptr<CircuitSimulatorExecutor> circuitSimulatorExecutor;
  TestConfigurationDDSIM                    test;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, DDSIMExecTest, testing::ValuesIn(getTests("sim_circuits.json")),
    [](const testing::TestParamInfo<DDSIMExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(DDSIMExecTest, Tests) {
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  if (!result["measurement_results"].empty()) {
    EXPECT_EQ(result["measurement_results"], test.expectedResults);
  }

  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}
