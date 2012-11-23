#include <cstdio>
#include <vector>
//this is a simple problem but numbers are large use mathematica
using namespace std;
vector<int> vc;
int vinit = -1000000000;
i64 a = 1801088541LL;
i64 b = ;
i64 c = 40;
int C(int n)
{
    if( n > 2000)
        return n - c;
    int val = C(a+C(a+C(a+C(a+n))));
    vc[n] = val;
    return val;
}
int main()
{
}
