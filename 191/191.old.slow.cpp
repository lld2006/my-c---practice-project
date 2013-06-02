#include <cstdio>
#include <cassert>
int nprize(int today, int total, int absent, int late){
    ++today;
    int sum = 0;
    if(today == total){
        if(late == 0){
            if(absent <= 1)
                return 3;
            else if(absent == 2){
                return 2;
            }else{
                assert(absent == 3);
                return 0;
            }
        }else if(late == 1){
            if(absent <= 1)
                return 2;
            else if(absent == 2){
                return 1;
            }else{
                assert(absent == 3);
                return 0;
            }
        }else{
            assert(late == 2);
            return 0;
        }
    }
    if(late == 0){
        if(absent <= 1)
            sum = nprize(today, total, 0, 0)+nprize(today, total, absent+1, 0)
                +nprize(today, total, 0, 1);
        else if(absent == 2){
            sum = nprize(today, total, 0, 0)+ +nprize(today, total, 0, 1);
        }
        else
            return 0;
    }
    else if(late == 1){
        if(absent <= 1)
            sum = nprize(today, total, 0, late)+nprize(today, total, absent+1, late);
        else if(absent == 2){
            sum = nprize(today, total, 0, late); 
        }
        else
            return 0;
    }
    return sum;
}
int main(){//need a dynamic programming approach
    int n = 0;
    int num = nprize(n, 30, 0, 0);
    //int num1 = nprize(n, 4, 1, 0);
    //int num2 = nprize(n, 4, 2, 0);
    printf("%d\n", num);
}
