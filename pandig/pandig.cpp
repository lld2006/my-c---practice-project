#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    vector<int> pand, psum;
    pand.resize(10);
    psum.resize(10,0);
    for(int i = 0 ; i < 10; ++i)
        pand[i]=i;
    bool flag = true;
    while(flag){
        bool passed = true;
        for(int i =1; i < 8; ++i){
            int num = pand[i]*100 + pand[i+1] * 10 + pand[i+2];
            if (num % prime[i-1]) {
                passed = false;
                break;
            }
        }
        // all test passed
        if(passed){
            for(int i = 0; i < 10; ++i)
               psum[i] += pand[i]; 
        }
        flag = next_permutation(pand.begin(), pand.end());
    }
    int incre = 0;
    for(int i = 0; i< 10; ++i){
        if(psum[9-i] > 10) {
            psum[9-i] += incre;
            incre = psum[9-i]/10;
            psum[9-i] = psum[9-i]%10;
        }
    } 
    if(incre > 0) printf("%d", incre);
    unsigned int psize = psum.size();
    for(unsigned int i = 0; i< psize; ++i){
        printf("%d", psum[i]);
    }
    return 0;
}
