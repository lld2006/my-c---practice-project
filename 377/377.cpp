//need to build up all needed clue to solve the problem 
//
//but now let us think about the number that is something like 2a2b like 1122, then the result is still easy to understand. 
//each line, the sum is s, assume there is n_i of i, so n_1 + 2n_2 + 3n_3 +9n_9 = s.
//so the contribution is N= (n_1+n_2+n_9-1)/n_1!/.../n_9! * s, but the problem here is the number 13^17 is 10^18! what a headache! 
//
//I just figured out that probably most of the combinations have zero contribution since there are too many trailing zeroes! this might be wrong!
//
//another small thing is that the sum of these numbers should multiply 1111...1, number of 1 is n1+n2+...+n_9
//
//This is an easy problem, since it can be solved by matrix multiplication
//just consider recurrent equation
//
//on second thought, not that easy, because sum is needed. 
//It only asks for the last 9 digits of the number, 
//so I can make the sum depends only on the N

#include <cstdio>
#include <algorithm>
#include "../lib/tools.h"
i64 nmod = 1000000000LL;

//#define DEBUG
#ifdef DEBUG
#else
vector<i64> vmult;
void compute_multiplier_of_sum()
{
    vector<i64> vs;
    vector<i64>& vn(vmult);
    vn.resize(82, 0);
    vs.resize(82, 0);
    vs[0] = 1;
    int nc = 0;
    bool stop = false;
    while (!stop){
        stop = true;
        for(unsigned int j = 0; j < 9; ++j){
            if(vs[nc+j]) stop = false;
        }
        if(stop)
            break;
        i64 mult = vs[nc];
        vs[nc] = 0;
        for(i64 i =1;i<=9;++i){
            i64 t = multmod(mult, 10LL, nmod);
            vs[nc+i] = addmod(t, vs[nc+i], nmod);
            t = multmod(mult, i, nmod);
            vn[nc+i] = addmod(t, vn[nc+i], nmod);
        }
        ++nc;
    }
}
vector<i64> matrix_multiplication(const vector<i64>& A, const vector<i64>& B, i64 nmod, int dim)
{
    vector<i64> C;
    C.resize(dim*dim, 0);
    for( int i = 0; i<dim; ++i){
        for( int j = 0; j<dim; ++j){
            for( int k = 0; k<dim; ++k){
                C[i*dim+j] += multmod(A[i*dim+k], B[k*dim+j], nmod);
                C[i*dim+j] %= nmod;
            }
        }
    }
    return C;
}

vector<i64> matrix_power(vector<i64> A, i64 np, i64 nmod)
{
    vector<i64> base(A);
    vector<i64> result;
    result.resize(81, 0);
    for(unsigned int i = 0; i < 9; ++i)
    result[i*9+i]= 1;
    while(np){
        if(np &1){
            result = matrix_multiplication(result, base, nmod, 9);
        }
        base = matrix_multiplication(base, base, nmod, 9);
        np >>= 1;
    }
    return result;
}

i64 solve13(i64 nn)
{
    i64 n = nn - 73;
    //build the multiplication matrix
    vector<i64> A;
    A.resize(81, 0);
    for(unsigned int i = 0; i<9; ++i){
        A[i] = 1;
    }
    for(unsigned int i=1; i<9; ++i){
        A[i*9+i-1] = 1;
    }
    //initialize the first 9 N(n), 
    //actually N(n) = 2^(n-1) 
    vector<i64> rhs;
    rhs.resize(9); 
    for(unsigned int i = 0; i < rhs.size(); ++i){
        rhs[i] = 1<<(8-i);
    }
    vector<i64> B = matrix_power(A, n-9, nmod);
    vector<i64> v81;
    v81.resize(81 , 0);
    //i64 rf=0; // a lesson, when I use some old code
    // some times the initialization is missed!
    for(int i = 8; i>=0; --i){
        i64 rf = 0;
        for(int j =0; j<9; ++j){
            rf += multmod(B[i*9+j], rhs[j], nmod);
            rf %= nmod;
        }
        v81[8-i] = rf;
    }
    // now I have n-81 to n-73, now expand to n-1;
    assert(v81[8]> 0 && v81[9] == 0);
    for(int i =9; i< (int)v81.size(); ++i){
        //what a hideous error!!!! 0 is different to 0LL!!!!!
        v81[i] = accumulate(v81.begin()+i-9, v81.begin()+i, 0LL);
        v81[i] %= nmod;
    }
    reverse(v81.begin(), v81.end());
    //multiply and sum
    i64 sum = 0;
    for(int i = 1; i<= 81; ++i){
        i64 t = multmod(v81[i-1], vmult[i], nmod);
        sum = addmod(sum , t, nmod);
    }
    return sum;
}
int main()
{
    compute_multiplier_of_sum();
    //13 does not fit in my algorithm for large numbers, so let me
    //compute s13 separately.
    vector<i64> s13, n13;
    int nsize = 28561;
    s13.resize(nsize+1, 0);
    n13.resize(nsize+1, 0);
    s13[1] = 1;
    n13[1] = 1;
    for(int i = 2; i<(int)s13.size(); ++i) {
        int imax = i> 9? 9: i-1; 
        for(int k = 1; k<= imax; ++k){
            n13[i] += n13[i-k];
            s13[i] += multmod(s13[i-k], 10LL, nmod)+multmod(n13[i-k], (i64)k, nmod);
        }
        if(i <= 9) { //single digit contribution to n and sum
            n13[i]++; 
            s13[i] += i;
        }
        n13[i]%=nmod;
        s13[i]%=nmod;
    }
    i64 sum = s13[13];
    i64 prod = 13LL;
    for(i64 j= 2; j<=17; ++j){
        prod *= 13LL;
        i64 t = solve13(prod);
        sum += t;
        //printf("%lld %lld %lld\n",prod, t, sum );
    }
    printf("%lld\n", sum%nmod);
}
#endif
