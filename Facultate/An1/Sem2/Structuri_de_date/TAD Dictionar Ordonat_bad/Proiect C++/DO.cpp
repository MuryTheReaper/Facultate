#include "Iterator.h"
#include "Nod.h"
#include "DO.h"
#include <cstddef>
#include <iostream>


#include <exception>
using namespace std;

DO::DO(Relatie r) {
	
	//initializam campurile
	prim=nullptr;
	rel=r;
	size=0;

	//T(n)=theta(1)
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	
	PNod p;
	//daca DO este vid atunci cream un prim element
	if(this->vid()){
		TElem e;
		e.first=c;
		e.second=v;
		PNod q= new Nod(e,nullptr,nullptr);
		prim=q;
		size++;
		return NULL_TVALOARE;
	}

	//Parcurgem DO pana gasim elementul sau elementul nu mai este in relatie sau am ajuns pe ultima pozitie
	p=prim;
	while (p->urm!=nullptr && rel(p->element().first,c)){
		if(p->element().first==c){
			//daca s-a gasit elementul in DO schimbam valoarea si o returnam pe chea veche
			TValoare x=p->e.second;
			p->e.second=v;
			return x;
		}
		p=p->urm;
	}

	if(p->urm==nullptr && p->element().first==c){
		//daca elementul este pe ultima pozitie in DO schimbam valoarea si o returnam pe chea veche
		TValoare x=p->e.second;
		p->e.second=v;
		return x;
	}

	if(p->urm==nullptr && rel(p->element().first,c)){
		//daca am ajuns la ultimul element trebuie sa introducem noul element pe ultima pozitie
		TElem e;
		e.first=c;
		e.second=v;
		PNod q = new Nod(e,nullptr,nullptr);
		q->urm=nullptr;
		q->pre=p;
		p->urm=q;
		size++;
		return NULL_TVALOARE;
	}

	if(!rel(p->element().first,c)){
		//daca elementul nu mai este in realtie avem 2 cazuri
		TElem e;
		e.first=c;
		e.second=v;
		PNod q = new Nod(e,nullptr,nullptr);
		if(p!=prim){
			//cazul in care elementul trebuie introdus undeva in interiorul DO in functie de relatie
			q->pre=p->pre;
			q->urm=p;
			p->pre->urm=q;
			p->pre=q;
			
		}
		else{
			//cazul in care elementul trebuie introdus pe prima pozitie
			q->pre=nullptr;
			q->urm=p;
			p->pre=q;
			prim=q;
		}
		size++;
		return NULL_TVALOARE;
	}

	return NULL_TVALOARE;

	//T(n)=O(n)

}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	
	//parcurgem DO pana cand ajungem la sfarsit sau elementul nu mai este in relatie
	PNod p=prim;
	while (p!=nullptr && rel(p->element().first,c)) {
		if(p->element().first==c){
			//daca am gasit elementul ne oprim
			return p->element().second;
		}
		p=p->urm;
	}
	return NULL_TVALOARE;

	//T(n)=O(n)

}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	
	//verificam daca DO este vid
	if(this->vid()==true)
		return NULL_TVALOARE;

	//verificam daca elementul este pe prima pozitie
	PNod p=prim;
	if(prim->e.first==c){
		//stergem elementul de pe prima pozitie
		TValoare x=prim->e.second;
		prim=prim->urm;
		delete p;
		size--;
		return x;
	}

	//parcurgem pana ajungem pe ultima pozitie sau elementul nu mai este in relatie
	while (p->urm!=nullptr && rel(p->element().first,c)){
		if(p->element().first==c){
			//stergem elementul din interiorul DO-ului
			TValoare x=p->e.second;
			p->pre->urm=p->urm;
			p->urm->pre=p->pre;
			delete p;
			size--;
			return x;
		}
		p=p->urm;
	}

	//verificam daca elementul este pe ultima pozitie
	if(p->urm==nullptr && p->element().first==c){
		//stergem elementul de pe ultima pozitie
		TValoare x=p->e.second;
		p->pre->urm=nullptr;
		delete p;
		size--;
		return x;
	}

	return NULL_TVALOARE;

	//T(n)=O(n)
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
	if(prim==nullptr){
		return true;
	}
	return false;

	//T(n)=theta(1)
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	
	//parcurgem DO-ul si stergem nodurile
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}

	//T(n)=theta(n)
}
