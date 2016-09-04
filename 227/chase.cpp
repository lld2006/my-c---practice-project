#include <cstdio>
#include <vector>
using namespace std;
int main(){
    //the first dimension of mat is original dist and 
    //the second dimension of mat is final distance.
    vector<vector<double> > mat;
    vector<double> rhs;
    mat.resize(51);
    rhs.resize(51, 36);
    for(unsigned int i = 0; i<mat.size(); ++i)
        mat[i].resize(51, 0);
    
    double x1 = -1;
    double x2 = -8; 
    for(int i = 1; i <= 50; ++i){
        //n n
        mat[i][i] += 18; //keep the same distance
        //n-2
        if(i-2<0)
            mat[i][2-i]+=x1;
        else if(i-2>0)
            mat[i][i-2]+=x1;//decrement by 2

        //n+2 i-2==0 --> no value in equation
        if(i+2<=50)
            mat[i][i+2]+=x1;
        else
            mat[i][98-i]+=x1;

        //n-1
        if(i-1>0)
            mat[i][i-1]+=x2;//distance decrement by 1

        //n+1
        if(i+1<=50)
            mat[i][i+1]+=x2;//distance increment by 1
        else
            mat[i][99-i]+=x2;
    }
    for(unsigned int i = 1; i< mat.size()-1;++i){
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
    printf("%30.20f\n", rhs[50]/mat[50][50]);
}
