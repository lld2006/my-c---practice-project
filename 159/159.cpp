#include <vector>
#include <numeric>
#include <cstdio>
using namespace std;
int main()
{
    int target = 1000000;
    vector<int> mdrs;
    mdrs.resize(target , 0);
    int cnt = 2;
    for( int i = 2;i < target; ++i ){
         if(cnt < 10) 
             mdrs[i] = cnt++;
         else{
             cnt = 1;
             mdrs[i] = cnt++;
         }
    }
    for(int pow2 = 2; pow2<=19; ++pow2){
        int first = (1<<pow2);
        int last = (1<<(pow2+1));
        if(last > target) last = target-1;
        for(int nx = 2; nx*nx <=last; ++nx){
            int jstart = first/nx;
            for(int j = jstart*nx; j<= last;j+= nx){
                int val = mdrs[j/nx] + mdrs[nx];
                if(val > mdrs[j]) 
                    mdrs[j] = val;
            }
        }
    }
    int sum = accumulate(mdrs.begin(), mdrs.end(), 0);
    printf("%d\n", sum);
}
