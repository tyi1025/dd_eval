#include "CircuitSimulatorExecutor.hpp"

class CircuitSimulatorExecutor::CircuitSimulatorExecutor {};

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

void CircuitSimulatorExecutor::setCircuitSimulator(
    std::unique_ptr<CircuitSimulator<>>& circuitSimulator) {
  mCircuitSimulator = std::move(circuitSimulator);
}
