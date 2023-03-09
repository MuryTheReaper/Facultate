#include "Colectie.h"
#include "IteratorColectie.h"
#include "Nod.h"
#include <exception>
#include <iostream>
#include <math.h>
using namespace std;

int Colectie::d(TElem e) const {
  // functia de dispersie
  return abs(e) % m;

  // T(n)=theta(1)
}

Colectie::Colectie() {
  // initializam tabela de dispersie
  size = 0;
  m = MAX;

  l = new PNod[MAX];

  for (int i = 0; i < m; i++) {
    l[i] = nullptr;
  }
  // T(n)=theta(1)
}

void Colectie::redim() {
  m = m * 2;

  PNod *lnou = new PNod[m];

  for (int i = 0; i < m; i++) {
    lnou[i] = nullptr;
  }

  for (int i = 0; i < m / 2; i++) {
    // se elibereaza memoria pentru lista i
    // si se introduc elementele in lista noua
    while (l[i] != nullptr) {
      PNod p = l[i];

      //
      int ind = d(p->e.first);
      TPair x;
      x.first = p->e.first;
      x.second = p->e.second;
      PNod q = new Nod(x, nullptr);
      q->urm = lnou[ind];
      lnou[ind] = q;
      //

      l[i] = l[i]->urm;
      delete p;
    }
  }

  l = lnou;

  // T(n)=O(1) amortizat
}

void Colectie::adauga(TElem elem) {

  if (size / m == 1) {
    redim();
  }

  // gasim pozitia i in care se introduce elementul in tabela
  int i = d(elem);

  PNod p;
  p = l[i];
  // parcurgem lista asociata
  while (p != nullptr) {
    // daca este gasit elementul, crestem frecventa lui
    if (p->e.first == elem) {
      p->e.second++;
      size++;
      return;
    }
    p = p->urm;
  }

  // daca nu este gasit il adaugam in fata listei
  TPair x;
  x.first = elem;
  x.second = 1;
  size++;
  p = new Nod(x, nullptr);
  p->urm = l[i];
  l[i] = p;

  // CD: T(n)=O(n)
  // CM: T(n)=theta(1 + n/m)
}

bool Colectie::sterge(TElem elem) {

  // verificam daca colectia este vida
  if (this->vida()) {
    return false;
  }

  // gasim pozitia i in care se poate afla elementul in tabela
  int i = d(elem);

  PNod p = l[i];

  // daca p este NIL atunci nu poate sa fie in lista
  if (p == nullptr) {
    return false;
  }

  // verificam daca trebuie sa stergem primul element
  if (p->e.first == elem) {
    // daca are doar o paratie il stergem
    if (p->e.second == 1) {
      l[i] = l[i]->urm;
      delete p;
    }
    // daca are mai multe apartitii scadem una
    else {
      p->e.second--;
    }
    size--;
    return true;
  }

  // parcurgem lista
  while (p->urm != nullptr && p->urm->e.first != elem) {
    p = p->urm;
  }

  // daca am ajuns la sfasitul listei nu s-a gasit elementul
  if (p->urm == nullptr) {
    return false;
  }

  // verificam daca trebuie sa stergem ultimul element
  if (p->urm->urm == nullptr) {
    // daca are doar o paratie il stergem
    if (p->urm->e.second == 1) {
      PNod q = p->urm;
      p->urm = nullptr;
      delete q;
    }
    // daca are mai multe apartitii scadem una
    else {
      p->urm->e.second--;
    }
    size--;
    return true;
  }

  // verificam daca trebuie sa stergem un element de la "mijloc"
  // daca are doar o paratie il stergem
  if (p->urm->e.second == 1) {
    PNod q = p->urm;
    p->urm = p->urm->urm;
    delete q;
  }
  // daca are mai multe apartitii scadem una
  else {
    p->urm->e.second--;
  }
  size--;
  return true;

  // CD: T(n)=O(n)
  // CM: T(n)=theta(1 + n/m)
}

bool Colectie::cauta(TElem elem) const {

  // gasim pozitia i in care se poate afla elementul in tabela
  int i = d(elem);

  PNod p;
  p = l[i];
  // parcurgem lista asocaita
  while (p != nullptr) {
    // daca am gasit elementul returnam true
    if (p->e.first == elem) {
      return true;
    }
    p = p->urm;
  }

  // daca nu am gasit returnam false
  return false;

  // CD: T(n)=O(n)
  // CM: T(n)=theta(1 + n/m)
}

int Colectie::elementeCuFrecventaData(int frecventa) const {

  int nr = 0;

  // aruncam exceptie daca frec <= 0

  if (frecventa <= 0)
    throw exception();

  // parcurgem fiecare camp
  for (int i = 0; i < m; i++) {
    PNod p = l[i];
    // parcurgem fiecare lista
    while (p != nullptr) {
      // daca apare de atata cat frecventa crestem nr
      if (p->e.second == frecventa) {
        nr++;
      }
      p = p->urm;
    }
  }

  return nr;

  // T(n)=theta(n)

  // pseudocod

  /* elementeCuFrecventaData(c - i, frecventa - i, nr - o)
        pre: c - colectie, frecventa - nr natural
        post: nr - numărul de elemente care apar de frecvență ori în colecție

        nr <- 0
        pentru i=0,c.m executa
          p <- l[i]
          cat timp p != NIL executa
            daca [p].e.second = frecventa atunci
              nr <- nr+1
            sf. daca
            p <- [p].urm
          sf. cat timp
        sf. pentru

        daca nr <= 0 atunci
          @arunca exceptie
        sf. daca

        sf.subalg
  */
}

int Colectie::nrAparitii(TElem elem) const {
  // gasim pozitia i in care se poate afla elementul in tabela
  int i = d(elem);

  PNod p;
  p = l[i];
  // parcurgem lista asocaita
  while (p != nullptr) {
    // daca am gasit elementul returnam aparitiile lui
    if (p->e.first == elem) {
      return p->e.second;
    }
    p = p->urm;
  }

  // daca nu am gasit inseamna ca are 0 aparaitii
  return 0;

  // CD: T(n)=O(n)
  // CM: T(n)=theta(1 + n/m)
}

int Colectie::dim() const {

  // returnam dimensiunea colectiei
  return size;

  // T(n)=theta(1)
}

bool Colectie::vida() const {

  // verificam daca colectia este vida
  return (size == 0);

  // T(n)=theta(1)
}

IteratorColectie Colectie::iterator() const { return IteratorColectie(*this); }

Colectie::~Colectie() {

  for (int i = 0; i < m; i++) {
    // se elibereaza memoria pentru lista i
    while (l[i] != nullptr) {
      PNod p = l[i];
      l[i] = l[i]->urm;
      delete p;
    }
  }
  // T(n)=theta(n)
}
