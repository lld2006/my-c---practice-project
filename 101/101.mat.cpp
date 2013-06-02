# include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
int index(int n, int i, int j){
    return  i*n+j;
}

//n(n-1)(n^8+n^6+n^4+n^2+1)+1
i64 f(i64 n){
    //return n*n*n;
    return (1+(power(n, 8LL)+power(n,6LL)+power(n, 4LL)+power(n,2LL)+1)*(n-1)*n);
}
i64 g(int n, vector<i64>& sol){
    i64 sum =0;
    for(int i = 0; i < static_cast<int>(sol.size()); ++i){
        sum += sol[i]*power(n, i);
    }
    return sum;
}
void initMatrix(int ith, vector<i64>& matrix, vector<i64>& rhs, vector<i64>& sol){
    sol.resize(ith, 0);
    rhs.resize(ith, 0);
    matrix.resize(ith* ith, 0);
    for(int i = 0; i<ith; ++i)
         rhs[i]=f(i+1); 
    
    for(int i =0 ; i < ith; ++i)
        for(int j = 0; j< ith; ++j){
            matrix[index(ith, i,j )]= power((i+1), j);
        }
}
void gauss_elimination(int n, vector<i64>& A){
    assert(static_cast<int>(A.size()) == n * n);
    for(int i = 0; i < n; ++i){
        i64 diag = A[index(n, i, i)];
        for(int j = i+1; j < n; ++j){
            //first find the aji/aii
            assert(A[index(n, j, i)] % diag == 0);
            A[index(n, j, i)] /= diag;
            //update jth row
            for(int k = i+1; k<n; ++k){
                A[index(n, j, k)] -= A[index(n, j, i)] * A[index(n,i,k)];
            }
        }
    }
}
void LU(vector<i64>& A, vector<i64>& rhs, vector<i64>& sol){
    //forward
    int size = rhs.size();
    assert(rhs.size() == sol.size());
    assert(static_cast<int>(A.size()) == size * size);
    vector<i64> y(rhs);
    //diagonal belongs to upper triangle matirx
    for(int i = 0 ; i < size; ++i){
        for(int j = 0; j < i; ++j){
            y[i]-= A[index(size, i,j)] * y[j];
        }
    }
    //backward
    for(int i = size -1 ; i>=0; --i){
        for(int j = size - 1; j > i; --j){
            y[i] -= A[index(size, i, j)] * sol[j];
        }
        sol[i] = y[i]/A[index(size, i, i)];
    }
}
int main(){
    int nth  = 10;
    vector<i64> matrix;
    vector<i64> rhs;
    vector<i64> sol;
    i64 diff = 0;
    for(int i = 1; i<= nth; ++i){
        initMatrix(i, matrix, rhs, sol);
        gauss_elimination(i, matrix);
        LU(matrix, rhs, sol);
        i64 val = g(i+1, sol);
        printf("%lld\n", val);
        diff += val;
    }
    printf("%lld\n", diff);
}
