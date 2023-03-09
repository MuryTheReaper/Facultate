#include "services.h"
#include "disciplina.h"
#include "repository.h"
#include "undo.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>
#include <memory>
#include <random>
#include <vector>

void services::add(const std::string &denumire, const std::string &ore,
                   const std::string &tip, const std::string &profesor) {

  val.validate(denumire, ore, tip, profesor);
  disciplina x{denumire, std::stoi(ore), tip, profesor};
  repo.add(x);
  undoList.push_back(std::make_unique<UndoAdd>(x, repo));
}

void services::remove(const std::string &denumire, const std::string &ore,
                      const std::string &tip, const std::string &profesor) {

  val.validate(denumire, ore, tip, profesor);
  disciplina x{denumire, std::stoi(ore), tip, profesor};
  undoList.push_back(std::make_unique<UndoRemove>(repo.find(x), repo));
  repo.remove(x);
}

const disciplina &services::find(const std::string &denumire,
                                 const std::string &ore, const std::string &tip,
                                 const std::string &profesor) {

  val.validate(denumire, ore, tip, profesor);
  disciplina x{denumire, std::stoi(ore), tip, profesor};
  return repo.find(x);
}

void services::modify(const std::string &denumire, const std::string &ore,
                      const std::string &tip, const std::string &profesor) {

  val.validate(denumire, ore, tip, profesor);
  disciplina x{denumire, std::stoi(ore), tip, profesor};
  undoList.push_back(std::make_unique<UndoModify>(repo.find(x), repo));
  repo.modify(x);
}

/*const std::vector<disciplina>
services::filter(std::function<bool(const disciplina &)> fct) const {

  std::vector<disciplina> rez;
  for (const auto &x : repo.get_all()) {
    if (fct(x)) {
      rez.push_back(x);
    }
  }
  return rez;
}*/
const std::vector<disciplina>
services::filter_stl(std::function<bool(const disciplina &)> fct) const {
  std::vector<disciplina> rez;

  std::copy_if(repo.get_all().begin(), repo.get_all().end(),
               std::back_inserter(rez), fct);

  return rez;
}

const std::vector<disciplina>
services::filter_ore_up(const std::string &ore) const {

  val.validate(".", ore, ".", ".");
  int o = std::stoi(ore);
  return filter_stl([o](const disciplina &x) { return x.get_ore() > o; });
}

const std::vector<disciplina>
services::filter_profesor(const std::string &profesor) const {

  val.validate(".", "1", ".", profesor);
  return filter_stl(
      [&](const disciplina &x) { return x.get_profesor() == profesor; });
}

/*const std::vector<disciplina> services::sort(
    std::function<bool(const disciplina &, const disciplina &)> fct) const {

  std::vector<disciplina> v{repo.get_all()};
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = i + 1; j < v.size(); j++) {
      if (!fct(v[i], v[j])) {
        disciplina aux = v[i];
        v[i] = v[j];
        v[j] = aux;
      }
    }
  }
  return v;
}*/

const std::vector<disciplina> services::sort_stl(
    std::function<bool(const disciplina &, const disciplina &)> fct) const {

  std::vector<disciplina> v{repo.get_all()};
  std::sort(v.begin(), v.end(), fct);

  return v;
}

const std::vector<disciplina> services::sort_denumire() {

  return sort_stl([](const disciplina &x, const disciplina &y) {
    return x.get_denumire() < y.get_denumire();
  });
}

const std::vector<disciplina> services::sort_ore() {

  return sort_stl([](const disciplina &x, const disciplina &y) {
    return x.get_ore() < y.get_ore();
  });
}

const std::vector<disciplina> services::sort_mix() {

  return sort_stl([](const disciplina &x, const disciplina &y) {
    if (x.get_profesor() == y.get_profesor()) {
      return x.get_tip() < y.get_tip();
    }
    return x.get_profesor() < y.get_profesor();
  });
}

void services::add_to_contract(const std::string &denumire,
                               const std::string &ore, const std::string &tip,
                               const std::string &profesor) {
  val.validate(denumire, ore, tip, profesor);
  disciplina x{denumire, std::stoi(ore), tip, profesor};
  contr.add_to_contract(repo.find(x));
}

void services::addrandom_to_contract(long unsigned int nr) {
  contr.addrandom_to_contract(nr);
}

void services::export_contract(std::string file) {
  file.append(".csv");
  std::ofstream f(file);

  const std::vector<disciplina> &list{get_all_contract()};

  for (const auto &disc : list) {
    f << disc.get_denumire() << "," << disc.get_tip() << ","
      << disc.get_profesor() << "," << disc.get_ore() << "\n";
  }

  f.close();
}

const std::unordered_map<std::string, profesor_frecventa> &
services::raport_profesor_frecventa() {

  rap.make_raport_prof_frec(get_all());
  return rap.get_raport();
}

std::ostream &operator<<(std::ostream &out, const servException &ex) {

  out << ex.msg;
  return out;
}

void services::undo() {
  if (undoList.empty()) {
    throw servException("Nu mai exista operatii");
  }

  undoList.back()->do_undo();
  undoList.pop_back();
}

void services::addrandom(const std::string &nr) {
  int n = std::stoi(nr);
  while (n) {
    std::mt19937 mt{std::random_device{}()};
    const int size = 1000;
    std::uniform_int_distribution<> dist(0, size - 1);
    std::string o = std::to_string(dist(mt)); // numar aleator intre [0,size-1]

    const int size_l = 10;
    auto randchar = []() -> char {
      const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz";
      const size_t max_index = (charset.size() - 1);
      return charset[rand() % max_index];
    };
    std::uniform_int_distribution<> dist_l(1, size_l - 1);
    const int length = dist_l(mt);
    std::string d(length, 0);
    std::string t(length, 0);
    std::string p(length, 0);

    std::generate_n(d.begin(), length, randchar);
    std::generate_n(t.begin(), length, randchar);
    std::generate_n(p.begin(), length, randchar);

    val.validate(d, o, t, p);
    disciplina x{d, std::stoi(o), t, p};
    repo.add(x);
    n--;
  }
}
