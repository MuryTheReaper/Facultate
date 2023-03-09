#include "oferta.h"
#include <string.h>
#include <stdlib.h>

int compara_oferte(oferta x,oferta y){
    if(strcmp(x.data,y.data)!=0)
        return 1;
    if(strcmp(x.tip,y.tip)!=0)
        return 1;
    if(strcmp(x.destinatie,y.destinatie)!=0)
        return 1;
    if(x.pret!=y.pret)
        return 1;
    return 0;
}

void swap(oferta *x, oferta *y){
    oferta temp=*x;
    *x=*y;
    *y=temp;
}

int sort_oferta_pret(oferta x, oferta y){
    if(x.pret>y.pret){
        return 1;
    }
    if(abs(x.pret-y.pret)<0.001)
        return 0;
    return -1;
}

int sort_oferta_destinatie(oferta x, oferta y){
    if(strcmp(x.destinatie,y.destinatie)>0){
        return 1;
    }
    if(strcmp(x.destinatie,y.destinatie)==0){
        return 0;
    }
    return -1;
}