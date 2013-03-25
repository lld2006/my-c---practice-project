#include <cstdio>
#include <array>
#include "../lib/typedef.h"
using namespace std;
#define nmax 20
i64 search_pathes( int row, int col, i64 a[nmax+1][nmax+1])
{
    //assert(row >= 0 && col >= 0 && row <)
    if(a[row][col] > 0 ) 
        return a[row][col];
    i64 value = search_pathes(row-1, col, a) + 
        search_pathes(row, col-1, a);
    a[row][col] = value;
    return value;
}
int main()
{
    i64 a[nmax+1][nmax+1];
    for( int i = 0; i < nmax+1; ++i)
        for( int j = 0; j < nmax+1; ++j){
            a[i][j] = 0;
        }
    for(int i = 0; i < nmax+1; ++i){
        a[i][0] = 1;
        a[0][i] = 1;
    }
    i64 value = search_pathes(nmax, nmax, a);
    printf("%lld\n", value);
}
