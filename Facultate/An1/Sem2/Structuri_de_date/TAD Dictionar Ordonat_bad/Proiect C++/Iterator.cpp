#include "Iterator.h"
#include "DO.h"
#include "Nod.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	//Initializam iteratorul
	curent=d.prim;

	//T(n)=theta(1)
}

void Iterator::prim(){
	//Setam iteratorul pe prima pozitie
	curent=dict.prim;

	//T(n)=theta(1)
}

void Iterator::urmator(){

	//aruncam exceptie daca iteratorul nu este valid
	if(!(this->valid())){
		throw exception();
	}
	//mutam iteratorul pe urmatoarea pozitie
	curent=curent->urmator();

	//T(n)=theta(1)
}

void Iterator::anterior(){

	//aruncam exceptie daca iteratorul nu este valid
	if(!(this->valid())){
		throw exception();
	}
	//mutam iteratorul pe urmatoarea pozitie

	curent=curent->precedent();
	//T(n)=theta(1)
}

bool Iterator::valid() const{
	
	//verificam daca iteratorul este valid
	return curent!=nullptr;

	//T(n)=theta(1)
}

TElem Iterator::element() const{
	
	//aruncam exceptie daca iteratorul nu este valid
	//returnam elementul referit de iterator
	if(this->valid()){
		return curent->element();
	}
	else{
		throw exception();
	}

	//T(n)=theta(1)
}


