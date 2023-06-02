#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

class SimulationTask : public Task {
public:
  SimulationTask() = default;

  explicit SimulationTask(std::unique_ptr<qc::QuantumComputation> qc)
      : qc(std::move(qc)) {}

protected:
  std::unique_ptr<qc::QuantumComputation> qc;

public:
  std::string getIdentifier() override;
};
