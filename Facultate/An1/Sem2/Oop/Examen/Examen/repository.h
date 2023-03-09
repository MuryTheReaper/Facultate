#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "muzica.h"
#include <vector>

using std::vector;

class repository {
private:
  // lsita cu melodii
  vector<melodie> list;

  // fisierul din care se incarca datele
  string file;

  // fucntia de incarcare date
  void loadFromFile();

  // functia de pus date in fisier
  void storeToFile();

public:
  // constructor
  repository(const string &file) : file{file} { loadFromFile(); };

  // copy constroctor(deleted)
  repository(const repository &x) = delete;

  ~repository() = default;

  // orice forma de copiere este deleted
  repository &operator=(const repository &) = delete;

  repository(repository &&) = default;

  repository &operator=(repository &&) = delete;

  // fuctie de returnat lista cu melodii
  const vector<melodie> &getAll() const noexcept;

  // fucntie care modifica o melodie
  void modify(const melodie &x);

  // functie care sterge o melodie
  void remove(const melodie &x);

  // functie care returneaza melodiea cautata
  // arunca exceptie daca nu se gasete
  const melodie &find(const melodie &x) const;
};

#endif // REPOSITORY_H
