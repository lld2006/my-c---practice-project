#include <cstdio>
#include <vector>
using namespace std;
bool isSumAbundant(int num, vector<int>& vd)
{
    for( int i = 1; i<= num/2; ++i){
        if(vd[i] > i && vd[num-i] > num -i)
            return true;
    }
    return false;
}
int main()
{
    int nmax = 28123;
    vector<int> vd;
    vd.resize(28123, 1);
    vd[1]= 0;
    int nl = nmax/2;
    for(int i = 2; i <=nl; ++i ){
        for(unsigned int j = 2*i; j < vd.size(); j += i) {
            vd[j] += i;
        }
    }
    int sum = 0;
    for( int j = 1 ; j <= nmax; ++j){
        if(!isSumAbundant(j, vd))
            sum += j;
    }
    printf("%d\n", sum);
}
