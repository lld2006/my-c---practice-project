#include <vector>
#include <cstdio>
#include <numeric>
#include <cassert>
using namespace std;
//lesson, when there is duplication, please use function, if you donot, you are 
//more likely to make mistakes.
int check_value(vector<double>& vn)
{
    int nlim = vn.size();
    for(int i = vn.size()-1; i>=0; --i){
        if(vn[i] < 1e-20){
            --nlim;
        }else{
            break;
        }
    }
    return nlim;
}
void polynomial_product(vector<double>& pa, vector<double> pb, vector<double>& pr)
{
    int order1 = pa.size();
    int order2 = pb.size();
    pr.clear();
    pr.resize(order1+order2-1, 0);
    for(unsigned int a = 0; a<pa.size(); ++a){
        for(unsigned int b = 0; b<pb.size(); ++b){
            pr[a+b] += pa[a] * pb[b];
        }
    }
}
void convert_A2B(vector<double>& va, vector<double>& vb, int orderB)
{
    double sum = accumulate(va.begin(), va.end(), 0.0);
    for(unsigned int i = 0; i < va.size(); ++i){
        va[i]/= sum;
    }
    int newsize = check_value(va);

    va.resize(newsize); //ignore small numbers
    vector<double> vni(va);

    vb.clear();
    vb = va;
    vector<double> vt;
    for( int i = 2; i<= orderB; ++i){
        polynomial_product(va, vni, vt);
        assert(vt.size() >= vb.size());
        vb.resize(vt.size(), 0);
        for(unsigned int j = 0; j < vt.size(); ++j)
            vb[j] += vt[j];
        vni.swap(vt); //next order ready in vni
    }
}
int main()
{
    vector<double> v20, v12, v8, v6, v4; 
    vector<double> vni, vt;
    v20.resize(21, 0.05);
    v20[0] = 0;
    vni = v20;

    convert_A2B(v20, v12, 12); 
    convert_A2B(v12, v8, 8); 
    convert_A2B(v8, v6, 6); 
    convert_A2B(v6, v4, 4); 
    
    double x=0, x2 = 0, sum= 0;
    for(unsigned int i = 0; i < v4.size(); ++i){
        sum += v4[i];
        x += v4[i] * i; 
        x2 += v4[i] * i * i;
    }
    x /= sum;
    x2 /= sum;
    printf("%30.15f %30.15f\n", x2 - x*x, sum);
}
