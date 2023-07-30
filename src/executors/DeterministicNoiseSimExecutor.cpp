#include "executors/DeterministicNoiseSimExecutor.hpp"

std::unique_ptr<DeterministicNoiseSimulator<>>
DeterministicNoiseSimExecutor::constructSimulator(
    std::unique_ptr<qc::QuantumComputation>& qc) {
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
