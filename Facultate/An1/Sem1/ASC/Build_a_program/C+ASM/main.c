/*++
Se cere un program C/C++ care apeleaza functia asmConcat scrisa in limbaj de asamblare. Aceasta functie primeste
ca si parametru un sir de caractere citit in programul C/C++, citeste un sir de caractere apelând pentru aceasta
functia C/C++ citesteSir si mai acceseaza un sir de caractere care este o variabila globala a programului C/C++ (numita sirC).
Functia asmConcat construieste si intoarce ca rezultat sirul obtinut prin concatenarea primelor 10 caractere ale celor 3 siruri.
Acest sir va fi afisat pe ecran. Obs.: Sirurile citite de la tastatura nu contin spatii.
--*/


#include <stdio.h>

// functia declarata in fisierul modulConcatenare.asm
int _asmConcat(char sir[], char sirR[]);

// functia folosita pentru a citi un sir de la tastatura
void _citireSirC(char sir[]);

// sir global accesat din asmConcat
char _str3[] = "0011223344";

int main()
{
    char str1[11];
    char strRez[31] = "";
    int lenStrRez = 0;

    printf("! se presupune ca sirurile citite de la tastatura au lungimea 10!! (nu se fac verificari suplimentare)\n");
    printf("Sirul 1 citit din modulul C: ");
    _citireSirC(str1);

    lenStrRez = _asmConcat(str1, strRez);
    printf("\nSirul rezultat de lungime %d:\n%s", lenStrRez, strRez);
    return 0;
}

void _citireSirC(char sir[])
{
    scanf("%s", sir);
}
