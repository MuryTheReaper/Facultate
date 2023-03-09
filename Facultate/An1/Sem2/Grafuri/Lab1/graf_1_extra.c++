#include <iostream>
#include <fstream>
using namespace std;
ifstream f("in.txt");
int i,j,x,y,mat_a[100][100],n,m,nr_i,zero,ok_regulat=1,viz[100];
#define INF 99999
void DFS(int x)
{
    int i;
    viz[x]=1;
    for(i=1;i<=n;i++)
        if(mat_a[x][i]==1 && viz[i]==0) DFS(i);
}
int Conex()
{
    int i;
    DFS(1);
    for(i=1;i<=n;i++)
        if(viz[i]==0) 
            return 0;
    return 1;
}
int main()
{
    f>>n>>m;
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        mat_a[x][y]=1;
        mat_a[y][x]=1;
        //calculam gradul nodurilor
        mat_a[x][0]+=1;
        mat_a[y][0]+=1;

    }
    //calculam noduri izolate
    cout<<"Noduri izolate: ";
    for(i=1;i<=n;i++)
    {   
        zero=0;
        for(j=1;j<=n;j++)
            zero=zero+mat_a[i][j];
        if(zero==0)
            cout<<i<<" ";
    }
    cout<<endl;
    //verificam daca este regulat
    for(i=2;i<=n;i++)
    {
        if(mat_a[i][0]!=mat_a[i-1][0]){
            ok_regulat=0;
            break;
            }
    }
    
    if(ok_regulat)
        cout<<"Regulat: T";
    else
        cout<<"Regulat: F";
    cout<<endl;

    if(Conex())
        cout<<"Conex: T";
    else
        cout<<"Conex: F";
    cout<<endl;
    
    //Punem INF unde nu se poate face drum direct
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(i!=j && mat_a[i][j]==0)
                mat_a[i][j]=INF;

    //Transformam in matrice de distante
    for(int k = 1 ; k <= n ; ++k)
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= n ; ++j)
                if((mat_a[i][j]>(mat_a[i][k]+mat_a[k][j])) && mat_a[k][j]!=INF && mat_a[k][j]!=INF)
                    mat_a[i][j] = mat_a[i][k] + mat_a[k][j];
    
    for(i=1;i<=n;i++)
    {   
        for(j=1;j<=n;j++)
            cout<<mat_a[i][j]<<" ";
        cout<<endl;
    }
    return 0;

}