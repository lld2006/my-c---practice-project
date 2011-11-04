#include <cstdio>
#include <set>
#include "../lib/int.h"

// lesson, first after add set iterator, the process is not kept the same.
// second, number should from 0 -- 9
int main()
{
    set<int> numH, numL;
    numL.insert(3);
    numL.insert(7);
    for(int round = 1; round <=4 ; ++round) {   
        numH.clear();
        for(int i = 0; i<= 9; ++i){
            if(round == 4 && (i==0 || i>=2))continue;
            for( int j = 0; j <= 9; ++j){
                int ix = 10 * i + j;
                for(int m = 1; m<= 2*round - 1; ++m) 
                    ix *= 10;
                for(set<int>::iterator iter=numL.begin(); iter != numL.end(); ++iter){
                    int ixp = ix + *iter;
                    GeneralInteger ia(ixp);
                    ia = ia.multiply(ixp);
                    if(ia.numberDigit() < (2*round + 1) )continue;
                    if( ia.getNthDigit(2*round) == 9-round ){
                        assert( round >1 || ixp < 1000);
                        numH.insert(ixp);
                    }
                }
            }
        }
        numL = numH;
    }
    for(set<int>::iterator iter = numL.begin(); iter != numL.end(); ++iter){
       GeneralInteger ia(*iter);
       ia = ia.multiply(*iter);
       if(ia.numberDigit() != 17)continue;
       if(ia.getNthDigit(0)==9 && ia.getNthDigit(2)==8 && ia.getNthDigit(4)==7 
               && ia.getNthDigit(6)==6 && ia.getNthDigit(8) ==5 && ia.getNthDigit(10)==4
               && ia.getNthDigit(12)==3 && ia.getNthDigit(14)==2 && ia.getNthDigit(16)==1)
       {
           printf("result\n");
           ia.print();
           printf("result\n");
       }
    }
}
