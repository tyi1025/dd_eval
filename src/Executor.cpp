#include "Executor.hpp"
#include <chrono>

class Executor::Executor {
    json executeTask() {
        json result;
        auto start = std::chrono::high_resolution_clock::now();

        this->executeTask();
        // Add memory usage later

        auto stop = std::chrono::high_resolution_clock::now();
        auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        result["runtime"] = runtime.count();
        std::string const identifier = this->getTask()->getIdentifier() + "_" + this->getIdentifier();
        result["identifier"] = identifier;
        return result;
        // what about the Results class?
    }
};

//add adapter for simulators
const std::shared_ptr<Task> &Executor::getTask() const {
    return task;
}

void Executor::setTask(const std::shared_ptr<Task> &newTask) {
    this->task = newTask;
}


