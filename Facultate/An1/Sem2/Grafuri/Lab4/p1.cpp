#include <fstream>
#include <iostream>

void citire(char* file, int p[], int f[], int& n){

    std::ifstream fin(file);

    fin>>n;
    for(int i=0;i<n;i++){
        f[i]=0;
    }
    for(int i=0;i<n;i++){
        fin>>p[i];
        if(p[i]!=-1)
            f[p[i]]++;

    }

    fin.close();

}

void codare(int n, int p[], int f[]){
    
    int min=-1;
    std::cout<<n-1<<"\n";

    for(int k=0;k<n-1;k++){

        for(int i=0;i<n;i++){
            if(f[i]==0){
                min=i;
                break;
            }
        }

        std::cout<<p[min]<<" "; //NOLINT

        f[min]--;
        f[p[min]]--;
    }
    std::cout<<std::endl;


}

int main(int argc, char** argv){

    int p[100001],f[100001],n;
    citire(argv[1], p, f, n);
    codare(n, p, f);

    return 0;
}