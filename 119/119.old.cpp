#include "../lib/tools.h"
#include "../lib/int.h"
#include <cmath>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <numeric>
using namespace std;
int main(){
    vector<int> maxnum;
    double limit = 1e15;
    int max_pow = floor(log(limit)/log(2.0));
    maxnum.resize(max_pow+1, 0);
    for(int p = 2; p <= max_pow; ++p){
        int nmax = pow((double)limit, 1.0/p);
        maxnum[p] = min<int>(nmax, 150);
    }
    GeneralInteger one(1);
    set<GeneralInteger> nset;

    int pos = maxnum.size()-1;
    int kx = 2;
    while(pos >=2){
        while(kx <= maxnum[pos]){
            GeneralInteger gx(kx); 
            GeneralInteger gy(gx);
            for(int p = 2; p<=pos; ++p){
                gx=gy.multiply(kx);
                gy = gx;
                vector<int>& nu = gx.getNumber();
                int sum = accumulate(nu.begin(), nu.end(), 0);
                bool flag = true;
                if(sum == 1|| gx.numberDigit() < 2) flag = false;
                int n1 = sum %10;
                n1 = power(n1, p) % 10;
                if(n1 != gx.getNthDigit(0))continue;
                while(flag){
                    if(gx.modulus(sum)){ 
                        flag =false;
                        break;
                    }
                    gx = gx.divide(sum);
                    if(gx.getNumber() == one.getNumber()) break;
                }
                if(flag) {
                    nset.insert(gy);
                }
            }//different power
            ++kx;
            while(kx > maxnum[pos])--pos;
            if(pos <2) break;
        }
    }
    int count = 0;
    for(set<GeneralInteger>::iterator iter=nset.begin(); iter!=nset.end(); ++iter){
        printf("%d ", count+1);
        ++count;
        iter->print();
        printf("\n");
    }
}
