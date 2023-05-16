#pragma once

#include <nlohmann/json.hpp>
#include "Task.hpp"
#include "Executor.hpp"

using json = nlohmann::json;

class Results {
public:
    virtual ~Results() = default;

    virtual json toJson() const = 0;
    virtual std::string toString() const { return toJson().dump(2); }

    Results(Task task, Executor executor) {
        identifier = task.getIdentifier() + "_" + executor.getIdentifier();
    }


private:
    std::string identifier;
};
