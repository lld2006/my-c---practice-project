#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
//lesson, first if the single flag has already marked, its successor should always be 0
//simplified some code about is_single. Then it is solved.
int nsize = 100;
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
//first notice that the sum can at most reach 100*100*201/6=338350 - 50*51*101/6
void update_sumset_vec(int level, vector<sumset>& sqvec){
    vector<sumset> dpvec;
    int maxval = 295425/2;//at most equal to this value, greater than will be omitted
    dpvec.resize(maxval+1, sumset());
    int cnt = 0;
    for(int i = 0; i < static_cast<int>(sqvec.size()); ++i){
        int start = sqvec[i].index+1;
        int final = nsize/2+level;
        for(int j = start; j <= final; ++j){
            bool is_single = (j <= sqvec[i].max_index) && sqvec[i].single; //this is not quite right
            assert(j < static_cast<int>(square.size()));
            int value = sqvec[i].sum + square[j];
            if(value > maxval) continue;
            assert(value > 0 && value < static_cast<int>(dpvec.size()));
            if(dpvec[value].index == -1){//the first entry in dpvec
                assert(sqvec[i].max_index <= 101 && sqvec[i].max_index > 0);
                dpvec[value].init(j, value, is_single, 101); // for single no constrain
                ++cnt;
            }else{ //use the minimal index as index val
                if(j < dpvec[value].index){
                    int max_idx = dpvec[value].index;
                    dpvec[value].init(j, value, is_single, max_idx);
                }
                else{
                    int idx = dpvec[value].max_index;
                    if(j < idx)
                        dpvec[value].max_index = j;
                }
            }
        }
    }
    sqvec.clear(); 
    sqvec.resize(cnt, sumset());
    int nnew = 0;
    for(unsigned int i = 0; i < dpvec.size(); ++i){
        if(dpvec[i].single>=0)
            sqvec[nnew++] = dpvec[i];
    }
}
int main(){
    square.resize(nsize+1, 0);
    vector<sumset> sqvec; //square sum
    sqvec.resize(nsize/2+1, sumset());//at the beginning, there are 51 sums
    for(unsigned int i = 0; i < square.size(); ++i)
        square[i] = i*i;
    for(unsigned int i = 0; i<sqvec.size(); ++i)
        sqvec[i].init(i+1, square[i+1], 1, 101);
    for(int level = 2; level <= nsize/2; ++level)
        update_sumset_vec(level, sqvec);
    i64 sum = 0;
    
    for(unsigned int i = 0; i < sqvec.size(); ++i){
        if(sqvec[i].single == 1 && sqvec[i].max_index == 101){
            ++sum;
        }
    }
    printf("%lld\n", sum*338350);
}
