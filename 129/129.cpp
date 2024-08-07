#include <cstdio>
#include "../lib/tools.h"
#include <cstdlib>
#include <cassert>
int minrepunit(int num){
    if(num %2 ==0 || num%5 ==0) return 0;
    int sum = 0;
    bool flag = true;
    int count = 0;
    while(flag){
        sum *= 10;
        ++sum;
        ++count;
        int res = sum % num;
        if(res == 0)
            return  count;
        else
            sum = res;
    }
    return 0;
}

/*  
int main(){
    int limit = 100000;
    vector<int> primes;
    primeWithin(primes, limit);
    int count = 0;
    int sum = 0;
    for(int i = 0; i  < primes.size(); ++i){
        int value = minrepunit(primes[i]);
        int vx = value;
        if(value == 0) continue;
        bool flag =true;
        int v2 = 0;
        int v5 = 0;
        while(vx > 1 && flag){
            flag = false;
            if(vx % 2 == 0){
                vx /=2;
                flag = true;
                ++v2;
            }
            if(vx % 5 == 0){
                vx /= 5; 
                flag = true;
                ++v5;
            }
            if(v2 > 12 ||v5 > 12){
                flag = false;
            }
        }
        if(flag){
            sum += primes[i];
            ++count;
            printf("%d %d %d\n",count, primes[i], sum);
        }
    }
}
int main(){
    unsigned long long int sum = 7;
    int limit = 100000;
    vector<int> primes;
    primeWithin(primes, limit);
    for(unsigned int i = 0; i< primes.size(); ++i){
        if(primes[i] %5 == 0 || primes[i]%2==0)continue;
        int value = minrepunit(primes[i]);
        while(value %2 == 0) value /=2;
        while(value %5 == 0) value /=5;
        if(value != 1)
            sum += primes[i];
    }
    printf("%I64d\n", sum);
}
int main(){
    u64 sum = 0;
    int limit = 100000;
    vector<int> primes;
    primeWithin(primes, limit);
    int size = primes.size();
    vector<int> svec;
    svec.resize(size, 0);
    svec[0] = 0;
    svec[1] = 3;
    svec[2] = 0;
    int ppos = 0;
    for(unsigned int i = 3; i < primes.size(); ++i){
        svec[i] = minrepunit(primes[i]);
    }
    IntPairVec ifac;
    for(int num = 9; num; num+=2){
        factor(num, ifac, primes);
        int value = num - 1;
        for(unsigned int j = 0; j < ifac.size(); ++j){
            if(value % 
        }
    }
}
*/
//problem 130
int main(){
    i64 sum = 0;
    vector<int> primes;
    int count = 0;
    for(int i = 3; i; i+=2){
        //if(pos == primes.size()-1) break;
        if(i %5==0) continue;
        if(i%3 == 0) continue;
        if(strong_pseudo_test(i)) 
            continue;
        int rep = powermodule(10LL, (i64)i-1, (i64) i);
        if(rep == 1){
            ++count;
            sum += i;
            if(count % 500 == 0)
                printf("num = %d rep =%d\n", i, minrepunit(i));
            if(count ==5000) break;
        }
    }
    printf("%lld\n", sum);
}


//int main(int argc, const char *argv[])
//{
//    for(int i = 1000001; i; i+=2){
//        if(i%5 ==0) continue;
//        int value = minrepunit(i);    
//        if(value > 1000000){
//            printf("%d\n", i);
//            return 0;
//        }
//    }
//    return 0;
//}
