#pragma once

#include "Nod.h"

#define NULL_TELEM -1
typedef int TElem;

class Nod;
typedef Nod *PNod;

#define MAX 2

class IteratorColectie;

class Colectie {
  friend class IteratorColectie;

private:
  int m;
  PNod *l;
  int size;
  int d(TElem e) const;
  void redim();

public:
  // constructorul implicit
  Colectie();

  // adauga un element in colectie
  void adauga(TElem e);

  // sterge o aparitie a unui element din colectie
  // returneaza adevarat daca s-a putut sterge
  bool sterge(TElem e);

  // verifica daca un element se afla in colectie
  bool cauta(TElem elem) const;

  // returnează numărul de elemente care apar de frecvență ori în colecție
  // aruncă excepție în cazul în care frecvență este negativă sau zero,
  int elementeCuFrecventaData(int frecventa) const;

  // returneaza numar de aparitii ale unui element in colectie
  int nrAparitii(TElem elem) const;

  // intoarce numarul de elemente din colectie;
  int dim() const;

  // verifica daca colectia e vida;
  bool vida() const;

  // returneaza un iterator pe colectie
  IteratorColectie iterator() const;

  // destructorul colectiei
  ~Colectie();
};
