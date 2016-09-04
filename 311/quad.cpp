#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
i64 limit = 10000/2;
i64 root = 100;
// 1. a^2 +b^2 = u 
//x^2+y^2 = 2u has at least two solutions, one is 
//greater than u they other is less than u
// 2. since the multiple of x y z w is still a solution,
// so gcd(a, b) = 1 is needed to remove duplicity, and u
// should have no 4p+3 factor
// 3. the example is x^2 + y^2=1105=5*13*17
//how to handle BD is the challenging part
vector<int> primes;
//cpos is the current pos in primes
//ncurr is the current product of powers
//pcurr is the current number (product of primes)
//np1 is how many p1 types of 
i64 find_quad(i64 pcurr,  i64 np1, int cpos, i64 ncurr)
{
    if(pcurr >  limit || cpos == static_cast<int>(primes.size())) //no need to multiply anything
        return 0;
    i64 total = 0;
    if(primes[cpos] % 4 == 1){ //4k+1 type
        i64 pc1 = pcurr;
        for(unsigned int i = 0; ;++i){
            if(i==0){
                //nothing new introduced
                total += find_quad(pc1, np1, cpos+1, ncurr);
            }else{
                if(pc1 <= limit && np1 >= 1){
                    i64 tp = ncurr * (i+1)/2;
                    printf("%lld %lld\n", 2*pc1, tp*(tp-1)/2);
                    total += (tp-1)*tp/2; 
                }
                i64 ntp = find_quad(pc1, np1+1, cpos+1, ncurr*(i+1));
                total += ntp;
            }
            pc1 *= primes[cpos];
            if(pc1 > limit)
                break;
        }
    }else{// 4k+3 type primes
        i64 np = static_cast<i64>(primes[cpos]) * primes[cpos];
        i64 pc1 = pcurr;
        for(unsigned int i = 0; ;++i){
                total += find_quad(pc1, np1, cpos+1, ncurr);
                pc1 *= np;
                if(pc1 > limit)
                    break;
        }
    }
    return total;

}

bool isTriangle(int a, int b, int c)
{
    return (a+b >c) && (b<c+a) &&(a< b+c);;
}

bool checkValidity(int a, int b, int x, int y, int z, int w)
{
    return isTriangle(a,b,x) && isTriangle(a,b,y) && isTriangle(a, b,z) && isTriangle(a,b,w);
}

int main()
{
    //for real problem it is more important to calculate a^2 + d ^ 2 
    //and b^2 + c^2, but for brute force, it is only need the sum of the 
    //four, which is is 4*(x^2 + y^2)
    vector<vector<int>> vvx; // a <= b
    vector<vector<int>> vvy;
    int n = 10000;
    vvx.resize(2*n+1);
    vvy.resize(2*n+1);
    int nr = sqrt(n);
    assert(nr == 100);
    for(int x = 1; x <= nr; ++x){ //AO
        for(int y = x; y <= nr; ++y){ //BO
            int sum = x*x + y*y;
            //if(sum * 4 > n) continue;
            vvx[sum].push_back(x);
            vvy[sum].push_back(y);
        }
    }
    //for(int i = 2; i<= nr; ++i){
    //    int val = i * i;
    //    for(unsigned int j = val; j < vvx.size(); j+=val ){
    //        vvx[j].clear();
    //        vvy[j].clear();
    //    }
    //}
    i64 sum = 0;
    for( int i = 1; i <= n; ++i){
        if(vvx[i].empty()) continue;
        if(vvx[2*i].size() < 2) continue;
        for(unsigned int k = 0; k < vvx[i].size(); ++k){
            int sq = (vvx[i][k]*vvx[i][k]+vvy[i][k]*vvy[i][k]);
            //assert(sq <= 2500);
            if(sq > 2500) continue;
            for(unsigned int j = 0; j< vvx[2*i].size(); ++j){
                if(vvx[2*i][j] == vvy[2*i][j]) continue;
                for(unsigned int l = j+1; l< vvx[2*i].size(); ++l){
                    if(vvx[2*i][l] == vvy[2*i][l]) continue;
                     if(checkValidity(vvx[i][k], vvy[i][k], vvx[2*i][j], vvy[2*i][j], vvx[2*i][l], vvy[2*i][l])){
                        //sum += sqrt(2500/sq);
                        ++sum;
                        printf("%d %d %d %d %d %d %d\n", vvx[i][k], vvy[i][k], vvx[2*i][j], vvy[2*i][j], vvx[2*i][l], vvy[2*i][l], sq);
                     }
                }
            }
        }
    }
    printf("%lld\n", sum);
    exit(1);
    root = sqrt(limit);
    primeWithin(primes, root);
    //vector<int> flags;
    //flags.resize(primes.size(), 0);
    //for(unsigned int i = 0; i < primes.size(); ++i){
    //    if(primes[i] % 4 == 1){
    //        flags[i] = 1;
    //    }
    //}
    int n2 = log(static_cast<double>(limit)/65)/log(2.0);
    i64 p2 = 2;
    sum = 0;
    for( int i2 = 1; i2 <= n2; ++i2, p2 *= 2)
        sum += find_quad(p2, 0, 1, 1 );
    printf("%lld\n", sum); 
}
