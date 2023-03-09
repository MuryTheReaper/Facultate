#ifndef UTILS_H_
#define UTILS_H_

/*
    compara daca doua oferte sunt identice
    intrare: x,y-oferta
    iesire: 0 daca sunt identice, 1 altfel
*/
int compara_oferte(oferta x,oferta y);

/*
    interschimba oferta x cu y
    intrare: x,y-pointer oferta
    iesire: - 
*/
void swap(oferta *x, oferta *y);
/*
    compara pretul a doua oferte
    intrare: x,y-oferta
    iesire: 0 daca sunt identice, 1 daca x>y, -1 altfel
*/
int sort_oferta_pret(oferta x, oferta y);
/*
    compara destinatia a doua oferte
    intrare: x,y-oferta
    iesire: 0 daca sunt identice, 1 daca x>y, -1 altfel
*/
int sort_oferta_destinatie(oferta x, oferta y);

#endif