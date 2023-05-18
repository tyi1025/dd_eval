#pragma once

#include "Task.hpp"

#include <memory>

class Executor {
public:
  virtual ~Executor()        = default;
  virtual json executeTask() = 0;
  explicit Executor()        = default;
  const std::shared_ptr<Task>& getTask();
  void                         setTask(const std::shared_ptr<Task>& task);
  virtual std::string          getIdentifier() = 0;

private:
  std::shared_ptr<Task> task;
};
