#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cassert>
#include <cstdio>
#include <algorithm>
//quick and dirty get neighbors
//lesson missed one special corner, for each ring the number is 6*nring, 6 more 
//than last ring, for each of these last value*%nring = nring -1, we need to handle 
//them specially. code currently is incorrect. method is fast though.
int diff(i64 num, i64 n2){
    return num > n2? num-n2:n2-num;
}
void getNeighbors(i64 num, vector<int>& nbvec){
    nbvec.clear();
    static i64 nthring = 1;
    if(3LL*nthring*(nthring+1)+2 <= num)
        ++nthring;
    i64 first = 3LL*nthring*(nthring-1)+2;
    assert(num >= first);
    i64 outer0 = 3LL*nthring*(nthring+1)+2;
    i64 inner0 = 1; //0th first;
    if(nthring >= 2) 
        inner0 = 3LL*(nthring-1)*(nthring-2)+2;

    int kth = (num -first)/nthring;
    assert(kth >= 0 && kth <= 5);

    if((num - first)%nthring==0){//one inner in0 two same ring, 3 out; out0 out0-1 out0+1
        //inner ring
        i64 value = inner0 + kth * (nthring-1);
        if((num - value) & 1 )
            nbvec.push_back(num - value); 

        //neighbor in the same ring, special num = 7
        if(num == first || num == outer0 - 1)
            nbvec.push_back(nthring*6-1);

        // number in the outer ring
        value = nthring * 6 + kth;
        if(value & 1)
            nbvec.push_back(value);
        else{
            nbvec.push_back(value +1);
            if(num != first)
                nbvec.push_back(value - 1);
            else
                nbvec.push_back(nthring*12+5);
        }
    }else{//not divisible, ith, inner i, i-1, outer i i+1, same ring num-1, num+1
        int res = (num - first) % nthring; 
        i64 value = inner0 + kth*(nthring-1)+res-1;
        //inner neighbour
        if((num - value) & 1)
            nbvec.push_back(num - value);
        else
            nbvec.push_back(num-value+1);

        //same ring
        if(num == outer0 - 1)
            nbvec.push_back(nthring*6-1);
        //outer ring
        //value = outer0 + kth*(nthring+1)+res;
        value = nthring * 6 + kth;
        if(value & 1)
            nbvec.push_back(value);
        else
            nbvec.push_back(value+1);
    }
}
int main(){
    int limit = 1000000;
    int np3 = 0;
    vector<int> primes;
    primeWithin(primes, limit);
    for(int i = 2; i ; ++i){
        i64 number = 3LL * i*(i-1)+2;
        vector<int> neighbors;
        getNeighbors(number, neighbors);
        if(neighbors.size() >= 3) {
            int count = 0;
            int max_delta = 0;
            for(unsigned int j = 0; j<neighbors.size(); ++j){
                if(neighbors[j] > max_delta)
                    max_delta = neighbors[j];
                if(binary_search(primes.begin(), primes.end(), neighbors[j] ))
                    ++count;
            }
            if(count == 3){
                ++np3;
                //if(np3 % 10 ==0)
                    printf("%lld %d %d\n", number, np3, max_delta);
            }
            if(np3 == 2000) break;
        }

        number = 3LL * i*(i+1)+1;
        getNeighbors(number, neighbors);
        if(neighbors.size() >= 3) {
            int count = 0;
            int max_delta = 0;
            for(unsigned int j = 0; j<neighbors.size(); ++j){
                if(neighbors[j] > max_delta)
                    max_delta = neighbors[j];
                if(binary_search(primes.begin(), primes.end(), neighbors[j] ))
                    ++count;
            }
            if(count == 3){
                ++np3;
                //if(np3 % 1 ==0)
                    printf("%lld %d %d\n", number, np3, max_delta);
            }
            if(np3 == 2000) break;
        }
    }
}
