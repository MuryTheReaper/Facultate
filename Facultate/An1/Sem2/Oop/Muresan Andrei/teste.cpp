#include "teste.h"
#include "disciplina.h"
#include "my_vector.h"
#include "raport.h"
#include "services.h"
#include <assert.h> // NOLINT
#include <fstream>
#include <sstream> // NOLINT
#include <string>
#include <utility> // NOLINT

void test_add() {

  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("a", "1", "b", "c");
  assert(repo.get_all().size() == 1);
  serv.add("x", "1", "b", "c");
  assert(repo.get_all().size() == 2);

  try {
    serv.add("x", "1", "b", "c");assert(false);
  } catch (const repoException &ex) {
    std::stringstream os;
    os << ex;
  }
}
void test_remove() {

  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("a", "1", "b", "c");
  assert(repo.get_all().size() == 1);

  serv.remove("a", "1", "b", "c");
  assert(repo.get_all().size() == 0);

  serv.add("a", "1", "b", "c");
  serv.add("b", "1", "b", "c");
  serv.add("c", "1", "b", "c");
  serv.add("d", "1", "b", "c");

  serv.remove("a", "1", "b", "c");
  assert(repo.get_all().size() == 3);

  try {
    disciplina x{"x", 1, "b", "c"};
    repo.remove(x);assert(false);
  } catch (const repoException &ex) {
    std::stringstream os;
    os << ex;
    assert(os.str().find("Nu exista disciplina: x") >= 0);
  }
}

void test_modify() {

  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("a", "1", "b", "c");
  assert(serv.get_all().size() == 1);
  serv.modify("a", "2", "c", "d");
  disciplina x = serv.find("a", "2", "c", "d");
  assert(x.get_denumire() == "a");
  assert(x.get_ore() == 2);
  assert(x.get_tip() == "c");
  assert(x.get_profesor() == "d");

  x.set_disciplina("x");
  x.set_tip("x");
  x.set_profesor("x");
  x.set_ore(1);

  disciplina y{"a", 1, "b", "c"};
  disciplina z{"b", 1, "b", "c"};
  z = std::move(y);
  y = z;

  assert(x.get_denumire() == "x");
  assert(x.get_ore() == 1);
  assert(x.get_tip() == "x");
  assert(x.get_profesor() == "x");

  try {
    disciplina x{"b", 2, "c", "d"};
    repo.modify(x);assert(false);
  } catch (const repoException &ex) {
    std::stringstream os;
    os << ex;
    assert(os.str().find("Nu exista disciplina: b") >= 0);
  }
}

void test_filter() {

  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("a", "1", "b", "p1");
  serv.add("b", "10", "b", "p2");
  serv.add("c", "20", "b", "p1");

  assert(serv.filter_ore_up("5").size() == 2);
  assert(serv.filter_profesor("p1").size() == 2);
}

void test_sort() {

  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("x", "10", "b", "p1");
  serv.add("y", "1", "b", "p2");
  serv.add("a", "20", "c", "p1");

  assert(serv.sort_denumire()[0].get_denumire() == "a");
  assert(serv.sort_ore()[0].get_denumire() == "y");
  assert(serv.sort_mix()[0].get_denumire() == "x");
}
void test_validate() {

  validator val;
  try {
    val.validate(".", "1", ".", ".");
    assert(true);
    val.validate("", "abcd", "", "");assert(false);
  } catch (const validateException &ex) {
    std::stringstream os;
    os << ex;
    auto mesaj = os.str();
    assert(mesaj.find("invalid") >= 0);
    assert(mesaj.find("vid") >= 0);
  }
}
/*void test_vector() {
  vector_dinamic<int> x;
  assert(x.size() == 0);
  x.remove(2);
  assert(x.size() == 0);
}*/

void test_contract() {
  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("x", "10", "b", "p1");
  serv.add("y", "1", "b", "p2");
  serv.add("a", "20", "c", "p1");

  serv.add_to_contract("x", "1", ".", ".");
  serv.add_to_contract("a", "1", ".", ".");

  assert(serv.get_all_contract()[0].get_denumire() == "x");
  assert(serv.get_all_contract()[1].get_denumire() == "a");

  serv.delete_all_contract();
  assert(serv.get_all_contract().size() == 0);

  serv.addrandom_to_contract(1);
  assert(serv.get_all_contract()[0].get_denumire() == "x" ||
         serv.get_all_contract()[0].get_denumire() == "a" ||
         serv.get_all_contract()[0].get_denumire() == "y");

  serv.delete_all_contract();
  serv.add_to_contract("x", "1", ".", ".");

  serv.export_contract("testing");

  std::ifstream f("testing.csv");
  std::string str;
  f >> str;
  assert(str == "x,b,p1,10");
}

void test_raport() {
  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("y", "1", "b", "p2");
  serv.add("a", "20", "c", "p1");
  serv.add("x", "20", "c", "p1");

  assert(serv.raport_profesor_frecventa().find("p2")->second.get_frecventa() ==
         1);
  assert(serv.raport_profesor_frecventa().find("p1")->second.get_frecventa() ==
         2);
}

void test_undo() {
  repository repo;
  validator val;
  services serv{repo, val};

  serv.add("y", "1", "b", "p2");
  assert(repo.get_all()[0].get_denumire() == "y");
  serv.undo();
  assert(repo.get_all().size() == 0);

  serv.add("y", "1", "b", "p2");
  serv.remove("y", "1", ".", ".");

  assert(repo.get_all().size() == 0);
  serv.undo();

  assert(repo.get_all()[0].get_denumire() == "y");

  serv.modify("y", "2", "c", "p3");

  serv.undo();

  assert(repo.get_all()[0].get_ore() == 1);
  assert(repo.get_all()[0].get_profesor() == "p2");
  assert(repo.get_all()[0].get_tip() == "b");

  serv.undo();

  try {
    serv.undo();assert(false);
  } catch (const servException &ex) {
    std::stringstream os;
    os << ex;
    assert(true);
  }
}
void test_all() {

  test_add();
  test_remove();
  test_modify();
  test_filter();
  test_sort();
  test_validate();
  // test_vector();
  test_contract();
  test_raport();
  test_undo();
}