#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

vector<int> single;
vector<int> dbl;
vector<int> triple;

int check3(int total, int limit, int scorelimit, int count);
int check2(int total, int limit, int scorelimit, int count);
int check1(int total, int limit, int scorelimit, int count);

int freeThrow(int total, int limit, int scorelimit, int count){
    if(total == 0) return 1;
    if(total < 0 || count >=3 ) return 0;
    assert(limit >= 0 && limit <= 3);
    int sum  = 0;
    if(limit ==3 && total >=3) //can use all level
        sum += check3(total, 3, scorelimit, count);
    if(limit >= 2 && total >= 2){//up to two level
        if(limit >2)
            sum += check2(total, 2, 100, count);
        else
            sum += check2(total, 2, scorelimit, count);
    }
    if(limit >= 1){ // only level one
        if(limit > 1)
            sum += check1(total, 1, 100, count);
        else
            sum += check1(total, 1, scorelimit, count);
    }
    return sum;
}
int check3(int total, int limit, int scorelimit, int count){
    assert(limit == 3);
    int sum = 0;
    for(unsigned int i = 0; i < triple.size(); ++i){
        if(triple[i] <= scorelimit && total >= triple[i]){
            sum += freeThrow(total - triple[i], limit, triple[i], count+1) ;
        }
    }
    return sum;
}
int check2(int total, int limit, int scorelimit, int count ){
    assert(limit == 2);
    int sum = 0;
    for(unsigned int i = 0; i < dbl.size(); ++i){
        if(dbl[i] <= scorelimit && total >= dbl[i]){
            sum += freeThrow(total - dbl[i], limit, dbl[i], count+1);
        }
    }
    return sum;
}
int check1(int total, int limit, int scorelimit, int count){
    assert(limit == 1);
    int sum = 0;
    for(unsigned int i = 0; i < single.size(); ++i){
        if(single[i] <= scorelimit && total >= single[i]){
            sum += freeThrow(total - single[i], limit, single[i], count+1) ;
        }
    }
    return sum;
}
int main(){
    int tcount = 1;
    single.resize(21);
    dbl.resize(21);
    triple.resize(20);
    for(unsigned int i = 0; i < 20; ++i){
        single[i] = i+1;
        dbl[i] = (i+1)*2;
        triple[i] = (i+1)*3;
    }
    dbl[20] = 50;
    single[20] = 25;
    int count = 0;
    for(unsigned int j = 2; j<= 99; ++j){
    for(unsigned int i = 0; i< dbl.size(); ++i){
        //                  total       level constrain score constrain
        count += freeThrow( j - dbl[i], 3, 100, tcount);
    }
    }
    printf("%d\n", count);
}
