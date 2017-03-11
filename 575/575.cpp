//observe the pattern of n = 5 n =6 will help a great deal for n= 1000
#include<cstdio>
#include<vector>
using namespace std;
int main()
{
    vector<int> vn;
    vn.resize(3, 0);
    int nmax = 1000;
    for(int i = 1 ; i <= nmax; ++i){
        int val = i * i - 1;
        int x = val / nmax;
        int y = val % nmax;
        bool xside = false, yside = false;
        if(x == 0 || x == nmax - 1)  xside = true;
        if(y == 0 || y == nmax - 1)  yside = true;
        if(xside && yside ) 
            ++vn[0];
        else if(xside || yside)
            ++vn[1];
        else
            ++vn[2];
    }
    double v1 = 1.0/(nmax*(nmax-1));
    double v2 = 1.0/((5*nmax-4)*nmax);
    vector<double> va = {0.5*v1, 0.75*v1, v1};
    vector<double> vb = {3*v2, 4*v2, 5*v2};
    double nf = va[0]*vn[0]+vn[1]*va[1]+vn[2]*va[2];
    nf += vb[0]*vn[0]+vn[1]*vb[1]+vn[2]*vb[2];
    printf("%15.13f\n", nf/2);
}
