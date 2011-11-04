#include  <vector>
#include "../lib/typedef.h"
#include "../lib/primelist.h"
#include <cstdio>
//lesson, need to understand the algo first

int main()
{
    IntVec cvec;    
    cvec.resize(4);
    for(int i =0; i< 4; ++i)
        cvec[i] = i;

    int count=0;
    while(next_combination(cvec, 10, 4)){
        ++count;
        for(int i =0; i<4;++i)
            printf("%d ", cvec[i]);
        printf("\n");
    }
        printf("%d \n", count);
}
