#include <cstdio>
#include <cstdlib>
#include <vector>
#include <numeric>
#include "../lib/tools.h"
#include "./pcf.h"
using namespace std;
//prime counting function
//generating pcf in a small range
//prime counting function in a larger range using combinatoric
//algorithm 

int main()
{
    primeCountingFunction pcf(1000);
    printf("%lld\n", pcf.compute(1000));
}
