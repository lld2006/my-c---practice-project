#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
//why my chinses remainder theorem not working well here !!!!! 
//any other approach ????
//see http:///www.johndcook.com/blog/quadratic_congruences for detail
//of the mod p^n algo
//
// if x^2 mod p^k = 1 && y^2 mod q^l = 1
// then the u^2 = 1 mod p^k q^l
//
vector<vector<int>> vSolutions; //primeIndex + powerIndex, save only one typical solution
vector<int> vprimes;
vector<int> ftable;
vector<int> vpIndex;
vector<int> one;


vector<int>& get_2_solutions(int power, int res);
vector<int>& mod_odd_p_n(int prime, int pow, int res);
vector<int> getSolution(int prime, int power, int res);


i64 chinese_remainder_theorem2(const vector<i64>& vp, const vector<i64>& vr)
{
    i64 N = 1; 
    for(unsigned int i = 0; i < vp.size(); ++i)
        N*= vp[i];
    i64 sum = 0;
    for(unsigned int i = 0; i< vp.size(); ++i){
        i64 a =  N /vp[i];
        i64 b = vp[i];
        i64 x=1, y=1, gcd=1;
        extended_euclid(a, b, x, y, gcd);
        if((a *x ) % b != 1){
            assert(x < 0);
            x+=b;
            assert((a * x )% b == 1);
        }
        sum +=  vr[i] * a *x;
    }
    sum %= N;
    return sum;
}

int getPrimeIndex( int prime)
{
    return vpIndex[prime];
}

vector<int> mod_2_n(int n, int res)
{
    vector<int> v2n;
    assert( res == 1);
    if(n == 1){
        v2n.push_back(1);
    }else if (n == 2){
        v2n.push_back(1);
    }else if(n==3){
        v2n.push_back(3);
    }else{
        vector<int> v2p1 = getSolution(2, n-1, 1);
        vector<int>& v2p  = v2n;
        for(unsigned int i = 0; i < v2p1.size(); ++i){
            i64 px = v2p1[i];
            px *= px;
            px -= res;
            px /= (1LL<<(n-1));
            px = (px & 1) ?  v2p1[i] + (1LL<<(n-2)):v2p1[i];
            px %= (1LL<<n);
            if(px == 1){
                px += (1<<(n-1));
            }else if(px == (1<<n)-1){
                px -= (1<<(n-1));
            }
            assert((px * px - res) % (1<< n) == 0);
            v2p.push_back(px);

        }
        assert(v2p.size() == 1);
    }
    return v2n;
}

vector<int> getSolution(int prime, int power, int res)
{
    assert(power > 0);

    int primeIndex = getPrimeIndex(prime);
    assert(primeIndex >= 0);
    if(prime == 2){
        vector<int>& v2sol = get_2_solutions(power, res);
        vector<int> sol;
        sol.push_back(v2sol[power]);
        return sol;
    }else{
        return mod_odd_p_n(prime, power, res);
    }
}

vector<int>& get_2_solutions(int power, int res)
{
    assert(res == 1 && power > 0);
    if (vSolutions[0].size() <= (unsigned int)power){
        vSolutions[0].resize(power+1, 0);
        return get_2_solutions(power, res);
    }
    if(vSolutions[0][power] == 0){
        //create it!
        vSolutions[0][power]  = mod_2_n(power, 1)[0];
    }
    return vSolutions[0];
}
//the number of solution is 2 when mod p^n x and -x, so just one
//solution per power
vector<int>& mod_odd_p_n(int prime, int pow, int res )
{
    assert(pow > 0);
    assert(prime & 1);
    assert(res == 1);
    return one; //I will leave it for later
    int primeIndex = getPrimeIndex(prime);
    assert(primeIndex < (int)vSolutions.size());
    vector<int>& vpn = vSolutions[primeIndex];
    if(static_cast<int>(vpn.size()) <= pow)
        vpn.resize(pow+1, 0);
    if(pow == 1){
        vpn[1] = 1;
    }else if( vpn[pow] > 0){
        ;
    }else{
        if(vpn[pow-1] == 0){
            //recursive call for results
            mod_odd_p_n(prime, pow-1, res);
        }
        i64 val = 2*vpn[pow-1];
        i64 tpow = pow;
        i64 pk = power((i64)prime, tpow);
        i64 x, y, gcd;
        extended_euclid(val, pk, x, y, gcd);
        assert(gcd == 1);
        vpn[pow] = vpn[pow-1]- (vpn[pow-1] * vpn[pow-1] -res)*x;
        vpn[pow] %= pk*prime;
        assert((vpn[pow] * vpn[pow]-res ) % (pk*prime) == 0);
    }
    return vpn;
}

vector<int> getRealSolutions(int prime, int pow, int res)
{
    assert(res == 1);
    vector<int> sol = getSolution(prime, pow, res);
    vector<int> rsol(sol);
    if(prime == 2){
        if(pow == 1) 
            ;
        else if(pow == 2){
            rsol.push_back(4 -sol[0]);
        }else if(pow >= 3){
            rsol.push_back((1<<pow) -sol[0]);
            rsol.push_back(1);
            rsol.push_back((1<<pow)-1);
        }
    }else{
        int value = power(prime, pow);
        rsol.push_back(value-1);
    }
    return rsol;
}

//check function
//i64 get_max_square_1(int n, const IntPairVec& nfac)
//{
//    vector<int> vn;
//    vn.resize(n, 0);
//    int fsize = nfac.size();
//    for(unsigned int i = 0; i < nfac.size(); ++i){
//        int nf = nfac[i].first;
//        int pf = nfac[i].second;
//        int px = power(nf, pf);
//        vector<int> vs1 = getRealSolutions(nf, pf, 1);
//        for(unsigned int j = 0; j < vs1.size(); ++j){
//            int xj = vs1[j];
//            for( int y = xj ; y < n; y += px){
//                ++vn[y];
//            }
//        }
//    }
//    i64 max = 0;
//    for(int k = n - 2; k >= 1; --k ){
//       if(vn[k] ==fsize){
//           max = k;
//           break;
//       }
//    }
//    assert( (max*max) % n == 1);
//    return max;
//}
// since I used the factor_table_min so the first one
// can be 2 or 4 for termination purpose
void getNextConfig(vector<int>& vIndex)
{
    int inced = 0;
    int k = vIndex.size() - 1;
    do{
        inced = 0;
        ++vIndex[k];
        if(k > 0 && vIndex[k]==2){
            vIndex[k] = 0;
            inced = 1;
            --k;
        }
    }while(inced);
}
void prepareSolution(const IntPairVec& nfac,vector<i64>& factors, vector<vector<int>>& vres)
{
    factors.clear();
    vres.clear();
    for(unsigned int i = 0; i < nfac.size(); ++i){
        int prime = nfac[i].first;
        int pow = nfac[i].second;
        int val = power(prime, pow);
        factors.push_back(val);
        vres.push_back(getRealSolutions(prime, pow, 1));
    }
}
void prepareInput(const vector<int>& vIndex, const vector<i64>& vfac, const vector<vector<int>>& vvres, vector<i64>& vrem)
{
    assert(vIndex.size() == vfac.size());

    vrem.clear();
    vrem.resize(vfac.size());

    for(unsigned int i = 0; i < vfac.size(); ++i){
        vrem[i] = vvres[i][vIndex[i]];
    }
}
i64 search_x2_mod_n1(int n, const IntPairVec& nfac)
{
    if(nfac.size()==1 && nfac[0].second == 1)
        return 1LL;
    vector<int> vIndex;
    vIndex.resize(nfac.size(), 0);
    assert(nfac.size()>= 1);
    int nTerm = 2;
    if(nfac[0].first == 2){
        if(nfac[0].second >= 3)
            nTerm = 4;
        else if(nfac[0].second == 2)
            nTerm = 2;
        else if(nfac[0].second == 1)
            nTerm = 1;
    }

    //prepare solution
    vector<i64> vfac;
    vector<vector<int>> vvres;
    prepareSolution(nfac, vfac, vvres);
    i64 nmax = 1;
    while(vIndex[0] < nTerm){
        //prepare input
        vector<i64> vrem;
        prepareInput(vIndex, vfac, vvres, vrem);
        //chinese remainer theorem
        i64 nx =  chinese_remainder_theorem2(vfac, vrem);
        assert(nx > 0 && nx < n);
        assert(nx*nx % n == 1);
        if(nx > nmax && nx < n - 1) nmax = nx;
        //check if termination needed
        // remainder determined by vIndex
        getNextConfig(vIndex);
    }
    assert(nmax * nmax % n == 1);
    return nmax;
}


int main()
{
    int nmax = 20000000;
    //nmax = 200000;
    one.push_back(1);
    vector<int> vprimes, ftable;
    primeWithin(vprimes, nmax);
    vSolutions.resize(vprimes.size());
    //set up a simple prime index vector
    vpIndex.resize(nmax+1, 0);
    int count = 0;
    for(unsigned int i = 0; i < vprimes.size(); ++i){
        int px = vprimes[i];
        vpIndex[px] = count++;
    }

    //now need a factor table
    factor_table_min(nmax, ftable);
    //test
    vSolutions[0].resize(3);
    vSolutions[0][1] = 1;
    vSolutions[0][2] = 1;
    vSolutions[0][3] = 3;

    i64 sum = 0;
    for(int i =3; i<=nmax; ++i){
        IntPairVec ifac;
        factor_using_table(i, ifac, ftable);
        i64 val = search_x2_mod_n1(i, ifac);
        //assert(val == get_max_square_1(i, ifac));
        sum += val;
        if(i % 100000 == 0)
            printf("%f %lld\n", i/(double)nmax, val);
    }
    printf("\n%lld\n", sum);
}
