#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdlib>
using namespace std;
vector<i64> factorials, modinv;
i64 nmod = 100000007;
void solve23(int& n2, int& n3, int ntot)
{
    n2 = 2*ntot;
    n3 = -ntot;
    int n2res = n2%3;
    int shift = (n2-n2res)*2/3;
    n3 += shift;
    n2 = n2res;
    return;
}
i64 inv(i64 num)
{
    if(num == 0||num==1)
        return 1;
    if(num < modinv.size() && modinv[num] > 0)
        return modinv[num];
    i64 x=0, y=0, gcd=0;
    extended_euclid(num, nmod, x, y, gcd);
    assert(gcd == 1);
    if(x < 0){
        x%=nmod;
        x+=nmod;
    }
    assert(num > 0);
    if(num < modinv.size())
        modinv[num] = x;
    return x;
}
int main(int argc, const char *argv[])
{
    int target = atol(argv[1]);
    factorials.resize(target+1, 0);
    modinv.resize(target+1, 0);
    factorials[0] = 1;
    i64 prod = 1;
    for( int i= 1; i<=target; ++i ){
        prod *= i;
        prod %= nmod;
        factorials[i] = prod;
    }
    int n2=0, n3= 0;
    i64 sum = 0;
    solve23(n2, n3, target - 1);
    for(int a = n2, b = n3; b >= 0; a+=3, b-=2){
        prod = factorials[a+b+1];
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= factorials[b];
        prod %= nmod;
        prod *= powermodule(2, b, nmod);
        prod %= nmod;
        prod *= inv(factorials[a]);
        prod %= nmod;
        prod *= inv(factorials[b]);
        prod %= nmod;
        sum += prod;
    }
    solve23(n2, n3, target - 3);
    for(int a = n2, b = n3; b >= 0; a+=3, b-=2){
        prod = factorials[a+b+1];
        prod *= factorials[2+b];
        prod %= nmod;
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= powermodule(2, b, nmod);
        prod %= nmod;
        prod *= inv(factorials[a]);
        prod %= nmod;
        prod *= inv(factorials[b]);
        prod %= nmod;
        sum += prod;
    }
    //this is a little bit tricky
    solve23(n2, n3, target - 2);
    for(int a = n2, b = n3; b >= 0; a+=3, b-=2){
        prod = powermodule(2, b+1, nmod);
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= factorials[a+b+1];
        prod %= nmod;
        prod *= factorials[a+b];
        prod %= nmod;
        prod *= factorials[1+b];
        prod %= nmod;
        prod *= inv(factorials[a]);
        prod %= nmod;
        prod *= inv(factorials[b]);
        prod %= nmod;
        sum += prod;
    }
    sum %= nmod;
    printf("%lld\n",sum);
}
