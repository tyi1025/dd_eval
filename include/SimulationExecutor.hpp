#pragma once

#include "Executor.hpp"
#include "QuantumComputation.hpp"
#include "Simulator.hpp"
#include "tasks/SimulationTask.hpp"

template <class S> class SimulationExecutor : public Executor<SimulationTask> {
  //    static_assert(std::is_base_of_v<Simulator<>, S>);
  //    How to use this while disregarding the template parameter of the
  //    Simulator class?
public:
  virtual std::unique_ptr<S>
  constructSimulator(std::unique_ptr<qc::QuantumComputation>& qc) = 0;

  virtual json runSimulator(std::unique_ptr<S> simulator) = 0;

  json execute(const SimulationTask& task) override {
    auto qc = std::make_unique<qc::QuantumComputation>(task.getQc()->clone());
    auto const constructionStart = std::chrono::steady_clock::now();
    auto       simulator         = constructSimulator(qc);
    auto const executionStart    = std::chrono::steady_clock::now();

    json       result        = runSimulator(std::move(simulator));
    auto const executionStop = std::chrono::steady_clock::now();
    // Add memory usage

    auto const constructionTime =
        std::chrono::duration_cast<std::chrono::microseconds>(
            executionStart - constructionStart);
    auto const execTime = std::chrono::duration_cast<std::chrono::microseconds>(
        executionStop - executionStart);
    result["construction_time"] = constructionTime.count();
    result["execution_time"]    = execTime.count();
    result["executor"]          = getIdentifier();
    result["task"]              = task.getIdentifier();

    return result;
  };
};
