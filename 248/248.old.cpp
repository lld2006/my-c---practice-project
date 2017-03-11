#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
#include <vector>
#include <cstdio>
#include <set>
#include <algorithm>
set<i64> nset;
vector<int> pindex={0,0,0,1,0,2,0,3,0,0,0,4,0,5};
vector<int> vp={2,3,5,7,11, 13};
vector<int> vpow={10,5,2,1,1,1};
vector<i64> vcands;
i64 n13 = 6227020800LL;
i64 nlim = 100000000000LL;
void find_phi(i64 cphi, i64 cprod, int index);
//find all prime candidates which are greater than 13
void search_all_prime_cand(vector<i64>& vcands, i64 prod, int level)
{
    if(level == 6) {
        if(prod < 15) return;
        if(strong_pseudo_test(prod+1))
            vcands.push_back(prod+1);
        return;
    }
    i64 pm = vp[level];
    i64 tp = 1;
    for( int i = 0; i <= vpow[level]+1; ++i){
       search_all_prime_cand(vcands, prod*tp, level+1);
       tp *= pm;
    }
}
//lesson, here is another headache problem. the problem is revised somehow
//but when I start revising on the previous code, always make more bugs. 
//equal to phix is unacceptable in some case is unacceptable
//find the number whose totient is phix, binary search
int find_phi_index(i64 phix)
{
    int low = 0; 
    int high = vcands.size()-1;
    int mid;
    if( phix < vcands[0] - 1 ) 
        return -1;
    if(phix > vcands.back())
        return vcands.size()-1;
    while(high > low+1){
       mid = (low+high)/2; 
       if(vcands[mid] - 1 <= phix ){
            low = mid;
       }else{
           high = mid;
       }
    }
    assert(vcands[high] > vcands[low] );
    assert(vcands[low] - 1 <= phix);
    return low;
}
void search2(int level, i64 proda, i64 phia)
{
    if(proda > nlim) return;
    if(level == vpow.size()) {
        if(phia > n13) return;
        if(phia == n13){ 
            nset.insert(proda);
            return;
        }
        if(n13 % phia != 0) return;
        find_phi(phia, proda, vcands.size());
        return;
    }
    //consider all small primes
    i64 pm = vp[level];
    i64 tpa = 1;
    for( int i = 0; i <= vpow[level]+1; ++i){
       i64 tphia = 1;
       if( i >= 1 ) tphia = tpa/pm*(pm-1);
       search2(level+1, proda*tpa, phia*tphia);
       tpa *= pm;
    }
}
void find_phi(i64 cphi, i64 cprod, int phiIndex)
{
    if(cprod > nlim || cphi > n13 || n13%cphi )
        return;
    if(cphi == n13) {
        nset.insert(cprod);
        return;
    }
    i64 phi1 = n13/cphi;
    i64 upperindex = find_phi_index(phi1);
    if(upperindex >= phiIndex)
        upperindex = phiIndex-1;
    assert(upperindex == -1 || vcands[upperindex]-1 <= phi1 );
    for(int j = upperindex; j >= 0; --j){
        if( phi1 % (vcands[j]-1) != 0 ) 
            continue;
        find_phi(cphi*(vcands[j]-1),cprod*vcands[j], j);
    }
}
int main()
{
    vector<int> vfac;
    vector<int> primes;

    search_all_prime_cand(vcands, 1, 0);
    sort(vcands.begin(), vcands.end());

    search2(0, 1LL, 1LL);
    printf("number %zu\n", nset.size());
    i64 cnt=0;
    for(set<i64>::iterator iter = nset.begin(); iter!=nset.end(); ++iter){
        ++cnt;
        if(cnt == 150000 ) printf("%lld\n", *iter);
    }
}
