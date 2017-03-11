#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/int.h"
using namespace std;

vector<i64> matrix_multiplication(const vector<i64>& A, const vector<i64>& B, i64 nmod, int size);

vector<i64> matrix_power(vector<i64> A, i64 np, i64 nmod)
{
    vector<i64> base(A);
    vector<i64> result;
    result.resize(4, 0);
    result[0]= result[3]= 1;
    while(np){
        if(np &1){
            result = matrix_multiplication(result, base, nmod, 2);
        }
        base = matrix_multiplication(base, base, nmod, 2);
        np >>= 1;
    }
    return result;
}

i64 mult(i64 x, i64 y, i64 nmod)
{
    GeneralInteger gx(x);
    GeneralInteger gy(y);
    GeneralInteger gmod(nmod);

    GeneralInteger gz(0LL), gq(0LL), gr(0LL);
    gz = gx.multiply(gy);
    gq = gz.divide(gmod, gr);
    //assert(gr.to_i64() == (x*y)%nmod);
    return gr.to_i64();
}
vector<i64> matrix_multiplication(const vector<i64>& A, const vector<i64>& B, i64 nmod, int size)
{
    //A11 0 A12 1 A21 2 A22 2
    assert(size == 2);
    vector<i64> result;
    result.resize(4, 0);
    //result[0] = A[0] * B[0] +A[1] * B[2];
    //result[1] = A[0] * B[1] + A[1] * B[3];
    //result[2] = A[2] * B[0] + A[3] * B[2];
    //result[3] = A[2] * B[1] + A[3] * B[3];
    result[0] = mult(A[0], B[0], nmod) +mult(A[1], B[2], nmod);
    result[1] = mult(A[0], B[1], nmod) +mult(A[1], B[3], nmod);
    result[2] = mult(A[2], B[0], nmod) +mult(A[3], B[2], nmod);
    result[3] = mult(A[2], B[1], nmod) +mult(A[3], B[3], nmod);
    result[0] %= nmod;
    result[1] %= nmod;
    result[2] %= nmod;
    result[3] %= nmod;
    return result;
}
vector<i64> matrix_sum(const vector<i64>& A, const vector<i64>& B, int sign, i64 nmod)
{
    vector<i64> result;
    result.resize(4, 0);
    for(unsigned int i = 0; i < result.size(); ++i){
        result[i] = A[i] + sign * B[i];
        result[i] %= nmod;
    }
    return result;
}
i64 fn(i64 x, i64 limit, i64 nmod)
{
    vector<i64> A, A1;
    A.resize(4, x);
    A[0] = 0;
    vector<i64> result, result1;
    result.resize(4, 0);
    result[0]=result[3]= 1;
    i64 det = (1-x-x*x);
    i64 nmod1 = nmod*det;
    if(nmod1 < 0) nmod1 = -nmod1;
    result1 = matrix_power(A, limit, nmod1);

    //result1 = (Ax)^n
    --result1[0];
    --result1[3];
    //Ax*((Ax)^n-I)
    result = matrix_multiplication(A, result1, nmod1, 2);
    A1 = A;
    --A1[0]; --A1[3];
    swap(A1[0], A1[3]);
    A1[1]=-A[2];
    A1[2]=-A[1];
    result = matrix_multiplication(result, A1, nmod1, 2);
    assert(result[3] % det == 0);
    return (x*result[3]/det+x)% nmod;
}
int main()
{
    i64 sum = 0;
    i64 limit = 1000000000000000LL;
    i64 nmod = 1307674368000LL;
    //i64 value = fn(11, 7-1, nmod);
    //printf("test %lld\n", value);
    //return 0;
    for(int i = 1; i <= 100; ++i){
        i64 value = fn(i, limit-1, nmod);
        if(value < 0 ) value += nmod;
        assert(value >=0 && value < nmod);
        sum += value;
        sum %= nmod;
    }
    printf("%lld\n", sum);
}
