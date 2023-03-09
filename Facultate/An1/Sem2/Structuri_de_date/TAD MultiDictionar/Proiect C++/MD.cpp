#include "MD.h"
#include "IteratorMD.h"
#include "Nod.h"
#include <exception>
#include <iostream>
#include <algorithm>

using namespace std;


MD::MD() {
	//Initializam primul nod cu null
	prim=nullptr;
	dime=0;

	//T(n)=theta(1)
}

void MD::adauga(TCheie c, TValoare v) {
	
	//Cream TElement cu c si v
	TElem e;
	e.first=c;
	e.second=v;

	//Cream nodul nou si il legam in fata celorlalte
	PNod q = new Nod(e, nullptr);
	q->urm = prim;
	prim = q;

	dime++;

	//T(n)=theta(1)
}


bool MD::sterge(TCheie c, TValoare v) {
	
	//verificam daca MD este vid(daca da => nu exista elementul)
	if(this->vid()==true)
		return false;

	//Verificam daca elementul de sters este primul element	
	PNod p = prim;
	if(prim->element().first==c && prim->element().second==v){
		prim=prim->urm;
		delete p;
		dime--;
		return true;
	}
	//Parcurgem MD-ul pana la nodul din fata elementului de sters sau pana la sfarsit
	while (p->urm!=nullptr && (p->urm->element().first!=c || p->urm->element().second!=v)) {
		p = p->urm;
	}
	//daca am ajuns la sfarsit => nu am gasit elementul
	if(p->urm==nullptr){
		return false;
	}
	//verificam daca elemtul de sters este ultimul
	if(p->urm->urm==nullptr){
		PNod q = p->urm;
		p->urm=nullptr;
		delete q;
		dime--;
		return true;
	}
	
	//daca ajungem aici => elementul de sters este intre 2 noduri
	PNod q=p->urm;
	p->urm=p->urm->urm;
	delete q;
	dime--;
	return true;

	//T(n)=O(n)
}

TValoare MD::ceaMaiFrecventaValoare() const{

	//Daca MD vid returnam NULL_TValoare
	if(this->vid()==true)
		return NULL_TValoare;

	vector<TValoare>V;
	vector<int>NR;

	PNod p=prim;
	//Parcurgem MD-ul
	while (p != nullptr) {
		//Cautam valoare daca exista sau trebuie incrementata
		TValoare key=p->element().second;
		vector<TValoare>::iterator it=find(V.begin(),V.end(),key);
		if(it==V.end()){
			//marcam ca exista
			V.push_back(key);
			NR.push_back(key);
		}else{
			//incrementam
			NR.push_back(key);
		}
		p = p->urm;
	}

	int max=-1,poz=-1;
	//cautam maxim;
	for(int i=0;i<V.size();i++){
		int nr=count(NR.begin(),NR.end(),V[i]);
		if(nr>max){
			max=nr;
			poz=i;
		}
	}

	//returnam pozitia maximului
	return V[poz];

	//CF: theta(n)
	//CD: theta(n^2)
	//T(n)=O(n^2)

}

vector<TValoare> MD::cauta(TCheie c) const {
	
	vector<TValoare> X;
	PNod p=prim;
	//parcurgem MD-ul si daca am gasit cheia punem valoarea in vector
	while (p != nullptr) {
		if(p->element().first==c){
			X.push_back(p->element().second);
		}
		p = p->urm;
	}
	return X;

	//T(n)=theta(n)
}


int MD::dim() const {
	
	return dime;

	//T(n)=theta(1)

	//sau varianta mai lunga

	/*int nr=0;
	PNod p = prim;
	//numaram cate elemete sunt
	while (p != nullptr) {
		p = p->urm;
		nr++;
	}
	return nr;

	//T(n)=theta(n)*/
}


bool MD::vid() const {
	//verficam daca MD este null
	if(prim==nullptr){
		return true;
	}
	return false;

	//T(n)=theta(1)

}

IteratorMD MD::iterator() const {
	//returnam iteratorul
	return IteratorMD(*this);

	//T(n)=theta(1)
}


MD::~MD() {
	
	//stergem fiecare nod
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
	
	//T(n)=theta(n)
}

