#include <cstdio>
#include "../lib/tools.h"
int main()
{
    vector<int> flags;
    flags.resize(1001, 0);
    for(unsigned int a = 1; a<23;++a){
        for(unsigned int b = a+1; ;b+=2){
            if(gcd(a, b) != 1) continue;
            int c = b*b+a*a;
            if(c>1000) break;
            int peri = 2*b*(b+a);
            for(unsigned int k = peri; k < flags.size(); k+=peri){
                ++flags[k];
            }
        }
    }
    int maxcnt = 0;
    int maxn = 0;
    for(unsigned int i = 0; i < flags.size(); ++i){
        if(flags[i] > maxcnt){
            maxcnt = flags[i];
            maxn = i;
        }
    }
    printf("%d %d\n", maxn, maxcnt);
}
