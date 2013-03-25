#include <cstdio>
#include <string>
#include <vector>
using namespace std;
int mult_pandig(int num)
{
    vector<int> flag;
    flag.resize(9, 0);
    int mult = 1;
    int cnt = 0;
    string ts;
    while(cnt < 9){
        int value = mult * num;
        ts.append(to_string(value));
        while(value){
            int res = value % 10;
            if(res == 0) return -1;
            if(flag[res-1] == 1)
                return -1;
            flag[res-1] = 1;
            ++cnt;
            value/=10;
        }
        ++mult;
    }
    return stoll(ts);
}
int main()
{
    int nmax = 0;
    for(int i = 1; i <10000; ++i){
       if(i>=1000 && i<=9123) continue;
       int ret = mult_pandig(i);
       if(ret > nmax)
           nmax = ret;
    }    
    printf("%d\n", nmax);
}
