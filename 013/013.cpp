#include <cstdio>
#include "../lib/typedef.h"
#include <string>
#include <vector>
using namespace std;
i64 nmod = 10000000000LL;
int main()
{
    char tstr[64];
    FILE * fin;
    fin = fopen("n50.txt", "r");
    vector<string> vs;
    while(fscanf(fin,"%s", tstr)==1) {
        vs.push_back(string(tstr));
    }
    printf("%zu\n", vs.size());
    i64 sum1=0; i64 sum2=0;
    for(unsigned int i = 0; i < vs.size(); ++i){
        string s1=vs[i].substr(0, 10);
        string s2=vs[i].substr(11, 10);
        i64 n1 = stoll(s1);
        i64 n2 = stoll(s2);
        sum1 += n1; sum2 += n2;
    }
    sum1 += sum2/nmod;
    while(sum1 >nmod)
        sum1/=10;
    printf("%lld\n", sum1);
}
