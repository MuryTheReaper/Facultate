#ifndef SERVICES_H
#define SERVICES_H
#include "repository.h"

class services {

private:
  // adresa catre repository
  repository &repo;

public:
  // constructor
  services(repository &repo) : repo{repo} {};

  services(const services &x) = delete;

  ~services() = default;

  services &operator=(const services &) = delete;

  services(services &&) = default;

  services &operator=(services &&) = delete;

  // functie care returneaza lista cu toate melodiile
  const vector<melodie> &getAll() const noexcept { return repo.getAll(); };

  // functie care returneaza lista cu melodiile ordonate crescator dupa rank
  const vector<melodie> sortByRank();

  // functie care retunreaza lista cu pereche melodie,int
  // int se refera la cate melodii au acelasi rank cu melodia respectiva
  const vector<std::pair<melodie, int>> raportSameRank();

  // functie care returneaza melodia cautata
  const melodie &find(int id, string titlu, string autor, int rank) const;

  // functie care modifica melodia cu id respectiv
  void modify(int id, string titlu, string autor, int rank) const;

  // functie care sterge melodia respectiva
  void remove(int id, string titlu, string autor, int rank) const;

  // functie care returneaza cate melodii are un artist
  int nrArtist(string autor) const;

  // functie care returneaza un vector de frecventa
  // pentru fiecare rank existent
  vector<int> nrRank();
};
#endif // SERVICES_H
