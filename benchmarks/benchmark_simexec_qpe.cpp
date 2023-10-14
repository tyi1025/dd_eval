#include "algorithms/QPE.hpp"
#include "executors/CircuitSimulatorExecutor.hpp"
#include "executors/UnitarySimulatorExecutor.hpp"
#include "tasks/SimulationTask.hpp"

#include "gtest/gtest.h"

// QPE fails from n=65 on in ComplexTable line 151. See if later versions of the
// dd package can fix this.

TEST(SimExecBenchmarkQPE, CircuitSimulatorExec) {
  auto circuitSimulatorExecutor = std::make_unique<CircuitSimulatorExecutor>();
  std::size_t const    n        = 65;
  auto                 qc       = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(circuitSimulatorExecutor->execute(simulationTask), "Assertion");
}

TEST(SimExecBenchmarkQPE, UnitarySimRecursiveExec) {
  auto unitarySimRecursiveExecutor =
      std::make_unique<UnitarySimulatorExecutor>();
  std::size_t const    n  = 65;
  auto                 qc = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(unitarySimRecursiveExecutor->execute(simulationTask),
               "Assertion");
}

TEST(SimExecBenchmarkQPE, UnitarySimSequentialExec) {
  auto unitarySimSequentialExecutor =
      std::make_unique<UnitarySimulatorExecutor>();
  unitarySimSequentialExecutor->setRecursive(false);
  unitarySimSequentialExecutor->setSequential(true);
  std::size_t const    n  = 65;
  auto                 qc = std::make_unique<qc::QPE>(n, true, false);
  SimulationTask const simulationTask(std::move(qc));
  EXPECT_DEATH(unitarySimSequentialExecutor->execute(simulationTask),
               "Assertion");
}
