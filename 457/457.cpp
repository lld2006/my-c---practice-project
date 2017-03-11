#include "../lib/tools.h"
#include "../lib/int.h"
//try to avoid compile the code, try to make the code debuggable if needed
i64 find_mod_p2_13(i64 p)
{
    i64 sol = 0;
    i64 b = p * p; 
    bool exist = tonelli_shank((i64)p, 13LL%b, sol);
    if(!exist) return -1;
    assert((sol * sol )% p == 13LL);
    i64 a = 2 * sol;
    i64 x, y, gcd;
    extended_euclid(a, p, x, y, gcd);
    if(x < 0) x += p;
    assert(a*x % p == 1);
    i64 t = sol * sol -13;
    t %= b;
    GeneralInteger xt(t);
    GeneralInteger xx(x);
    GeneralInteger xy = xt.multiply(xx);
    GeneralInteger rem(1);
    GeneralInteger den (b);
    xy.divide(b, rem);
    i64 nsol = sol - rem.to_i64();
    nsol %= b;
    if(nsol < 0) nsol += b;
    assert(nsol > 0 && nsol < b);
    GeneralInteger isol(nsol);
    GeneralInteger i2 = isol.multiply(isol);
    i2.divide(b, rem);
    if(!(rem == GeneralInteger(13)))
        assert(0);
    //assert((nsol * nsol )% b == 13);
    i64 v1, v2;
    if(nsol & 1) {//odd
        v1 = (nsol + 3)/2;
        v2 = (2*b - nsol+3)/2;
    }else{//even
        v1 = (b+nsol+3)/2;
        v2 = (b-nsol+3)/2;
    }
    return v1 < v2? v1:v2;
}
int main()
{
    i64 nmax = 10000000;
    vector<int> vp;
    primeWithin(vp, nmax);
    i64 sum = 0;
    for(unsigned int i = 1; i< 6; ++i){
        int px = vp[i]*vp[i];
        i64 val = 0;
        int j = 0;
        for( j = 1; j< px; ++j ){
            val = j *j - 3*j -1;
            if(val % px == 0)
                break;
        }
        if(val % px == 0) 
            sum += j;
    }
    for(unsigned int i = 6; i < vp.size(); ++i){
        i64 t = find_mod_p2_13(vp[i]);
        if(t == -1) continue;
        sum += t;
    }
    printf("%lld %lld\n", nmax, sum);
}
