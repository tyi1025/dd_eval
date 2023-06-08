#include "executors/CircuitSimulatorExecutor.hpp"

json CircuitSimulatorExecutor::execute(const SimulationTask& task) {
  json result;
  auto start = std::chrono::steady_clock::now();

  auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());
  auto circuitSimulator = std::make_unique<CircuitSimulator<>>(std::move(qc));

  result["measurement_results"] = circuitSimulator->simulate(1024U);
  // Add memory usage

  auto       stop = std::chrono::steady_clock::now();
  auto const runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"]  = runtime.count();
  result["executor"] = getIdentifier();
  result["task"]     = task.getIdentifier();

  return result;
}
