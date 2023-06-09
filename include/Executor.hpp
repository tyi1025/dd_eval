#pragma once

#include "Task.hpp"

#include <nlohmann/json.hpp>
#include <type_traits>

using json = nlohmann::json;

template <class T> class Executor {
  static_assert(std::is_base_of_v<Task, T>);

public:
  virtual ~Executor() = default;

  virtual json execute(const T& task) = 0;

  [[nodiscard]] virtual std::string getIdentifier() const = 0;
};
