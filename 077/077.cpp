#include "../lib/tools.h"
#include <cstdio>
vector<vector<int>> vn;
//find number in partions with primes no greater than primes[]pindex]
int find_partition_prime(int num, int pindex, vector<int>& primes)
{
    assert(num >= 0);
    //logic error, 0 and 1 are different
    if(num == 1) return 0; 
    if(num == 0) return 1; 

    while(primes[pindex]> num) --pindex;
    assert(primes[pindex] <= num);
    if(vn[num][pindex] >= 0)
        return vn[num][pindex];
    int q = num/primes[pindex];
    int total = 0;
    for( int j = 0; j <= q; ++j){
        total += find_partition_prime(num -j * primes[pindex], pindex-1, primes);
    }
    vn[num][pindex] = total;
    return total;
}
int main()
{
    int target = 1000;
    vector<int> primes;
    primeWithin(primes, target);
    vn.resize(target);
    for(unsigned int i = 0; i < vn.size(); ++i){
        vn[i].resize(i+1, -1);
    }
    
    int pindex = 0;
    for( int i = 1; i; ++i){
        if(i >= primes[pindex]){
            ++pindex;
        }
        int value = find_partition_prime(i, pindex-1, primes);
        if(value >= 5000){
            printf("%d %d\n", i, value);
            return 0;
        }
    }
}
