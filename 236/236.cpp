#include <cstdio>
#include <vector>
#include <set>
#include <cassert>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;
//lesson, why did not I group those 3 similar groups together?! 
//too stupid on such an easy problem!
//second lesson in this problem is that I should start searching from va[0]
//instead of total numbers of defected items. since there are much less possibilities
//in va[0] than that in the total.
vector<int> va = {5248, 5760, 7872};
vector<int> vb = {640, 3776, 11328};
int main()
{
    set<IntPair> pset;
    int cnt = 0;
    for(int db1 = 1; db1 <= vb[0]; ++db1){
        int da1max = 41*db1/5;
        if(da1max > va[0]) da1max = va[0];
        for( int da1 = 1; da1 <= da1max; ++da1){
            i64 num = 41 * db1;
            i64 den = 5 * da1;
            assert(num >= den );
            i64 num2 = num * 59; 
            i64 den2 = den * 90;
            int g2 = gcd(num2, den2);
            num2/=g2;  //for b 
            den2/=g2;  //for a, reduced
            for(int k2 = 1; k2; ++k2){
                i64 tn2 = num2 * k2; // db4
                i64 td2 = den2 * k2; // da4
                if(tn2> vb[1] || td2> va[1] )
                    break;
                i64 num3 = num * 59;
                i64 den3 = den * 41;
                int g3 = gcd(num3, den3);
                num3/=g3; den3/=g3;
                for(int k3 = 1; k3; ++k3){
                    i64 tn3 = num3*k3;
                    i64 td3 = den3*k3;
                    if(tn3 > vb[2] && td3 > va[2])
                        break;
                    i64 tn = tn3 + tn2 + db1;
                    i64 td = td3 + td2 + da1;
                    if(tn*295*num == td*246*den){
                        int g1 = gcd(num, den);
                        num/=g1, den/=g1;
                        if(pset.insert(IntPair(num, den)).second)
                            printf("%lld %lld %f %d\n", num, den, (double)num/den,++cnt);
                    }
                        
                }
            }
        }
    }
}
