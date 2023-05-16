#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Task {
public:
    virtual ~Task() = default;
    virtual std::string getIdentifier() = 0;
};
