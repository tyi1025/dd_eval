#include "CircuitSimulatorExecutor.hpp"

class CircuitSimulatorExecutor::CircuitSimulatorExecutor {
  //    CircuitSimulatorExecutor(std::unique_ptr<SimulationTask> &simTask) {
  //        setMSimTask(simTask);
  //    }
  //    CircuitSimulatorExecutor(std::unique_ptr<SimulationTask> &simTask) {
  //        mSimTask = std::move(simTask);
  //    }
  //    CircuitSimulatorExecutor() {
  //        mCircuitSimulator =
  //        CircuitSimulator(std::move(this->getMSimTask()->getQc()));
  //    }
};

std::string CircuitSimulatorExecutor::getIdentifier() {
  return {"This is a circuit simulator executor"};
  // refactor
}

json CircuitSimulatorExecutor::executeTask() {
  json result;
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "I'm here in testa\n";

  // execute the actual task
  const auto results = mCircuitSimulator->simulate(1024U);
  //  std::cout << results << std::endl;
  // use the results
  // Add memory usage

  auto stop = std::chrono::high_resolution_clock::now();
  auto runtime =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  result["runtime"]            = runtime.count();
  std::string const identifier = "test identifier";
  //      this->getTask()->getIdentifier() + "_" + this->getIdentifier();
  std::cout << "I'm here in testc\n";
  result["identifier"] = identifier;

  result["00"] = results.count("00");
  result["01"] = results.count("01");
  result["10"] = results.count("10");
  result["11"] = results.count("11");
  // what about more qubits？
  std::cout << "I'm here in testd\n";
  return result;
  //    return SimulationExecutor::executeTask();
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

// CircuitSimulatorExecutor(std::unique_ptr<SimulationTask> &mSimTask)
//         : SimulationExecutor(task), mSimTask(mSimTask) {}

// const CircuitSimulator<dd::DDPackageConfig>
// &CircuitSimulatorExecutor::getCircuitSimulator() const {
//     return circuitSimulator;
// }
//
// void CircuitSimulatorExecutor::setCircuitSimulator(const
// CircuitSimulator<dd::DDPackageConfig> &circuitSimulator) {
//     CircuitSimulatorExecutor::circuitSimulator = circuitSimulator;
// }
