#include <cstdio>
#include <numeric>
#include <vector>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

//lesson learned, made assumption here.
//all numbers are greater than 0, but actually it could be 0

i64 nmod = 1000000000LL;
double phi = (sqrt(5.0)+1)/2;
double log5 = log10(5.0);
void calcFib( i64& f1, i64& f2, i64& f3)
{
    //num will be credited to the next level
    f3 = f1 + f2;
    f3 %= nmod;
}

bool isPandigital(i64 n)
{
    vector<int> flags;
    flags.resize(10, 0);
    while(n > 0){
        int res = n% 10;
        if(!res) return false;
        if(flags[res])
            return false;
        else
            ++flags[res];
        n/=10;
    }
    int sum = accumulate(flags.begin(), flags.end(), 0);
    return (sum == 9);
}
bool pandigit(i64 f, int kth)
{
    if(!isPandigital(f)) return false;
    double nlog = log10(phi) * kth - log5/2.0;
    nlog = nlog - floor(nlog) + 8;
    i64 val = pow(10.0, nlog);
    return isPandigital(val);
}

int main()
{
   int kth =2;
   vector<i64> fib; 
   fib.resize(3, 0);
   fib[1] = 1;
   fib[0] = 1;
   while(true ){
       calcFib(fib[(kth-1)%3], fib[(kth-2)%3], fib[kth%3]);
       if(pandigit(fib[kth%3], kth+1)) 
           break;
       ++kth;
       if( kth % 100000 == 0 )
           printf("%d\n", kth);
   }
   printf("pandigit fibonacci is found at %d\n", kth+1);
}
