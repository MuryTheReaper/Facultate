#ifndef TESTE_H_
#define TESTE_H_
/*
    Functie de test cu assert pentru functia compara_oferte(uitls.h)
*/
void test_compara_oferte();

/*
    Functie de test cu assert pentru functia swap(uitls.h)
*/
void test_swap();

/*
    Functie de test cu assert pentru functia validare_tip(validare.h)
*/
void test_validare_tip();

/*
    Functie de test cu assert pentru functia validare_pret(validare.h)
*/
void test_validare_pret();

/*
    Functie de test cu assert pentru functia validare_data(validare.h)
*/
void test_validare_data();

/*
    Functie de test cu assert pentru toate functiile ce tin de tipul de data catalog(catalog.h)
*/
void test_catalog();

/*
    Functie de test cu assert compararea destinatiei unei oferte
*/
void test_sort_oferta_destinatie();

/*
    Functie care apeleaza toate celelatle functii de test
*/
void all_test();
#endif