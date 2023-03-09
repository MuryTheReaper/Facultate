#include "repository.h"
#include <fstream>

using std::ifstream;

void repository::loadFromFile() {

  ifstream f(file);
  const int maxsize = 5;
  vector<string> tokens;
  string line;
  while (getline(f, line, ';')) {
    tokens.push_back(line);
    if (tokens.size() == maxsize) {

      string tip{tokens[0]};
      if (tip[0] == '\n') {
        tip.erase(tip.begin(), tip.begin() + 1);
      }
      string model{tokens[1]};
      int an{std::stoi(tokens[2])};
      string culoare{tokens[3]};
      int pret{std::stoi(tokens[4])};

      device x{tip, model, an, culoare, pret};
      list.push_back(x);
      tokens.clear();
    }
  };

  f.close();
};

const vector<device> &repository::get_all() const noexcept { return list; }
