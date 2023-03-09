#include <stdio.h>

/*
    Intrare: un numar n intreg
    Iesire: 0 daca n nu este prim, 1 daca n este prim

*/
int prim(int n);

/*
    Intrare: un n numar natural
    Iesire: Afiseaza pe ecran primele n numere prime
*/
void first_n_prime(int n);

void main()
{   
    int n;
    printf("n= ");
    scanf("%d",&n);
    first_n_prime(n);

}

int prim(int n)
{   
    int d;
    if (n<=1)
        return 0;
    if (n==2)
        return 1;
    if (n%2==0)
        return 0;
    for(d=3;d*d<=n;d+=2)
    {
        if (n%d==0)
            return 0;
    }
    return 1;

}
void first_n_prime(int n)
{   
    int i;
    i=2;
    while(n)
    {
        if (prim(i)==1)
        {
            printf("%d ",i);
            n--;
        }
        i++;
    }
    printf("\n");
}
