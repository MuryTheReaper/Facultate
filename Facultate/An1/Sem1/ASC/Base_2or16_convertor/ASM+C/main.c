#include <stdio.h>

void base_2(int); 	//functia de transformare in baza 2
void base_16(int);	//functia de transformare in baza 16

int main()
{   
	int nr[]={64,123,1235,34,12,32},i;	//declararea sirului de numere

	for(i=0;i<=6;i++){		//parcurgerea sirului si afisarea transformarilor
    	printf("Numarul de convertit din baza 10: %d\n",nr[i]);
		base_2(nr[i]);
		base_16(nr[i]);
	}	
	return 0;
	
}