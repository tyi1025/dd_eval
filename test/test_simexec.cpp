#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"

#include "gtest/gtest.h"

struct TestConfiguration {
  // given input
  std::string description;
  std::string initialCircuit;

  // expected output
  std::size_t expected00{};
};

// NOLINTNEXTLINE (readability-identifier-naming)
inline void from_json(const nlohmann::json& j, TestConfiguration& test) {
  test.description    = j.at("description").get<std::string>();
  test.initialCircuit = j.at("initial_circuit").get<std::string>();
  test.expected00     = j.at("expected_00").get<std::size_t>();
}

static std::vector<TestConfiguration> getTests(const std::string& path) {
  std::ifstream  input(path);
  nlohmann::json j;
  input >> j;
  return j;
}

class SimulatorTest : public ::testing::TestWithParam<TestConfiguration> {
protected:
  void SetUp() override {
    test = GetParam();

    if (test.initialCircuit.empty()) {
      throw std::runtime_error("No circuit!");
    }
    std::stringstream      ss(test.initialCircuit);
    qc::QuantumComputation qc{};
    qc.import(ss, qc::Format::OpenQASM);
    std::cout << "Circuit:\n" << qc;

    qcForTask      = std::make_unique<qc::QuantumComputation>(qc.clone());
    qcForSim       = std::make_unique<qc::QuantumComputation>(qc.clone());
    simulationTask = std::make_unique<SimulationTask>(std::move(qcForTask));
    circuitSimulator =
        std::make_unique<CircuitSimulator<>>(std::move(qcForSim));
    circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
    circuitSimulatorExecutor->setCircuitSimulator(circuitSimulator);
    circuitSimulatorExecutor->setMSimTask(simulationTask);
  }

  void TearDown() override { std::cout << "Tearing down...\n"; }

  std::unique_ptr<qc::QuantumComputation>   qcForTask;
  std::unique_ptr<qc::QuantumComputation>   qcForSim;
  std::unique_ptr<SimulationTask>           simulationTask;
  std::unique_ptr<CircuitSimulator<>>       circuitSimulator;
  std::unique_ptr<CircuitSimulatorExecutor> circuitSimulatorExecutor;
  TestConfiguration                         test;
};

void printAll(const json& jsonObject) {
  for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
    const auto& key   = it.key();
    const auto& value = it.value();
    std::cout << key << ": " << value << std::endl;
  }
}

INSTANTIATE_TEST_SUITE_P(
    Circuits, SimulatorTest, testing::ValuesIn(getTests("circuits.json")),
    [](const testing::TestParamInfo<SimulatorTest::ParamType>& inf) {
      return inf.param.description;
    });

TEST_P(SimulatorTest, EmptyCircuit) {
  json const result = circuitSimulatorExecutor->executeTask();
  std::cout << "Results:" << std::endl;
  printAll(result);
  EXPECT_EQ(result["00"], test.expected00);
}
