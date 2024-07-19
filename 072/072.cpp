#include "../lib/tools.h"
#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;
int main()
{
    int target = 100000000;
    vector<int> vtot = totient_sieve(target);
    i64 total = accumulate(vtot.begin(), vtot.end(), 0LL) - 1;
    printf("%lld\n", total);
}
