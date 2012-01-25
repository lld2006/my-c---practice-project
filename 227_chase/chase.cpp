#include <cstdio>
#include <vector>
using namespace std;
int main(){
    vector<vector<double> > mat;
    vector<double> rhs;
    mat.resize(50);
    rhs.resize(50, 36);
    for(unsigned int i = 0; i<mat.size(); ++i){
        mat[i].resize(50, 0);
    }
    double x1 = -(double)1;
    double x2 = -(double)8;
    for(int i = 1; i <= 50; ++i){
        //n n
        mat[i-1][i-1] += 18;
        //n-2
        if(i-2<0)
            mat[i-1][1-i]+=x1;
        else if(i-2>0)
            mat[i-1][i-3]+=x1;
        //n+2 i-2==0 --> no value in equation
        if(i+2<=50)
            mat[i-1][i+1]+=x1;
        else
            mat[i-1][97-i]+=x1;

        //n-1
        if(i-1>0)
            mat[i-1][i-2]+=x2;

        //n+1
        if(i+1<=50)
            mat[i-1][i]+=x2;
        else
            mat[i-1][98-i]+=x2;
    }
    for(unsigned int i = 0; i< mat.size()-1;++i){
        for(unsigned int j = i+1; j<mat.size();++j){
            if(mat[j][i] == 0) 
                continue;
            double ratio = -mat[j][i]/mat[i][i];
            rhs[j] += ratio * rhs[i];
            for(unsigned int k = i+1; k < mat.size(); ++k){
                mat[j][k] += ratio * mat[i][k];
            }
        }
    }
    printf("%30.20f\n", rhs[49]/mat[49][49]);
}
