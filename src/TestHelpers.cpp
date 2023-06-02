#include "TestHelpers.hpp"

#include <iostream>

void printAll(const nlohmann::json& jsonObject) {
  for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
    const auto& key   = it.key();
    const auto& value = it.value();
    std::cout << key << ": " << value << std::endl;
  }
}
