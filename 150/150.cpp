#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int get(int row, int col, vector<int>& vn)
{
    if(col < 0) return 0;
    int shift = row*(row+1)/2+col;
    return vn[shift];
}
int main()
{
    vector<int> vn;
    i64 n20 = 1<<20;
    i64 n19 = 1<<19;
    vn.resize(500500, 0);
    i64 t = 0;
    int k = 0;
    for(int row = 0; row < 1000; ++row){
        for(int col = 0; col <= row; ++col){
            t = (615949*t+797807);
            t %= n20;
            if(col==0)
                vn[k] = t - n19;
            else
                vn[k] = vn[k-1] + t-n19;
            ++k;
        }
    }

    assert(vn.size() == 500500);
    int gmin = 1000000;
    for(int row = 0; row < 1000; ++row){
        for(int col = 0; col <= row; ++col){
            int sum = get(row, col, vn)-get(row, col-1, vn);;
                for(int drow = 1; drow < 1000 - row; ++drow){
                    int col2 = col+drow;
                    sum += get(row+drow, col2, vn)-get(row+drow, col-1, vn);
                    if(sum < gmin){
                        printf("%d\n", sum);
                        gmin = sum;
                    }
                }
        }
    }
}
