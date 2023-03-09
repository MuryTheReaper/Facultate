#include <iostream>
#include <fstream>
using namespace std;
ifstream f("in.txt");
int i,j,x,y,mat_a[100][100],n,m,mat_v[100][100],k;
int main()
{
    f>>n>>m;
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        mat_a[x][y]=1;
        mat_a[y][x]=1;

    }
    for(i=1;i<=n;i++)
    {   
        for(j=1;j<=n;j++)
            cout<<mat_a[i][j]<<" ";
        cout<<endl;
    }
    for(i=1;i<=n;i++)
    {   k=1;
        for(j=1;j<=n;j++)
            if (mat_a[i][j]==1)
                {
                    mat_v[i][k]=j;
                    k++;
                }
        if(k>1)
        mat_v[i][0]=k-1;
        else
        mat_v[i][0]=k;

    }
    for(i=1;i<=n;i++)
    {   
        for(j=1;j<=mat_v[i][0];j++)
            cout<<mat_v[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}