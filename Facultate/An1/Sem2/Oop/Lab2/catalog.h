#ifndef CATALOG_H_
#define CATALOG_H_
#include "oferta.h"

/*
    Structura pentru catalog
    elemente: sir alocat dinamic pentru elementele de tip oferta
    lungime: lungimea curenta a sirului
    capacitate: lungimea maxima curenta  
*/
typedef struct {
    oferta* elemente;
    int lungime;
    int capacitate;
}catalog;

/*
    creaza un catalog gol
    intrare: -
    iesire: pointer catre noul catalog vid
*/
catalog* creaza_catalog();

/*
    elibereaza memoria unui catalog(toate campurile si el insusi)
    intrare: x-pointer catalog
    iesire: - 
*/
void distruge_catalog(catalog* x);

/*
    adauga in memorie o oferta in catalog
    intrare: x-pointer catalog, el- pointer oferta 
    iesire: -
*/
void add_oferta_to_catalog(catalog* x, oferta* el);

/*
    realoca spatiul sirului de oferte din catalog in caz-ul in care se ajunge la maxim
    intrare: x-pointer catalog
    iesire:  
*/
void resize(catalog* x);

/*
    modifica in memorie oferta el din catalog x cu oferta new_el
    intrare: x-pointer catalog, el,new_el-pointer oferta
    iesire: 0 daca operatia s-a efectuat cu succes, 1 altfel
*/
int modifica_oferta_to_catalog(catalog* x, oferta* el, oferta* new_el);

/*
    sterge din memorie oferta el din catalog x
    intrare: x-pointer catalog, el-pointer oferta
    iesire: 0 daca operatia s-a efectuat cu succes, 1 altfel
*/
int sterge_oferta_to_catalog(catalog* x, oferta* el);

/*
    afiseaza ofertele din catalogul x care indeplinesc conditia data de crt si mod,prin intermediul catalogului y
    intrare: x,y-pointer catalog, crt-point char(string), mod-int
    iesire: -
*/
void filtreaza_catalog(catalog* x,catalog* y, char* crt, int mod);

/*
    sorteaza in memorie ofertele din catalogul x dupa conditia data de mod si cres
    intrare: x-pointer catalog, mod-int, cres-char(pointer)
    iesire: -
*/
void sort_catalog(catalog* x, int(*cmp)(oferta,oferta), char* cres);

catalog* copy_catalog(catalog* x);
#endif