//
// Created by Tianyi Wang on 5/14/23.
//

#include "../include/Result.hpp"

Result::Result(const std::string& name, double value)
    : name_(name), value_(value) {}

json Result::toJson() const {
  json resultJson;
  resultJson["name"]  = name_;
  resultJson["value"] = value_;
  return resultJson;
}

std::string Result::toString() const { return toJson().dump(); }
