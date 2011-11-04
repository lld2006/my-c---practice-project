#include<cstdio>
#include<vector>
#include<numeric>
#include<algorithm>
#include "../lib/int.h"
using namespace std;

bool isPaldrome(int i)
{
    bool flag = true;
    GeneralInteger gi(i);
    for(int j = 0; j < 60; ++j){
        vector<int>& nvec = gi.getNumber();
        int size = nvec.size();
        vector<int> nx;
        nx.resize(size, 0);
        reverse_copy(nvec.begin(), nvec.end(), nx.begin());
        GeneralInteger ginv(nx);
        GeneralInteger gsum = ginv + gi;
        vector<int>& nsumvec = gsum.getNumber();
        nx.resize(nsumvec.size(), 0);
        reverse_copy(nsumvec.begin(), nsumvec.end(), nx.begin());
        if(nsumvec == nx) {
            flag = false;
            //printf("iter = %d\n", j);
            //gsum.print();
            break;
        }
            //gsum.print();
        gi = gsum;
    }
    return flag;
}

int main()
{
    int num = 0;
    for(int i = 1; i < 10000; ++i){
        if(isPaldrome(i)) ++num;
    }
    printf("%d\n", num);
}

