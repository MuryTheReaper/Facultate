#include "disciplina.h"

bool operator==(const disciplina& x,const disciplina& y){
    
    return x.get_denumire()==y.get_denumire();

    /*if(x.get_ore()!=y.get_ore()){
        return false;
    }

    if(x.get_profesor()!=y.get_profesor()){
        return false;
    }

    if(x.get_tip()!=y.get_tip()){
        return false;
    }*/
    
}
