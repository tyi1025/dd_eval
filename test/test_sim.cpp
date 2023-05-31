#include "CircuitSimulatorExecutor.hpp"
#include "SimulationTask.hpp"

#include "gtest/gtest.h"

namespace cs {

//    struct TestConfiguration {
//        // given input (either as tableau or as circuit)
//        std::string description;
//        std::string initialCircuit;
//
//        // expected output
//        std::size_t expected00{};
//    };

// NOLINTNEXTLINE (readability-identifier-naming)
//    inline void from_json(const nlohmann::json &j, TestConfiguration &test) {
//        test.description = j.at("description").get<std::string>();
//        if (j.contains("initial_circuit")) {
//            test.initialCircuit = j.at("initial_circuit").get<std::string>();
//        }
//        test.expected00 = j.at("expected_00").get<std::size_t>();
//
//    }

//    static std::vector<TestConfiguration> getTests(const std::string &path) {
//        std::ifstream input(path);
//        nlohmann::json j;
//        input >> j;
//        return j;
//    }
//    : public ::testing::TestWithParam<TestConfiguration>
class SimulatorTest {
protected:
  //        void SetUp() override {
  //            test = GetParam();
  //            std::cout << "I'm here in setup\n";

  //            if (!test.initialCircuit.empty()) {
  //                std::stringstream ss(test.initialCircuit);
  //                qc::QuantumComputation qc{};
  //                qc.import(ss, qc::Format::OpenQASM);
  //                std::cout << "Initial circuit:\n" << qc;
  //                std::cout << "NQubits:\n" << qc.getNqubits();
  //            }
  //            else {
  //                throw std::runtime_error("No circuit!");
  //            }
  //            config = Configuration();
  //            config.verbosity = plog::Severity::verbose;
  //            config.dumpIntermediateResults = true;
  //        }

  //        void TearDown() override {
  //            std::cout << "I'm here in teardown\n";
  //            std::cout << "Results:\n" << results << "\n";

  //            resultTableau = synthesizer.getResultTableau();
  //            std::cout << "Resulting tableau:\n" << resultTableau;
  //            EXPECT_EQ(resultTableau, targetTableau);
  //            EXPECT_EQ(expected00, 1024);
  //            const auto &resultCircuit = synthesizer.getResultCircuit();
  //            std::cout << "Resulting Circuit:\n" << resultCircuit;
  //            consistencyCheck(resultCircuit);
  //        }

  //        void consistencyCheck(const qc::QuantumComputation &qc) const {
  //            auto circuitTableau = initialTableau;
  //            for (const auto &gate: qc) {
  //                circuitTableau.applyGate(gate.get());
  //            }
  //            EXPECT_EQ(resultTableau, circuitTableau);
  //        }

  //        Tableau initialTableau;
  //        Tableau initialTableauWithDestabilizer;
  //        Tableau targetTableau;
  //        Tableau targetTableauWithDestabilizer;
  //        Configuration config;
  //        CliffordSynthesizer synthesizer;
  //        CliffordSynthesizer synthesizerWithDestabilizer;
  //        Results results;
  //        Results resultsWithDestabilizer;
  //        Tableau resultTableau;
  //        Tableau resultTableauWithDestabilizer;
  //        CircuitSimulatorExecutor circuitSimulatorExecutor;
  //        TestConfiguration test;
  //        SimulationTask simulationTask;
  //        json result;
};

//    INSTANTIATE_TEST_SUITE_P(
//            Tableaus, SynthesisTest,
//            testing::ValuesIn(getTests("cliffordsynthesis/tableaus.json")),
//            [](const testing::TestParamInfo<SynthesisTest::ParamType>& inf) {
//                return inf.param.description;
//            });

//    INSTANTIATE_TEST_SUITE_P(
//            Circuits, SimulatorTest,
//            testing::ValuesIn(getTests("/Users/tianyiwang/Documents/tum/GR/repos/dd_eval/test/circuits.json")),
//            [](const testing::TestParamInfo<SimulatorTest::ParamType>& inf) {
//                return inf.param.description;
//            });

TEST(SimulatorTest, EmptyCircuit) {
  auto qc             = std::make_unique<qc::QuantumComputation>(2U);
  auto simulationTask = std::make_unique<SimulationTask>(std::move(qc));
  auto circuitSimulator =
      std::make_unique<CircuitSimulator<>>(std::move(simulationTask->getQc()));
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  circuitSimulatorExecutor->setCircuitSimulator(circuitSimulator);
  circuitSimulatorExecutor->setMSimTask(simulationTask);
  json const result = circuitSimulatorExecutor->executeTask();

  EXPECT_EQ(1, result["00"]);
}

//    TEST_P(SynthesisTest, GatesMaxSAT) {
//        config.target    = TargetMetric::Gates;
//        config.useMaxSAT = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getGates(), test.expectedMinimalGates);
//    }
//
//    TEST_P(SynthesisTest, Depth) {
//        config.target = TargetMetric::Depth;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getDepth(), test.expectedMinimalDepth);
//    }
//
//    TEST_P(SynthesisTest, DepthMaxSAT) {
//        config.target    = TargetMetric::Depth;
//        config.useMaxSAT = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getDepth(), test.expectedMinimalDepth);
//    }
//
//    TEST_P(SynthesisTest, DepthMinimalGates) {
//        config.target                              = TargetMetric::Depth;
//        config.minimizeGatesAfterDepthOptimization = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getDepth(), test.expectedMinimalDepth);
//        EXPECT_EQ(results.getGates(),
//        test.expectedMinimalGatesAtMinimalDepth);
//    }
//
//    TEST_P(SynthesisTest, DepthMinimalTimeSteps) {
//        config.target           = TargetMetric::Depth;
//        config.minimalTimesteps = test.expectedMinimalDepth;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getDepth(), test.expectedMinimalDepth);
//    }
//
//    TEST_P(SynthesisTest, DepthMinimalGatesMaxSAT) {
//        config.target                              = TargetMetric::Depth;
//        config.useMaxSAT                           = true;
//        config.minimizeGatesAfterDepthOptimization = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getDepth(), test.expectedMinimalDepth);
//        EXPECT_EQ(results.getGates(),
//        test.expectedMinimalGatesAtMinimalDepth);
//    }
//
//    TEST_P(SynthesisTest, TwoQubitGates) {
//        config.target = TargetMetric::TwoQubitGates;
//        config.tryHigherGateLimitForTwoQubitGateOptimization = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getTwoQubitGates(),
//        test.expectedMinimalTwoQubitGates);
//    }
//
//    TEST_P(SynthesisTest, TwoQubitGatesMaxSAT) {
//        config.target = TargetMetric::TwoQubitGates;
//        config.tryHigherGateLimitForTwoQubitGateOptimization = true;
//        config.useMaxSAT                                     = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getTwoQubitGates(),
//        test.expectedMinimalTwoQubitGates);
//    }
//
//    TEST_P(SynthesisTest, TwoQubitGatesMinimalGates) {
//        config.target = TargetMetric::TwoQubitGates;
//        config.tryHigherGateLimitForTwoQubitGateOptimization = true;
//        config.minimizeGatesAfterTwoQubitGateOptimization    = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getTwoQubitGates(),
//        test.expectedMinimalTwoQubitGates); EXPECT_EQ(results.getGates(),
//                  test.expectedMinimalGatesAtMinimalTwoQubitGates);
//    }
//
//    TEST_P(SynthesisTest, TwoQubitGatesMinimalGatesMaxSAT) {
//        config.target = TargetMetric::TwoQubitGates;
//        config.tryHigherGateLimitForTwoQubitGateOptimization = true;
//        config.minimizeGatesAfterTwoQubitGateOptimization    = true;
//        config.useMaxSAT                                     = true;
//        synthesizer.synthesize(config);
//        results = synthesizer.getResults();
//
//        EXPECT_EQ(results.getTwoQubitGates(),
//        test.expectedMinimalTwoQubitGates); EXPECT_EQ(results.getGates(),
//                  test.expectedMinimalGatesAtMinimalTwoQubitGates);
//    }
//
//    TEST_P(SynthesisTest, TestDestabilizerGates) {
//        if (!initialTableauWithDestabilizer.getTableau().empty()) {
//            std::cout << "Testing with destabilizer" << std::endl;
//            config.target    = TargetMetric::Gates;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            synthesizerWithDestabilizer.synthesize(config);
//            results                 = synthesizer.getResults();
//            resultsWithDestabilizer =
//            synthesizerWithDestabilizer.getResults();
//
//            EXPECT_GE(resultsWithDestabilizer.getGates(), results.getGates());
//        } else {
//            std::cout << "Testing without destabilizer" << std::endl;
//            config.target    = TargetMetric::Gates;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            results = synthesizer.getResults();
//        }
//    }
//
//    TEST_P(SynthesisTest, TestDestabilizerDepth) {
//        if (!initialTableauWithDestabilizer.getTableau().empty()) {
//            std::cout << "Testing with destabilizer" << std::endl;
//            config.target    = TargetMetric::Depth;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            synthesizerWithDestabilizer.synthesize(config);
//            results                 = synthesizer.getResults();
//            resultsWithDestabilizer =
//            synthesizerWithDestabilizer.getResults();
//
//            EXPECT_GE(resultsWithDestabilizer.getDepth(), results.getDepth());
//        } else {
//            std::cout << "Testing without destabilizer" << std::endl;
//            config.target    = TargetMetric::Gates;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            results = synthesizer.getResults();
//        }
//    }
//
//    TEST_P(SynthesisTest, TestDestabilizerTwoQubitGates) {
//        if (!initialTableauWithDestabilizer.getTableau().empty()) {
//            std::cout << "Testing with destabilizer" << std::endl;
//            config.target    = TargetMetric::TwoQubitGates;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            synthesizerWithDestabilizer.synthesize(config);
//            results                 = synthesizer.getResults();
//            resultsWithDestabilizer =
//            synthesizerWithDestabilizer.getResults();
//
//            EXPECT_GE(resultsWithDestabilizer.getTwoQubitGates(),
//                      results.getTwoQubitGates());
//        } else {
//            std::cout << "Testing without destabilizer" << std::endl;
//            config.target    = TargetMetric::Gates;
//            config.useMaxSAT = true;
//
//            synthesizer.synthesize(config);
//            results = synthesizer.getResults();
//        }
//    }

} // namespace cs
