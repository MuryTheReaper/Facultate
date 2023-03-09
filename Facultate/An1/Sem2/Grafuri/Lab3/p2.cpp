#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;
#define MAX 100
#define INT_MAX 9999


typedef struct muchie 
{
    int src;
    int dest;
    int wt;
}muchie;


void citire(char in[], muchie x[], int &V, int &E){

    ifstream f(in);
    f>>V>>E;
    
    for(int i=0;i<E;i++){
        f>>x[i].src>>x[i].dest>>x[i].wt;
    }

    f.close();
}
bool bellman_ford(int nv,muchie e[],int src_graph,int ne, int dis[])
{
    int u,v,weight,i,j=0;
    //int dis[MAX];
    
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
            return false;
        }  
    }
    return true;
    /*cout<<"\nNOD "<<"  DISTANTA DE LA SURSA";
    for(i=0;i<nv;i++)
    {
        cout<<"\n"<<i<<"\t"<<dis[i];
    }
    cout<<"\n";*/

}
void add_nod(muchie x[], int &V, int &E){
    
    int S=V+1;
    for(int i=0;i<V;i++){
        x[E+i].src=S;
        x[E+i].dest=i;
        x[E+i].wt=0;
    }
    V++;
    E=E+V;

}
void modificare(muchie x[], int dis[], int &V, int &E){

    cout<<"Muchii dupa reponderare\n";
    for(int i=0;i<E-V;i++){
       x[i].wt=x[i].wt+dis[x[i].src]-dis[x[i].dest];
       cout<<x[i].src<<" "<<x[i].dest<<" "<<x[i].wt<<"\n";
    }
}
int minDistance(int dist[], bool sptSet[], int nV)
{
   
    // Initialize min value
    int min = INT_MAX, min_index=-1;
 
    for (int v = 0; v < nV; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
void dijkstra(int graph[MAX][MAX], int src, int nV, int dist[])
{
    //int dist[nV]; 
    bool sptSet[nV]; 
    
    for (int i = 0; i < nV; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    
    dist[src] = 0;
 
    
    for (int count = 0; count < nV - 1; count++) {
        
        int u = minDistance(dist, sptSet, nV);
 
        sptSet[u] = true;
 
        for (int v = 0; v < nV; v++)
            if (!sptSet[v] && graph[u][v]!=-1 && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    /*cout <<"Vertex \t Distance from Source" << endl;
    for (int i = 0; i < nV; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;*/
}

int main(int argc, char* argv[]){


    //adauga un nou nod, leagal de lelelate cu muchie de cost 0
    //aplica bellman-ford
    //repondereaza graful
    //aplica dijksta pe toate nodurile

    int V,E,dis[MAX];
    muchie x[MAX];
    citire(argv[1], x, V, E);
    add_nod(x, V, E);
    bool ok=bellman_ford(V,x,V,E,dis);

    if(!ok){return 0;}

    modificare(x, dis, V, E);

    int graf[MAX][MAX];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            graf[i][j]=-1;
    }

    for(int i=0;i<E;i++){
        graf[x[i].src][x[i].dest]=x[i].wt;
    }
    int new_dis[MAX];
    for(int i=0;i<V-1;i++){
        dijkstra(graf, i, V, new_dis);
        for(int j=0;j<V-1;j++){
            graf[i][j]=new_dis[j]-dis[i]+dis[j];
        }
    }
                
    for(int i=0 ;i< V-1;i++)
    {   
        for(int j=0;j< V-1;j++)
            if(graf[i][j]>=9999)
                cout<<"INF ";
            else
                cout<<graf[i][j]<<" ";
        cout<<endl;
    }

    
}
