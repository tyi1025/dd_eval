//
// Created by Tianyi Wang on 5/14/23.
//

#ifndef DD_EVAL_EXECUTOR_HPP
#define DD_EVAL_EXECUTOR_HPP

#endif // DD_EVAL_EXECUTOR_HPP

#include "Task.hpp"

class Executor {
private:
  Task* task;
};

void executeTask(Task* task) { task->execute(); }
