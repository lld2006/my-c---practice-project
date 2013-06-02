#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    vector<i64> vn={0, 1, 2, 4, 8};
    for(int i=5; i<=50; ++i){
        i64 value = vn[i-1]+vn[i-2]+vn[i-3]+vn[i-4];
        vn.push_back(value);
    }
    printf("%lld\n", vn[50]);
}
