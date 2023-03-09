#include "contract.h"
#include <algorithm>
#include <chrono>
#include <random>

void contract::add_to_contract(const disciplina &x) { c_list.push_back(x); }

void contract::delete_all() { c_list.clear(); }

const std::vector<disciplina> &contract::get_all() { return c_list; }

void contract::addrandom_to_contract(std::vector<disciplina> list,
                                     long unsigned int nr) {
  c_list.clear();
  std::shuffle(list.begin(), list.end(),
               std::default_random_engine(std::random_device{}()));
  while (c_list.size() < nr && list.size() > 0) {
    c_list.push_back(list.back());
    list.pop_back();
  }
}