#include "services.h"
#include <algorithm>

// clang-format off
const vector<device> services::filterByModel(const std::string &model) const {
  vector<device> rez;
  std::copy_if(repo.get_all().begin(), repo.get_all().end(),
               std::back_inserter(rez),
               [&model](const device &x) { return x.get_model() == model; });

  return rez;};

const vector<device> services::filterByAn(const int &an) const {
  vector<device> rez;
  std::copy_if(repo.get_all().begin(), repo.get_all().end(),
               std::back_inserter(rez),
               [&an](const device &x) { return x.get_an() == an; });

  return rez;};
// clang-format on
