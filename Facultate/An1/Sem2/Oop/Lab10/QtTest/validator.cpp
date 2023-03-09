#include "validator.h"
#include <string.h> // NOLINT

std::ostream &operator<<(std::ostream &out, const validateException &ex) {
  for (const auto &msgs : ex.msg) {
    out << msgs + " ";
  }
  return out;
}

void validator::validate(const std::string &denumire, const std::string &ore,
                         const std::string &tip, const std::string &profesor) {

  std::vector<std::string> msgs;
  if (denumire.size() == 0) {
    msgs.push_back("Denumire vida!");
  }
  if (tip.size() == 0) {
    msgs.push_back("Tip vid!");
  }
  if (profesor.size() == 0) {
    msgs.push_back("Profesor vid!");
  }
  for (const auto &c : ore) {
    if (strchr("0123456789", c) == nullptr) {
      msgs.push_back("Numar de ore invalid!");
      break;
    }
  }

  if (msgs.size() > 0) {
    throw validateException(msgs);
  }
}

std::string validateException::getMsg() const {
  std::string msgs;
  for (const auto &x : msg) {
    msgs.append(x);
    msgs.append("\n");
  }
  // msgs.erase()
  return msgs;
}
