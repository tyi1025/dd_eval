#pragma once

#include "Executor.hpp"
#include "tasks/SimulationTask.hpp"

class HybridSimulatorExecutor : public Executor<SimulationTask> {
public:
  json execute(const SimulationTask& task) override;

  [[nodiscard]] std::string getIdentifier() const override {
    if (runDD) {
      return "hybrid_schrodinger_feynman_simulator_dd";
    }
    return "hybrid_schrodinger_feynman_simulator_amplitude";
  };

  [[nodiscard]] bool isRunAmplitude() const { return runAmplitude; }

  void setRunAmplitude(bool run) { runAmplitude = run; }

  [[nodiscard]] bool isRunDd() const { return runDD; }

  void setRunDd(bool run) { runDD = run; }

private:
  bool runAmplitude = true;
  bool runDD        = false;
};
