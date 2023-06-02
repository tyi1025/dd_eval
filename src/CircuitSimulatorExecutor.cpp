#include "CircuitSimulatorExecutor.hpp"

CircuitSimulatorExecutor::CircuitSimulatorExecutor(
    std::unique_ptr<SimulationTask> simulationTask) {
  mTask   = std::move(simulationTask);
  auto qc = std::make_unique<qc::QuantumComputation>(mTask->getQc()->clone());
  mCircuitSimulator = std::make_unique<CircuitSimulator<>>(std::move(qc));
}

std::string CircuitSimulatorExecutor::getIdentifier() {
  return "circ_sim_exe" + mTask->getIdentifier();
}

template <typename KTy, typename VTy>
inline void toJson(json& j, const std::map<KTy, VTy>& m) {
  for (const auto& entry : m) {
    j[entry.first] = entry.second;
  }
}

json CircuitSimulatorExecutor::executeTask() {
  json result;
  auto start = std::chrono::high_resolution_clock::now();

  const auto results = mCircuitSimulator->simulate(1024U);
  toJson(result, results);
  // Add memory usage

  auto stop = std::chrono::high_resolution_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"] = runtime.count();
  std::string const identifier =
      this->getTask()->getIdentifier() + "_" + this->getIdentifier();
  result["identifier"] = identifier;

  return result;
}
