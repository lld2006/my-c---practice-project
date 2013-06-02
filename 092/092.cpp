#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

int square_sum(int num);
int square(int num, vector<int>& sqvec)
{
    if(sqvec[num] != -1) {
        return sqvec[num];
    }else if(num == 89 || num ==1)
    {
        return num;
    }
    int sum = square_sum(num);
    sqvec[num] = square(sum, sqvec);
    return sqvec[num];
}

int square_sum(int num)
{
    int sum = 0;
    while(num){
        int res = num % 10;
        sum += res * res;
        num /= 10;
    }
    return sum;
}

int main()
{
    vector<int> sqvec;
    sqvec.resize(568, -1);
    sqvec[1]= 1;
    sqvec[89]=89;
    for(int i = 1 ; i <= 81*7; ++i)
        square(i, sqvec);
    int count = 0;
    for(int i = 1; i < 10000000; ++i) {
        int nx = square_sum(i);
        count += (sqvec[nx] == 89);
    }
    printf("%d\n", count);
}
