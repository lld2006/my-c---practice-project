#include <cstdio>
#include <vector>
using namespace std;

bool isPalindromic(int num){
    vector<int> vd, vd1;
    while(num){
        int res = num %10;
        vd.push_back(res);
        num /= 10;
    }
    
    int iter = 0;
    while(iter < 50){
        vd1.clear();
        vd1.resize(vd.size(), 0); 
        int carry = 0;
        int vsize = vd.size();
        for(unsigned int i = 0; i <vd.size(); ++i ){
            vd1[i] = vd[i] + vd[vsize-i-1]+carry;
            if(vd1[i]>9){ 
                vd1[i] -= 10;
                carry = 1;
            }else{
                carry = 0;
            }
        }
        if(carry){
            vd1.push_back(1);
        }
        bool flag = true;
        vsize = vd1.size();
        for(unsigned int i = 0; i < vd1.size()/2; ++i){
            if(vd1[i] != vd1[vsize-1-i]){
                flag = false;
                break;
            }
        }
        if(flag)
            return true;
        ++iter;
        vd.swap(vd1);
    }
    return false;
}
int main()
{
    int cnt = 0;
    for(unsigned int i = 10; i< 10000; ++i){
        if(!isPalindromic(i)){
            ++cnt;
            //printf("%d\n", i);
        }
    }
    printf("%d\n", cnt);
}
