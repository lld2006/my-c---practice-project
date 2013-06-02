#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
//my code is following the following idea,
//where did you stop spliting. it can only stop at a zero. 
int main(){
    vector<int> num;
    vector<i64> value;
    num.resize(25, 0);
    unsigned long long v5 = power(5LL, 25LL);
    //num.clear();
    //v5 = 12;
    while(v5){
        if(v5 %2 ==1){
            num.push_back(1);
        }else{
            num.push_back(0);
        }
        v5 /= 2;
    }
    value.resize(num.size(), 0);
    value[0] = 1;
    for(unsigned int i = 1; i < num.size(); ++i){
        if(!num[i])
            value[i] = value[i-1];
        else{
            unsigned long long int vt = value[i-1];//itself is one possibility
            for(int j = i-1; j >= 0 ; --j){
                if(num[j] == 0)
                    vt += value[j];
            }
            value[i] = vt;
        }
    }
    for(unsigned int i = 0; i < value.size(); ++i){
       // printf("%d %d %lld\n", i,num[i], value[i]);
    }
}
