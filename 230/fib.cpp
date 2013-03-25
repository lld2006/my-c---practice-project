# include <cstdio>
# include <cstdlib>
# include <cassert>
# include <string>
# include "../lib/typedef.h"
# include "../lib/tools.h"

using namespace std;

vector<i64> fvec;
i64 func(i64 n){
    return (127LL+19*n)*power(7, n);
}

int searchPosition(i64 number){
    int pos =89;
    while(true){
        if(fvec[pos-1] < number) break;
        --pos;
    }
    assert(pos > 0);
    if(pos  < 2) return pos;
    i64 value = number;
    while(pos > 2){
        assert(pos >= 2);
        if(value > fvec[pos -2]){
            value -= fvec[pos-2];
            --pos;
        }else{
            pos -=2;
        }
    }
    return pos;
}
int main(){
    string sa("1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");
    string sb("8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196");
    fvec.resize(90, 0);
    fvec[1]=1;
    for(int i = 2; i< 90; ++i){
        fvec[i] = fvec[i-1]+fvec[i-2];   
    }
    //int xs = searchPosition(16);
    //printf("%d\n", xs);
    //xs = searchPosition(15);
    //printf("%d\n", xs);
    //exit(0);
    for(int i = 17 ; i >= 0; --i){
        i64 nt = func(i);
        int pos = nt % 100;
        //should have a fix for this part %
        assert(pos > 0);
        i64 num = nt /100;
        int ab = searchPosition(num+1);
        assert(ab == 1|| ab==2);
        printf("%c", ab==1? sa[pos-1]:sb[pos-1]);
    }
}
    
