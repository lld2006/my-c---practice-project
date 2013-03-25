#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

int main()
{
    vector<int> fvec;
    fvec.resize(3000, 0);
    map<int, int> square;
    for( int i = 1; i<= 1000;++i)
        square.insert(pair<int, int>(i*i, i));

    for(int j = 1000; j >= 5; --j){
        int maxk = (double) j / sqrt(2.0);
        for( int k = 1; k <= maxk; ++k){
            int diff = j * j - k * k;
            assert( diff >= 0 );
            map<int, int>::iterator iter;
            if((iter = square.find(diff)) != square.end()) {
                int nx = iter->second;
                int sum = j + k + nx;
                assert(sum < 3000);
                ++fvec[sum];
            }
        }
    }
    int max = 0, num;
    for(int i = 0; i <= 1000;++i) {
        if( fvec[i] > max ) {
            max = fvec[i];
            num = i;
        }
    }
    printf("%d %d\n", max, num);
    return 0;
}

