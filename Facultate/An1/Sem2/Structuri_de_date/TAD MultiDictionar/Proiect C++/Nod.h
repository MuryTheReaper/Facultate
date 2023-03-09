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

public:

    friend class MD;

    Nod(TElem e, PNod urm);

    TElem element();

    PNod urmator();
	
};