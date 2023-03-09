#include "services.h"
#include <algorithm>
#include <exception>

// clang-format off
const vector<melodie> services::sortByRank() {
  vector<melodie> rez{this->getAll()};

  std::sort(rez.begin(), rez.end(), [](const melodie &x, const melodie &y) {
    return x.getRank() < y.getRank();
  });

  return rez;}; // clang-format on

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

void services::remove(int id, string titlu, string autor, int rank) const {

  melodie x{id, titlu, autor, rank};

  if (nrArtist(autor) > 1) {
    repo.remove(x);
  } else {
    throw std::exception();
  }
};

int services::nrArtist(string autor) const {

  int nr = 0;

  vector<melodie> list{getAll()};

  for (auto &x : list) {
    if (x.getArtist() == autor)
      nr++;
  }

  return nr;
}

vector<int> services::nrRank() {
  vector<int> rez;
  vector<melodie> list{getAll()};

  const int maxRank = 10;
  for (int i = 0; i <= maxRank; i++) {
    rez.push_back(0);
  }

  for (auto &x : list) {
    rez[x.getRank()]++;
  }

  return rez;
}
