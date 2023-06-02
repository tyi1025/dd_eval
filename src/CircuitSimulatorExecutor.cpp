#include "CircuitSimulatorExecutor.hpp"

class CircuitSimulatorExecutor::CircuitSimulatorExecutor {};

std::string CircuitSimulatorExecutor::getIdentifier() {
  return {"This is a circuit simulator executor"};
  // refactor. how?
}

json CircuitSimulatorExecutor::executeTask() {
  json result;
  auto start = std::chrono::high_resolution_clock::now();

  // execute the actual task
  const auto results = mCircuitSimulator->simulate(1024U);
  // use the results
  // Add memory usage

  auto stop = std::chrono::high_resolution_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"]            = runtime.count();
  std::string const identifier = "test identifier";
  //      this->getTask()->getIdentifier() + "_" + this->getIdentifier();
  result["identifier"] = identifier;

  result["00"] = results.count("00");
  result["01"] = results.count("01");
  result["10"] = results.count("10");
  result["11"] = results.count("11");
  // what about circuits with not 2 qubits？
  return result;
}

const std::unique_ptr<SimulationTask>&
CircuitSimulatorExecutor::getMSimTask() const {
  return mSimTask;
}

void CircuitSimulatorExecutor::setMSimTask(
    std::unique_ptr<SimulationTask>& simTask) {
  mSimTask = std::move(simTask);
}

const std::unique_ptr<CircuitSimulator<>>&
CircuitSimulatorExecutor::getCircuitSimulator() {
  return mCircuitSimulator;
}

void CircuitSimulatorExecutor::setCircuitSimulator(
    std::unique_ptr<CircuitSimulator<>>& circuitSimulator) {
  mCircuitSimulator = std::move(circuitSimulator);
}
