#include <stdio.h>

int suma();

void main()
{
    printf("Hello World!\n");
    printf("Suma este: %d\n",suma());
}

int suma()
{   
    /*
    Intrare: se citesc de la tastataura n si apoi n numere intregi
    Iesire: suma celor n numere intregi
    */
    int n,suma=0,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        suma+=x;
    }
    return suma;
}