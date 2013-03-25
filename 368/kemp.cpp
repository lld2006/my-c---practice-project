#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
double precision = 1e-18;
int npart = 20;
vector<vector<vector<double>>> vphi;
double alpha(int k, int w, int m)
{
    double prod = 1.0;
    int wf = w;
    if(w > k-1)
        wf = k-1;
    //combination number
    for(int wi = 1; wi <= wf; ++wi)
        prod *= static_cast<double>(k+w-wi)/wi;
    if( w > 0)
        prod *= pow((double)m, (double)w);
    double t1 = pow((double)10, (double)(-k-w));
    prod *= t1;
    return w%2? -prod: prod;
}
//3 digit direct computation
double compute_phi_direct(int i, int j, int k)
{
    double sum = 0;

    for( int i = 1; i <= 9; ++i){ //100---900
        if(j < 10){
            for(int p = 0; p <= 9; ++p){
                if(p == j) continue;
                int val = i * 100 + p * 10 + j;
                sum += 1.0/pow((double)val, k);
            }
        }else{
            int q = j - 10;
            if(q == i) continue;
            q *= 11;
            int val = i * 100 + q;
            sum += 1.0/pow((double)val, k);
        }
    }
    return sum;
}
int compute_part(int cpart, int digit)
{
    if(cpart < 10){
        int val = (cpart-digit)%10;
        if(val == 0)
            return cpart+10;
        else
            return digit;
    }else{
        int val = (cpart-digit)%10;
        if(val == 0)
            return -1;
        else
            return digit;
    }
}
//i is the number of digits
//j is the jth partition
//k is the power n^k //sum all the i-digit numbers in the jth partion to the kth power
double phi(int i, int j, int k)
{
    if(vphi[i][j][k] != -1000)
        return vphi[i][j][k];
    if(i <= 3){
            assert(i==3);
            double res = compute_phi_direct(i,j,k);
            vphi[i][j][k] = res;
            return res;
    }
    double result = 0.0;
    int m0 = j;
    //recursive relationship!
    if(j >= 10)
       m0 = j - 10; 

    for(int mi = m0; mi <= m0; ++mi){
        assert(mi < 10);
        for(int li = 0; li< npart; ++li){
            int newpart = compute_part(li, mi);
            if(newpart != j) continue;
            for(int wi = 0;  ;++wi){
                double ai = alpha(k, wi, mi);
                double phit = phi(i-1, li, k+wi);
                double tr = phit * ai;
                if(fabs(tr) < precision) 
                    break;
                else
                    result += tr;
            }
        }
    }
    vphi[i][j][k] = result;
    return result;
}

//first use '9' as an example
int main()
{
    int vsize = 10000;
    vphi.resize(vsize+1);
    for( int i = 0; i<= vsize; ++i)
        vphi[i].resize(20);
    for(unsigned int i = 0; i< vphi.size();++i)
        for(unsigned int j = 0; j < vphi[i].size(); ++j){
            vphi[i][j].resize(20, -1000);
        }
    double sum = 0.0;
    //for 1 or two digits, if expanded, may be too slow
    //direct is good 
    for(unsigned int i = 1; i<=99; ++i)
        sum += 1.0/(double)i;

    for(unsigned int i =3; i<=8000 ; ++i){//digits
        for(unsigned int j = 0; j < 20; ++j){// partition
            double tp= phi(i, j, 1);
            sum += tp;
            printf("%d digits part %d %30.25g\n", i,j, tp);
            assert(tp >= 0.0);
            if(tp < precision) break;
        }
    }
    printf("%30.20g\n", sum);
}

