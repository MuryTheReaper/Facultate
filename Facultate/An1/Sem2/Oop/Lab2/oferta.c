#include "oferta.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

oferta* creeaza_oferta(char* tip, char* destinatie, char* data, float pret){

    oferta* x=(oferta*)malloc(sizeof(oferta));

    x->tip=(char*)malloc(strlen(tip)+1);
    strcpy(x->tip,tip);

    x->destinatie=(char*)malloc(strlen(destinatie)+1);
    strcpy(x->destinatie,destinatie);

    x->data=(char*)malloc(strlen(data)+1);
    strcpy(x->data,data);

    x->pret=pret;

    return x;
}

void distruge_oferta(oferta* x){

    free(x->tip);
    free(x->destinatie);
    free(x->data);

}

