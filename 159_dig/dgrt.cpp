#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
int digsum(int num){
    int sum = 0;
    while(num >0 ){
        int res = num % 10;
        sum += res;
        num /= 10;
    }
    if(sum < 10)
        return sum;
    else
        return digsum(sum);
}
int main(){
    vector<int> mdrs;
    mdrs.resize(1000000, -1);
    mdrs[0]=mdrs[1]=0;

    for(unsigned int root = 1; root <1000; ++root){
        for(unsigned int ri = root*root; ri < (root+1)*(root+1); ++ri){
            int max = digsum(ri);
            if(ri == 1) 
                max = 0;
            for(unsigned int j = 2; j<=root; ++j){
                int curr = 0;
                if(ri % j != 0) continue;
                assert(mdrs[j]> 0);
                assert(mdrs[ri/j] > 0);
                curr = mdrs[j] + mdrs[ri/j];
                if(curr > max ) max = curr;
            }
            mdrs[ri] = max;
        }
    }
    int sum = 0;
    for(unsigned int i =0 ; i < mdrs.size(); ++i){
        sum += mdrs[i];
    }
    printf("%d\n", sum);
}
