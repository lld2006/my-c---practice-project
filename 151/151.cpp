#include <cstdio>
#include <vector>
using namespace std;
int dim = 16;
vector<double> vp;
double get(int i, int j, int k, int l, int dim)
{
    int total = i+j+k+l;
    int pos =  (((i*dim+j)*dim)+k)*dim+l;
    if(total == 1){
        if(i==1) return 1.0+get(0,1,1,1,dim);
        if(j==1) return 1.0+get(0,0,1,1,dim);
        if(k==1) return 2.0;
        if(l==1) return 1.0;
    }

    double prob = 0.0;
    if(vp[pos] < 0) {
        if(i) prob += (double)i/total * get(i-1, j+1, k+1, l+1, dim);
        if(j) prob += (double)j/total * get(i, j-1, k+1, l+1, dim);
        if(k) prob += (double)k/total * get(i, j, k-1, l+1, dim);
        if(l) prob += (double)l/total * get(i, j, k, l-1, dim);
        vp[pos] = prob;
        //printf("%d %d %d %d %20.10f\n", i,j,k, l, prob);
        return prob;
    }else{
        return vp[pos];
    }
}
int main()
{
    vp.resize(65536, -1.0);
    double prob = get(1,1,1,1,dim);
    printf("%20.10f\n", prob);
}
