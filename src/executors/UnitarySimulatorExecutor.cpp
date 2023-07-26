#include "executors/UnitarySimulatorExecutor.hpp"

#include "UnitarySimulator.hpp"

json UnitarySimulatorExecutor::execute(const SimulationTask& task) {
  json       result;
  auto const constructionStart = std::chrono::steady_clock::now();

  auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());

  std::unique_ptr<UnitarySimulator<>> unitarySimulator;
  if (this->recursive) {
    unitarySimulator = std::make_unique<UnitarySimulator<>>(
        std::move(qc), ApproximationInfo{}, constants::GLOBAL_SEED);
  } else {
    unitarySimulator = std::make_unique<UnitarySimulator<>>(
        std::move(qc), ApproximationInfo{}, constants::GLOBAL_SEED,
        UnitarySimulator<>::Mode::Sequential);
  }

  auto const executionStart = std::chrono::steady_clock::now();

  unitarySimulator->construct();
  result["final_node_count"] = unitarySimulator->getFinalNodeCount();
  result["max_node_count"]   = unitarySimulator->getMaxNodeCount();

  // Add memory usage

  //  auto const executionStop = std::chrono::steady_clock::now();
  auto const constructionTime =
      std::chrono::duration_cast<std::chrono::microseconds>(executionStart -
                                                            constructionStart);
  //  auto const execTime =
  //  std::chrono::duration_cast<std::chrono::microseconds>(
  //      executionStop - executionStart);
  result["simulator_construction_time"] = constructionTime.count();
  result["unitary_execution_time"] = unitarySimulator->getConstructionTime();

  result["executor"] = getIdentifier();
  result["task"]     = task.getIdentifier();

  return result;
}
