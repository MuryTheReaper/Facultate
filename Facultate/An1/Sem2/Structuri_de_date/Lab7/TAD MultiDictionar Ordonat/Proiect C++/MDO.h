#pragma once

#include <algorithm>
#include <vector>

typedef int TCheie;
typedef int TValoare;

#define MAXSIZE 1000

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool (*Relatie)(TCheie, TCheie);

class MDO {
  friend class IteratorMDO;

private:
  // relatia
  Relatie rel;
  // vectorul de elemente
  struct {
    TCheie cheie;
    vector<TValoare> valori;
  } e[MAXSIZE];
  // date e[MAXSIZE];
  //  vector pentru stanga si dreapta
  int stanga[MAXSIZE];
  int dreapta[MAXSIZE];

  int primLiber;
  int radacina;
  int size;

  // functii de aditionale folositoare
  int minim(int p) const;
  int succesor(int p) const;
  int parinte(int p) const;
  int adauga_rec(int p, TElem x);
  int cauta_rec(int p, TCheie x) const;
  int sterge_rec(int p, TElem x);

public:
  // constructorul implicit al MultiDictionarului Ordonat
  MDO(Relatie r);

  // adauga o pereche (cheie, valoare) in MDO
  void adauga(TCheie c, TValoare v);

  // cauta o cheie si returneaza vectorul de valori asociate
  vector<TValoare> cauta(TCheie c) const;

  // sterge o cheie si o valoare
  // returneaza adevarat daca s-a gasit cheia si valoarea de sters
  bool sterge(TCheie c, TValoare v);

  // returneaza numarul de perechi (cheie, valoare) din MDO
  int dim() const;

  // verifica daca MultiDictionarul Ordonat e vid
  bool vid() const;

  // se returneaza iterator pe MDO
  // iteratorul va returna perechile in ordine in raport cu relatia de ordine
  IteratorMDO iterator() const;

  // destructorul
  ~MDO();

  // returneaza un vector cu toate valorile din MultidicționarOrdonat
  vector<TValoare> colectiaValorilor() const;
};
