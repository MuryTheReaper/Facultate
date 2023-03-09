#include <cstddef>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <queue>
#define MAXSIZE 1000

struct nod {

    char data;
    int freq;
    nod *left, *right;
};

struct graph {

    int size;
    //std::priority_queue<nod*> tree;
    nod **tree;
};

void citire(char* file, int* freq, std::string& s,int& nr){
    std::ifstream f(file);

    for(int i=0;i<2000;i++){
        freq[i]=0;
    }

    std::getline(f,s);

    std::cout<<s<<"\n";
    nr=0;
    for(const char c:s){
        if(freq[int(c)]==0){
            nr++;
        }
        freq[int(c)]++;

    }
}

graph* create(int* freq,int& nr){
    
    graph* huff=new graph;

    huff->size=nr;
    int k=0;

    huff->tree=new nod*[nr];

    for(int i=0;i<2000;i++){
        if(freq[i]!=0){
            huff->tree[k]=new nod;
            huff->tree[k]->data=char(i);
            huff->tree[k]->freq=freq[i];
            huff->tree[k]->left=nullptr;
            huff->tree[k]->right=nullptr;
            k++;
        }
    }

    return huff;

}

nod* extract_min(graph* huff){

    int min=huff->tree[0]->freq,p=0;
    nod* x=new nod; //NOLINT

    for(int i=0;i<huff->size;i++){
        if(min>huff->tree[i]->freq){
            min=huff->tree[i]->freq;
            p=i;
        }
    }

    x=huff->tree[p];

    for(int i=p;i<huff->size-1;i++)  //NOLINT
        huff->tree[i]=huff->tree[i+1];

    huff->size--;
    
    return x;
}


void insert(graph* huff, nod* x){

    for(int i=huff->size-1;i>=0;i--){
        huff->tree[i+1]=huff->tree[i];
    }
    huff->tree[0]=x;    
    huff->size++;

}

nod* codare(graph* huff, int& nr){

    for(int i=0;i<nr;i++){
        nod* z=new nod;
        
        z->left=extract_min(huff);
        z->right=extract_min(huff);

        z->freq=z->left->freq + z->right->freq;
        z->data='|';
        insert(huff, z);
    }

    return extract_min(huff)->left;
}


void conversie(int top, nod* cod, int cif[], char x){

    if(cod->left!=nullptr){
        cif[top]=0;
        conversie(top+1, cod->left, cif, x);
    }

    if(cod->right!=nullptr){
        cif[top]=1;
        conversie(top+1, cod->right, cif, x);
    }

    if(cod->data==x){
        for (int i = 0; i < top; ++i)
            std::cout<< cif[i];
    }
}

int main(int argc, char **argv){

    int freq[2000],nr;
    std::string s;

    citire(argv[1], freq, s, nr);

    std::cout<<nr<<"\n";
    for(int i=0;i<2000;i++){
        if(freq[i]!=0){
            std::cout<<char(i)<<" "<<freq[i]<<"\n";
        }
    }

    graph* huff=create(freq, nr);
    nod* cod=codare(huff, nr);

    std::string c;
    int top=0, cif[nr];
    for(const char c:s)
       conversie(top, cod, cif, c);
    std::cout<<std::endl;


}

