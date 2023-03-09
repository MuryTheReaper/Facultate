#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>
#include <iostream>

IteratorMDO::IteratorMDO(const MDO &d) : dict(d) { prim(); }

void IteratorMDO::prim() {
  // initializam primul elementul cu minimul
  curent = dict.minim(dict.radacina);
  poz = 0;
  // T(n)=O(h)
}

void IteratorMDO::urmator() {
  if (!valid())
    throw exception();

  // daca nu mai sunt elemente in lista de valori trecem la urmatoarea cheie
  if (poz == dict.e[curent].valori.size() - 1) {
    curent = dict.succesor(curent);
    poz = 0;
  } else
    // daca mai sunt elemente trecem la urmatorul element
    poz++;

  // T(n)=O(h^2)
}

bool IteratorMDO::valid() const {
  return curent != -1;
  // T(n)=theta(1)
}

TElem IteratorMDO::element() const {
  if (!valid())
    throw exception();
  // returnam elementul din lista curenta si pozitia poz
  TElem x;
  x.first = dict.e[curent].cheie;
  x.second = dict.e[curent].valori[poz];
  return x;

  // T(n)=theta(1)
}
