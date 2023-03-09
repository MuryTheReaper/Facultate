#ifndef REPOSITORY_H_
#define REPOSITORY_H_
#include "entities.h"

typedef struct{
    int cp;//capacitate

    int n;//dimensiune

    stoc* e;

}vectorDinamic;

typedef struct{

    vectorDinamic* v;

    int curent;//pozitia curenta

}Iterator;


//VECTOR DE VECTOR

vectorDinamic* copyVectDin(vectorDinamic* v);

vectorDinamic** creeazaVectVectDin(int cp);

void makeBackup(vectorDinamic** back, vectorDinamic* v);

void redim2(vectorDinamic** v);

void distrugeVV(vectorDinamic** v);

void distrugeLastBack(vectorDinamic** v);

//VECTORUL DINAMIC

vectorDinamic* creeazaVectDin(int cp);

void redim(vectorDinamic *v);

void distruge(vectorDinamic* v);

int dim(vectorDinamic* v);

stoc* element(vectorDinamic* v, int pos);

void pushBack(vectorDinamic* v, stoc e);

void removeElem(vectorDinamic* v, int pos);

//ITERATORUL
Iterator* creaazaIterator(vectorDinamic* v);

void prim(Iterator* i);

void urmator(Iterator* i);

stoc* elementIT(Iterator* i);

int valid(Iterator* i);

void distrugeIT(Iterator* i);

#endif
