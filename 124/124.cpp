#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#include "../lib/tools.h"
int radical(int number, const vector<int>& ftable)
{
    int factor = ftable[number];
    int prod = factor;
    while(number > 1){
        if(ftable[number] != factor){
           prod *= ftable[number];
           factor = ftable[number];
        }
        number /= ftable[number];
    }
    assert(prod != 3610);
    return prod;
}
void generate_all_numbers(int num, IntPairVec& pairs, vector<int>& vn, int cpos)
{
    if(cpos == pairs.size()){
        vn.push_back(num);
        return;
    } 
    for( int i = 0; true ; ++i ){
        int n1 = num * power(pairs[cpos].first, i);
        if(n1 > 100000) break;
        generate_all_numbers(n1, pairs, vn, cpos+1);
    }
}
int main()
{
    int target = 100000;
    vector<int> ftable;
    vector<int> vct;
    vct.resize(target+1, 0);
    factor_table_min(target, ftable);
    for(int i = 1; i<=target; ++i){
        int value = radical(i, ftable);
        ++vct[value];
    }
    int cnt = 0;
    int i;
    for(i = 0; i < vct.size(); ++i){
        cnt += vct[i];
        if(cnt >= 10000){
            printf("%d %d %d\n", cnt, i, vct[i]);
            break;
        }
    }
    IntPairVec pairs;
    vector<int> vn;
    factor_using_table(i, pairs, ftable);
    generate_all_numbers(i, pairs,vn, 0);
    sort(vn.begin(), vn.end());
    for(unsigned int i = 0; i < vn.size(); ++i){
        printf("%d\n", vn[i]);
    }
}
