#include <map>
#include <set>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/primelist.h" 
#include <cstdio>
#include <cmath>
int main()
{
    int limit = 5000000;
//    int nsquare = 2;
    vector<int> numvec;
    vector<int> primes;
    IntPairVec ifac;
    map<int, int> facmap;
    primeWithin(primes, limit);
    for(int i =1; i<=32; ++i){
        for(int j = i*i+1; j<(i+1)*(i+1);j++)
            if(j <= 1000) numvec.push_back(j);
    }
    set<int> diop(numvec.begin(), numvec.end());
    for(int i = 2; i < limit;++i){
        facmap.clear();
        //for first number
        factor(i-1, ifac, primes);
        for(unsigned int j = 0; j< ifac.size(); ++j)
            facmap.insert(ifac[j]);
        //for second number
        factor(i+1, ifac, primes);
        for(unsigned int j = 0; j< ifac.size(); ++j){
            if(facmap.find(ifac[j].first) != facmap.end())
                facmap[ifac[j].first]+= ifac[j].second;
            else
                facmap.insert(ifac[j]);
        }
        int num = 1;
        int optnum = 1;
        for(map<int, int>::iterator iter=facmap.begin(); iter != facmap.end(); ++iter){
            if(iter->second %2 == 1){
                num *= iter->first;
                iter->second=(iter->second-1)/2;
            }else{
                iter->second /= 2;
            }
            if(num >  1000) break; //minimum value should be less(eq) than 1000
        }
            if(num <= 1000) {
                for(map<int,int>::iterator iter=facmap.begin(); iter!=facmap.end(); ++iter){
                    optnum *= power(iter->first, iter->second);
                }
                bool flag = true;
                int nlim = sqrt((double) optnum )+1;
                while(flag){
                    for(int m = 1; m <= nlim; ++m){
                        if( optnum % m == 0){
                            int tnum = num * m *m;
                            if(tnum <= 1000){
                                diop.erase(tnum);
                               printf("%d erased,%d, %u %d\n", tnum,i, diop.size(), m);
                            }else{
                                break;
                            }
                            if(optnum/m <= 1000){
                                tnum = num * (optnum/m)*(optnum/m);
                                if(tnum <= 1000)
                                    diop.erase(tnum);
                                printf("%d erased2,%d, %u %d\n", tnum,i, diop.size(), m);
                            }
                        }
                    }
                    flag = false;
                    if(diop.empty()) break;
                }
            }
    }
    for(set<int>::iterator iter = diop.begin(); iter != diop.end(); ++iter)
        printf("%d\n", *iter);
    printf("\n");
}
