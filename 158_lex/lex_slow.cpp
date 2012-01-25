#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
//ntotal is the total number of alphabets that may be used
//nvalue is the value of alphabet that is used that sastisfy nx<nx+1 condition
//nused is the number of alphabets that are used
//nless is the number of values in first part
// a_1>a_2>...> a_{nless} < a_{nless+1} >a_{nless+2}>...>a_{ntotal}
i64 alphabet(int ntotal, int nvalue, int nless, int nused, int ncurr, const vector<int>& vflag, int ng){
    if(ncurr + nless - nused > 26) return 0;
    if(ng < nvalue) return 0;
        i64 sum = 0;
    int ng1 = ng;
    if(nused == nless){
        int nhigh_index = 0;
        //first find the largest unused value index, if largest value is less than nvalue
        // return 0, otherwise, count the total number of combinations
        for(int i= 25; i >=0; --i)
            if(vflag[i] == 0){
                nhigh_index = i;
                break;
            }
            if(nhigh_index+1 < nvalue)
                return 0;
            while(nhigh_index+1 > nvalue){
                sum += combination((i64)(nhigh_index-nless), (i64)(ntotal - nless-1));
                int j=0;
                for(j= nhigh_index-1; j >=0; --j)
                    if(vflag[j] == 0){
                        nhigh_index = j;
                        break;
                    }
                if( j== -1) break;
            }
        return sum;
    }
    for(int nx = ncurr + 1; nx <= 26; ++nx){
        vector<int> vf1(vflag);
        vf1[nx-1] = 1;
        if(ng == nx){
            int j = 0;
            for(j = ng - 2; j >= 0; --j){
                if(vf1[j] == 0){
                    ng1 = j+1;
                    break;
                }
            }
            assert(j>= 0);
        }
        sum += alphabet(ntotal, nvalue, nless, nused+1, nx, vf1, ng1);
    }
    return sum;
}
i64 search_n1(int ntotal){//
    //nvalue is the position where nvalue < next value in array happens; 
    //this only happens once
    vector<int> vflag;
    i64 nsum = 0;
    for(int nvalue = 1; nvalue <=25; ++nvalue){
        vflag.clear();
        vflag.resize(26, 0);//1 means selected
        vflag[nvalue-1]=1;
        for(int nless=1; nless <= ntotal-1; ++nless){
            nsum += alphabet(ntotal, nvalue, nless, 1, nvalue, vflag, 26); 
        }
    }
    return nsum;
}
int main(){
    for(int ns= 26; ns <= 26; ++ns){
        i64 n1 = search_n1(ns);
        printf("ns=%d count=%lld\n", ns, n1);
    }
}
