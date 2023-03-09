#include "catalog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define INIT_CAPACITY 1

catalog* creaza_catalog(){

    catalog* x=(catalog*)malloc(sizeof(catalog));
    x->elemente=(oferta*)malloc(sizeof(oferta)*INIT_CAPACITY);
    x->lungime=0;
    x->capacitate=INIT_CAPACITY;

    return x;
}

void distruge_catalog(catalog* x){
    int i;
    for(i=0;i<x->lungime;i++){
        distruge_oferta(&(x->elemente[i]));
    }
    free(x->elemente);
    free(x);

}

void resize(catalog* x){
    int new_cap=2*x->capacitate;
    oferta* new_elems=(oferta*)malloc(sizeof(oferta)*new_cap);
    
    int i;
    for(i=0;i<x->lungime;i++){
        new_elems[i]=x->elemente[i];
    }
    free(x->elemente);
    x->capacitate=new_cap;
    x->elemente=new_elems;

}

void add_oferta_to_catalog(catalog* x, oferta* el){
    if(x->lungime==x->capacitate){
        resize(x);
    }
    x->elemente[x->lungime].data=el->data;
    x->elemente[x->lungime].destinatie=el->destinatie;
    x->elemente[x->lungime].tip=el->tip;
    x->elemente[x->lungime].pret=el->pret;
    x->lungime+=1;

}

int modifica_oferta_to_catalog(catalog* x, oferta* el, oferta* new_el){
    int i;
    for(i=0;i<x->lungime;i++){
       if(compara_oferte(*el,x->elemente[i])==0){
           distruge_oferta(&x->elemente[i]);
           
           x->elemente[i].data=new_el->data;
           x->elemente[i].destinatie=new_el->destinatie;
           x->elemente[i].tip=new_el->tip;
           x->elemente[i].pret=new_el->pret;
           return 0;
       }
    }
    return 1;
}

int sterge_oferta_to_catalog(catalog* x, oferta* el){
    int i,p=-1;
    for(i=0;i<x->lungime;i++){
        if(compara_oferte(*el,x->elemente[i])==0){
            p=i;
            break;
        }
    }
    if(p==-1){
        return 1;
    }
    distruge_oferta(&x->elemente[p]);
    for(i=p;i < x->lungime-1;i++){
        x->elemente[i].data=x->elemente[i+1].data;
        x->elemente[i].destinatie=x->elemente[i+1].destinatie;
        x->elemente[i].tip=x->elemente[i+1].tip;
        x->elemente[i].pret=x->elemente[i+1].pret;
    }
    x->lungime--;

    return 0;
}

void filtreaza_catalog(catalog* x,catalog* y, char* crt,int mod){
    int i;
    for(i=0;i<x->lungime;i++){
        if(mod==1 && strcmp(x->elemente[i].tip,crt)==0){
            add_oferta_to_catalog(y,&x->elemente[i]);
        }
        if(mod==2 && strcmp(x->elemente[i].destinatie,crt)==0){
            add_oferta_to_catalog(y,&x->elemente[i]);
        }
        if(mod==3 && abs(x->elemente[i].pret-atof(crt))<0.0001){
            add_oferta_to_catalog(y,&x->elemente[i]);
        }
    }
}
/*
void sort_catalog(catalog* x, int mod, char* cres){
    int i,j,ok=atoi(cres);

    for(i=0;i<x->lungime-1;i++)
        for(j=i+1;j<x->lungime;j++)
            if(mod==1){
                if(ok==1 && x->elemente[j].pret<x->elemente[i].pret){
                    swap(&x->elemente[j],&x->elemente[i]);
                }
                else if(ok==2 && x->elemente[j].pret>x->elemente[i].pret){
                    swap(&x->elemente[j],&x->elemente[i]);
                }
            }
            else if(mod==2){
                if(ok==1 && strcmp(x->elemente[j].destinatie,x->elemente[i].destinatie)<0){
                    swap(&x->elemente[j],&x->elemente[i]);
                }
                else if(ok==2 && strcmp(x->elemente[j].destinatie,x->elemente[i].destinatie)>0){
                    swap(&x->elemente[j],&x->elemente[i]);
                }
            }
}*/
catalog* copy_catalog(catalog* x){
    catalog* y=creaza_catalog();

    for(int i=0;i<x->lungime;i++){
        oferta* of=creeaza_oferta(x->elemente[i].tip,x->elemente[i].destinatie,x->elemente[i].data,x->elemente[i].pret);
        add_oferta_to_catalog(y,of);
        free(of);
    }

    return y;
}

void sort_catalog(catalog* x, int(*cmp)(oferta,oferta), char* cres){
    int i,j,ok=atoi(cres);
    for(i=0;i<x->lungime-1;i++)
        for(j=i+1;j<x->lungime;j++){
            if(ok==1 && cmp(x->elemente[j],x->elemente[i])<0){
                swap(&x->elemente[j],&x->elemente[i]);
            }
            else if(ok==2 && cmp(x->elemente[j],x->elemente[i])>0){
                swap(&x->elemente[j],&x->elemente[i]);
            }
        }
}