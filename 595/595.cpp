#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
/*  
vector<int> test_count(int n)
{
    vector<int> vn(n);
    vector<int> result(n+1, 0);
    for(int k = 0; k<n; ++k){
        vn[k] = k+1;
    }
    do{
        int group = 1; 
        bool flag = false;
        for(int i= 1; i< (int)vn.size(); ++i ){
            if(vn[i]!=vn[i-1]+1){
            //    if(!flag){
            //        ++count;
            //        flag = true;
            //    }
            //}else{
                ++group;
            }
        }
        ++result[group];
    }while(next_permutation(vn.begin(), vn.end()));
    return result;
}
*/
int main()
{
    //for(int i = 2; i<= 10; ++i){
    //    printf("======= %d ========\n", i);
    //    vector<int> result = test_count(i);
    //    for(int j = 1; j< (int)result.size(); ++j)
    //        printf("%d %d\n", j, result[j]);
    //}
    //count in each category
    int nmax= 52;
    vector<vector<double>> vn;
    vn.resize(nmax+1);
    for(int i = 1; i<=nmax;++i ){
        vn[i].resize(nmax+1, 0);
    }
    for(int i = 1; i<= nmax; ++i){
        vn[i][1] = 1;
    }
    double nfac = 2;
    for(int j = 2; j<=nmax; ++j){
        double sum = 0;
        for(int i = 1; i< j; ++i){
            sum += vn[j][i];
        }
        double coeff = nfac - sum;
        vn[j][j]=coeff;
        nfac *= (j+1);//(j+1)!
        double bino = 1;
        for(int k = j+1; k<= nmax; ++k){
            bino *= k-1;
            bino /= k-j;
            vn[k][j] = bino*coeff;
        }
    }
    vector<double> sols;
    sols.resize(nmax+1, 0); //s1 s21 s321
    sols[1] = 0;
    nfac = 1;
    for(int i = 2; i<=nmax; ++i){
        nfac *= i;
        double sum = nfac;
        for(int k = 1; k<i; ++k){
            sum += vn[i][k]*sols[k];
        }
        sols[i] = (sum)/(nfac-vn[i][i]);
        printf("%d %15.10f\n", i, sols[i]-1);
    }
    
}
