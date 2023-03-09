#include "repository.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::ofstream;

void repository::loadFromFile() {

  ifstream f(file);
  const int maxsize = 4;
  vector<string> tokens;
  string line;
  while (getline(f, line, ';')) {
    tokens.push_back(line);
    if (tokens.size() == maxsize) {

      string t1{tokens[0]};
      if (t1[0] == '\n') {
        t1.erase(t1.begin(), t1.begin() + 1);
      }
      string t2{tokens[1]};
      string t3{tokens[2]};
      string t4{tokens[3]};

      melodie x{std::stoi(t1), t2, t3, std::stoi(t4)};
      list.push_back(x);
      tokens.clear();
    }
  };

  f.close();
};

void repository::storeToFile() {
  ofstream f(file);
  for (const auto &x : list) {
    f << x.getId() << ";" << x.getTitlu() << ";" << x.getArtist() << ";"
      << x.getRank() << ";\n";
  }
  f.close();
};

void repository::modify(const melodie &x) {
  for (auto &y : list) {
    if (x == y) {
      y.setRank(x.getRank());
      y.setTitlu(x.getTitlu());
    }
  }
  storeToFile();
}

const melodie &repository::find(const melodie &x) const {

  for (const auto &y : list) {
    if (x == y) {
      return y;
    }
  }

  throw std::exception();
}

void repository::remove(const melodie &x) {

  list.erase(std::remove(list.begin(), list.end(), x));
  storeToFile();
}

const vector<melodie> &repository::getAll() const noexcept { return list; }
