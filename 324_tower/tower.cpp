#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include "../lib/typedef.h"
using namespace std;
//first, I thought this problem is the same as problem 161. 
//But I was wrong, there are some subtle difference between 
//these two problems. That is why I need to change my code. 
//first I think the state is related with one level only. but 
//actually it related to two levels.
//
//this function tells us whether this position is occupied
//or it is empty
typedef vector<vector<i64>> Matrix;
vector<vector<i64>> vn;
i64 nmod = 100000007LL;

int isOccupied(int num, int x, int y)
{
    assert(x>= 0 && x < 3);
    assert(y>= 0 && y < 3);
    int pos = y * 3 + x;
    int btest = 1<<pos;
    return num & btest;
}
void state_transition(int nc, int gridn, int n0) 
{
    assert(gridn <= 9 && gridn >= 0);
    if(gridn == 9) {
        //new state is ready to be processed
        int n1 = nc>>9;
        ++vn[n0][n1];
        return;
    }
    int xi = gridn % 3;
    int yi = gridn /3;
    if(isOccupied(nc, xi, yi)){
        state_transition(nc,gridn+1, n0);
        return;//lesson, when the rest of the codes are 
        //no need to be executed, do not miss a return!!!
    }
    if(xi < 2 && !isOccupied(nc, xi+1, yi)) {//insert in x direction
        int nc1 = nc;
        nc1 |= 1<< gridn; //mark these two are occupied
        nc1 |= 1<< (gridn+1);
        state_transition(nc1, gridn+2, n0);
    }
    //y direction
    if(yi < 2 && !isOccupied(nc, xi, yi+1)){
        int nc1 = nc;
        nc1 |= 1<<gridn;
        nc1 |= 1<<(gridn+3);
        state_transition(nc1, gridn+1, n0);
    }
    //if this position is empty, we can always try 
    //z direction
    int nc1 = nc | (1<<(gridn+9));
    state_transition(nc1, gridn+1, n0);
}
//mat1 * mat2 == mat3//square matrix
void mat_mult(const Matrix& mat1, const Matrix& mat2, Matrix& mat3)
{
    unsigned int matsize = mat1.size();
    mat3.clear();
    mat3.resize(matsize);
    for(unsigned int i = 0; i < matsize; ++i)
        mat3[i].resize(matsize, 0);
    
    for(unsigned int i = 0; i < matsize; ++i){
        for(unsigned int j= 0; j < matsize; ++j){
            if(mat1[i][j] == 0) continue;
            for(unsigned int k =0; k < matsize; ++k){
                mat3[i][k] += mat1[i][j] * mat2[j][k];
                mat3[i][k] %= nmod;
            }
        }
    }
}

//vbin is from low to high order
//bad name, same name different meaning vn with global vn!!!
void convert_number_to_binary(vector<int>& vn, vector<short>& vbin)
{
    vbin.clear();
    vector<int> vn1;
    vn1.reserve(vn.size());
    while(!vn.empty()){
       vn1.clear();
       int val = vn[0];
       int quote = val/2;
       int res = val & 1;
       if(val>1)
           vn1.push_back(quote);
       for(unsigned int i = 1; i < vn.size(); ++i){
            val = res*10+vn[i];
            quote = val/2;
            res = val & 1;
            vn1.push_back(quote);
       }
       vbin.push_back(res);
       vn.swap(vn1);
    }
}
int main()
{
    unsigned int nstate = 512; 
    vn.resize(nstate);
    for(unsigned int i = 0; i < nstate; ++i){
        vn[i].resize(nstate, 0);
    } 
    for(unsigned int i = 0; i < nstate; ++i)
        state_transition(i, 0, i);
    //now all the states are available 
    vector<int> flags, vstack, vlink;
    flags.resize(nstate, 0);
    vstack.push_back(0);
    while(!vstack.empty()){
        int row = vstack.back();
        vstack.pop_back();
        flags[row] = 1; 
        for(unsigned int i = 0; i< vn.size(); ++i) {
            if(vn[row][i] && flags[i]==0)
                vstack.push_back(i); 
        }
    }
    for(unsigned int i =0; i<flags.size(); ++i){
        if(flags[i])
            vlink.push_back(i);
    }
    printf("reduced mat size is %zu\n", vlink.size());
    
    Matrix vn1;
    vn1.resize(vlink.size());
    for(unsigned int i = 0; i < vn1.size(); ++i){
        vn1[i].resize(vlink.size(), 0);
        int row = vlink[i];
        for(unsigned int j = 0; j < vn1.size(); ++j){
            int col = vlink[j];
            vn1[i][j] = vn[row][col];
        }
    }

    Matrix b1;
     
    vn.clear(); flags.clear(); vlink.clear(); vstack.clear();
    vn1.swap(vn);
    Matrix bmat(vn);
    

    vector<int> vnum;
    vector<short> vbin;
    vnum.resize(9,0);    
    vnum[0] = 1;
    vnum[8] = 6;
    convert_number_to_binary(vnum, vbin);

    Matrix result, rt;
    result.resize(bmat.size());
    for(unsigned int i = 0; i < bmat.size(); ++i){
        result[i].resize(bmat.size(), 0);
        result[i][i]=1;
    }
    printf("binary size is %zu \n ", vbin.size());
    for(unsigned int i=0; i < vbin.size(); ++i){
        if(i%1000==0)
            printf("%d\n", i);
        if(vbin[i] == 0) {
            mat_mult(bmat, bmat, b1);
            b1.swap(bmat);
        }else{
            mat_mult(result, bmat, rt);
            mat_mult(bmat, bmat, b1);
            b1.swap(bmat);
            result.swap(rt);
        }
    }
    printf("%lld\n", result[0][0]);
}   

