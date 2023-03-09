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

  const vector<melodie> &getAll() const noexcept { return repo.getAll(); };

  const vector<melodie> sortByRank();

  const vector<std::pair<melodie, int>> raportSameRank();

  const melodie &find(int id, string titlu, string autor, int rank) const;

  void modify(int id, string titlu, string autor, int rank) const;
};
#endif // SERVICES_H
