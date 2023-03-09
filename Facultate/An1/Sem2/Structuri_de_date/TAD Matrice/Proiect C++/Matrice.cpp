#include "Matrice.h"
#include <iostream>
#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) {
	//Aruncam exceptii pentru date invalide
	if(m<=0 || n<=0){
		throw exception();
	}

	//Initializam capacitatea cu 1 si 0 elemente nenule
	this->cp=1;
	this->n=0;
	//Initializam nr de linii si coloane
	this->maxC=n;
	this->maxL=m;

	//Alocam spatiu pentru vectori
	this->L=new TElem[cp];
	this->V=new TElem[cp];
	this->C=new int[maxC+1];


	//T(n)=theta(1)
}

int Matrice::nrLinii() const{
	
	return this->maxL;
	//T(n)=theta(1)
}


int Matrice::nrColoane() const{

	return this->maxC;
	//T(n)=theta(1)
}


TElem Matrice::element(int i, int j) const{
	
	//Aruncam exceptie daca i si j nu apratin matricii
	if((i>=this->maxL || i<0) || (j>=this->maxC || j<0)){
		throw exception();
	}

	//localizam zona unde se poate alfa elementul in vecotrul LINIE
	int start_p=this->C[j-1];
	int end_p=this->C[j];

	//parcurgem intervalul in vectorul LINIE
	for(int k=start_p;k<end_p;k++){
		if(this->L[k]==i)
			return this->V[k];
	}

	//daca nu se gaseste inceamna ca elementul e null
	return NULL_TELEMENT;

	//T(n)=O(maxL)
}



TElem Matrice::modifica(int i, int j, TElem e) {
	
	//Aruncam exceptie daca i si j nu apratin matricii
	if((i>=this->maxL || i<0) || (j>=this->maxC || j<0)){
		throw exception();
	}

	//retinem ce element este pe pozitia i,j
	TElem ok=element(i,j);

	//Pe pozitia i si j este null si elementul nostru e diferit de null
	if(e!=NULL_TELEMENT && ok==NULL_TELEMENT){
		if(this->n==this->cp){
			//Redimensionare
			TElem *Vnou=new TElem[this->cp*2];
			TElem *Lnou=new TElem[this->cp*2];

			for(int k=0;k<this->n;k++){
				Vnou[k]=this->V[k];
				Lnou[k]=this->L[k];
			}

			this->cp=this->cp*2;
			
			delete[] this->L;
			delete[] this->V;

			this->L=Lnou;
			this->V=Vnou;
		}

		//mutam elementele din vectorii LINIE SI VALOARE la dreapta
		int start_p=this->C[j-1];
		for(int k=this->n-1;k>=start_p;k--){
			this->L[k+1]=this->L[k];
			this->V[k+1]=this->V[k];
		}
		//inseram noul element in vectorii LINIE SI VALOARE
		this->L[start_p]=i;
		this->V[start_p]=e;
		this->n++;

		//'inseram' noul element in vectorul COLOANA
		for(int k=j;k<this->maxC;k++){
			this->C[k]++;
		}

		//T(n)=O(max(n,maxC))(n = nr de elemente nenule)

	}
	//Pe pozitia i si j este nu este null si elementul nostru e diferit de null
	else if(e!=NULL_TELEMENT && ok!=NULL_TELEMENT){

		//localizam zona unde se poate alfa elementul in vecotrul LINIE
		int start_p=this->C[j-1];
		int end_p=this->C[j];

		//parcurgem intervalul in vectorul LINIE
		for(int k=start_p;k<end_p;k++){
			if(this->L[k]==i){
				this->V[k]=e;
				break;
			}
		}
		//T(n)=O(maxL)
	}
	//Pe pozitia i si j este nu este null si elementul nostru este null
	else if(e==NULL_TELEMENT && ok!=NULL_TELEMENT){
		int start_p=this->C[j-1];

		//mutam elementele din vectorii LINIE si COLOANA la stanga
		for(int k=start_p;k<this->n-1;k++){
			this->L[k]=this->L[k+1];
			this->V[k]=this->V[k+1];
		}
		//'stergem' elementul respectiv
		this->n--;

		//'stergem' elementul in vectorul COLOANA
		for(int k=j;k<this->maxC;k++){
			this->C[k]--;
		}

		//T(n)=O(max(n,maxC))(n = nr de elemente nenule)
	}

	//T(n)=O(max(n,maxL,maxC))

	return ok;
}


