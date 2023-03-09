#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) {

	//initializam campurile
	cp=10;
	size=0;
	e = new TElem[cp];
	next = new int[cp];
	back = new int[cp];
	prim = -1;
	primLiber = 0;

	//se construieste spatiul liber
	for(int i=0;i<cp;i++){
		next[i]=i+1;
	}

	rel=r;

	//T(n)=theta(cp)


}
void DO::redim(){

	//alocam spatiul nou
	TElem *eNou = new TElem[2*cp];
	int *nextNou = new int[2*cp];
	int *backNou = new int[2*cp];

	//copiem ce avem deja
	for(int i=0;i<size;i++){
		eNou[i]=e[i];
		nextNou[i]=next[i];
		backNou[i]=back[i];
	}

	//prelungim spatiul liber
	for(int i=cp;i<cp*2;i++){
		nextNou[i]=i+1;
	}

	//marim capacitatea
	cp = cp * 2;


	//stergem spatiul vechi de memorie
	delete [] e;
	e=eNou;

	delete [] next;
	next = nextNou;

	delete [] back;
	back = backNou;

	//T(n)=theta(1) - amortizat

}
//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	int p;
	//daca DO este vid atunci cream un prim element
	if(this->vid()){
		p=primLiber;
		primLiber = next[primLiber];
		TElem x;
		x.first=c;
		x.second=v;
		e[p]=x;
		next[p]=-1;
		back[p]=-1;
		prim=p;
		size++;
		return NULL_TVALOARE;
	}
	//Parcurgem DO pana gasim elementul sau 
	//elementul nu mai este in relatie sau
	//am ajuns pe ultima pozitie
	p=prim;
	while (next[p]!=-1 && rel(e[p].first,c)) {
		if(e[p].first==c){
			//daca s-a gasit elementul in DO 
			//schimbam valoarea si o returnam pe cea veche
			TValoare x;
			x=e[p].second;
			e[p].second=v;
			return x;
		}
		p=next[p];
	}

	if(next[p]==-1 && e[p].first==c){
		//daca elementul este pe ultima pozitie in DO
		//schimbam valoarea si o returnam pe cea veche
		TValoare x;
		x=e[p].second;
		e[p].second=v;
		return x;
	}	

	if(next[p]==-1 && rel(e[p].first,c)){
		if(size==cp){
			redim();
		}
		//daca am ajuns la ultimul element trebuie 
		//sa introducem noul element pe ultima pozitie
		int i=primLiber;
		primLiber = next[primLiber];
		TElem x;
		x.first=c;
		x.second=v;
		e[i]=x;
		next[p]=i;
		next[i]=-1;
		back[i]=p;
		size++;
		return NULL_TVALOARE;
	}

	if(!rel(e[p].first,c)){
		if(size==cp){
			redim();
		}
		//daca elementul nu mai este in realtie avem 2 cazuri
		TElem x;
		x.first=c;
		x.second=v;
		int i=primLiber;
		primLiber = next[primLiber];
		e[i]=x;
		if(p!=prim){
			//cazul in care elementul trebuie introdus 
			//undeva in interiorul DO in functie de relatie
			next[i]=p;
			back[i]=back[p];
			next[back[p]]=i;
			back[p]=i;
		}
		else{
			//cazul in care elementul trebuie introdus
			//pe prima pozitie
			next[i]=p;
			back[i]=-1;
			back[p]=i;
			prim=i;
		}
		size++;
		return NULL_TVALOARE;
	}

	return NULL_TVALOARE;

	//T(n)=O(n)
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	
	//parcurgem DO pana cand ajungem la sfarsit sau
	//elementul nu mai este in relatie
	int p=prim;
	while (p!=-1 && rel(e[p].first,c)) {
		if(e[p].first==c){
			//daca am gasit elementul ne oprim
			return e[p].second;
		}
		p=next[p];
	}
	//T(n)=O(n)
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	
	//verificam daca DO este vid
	if(this->vid()){
		return NULL_TVALOARE;	
	}
	
	//verificam daca elementul este pe prima pozitie
	if(e[prim].first==c){
		//stergem elementul de pe prima pozitie
		TValoare x = e[prim].second;
		int i=next[prim];
		next[prim]=primLiber;
		primLiber=prim;
		prim=i;
		if(prim!=-1){
			//pentru noul prim rupem legatura
			back[i]=-1;
		}
		size--;
		return x;
	}

	int p=prim;
	//parcurgem pana ajungem pe ultima pozitie sau
	//elementul nu mai este in relatie
	while (next[p]!=-1 && rel(e[p].first,c)) {
		if(e[p].first==c){
			//stergem elementul din interiorul DO-ului
			TValoare x = e[p].second;
			next[back[p]]=next[p];
			back[next[p]]=back[p];
			next[p]=primLiber;
			primLiber=p;
			size--;
			return x;
		}
		p=next[p];
	}

	//verificam daca elementul este pe ultima pozitie
	if(next[p]==-1 && e[p].first==c){
		//stergem elementul de pe ultima pozitie
		TValoare x = e[p].second;
		next[back[p]]=-1;
		next[p]=primLiber;
		primLiber=p;
		size--;
		return x;
	}


	return NULL_TVALOARE;

	//T(n)=O(n)	
}

void DO::goleste(){

	//reinitalizam spatiul liber
	for(int i=0;i<cp;i++){
		next[i]=i+1;
	}

	//setam parametrii pe pozitiea de inceput
	size=0;
	primLiber=0;
	prim=-1;

	//T(n)=theta(cp)
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	//returnam dimensiunea DO-ului
	return size;

	//T(n)=theta(1)
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	//verificam daca DO este vid
	return prim==-1;

	//T(n)=theta(1)
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {

	//dealocam memoria pentru vectorii folositi
	delete[] back;
	delete[] next;
	delete[] e;
	
}
