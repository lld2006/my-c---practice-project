#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cassert>
#include <cstdio>
#include <algorithm>

int limit = 20000;

bool isPrimeJoint(int p1, int p2, vector<int>& primes){
    if(p1%3==1 && p2%3==2) return false;
    if(p1%3==2 && p2%3==1) return false;
    int prod = 1;
    while(prod < p1){
        prod *=10;
        p2 *= 10;
    }
    int px = p1 + p2;
    return isPrime(px, primes);
}

int main(){
    vector<int> primes;
    int upper = 10000;
    primeWithin(primes, limit);//2 3 5 7
    primes[2] = 3;// ignore 2 5 which could not be primejointer;
    int cnt = 0;
    for(unsigned int i = 2; i< primes.size(); ++i){
        if(primes[i] < upper) 
            ++cnt;
        else
            break;
    }
    //candidates are picked for each number
    vector<vector<int> > plist (cnt, IntVec() );
    for(int i =2; i < cnt +2; ++i){
        int px = primes[i];
        for(int j= i+1; j < cnt +2; ++j){
            if(isPrimeJoint(px, primes[j], primes) && 
               isPrimeJoint(primes[j], px, primes))
                plist[i-2].push_back(primes[j]);
        }
    }
    vector<int> v12, v123, v1234;
    for(unsigned int i1 = 0; i1 < plist.size(); ++i1){ 
        //start of all the list
        int p1 = primes[i1+2]; // first prime owner
        for(unsigned int i2 =0; i2 < plist[i1].size(); ++i2){
            int p2=plist[i1][i2];
            int pi2 = binary_find(p2, primes);
            assert( pi2 > 0);
            v12.clear();
            set_intersection(plist[i1].begin(), plist[i1].end(),
                             plist[pi2-2].begin(), plist[pi2-2].end(),
                             back_inserter(v12));
            if(v12.size() < 3) continue;
            for(unsigned int i3 =0 ; i3 < v12.size(); ++i3){
                int p3 = v12[i3];
                int pi3 = binary_find(p3, primes);
                assert(pi3 >0);
                v123.clear();
                set_intersection(plist[pi3-2].begin(), plist[pi3-2].end(),
                                 v12.begin(), v12.end(),
                                 back_inserter(v123));
                if(v123.size() < 2 ) continue;
                for(unsigned int i4 = 0; i4 < v123.size(); ++i4){
                    int p4 = v123[i4];
                    int pi4 = binary_find(p4, primes);
                    assert(pi4 > 0);
                    v1234.clear();
                    set_intersection(plist[pi4-2].begin(), plist[pi4-2].end(),
                                     v123.begin(), v123.end(),
                                     back_inserter(v1234));
                    if( v1234.empty()) 
                        continue;
                    else{
                        int p5 = v1234.front();
                        printf("%d %d %d %d %d %d\n",p1, p2, p3, p4, p5, p1+p2+p3+p4+p5);
                    }
                }
            }
        }
    }
}
