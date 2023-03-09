#pragma once
#include "disciplina.h"
#include <string>
#include <unordered_map>
#include <vector>

class profesor_frecventa {
private:
  std::string profesor;
  int frecventa = 0;

public:
  profesor_frecventa() = default;

  const std::string get_profesor() const noexcept { return profesor; }

  void set_profesor(const std::string &x) noexcept { profesor = x; }

  const int get_frecventa() const noexcept { return frecventa; }

  void set_frecventa(const int &x) noexcept { frecventa = x; }

  void change_frecventa(const int &x) noexcept { frecventa += x; }
};

class raport {
private:
  std::unordered_map<std::string, profesor_frecventa> rap_prof_frec;

public:
  raport() = default;

  void make_raport_prof_frec(const std::vector<disciplina> &list);

  const std::unordered_map<std::string, profesor_frecventa> &get_raport() {
    return rap_prof_frec;
  }
};