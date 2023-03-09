#include <iostream>
#include <fstream>
std::ifstream f("in.txt");
# define INT_MAX 9999
# define NMAX 1000

int n,x,y,l;
int graf[NMAX][NMAX];

int minDistance(int dist[], bool sptSet[], int nV)
{
   
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < nV; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void dijkstra(int graph[NMAX][NMAX], int src, int nV, int dest)
{
    int dist[nV]; 
    bool sptSet[nV]; 
    
    for (int i = 0; i < nV; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    
    dist[src] = 0;
 
    
    for (int count = 0; count < nV - 1; count++) {
        
        int u = minDistance(dist, sptSet, nV);
 
        sptSet[u] = true;
 
        for (int v = 0; v < nV; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    
    std::cout<<"Lungime minima:"<<dist[dest]<<"\n";
    
}

int main(){

    int S,D;
    f>>n>>S>>D;

    while(f>>x>>y>>l){
        graf[x][y]=l;
    }

    dijkstra(graf, S, n, D);


}