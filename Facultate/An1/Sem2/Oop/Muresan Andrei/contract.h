#pragma once
#include "disciplina.h"
#include <vector>
class contract {
private:
  std::vector<disciplina> c_list;

public:
  contract() = default;

  void add_to_contract(const disciplina &x);

  void addrandom_to_contract(std::vector<disciplina> list,
                             long unsigned int nr);

  void delete_all();

  const std::vector<disciplina> &get_all();
};