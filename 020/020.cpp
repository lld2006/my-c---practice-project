#include <cstdio>
#include <vector>
using namespace std;
int nmod = 10000000;
int main()
{
    vector<int> vn;
    vn.reserve(50);
    vn.push_back(1);
    for(unsigned int i = 2; i <= 100; ++i){
        int carry = 0;
        for(unsigned int j = 0; j < vn.size(); ++j){
            vn[j] = vn[j] * i+ carry;
            carry = vn[j] /nmod;
            vn[j] %= nmod;
        }
        if(carry)
            vn.push_back(carry);
    }
    int sum = 0;
    int res = 0;
    for(unsigned int i = 0; i < vn.size(); ++i){
        while(vn[i]>0){
           res = vn[i] % 10;
           vn[i]/= 10;
           sum += res;
        }
    }
    printf("%d\n", sum);
}
