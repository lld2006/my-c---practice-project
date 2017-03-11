#include "../lib/tools.h"
#include <cstdlib>
#include <algorithm>
//TODO speed is still not good enough
class pairLess 
{
    public:
        bool operator()(const IntPair& pa, const IntPair& pb){
            return (pa.first <= pb.first && pa.second < pb.second)||
                   (pa.first < pb.first && pa.second <= pb.second);
        }
};
class pairLess2
{
    public:
        bool operator()(const IntPair& pa, const IntPair& pb) {
            return pa.first + pa.second < pb.first + pb.second;
        }
};
int main(int argc, char* argv[])
{
    i64 nmod = 1000000007; //TODO 
    IntPairVec vpoints;
    int nmax = 10000000;
    if(argc == 2)
        nmax = atol(argv[1]);
    int xmax = sqrt(nmax/2);
    for(i64 a = 1; a<=xmax; ++a){
        for(i64 b=a+1; b; b+=2){
            if(gcd(a,b)>1) continue;
            i64 sa = b*b-a*a;
            i64 sb = 2*a*b;
            i64 sa2 = sa * sa;
            i64 sb2 = sb*sb;
            if(sa2 > nmax || sb2 > nmax) break;
            for(i64 k = 1; k; ++k){
                i64 k2 = k * k; 
                i64 xa = k2 * sa2;
                i64 xb = k2 * sb2;
                if(xa > nmax || xb > nmax) break;
                vpoints.push_back(IntPair(xa, xb));
                vpoints.push_back(IntPair(xb, xa));
            }
        }
    }
    vpoints.push_back(IntPair(nmax, nmax));
    printf("number of points=%zu\n", vpoints.size());
    sort(vpoints.begin(), vpoints.end(), pairLess2());
    vector<i64> vFactorial; 
    vFactorial.resize(2*nmax+1, 1);
    i64 prod = 1LL;
    for(i64 k = 2; k< (i64)vFactorial.size(); ++k){
        prod = multmod(prod, k, nmod);
        vFactorial[k] = prod;
    }
    vector<i64> vCount;
    vCount.resize(vpoints.size());
    i64 x, y, g;
    //initial value for all points
    for(unsigned int i = 0; i < vpoints.size(); ++i){
        int a = vpoints[i].first;
        int b = vpoints[i].second;
        i64 num = vFactorial[a+b];  
        i64 den = multmod(vFactorial[a], vFactorial[b], nmod);
        extended_euclid(den, nmod, x, y, g);
        num = multmod(num, x, nmod);
        vCount[i] = num;
    }
    pairLess o;
    for(unsigned int i = 0; i < vpoints.size(); ++i){
        i64 multiplier = vCount[i];
        for(unsigned int j = i+1; j < vpoints.size(); ++j){
            if(!o(vpoints[i], vpoints[j])) continue;
            i64 a = vpoints[j].first - vpoints[i].first;
            i64 b = vpoints[j].second-vpoints[i].second;
            i64 num = vFactorial[a+b];
            i64 den = multmod(vFactorial[a], vFactorial[b], nmod);
            extended_euclid(den, nmod, x, y, g);
            num = multmod(num, x, nmod);
            num = multmod(num, multiplier, nmod);
            vCount[j] -= num;
        }
    }
    i64 f = vCount.back() % nmod;
    if (f < 0) f+= nmod;
    printf("%lld\n", f);
}
