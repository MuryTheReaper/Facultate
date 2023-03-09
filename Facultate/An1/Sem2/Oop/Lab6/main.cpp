#include "teste.h"
#include "ui.h"
#include "validator.h"

int main() {

  repository repo;
  validator val;
  services serv{repo, val};
  ui console{serv};
  console.run();
  // test_all();

  std::cout << "END\n";
}