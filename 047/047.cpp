#include <cstdio>
#include <vector>
#include "../lib/tools.h"
int main()
{
    int target=1000000;
    vector<int> ftable;
    factor_table_min(target, ftable);
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
}
