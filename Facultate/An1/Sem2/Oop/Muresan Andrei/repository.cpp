#include "repository.h"
#include "my_vector.h"
#include <algorithm> // NOLINT
#include <vector>

void repository::add(const disciplina &x) {

  if (exist(x)) {
    throw repoException("Exista deja disciplina: " + x.get_denumire());
  }
  list.push_back(x);
}

bool repository::exist(const disciplina &x) const {

  try {
    find(x);
    return true;
  } catch (repoException &) {
    return false;
  }
}

const disciplina &repository::find(const disciplina &x) const {

  for (const auto &y : list) {
    if (x == y) {
      return y;
    }
  }

  throw repoException("Nu exista disciplina: " + x.get_denumire());
}

const std::vector<disciplina> &repository::get_all() const noexcept {

  return list;
}

std::ostream &operator<<(std::ostream &out, const repoException &ex) {

  out << ex.msg;
  return out;
}

void repository::remove(const disciplina &x) {

  if (!exist(x)) {
    throw repoException("Nu exista disciplina: " + x.get_denumire());
  }
  list.erase(std::remove(list.begin(), list.end(), x));
  // list.remove(x);
}

void repository::modify(const disciplina &x) {

  bool ok = false;
  for (auto &y : list) {
    if (x == y) {
      y.set_ore(x.get_ore());
      y.set_tip(x.get_tip());
      y.set_profesor(x.get_profesor());
      ok = true;
      break;
    }
  }
  if (!ok) {
    throw repoException("Nu exista disciplina: " + x.get_denumire());
  }
}