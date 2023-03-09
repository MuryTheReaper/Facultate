#include "services.h"

#include <algorithm>

const vector<melodie> services::sortByRank() {
  vector<melodie> rez{this->getAll()};

  std::sort(rez.begin(), rez.end(), [](const melodie &x, const melodie &y) {
    return x.getRank() < y.getRank();
  });

  return rez;
};

const vector<std::pair<melodie, int>> services::raportSameRank() {

  vector<melodie> list{sortByRank()};
  vector<std::pair<melodie, int>> rez;

  for (const auto &x : list) {
    std::pair<melodie, int> el{x, -1};

    for (const auto &m : list) {
      if (m.getRank() == x.getRank()) {
        el.second++;
      }
    }

    rez.push_back(el);
  }
  return rez;
}

const melodie &services::find(int id, string titlu, string autor,
                              int rank) const {
  melodie x{id, titlu, autor, rank};

  return repo.find(x);
}

void services::modify(int id, string titlu, string autor, int rank) const {
  melodie x{id, titlu, autor, rank};

  repo.modify(x);
}
