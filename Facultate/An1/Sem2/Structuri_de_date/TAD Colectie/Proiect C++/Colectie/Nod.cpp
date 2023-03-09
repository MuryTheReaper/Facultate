#include "Nod.h"

Nod::Nod(TPair e, PNod urm) {
  // Initializam un nod
  this->e = e;
  this->urm = urm;

  // T(n)=theta(1)
}

TPair Nod::element() {
  // Returnam elementul unui nod
  return e;

  // T(n)=theta(1)
}

PNod Nod::urmator() {
  // Returnam adresa urmatorului nod
  return urm;

  // T(n)=theta(1)
}