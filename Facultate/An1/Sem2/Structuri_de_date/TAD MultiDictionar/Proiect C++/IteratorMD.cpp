#include "IteratorMD.h"
#include "MD.h"
#include "Nod.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	//Initializam iteratorul
	curent=_md.prim;

	//T(n)=theta(1)
}

TElem IteratorMD::element() const{
	//Returnam elementul iteratorului sau exceptie daca nu este valid
	if(this->valid()){
		return curent->element();
	}
	else{
		throw exception();
	}

	//T(n)=theta(1)
}

bool IteratorMD::valid() const {
	//Verificam daca iteratorul este null
	return curent!=nullptr;

	//T(n)=theta(1)
}

void IteratorMD::urmator() {
	//Trecem pe pozitia urmatoara
	curent = curent->urmator();

	//T(n)=theta(1)
}

void IteratorMD::prim() {
	//Punem iteratorul pe prima pozitie
	curent= md.prim;

	//T(n)=theta(1)
}

