
#include <cassert>
#include <cstdio>
#include "../lib/typedef.h"
i64 neville(int x, int i, int j, vector<i64>& p, int order, vector<i64>& y)
{
    assert(i <= 10);
    if(i == j){
        p[(i-1)*order+j-1] = y[i];
        return y[i];
    }
    if(p[i*order+j] > 0)
        return p[(i-1)*order+j-1];
    else{
        i64 value = (j-x)*neville(x, i, j-1, p, order, y) +
            (x-i) * neville(x, i+1, j, p, order, y);
        assert((value % (j-i)) == 0);
        value /= (j- i);
        p[(i-1)*order+j-1] = value;
        return value;
    }

}
i64 f(i64 n)
{
    i64 sum = 0;
    for(int i = 0; i <= 10; ++i){
        sum *= -n;
        sum += 1;
    }
    return sum;
}
int main()
{
    i64 sum = 0;
    vector<i64> vy;
    for(unsigned int i = 0; i <= 10; ++i)
        vy.push_back(f(i));
    
    vy.resize(10, 0);
    for(i64 i = 1; i <= 10; ++i ){
        vector<i64> vp;
        vp.resize((i+1)*(i+1), 0);
        i64 val= neville(i+1, 1, i, vp, i, vy);
        sum += val;
        printf("%lld\n", val);
    }
    printf("%lld\n", sum);
}
