#include <cstdio>
#include "../lib/typedef.h"
//although this is my second time that I worked on this problem, 
//it still takes me some time to find the answer. Let me summarize where
//I made mistakes;
//first the problem set no restriction on d1, I forgot this and always got
//a 9 digit number. Second, I forgot to set and reset vflags when a number 
//is selected. third, a minor mistake, that when I want to get the final number
//before added to total, I forgot to multiply i! last, I forgot that zero
//maybe taken, I always checked 1 to 9
i64 total = 0;
vector<int> primes = {1, 2,3,5,7,11,13,17};

void find_all_pan(vector<int>& vflag, int cpos, i64 multiplier, i64 cnum, int next)
{
    if(cpos == 0){
        for(unsigned int i = 1; i<=9; ++i){
            if(vflag[i] == 0) {
                i64 c1 = cnum + multiplier*10*i;
                total += c1;
                printf("%lld\n", c1);
                return;
            }
        }
        return;
    }
    for(unsigned int i = 0; i<=9; ++i ){
        if(vflag[i]) continue;
        int value = i * 100 + next;
        if((value % primes[cpos]) == 0){
            i64 c1 = cnum + multiplier*10*i;
            i64 n1 = value / 10;
            vflag[i] = 1;
            find_all_pan(vflag, cpos-1, multiplier*10, c1, n1 );
            vflag[i] = 0;
        }
    }
}
int main()
{
    vector<int> vflag;
    int nmax = 1000/primes.back();
    for( int i = 1; i <=nmax; ++i){
        vflag.clear();
        vflag.resize(10, 0);
        int num = i * primes.back();
        int nnext = num/10;
        int n1 = num;
        bool isCand = true;
        if(n1 < 100) vflag[0] = 1;
        while(n1){
            int res = n1 %10;
            if(vflag[res] == 1){
                isCand = false;
                break;
            }
            vflag[res] = 1;
            n1 /= 10;
        }
        if(!isCand)
            continue;
        find_all_pan(vflag, 6, 100, num, nnext);
    }
    printf("%lld\n", total);
}
