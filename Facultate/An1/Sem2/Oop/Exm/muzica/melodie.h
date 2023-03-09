#ifndef MELODIE_H
#define MELODIE_H

#include <QWidget>

using std::string;

class melodie {
private:
  int id; // unic
  string titlu;
  string artist;
  int rank; // intre 0 si 10

public:
  melodie(const int &id, const string &titlu, const string &artist,
          const int &rank)
      : id{id}, titlu{titlu}, artist{artist}, rank{rank} {};

  melodie(const melodie &x)
      : id{x.id}, titlu{x.titlu}, artist{x.artist}, rank{x.rank} {};

  ~melodie() = default;

  melodie(melodie &&) = default;

  melodie &operator=(melodie &&) = default;

  melodie &operator=(const melodie &) = default;

  friend bool operator==(const melodie &x, const melodie &y) {
    return y.id == x.id;
  }

  // toate getterele

  const int getId() const noexcept { return id; }
  const string getTitlu() const noexcept { return titlu; }
  const string getArtist() const noexcept { return artist; }
  const int getRank() const noexcept { return rank; }
  void setRank(int r) noexcept { rank = r; }
};
#endif // MELODIE_H
