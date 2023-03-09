#ifndef SERVICES_H
#define SERVICES_H
#include "repository.h"

class services {

private:
  repository &repo;

public:
  services(repository &repo) : repo{repo} {};

  services(const services &x) = delete;

  ~services() = default;

  services &operator=(const services &) = delete;

  services(services &&) = default;

  services &operator=(services &&) = delete;

  const vector<device> &get_all() const noexcept { return repo.get_all(); };

  const vector<device> filterByModel(const string &model) const;

  const vector<device> filterByAn(const int &an) const;
};
#endif // SERVICES_H
