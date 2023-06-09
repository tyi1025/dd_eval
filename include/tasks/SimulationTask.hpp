#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

#include <memory>

class SimulationTask : public Task {
public:
  explicit SimulationTask() = default;
  explicit SimulationTask(std::unique_ptr<qc::QuantumComputation> circ)
      : qc(std::move(circ)) {}

  [[nodiscard]] std::string getIdentifier() const override {
    return "sim_" + qc->getName();
  };

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc() const {
    return qc;
  };

protected:
  std::unique_ptr<qc::QuantumComputation> qc;
};
