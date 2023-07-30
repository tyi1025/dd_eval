#include "executors/StochasticNoiseSimulatorExecutor.hpp"

std::unique_ptr<StochasticNoiseSimulator<>>
StochasticNoiseSimulatorExecutor::constructSimulator(
    const SimulationTask& task) {
  auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());
  auto stochasticNoiseSimulator = std::make_unique<StochasticNoiseSimulator<>>(
      std::move(qc), 1, 1, constants::GLOBAL_SEED);
  return stochasticNoiseSimulator;
}

json StochasticNoiseSimulatorExecutor::runSimulator(
    std::unique_ptr<StochasticNoiseSimulator<>> simulator) {
  json result;
  auto results                  = simulator->simulate(1024U);
  result["measurement_results"] = results;
  return result;
}
