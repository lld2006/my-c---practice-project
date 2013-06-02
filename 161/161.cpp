//start config to final config
#include <tr1/unordered_map>
#include <vector>
#include <bitset>
#include <cassert>
#include <cstdio>
#include "../lib/typedef.h"
using namespace std;
typedef std::tr1::unordered_map<int, int> hashmap;
typedef std::tr1::unordered_map<int, i64> hashmap64;
typedef std::tr1::unordered_map<int, hashmap> hashhashmap;

vector<IntPair>     trios;
hashhashmap         trimap;

int nx=9, ny=12;
//cindex is the column index.
//
void convert(int nstart, bitset<27> gbit, int cindex)//gbit must be set before convert
{
    while(gbit.test(cindex) && cindex < nx){//remove unnecessary col check
        ++cindex;
    }
    if(cindex==nx){
        for(int i = 0; i < nx; ++i){
            if(!gbit.test(i))
                return;
        }
        gbit >>= nx;
        int nend = gbit.to_ulong();
        assert(nend < (1<<18));
        hashhashmap::iterator hhiter;
        hashmap::iterator     hiter;
        hhiter = trimap.find(nstart);
        if(hhiter == trimap.end()){
            trimap.insert(make_pair(nstart, hashmap()));
            //the following 3 lines are missed forgot to insert the first value
            hhiter = trimap.find(nstart);
            assert(hhiter != trimap.end());
            hashmap& hmap(hhiter->second);
            assert(hmap.size()==0);
            //printf("find new cfg %d\n", nend);
            hmap.insert(IntPair(nend,1));
        }else{
            hashmap& hmap(hhiter->second);
            hiter = hmap.find(nend);
            if(hiter==hmap.end()){
                //printf("find new cfg %d\n", nend);
                hmap.insert(IntPair(nend, 1));
            }else{
                ++hiter->second;
                //printf("update cfg %d %d\n", nend, hiter->second);
            }
        }
        return;
    }
    int col = cindex;
    for(int type = 0; type<6; ++type){
        bitset<27> gnew(gbit);
        gnew.set(cindex);//lesson forgot to set the base position
        int rowshift = trios[2*type].first;
        int colshift = trios[2*type].second;
        if(col+colshift>=nx ||col+colshift <0) continue;//exceeding boundary
        if(gbit.test(cindex+rowshift*nx+colshift)) continue;//col occupied
        gnew.set(cindex+rowshift*nx+colshift);

        rowshift = trios[2*type+1].first;
        colshift = trios[2*type+1].second;
        if(col+colshift>=nx ||col+colshift <0) continue;//exceeding boundary
        if(gbit.test(cindex+rowshift*nx+colshift)) continue;//col occupied
        gnew.set(cindex+rowshift*nx+colshift);
        convert(nstart, gnew, cindex+1);
    }
    return;
}
void phmap(hashmap& hmap)
{
    hashmap::iterator iter;
    for(iter = hmap.begin(); iter!=hmap.end(); ++iter){
        if(iter->first < 10)
        printf("        ||%d %d\n", iter->first, iter->second);
    }
}
void phhmap(hashhashmap& hhmap)
{
    hashhashmap::iterator hhiter;
    for(hhiter = hhmap.begin(); hhiter!=hhmap.end(); ++hhiter){
        printf("hashhashmap key %d\n", hhiter->first);
        phmap(hhiter->second);
    }
        
}
//it would be nice to use hashmap than map
int main()
{
    trios.resize(12);
    trios[0]=IntPair(0,1);
    trios[1]=IntPair(0,2);
    trios[2]=IntPair(1,0);
    trios[3]=IntPair(2,0);
    trios[4]=IntPair(0,1);
    trios[5]=IntPair(1,0);
    trios[6]=IntPair(0,1);
    trios[7]=IntPair(1,1);
    trios[8]=IntPair(1,-1);
    trios[9]=IntPair(1,0);
    trios[10]=IntPair(1,0);
    trios[11]=IntPair(1,1);
    hashmap64 candidates, newcand;
    hashhashmap::iterator hhiter;
    hashmap::iterator     hiter2;
    hashmap64::iterator   hiter, hiter3;
    candidates.insert(pair<int, i64>(0, 1));
    for(int row = 0; row < ny; ++row){
           newcand.clear(); 
           for(hiter=candidates.begin(); hiter != candidates.end(); ++hiter){
                int value = hiter->first;
                i64 mult = hiter->second;
                hhiter = trimap.find(value);
                if(hhiter == trimap.end()){//non-exist 
                    bitset<27> gbit(value);
                    convert(value, gbit, 0);
                    hhiter = trimap.find(value);
                    //assert(hhiter != trimap.end());
                }
                if(hhiter != trimap.end()){
                    hashmap& hc = hhiter->second;
                    for(hiter2 = hc.begin(); hiter2 !=hc.end(); ++hiter2){
                        int value = hiter2->first; 
                        i64 cnt = hiter2->second*mult;
                        hiter3 = newcand.find(value);
                        if(hiter3 == newcand.end())
                            newcand.insert(pair<int, i64>(value, cnt));
                        else
                            hiter3->second += cnt;
                    }
                }
           }
           swap(candidates, newcand);
    }
    printf("%lld\n", candidates[0]);
}
