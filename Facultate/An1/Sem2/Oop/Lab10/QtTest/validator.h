#pragma once

#include "my_vector.h"
#include <string> // NOLINT
#include <vector> // NOLINT

class validator {

public:
  void validate(const std::string &denumire, const std::string &ore,
                const std::string &tip, const std::string &profesor);
};

class validateException {

private:
  std::vector<std::string> msg;

public:
  validateException(const std::vector<std::string> &errors) : msg{errors} {}
  std::string getMsg() const;
  friend std::ostream &operator<<(std::ostream &out,
                                  const validateException &ex);
};
