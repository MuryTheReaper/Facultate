#ifndef ENTITIES_H_
#define ENTITIES_H_

typedef struct produse {

    //struct pentru definirea entitatii de medicament 
    //pentru farmacie   
    char name[100];
    float concentr;
}produs;

typedef struct stocuri{
    produs med;
    int uniqueCode;
    int quantity;
}stoc;

int compareStocs(stoc* prod1, stoc* prod2);

stoc NULL_STOC();

#endif


