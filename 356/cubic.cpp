#include <cstdio>
#include <cmath>
#include "../lib/typedef.h"
using namespace std;
i64 nmod = 100000000LL;
//finally I solved it!!!
void mat_mult(const vector<i64>& mat1, const vector<i64>& mat2, vector<i64>& result, int dim)
{
    result.clear();
    result.resize(dim*dim , 0);
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim; ++j){
            for(int k = 0; k < dim; ++k){
                result[i*dim+k] += mat1[i*dim+j] * mat2[j*dim+k];
                result[i*dim+k] %= nmod;
            }
        }
    }
}

void mat_power(const vector<i64>& mat, vector<i64>& result, i64 npow)
{
    vector<i64> base(mat);
    vector<i64> base1, result1;
    result.clear();
    result.resize(9, 0);
    result[0] = 1;
    result[4] = 1;
    result[8] = 1;
    while(npow > 0){
        if(npow % 2== 1){
            mat_mult(base, result, result1, 3);
            result.swap(result1);
        }
        mat_mult(base, base, base1, 3);
        base.swap(base1);
        npow /= 2;
    }
}

int main()
{
    int nmax = 30;
    int npow= 987654321;
    //npow = 123456789;
    i64 sum = 0;
    for( int i = 1; i <=nmax; ++i){
    //for( int i = 2; i <=2; ++i){
        vector<i64> vn;
        vector<i64> rhs;
        vector<i64> result;
        vn.resize(9, 0);
        rhs.resize(3, 0);
        i64 s1 = 1LL<<i; //x+y+z
        i64 s3 = -i; //x*y*z
        rhs[2] = s1;
        rhs[1] = (s1 * s1) % nmod;
        rhs[0] = rhs[1] * s1 - 3 * i;
        rhs[0] %= nmod;
        vn[0] = s1;
        vn[2] = s3;
        vn[3] = 1;
        vn[7] = 1;
        mat_power(vn, result, npow-3);
        sum += result[0]*rhs[0]+result[2]*rhs[2]+result[1]*rhs[1]-1;
    }
    sum %= nmod;
    if(sum < 0)
        sum += nmod;
    printf("%lld\n", sum);
}
