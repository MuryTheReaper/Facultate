#ifndef OFERTA_H_
#define OFERTA_H_

/*
    Structura de date pentru a retine oferte
*/
typedef struct {
    char* tip;
    char* destinatie;
    char* data;
    float pret;

}oferta;

/*
    Creaza o oferta si initializeaza comform datelor de intrare
    
    tip: string din multimea {munte, mare, city_break}
    destinatie: string
    data: string de tipul zz/mm/yyyy
    pret: float
    return pointer la oferta creata
*/
oferta* creeaza_oferta(char* tip, char* destinatie, char* data, float pret);

/*
    elibereaza memoria unei oferte(doar campurile)
    intrare: x-pointer oferta
    iesire: - 
*/
void distruge_oferta(oferta* x);

#endif