#include "QuantumComputation.hpp"
#include "algorithms/QPE.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/DeterministicNoiseSimExecutor.hpp"
#include "executors/HybridSimulatorAmplitudeExecutor.hpp"
#include "executors/HybridSimulatorDDExecutor.hpp"
#include "executors/StochasticNoiseSimulatorExecutor.hpp"
#include "executors/UnitarySimRecursiveExecutor.hpp"
#include "executors/UnitarySimSequentialExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

// QPE fails from n=65 on in ComplexTable line 151. See if later versions of the
// dd package can fix this.

TEST(SimExecTestQPE, CircuitSimulatorExec) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 65;
  auto                 qc       = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(circuitSimulatorExecutor->execute(simulationTask), "Assertion");
}

TEST(SimExecTestQPE, UnitarySimRecursiveExec) {
  auto unitarySimRecursiveExecutor =
      std::make_unique<UnitarySimRecursiveExecutor>();
  std::size_t const    n  = 65;
  auto                 qc = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(unitarySimRecursiveExecutor->execute(simulationTask),
               "Assertion");
}

TEST(SimExecTestQPE, UnitarySimSequentialExec) {
  auto unitarySimSequentialExecutor =
      std::make_unique<UnitarySimSequentialExecutor>();
  std::size_t const    n  = 65;
  auto                 qc = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(unitarySimSequentialExecutor->execute(simulationTask),
               "Assertion");
}
