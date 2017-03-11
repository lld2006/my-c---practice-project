#include <cstdio>
#include <map>
#include "../lib/tools.h"
map<i64, double> bmap;

//no difference on average, but worst case may differs 
double Binary_search_step(i64 n)
{
    if(n == 1) return 1.0;
    if(n==0) return 0.0; 
    map<i64, double>::iterator iter = bmap.find(n);
    if(iter != bmap.end()) return iter->second; 
    i64 pos = (n-1)/2;
    double value;
    if(n & 1){
        assert(2*pos+1 ==n);
        value = 1.0+ Binary_search_step(pos)*2*pos/n;
        bmap[n] = value;
    }else{
        assert(2*pos+2 == n);
        value = 1.0+ Binary_search_step(pos)*(pos)/n + Binary_search_step(pos+1)*(pos+1)/n;
        bmap[n] = value;
    }
    return value;
}
double Random_binary_search_step(i64 n)
{
    double harm = log(n+1) + 0.5772156649 + 1/(2*n+2)-1/(12*(n+1)*(n+1));
    return (2*(n+1)*harm-3*(n+1)+1)/n;
}
int main()
{
    i64 n = 10000000000;
    //n = 6;
    double val = Binary_search_step(n);
    double val2 = Random_binary_search_step(n);
    printf("%20.15f, %20.15f\n", val2- val, log(n+1));
    return 0;
}
