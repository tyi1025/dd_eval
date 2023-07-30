#include "executors/StochasticNoiseSimulatorExecutor.hpp"

std::unique_ptr<StochasticNoiseSimulator<>>
StochasticNoiseSimulatorExecutor::constructSimulator(
    std::unique_ptr<qc::QuantumComputation>& qc) {
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
