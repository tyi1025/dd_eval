#pragma once

#include "SimulationExecutor.hpp"
#include "UnitarySimulator.hpp"

class UnitarySimulatorExecutor : public SimulationExecutor<UnitarySimulator<>> {
public:
  std::unique_ptr<UnitarySimulator<>>
  constructSimulator(std::unique_ptr<qc::QuantumComputation>& qc) override;

  json runSimulator(std::unique_ptr<UnitarySimulator<>> simulator) override;

  [[nodiscard]] std::string getIdentifier() const override {
    if (sequential) {
      return "unitary_simulator_sequential";
    }
    return "unitary_simulator_recursive";
  };

  [[nodiscard]] bool isSequential() const { return sequential; }

  void setSequential(bool run) { sequential = run; }

  [[nodiscard]] bool isRecursive() const { return recursive; }

  void setRecursive(bool run) { recursive = run; }

private:
  bool sequential = false;
  bool recursive  = true;
};
