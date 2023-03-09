#ifndef VALIDARE_H_
#define VALIDARE_H_

/*
    verifica daca tip-ul respecta cerinta
    intrare: tip-pointer char(string)
    iesire: 0 daca este valid, 1 altfel 
*/
int validare_tip(char* tip);

/*
    verifica daca data respecta cerinta
    intrare: data-pointer char(string)
    iesire: 0 daca este valid, 1 altfel 
*/
int validare_data(char* data);

/*
    verifica daca pretul respecta cerinta
    intrare: pret-pointer char(string)
    iesire: 0 daca este valid, 1 altfel 
*/
int validare_pret(char* pret);
#endif