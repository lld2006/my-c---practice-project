#include <cstdio>
#include <unordered_set>
#include <set>
using namespace std;
int pan(int num)
{
    return num*(3*num-1)/2;
}
int main()
{
    int nmax = 10000;
    unordered_set<int> nset;
    //set<int> nset;
    for(int i = 1; i <=nmax; ++i)
        nset.insert(pan(i));

    for(int i = 1; i<nmax;++i){
        int pi = pan(i);
        //let pi the minimum difference
        for(int j = 1; j<nmax;++j){
            int pj = pan(j);
            if(nset.find(pi+pj) == nset.end()) continue;
            if(nset.find(pi+2*pj)!= nset.end()){
                printf("i=%d %d j=%d %d %d\n",i, pi,j, pj, pi+2*pj);
                return 0;
            }
        }
    }
}
