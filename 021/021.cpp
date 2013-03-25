#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    int nmax = 10000;
    vector<int> vn;
    vn.resize(nmax+1, 1);
    for( int i =2; i<= nmax/2; ++i){
        for(unsigned int j = 2*i; j < vn.size(); j += i){
            vn[j] += i;
        }
    }
    int sum = 0;
    for(unsigned int i = 2; i < vn.size(); ++i){
        int value = vn[i];
        if(value  <= i) continue;
        if(vn[value] == i)
            sum += value + i;
    }
    printf("%d\n", sum);
}
