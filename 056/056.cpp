#include <cstdio>
#include <numeric>
#include "../lib/int.h"
int main()
{
    int maxsum = 0;
    for(unsigned int i = 2; i< 100; ++i){
        for(unsigned int j = 2; j<100; ++j){
            GeneralInteger gi(i);
            GeneralInteger gij = gi.power(j);
            vector<int>& vd = gij.getNumber();
            int sum = accumulate(vd.begin(), vd.end(), 0);
            if(sum > maxsum){
                maxsum = sum;
            }
        }
    }
    printf("%d\n", maxsum);
}
