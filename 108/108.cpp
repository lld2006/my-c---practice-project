#include <cstdio>
#include <cmath>
#include <vector>
#include "../lib/tools.h"
using namespace std;
int main()
{
    int target = 500000;
    vector<int> vcount;
    vcount.resize(target+1, 1);
    int root = sqrt(target);
    for(int i = 1; i< root; ++i){
        for(int j =i+1; j <= target/i; ++j){
            if(gcd(i,j) > 1) continue;
            int value = i*j;
            for(unsigned int k = value; k < vcount.size();k+=value )
                ++vcount[k];
        }
    }
    for(unsigned int i = 1; i < vcount.size(); ++i){
        if(vcount[i] > 1000){
            printf("%d %d\n", i, vcount[i]);
            return 0;
        }
    }
}
