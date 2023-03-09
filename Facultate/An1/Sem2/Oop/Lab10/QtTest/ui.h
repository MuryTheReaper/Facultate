#pragma once
#include "services.h"
//#include ""

class ui {

private:
  services &serv;

  void print(const std::vector<disciplina> x);

  void add_ui();

  void add_random_ui();

  void remove_ui();

  void find_ui();

  void modify_ui();

  void filter_ui();

  void sort_ui();

  void contract_ui();

  void add_contract_ui();

  void generate_contract_ui();

  void delete_contract_ui();

  void export_contract_ui();

  void raport_ui();

  void print_raport_prof_frec(
      const std::unordered_map<std::string, profesor_frecventa> &x);

  void undo_ui();

public:
  ui(services &serv) : serv{serv} {}

  ui(const ui &x) = delete;

  ~ui() = default;

  ui &operator=(const ui &) = delete;

  ui(ui &&) = default;

  ui &operator=(ui &&) = delete;

  void run();
};