#include <cstdio>
int main()
{
    int target = 2000000;
    int marea = 0;
    int mdiff = target;
    for(int i = 1; i; ++i){
        int pi = i*(i+1)/2;
        for(int j = 1; j; ++j){
            int pj = j*(j+1)/2;
            int result = pi * pj;
            int diff = result  - target;
            if(diff < 0) diff = -diff;
            if(diff < mdiff){
                mdiff = diff;
                marea = i*j;
            }
            if(result > target)
                break;
        }
        if(pi > target )
            break;
    }
    printf("%d\n", marea);
}
