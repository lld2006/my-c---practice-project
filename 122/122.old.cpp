#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <numeric>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;

/*
// lesson, do not use the same name for different variables; how to turn on this compilor 
// warnings?
int minmult(int num, vector<int> nvec, vector<int> flag, int nmult, int& nmax){
    if(flag[num] == 1) {
        return nmult;
    }
    if(nmult >= nmax-1 )
        return nmax;
    //summation
    for(unsigned int i = 0; i < nvec.size(); ++i){
        if(flag[num - nvec[i]]) return nmult+1;
        for(unsigned int j = i; j < nvec.size(); ++j){
            if(nvec[i] + nvec[j] <= nvec.back())
                continue;
            if( nvec[i] + nvec[j] > num)
                continue;
            else{
                int nt = nvec[i] + nvec[j];
                vector<int> n1(nvec);
                vector<int> f1(flag);
                assert(nt <= num);
                f1[nt] = 1;
                n1.push_back(nt);
                int ret = minmult(num, n1, f1, nmult+1, nmax);
                if(ret  < nmax )
                    nmax = ret;
            }
        }
    }
    return nmax;
}

int main(){
    vector<int> data;
    vector<int> primes;
    vector<set<int> > primemult;
    data.resize(201, 0);
    primeWithin(primes, 210);
    data[1] = 0;
    for(unsigned int num = 2; num <= 200; ++num){
        if(isPrime(num)) {
            data[num] = data[num - 1]+1;
            printf("%d %d\n", num, data[num]);
            continue;
        }
        bool pflag = false;
        for(unsigned int j = 0; j < primes.size(); ++j){
            if(num % primes[j] == 0 ) {
                data[num] = data[primes[j]]+data[num/primes[j]];
                printf("%d %d\n", num, data[num]);
                pflag = true;
                break;
            } 
        }
        if(pflag) continue;
        int nmax = num -1;
        vector<int> nvec, flag;
        nvec.clear();
        flag.clear();
        nvec.resize(1, 1);
        flag.resize(num+1, 0);
        flag[1] = 1;
        int nmult  = 0;
        data[num] = minmult(num, nvec, flag, nmult, nmax);
        printf("%d %d\n", num, data[num]);
    }
    int sum = accumulate(data.begin(), data.end(), 0);
    printf("%d\n", sum);
}
*/
struct expo{
    int number; 
    int upper;
    int right;
    int level;
};

int main(){
    vector<int> vpow;
    vector<expo> vexpo;
    vpow.resize(1000, 0);
    vexpo.resize(100000000);
    int level = 0;
    int pos = 0;
    int current = 0;
    int count = 1;
    vpow[0] = 1;
    vpow[1] = 1;
    vexpo[0].number = 1;
    vexpo[0].upper = -1;
    vexpo[0].right = -1;
    vexpo[0].level = 0;
    int next = pos+1;
    while(level <= 11 && count< 10000000){
        ++level;
        while(current != -1){
            int upper = current;
            vector<int> vupper;
            while(upper!= -1){
                vupper.push_back(vexpo[upper].number);
                upper = vexpo[upper].upper;
            }
            for(int i = vupper.size() -1; i >= 0; --i){
                int value = vexpo[current].number + vupper[i];
                if( value < 201){
                    ++pos;
                    ++count;
                    vexpo[pos].number = value;
                    vexpo[pos].upper = current;
                    vexpo[pos].right = pos+1;
                    vexpo[pos].level = level;
                }
            }
            current = vexpo[current].right;
        }
        vexpo[pos].right = -1;
        current = next;
        next = pos +1;
    }
    int sum = 0;
    vpow.clear();
    vpow.resize(201, 50);
    vpow[0] = 0;
    for( int i = 0; i <= pos; ++i){
        if(vexpo[i].number <= 200 && vexpo[i].number > 0){
            if(vexpo[i].level < vpow[vexpo[i].number]){
                vpow[vexpo[i].number]= vexpo[i].level;
            }
        }
    }
    int s2 = accumulate(vpow.begin(), vpow.end(), 0);
    printf("count %d %d %d\n", pos, sum, s2);
}
