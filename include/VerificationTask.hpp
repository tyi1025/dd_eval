#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

class VerificationTask : public Task {
public:
  VerificationTask() = default;
  VerificationTask(std::unique_ptr<qc::QuantumComputation> qc1,
                   std::unique_ptr<qc::QuantumComputation> qc2)
      : qc1(std::move(qc1)), qc2(std::move(qc2)) {}
  std::string getIdentifier() override;

protected:
  std::unique_ptr<qc::QuantumComputation> qc1;
  std::unique_ptr<qc::QuantumComputation> qc2;

public:
  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc1() const;

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc2() const;
};
