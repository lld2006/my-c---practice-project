//my algorithm is the following, implement a function to find out 
//the number of partitions with nb blacks and nw whites with at least 
//nwmin and nbmin in each of the partition. for 60 black and 40 whites, 
//we can assigne 41 for each black and 1 for white. then nw nb and nmin
//can formulate a number for a hashmap. using dynamic programmings to speed
//up the searhcing process.
#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;
int debug = 0;
int main()
{
    vector<int> parts;
    parts.reserve(200);
    int tot = 2500;
    int n1 = 0;
    int nb = 41, nw=1;
    i64 cnt=0;
    parts.push_back(tot);
    assert(tot > 0);
    while(true){
        assert(n1<=40);
        ++cnt;
        int psize = parts.size();
        //if(parts[psize-1-n1]==1){
        if(parts.size()==100&& n1==40 && parts[psize-1-n1]==41 && parts[0]==41){//for all possible partitions
            break;
        }
        if(parts[psize-1-n1]==2){
            if(n1<39){
                --parts[psize-1-n1];
                n1+=2;
                parts.push_back(1);
            }else if(n1==39){

            }
        }else{
            if(psize <n1+1)break;
            int last = (--parts[psize-1-n1]);
            assert(last > 0);
            int nlast = (n1+1)/last;
            int res = (n1+1)- nlast*last;
            for(int j = 0; j < nlast; ++j)
                parts[psize-n1+j] = last;
            parts.resize(psize-n1+nlast);
            if(res > 0)
                parts.push_back(res);
            if(res ==0 || res>1)
                n1= 0;
            else
                n1 = 1;
        }
        if(debug){
            for(unsigned int i = 0; i < parts.size(); ++i){
                printf("%d  ", parts[i]);
            }
            printf("\n");
        }
    }
    printf("%lld\n", cnt);
}
