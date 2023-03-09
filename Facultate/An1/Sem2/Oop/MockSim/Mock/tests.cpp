#include "assert.h"
#include "repository.h"
// clang-format off

void test_read() {
  repository repo{"input.txt"};
  auto x=repo.get_all();

  assert(x[0].get_tip()=="tip1");
  assert(x[1].get_tip()=="tip2");
  assert(x[3].get_tip()=="tip4");
  //std::cout<<x[1].get_tip();
}

void run_tests() { test_read(); }
// clang-format on
