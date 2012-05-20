#include <cstdio>
#include "../lib/tools.h"
int main()
{
    for(int i = 0; i < 100; ++i)
        for(int j = i+1; j < 100; ++j){
            if(gcd(i, j) != 1)
                continue;
            int sum = i *i +j*j-i*j;
            int root = sqrt(sum);
            if(root *root== sum){
                int a = i;
                int b = j;
                if( a > b) 
                    swap(a, b);
                printf("%d %d %d\n", a, b, root);
            }
        }
}
