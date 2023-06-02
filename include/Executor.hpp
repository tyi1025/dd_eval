#pragma once

#include "Task.hpp"

#include <memory>

class Executor {
public:
  virtual ~Executor() = default;
  explicit Executor() = default;

  virtual json        executeTask()   = 0;
  virtual std::string getIdentifier() = 0;

private:
  std::unique_ptr<Task> task;
};
