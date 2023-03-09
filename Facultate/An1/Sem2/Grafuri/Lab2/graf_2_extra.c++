#include    <iostream>
#include    <fstream>
#include    <queue>
#include    <vector>
using namespace std;
ifstream fin("in.txt");
const int NMax = 50005;
const int oo = (1 << 30);
int N, M, p[100];
int D[NMax];
bool InCoada[NMax];
vector < pair <int,int> > G[NMax];
struct compara
{
    bool operator()(int x, int y)
    {
        return D[x] > D[y];
    }
};
priority_queue<int, vector<int>, compara> Coada;
void Citeste()
{
    fin >> N;
    int x,y;
    while(fin>>x>>y)
    {
        G[x].push_back(make_pair(y,1));
    }
}
void Dijkstra(int nodStart)
{
    for(int i = 1; i <= N; i++)
        D[i] = oo;
    D[nodStart]=0;
    Coada.push(nodStart);
    InCoada[nodStart] = true;
    while(!Coada.empty())
    {
        int nodCurent = Coada.top();
        Coada.pop();
        InCoada[nodCurent] = false;
        for(size_t i = 0; i < G[nodCurent].size(); i++)
        {
            int Vecin = G[nodCurent][i].first;
            int Cost = G[nodCurent][i].second;
            if(D[Vecin] == oo)
            {
                D[Vecin] = D[nodCurent] + Cost;
                p[Vecin] = nodCurent;
                if(InCoada[Vecin] == false)
                {
                    Coada.push(Vecin);
                    InCoada[Vecin] = true;
                }
            }
        }
    }
}   
void Afiseaza()
{
    for(int i = 2; i <= N; i++)
    {
        if(D[i] != oo)
            cout << D[i] << " ";
        else
            cout << "0 ";
    }
}
void Drum(int v)
{
    int k=D[v];
    int U[100];
    U[k]=v;
    while(k!=0)
    {
        U[k-1]=p[U[k]];
        k=k-1;
    }
    

}
int main()
{   
    Citeste();
    Dijkstra(1);


    //Afiseaza();
}