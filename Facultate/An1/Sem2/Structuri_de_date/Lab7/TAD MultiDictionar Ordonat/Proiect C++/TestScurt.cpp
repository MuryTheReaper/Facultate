#include "IteratorMDO.h"
#include "MDO.h"
#include <assert.h>
#include <iostream>

#include <exception>
#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
  if (cheie1 <= cheie2) {
    return true;
  } else {
    return false;
  }
}

void testAll() {
  MDO dictOrd = MDO(relatie1);
  assert(dictOrd.dim() == 0);
  assert(dictOrd.vid());
  dictOrd.adauga(1, 2);
  dictOrd.adauga(1, 3);
  assert(dictOrd.dim() == 2);
  assert(!dictOrd.vid());
  vector<TValoare> v = dictOrd.cauta(1);
  assert(v.size() == 2);
  v = dictOrd.cauta(3);
  assert(v.size() == 0);
  //   dictOrd.adauga(2, 2);
  //   dictOrd.adauga(2, 3);
  //   dictOrd.adauga(3, 0);
  // dictOrd.debugg();
  IteratorMDO it = dictOrd.iterator();
  it.prim();
  // int cont = 0;
  while (it.valid()) {
    TElem e = it.element();
    // std::cout << e.first << " " << e.second << "\n";
    //   cin.get();
    it.urmator();

    // cout << cont << "\n";
    // cont++;
    // cin.get();
  }
  assert(dictOrd.sterge(1, 2) == true);
  assert(dictOrd.sterge(1, 3) == true);
  assert(dictOrd.sterge(2, 1) == false);
  assert(dictOrd.vid());
}
