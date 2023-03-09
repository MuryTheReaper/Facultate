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

  const std::vector<device> &get_all() const noexcept {
    return repo.get_all();
  };
};
#endif // SERVICES_H
