#include "../lib/typedef.h"
#include <cstdio>
//the problem asks for sum of all numbers that is a perfect
//square, what is last 9 digit sum
int main(){
    vector<int> squares;
    vector<int> result;
    result.resize(1621,0);
    squares.resize(40, 0);
    //initialize the first digit on the left;
    for(int i = 1; i< 41; ++i){
        squares[i-1] = i * i;
    }
    for(int i = 1; i < 9; ++i){
        ++result[i*i];
    }
    u64 count = 9;
    // find out how many square numbers maybe formed
    for(int i = 2; i<=20; ++i){
        int csize = i*81+1;//0...81 *i
        vector<int> tp;
        tp.resize(csize);
        copy(result.begin(), result.begin()+csize, tp.begin());
        result.clear();
        result.resize(1621,0);
        for(int ia =0; ia < 10; ++ia){
            for(unsigned int j = 0; j < tp.size(); ++j){
                result[j+ia*ia] += tp[j];
            }
        }
        for(unsigned int j = 0; j<squares.size(); ++j)
            count += result[squares[j]];
    }
    printf("%lld\n", count);
}
