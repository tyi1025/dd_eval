#include "QuantumComputation.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/DeterministicNoiseSimExecutor.hpp"
#include "executors/HybridSimulatorExecutor.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"
#include "executors/UnitarySimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

struct TestConfigurationDDSIM {
  // given input
  std::string description;
  std::string circuit;
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfigurationDDSIM& test) {
  test.description = j.at("description").get<std::string>();
  test.circuit     = j.at("circuit").get<std::string>();
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

    simulationTask = SimulationTask(std::move(qc));
  }

  SimulationTask         simulationTask;
  TestConfigurationDDSIM test;
};

INSTANTIATE_TEST_SUITE_P(
    Circuits, DDSIMExecTest, testing::ValuesIn(getTests("sim_circuits.json")),
    [](const testing::TestParamInfo<DDSIMExecTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(DDSIMExecTest, CircuitSimulatorExec) {
  std::unique_ptr<CircuitSimulatorExecutor> circuitSimulatorExecutor =
      std::make_unique<CircuitSimulatorExecutor>();
  const auto result = circuitSimulatorExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, DeterministicNoiseSimExec) {
  std::unique_ptr<DeterministicNoiseSimExecutor> deterministicNoiseSimExecutor =
      std::make_unique<DeterministicNoiseSimExecutor>();
  const auto result = deterministicNoiseSimExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, HybridSimulatorAmplitudeExec) {
  std::unique_ptr<HybridSimulatorExecutor> hybridSimulatorAmplitudeExecutor =
      std::make_unique<HybridSimulatorExecutor>();
  ASSERT_TRUE(hybridSimulatorAmplitudeExecutor->isRunAmplitude());
  const auto result = hybridSimulatorAmplitudeExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, HybridSimulatorDDExec) {
  std::unique_ptr<HybridSimulatorExecutor> hybridSimulatorDDExecutor =
      std::make_unique<HybridSimulatorExecutor>();
  hybridSimulatorDDExecutor->setRunAmplitude(false);
  hybridSimulatorDDExecutor->setRunDd(true);

  const auto result = hybridSimulatorDDExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  ASSERT_TRUE(result["executor"] ==
              ("hybrid_schrodinger_feynman_simulator_dd"));
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, StochasticNoiseSimExec) {
  std::unique_ptr<StochasticNoiseSimulatorExecutor>
      stochasticNoiseSimulatorExecutor =
          std::make_unique<StochasticNoiseSimulatorExecutor>();
  const auto result = stochasticNoiseSimulatorExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("measurement_results"));
  EXPECT_TRUE(result.contains("construction_time"));
  EXPECT_TRUE(result.contains("execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, UnitarySimRecursiveExec) {
  std::unique_ptr<UnitarySimulatorExecutor> unitarySimRecursiveExecutor =
      std::make_unique<UnitarySimulatorExecutor>();
  const auto result = unitarySimRecursiveExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("final_node_count"));
  ASSERT_TRUE(result.contains("max_node_count"));
  EXPECT_TRUE(result.contains("unitary_execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}

TEST_P(DDSIMExecTest, UnitarySimSequentialExec) {
  std::unique_ptr<UnitarySimulatorExecutor> unitarySimSequentialExecutor =
      std::make_unique<UnitarySimulatorExecutor>();
  unitarySimSequentialExecutor->setRecursive(false);
  unitarySimSequentialExecutor->setSequential(true);

  const auto result = unitarySimSequentialExecutor->execute(simulationTask);
  std::cout << "Results:\n" << result.dump(2U) << std::endl;

  ASSERT_TRUE(result.contains("final_node_count"));
  ASSERT_TRUE(result.contains("max_node_count"));
  ASSERT_TRUE(result["executor"] == ("unitary_simulator_sequential"));
  EXPECT_TRUE(result.contains("unitary_execution_time"));
  EXPECT_TRUE(result.contains("executor"));
  EXPECT_TRUE(result.contains("task"));
}
