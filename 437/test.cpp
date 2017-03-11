#include "../lib/tools.h"
int main()
{
    vector<int> vprimes;
    primeWithin(vprimes, 10000);
    i64 sum = 0;
    for(unsigned int i = 3; i < vprimes.size();++i){
        int np = vprimes[i];
        if(np > 10000)break;
        int flag = 0;
        for(i64 j = 2; j < np; ++j ){
            i64 value = j *j -j -1;
            if(value% np ==0){
                flag = 1;
                break;
            }
        }
        if(flag){
            sum += np;
            printf("%d\n", np);
        }
    }
    printf("%lld\n", sum);
}
