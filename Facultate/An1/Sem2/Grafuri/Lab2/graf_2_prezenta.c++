#include <iostream>
#include <fstream>
using namespace std;
ifstream f("in.txt");
int i,j,x,y,mat_a[100][100],n;
#define INF 99999
int main()
{
    f>>n;
    while(f>>x>>y)
    {
        mat_a[x][y]=1;
    }  
    
    //inchidere transitiva
    for(int k = 1 ; k <= n ; ++k)
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= n ; ++j)
                if(mat_a[i][j] == 0)
                    mat_a[i][j] = mat_a[i][k] * mat_a[k][j];

    for(i=1;i<=n;i++)
    {   
        for(j=1;j<=n;j++)
            cout<<mat_a[i][j]<<" ";
        cout<<endl;
    }
    return 0;

}