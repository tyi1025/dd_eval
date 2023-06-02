#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

class SimulationTask : public Task {
public:
  SimulationTask() = default;

  explicit SimulationTask(std::unique_ptr<qc::QuantumComputation> qc)
      : qc(std::move(qc)) {}

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc() const;
  std::string getIdentifier() override;

protected:
  std::unique_ptr<qc::QuantumComputation> qc;
};
