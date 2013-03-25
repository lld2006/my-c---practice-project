#include <cstdio>
#include "../lib/typedef.h"
#include <unordered_map>
using namespace std;
unordered_map<i64, int> fmap;
vector<int> vf;
int nmax = 1000000;

int iterate(i64 num){
    if(num == 1) return 0;
    if(num <=nmax && vf[num] > 0)
        return vf[num];
    else if(num > nmax ){
        auto iter = fmap.find(num);
        if(iter  != fmap.end())
            return iter->second;
    }
    int value = 0;
    if(num & 1 )
        value = iterate(num*3+1)+1;
    if((num & 1) == 0)
        value = iterate(num/2)+1;
    if(num <= nmax) 
        vf[num] = value;
    else 
        fmap.insert(make_pair(num, value));
    return value;
}
int main()
{
    vf.resize(nmax+1, 0);
    int rmax = 0;
    int rn = 1;
    int start = nmax/2;
    for(unsigned int i = start; i< vf.size(); ++i){
        int nf = iterate(i);
        if(rmax < nf ){
            rmax = nf;
            rn = i;
        }
    }
    printf("hashmap size is %zu\n", fmap.size());
    printf("%d %d\n", rn, rmax);
}
