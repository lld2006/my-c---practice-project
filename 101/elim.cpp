# include <cstdio>
#include <cassert>
#include <vector>
using namespace std;
int index(int n, int i, int j){
    return  i*n+j;
}

long long power(int base, int exp)
{
    long long ret = 1;
    for(int i= 0; i< exp; ++i)
        ret *= base;
    return ret;
}
//n(n-1)(n^8+n^6+n^4+n^2+1)+1
long long f(int n){
    //return n*n*n;
    return (1+(power(n, 8)+power(n,6)+power(n, 4)+power(n,2)+1)*(n-1)*n);
}
long long g(int n, vector<long long>& sol){
    long long sum =0;
    for(int i = 0; i < static_cast<int>(sol.size()); ++i){
        sum += sol[i]*power(n, i);
    }
    return sum;
}
void initMatrix(int ith, vector<long long>& matrix, vector<long long>& rhs, vector<long long>& sol){
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
void gauss_elimination(int n, vector<long long>& A){
    assert(static_cast<int>(A.size()) == n * n);
    for(int i = 0; i < n; ++i){
        long long diag = A[index(n, i, i)];
        //for(int k = i+1; k < n ; ++k){
        //    assert(A[index(n,i,k)]%diag ==0);
        //    A[index(n, i, k)] /= diag;
        //}
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
void LU(vector<long long>& A, vector<long long>& rhs, vector<long long>& sol){
    //forward
    int size = rhs.size();
    assert(rhs.size() == sol.size());
    assert(static_cast<int>(A.size()) == size * size);
    vector<long long> y(rhs);
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
    vector<long long> matrix;
    vector<long long> rhs;
    vector<long long> sol;
    long long diff = 0;
    for(int i = 1; i<= nth; ++i){
        initMatrix(i, matrix, rhs, sol);
        gauss_elimination(i, matrix);
        LU(matrix, rhs, sol);
        diff += g(i+1, sol);
    }
    printf("%I64d\n", diff);
}
