#include "executors/HybridSimulatorDDExecutor.hpp"

#include "HybridSchrodingerFeynmanSimulator.hpp"

json HybridSimulatorDDExecutor::execute(const SimulationTask& task) {
  json       result;
  auto const constructionStart = std::chrono::steady_clock::now();

  auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());
  auto hybridSimulator = std::make_unique<HybridSchrodingerFeynmanSimulator<>>(
      std::move(qc), ApproximationInfo{}, 23,
      HybridSchrodingerFeynmanSimulator<>::Mode::DD);

  auto const executionStart = std::chrono::steady_clock::now();

  result["measurement_results"] = hybridSimulator->simulate(1024U);
  // Add memory usage

  auto const executionStop = std::chrono::steady_clock::now();
  auto const constructionTime =
      std::chrono::duration_cast<std::chrono::microseconds>(executionStart -
                                                            constructionStart);
  auto const execTime = std::chrono::duration_cast<std::chrono::microseconds>(
      executionStop - executionStart);
  result["construction_time"] = constructionTime.count();
  result["execution_time"]    = execTime.count();

  result["executor"] = getIdentifier();
  result["task"]     = task.getIdentifier();

  return result;
}
