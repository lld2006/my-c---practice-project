#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
i64 debug(int n)
{
    i64 k;
    for( k = n-1; k > 0; --k){
        if((k*k-k)%n==0)
            break;
    }
    return k;
}
int main()
{
    //int n = 210;
    //for(unsigned int i = 1; i<n;++i){
    //    int i2 = i*i;
    //    if(i2 % n == i)
    //        printf("%d\n", i);
    //}
    int limit = 10000000;
    vector<int> ftable;
    factor_table_max(limit, ftable);
    i64 sum = 1;
    i64 n1=0, n2=0;
    for( int i = 3; i <= limit; ++i){
        if(i % 100000==0)
            printf("%d\n",i);
        i64 ni4 = 4*i;
        int np = ftable[i];
        if(np == 2) {
            sum += 1;
            //assert( 1 == debug(i));
            //printf("%d %lld\n",i, 1LL);
            continue;
        }
        n1 = 2*i -1-np;
        n2 = 2*i +1-np;
        
        if(n1 % 2 == 0)
            n1 -= np;
        if(n2 %2 == 0)
            n2 -= np;
        //assert((n1*n1)%ni4 == 1);
        //assert((n2*n2)%ni4 == 1);
        bool notfound = true;
        //always make n1 > n2
        if(n1 < n2){
            swap(n1, n2);
        }
            
        while(notfound){
            assert(n1 > 0);
            if( (n1*n1 )% ni4 == 1){
                //printf("%d %lld\n",i, (n1+1)/2);
                //assert( (n1+1)/2 == debug(i));
                sum += (n1+1)/2;
                break;
            }else{
                n1 -= np;
            }
            assert(n2 > 0);
            if( (n2*n2 )% ni4 == 1){
                //printf("%d %lld\n",i, (n2+1)/2);
                //assert( (n2+1)/2 == debug(i));
                sum += (n2+1)/2;
                break;
            }else{
                n2 -= np;
            }
            assert(n1 > 0 || n2 > 0);
        }
    }
    printf("%lld\n", sum);
}
