#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include "../lib/tools.h"
using namespace std;
//looks like I found some clue on this problem, the answer has some pattern!
//it is like binomial coefficient arranged in some order!!!! what an amazing result.
vector<double> data;
vector<int> pos;
double a, b;
class binoData
{
  public:
    binoData(int x0, int y0, double val0):x(x0), y(y0), val(val0) 
    //binoData(int x0, int y0, i64 bco0, double val0):x(x0), y(y0), bco(bco0), val(val0) 
    {
        assert(x0 != 0 || y0 != 0);
    }
    int x;
    int y;
    //i64 bco;
    double val;
    binoData()
    {
        assert(0);
        x = 0;
        y =0;
        //bco = 0;
        val = 0.0;
    }
};
class binoLess{
    public:
        bool operator()(const binoData& b1, const binoData& b2)
        {
            if(b1.val < b2.val) return true;
            if(b1.val == b2.val && b1.x > b2.x) return true;
            return false;
        }
};
/* 
int search_optimal_worstcase(int n, double a, double b)
{
    if(n==1) return 0;
    for(int nt = 2; nt <= n; ++nt){
        double minCost = 100000000;
        int minPos = 0;
        for( int k = 1; k<= nt; ++k){
            double val1, val2, val;
            if(k == 1){
                val1 = 0; 
                val2 = b+data[nt-1];
            }else if (k== nt){
                val2 = 0;
                val1 = a+data[nt-1];
            }else{
                val1 = a + data[k-1];
                val2 = b + data[nt-k];
            }
            val = max(val1, val2);
            if(minCost > val){
                minCost = val;
                minPos = k;
            }
        }
        data[nt] = minCost;
        pos[nt] = minPos;
    }
    return 0;
}
void convert_double_to_sqrt(double val, double a, double b, int& na, int& nb)
{
    double minres= 10000000;
    na = nb = 0;
    for(int ma = 0; ma <= 100; ++ma){
        for(int mb = 0; mb<= 100; ++mb){
            double t = val - ma*a -mb*b;
            if(t < - 0.01)break;
            if(abs(t) < minres ){
                minres = fabs(t);
                na = ma;
                nb = mb;
            }
        }
    }
}
*/
bool checkBino(vector<binoData>& vbino)
{
    for(unsigned int i = 0; i < vbino.size(); ++i){
        assert(vbino[i].x !=0 || vbino[i].y != 0);
    }
    return true;
}
double find_binomial_coefficient(i64 n, i64 a2, i64 b2 )
{
    assert(a2<= b2);
    vector<int64_t> vbc;
    vector<int64_t> nvbc;
    double a = sqrt(a2);
    double b = sqrt(b2);
    vbc.resize(1, 1);
    nvbc.resize(1 , 0);
    vector<binoData> vbino;
    vbino.reserve(1000000);
    double dmax = 41*b;
    for(int i = 1; i<= 1600; ++i){
        for(int j = 0; j <=i; ++j){
            double val = (i-j)*a + j*b;
            if(val > dmax)break;
            vbino.push_back(binoData(i-j, j, (i-j)*a+j*b));
        }
    }
    sort(vbino.begin(), vbino.end(), binoLess());
    //    checkBino(vbino);
    int64_t sum = 1;
    for(int i = 0; i <(int)vbino.size(); ++i){
        int64_t vn = combination((i64)vbino[i].x+vbino[i].y, (i64)vbino[i].x);
        sum += vn;
        //printf("%d %d %ld %ld\n", vbino[i].x+vbino[i].y, vbino[i].y, vn, sum );
        if(sum > n){
            double vx = vbino[i].val;
            return vx;
        }
    }
    assert(0);
    return 0.0;
}
int64_t fibo(int i)
{
    if(i<= 2) return 1LL;
    return fibo(i-1)+fibo(i-2);
}
int main(int argc, char* argv[])
{
    int64_t n = 0; 
    int clow, chigh;
    a=2, b=3;
    if(argc==2){
        n = atol(argv[1]);
    }else if(argc==4){
        n = atol(argv[1]);
        clow = atol(argv[2]);
        chigh = atol(argv[3]);
        a = sqrt(clow);
        b = sqrt(chigh);
        printf("%15.10f\n", find_binomial_coefficient(n, clow, chigh));
        return 0;
    }
    double sum = 0.0;
    n = 1000000000000LL;
    for(unsigned int i = 1; i<= 30; ++i){
        i64 f = fibo(i);
        i64 a = i;
        if(f < a)swap(a, f);
        double val = find_binomial_coefficient(n , a ,f);
        sum += val;
        printf("%d %15.10f %15.10f\n", i, val, sum);
    }
    printf("%15.10f\n", sum);
    //data.clear();
    //pos.clear();
    //data.resize(n+1, 0);
    //pos.resize(n+1, 0);
    //search_optimal_worstcase(n, a, b);
    //for(unsigned int i = 0; i < data.size(); ++i){
    //    int na, nb; 
    //    convert_double_to_sqrt(data[i], a, b, na, nb);
    //    printf("%d %d %d %f %d\n",i, na, nb,data[i], pos[i]);
    //}
}
