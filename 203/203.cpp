#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <set>
#include <cstdlib>
#include <cstdio>
#include <numeric>
using namespace std;
//removed all factor code since only a couple of 
//numbers neeed to be divided to know if it is 
//square free
int main(){
    int limit = 50;
    int count = 1;
    vector<i64> triangle;
    set<i64> numberset;
    triangle.resize(limit/2+1, 0);
    triangle[0] = 1;
    vector<int> primes;
    primeWithin(primes, 50); 
    for(int i = 2; i<=limit; ++i){
        //first generate the value on row i
        for(int j = i/2; j >= 0; --j){
            int fir = j;
            int sec = j-1;
            if( fir > (i-1)/2) {
                assert(j >= 1);
                triangle[j] = triangle[j-1] * 2;
            }else if ( sec < 0){
                continue; //keep the value 1
            }else{
                triangle[j]= triangle[fir]+triangle[sec];
            }
        }
        //check square item, insert square free item into set
        for(int j=1; j<=i/2;++j){
            if((triangle[j]%4) && (triangle[j]%9) && (triangle[j]%25) && (triangle[j]%49)){
                ++count;
                numberset.insert(triangle[j]);
            }
        }
    }
    i64 gx = accumulate(numberset.begin(), numberset.end(), 1LL);
    printf("%lld %d %zu\n", gx, count, numberset.size());

}
