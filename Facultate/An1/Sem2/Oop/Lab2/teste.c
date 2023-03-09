#include <assert.h>
#include "oferta.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include "validare.h"
#include "catalog.h"
#include "ui.h"

void test_compara_oferte(){
    
    char* tip=(char*)malloc(128*sizeof(char));
    char* destinatie=(char*)malloc(128*sizeof(char));
    char* data=(char*)malloc(128*sizeof(char));

    strcpy(tip,"munte");
    strcpy(destinatie,"1");
    strcpy(data,"11/11/2021");

    oferta* x=creeaza_oferta(tip,destinatie,data,11.2);
    oferta* y=creeaza_oferta(tip,destinatie,data,11.2);

    assert(compara_oferte(*x,*y)==0);

    distruge_oferta(x);
    free(x);

    strcpy(tip,"f");
    x=creeaza_oferta(tip,destinatie,data,11.2);

    assert(compara_oferte(*x,*y)==1);

    distruge_oferta(x);
    free(x);

    strcpy(tip,"munte");
    strcpy(destinatie,"2");

    x=creeaza_oferta(tip,destinatie,data,11.2);

    assert(compara_oferte(*x,*y)==1);

    distruge_oferta(x);
    free(x);

    strcpy(tip,"munte");
    strcpy(destinatie,"1");
    strcpy(data,"0");

    x=creeaza_oferta(tip,destinatie,data,11.2);

    assert(compara_oferte(*x,*y)==1);

    distruge_oferta(x);
    free(x);

    strcpy(tip,"munte");
    strcpy(destinatie,"1");
    strcpy(data,"11/11/2021");

    x=creeaza_oferta(tip,destinatie,data,11.3);

    assert(compara_oferte(*x,*y)==1);

    free(tip);
    free(destinatie);
    free(data);
    distruge_oferta(x);
    free(x);
    distruge_oferta(y);
    free(y);
}

void test_swap(){
    char* tip=(char*)malloc(128*sizeof(char));
    char* destinatie=(char*)malloc(128*sizeof(char));
    char* data=(char*)malloc(128*sizeof(char));
    strcpy(tip,"munte");
    strcpy(destinatie,"1");
    strcpy(data,"11/11/2021");
    oferta* x=creeaza_oferta(tip,destinatie,data,11.2);
    oferta* y=creeaza_oferta(tip,destinatie,data,22.1);
    oferta* z=creeaza_oferta(tip,destinatie,data,22.1);
    swap(x,y);
    assert(compara_oferte(*x,*z)==0);
    free(tip);
    free(destinatie);
    free(data);
    distruge_oferta(x);
    free(x);
    distruge_oferta(y);
    free(y);
    distruge_oferta(z);
    free(z);
}
void test_validare_tip(){
    char* tip=(char*)malloc(128*sizeof(char));
    strcpy(tip,"munte");
    assert(validare_tip(tip)==0);
    strcpy(tip,"0");
    assert(validare_tip(tip)==1);
    free(tip);

}

void test_validare_pret(){
    char* pret=(char*)malloc(128*sizeof(char));
    strcpy(pret,"a1");
    assert(validare_pret(pret)==1);
    strcpy(pret,"1.2");
    assert(validare_pret(pret)==0);
    free(pret);
}

void test_validare_data(){
    char* data=(char*)malloc(128*sizeof(char));
    strcpy(data,"a1");
    assert(validare_data(data)==1);

    strcpy(data,"1/");
    assert(validare_data(data)==1);

    strcpy(data,"a1/");
    assert(validare_data(data)==1);

    strcpy(data,"1a/");
    assert(validare_data(data)==1);

    strcpy(data,"11/a");
    assert(validare_data(data)==1);

    strcpy(data,"11/a1");
    assert(validare_data(data)==1);

    strcpy(data,"11/1a");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/a");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/aaaa");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/1aaa");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/11aa");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/111a");
    assert(validare_data(data)==1);

    strcpy(data,"11/11/1111");
    assert(validare_data(data)==0);

    free(data);
}

void test_catalog(){
    catalog* ctlg=creaza_catalog();

    char* tip=(char*)malloc(128*sizeof(char));
    char* destinatie=(char*)malloc(128*sizeof(char));
    char* data=(char*)malloc(128*sizeof(char));

    strcpy(tip,"munte");
    strcpy(destinatie,"1");
    strcpy(data,"11/11/2021");

    oferta* x=creeaza_oferta(tip,destinatie,data,11.2);

    add_oferta_to_catalog(ctlg,x);
    free(x);

    oferta* y=creeaza_oferta(tip,destinatie,data,22.1);
    x=creeaza_oferta(tip,destinatie,data,11.2);
    assert(modifica_oferta_to_catalog(ctlg,x,y)==0);
    distruge_oferta(x);
    free(x);
    free(y);

    x=creeaza_oferta(tip,destinatie,data,11.2);
    y=creeaza_oferta(tip,destinatie,data,22.1);
    assert(modifica_oferta_to_catalog(ctlg,x,y)==1);
    distruge_oferta(x);
    distruge_oferta(y);
    free(x);
    free(y);

    y=creeaza_oferta(tip,destinatie,data,22.1);
    assert(sterge_oferta_to_catalog(ctlg,y)==0);
    distruge_oferta(y);
    free(y);

    y=creeaza_oferta(tip,destinatie,data,22.1);
    assert(sterge_oferta_to_catalog(ctlg,y)==1);
    distruge_oferta(y);
    free(y);

    x=creeaza_oferta(tip,destinatie,data,11.2);
    add_oferta_to_catalog(ctlg,x);
    free(x);

    y=creeaza_oferta(tip,destinatie,data,22.1);
    add_oferta_to_catalog(ctlg,y);
    free(y);

    x=creeaza_oferta(tip,destinatie,data,11.2);
    add_oferta_to_catalog(ctlg,x);
    free(x);

    x=creeaza_oferta(tip,destinatie,data,11.2);
    assert(sterge_oferta_to_catalog(ctlg,x)==0);
    distruge_oferta(x);
    free(x);

    strcpy(destinatie,"2");
    x=creeaza_oferta(tip,destinatie,data,11.2);
    add_oferta_to_catalog(ctlg,x);
    free(x);



    char* cres=(char*)malloc(128*sizeof(char));
    strcpy(cres,"1");
    catalog* c_ctlg=copy_catalog(ctlg);
    sort_catalog(ctlg,sort_oferta_pret,cres);
    assert(c_ctlg->elemente[0].pret!=ctlg->elemente[0].pret);
    distruge_catalog(c_ctlg);
    strcpy(cres,"2");
    sort_catalog(ctlg,sort_oferta_pret,cres);
    strcpy(cres,"1");
    sort_catalog(ctlg,sort_oferta_destinatie,cres);
    strcpy(cres,"2");
    sort_catalog(ctlg,sort_oferta_destinatie,cres);

    catalog* new_ctlg=creaza_catalog();

    strcpy(cres,"munte");
    filtreaza_catalog(ctlg,new_ctlg,cres,1);
    free(new_ctlg->elemente);
    free(new_ctlg);

    new_ctlg=creaza_catalog();
    strcpy(cres,"1");
    filtreaza_catalog(ctlg,new_ctlg,cres,2);
    free(new_ctlg->elemente);
    free(new_ctlg);

    new_ctlg=creaza_catalog();
    strcpy(cres,"11.2");
    filtreaza_catalog(ctlg,new_ctlg,cres,3);
    free(new_ctlg->elemente);
    free(new_ctlg);

    free(tip);
    free(destinatie);
    free(data);
    free(cres);
    distruge_catalog(ctlg);

}
void test_sort_oferta_destinatie(){
    
    oferta* x=creeaza_oferta("-","abc","-",0);
    oferta* y=creeaza_oferta("-","bca","-",0);

    assert(sort_oferta_destinatie(*x,*y)<0);
    assert(sort_oferta_destinatie(*x,*x)==0);
    assert(sort_oferta_destinatie(*y,*x)>0);

    distruge_oferta(x);
    free(x);
    distruge_oferta(y);
    free(y);
}

void all_test(){
    test_compara_oferte();
    test_swap();
    test_validare_tip();
    test_validare_pret();
    test_validare_data();
    test_catalog();
    test_sort_oferta_destinatie();
}