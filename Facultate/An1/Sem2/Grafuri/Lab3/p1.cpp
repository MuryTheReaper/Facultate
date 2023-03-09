#include <iostream>
#include <fstream>

using namespace std;

typedef struct muchie 
{
    int src;
    int dest;
    int wt;
}muchie;

#define nV 100
#define INT_MAX 9999


void citire(char in[], muchie x[], int &V, int &E, int &S){

    ifstream f(in);
    f>>V>>E>>S;
    
    for(int i=0;i<E;i++){
        f>>x[i].src>>x[i].dest>>x[i].wt;
    }

    f.close();
}
void bellman_ford(int nv,muchie e[],int src_graph,int ne)
{
    int u,v,weight,i,j=0;
    int dis[100000];
    
    for(i=0;i<nv;i++)
    {
        dis[i]=999;
    }
        
    dis[src_graph]=0;
    
    /* 'relaxam' muchiile nv - 1 ori */
    for(i=0;i<nv-1;i++)
    {
        for(j=0;j<ne;j++){
            u=e[j].src;
            v=e[j].dest;
            weight=e[j].wt;
            
            if(dis[u]!=999 && dis[u]+weight < dis[v]){
                dis[v]=dis[u]+weight;
            }  
        }
        
    }
    
    /* verificam ciclu negativ */
    for(j=0;j<ne;j++)
    {
        u=e[j].src;
        v=e[j].dest;
        weight=e[j].wt;
        
        if(dis[u]+weight < dis[v]){
            cout<<"\nCICLU NEGATIV!!\n";
            return;
        }  
    }
    
    cout<<"\nNOD "<<"  DISTANTA DE LA SURSA";
    for(i=0;i<nv;i++)
    {
        cout<<"\n"<<i<<"\t"<<dis[i];
    }
    cout<<"\n";
}

int minDistance(int dist[], bool sptSet[])
{
   
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < nV; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void dijkstra(int graph[nV][nV], int src)
{
    int dist[nV]; 
    bool sptSet[nV]; 
    
    for (int i = 0; i < nV; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    
    dist[src] = 0;
 
    
    for (int count = 0; count < nV - 1; count++) {
        
        int u = minDistance(dist, sptSet);
 
        sptSet[u] = true;
 
        for (int v = 0; v < nV; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    cout <<"Vertex \t Distance from Source" << endl;
    for (int i = 0; i < nV; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
}


int main(int argc, char* argv[]){

    int V,E,S;
    muchie x[100600];
    citire(argv[1], x, V, E, S);
    bellman_ford(V,x,S,E);
    
}
