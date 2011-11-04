#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "../lib/tools.h"
//vector zero bit first, easier to 
//lesson, do not forget to reset the value that need to be used in the loop if the
//value will be checked
void next_small_number(vector<int>& nvec){
    int carry = 1;
    for(unsigned int i = 0; i < nvec.size(); ++i){
        nvec[i] +=carry;
        carry = 0;// forgot to reset carry!
        if(nvec[i] ==3){
            nvec[i] = 0;
            carry = 1;
        }
        if(carry == 0)
            break;
    }
    if(carry == 1)
        nvec.push_back(1);
}
unsigned long long int form_number(const vector<int>& nvec){
    unsigned long long int sum = 0;
    for(unsigned int i = 0; i < nvec.size(); ++i){
        sum += power(10,  i)*nvec[i];
    }
    return sum;
}
int main(){
    unsigned long long int sum = 0;
    //x9 = (unsigned long long int )11112222222222222222;
    int limit = 10000;
    //for(int i = 1; i<= 10; ++i){
    for(int i = 999; i<= limit; i+=999){
        //if(i % 999 == 0 || i%9999==0) continue;
        vector<int> nvec;
        nvec.clear();
        int numDig = 0;
        int n = i;
        while(n){
            n /= 10;
            ++numDig;
        }
        nvec.resize(numDig,0);
        nvec.back() = 1;
        bool notFound = true;
        while(notFound){
            unsigned long long int value = form_number(nvec);
            if(value % i ==0){
                sum += value / i;
                //printf("%d %I64d\n", i, value);
                break;
            }else{
                next_small_number(nvec);
            }
        }
    }
    printf("%I64d\n", sum);
}
