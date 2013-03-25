#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
//lesson, first if the single flag has already marked, its successor should always be 0
//second a bug, ignored some single case

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
    int breach = 0;//times of boundary reached 
    int nmin =  level*(level +1)*(2*level+1)/6;
    int n50 = 42925;
    int nmax = (50+level)*(51+level)*(101+level*2)/6-n50;
    dpvec.resize(nmax-nmin+1, sumset());
    int cnt = 0;
    for(int i = 0; i < static_cast<int>(sqvec.size()); ++i){
        int start = sqvec[i].index+1;
        int final = 50+level;
        for(int j = start; j <= final; ++j){
            int value = sqvec[i].sum + j * j - nmin;
            if(value == 0) ++breach;
            if(value == nmax-nmin) ++breach;
            assert(value >= 0 && value < static_cast<int>(dpvec.size()));
            if(dpvec[value].index == -1){//the first entry in dpvec
                if( j <= sqvec[i].max_index)
                    dpvec[value].init(j, value + nmin, 1, 101); // for single no constrain
                else
                    dpvec[value].init(j, value + nmin, 0, 0);//for dup, always constrain

                ++cnt;
            }
            else{// already been touched
                assert(dpvec[value].index > 0 && dpvec[value].index <= 100);
                if(dpvec[value].max_index != 0){ //some are still single
                    if(j < dpvec[value].index){
                        assert(value + nmin == dpvec[value].sum);
                        assert(dpvec[value].max_index >= dpvec[value].index);
                        dpvec[value].init(j , value + nmin, 0, dpvec[value].index);
                    }
                    else{
                        assert(j != dpvec[value].index);//may be incorrect
                        dpvec[value].single = 0;
                        dpvec[value].max_index = j<dpvec[value].max_index? j:dpvec[value].max_index;
                    }
                }else{//for check purpose only no hope to be single
                    if(j < dpvec[value].index)
                        dpvec[value].init(j, value + nmin, 0, 0);
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
    assert(breach == 2);
}
int main(){
    vector<sumset> sqvec; //square sum
    sqvec.resize(51, sumset());
    for(unsigned int i = 1; i<= 51; ++i)
        sqvec[i-1].init(i, i*i, 1, 101);
    for(int level = 2; level <= 50; ++level)
        update_sumset_vec(level, sqvec);
    i64 sum = 0;
    printf("%d\n", sqvec.size());
    for(unsigned int i = 0; i < sqvec.size(); ++i){
        assert(sqvec[i].index >= 50);
        assert(sqvec[i].sum >= 42925 && sqvec[i].sum <= 295425 );
        if(sqvec[i].single == 1){
            assert(sqvec[i].max_index == 101);
            sum += sqvec[i].sum;
        }
    }
    printf("%lld\n", sum);
}
