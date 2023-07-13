#pragma once

#include "Executor.hpp"
#include "tasks/VerificationTask.hpp"

class EquivalenceCheckerExecutor : public Executor<VerificationTask> {
public:
  json execute(const VerificationTask& task) override;

  [[nodiscard]] std::string getIdentifier() const override {
    return "equivalence_checker";
  }
  bool runConstructionChecker = false;
  bool runSimulationChecker   = false;
  bool runAlternatingChecker  = true;

  void setRunConstructionChecker(bool run) {
    this->runConstructionChecker = run;
  };

  void setRunSimulationChecker(bool run) { this->runSimulationChecker = run; };

  void setRunAlternatingChecker(bool run) {
    this->runAlternatingChecker = run;
  };

  bool sequentialApplicationScheme = false;
  bool oneToOneApplicationScheme   = false;

  bool proportionalApplicationScheme = true;
  bool lookaheadApplicationScheme    = false;
  bool gateCostApplicationScheme     = false;

  void setSequentialApplicationScheme(bool ac) {
    this->sequentialApplicationScheme = ac;
  };

  void setOneToOneApplicationScheme(bool ac) {
    this->oneToOneApplicationScheme = ac;
  };

  void setProportionalApplicationScheme(bool ac) {
    this->proportionalApplicationScheme = ac;
  };

  void setLookaheadApplicationScheme(bool ac) {
    this->lookaheadApplicationScheme = ac;
  };

  void setGateCostApplicationScheme(bool ac) {
    this->gateCostApplicationScheme = ac;
  };
};
