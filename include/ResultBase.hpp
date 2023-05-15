//
// Created by Tianyi Wang on 5/15/23.
//

#ifndef DD_EVAL_RESULTBASE_HPP
#define DD_EVAL_RESULTBASE_HPP

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ResultBase {
public:
    virtual ~ResultBase() = default;

    virtual json toJson() const = 0;
    virtual std::string toString() const = 0;
};


#endif //DD_EVAL_RESULTBASE_HPP

