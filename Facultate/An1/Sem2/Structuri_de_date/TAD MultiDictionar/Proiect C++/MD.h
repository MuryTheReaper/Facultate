#pragma once
#include<vector>
#include<utility>
#include "Nod.h"

using namespace std;

typedef int TCheie;
typedef int TValoare;
#define NULL_TValoare 0;


typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;
class Nod;
typedef Nod *PNod;

class MD
{
	friend class IteratorMD;

private:
	
	//adresa primului nod
	PNod prim;
	//eventual dimenisunea
	int dime;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	// returneaza valoarea care apare cel mai frecvent în multidicționar. Dacă mai multe valori apar cel mai frecvent, se returnează una (oricare) dintre ele. 
	// Dacă multidicționarul este vid, operația returnează NULL_TVALOARE 
	TValoare ceaMaiFrecventaValoare() const;

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

