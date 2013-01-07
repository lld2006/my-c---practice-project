#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;
bool check_even(const vector<int>& vn)
{
    for(unsigned int i = 0; i< vn.size(); ++i){
        if(vn[i] != 1) 
            return false;
    }
    return true;
}
int compute_steps(int n)
{
    vector<int> vn;
    vn.resize(n, 1);
    vn[0]=0;
    vn[1]=2;
    int cnt = 1;
    int cp = 1;
    while(!check_even(vn)){
        ++cnt;
        int nb = vn[cp];
        vn[cp] = 0;
        for( int i = 1; i<= nb; ++i){
            int t = i + cp;
            if(t < n)
                ++vn[t];
            else
                ++vn[t-n];
        }
        cp += nb;
        if( cp >= n){
            cp -= n;
        }
    }
    return cnt;
}
int main()
{
    for(unsigned int i = 2; i<= 1000; ++i){
        int ni = compute_steps(i);
        printf("%d %d %d\n", i, ni, ni-i*i);
    }
}
