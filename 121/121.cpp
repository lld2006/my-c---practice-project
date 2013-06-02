#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<double> vp;
    int nturns = 15;
    vp.resize(nturns+1, 0);
    vp[0] = 1.0;
    for( int i = 1; i <= nturns; ++i){
        vector<double> vpnew;
        vpnew.resize(nturns+1, 0);
        for( int j = 0; j < i; ++j){
            vpnew[j] += vp[j] *(static_cast<double>(i)/(i+1));//get a blue
            vpnew[j+1] += vp[j] *(static_cast<double>(1)/(i+1)); //get a red
        }
        vpnew.swap(vp);
    }
    double p = 0;
    for( int j = nturns/2+1; j<=nturns; ++j){
        p += vp[j];
    }
    int value = 1.0/p;
    printf("%d\n", value );
}
