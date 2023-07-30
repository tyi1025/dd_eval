#include "executors/UnitarySimulatorExecutor.hpp"

std::unique_ptr<UnitarySimulator<>>
UnitarySimulatorExecutor::constructSimulator(const SimulationTask& task) {
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
  return unitarySimulator;
}

json UnitarySimulatorExecutor::runSimulator(
    std::unique_ptr<UnitarySimulator<>> simulator) {
  json result;
  simulator->construct();
  result["final_node_count"]       = simulator->getFinalNodeCount();
  result["max_node_count"]         = simulator->getMaxNodeCount();
  result["unitary_execution_time"] = simulator->getConstructionTime();
  return result;
}
