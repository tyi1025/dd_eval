#include "executors/CircuitSimulatorExecutor.hpp"

std::unique_ptr<CircuitSimulator<>>
CircuitSimulatorExecutor::constructSimulator(
    std::unique_ptr<qc::QuantumComputation>& qc) {
  auto circuitSimulator = std::make_unique<CircuitSimulator<>>(
      std::move(qc), constants::GLOBAL_SEED);

  return circuitSimulator;
}

json CircuitSimulatorExecutor::runSimulator(
    std::unique_ptr<CircuitSimulator<>> simulator) {
  json result;
  auto results                  = simulator->simulate(1024U);
  result["measurement_results"] = results;
  return result;
}
