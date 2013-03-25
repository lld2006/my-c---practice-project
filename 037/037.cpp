#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
bool check_circular_prime(int num, vector<int>& flags){
    int nx = num;
    int rev = 0;
    int shift = 1;
    while(nx){
        if(!flags[nx])
            return false;
        int res = nx % 10;
        rev += shift*res;
        shift *= 10;
        if(!flags[rev])
            return false;
        nx /= 10;
    }
    return true;
}
int main()
{
    int target = 1000000;
    vector<int> flags;
    flags.resize(target + 1, 1);
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 1;
    int root = round(sqrt(target));
    for( int i = 2; i <= root; ++i){
        if(!flags[i]) continue;
        for(unsigned int j = 2*i; j< flags.size(); j+=i){
            flags[j] = 0;
        }
    }
    int total = 0;
    for(unsigned int i = 11; i < flags.size(); ++i){
        if(!flags[i]) continue;
        if(check_circular_prime(i, flags)){
            printf("%d\n", i);
            total += i;
        }
    }
    printf("%d\n", total);
}
