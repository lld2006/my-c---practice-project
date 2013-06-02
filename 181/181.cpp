#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int target = 2500;
int nbm = 40;
int nwm = 60;
vector<vector<i64>> vn;
void  update_partition(int num)
{
    int nw = num/41;
    int nb = num%41;
    int restart = 0;
    if(num > 40) restart = 40;
    for(int nres = restart; nres <= num; ++nres){
        if(vn[num][nres] == 0) continue;
        int rw =  nres/41;
        int rb =  nres%41;
        //consider the situation next partition has the same white
        if(nw + rw <= nwm){
            for(int mb = rb+1; mb<=nbm-nb; ++mb){
                for(int di= 1; di; ++di){ //di new  partition
                    int tb = nb + di * mb;
                    int tw = nw + di * rw;
                    if(tw > nwm || tb > nbm) break;
                    int np = rw*41+mb;
                    int tn = num + di*np;
                    vn[tn][np] += vn[num][nres];
                }
            }
        }
        //now consider next partition has more white
        for(int mw = rw+1; mw <= nwm-nw; ++mw){
            for(int di = 1; di; ++di){ //di new partition
                int tw = nw + di*mw;
                if( tw > nwm) break;
                for(int mb=0; mb<=nbm-nb; ++mb){
                    int tb = nb + di * mb;
                    if(tb > nbm) break;
                    int np = mw*41+mb;
                    int tn = num + di*np;
                    vn[tn][np] += vn[num][nres];
                }
            } 
        }
    }
    return;
}
int main()
{
    //the first dimension is number of balls  and the second dimension is 
    //restrictions for each partition max
    vn.resize(target+1);
    for(unsigned int i = 0; i<vn.size(); ++i){
        vn[i].resize(i+1, 0);
    }
    vn[0][0]= 1;
    //now build up the partition
    for( int i = 0; i<target; ++i){
        //if(i% 100 ==0)
        //    printf("%d\n", i);
        update_partition(i);
    }
    i64 sum = 0;
    for(unsigned int i  = 40; i<=2500; ++i){
        sum += vn[2500][i];
    }
    printf("%lld\n", sum);
}
