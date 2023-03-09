#ifndef UI_H_
#define UI_H_
#include "catalog.h"
#include "oferta.h"
/*
    citeste un cmd comanda utilizatorului
    intrare: cmd-pointer char(string)
    iesire: -
*/
void read_cmd(char* cmd);

/*
    printeaza meniul aplicatiei
    intrare: -
    iesire: -    
*/
void print_meniu();

/*
    functie care initializeaza adaugarea un catalogul x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_add(catalog* x);

/*
    functie care printeaza intregul catalog x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_print(catalog *x);

/*
    functie care initializeaza modificare unui element din catalogul x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_modifica(catalog *x);

/*
    functie care initializeaza stergerea unui element din catalogul x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_sterge(catalog* x);

/*
    functie care initializeaza sortarea catalogul x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_sortare(catalog* x);

/*
    functie care initializeaza filtrarea catalogul x
    intrare: x-pointer catalog
    iesire: -    
*/
void ui_filtrare(catalog* x);

/*
    functie care printeaza intregul catalog x
    intrare: x-pointer catalog
    iesire: -    
*/
void print_catalog(catalog* x);

/*
    functie care printeaza o oferta
    intrare: x-pointer catalog
    iesire: -    
*/
void print_oferta(oferta* x);

/*
    functie de ui(care porneste programul)
    intrare: x-pointer catalog
    iesire: -    
*/
int ui();

#endif