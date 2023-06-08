#pragma once

class Task {
public:
  virtual ~Task()                                         = default;
  [[nodiscard]] virtual std::string getIdentifier() const = 0;
};
