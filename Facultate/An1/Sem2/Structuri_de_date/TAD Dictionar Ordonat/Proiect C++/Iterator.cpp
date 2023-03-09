#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	//Initializam iteratorul
	curent = d.prim;

	//T(n)=theta(1)
}

void Iterator::prim(){
	//Setam iteratorul pe prima pozitie
	curent = dict.prim;

	//T(n)=theta(1)
}

void Iterator::urmator(){
	//aruncam exceptie daca iteratorul nu este valid
	if(!this->valid()){
		throw exception();
	}
	//mutam iteratorul pe urmatoarea pozitie
	curent = dict.next[curent];

	//T(n)=theta(1)
		
}

bool Iterator::valid() const{
	//verificam daca iteratorul este valid
	return curent!=-1;

	//T(n)=theta(1)
}

TElem Iterator::element() const{
	
	//aruncam exceptie daca iteratorul nu este valid
	if(!this->valid()){
		throw exception();
	}
	//returnam elementul referit de iterator
	return dict.e[curent];

	//T(n)=theta(1)
}



