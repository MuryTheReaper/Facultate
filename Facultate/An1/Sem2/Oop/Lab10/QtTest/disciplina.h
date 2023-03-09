#pragma once
#include <iostream> // NOLINT
#include <ostream>  // NOLINT

class disciplina {

private:
  std::string denumire;
  int ore;
  std::string tip;
  std::string profesor;

public:
  disciplina() : ore{0} {}

  disciplina(const std::string &denumire, const int &ore,
             const std::string &tip, const std::string &profesor)
      : denumire{denumire}, ore{ore}, tip{tip}, profesor{profesor} {}

  ~disciplina() = default;

  disciplina &operator=(const disciplina &) = default;

  disciplina(disciplina &&) = default;

  disciplina &operator=(disciplina &&) = default;

  disciplina(const disciplina &x)
      : denumire{x.denumire}, ore{x.ore}, tip{x.tip}, profesor{x.profesor} {
    // std::cout << "Copy constructor was used\n";
  }

  const std::string get_denumire() const noexcept { return denumire; }

  const int get_ore() const noexcept { return ore; }

  const std::string get_tip() const noexcept { return tip; }

  const std::string get_profesor() const noexcept { return profesor; }

  void set_disciplina(const std::string &x) noexcept { denumire = x; }

  void set_tip(const std::string &x) noexcept { tip = x; }

  void set_ore(const int &x) noexcept { ore = x; }

  void set_profesor(const std::string &x) noexcept { profesor = x; }

  friend bool operator==(const disciplina &x, const disciplina &y);
};