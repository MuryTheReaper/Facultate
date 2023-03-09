#pragma once
#include "disciplina.h"
#include "observer.h"
#include "repository.h"
#include <vector>

class contract : public observable {
private:
  std::vector<disciplina> c_list;
  const repository &repo;

public:
  contract(const repository &repo) : repo{repo} {};

  void add_to_contract(const disciplina &x);

  void addrandom_to_contract(long unsigned int nr);

  void delete_all();

  const std::vector<disciplina> &get_all();

  const repository &get_repo() { return repo; }
};

class contractException {

private:
  std::string msg;

public:
  contractException(std::string m) : msg{m} {}
  std::string getMsg() const { return msg; }
  //  friend std::ostream &operator<<(std::ostream &out,
  //                                  const contractException &ex);
};
