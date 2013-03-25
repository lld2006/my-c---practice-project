#include "../lib/tools.h"
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

//convention for same vector, 
//first number, the identical digit
//second number, number of repeat
//third, third + second number - 1, the position of same digit;
//if the identical digit is greater than 2, no use;
// position is n, n-1,..., 1,0
// possibility two identical number!!!
void samedigit(int num, vector<int>& same){
    same.clear();
    vector<int> digvec;
    digvec.resize(10, 0);
    int nx = num;
    while(nx){
        int res = nx %10;
        ++digvec[res];
        nx /= 10;
    }
    for(int i = 0; i < 9 ; ++i){
        if(digvec[i] <= 1)continue;
        same.push_back(i);  // identical number 0--9
        same.push_back(digvec[i]); //number of repeat
        nx = num;
        int pos = 0;
        while(nx){
            int res = nx %10;
            if( i == res )
                same.push_back(pos);
            ++pos;
            nx /= 10;
        }
    }
}
int check8prime(int num, int sd, vector<int>& pos, vector<int>& primes){
    int ret = 1;
    vector<int> comb;
    for(unsigned int ci = 2; ci <= pos.size();++ci){
        comb.resize(ci);
        for(unsigned int j =0 ; j < ci; ++j)
            comb[j] = j;
        do{
            int temp = 1;
            int nx = num;
            int sx = 0;
            for(unsigned int j =0; j <ci; ++j)
                sx += power(10, pos[comb[j]]);
            nx -= sx*sd;
            for(int j = sd+1; j <=9; ++j){
                int nt = nx + sx * j;
                if(binary_search(primes.begin(), primes.end(), nt))
                    ++temp;
            }
            if(temp > ret) ret = temp;
        }while (next_combination(comb, pos.size(), ci));
    }
    return ret;
}

int main(){
    vector<int> primes;
    vector<int> same;
    int limit = 1000000;
    primeWithin(primes, limit);
    for(unsigned int i = 0 ; i < primes.size(); ++i){
        if( primes[i] < 56000)continue;
        samedigit(primes[i], same);
        if(same.empty())continue;
        unsigned int shift = 0;
        while(shift < same.size()){
            int sd = same[shift++];
            int repeat = same[shift++];
            if(sd > 2) 
                shift += repeat;
            else{
                vector<int> pos(same.begin()+shift, same.begin()+shift+repeat);
                int mx = check8prime(primes[i], sd, pos, primes);
                if(mx >= 7){
                    printf("%d, %d\n", primes[i], mx);
                    if(mx >= 8)
                        exit(0);
                }
                shift += repeat;
            }
                
        }

    }
}
