#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int nmod = 1000000;

int partition(int num, vector<int>& vn)
{
    i64 sum = 0;
    for( int i = 1; i ; ++i){
        int n5 = i*(3*i-1)/2;
        if(n5 > num) break;
        if(i & 1)
            sum += vn[num-n5];
        else
            sum -= vn[num-n5];
    }
    for( int i = 1; i ; ++i){
        int n5 = i*(3*i+1)/2;
        if(n5 > num) break;
        if(i & 1)
            sum += vn[num-n5];
        else
            sum -= vn[num-n5];
    }
    sum %= nmod;
    if(sum < 0)
        sum += nmod;
    return sum;
}
int main()
{
    vector<int> vn;
    int target = 200000;
    vn.resize(target+1, 0);
    vn[0] = 1;
    vn[1] = 1;
    for(unsigned int i = 2; i< vn.size(); ++i){
        vn[i] = partition(i, vn);
            //printf("%d %d\n", i, vn[i]);
        if(vn[i] == 0){
            printf("%d\n", i);
            return 0; 
        }
    }
}
