#pragma once
#include<vector>

class Nod;
typedef Nod *PNod;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;


class Nod
{
private:

    //informatia nodului
    TElem e;
    //adresa urmatorului nod
    PNod urm;
    //adresa nodului precedent
    PNod pre;

public:

    friend class DO;

    Nod(TElem e, PNod pre, PNod urm);

    TElem element();

    PNod urmator();

    PNod precedent();
	
};