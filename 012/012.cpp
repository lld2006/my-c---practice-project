#include <cstdio>
#include <vector>
using namespace std;

void divisor_sieve(vector<int>& dtable, int limit)
{
    dtable.clear();
    dtable.resize(limit+1, 1);
    for( int step = 2; step <=limit; ++step)
        for(unsigned int j = step; j < dtable.size(); j += step){
            ++dtable[j];
        }
}
int main()
{
    int limit = 20000;
    vector<int> dtable;
    divisor_sieve(dtable, limit);
    int nd = 0;
    for(int i = 3; i < limit; ++i) {
        if(i  & 1) 
            nd = dtable[i] * dtable[(i+1)/2];
        else
            nd = dtable[i/2] * dtable[i+1];
        if(nd > 500){
            printf("%d %d %d\n",i, i*(i+1)/2, nd);
            break;
        }
    }
}

