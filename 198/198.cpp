#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    int limit = 100000000;
    int limit2 = limit/2;
    int topmax =0;
    //limit = 10;
    vector<int> stack;
    stack.resize(limit, 0);
    i64 left = 1, right= 100;
    int top = 0;
    int cnt = 0;
    while(true){
        if(topmax < top)topmax = top;
        if(top < 0 ) break;
        i64 prod = left * right;
        int median = left + right;
        assert(prod > 0);
        if( prod <= limit2){
            stack[top++]=right;
            right = median;
            ++cnt;
        }else{
            left = right;
            right = stack[--top];
        }
    }
    printf("%d %d\n", cnt+49, topmax);
}
