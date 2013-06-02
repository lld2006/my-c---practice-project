//new method, consider normal triangle only, the upside-down shaped 
//triangle are only considered as multipliers
#include <vector>
#include "../lib/typedef.h"
#include <cstdio>
using namespace std;
//lesson used wrong place to reset the flag counter
//this is an version that simplified the code, but performance 
//is not good
void get_trinary_vector(int num, int level, vector<int>& vcache)
{
    vcache.clear();
    vcache.resize(level, 0);
    int nt = 0;
    while(num){
        int res = num % 3;
        vcache[nt++] = res;
        num /= 3;
    }
}
int main()
{
    vector<i64> vtri, vNext;
    vtri.resize(3, 1);
    int nLevel = 1;
    int nNext = 3;
    for(int level = 1; level<=2; ++level){
        nLevel *= 3;
        nNext *= 3;
        vNext.clear();
        vNext.resize(nNext, 0);
        vector<int> vcache;
        vector<int> flag;
        for(int n2 = 0; n2< nNext; ++n2){
            get_trinary_vector(n2, level+1, vcache);
            for(int n1 = 0; n1 < nLevel; ++n1){
                int nt = n1;
                i64 prod = 1;
                int opt=1, res;
                for(int di = 0; di < level; ++di){
                    flag.clear();
                    flag.resize(3,0);
                    flag[vcache[di]] = 1;
                    flag[vcache[di+1]] = 1;
                    res = nt % 3;
                    flag[res] = 1;
                    opt = 3 - flag[0] - flag[1]-flag[2];
                    if(opt == 0) break ;
                    prod *= opt;
                    nt/=3;
                }
                if(opt){
                    printf("level %d %d %d\n",level, n1, n2 );
                    vNext[n2] += prod * vtri[n1];
                }

            }
        }
        vNext.swap(vtri);
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < vtri.size(); ++i){
        //printf("%d %lld\n", i, vtri[i]);
        sum += vtri[i];
    }
    printf("%lld\n", sum);
}
