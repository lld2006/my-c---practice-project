#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

int square(int num, vector<int>& sqvec)
{
    if(sqvec[num] != -1) {
        return sqvec[num];
    }else if(num == 89 || num ==1)
    {
        return num;
    }
    int n1 = num;
    int sum = 0;
    while(n1)
    {
        int res = n1%10;
        sum += res * res;
        n1 /= 10;
    }
    sqvec[num] = square(sum, sqvec);
    return sqvec[num];
}

int main()
{
    vector<int> sqvec;
    sqvec.resize(10000000, -1);
    sqvec[1] = 1;
    sqvec[89] = 89;
    for(int i = 1 ; i < 10000000; ++i)
        square(i, sqvec);
    int count = 0;
    // 0 is intentionally wasted
    for(int i = 1; i < 10000000; ++i)
    {
        if(sqvec[i] == -1) printf("error %d\n", i);
        assert(sqvec[i] != -1);
        if(sqvec[i] == 89) ++count;
    }
    printf("%d\n", count);
}
