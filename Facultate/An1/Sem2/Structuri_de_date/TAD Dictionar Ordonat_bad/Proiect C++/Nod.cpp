#include "Nod.h"

Nod::Nod(TElem e, PNod urm, PNod prec){
    //Initializam un nod
	this->e = e;
	this->urm = urm;
    this->pre = prec;
    
    //T(n)=theta(1)
}

TElem Nod::element() {
    //Returnam elementul unui nod
	return e;

    //T(n)=theta(1)
}

PNod Nod::urmator() {
    //Returnam adresa urmatorului nod
	return urm;

    //T(n)=theta(1)
}

PNod Nod::precedent() {
    //Returnam adresa urmatorului nod
	return pre;

    //T(n)=theta(1)
}