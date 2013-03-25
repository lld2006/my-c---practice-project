#include "../lib/tools.h"
#include <vector>
#include <cstdio>
using namespace std;
bool isPandig(int num){
    vector<int> vf;
    vf.resize(8, 0);
    while( num ){
        int res = num % 10;
        if(res == 0 || res > 7 ||vf[res] ) 
            return false;
        vf[res] = 1;
        num /= 10;
    }
    return true;
}
int main()
{
    vector<int> primes;
    primeWithin(primes, 7654321);
    for(int i = primes.size()-1; i>=0; --i ){
        int px = primes[i];
        if(isPandig(px)){
            printf("%d\n", px);
            break;
        }
    }
}
