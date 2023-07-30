#include "executors/HybridSimulatorExecutor.hpp"

std::unique_ptr<HybridSchrodingerFeynmanSimulator<>>
HybridSimulatorExecutor::constructSimulator(
    std::unique_ptr<qc::QuantumComputation>& qc) {
  std::unique_ptr<HybridSchrodingerFeynmanSimulator<>> hybridSimulator;
  if (this->isRunAmplitude()) {
    hybridSimulator = std::make_unique<HybridSchrodingerFeynmanSimulator<>>(
        std::move(qc), ApproximationInfo{}, constants::GLOBAL_SEED);
  } else {
    hybridSimulator = std::make_unique<HybridSchrodingerFeynmanSimulator<>>(
        std::move(qc), ApproximationInfo{}, constants::GLOBAL_SEED,
        HybridSchrodingerFeynmanSimulator<>::Mode::DD);
  }
  return hybridSimulator;
}

json HybridSimulatorExecutor::runSimulator(
    std::unique_ptr<HybridSchrodingerFeynmanSimulator<>> simulator) {
  json result;
  auto results                  = simulator->simulate(1024U);
  result["measurement_results"] = results;
  return result;
}
