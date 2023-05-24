#include "CircuitSimulatorExecutor.hpp"

class CircuitSimulatorExecutor::CircuitSimulatorExecutor {};

std::string CircuitSimulatorExecutor::getIdentifier() {
  return std::string("This is a circuit simulator executor");
  // refactor
}

json CircuitSimulatorExecutor::executeTask() {
  json result;
  auto start = std::chrono::high_resolution_clock::now();

  //    this->executeTask();
  // execute the actual task
  // Add memory usage

  auto stop = std::chrono::high_resolution_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"] = runtime.count();
  std::string const identifier =
      this->getTask()->getIdentifier() + "_" + this->getIdentifier();
  result["identifier"] = identifier;
  return result;
  //    return SimulationExecutor::executeTask();
}
