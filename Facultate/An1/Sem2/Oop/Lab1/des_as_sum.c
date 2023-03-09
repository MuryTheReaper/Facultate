#include <stdio.h>

/*
desc:Determina toate reprezentarile posibile a unui numar natural ca suma de numere naturale consecutive.
param: n, numar natural
return: afiseaza toate sumele de numere consecutive in care poate fi descompus n
*/
void des_as_sum(int n);


void main()
{   
    int n;
    printf("n= ");
    scanf("%d",&n);
    des_as_sum(n);
}

void des_as_sum(int n)
{   
    int i,j,k,suma;
    for(i=1;i<=n/2;i++)
    {
        suma=i;
        for(j=i+1;j<=n;j++)
        {
            suma+=j;
            if(suma>=n)
                break;
        }
        if(suma==n)
        {
            printf("%d=",n);
            for(k=i;k<j;k++)
            {
                printf("%d+",k);
            }
            printf("%d\n",k);


        }

    }
}