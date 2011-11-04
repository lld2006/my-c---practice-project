#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;
int main()
{
    vector<int> nvec;
    for(int i = 1; i< 10000; ++i)
        nvec.push_back(i*(3*i-1)/2);
    for(unsigned int i = 0 ; i < nvec.size(); ++i)
        for(unsigned int j = 0; j < i; ++j) {
            int diff = nvec[i] - nvec[j];
            int sum = nvec[i] + nvec[j];
            if( !binary_search(nvec.begin(), nvec.begin()+i, diff) ) continue;
            if( !binary_search(nvec.begin(), nvec.end(), sum )) continue;
            printf("%d %d %d %d \n",i,j, nvec[i], nvec[j]);
            break;
        }
}
