#include <cstdio>
#include <vector>
#include "../lib/tools.h"
#include <numeric>

using namespace std;

bool pseqlen(int i, const vector<int>& prime, const vector<int>& fvec)
{
    int sqint2 = 2, sint = 1; 
    while(sqint2 < i ){
        if(fvec[i-sqint2] == 1)return true;
        ++sint;
        sqint2 = 2* sint*sint;
    }
    return false;
}


int main()
{
    vector<int> prime;
    primeWithin( prime, 1000000);   
    vector<int> fvec;
    fvec.resize(1000001, 0);
    for(unsigned int i =0 ; i < prime.size(); ++i){
        fvec[prime[i]] = 1;
    }
    for(unsigned int i = 9; i ; i+=2){
        if(fvec[i]==1)continue;
        if( ! pseqlen(i,prime, fvec)) {
            printf(" %d\n",i);
            break ;
        }
    }
    return 0 ;
}
