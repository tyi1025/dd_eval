#include "executors/DeterministicNoiseSimExecutor.hpp"

std::unique_ptr<DeterministicNoiseSimulator<>>
DeterministicNoiseSimExecutor::constructSimulator(const SimulationTask& task) {
  auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());
  auto deterministicNoiseSimulator =
      std::make_unique<DeterministicNoiseSimulator<>>(std::move(qc),
                                                      constants::GLOBAL_SEED);
  return deterministicNoiseSimulator;
}

json DeterministicNoiseSimExecutor::runSimulator(
    std::unique_ptr<DeterministicNoiseSimulator<>> simulator) {
  json result;
  auto results                  = simulator->deterministicSimulate();
  result["measurement_results"] = results;
  return result;
}
