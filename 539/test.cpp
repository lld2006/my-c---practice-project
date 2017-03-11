#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
int find_last(int n)
{
    vector<int> vn;
    vn.reserve(n);
    for(unsigned int i = 1; i<=n; ++i){
        vn.push_back(i);
    }
    while(vn.size() > 1){
        vector<int> vtemp;
        for(unsigned int i = 1; i< vn.size(); i+=2){
            vtemp.push_back(vn[i]);
        }
        reverse(vtemp.begin(), vtemp.end());
        swap(vn, vtemp);
    }
    return vn[0];
}
int main()
{
    vector<int> results;
    results.push_back(0);
    for(unsigned int i = 1; i <= 1000; ++i){
        int val = find_last(i);
        results.push_back(val);
    }
    int sum = 0;
    for(unsigned int i = 1; i<=1000; ++i){
        sum+=results[i];
        printf("%d %d\n", i, sum);
    }
    return 0;
}
