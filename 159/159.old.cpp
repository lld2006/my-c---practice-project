#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
int digsum(int num)
{
    int val =  num%9;
    if(val == 0) val = 9;
    return val;
}
void create_factors(int cpos, int prod, IntPairVec& facs, vector<int>& vdiv, int root)
{
    if(cpos == static_cast<int>(facs.size())){
        if(prod <= root)
            vdiv.push_back(prod);
        return;
    }
    for( int j = 0; j <= facs[cpos].second; ++j){
        int prod1 = prod * power(facs[cpos].first, j);
        if(prod1 > root) break;
        create_factors(cpos+1, prod1, facs, vdiv, root);
    }

}
int main(){
    int target = 1000000;
    vector<int> mdrs;
    vector<int> ftable;
    factor_table_min(target, ftable);
    mdrs.resize(target, -1);
    mdrs[0]=mdrs[1]=0;

    for(unsigned int root = 1; root <1000; ++root){
        for(unsigned int ri = root*root; ri < (root+1)*(root+1); ++ri){
            if(ri == 1) continue;
            int max = digsum(ri);
            IntPairVec facs;
            factor_using_table(ri, facs, ftable);
            vector<int> divisors;
            create_factors(0, 1, facs, divisors, root);
            for(unsigned int j = 0; j< divisors.size() ; ++j){
                int value = divisors[j];
                if(value == 1) continue;
                int curr = mdrs[value] + mdrs[ri/value];
                if(curr > max) max = curr;
            }
            mdrs[ri] = max;
        }
    }
    int sum = 0;
    for(unsigned int i =0 ; i < mdrs.size(); ++i){
        sum += mdrs[i];
    }
    printf("%d\n", sum);
}
