#pragma once

#include "Task.hpp"

#include <memory>

class Executor {
public:
  virtual ~Executor()        = default;
  virtual json executeTask() = 0;

  const std::shared_ptr<Task>& getTask() const;

  explicit Executor(){};

  void                setTask(const std::shared_ptr<Task>& task);
  virtual std::string getIdentifier() = 0;

private:
  std::shared_ptr<Task> task;
};
