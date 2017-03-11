//TODO not extremely efficient
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include "../lib/tools.h"
using namespace std;
int seg = 1000;
int nmax = 10000000;
int n2 = 0;
class pairLess
{
    public:
        bool operator()(const IntPair& p1, const IntPair& p2)
        {
            return p1.first < p2. first ||(p1.first == p2.first && p1.second < p2.second);
        }
};
void fillVector(IntPairVec& vprim, vector<vector<i64>>& vseg, i64 p)
{
    i64 nSegEnd = (p+1)*seg;
    for(unsigned int i = 0; i < vprim.size(); ++i){
        i64 a = vprim[i].first;
        i64 b = vprim[i].second;
        if(a > nSegEnd) break;
        i64 nstart = p*seg/a;
        i64 start = (p*seg)%a;
        if(start == 0) {
            start+=a;
            ++nstart;
        }else{
            start = a- start;
            ++nstart;
        }
        for(int j = start; j <=seg; j+=a, ++nstart){
            if(nstart*(a+b) > n2) break;
            vseg[j].push_back(nstart*b);
        }
    }
}
int main()
{
    n2 = nmax/2;
    IntPairVec vprim1, vprim2;
    int nt = sqrt(nmax/2);//should be 4
    for( i64 n = 1; n<=nt; ++n){
        for(i64 m = n+1; 1; m+=2){
            if(gcd(m, n) > 1) continue;
            i64 a = m*m - n*n;
            i64 b = 2*m*n;
            if(a + b > n2 ) break;
            //printf("triangle %lld %lld\n", a, b);
            if(a < b){
                vprim1.push_back(IntPair((int)a,(int)b)); //less
                vprim2.push_back(IntPair((int)b,(int)a)); //greater
            }else{
                vprim2.push_back(IntPair((int)a, (int)b));
                vprim1.push_back(IntPair((int)b, (int)a));
            }
        }
    }
    printf("found %d\n", static_cast<int>(vprim1.size()));
    sort(vprim1.begin(), vprim1.end(), pairLess());
    sort(vprim2.begin(), vprim2.end(), pairLess());
    //I cannot afford a big array of set, which is too costly, 
    //so let me use segmented sieve instead
    int piece = nmax/seg; // from 1 to seg or piece*seg+1 to piece*seg+seg
    i64 sum = 0;
    for(int p = 0; p<piece; ++p){
        if(p% 100 ==0) 
        printf("%d %lld\n", p, sum);
        vector<vector<i64>> vseg;
        vseg.resize(seg+1);
        fillVector(vprim1, vseg, p);
        fillVector(vprim2, vseg, p);
        for(unsigned int k = 0; k< vseg.size(); ++k){
            assert(vseg[0].empty());
            vector<i64>& vx = vseg[k];
            sort(vx.begin(), vx.end());
            i64 a = p*seg+k;
            for(unsigned int i = 0; i<vx.size(); ++i){
                i64 d1 = vx[i];
                if(d1 * 2 > vx.back()) break;
                for(int j = vx.size()-1; j >= 0; --j){
                    i64 d2 = vx[j];
                    if(d2 < 2*d1)break;
                    i64 delta = d2 - d1;
                    assert(delta > d1);
                    i64 c2 = delta*delta + 4*a*a;
                    i64 c = sqrt(c2);
                    if(c*c==c2){
                        i64 dx2 = a*a + d1 * d1;
                        i64 dx = sqrt(dx2);
                        assert(dx*dx == dx2);
                        i64 perim = 2*(a+delta+dx);
                        if(perim <= nmax){
                        sum+=perim;
                        //printf("a=%lld dt=%lld d1=%lld d2=%lld perim=%lld\n", a, delta, d1, d2, perim);
                        } 
                    }
                }
            }
        }
    }
    printf("%lld\n", sum);
}
