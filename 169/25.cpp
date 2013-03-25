#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
/*
int express2(vector<int>& vnum){
    while(vnum.back()==0) vnum.pop_back();
    if(vnum.size() == 0) return 0;
    if(vnum.size() == 1){
        if(vnum.back() == 3) 
            return 0; //last can not be 3
        else
            return 1;
    }
    assert(vnum.size() > 1);
    int back=vnum.back();
    vnum.pop_back();
    assert(back <= 3);
    int sum = 0;
    if(back==3){
        vector<int> v1(vnum);
        v1.back()+= 2;
        sum = express2(v1);
    }else{
        vector<int> v1(vnum);
        v1.pop_back();
        vector<int> v2(vnum);
        v2.back() += 2;
        sum = 1+express2(v1)+express2(v2);
    }
    return sum;
}
*/
int main(){
    vector<int> num;
    vector<unsigned long long int> value;
    num.resize(25, 0);
    unsigned long long v5 = power(5, 25);
    //unsigned long long v5 = 10;
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
        if(num[i] == 0)
            value[i] = value[i-1];
        else {
            assert(num[i] == 1);
            unsigned long long int vt = value[i-1];//it self is one possibility
            for(int j = i-1; j >= 0 ; --j){
                if(num[j] == 0){
                    vt += value[j];
                }
                else{
                    assert(num[j] == 1);
                }
            }
            value[i] = vt;
        }
    }
    printf("%I64d\n", value.back());
}
