#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
//lesson, first if the single flag has already marked, its successor should always be 0
//second a bug, ignored some single case

int nsize = 6;
vector<int> square;
struct sumset{
    int index; // smallest index for multiple equal sum or index for single sum
    int sum;
    int single;//for some false sumset, still need to prevent further equal sum
    int max_index;//max_index to be single
    sumset(){
        index = -1;
        sum = -1;
        single = -100;
        max_index = 0;
    }
    void init(int nindex, int nsum, int nsingle, int maxi){
        index = nindex;
        sum = nsum;
        single = nsingle;
        max_index = maxi;
    }
};
void update_sumset_vec(int level, vector<sumset>& sqvec){
    vector<sumset> dpvec;
    dpvec.resize(50, sumset());
    int cnt = 0;
    for(int i = 0; i < static_cast<int>(sqvec.size()); ++i){
        int start = sqvec[i].index+1;
        int final = nsize/2+level;
        for(int j = start; j < final; ++j){
            int value = sqvec[i].sum + square[j];
            assert(value >= 0 && value < static_cast<int>(dpvec.size()));
            if(dpvec[value].index == -1){//the first entry in dpvec
                if( j <= sqvec[i].max_index)
                    dpvec[value].init(j, value, 1, 101); // for single no constrain
                else
                    dpvec[value].init(j, value, 0, 0);//for dup, always constrain

                ++cnt;
            }
            else{// already been touched
                assert(dpvec[value].index > 0 && dpvec[value].index <= 100);
                if(dpvec[value].max_index != 0){ //some are still single
                    if(j < dpvec[value].index){
                        assert(value == dpvec[value].sum);
                        assert(dpvec[value].max_index >= dpvec[value].index);
                        dpvec[value].init(j , value, 0, dpvec[value].index);
                    }
                    else{
                        assert(j != dpvec[value].index);//may be incorrect
                        dpvec[value].single = 0;
                        dpvec[value].max_index = j<dpvec[value].max_index? j:dpvec[value].max_index;
                    }
                }else{//for check purpose only no hope to be single
                    if(j < dpvec[value].index)
                        dpvec[value].init(j, value, 0, 0);
                    else{
                        assert(dpvec[value].single == 0);
                    }
                }
            }
        }
    }
    sqvec.clear(); 
    sqvec.resize(cnt, sumset());
    int nnew = 0;
    for(unsigned int i = 0; i < dpvec.size(); ++i){
        if(dpvec[i].single != - 100){
            assert(dpvec[i].single==0||dpvec[i].single == 1);
            sqvec[nnew++] = dpvec[i];
        }
    }
    assert(nnew == static_cast<int>(sqvec.size()));
}
int main(){//1 3 6 8 10 11
    square.resize(6, 0);
    square[0]=1;
    square[1]=3;
    square[2]=6;
    square[3]=8;
    square[4]=10;
    square[5]=11;
    vector<sumset> sqvec; //square sum
    sqvec.resize(nsize/2+1, sumset());
    sqvec[0].init(0, 1, 1, 101);
    sqvec[1].init(1, 3, 1, 101);
    sqvec[2].init(2, 6, 1, 101);
    sqvec[3].init(3, 8, 1, 101);
    for(int level = 2; level <= nsize/2; ++level)
        update_sumset_vec(level, sqvec);
    i64 sum = 0;
    printf("%d\n", sqvec.size());
    for(unsigned int i = 0; i < sqvec.size(); ++i){
        if(sqvec[i].single == 1){
            sum += sqvec[i].sum;
        }
    }
    printf("%lld\n", sum);
}
