#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

#include <memory>

class VerificationTask : public Task {
public:
  VerificationTask() = default;
  VerificationTask(std::unique_ptr<qc::QuantumComputation> qc1,
                   std::unique_ptr<qc::QuantumComputation> qc2)
      : qc1(std::move(qc1)), qc2(std::move(qc2)) {}
  [[nodiscard]] std::string getIdentifier() const override {
    return "ver_" + qc1->getName() + "_" + qc2->getName();
  };

protected:
  std::unique_ptr<qc::QuantumComputation> qc1;
  std::unique_ptr<qc::QuantumComputation> qc2;

public:
  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc1() const {
    return qc1;
  };

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc2() const {
    return qc2;
  };
};
