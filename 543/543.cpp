#include <cstdio>
#include "../lib/tools.h"
//for k ==1 it is the number of primes
//for k ==2, odd numbers need to check prime table to find twins 
//for even numbers and k>=2, f(4)=1 f(6)=2, ...f(2n)=n-1
//for odd number>=7 k>=3, f(7, 3)=1,f(9, 4)=2, f(11, 5)=3, f(n)=(n+1)/2
int np = 701408733;
vector<int> primes;
int getLargestPrimeIndex(int num)
{
    unsigned int head = 0;
    unsigned int tail = primes.size()-1;
    while (head < tail ){
        int mid = (head + tail)/2;
        if(primes[mid] == num) 
            return mid;
        else if(primes[mid] < num){
            head = mid + 1;
        }else{//mid > num
            tail = mid ;
        }
    }
    assert( head == tail);
    if(primes[head] >= num) 
        return head-1;
    else
        return head;
}
i64 primesumf(int nmax)
{
    i64 m = nmax/2-1;
    i64 total = 0;
    total += m*(m+1)/2;
    m = (nmax-5)/2;
    total += m*(m+1)/2;
    //odd 2
    int np = getLargestPrimeIndex(nmax) +1;
    total += 2*np-1 - (primes[np-1]+2>nmax);
    return total;
}
int main()
{
    i64 sum = 8;
    primeWithin(primes, np);
    i64 f, f1 = 3, f2=5;
    for(int i =6; i <=44; ++i){
        f = f1 + f2;
        i64 tp = primesumf(f);
        sum += tp;
        //printf("%d %lld %lld\n", i,f, tp);
        f1 = f2; f2 = f;
    }
    printf("%lld\n", sum);
}
