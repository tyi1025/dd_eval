#pragma once

#include "Executor.hpp"
#include "tasks/SimulationTask.hpp"

class UnitarySimulatorExecutor : public Executor<SimulationTask> {
public:
  json execute(const SimulationTask& task) override;

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
