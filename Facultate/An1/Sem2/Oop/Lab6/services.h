#pragma once
#include "contract.h"
#include "raport.h"
#include "repository.h"
#include "undo.h"
#include "validator.h"
#include <functional> // NOLINT
#include <memory>
#include <vector>

class services {

private:
  repository &repo;
  validator &val;
  contract contr;
  raport rap;

  std::vector<std::unique_ptr<UndoAction>> undoList;

  /*const std::vector<disciplina>
  filter(std::function<bool(const disciplina &)> fct) const;

  const std::vector<disciplina>
  sort(std::function<bool(const disciplina &, const disciplina &)> fct)
  const;
  */
  const std::vector<disciplina>
  filter_stl(std::function<bool(const disciplina &)> fct) const;

  const std::vector<disciplina> sort_stl(
      std::function<bool(const disciplina &, const disciplina &)> fct) const;

public:
  services(repository &repo, validator &val) : repo{repo}, val{val} {}

  services(const services &x) = delete;

  ~services() = default;

  services &operator=(const services &) = delete;

  services(services &&) = default;

  services &operator=(services &&) = delete;

  void add(const std::string &denumire, const std::string &ore,
           const std::string &tip, const std::string &profesor);

  void remove(const std::string &denumire, const std::string &ore,
              const std::string &tip, const std::string &profesor);

  void modify(const std::string &denumire, const std::string &ore,
              const std::string &tip, const std::string &profesor);

  const disciplina &find(const std::string &denumire, const std::string &ore,
                         const std::string &tip, const std::string &profesor);

  const std::vector<disciplina> &get_all() const noexcept {
    return repo.get_all();
  }

  const std::vector<disciplina> filter_ore_up(const std::string &ore) const;

  const std::vector<disciplina>
  filter_profesor(const std::string &profesor) const;

  const std::vector<disciplina> sort_denumire();

  const std::vector<disciplina> sort_ore();

  const std::vector<disciplina> sort_mix();

  void add_to_contract(const std::string &denumire, const std::string &ore,
                       const std::string &tip, const std::string &profesor);

  void addrandom_to_contract(long unsigned int nr);

  void delete_all_contract() { contr.delete_all(); }

  const std::vector<disciplina> &get_all_contract() { return contr.get_all(); }

  void export_contract(std::string file);

  const std::unordered_map<std::string, profesor_frecventa> &
  raport_profesor_frecventa();

  void undo();
};

class servException {

private:
  std::string msg;

public:
  servException(std::string m) : msg{m} {}

  friend std::ostream &operator<<(std::ostream &out, const servException &ex);
};