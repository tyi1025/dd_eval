#pragma once

#include "Task.hpp"

#include <memory>

class Executor {
public:
  virtual ~Executor()        = default;
  virtual json executeTask() = 0;
  explicit Executor()        = default;
  //  virtual const std::unique_ptr<Task>& getTask();
  //  virtual void                         setTask(const std::unique_ptr<Task>
  //  &task);
  virtual std::string getIdentifier() = 0;

private:
  std::unique_ptr<Task> mTask;
};
