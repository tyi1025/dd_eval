#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

#include <memory>

class SimulationTask : public Task {
public:
  SimulationTask() = default;

  explicit SimulationTask(std::unique_ptr<qc::QuantumComputation> qc)
      : qc(std::move(qc)) {}

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc() const {
    return qc;
  };

  [[nodiscard]] std::string getIdentifier() const override {
    return "sim_" + qc->getName();
  };

protected:
  std::unique_ptr<qc::QuantumComputation> qc;
};
