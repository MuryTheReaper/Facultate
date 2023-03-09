#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#define MAXSIZE 1000

struct nod {

  char data;
  int freq;
  nod *left, *right;
};

struct graph {

  int size;

  nod **tree;
};

void citire(char *file, int *freq, std::string &s, int &nr) {
  std::ifstream f(file);

  for (int i = 0; i < 2000; i++) {
    freq[i] = 0;
  }
  std::string c;
  std::getline(f,c);

  nr=std::stoi(c);

  for (int i = 0; i < nr; i++) {
    std::getline(f,c);
    char k=c[0];
    c.erase(0,1);
    freq[int(k)] = std::stoi(c);
  }
  f >> s;
}

graph *create(int *freq, int &nr) {

  graph *huff = new graph;

  huff->size = nr;
  int k = 0;

  huff->tree = new nod *[nr];

  for (int i = 0; i < 2000; i++) {
    if (freq[i] != 0) {
      huff->tree[k] = new nod;
      huff->tree[k]->data = char(i);
      huff->tree[k]->freq = freq[i];
      huff->tree[k]->left = nullptr;
      huff->tree[k]->right = nullptr;
      k++;
    }
  }

  return huff;
}

nod *extract_min(graph *huff) {

  int min = huff->tree[0]->freq, p = 0;
  nod *x = new nod; // NOLINT

  for (int i = 0; i < huff->size; i++) {
    if (min > huff->tree[i]->freq) {
      min = huff->tree[i]->freq;
      p = i;
    }
  }

  x = huff->tree[p];

  for (int i = p; i < huff->size - 1; i++) // NOLINT
    huff->tree[i] = huff->tree[i + 1];

  huff->size--;

  return x;
}

void insert(graph *huff, nod *x) {

  for (int i = huff->size - 1; i >= 0; i--) {
    huff->tree[i + 1] = huff->tree[i];
  }
  huff->tree[0] = x;
  huff->size++;
}

nod *codare(graph *huff, int &nr) {

  for (int i = 0; i < nr; i++) {
    nod *z = new nod;

    z->left = extract_min(huff);
    z->right = extract_min(huff);

    z->freq = z->left->freq + z->right->freq;
    z->data = '|';
    insert(huff, z);
  }

  return extract_min(huff)->left;
}

void conversie(std::string s, nod *cod) {

  nod *p;
  p = cod;

  while (s.size()) {
    while (p->data == '|') {
      if (s[0] == '0')
        p = p->left;
      else
        p = p->right;
      s.erase(0, 1);
    }
    std::cout << p->data;
    p = cod;
  }
}

int main(int argc, char **argv) {

  int freq[2000], nr = 0;
  std::string s;

  citire(argv[1], freq, s, nr);

  std::cout << nr << "\n";
  for (int i = 0; i < 2000; i++) {
    if (freq[i] != 0) {
      std::cout << char(i) << " " << freq[i] << "\n";
    }
  }

  graph *huff = create(freq, nr);
  nod *cod = codare(huff, nr);

  conversie(s, cod);

  std::cout << std::endl;
}
