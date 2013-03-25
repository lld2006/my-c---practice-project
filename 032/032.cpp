#include <cstdio>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;

bool isPandigital(int a, int b, int c)
{
    vector<int> flags;
    flags.resize(10,0);
    int n = a;
    while(n > 0){
        int res = n % 10;
        if(res == 0) 
            return false;
        if(flags[res] == 0){
            flags[res] = 1;
        }else{
            return false;
        }
        n/= 10;
    }
    n = b;
    while(n > 0){
        int res = n % 10;
        if(res == 0) 
            return false;
        if(flags[res] == 0){
            flags[res] = 1;
        }else{
            return false;
        }
        n/= 10;
    }
    n = c;
    while(n > 0){
        int res = n % 10;
        if(res == 0) 
            return false;
        if(flags[res] == 0){
            flags[res] = 1;
        }else{
            return false;
        }
        n/= 10;
    }
    int sum = accumulate(flags.begin(), flags.end(), 0);
    return (sum == 9);
}
int main(int argc, const char *argv[])
{
    vector<int> vprod;
    for( int i = 1234; i <=9876; ++i){
        int nmax = sqrt(i);
        for( int fac1 = 2; fac1 <=nmax; ++fac1){
            int fac2 = i / fac1;
            if(fac1 *fac2!= i) continue;
            if(isPandigital(i, fac1, fac2)){
                vprod.push_back(i);
                break;
            }
        }
    }    
    int sum = accumulate(vprod.begin(), vprod.end(), 0);
    printf("%d\n", sum);
    return 0;
}
