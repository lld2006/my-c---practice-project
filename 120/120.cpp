#include <cstdio>
#include <cassert>

int maxres(int num)
{
    int nmax = 0;
    int n2 = num * num;
    for( int k = 1; k< 2*num; k+=2 ){
        int value = 2*k*num;
        value %= n2;
        if(value > nmax)
            nmax = value;
    }
    assert(nmax >= 2);
    return nmax;
}
int main()
{
    int sum = 0;
    for( int i = 3; i<= 1000; ++i){
        sum += maxres(i);
    }
    printf("%d\n", sum);
}
