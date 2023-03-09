#pragma once
#include "Colectie.h"
#include <vector>

class Nod;
typedef Nod *PNod;

typedef int TElem;
typedef int TFrecventa;
typedef std::pair<TElem, TFrecventa> TPair;

class Nod {
private:
  // informatia nodului
  std::pair<TElem, TFrecventa> e;
  // adresa urmatorului nod
  PNod urm;

public:
  friend class Colectie;

  Nod(TPair e, PNod urm);

  TPair element();

  PNod urmator();
};