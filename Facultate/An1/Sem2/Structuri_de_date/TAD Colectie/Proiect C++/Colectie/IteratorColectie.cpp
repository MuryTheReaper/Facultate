#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

void IteratorColectie::deplasare() {
  // gaseste prima lista nevida incepand cu locatia poz din tabela
  while (poz < col.m && col.l[poz] == nullptr)
    poz++;

  if (poz < col.m) {
    // initializam campurile
    curent = col.l[poz];
    frec = col.l[poz]->element().second;
  }
  // T(n)=theta(1)
}

IteratorColectie::IteratorColectie(const Colectie &c) : col(c) {
  // initializam cu prima pozitie in care exista o lista
  poz = 0;
  deplasare();

  // T(n)=theta(1)
}

void IteratorColectie::prim() {
  // initializam cu prima pozitie in care exista o lista
  poz = 0;
  deplasare();

  // T(n)=theta(1)
}

void IteratorColectie::urmator() {

  // aruncam exceptie daca iteratorul este nu este valid
  if (!this->valid()) {
    throw std::exception();
  }

  // daca frecventa este mai mare de 1
  // scadem frecventa si ramanem pe acelasi element
  if (frec > 1) {
    frec--;
  }
  // altfel, trecem la elementul urmator
  else {
    curent = curent->urmator();
    // daca am terminat lista curenta trecem la alta
    if (curent == nullptr) {
      poz = poz + 1;
      deplasare();
    }
    // daca nu initializam frecventa noua
    else {
      frec = curent->element().second;
    }
  }

  // T(n)=theta(1)
}

bool IteratorColectie::valid() const {

  // verificam daca iteratorul este valid
  return (poz < col.m) && (curent != nullptr);

  // T(n)=theta(1)
}

TElem IteratorColectie::element() const {

  // aruncam exceptie daca iteratorul este nu este valid
  if (!this->valid()) {
    throw std::exception();
  }

  // returnam elementul
  return curent->element().first;

  // T(n)=theta(1)
}
