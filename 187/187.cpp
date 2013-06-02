#include "../lib/tools.h"
#include <cstdio>
int binary_el(int num, vector<int>& vec){
    if(vec.empty()) return -1;
    unsigned int head = 0;
    unsigned int tail = vec.size()-1;
    while (head < tail ){
        int mid = (head + tail)/2;
        if(vec[mid] == num) 
            return mid;
        else if(vec[mid] < num){
            head = mid + 1;
        }else{//mid > num
            tail = mid - 1;
        }
    }
    if(vec[head] > num)
        return head-1;
    else
        return head;
}
int main()
{
    int limit = 1000000000;
    vector<int> primes;
    primeWithin(primes, limit/2);
    printf("number probable %zu\n",primes.size());
    int nroot = sqrt(limit)+1;
    int cnt = 0;
    for( int i = 0; primes[i]<nroot; ++i){
        int last = binary_el(limit/primes[i], primes);
        assert(last >= 0);
        assert(last-i+1>=0);
        cnt += last - i+1;
        
    }
    printf("%d\n", cnt);
}
