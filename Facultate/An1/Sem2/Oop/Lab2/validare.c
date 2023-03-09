#include "validare.h"
#include <string.h>
#include <stdlib.h>

int validare_tip(char* tip){
    if(strcmp(tip,"munte")==0 || strcmp(tip,"mare")==0 || strcmp(tip,"city_break")==0){
        return 0;
    }
    return 1;
}

int validare_data(char* d){
    char* data;
    data=(char*)malloc((sizeof(char)*strlen(d))+1);
    strcpy(data,d);
    if(strchr(data,'/')==0){
        free(data);
        return 1;
    }
    char* p=strtok(data,"/");
    if(strlen(p)!=2){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[0])==0){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[1])==0){
        free(data);
        return 1;
    }

    p=strtok(NULL,"/");
    if(strlen(p)!=2){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[0])==0){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[1])==0){
        free(data);
        return 1;
    }
    
    p=strtok(NULL,"/");
    if(strlen(p)!=4){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[0])==0){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[1])==0){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[2])==0){
        free(data);
        return 1;
    }
    if(strchr("0123456789",p[3])==0){
        free(data);
        return 1;
    }
    free(data);
    return 0;
}   

int validare_pret(char* pret){
    float x=atof(pret);
    if(x<=0){
        return 1;
    }
    return 0;
}