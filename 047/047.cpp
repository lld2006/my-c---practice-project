#include <cstdio>
#include <vector>
#include "../lib/tools.h"
//old looks ugly, but still effective. the new one looks fancy
//but still slow.
#if 1
int main()
{
    int target=1000000;
    vector<int> ftable;
    factor_table_min(target, ftable);
#if 0
    IntPairVec vp;
    int i = 647;
    while(true){
        factor_using_table(i, vp, ftable);
        if(vp.size() != 4 ){
            ++i;
            continue;
        }
        factor_using_table(i+1, vp, ftable);
        if(vp.size() != 4 ){
            i+=2;
            continue;
        }
        factor_using_table(i+2, vp, ftable);
        if(vp.size() != 4 ){
            i+=3;
            continue;
        }
        factor_using_table(i+3, vp, ftable);
        if(vp.size() != 4 ){
            i+=4;
            continue;
        }
        printf("Found %d\n", i);
        break;
    }
#else
    for( int i = 647; i< target; ++i){
        IntPairVec vp;
        factor_using_table(i, vp, ftable);
        if(vp.size() != 4 ) continue;
        factor_using_table(i+1, vp, ftable);
        if(vp.size() != 4 ) continue;
        factor_using_table(i+2, vp, ftable);
        if(vp.size() != 4 ) continue;
        factor_using_table(i+3, vp, ftable);
        if(vp.size() != 4 ) continue;
        printf("%d\n", i);
        break;
    }
#endif
}
#else
int main()
{
    int target = 1000000;
    vector<int> ftable;
    primeWithin(ftable, target);
    vector<int> ntable;
    ntable.resize(target, 0);
    for(int i = 0; i < ftable.size(); ++i){
        int prime = ftable[i];
        for(int j = prime; j < target; j+=prime)
            ++ntable[j];
    }
    int count = 0;
    for(unsigned int i = 0; i< ntable.size(); ++i){
        if(ntable[i]==4)
            ++count;
        else
            count = 0;
        if(count == 4){
            printf("found at %u\n", i - 3);
            break;
        }
    }
}
#endif
