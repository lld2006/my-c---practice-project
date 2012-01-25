#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
void findSquares(I64PairVec& fac, vector<int>& squares, int pos, int value){
    //pos is the index that needs to be investigated
    for()
    
}
int main(){
    vector<int> primes;
    primeWithin(primes, 50);
    int count = 0;
    for(i64 a = 2; a< 1000; a+=3){
        int u2v = (a*8-1);
        assert(u2v %3 == 0);
        int xu = 1; 
        int xv = u2v/3;
        I64PairVec ifac;
        vector<int> squares;
        factor(xv, ifac, primes);
        findSquares(ifac, squares, 0, 1);
        int b = (3+ xv);
        if(b %8 != 0)
            continue;
        b /= 8;
        if(a + b + xv <= 1000){
            printf("%d\n", b);
            ++count;
        }
    }
    printf("%d\n", count);
}
