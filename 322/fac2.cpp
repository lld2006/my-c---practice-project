//it is easy to see that the number that are not divisible by 10 are far less than 
//the numbers that are divisible by 10.
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
using namespace std;

//the only one that is not divisible by 2 and 5 is 1e18
//this is considered by return value. so check_2 and
//check_5 are independent.

//non divisible 1 : otherwise divisble
i64 single_num_modp(i64 num, i64 den, i64 prime)
{
   assert(num >= 0 && den >= 0);
   assert(prime > 1);
   if(num < den) return 0;
   if(num == den) return 1;
   if(num <= prime)
       return combination(num, den)%prime;
   i64 prod=1;
   int nres = num % prime; 
   int dres = den % prime;
   if(nres < dres) 
       return 0;
   else{
       prod = combination(nres, dres)%prime;
       i64 n1 = num / prime;
       i64 d1 = den / prime;
       return (prod * single_num_modp(n1, d1, prime))%prime;
   }
}
//find how many binomial coefficient are not divisible by p
i64 check_p(i64 nmin, i64 nmax, i64 base, i64 prime)
{
    if(nmin > nmax) return 0;
    if(base == 1) return (nmax - nmin+1);
    //if(nmin == nmax ) return 1;
    //assert(nmax == base);
    i64 total = 0;
    i64 low = nmin % prime == 0? nmin:(nmin/prime+1)*prime;
    i64 high = nmax % prime == prime-1? nmax:(nmax/prime)*prime-1;
    assert(high <= base);
    //each period is from 0 to prime - 1;
    i64 nb = low-1<nmax? low-1:nmax;
    for(i64 nx = nmin; nx <=nb;++nx)
        total += single_num_modp(base, nx, prime);
    
    if(nmin <= high+1){
        for(i64 nx = high+1; nx<=nmax; ++nx)
            total += single_num_modp(base, nx, prime);
    }
    //now we have whole piece that are easy to solve
    int bres = base % prime;
    assert(bres >= 0);
    
    total += (bres + 1) * check_p(low/prime,(high+1)/prime-1,base/prime, prime);
    return total;
}
i64 check(i64 pmin, i64 pmax)
{
    i64 nmin = power(10LL, pmin)-10;
    i64 nmax = power(10LL, pmax);
    i64 n2 = power(2LL, pmax);
    i64 n5 = power(5LL, pmax);
    i64 low = 1;
    i64 r2 = check_p(low, nmax/n2, n5, 2);
    low = (nmin%n5)==0?nmin/n5:nmin/n5+1;
    i64 r5 = check_p(low, nmax/n5, n2, 5);
    printf("%lld %lld\n", r2, r5);
    return (nmax-nmin+1)-(r2+r5-1);//this may need some modification, since this is not what is asked for
}
//this is a simple one, may be not right
int find_next_same_element(int element, int pcurr, vector<int>& vn)
{
    for(int p = pcurr+1; p < static_cast<int>(vn.size()); ++p){
        if(vn[p] == element)
            return p;
    }
    return -1;
}
int find_period(vector<int>& vn)
{
    int n0 = vn[0];
    int curr = 0;
    int next = 0;
    int period = vn.size();
    bool notFound = true;
    while(notFound){
       next = find_next_same_element(n0, curr, vn); 
       if(next == -1)return -1;
       notFound = false;
       for(int start = next; start < static_cast<int>(vn.size()); start += next){
           if(vn[start] != n0){
               printf("test period failed for %d at %d\n", next, start);
               notFound = true;
               break;
           } 
       }
       curr = next;
    }
    return next ;
}
int main()
{
    int pmin = 7;
    int pmax = 9;
    i64 low = power(10LL, (i64)pmin)-10;
    i64 high = power(10LL,(i64)pmax);
    int cnt = 0;
    vector<int> v2;
    vector<int> v5;
    for(i64 i = low; i<= low+80000000; ++i){
        ++cnt;
        int result = single_num_modp(i, low, 5);
        v2.push_back(result);
        if(result)
            printf("%lld %d %d\n", i, result, cnt);
        //for(unsigned int j =; j <i; ++j){
            //int p1 = single_num_modp(i,j,2);
            //int p2 = single_num_modp(i*10,j*10, 2);
            //int p3 = single_num_modp(i,j,5);
            //int p4 = single_num_modp(i*10,j*10,5);
            //if(p1 !=p2 || p3 != p4)
            //    printf("%d %d %d %d %d %d\n", i,j, p1,p2,p3,p4);
        //}
    }
    int p1 = find_period(v2);
    printf("array period of v2 is %d\n", p1);
    exit(1);
    i64 value = 9999990;
    i64 nmax = 1000000000LL;
    for(unsigned int i = value; i <nmax; ++i){
        int n2 = single_num_modp(i, value, 2);
        int n5 = single_num_modp(i, value, 5);
        if(n2||n5){
            ++cnt;
            printf("%d %d\n", i, 2*n5+n2);
        }
    }
    printf("%lld\n", nmax-value-cnt);
    exit(1);
    i64 result = check(pmin, pmax);
    printf("%lld\n", result);
}
