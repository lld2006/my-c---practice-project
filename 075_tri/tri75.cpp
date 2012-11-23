#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
int main()
{
    vector<int> vflags;
    int limit = 1500000;
    vflags.resize(limit+1, 0);
    int a, b, c, peri;
    int found = false;
    for(unsigned int i = 1; ; ++i){
        found = false;
        for(unsigned int j = i+1; ;j+=2){
            if(gcd(i, j)!=1)
                continue;
            a = j*j-i*i;
            b = 2*i*j;
            c = i*i+j*j;
            peri = a + b +c;
            if(peri > limit) break;
            found = true;
            for(unsigned int k = peri; k < vflags.size(); k += peri){
                ++vflags[k];
            }

        }
        if(!found) break;
    }
    int total = 0;
    for(unsigned int i = 0; i<vflags.size(); ++i){
        if(vflags[i] == 1)
            ++total;
    }
    printf("%d\n", total);
}
