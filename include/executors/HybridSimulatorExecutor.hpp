#pragma once

#include "HybridSchrodingerFeynmanSimulator.hpp"
#include "SimulationExecutor.hpp"

class HybridSimulatorExecutor
    : public SimulationExecutor<HybridSchrodingerFeynmanSimulator<>> {
public:
  [[nodiscard]] std::string getIdentifier() const override {
    if (runDD) {
      return "hybrid_schrodinger_feynman_simulator_dd";
    }
    return "hybrid_schrodinger_feynman_simulator_amplitude";
  };

  std::unique_ptr<HybridSchrodingerFeynmanSimulator<>>
  constructSimulator(const SimulationTask& task) override;

  json runSimulator(
      std::unique_ptr<HybridSchrodingerFeynmanSimulator<>> simulator) override;

  [[nodiscard]] bool isRunAmplitude() const { return runAmplitude; }

  void setRunAmplitude(bool run) { runAmplitude = run; }

  [[nodiscard]] bool isRunDd() const { return runDD; }

  void setRunDd(bool run) { runDD = run; }

private:
  bool runAmplitude = true;
  bool runDD        = false;
};
