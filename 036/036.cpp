#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
int total = 0;

//lesson 1, when calculate nc in final stage, line 17, I forgot 
//to multiply v10[di]; lesson 2, nc should be const, otherwise, it is 
//easy to mess up the number in different stages.
void recursive_find(int nd, int di, const int nc, const vector<int>& v10)
{
    if(di == (nd>>1)){
        if(nd & 1){
            int start = 0;
            if(nd == 1) start = 1;
            for(unsigned int i = start; i <= 9; ++i ){
                int nc1 = nc + i*v10[di];
                //assert(isPalindromic(nc1, 10));
                if(isPalindromic(nc1, 2))
                    total += nc1;
            }
        }else{
            //assert(isPalindromic(nc, 10));
            if(isPalindromic(nc, 2))
                total += nc;
        }
        return;
    }
    int start = 0;
    int inc = 1;
    if(di == 0){
        start = 1;
        inc = 2;
    }
    for(unsigned int j = start; j <=9; j+=inc ) {
        int nc1 = nc;
        nc1 += v10[di] * j;
        nc1 += v10[nd-1-di] * j;
        recursive_find(nd, di+1, nc1, v10);
    }
}
int main()
{
    
    for(unsigned int i = 1; i<=6; ++i){
        vector<int> v10;
        v10.resize(i, 0);
        int nx = 1;
        for(unsigned int j = 0; j < i; ++j){
            v10[j] = nx;
            nx *= 10;
        }
        recursive_find(i, 0, 0, v10);
    }
    printf("%d\n", total);
}
