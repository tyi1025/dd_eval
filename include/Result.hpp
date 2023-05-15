//
// Created by Tianyi Wang on 5/14/23.
//

#ifndef DD_EVAL_RESULT_HPP
#define DD_EVAL_RESULT_HPP


#include "ResultBase.hpp"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Result : public ResultBase {
public:
    Result(const std::string& name, double value);

    json toJson() const override;
    std::string toString() const override;

private:
    std::string name_;
    double value_;
};

#endif  // DD_EVAL_RESULT_HPP

