#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
//my method is kind of brute force, need to find better method
int main()
{
    //grid the range? since we can not afford that large a range
    vector<int> next_square, grid;
    next_square.resize(1000000, 2);
    i64 grid_size = 1000000;
    int grid_cnt = 1;
    int cnt = 0;
    i64 sum = 0;
    while(cnt < 5){
        grid.clear();
        grid.resize(grid_size, 0);
        i64 shift = 0;
        for(unsigned int i = 2; i < next_square.size(); ++i){
            i64 vcube = (i64)i * i * i;
            shift = (grid_cnt-1) * grid_size;
            if(vcube - shift - grid_size >= 0) break;
            i64 sum23 = 0;
            do{
                sum23 = vcube + next_square[i]*next_square[i];
                i64 delta = sum23 - shift;
                ++next_square[i];
                assert(delta >= 0);
                if(delta >= grid_size)
                    break;
                else
                    ++grid[delta];
                if(sum23==5229225)
                    printf("%d %d %d %lld %lld\n", next_square[i]-1, i, grid_cnt, sum23, vcube);
            }while(true);
        }//all n^3 +m^2 calculated
        shift = (grid_cnt-1) * grid_size; 
        for(unsigned int i = 0; i < grid.size(); ++i){
            if(grid[i]==4){
                i64 value = shift + i;
                if(isPalindromic(value, 10)){
                    ++cnt;
                    printf("%d %lld\n",cnt, value);
                    sum += value;
                }
            }
        }
        ++grid_cnt;
    }
    printf("%lld\n", sum);
}
