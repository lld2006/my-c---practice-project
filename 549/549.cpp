#include "../lib/tools.h"
#include <map>
class IntPairLess{
  public:
    bool operator() (const IntPair& p1, const IntPair& p2) const
    {
        return (p1.first < p2.first) || (p1.first == p2.first && p1.second < p2.second);
    }
};
using namespace std;
//some global variable
double root = 0;
int nmax = 100000000;
map<IntPair, int, IntPairLess> factorMap;

int find_prime_factor_val(const IntPair& np, const map<IntPair, int, IntPairLess>& factorMap )
{
    if(np.first > root){
        assert(np.second == 1);
        return np.first;
    }
    auto iter = factorMap.lower_bound(np); //some of the power are missing, 
    //so change find to lower_bound
    assert(iter != factorMap.end());
    return iter->second;
}
void check_p(int p, map<IntPair, int, IntPairLess>& factorMap, int nmax)
{
    assert(p > 1);
    vector<int> vres;
    vres.resize(30, 0);
    int npmax = log(nmax)/log(p);
    int rsize = 0;
    for(int val = p; val <= nmax; val += p){
        int res = 0;
        int pn = p;
        while(pn <= val ){
            res += val/pn;
            pn *=p;
        }
        //at most npmax of p is needed
        int index = val/p;
        vres[index] = res;
        rsize = index;
        if(res > npmax) break; //here should be break, no matter what happend, 
        //the rest part should always be processed
    }
    vres.resize(rsize+1);
    int tval = vres.back();
    assert(tval > 0);
    for(int j  = vres.size() - 1; j > 0; --j){
        if(vres[j] > 0) tval = vres[j];
        factorMap.insert(make_pair(IntPair(p, tval), j*p));//made a mistake here about key and val
    }
}
void update(int p, vector<int>& vn)
{
    i64 prod = p;
    int pow = 1;
    while(prod <= nmax){
        IntPair np = IntPair(p, pow);
        int val = find_prime_factor_val(np, factorMap);
        for(unsigned int ni = prod; ni < vn.size(); ni += prod){
            if(vn[ni] < val) vn[ni] = val;
        }
        prod *= p;
        ++pow;
    }
}
int main()
{
    vector<int> primes;
    primeWithin(primes, nmax);
    root = sqrt(nmax);
    // decided not to insert too many numbers into the map
    // preparing map
    for(unsigned int i = 0; i < primes.size(); ++i){
        int prime = primes[i];
        if (prime > root) break;
        check_p(prime, factorMap, nmax);
    }
    printf("map size %d\n", (int)factorMap.size());
    i64 sum = 0;
    vector<int> vn;
    vn.resize(nmax + 1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int prime = primes[i];
        update(prime, vn);
    }
    for(unsigned int k = 2; k < vn.size(); ++k)
        sum += vn[k];
    printf("%lld\n", sum);
}
