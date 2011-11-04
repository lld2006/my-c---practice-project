#include <cstdio>
int main()
{
    for( int i = 1 ; i<= 8; ++i)
        for ( int j = i+1; j <=9; ++j)
            for ( int k = i+1; k<=9; ++k){
                int xa = 10 * i +j;
                int xb = 10 *j +k;
                if( xa * k == xb * i)
                    printf( "%d %d %d\n",i, j, k);
            }
    return 0;
}
