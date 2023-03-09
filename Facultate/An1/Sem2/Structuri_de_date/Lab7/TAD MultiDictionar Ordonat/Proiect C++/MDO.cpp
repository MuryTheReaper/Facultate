#include "MDO.h"
#include "IteratorMDO.h"
#include <algorithm>
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
  // initializare campuri
  rel = r;
  radacina = -1;
  primLiber = 0;
  size = 0;

  // initializare vectori
  for (int i = 0; i < MAXSIZE; i++) {
    stanga[i] = -1;
    dreapta[i] = -1;
  }
}
void MDO::adauga(TCheie c, TValoare v) { /* de adaugat */
  TElem x;
  x.first = c;
  x.second = v;

  // apelam metoda recursiva
  radacina = adauga_rec(radacina, x);
  size++;

  // mutam primLiber pe prima pozitie libera
  int i = 0;
  while (e[i].valori.size()) {
    i++;
  }
  primLiber = i;
  // T(n)=O(h+MAXSIZE)
}

int MDO::adauga_rec(int p, TElem x) {
  if (p == -1) {
    // am ajuns la un subarbore vid si trebuie adaugat elementul
    e[primLiber].cheie = x.first;
    e[primLiber].valori.push_back(x.second);
    stanga[primLiber] = -1;
    dreapta[primLiber] = -1;
    p = primLiber;
  } else if (e[p].cheie == x.first) {
    // exista cheia deja in arbore si trebuie sa adaugam in vectorul cheii
    e[p].valori.push_back(x.second);
  } else {
    // continuam parcurgerea
    if (rel(x.first, e[p].cheie)) {
      // trebuie adaugat in arborele stang(<=)
      stanga[p] = adauga_rec(stanga[p], x);
    } else {
      // trebuie adaugat in arborele drept(>)
      dreapta[p] = adauga_rec(dreapta[p], x);
    }
  }
  // returnam radacina subarborelui
  return p;
}

vector<TValoare> MDO::cauta(TCheie c) const {

  // apelam metoda recursiava si retinem pozitia cheii in vector
  int poz = cauta_rec(radacina, c);

  // cream vectorul de TValori si il populam cu valoriile de la pozitia cheii
  vector<TValoare> vec;
  for (auto x : e[poz].valori) {
    vec.push_back(x);
  }

  // returnam vectorul
  return vec;

  // T(n)=O(h)
}

int MDO::cauta_rec(int p, TCheie x) const {
  if (p == -1 || e[p].cheie == x) {
    // daca nu exista(subarobore vid) sau daca am gasit cheia returnam pozitia
    return p;
  } else {
    if (rel(x, e[p].cheie)) {
      // cautam in subarborele stang(<=)
      return cauta_rec(stanga[p], x);
    } else {
      // cautam in subarborele drept(>)
      return cauta_rec(dreapta[p], x);
    }
  }
}

bool MDO::sterge(TCheie c, TValoare v) {
  TElem x;
  x.first = c;
  x.second = v;

  bool ok = false;

  // cautam mai intai daca exista cheia
  vector<TValoare> vec = cauta(c);

  for (auto e : vec) {
    // cautam daca exsita valoarea
    if (e == v) {
      ok = true;
      break;
    }
  }
  // daca nu exsita TElementul returnam false
  if (ok == false)
    return false;

  // apelam stergerea recursiva
  radacina = sterge_rec(radacina, x);
  size--;
  return true;

  // T(n) = O(h)
}
int MDO::sterge_rec(int p, TElem x) {
  if (p == -1) {
    // daca s-a ajuns la subarbore vid
    return -1;
  } else {
    if (rel(x.first, e[p].cheie) && x.first != e[p].cheie) {
      // stergem din subarborele stang(<)
      stanga[p] = sterge_rec(stanga[p], x);
      return p;
    } else if (!rel(x.first, e[p].cheie) && x.first != e[p].cheie) {
      // stergem din subarborele drept(>)
      dreapta[p] = sterge_rec(dreapta[p], x);
      return p;
    } // am ajuns pe pozitia elelemtului de sters
    else if (stanga[p] != -1 && dreapta[p] != -1) {
      // cheia are subarbore drept si stang
      if (e[p].valori.size() == 1) {
        // cheia are o singura valoare
        auto temp = minim(dreapta[p]);
        e[p].valori.clear();
        e[p] = e[temp];
        // se muta cheia minima in p
        TElem aux;
        aux.first = e[p].cheie;
        aux.second = e[p].valori[0];
        dreapta[p] = sterge_rec(dreapta[p], aux);
        // se sterge cheia minima din subarborele drept
      } else {
        // daca cheia are mai multe valori se sterge cea indicata
        e[p].valori.erase(
            std::remove(e[p].valori.begin(), e[p].valori.end(), x),
            e[p].valori.end());
      }
      return p;
    } else {
      // cheia are ori subarbore drept ori stang
      if (e[p].valori.size() == 1) {
        // cheia are o singura valoare
        auto temp = p;
        e[temp].valori.clear();
        int repl;
        if (stanga[p] == -1) {
          // nu are subarbore stang
          repl = dreapta[p];
        } else {
          // nu are subarbore drept
          repl = stanga[p];
        }
        // dealoca(temp)
        return repl;
      } else {
        // daca cheia are mai multe valori se sterge cea indicata
        e[p].valori.erase(
            std::remove(e[p].valori.begin(), e[p].valori.end(), x),
            e[p].valori.end());
        return p;
      }
    }
  }
}

int MDO::dim() const {
  return size;
  // T(n)=theta(1)
}

bool MDO::vid() const {
  return radacina == -1;
  // T(n)=theta(1)
}

IteratorMDO MDO::iterator() const { return IteratorMDO(*this); }

MDO::~MDO() { /*ALOCAT STATIC*/
}

int MDO::minim(int p) const {

  // subarbore vid
  if (p == -1)
    return -1;

  // mergem pana la capatul subarborelui stang(<=)
  while (stanga[p] != -1) {
    p = stanga[p];
  }
  return p;
  // T(n)=O(h)
}

int MDO::parinte(int p) const {
  // daca suntem in radacina returnam -1
  if (p == radacina) {
    return -1;
  }

  int poz = radacina;
  TCheie c = e[p].cheie;
  // parcurgem pana gasim nodul p si ne oprim la parintele lui
  while (dreapta[poz] != p && stanga[poz] != p) {
    if (rel(c, e[poz].cheie)) {
      poz = stanga[poz];
    } else
      poz = dreapta[poz];
  }

  return poz;
  // T(n)=O(h)
}

int MDO::succesor(int p) const {
  // exista subarbore drept si doar returnam minimul
  if (dreapta[p] != -1) {
    return minim(dreapta[p]);
  }
  int poz = parinte(p);
  // daca nu exista subarbore drept trebuie sa iesim din subarbore stang
  while (poz != -1 && p == dreapta[poz]) {
    p = poz;
    poz = parinte(p);
  }
  return poz;
  // T(n)=O(h^2)
}

vector<TValoare> MDO::colectiaValorilor() const {

  vector<TValoare> vec;

  for (int i = 0; i < MAXSIZE; i++) {
    if (e[i].valori.size()) {
      for (auto elm : e[i].valori) {
        vec.push_back(elm);
      }
    }
  }

  return vec;

  // T(n)=theta(n+MAXSIZE)

  // pseudocod

  /* colectiaValorilor(vec - o)
        pre: d - MDO
        post vec - vectorul care contine toate TValorile din MDO

      pentru i=0, d.MAXSIZE executa
        daca d.e[i].valori.dim != 0 atunci
          pentru j=0, d.e[i].valori.dim executa
            vec.push_back(d.e[i].valoari[j])
          sf pentru
        sf daca
      sf pentru

      colectieValorilor <- vec

  */
}
