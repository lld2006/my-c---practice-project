#include "../lib/typedef.h"
#include <set>
#include <map>
#include <cstdio>
#include <cassert>
#include <algorithm>
extern "C"
{
    void dgetrf_(int* M, int* N, double* A, int* LDA, int* IPIV, int* INFO);
    void dgetrs_(char* TRANS, int* N, int* NRHS, double* A, int* LDA, int* IPIV, double* B, int* LDB, int* INFO);
}
set<i64> stateset;
//let me give each state an index for matrix factor and solve
map<int, int> indexmap;
int gindex = 0;
i64 get_current_number(const vector<int>& states)
{
    i64 ret = 0;
    for(unsigned int i = 0; i < states.size(); ++i){
        ret <<= 4;
        ret += states[i];
    }
    //not necessary to create so many final states
    if(ret < 16) return 1;
    return ret;
}
vector<int> get_vector(i64 num)
{
    vector<int> vn;
    while(num){
        int n1 = num;
        n1 &= 15;
        vn.push_back(n1);
        num >>= 4;
    }
    assert(vn.size() <= 4);
    while(vn.size() < 4){
        vn.push_back(0);
    }
    reverse(vn.begin(), vn.end());
    return vn;
}
void create_states(vector<int>& states)
{
    int n0 = get_current_number(states);
    if(n0 <= 1) return;
    for(unsigned int i =0; i< states.size(); ++i){
        if (states[i] ==0) continue;
        --states[i];
        for(unsigned int j = i+1; j<states.size(); ++j){
            ++states[j];
        }
        int n1 = get_current_number(states);
        auto r1 = indexmap.insert(IntPair(n1, gindex));
        if(r1.second) ++gindex;
        i64 nstate = (n0<<16)+n1;
        //printf("%d %d %lld\n", n0, n1, nstate);
        auto ret = stateset.find(nstate);
        if(ret == stateset.end()){
            stateset.insert(nstate);
        }
        create_states(states);
        //revert the vector back to original state, save vector creation
        for(unsigned int j = i+1; j < states.size(); ++j){
            --states[j];
        }
        ++states[i];
    }
}
int index0(int row, int col, int dim)
{
    return (row*dim+col);
}
void debugset(set<i64>& sset)
{
    for(auto iter = sset.begin(); iter != sset.end(); ++iter)
        printf("%lld\n", *iter);
}
int main()
{
    //states means A2 A3 A4 A5
    vector<int> vstates = {1,1,1,1};
    int nx = get_current_number(vstates);
    indexmap.insert(IntPair(nx, gindex++));
    create_states(vstates);
    int matsize = indexmap.size();
    printf("states %d\n", matsize);
    vector<double> mat;
    vector<double> rhs;
    mat.resize(matsize*matsize, 0);
    rhs.resize(matsize, 0);
    for( int i = 0; i < matsize; ++i){
        mat[index0(i, i, matsize)] = 1.0;
    }

    for(auto iter = stateset.begin(); iter !=stateset.end(); ++iter){
        i64 value = *iter;
        i64 n1 = (value >> 16); //higher 16 bit, initial state
        i64 n2 =  value - (n1<<16); //lower 16 bits, final state
        if(n1 == 1) continue;
        assert(n1 > 15);
        auto iter = indexmap.find(n1);
        assert(iter != indexmap.end());
        int idxa = iter->second;
        iter = indexmap.find(n2);
        assert(iter != indexmap.end());
        int idxb = iter->second;
        vector<int> va = get_vector(n1);
        vector<int> vb = get_vector(n2);
        int nx = 0;
        for(nx = 0; nx < static_cast<int>(va.size()); ++nx){
            if(va[nx] == vb[nx] + 1)
                break;
        }
        assert(va[nx] = vb[nx] + 1);
        int total = accumulate(va.begin(), va.end(), 0);
        assert(va[nx] <= total);
        mat[index0(idxa, idxb, matsize)] = -(double) va[nx]/total;
        if(total == 1 && nx != 3)
            rhs[idxa] = 1;
    }
    vector<int> ipiv;
    int info = 0;
    ipiv.resize(matsize, 0);
    dgetrf_(&matsize, &matsize, &mat[0], &matsize, &ipiv[0], &info );
    assert(info==0);
    char trans='T';
    int nrhs = 1;
    dgetrs_(&trans, &matsize, &nrhs, &mat[0], &matsize, &ipiv[0], &rhs[0], &matsize, &info);
    printf("%20.10f\n", rhs[0]);
}
