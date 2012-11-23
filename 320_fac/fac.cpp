#include <cstdio>
#include <vector>
#include <cstdlib>
#include "../lib/tools.h"
i64 mult = 1234567890LL;
vector<int> primes;

int find_largest_prime(int num)
{
    int low = 0;
    int high = primes.size()-1;
    int mid;
    if(num > primes[high])
        return high;
    while(low < high){
        mid = (low + high)/2;
        if(primes[mid] == num)
            return mid;
        else if(primes[mid] > num)
            high = mid - 1;
        else
            low = mid + 1;
    }
    if(primes[low] < num)
        return low;
    else{
        assert(primes[low-1] < num);
        return low - 1;
    }
}

i64 primepow(int num, int px)
{
    int tot = 0;
    while(num > px){
        num /= px;
        tot += num;
    }
    return tot;
}
i64 find_min_facnum(int num)
{
    int maxpidx = find_largest_prime(num);
    vector<i64> vpow;
    vpow.resize(maxpidx +1, 0);
    for(unsigned int i =0; i < vpow.size(); ++i){
        vpow[i] = primepow(num, vpow[i])*mult;
    }
    //TODO
    return 0;    
}

int main()
{
    
    int limit = 1000000;
    int ma = limit;
    int su = 0;
    while(ma > 1){
        ma /= 2;
        su += ma;
    }
    printf("%d\n", su);
    exit(1);
    primeWithin(primes, limit);
    i64 sum = 0;
    for(int i = 10; i<=limit; ++i){
        i64 single = find_min_facnum(i);
        sum += single;
    }
}
