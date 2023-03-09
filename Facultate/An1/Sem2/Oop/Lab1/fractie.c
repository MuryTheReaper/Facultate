#include <stdio.h>

/*
Determina primele n cifre din scrierea fractiei subunitare
k/m = 0.c1c2c3..., pentru k si m numere naturale date.

param: k,m,nr numere naturale, k<m
return: nr de zecimale dupa virgula
*/
unsigned long long zecimale(unsigned long long k,int m, int nr);

void main()
{
    int m,nr;
    unsigned long long k;
    scanf("%llu %d %d",&k,&m,&nr);
    printf("%llu/%d=0.%llu\n",k,m,zecimale(k,m,nr));
}
unsigned long long zecimale(unsigned long long k,int m, int nr)
{
    for(int i=1;i<=nr;i++)
        k=k*10;
    return k/m;
}