#pragma once

#include "QuantumComputation.hpp"
#include "Task.hpp"

#include <memory>

class VerificationTask : public Task {
public:
  explicit VerificationTask() = default;
  VerificationTask(std::unique_ptr<qc::QuantumComputation> circ1,
                   std::unique_ptr<qc::QuantumComputation> circ2)
      : qc1(std::move(circ1)), qc2(std::move(circ2)) {}

  [[nodiscard]] std::string getIdentifier() const override {
    return "ver_" + qc1->getName() + "_" + qc2->getName();
  };

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc1() const {
    return qc1;
  };

  [[nodiscard]] const std::unique_ptr<qc::QuantumComputation>& getQc2() const {
    return qc2;
  };

protected:
  std::unique_ptr<qc::QuantumComputation> qc1;
  std::unique_ptr<qc::QuantumComputation> qc2;
};
