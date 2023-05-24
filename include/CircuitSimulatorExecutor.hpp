#pragma once

#include "SimulationExecutor.hpp"

class CircuitSimulatorExecutor : public SimulationExecutor {
public:
  json        executeTask() override;
  std::string getIdentifier() override;
};
