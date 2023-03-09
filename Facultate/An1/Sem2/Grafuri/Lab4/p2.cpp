#include <fstream>
#include <iostream>

void citire(char* file, int c[], int f[], int& n){
    std::ifstream fin(file);

    fin>>n;
    for(int i=0;i<n;i++){
        f[i]=0;
    }
    for(int i=0;i<n;i++){
        fin>>c[i];
        f[c[i]]++;

    }

    fin.close();
}

void decodare(int n, int c[], int f[]){
    
    int min=-1;
    std::cout<<n+1<<"\n";
    int p[n+1];
    for(int i=0;i<n+1;i++){
        p[i]=-1;
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n+1;i++){
            if(f[i]==0){
                min=i;
                break;
            }
        }
        p[min]=c[k];
        f[min]++;
        f[c[k]]--;

    }
    for(int i=0;i<n+1;i++){
        std::cout<<p[i]<<" ";
    }
    std::cout<<std::endl;


}

int main(int argc, char** argv){

   int c[100001],f[100001],n;
   citire(argv[1], c, f, n);
   decodare(n, c, f);

    return 0;
}