#include "contract.h"
#include <algorithm>
#include <chrono>
#include <random>

void contract::add_to_contract(const disciplina &x) {

  for (const auto &y : c_list) {
    if (x == y) {
      throw contractException("Exista djea disciplina: " + x.get_denumire());
    }
  }
  c_list.push_back(x);
  notify();
}

void contract::delete_all() {
  c_list.clear();
  notify();
}

const std::vector<disciplina> &contract::get_all() { return c_list; }

void contract::addrandom_to_contract(long unsigned int nr) {
  std::vector<disciplina> list = repo.get_all();
  c_list.clear();
  std::shuffle(list.begin(), list.end(),
               std::default_random_engine(std::random_device{}()));
  while (c_list.size() < nr && list.size() > 0) {
    c_list.push_back(list.back());
    list.pop_back();
  }

  notify();
}
