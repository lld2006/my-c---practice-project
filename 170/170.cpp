#include "../lib/typedef.h"
#include <algorithm>
#include <cstdio>
#include <numeric>
//need better algo
int main(){
    vector<int> vinit;
    vinit.resize(10,0);
    i64 max = 0;
    for(int i = 0; i <= 9; ++i)
        vinit[i] = 9 - i; //init to 9876543210
    
    for(int n = 9; n<=99; n+=1){
        vector<int> vn(vinit);
        vector<int> flags;
        flags.resize(10,0);
        int n1 = n;
        bool accept = true;
        while(n1){
            int res = n1 % 10;
            if(flags[res]==0)
                flags[res] = 1;
            else{
                accept = false;
                break;
            }
            n1/= 10;
        }
        if(!accept) continue;
        vector<int> f1(flags);
        do{
            i64 res1 = 0;
            for(unsigned int i = 0; i<vn.size(); ++i){
                res1 *= 10;
                res1 += vn[i];
            }
            if(res1 < 9786105234LL) break;
            i64 tp = 0;
            bool failed = false;
            int nb = 0;
            for(unsigned int i = 0; i< vn.size(); ++i){
                tp = tp * 10 + vn[i];
                if(i == vn.size()-1 && tp == 0 && f1[0] == 1)
                    failed = true;
                if(tp % n == 0){
                    ++nb;
                    tp /= n;
                    while(tp){
                        int res = tp % 10;
                        tp /= 10;
                        if(f1[res] == 0)
                            f1[res] = 1;
                        else{
                            failed = true;
                            break;
                        }
                    }
                    tp = 0;
                }
                if(failed)
                    break;
            }
            if(tp != 0) 
                failed = true;
            int sum = accumulate(f1.begin(), f1.end(), 0);
            if(nb == 2 && sum ==9 && f1[0] == 0)
                failed = true;
            if(!(sum == 10|| (sum == 9 && f1[0]==0)))
                failed = true;
            if(!failed){
                i64 res = 0;
                for(unsigned int i = 0; i<vn.size(); ++i){
                    res *= 10;
                    res += vn[i];
                }
                if(res > max){
                    max = res;
                    printf("%lld %d\n", max, n);
                }
                break;
            }else{
                f1 = flags;
            }
        }while(prev_permutation(vn.begin(), vn.end()));
    }
    printf("%lld\n", max);
}
