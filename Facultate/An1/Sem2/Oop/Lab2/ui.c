#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalog.h"
#include "validare.h"
#include "teste.h"
#include "ui.h"
#include "utils.h"

void read_cmd(char* cmd){

    printf("Comanda: ");
    scanf("%s",cmd);

}

void print_meniu(){
    printf("\nComenziu disponibile:\n-1:iesire\n 0:afisare\n 1:adaugare\n 2:modificare\n 3:stergere\n 4:sortare\n 5:filtrare\n\n");
}

void ui_add(catalog* x){
    printf("Adauga oferta\n");

    printf("Tipul: ");
    char* tip=(char*)malloc(128*sizeof(char));
    scanf("%s",tip);

    printf("Destinatia: ");
    char* destinatie=(char*)malloc(128*sizeof(char));
    scanf("%s",destinatie);

    printf("Data: ");
    char* data=(char*)malloc(128*sizeof(char));
    scanf("%s",data);

    printf("Pretul: ");
    char* pret=(char*)malloc(128*sizeof(char));
    scanf("%s",pret);

    int ok_t=validare_tip(tip);
    int ok_d=validare_data(data);
    int ok_p=validare_pret(pret);

    if(ok_t==1){
        printf("Tip invalid\n");
    }
    if(ok_d==1){
        printf("Data invalid\n");
    }
    if(ok_p==1){
        printf("Pret invalid\n");
    }
    if(ok_t==0 && ok_d==0 && ok_p==0){
        float p=atof(pret);
        oferta* el=creeaza_oferta(tip,destinatie,data,p);

        add_oferta_to_catalog(x,el);

        free(el);
    }
    free(tip);
    free(destinatie);
    free(data);
    free(pret);

}

void ui_print(catalog *x){
    print_catalog(x);
}

void ui_modifica(catalog *x){
    printf("Modifica oferta\n");

    printf("Tipul: ");
    char* tip=(char*)malloc(128*sizeof(char));
    scanf("%s",tip);

    printf("Destinatia: ");
    char* destinatie=(char*)malloc(128*sizeof(char));
    scanf("%s",destinatie);

    printf("Data: ");
    char* data=(char*)malloc(128*sizeof(char));
    scanf("%s",data);

    printf("Pretul: ");
    char* pret=(char*)malloc(128*sizeof(char));
    scanf("%s",pret);

    printf("Schimba tipul\n");

    printf("Noul tip: ");
    char* new_tip=(char*)malloc(128*sizeof(char));
    scanf("%s",new_tip);

    int ok_t=validare_tip(tip);
    int ok_d=validare_data(data);
    int ok_p=validare_pret(pret);
    int ok_t_new=validare_tip(tip);

    if(ok_t==1){
        printf("Tip invalid\n");
    }
    if(ok_t_new==1){
        printf("Noul tip invalid\n");
    }
    if(ok_d==1){
        printf("Data invalid\n");
    }
    if(ok_p==1){
        printf("Pret invalid\n");
    }
    if(ok_t==0 && ok_d==0 && ok_p==0 && ok_t_new==0){
        float p=atof(pret);
        oferta* el=creeaza_oferta(tip,destinatie,data,p);
        oferta* new_el=creeaza_oferta(new_tip,destinatie,data,p);

        int ok=modifica_oferta_to_catalog(x,el,new_el);
        if(ok==1){
            printf("Nu exista elementul");
        }
        else{
            printf("Modificat cu succes");
        }
        printf("\n");
        distruge_oferta(el);
        free(new_el);
        free(el);
    }
    
    free(new_tip);
    free(tip);
    free(destinatie);
    free(data);
    free(pret);
}

void ui_sterge(catalog* x){
    printf("Sterge oferta\n");

    printf("Tipul: ");
    char* tip=(char*)malloc(128*sizeof(char));
    scanf("%s",tip);

    printf("Destinatia: ");
    char* destinatie=(char*)malloc(128*sizeof(char));
    scanf("%s",destinatie);

    printf("Data: ");
    char* data=(char*)malloc(128*sizeof(char));
    scanf("%s",data);

    printf("Pretul: ");
    char* pret=(char*)malloc(128*sizeof(char));
    scanf("%s",pret);

    int ok_t=validare_tip(tip);
    int ok_d=validare_data(data);
    int ok_p=validare_pret(pret);

    if(ok_t==1){
        printf("Tip invalid\n");
    }
    if(ok_d==1){
        printf("Data invalid\n");
    }
    if(ok_p==1){
        printf("Pret invalid\n");
    }
    if(ok_t==0 && ok_d==0 && ok_p==0){
        float p=atof(pret);
        oferta* el=creeaza_oferta(tip,destinatie,data,p);

        int ok=sterge_oferta_to_catalog(x,el);
        if(ok==1){
            printf("Nu exista elementul");
        }
        else{
            printf("Sters cu succes");
        }
        distruge_oferta(el);
        free(el);
    }
    
    free(tip);
    free(destinatie);
    free(data);
    free(pret);
}

void ui_filtrare(catalog* x){
    printf("Filtrare oferte\n");

    printf("Filtrare dupa: ");
    char* criteriu=(char*)malloc(128*sizeof(char));
    scanf("%s",criteriu);

    printf("Criteriu: ");
    char* crt=(char*)malloc(128*sizeof(char));
    scanf("%s",crt);

    catalog* f_catalog=creaza_catalog();
    int inv=1;

    if(strcmp(criteriu,"tip")==0){
        
        int ok=validare_tip(crt);
        if(ok==0){
            filtreaza_catalog(x,f_catalog,crt,1);
        }
        else{
            printf("Criteriu invalid\n");
            inv=0;
        }
    }
    if(strcmp(criteriu,"destinatie")==0){
        
        int ok=0;
        if(ok==0){
            filtreaza_catalog(x,f_catalog,crt,2);
        }
        else{
            printf("Criteriu invalid\n");
            inv=0;
        }
    }
    if(strcmp(criteriu,"pret")==0){
        
        int ok=validare_pret(crt);
        if(ok==0){
            filtreaza_catalog(x,f_catalog,crt,3);
        }
        else{
            printf("Criteriu invalid\n");
            inv=0;
        }
    }
    if(inv==1){
        print_catalog(f_catalog);
    }

    free(f_catalog->elemente);
    free(f_catalog);
    free(crt);
    free(criteriu);

}

void ui_sortare(catalog* x){
    printf("Sortare oferte\n");

    printf("Sortare dupa: ");
    char* criteriu=(char*)malloc(128*sizeof(char));
    scanf("%s",criteriu);

    printf("Crescator/descrescator(1/2): ");
    char* cres=(char*)malloc(128*sizeof(char));
    scanf("%s",cres);

    if(strcmp(criteriu,"pret")==0){
        sort_catalog(x,sort_oferta_pret,cres);
    }else if(strcmp(criteriu,"destinatie")==0){
        sort_catalog(x,sort_oferta_destinatie,cres);
    }else{
        printf("Invalid");
    }

    free(criteriu);
    free(cres);
}

void print_oferta(oferta* x){
    printf("Tip: %s|Destinatie: %s|Data: %s|Pret: %.2f",x->tip,x->destinatie,x->data,x->pret);

}

void print_catalog(catalog* x){
    
    if(x->lungime==0){
        printf("Lista vida\n");
    }
    else{
        int i;
        for(i=0;i<x->lungime;i++){
            print_oferta(&x->elemente[i]);
            printf("\n");
        }
    }
}

int ui(){

    catalog* turism=creaza_catalog();

    while(9){
        print_meniu();
        char* cmd=(char*)malloc(128*sizeof(char));
        read_cmd(cmd);
        if(strcmp(cmd,"1")==0){
            ui_add(turism);
        }
        else if(strcmp(cmd,"0")==0){
            ui_print(turism);
        }
        else if(strcmp(cmd,"2")==0){
            ui_modifica(turism);
        }
        else if(strcmp(cmd,"3")==0){
            ui_sterge(turism);
        }
        else if(strcmp(cmd,"4")==0){
            ui_sortare(turism);
        }
        else if(strcmp(cmd,"5")==0){
            ui_filtrare(turism);
        }
        else if(strcmp(cmd,"-1")==0)
        {
            free(cmd);
            break;
        }
        else
        {
            printf("Comanda invalida.\n");
        }
        free(cmd);
    }
    distruge_catalog(turism);
    return 0;
}