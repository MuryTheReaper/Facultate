#ifndef MELODIE_H
#define MELODIE_H

//#include <QWidget>

#include <iostream>
#include <string>
using std::string;

class melodie {
private:
  int id; // unic
  string titlu;
  string artist;
  int rank; // intre 0 si 10

public:
  // constructor
  melodie(const int &id, const string &titlu, const string &artist,
          const int &rank)
      : id{id}, titlu{titlu}, artist{artist}, rank{rank} {};

  // copy constructor
  melodie(const melodie &x)
      : id{x.id}, titlu{x.titlu}, artist{x.artist}, rank{x.rank} {};

  // destructor
  ~melodie() = default;

  melodie(melodie &&) = default;

  melodie &operator=(melodie &&) = default;

  melodie &operator=(const melodie &) = default;

  // operatorul == (egalitate doar daca ID-uri egale)
  friend bool operator==(const melodie &x, const melodie &y) {
    return y.id == x.id;
  }

  // toate getterele/setterele

  const int getId() const noexcept { return id; }
  const string getTitlu() const noexcept { return titlu; }
  const string getArtist() const noexcept { return artist; }
  const int getRank() const noexcept { return rank; }
  void setRank(int r) noexcept { rank = r; }
  void setTitlu(string t) noexcept { titlu = t; }
};
#endif // MELODIE_H
