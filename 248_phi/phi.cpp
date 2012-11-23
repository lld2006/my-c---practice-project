#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
set<i64> nset;
vector<int> vpow, pindex, vp, vps;
vector<double> vnlog;
vector<vector<int> > vcand;
vector<i64> vcands;
i64 n13 = 6227020800LL;
i64 nlim = 100000000000LL;
void find_phi(i64 cphi, i64 cprod, int index);
//vps store all prime numbers
//vcand store all the factors of each corresponding prime number
//void find_all_candidate(const vector<int>& vfac, const vector<int>& primes, vector<int>& vps, vector<vector<int> >& vcand)
//{
//    for(unsigned int i = 0; i < primes.size(); ++i){
//        int p1 = primes[i]-1;
//        //this is a raw version of candidate test
//        if(vfac[p1] > 13) continue;
//        
//        vector<int> vpt;
//        vpt.resize(6 , 0);
//        bool isCandidate = true;
//        while(p1 > 1){
//            int fac = vfac[p1];
//            int np = 0;
//            while( vfac[p1] == fac){
//                p1 /= fac;
//                ++np;
//            }
//            //one factor processed
//            assert(fac < static_cast<int>(pindex.size()));
//            int index = pindex[fac];
//            if(np > vpow[index]){
//                isCandidate = false;
//                break;
//            }else{
//                vpt[index] = np;
//            }
//        }
//        //one number processed, check if need insertion
//        if(isCandidate){
//            vps.push_back(primes[i]);
//            vcand.push_back(vpt);
//        }
//    }
//}
//void search_numbers(const vector<int>& vpows, int pmax, i64 num, double sumlog)
//{
//    if(pmax < 0) return;
//    //skip this number 
//    search_numbers(vpows, pmax-1, num, sumlog);
//    i64 prod = 1;
//    int px = 0;//maximum power of prime number 
//    int tp = vps[pmax];// prime in this level
//    int tidx = tp <= 13 ? pindex[tp]:-1;
//    if( tp > 13) 
//        px = 1;
//    else
//        px = vpows[tidx]+1;//at most this much
//    
//    //tp^i
//    for( int i = 1; i <= px; ++i){
//        double logsum = sumlog + i*vnlog[pmax];
//        prod *= tp;
//        vector<int> vp1;
//        vp1.resize(6,100);
//        bool needToBreak = false;
//        bool allzero = true;
//        for(unsigned int j = 0; j <vp1.size(); ++j){
//            int tp = vpows[j] - vcand[pmax][j];
//            if( static_cast<int>(j) == tidx ) tp -= (i-1);
//            if(tp > 0) allzero = false;
//            if(tp < 0){
//                needToBreak = true;
//                break;
//            }
//            vp1[j] = tp;
//        }
//        
//        if( logsum > 18.5) break; //
//        if(allzero && !needToBreak){
//            nset.insert(num*prod);
//            return;
//        }
//        if(!needToBreak){
//            //if(true){
//            //    printf("the number choosen is %dd\n", vps[pmax]);
//            //}
//            search_numbers(vp1, pmax-1, num*prod, logsum);
//        }else{
//            break;
//        }
//    }
//}
//find all candidates which are greater than 13
void search_all_prime_cand(vector<i64>& vcands, i64 prod, int level)
{
    if(level == 6) {
        if(prod < 15) return;
        //if(isPrime(prod+1))
        //    assert(strong_pseudo_test(prod+1));
        if(strong_pseudo_test(prod+1))
            vcands.push_back(prod+1);
        return;
    }
    i64 pm = vp[level];
    for( int i = 0; i <= vpow[level]+1; ++i){
       i64 tp = power(pm, (i64)i);
       search_all_prime_cand(vcands, prod*tp, level+1);
    }
}
//for 
//void create_phi_factors(vector<i64>& vcands) 
//{
//    multimap<i64, i64> phimap;
//    for(unsigned int i = 0; i < vcands.size(); ++i){
//        i64 prod = 1;
//        i64 n1 = vcands[i] - 1;
//        for( int j = 5; j >= 0; --j ) {
//            i64 p1 = vp[j];
//            while(n1 % p1 == 0){
//                n1/=p1;         
//                prod *= p1;
//            }
//            if(prod % p1 == 0){
//                prod /= p1;
//                prod *= (p1-1);
//            }
//        }
//        if(vcands[i] > 2)
//            assert(prod > 1);
//        phimap.insert(pair<i64, i64>(prod, vcands[i]));
//    }
//    for(map<i64, i64>::iterator iter=phimap.begin(); iter != phimap.end(); ++iter ){
//        vphi.push_back(pair<i64, i64>(iter->first, iter->second));
//    }
//}
//lesson, here is another headache problem. the problem is revised somehow
//but when I start revising on the previous code, always make more bugs. 
//equal to phix is unacceptable in some case is unacceptable
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
    if(proda > nlim) 
        return;
    if(level == vpow.size()) {
        if(phia > n13) return;
        if(phia == n13){ 
            nset.insert(proda);
            return;
        }
        if(n13 % phia != 0) 
            return;
        find_phi(phia, proda, vcands.size());
        return;
    }
    i64 pm = vp[level];
    for( int i = 0; i <= vpow[level]+1; ++i){
       i64 tpa = power(pm, (i64)i);
       i64 tphia = 1;
       if( i >= 1 ) tphia = tpa/pm*(pm-1);
       search2(level+1, proda*tpa, phia*tphia);
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
    //int lim = 2000000;
    //vector<int> vsp;
    //for(int i = 1; i< lim; i+=2){
    //    if(strong_pseudo_test(i))
    //        vsp.push_back(i);
    //}
    //vector<int> paa, pres, pres2;
    //primeWithin(paa, lim);
    //set_difference(vsp.begin(), vsp.end(), paa.begin(), paa.end(), back_inserter(pres));
    //set_difference(paa.begin(), paa.end(), vsp.begin(), vsp.end(), back_inserter(pres2));
    //        
    //for(unsigned int i = 0; i < pres.size(); ++i)
    //    printf("%d\n", pres[i]);
    //printf("test2 \n");
    //for(unsigned int i = 0; i < pres2.size(); ++i)
    //    printf("%d\n", pres2[i]);
    vector<int> vfac;
    vector<int> primes;

    //power limit
    vpow.resize(6, 0);
    vpow[0] = 10;
    vpow[1] = 5;
    vpow[2] = 2;
    vpow[3] = 1;
    vpow[4] = 1;
    vpow[5] = 1;
    //prime to vector index
    pindex.resize(14, 0);
    pindex[2] = 0;
    pindex[3] = 1;
    pindex[5] = 2;
    pindex[7] = 3;
    pindex[11] = 4;
    pindex[13] = 5;
    //index to prime
    vp.resize(6, 0);
    vp[0] = 2;
    vp[1] = 3;
    vp[2] = 5;
    vp[3] = 7;
    vp[4] = 11;
    vp[5] = 13;

    search_all_prime_cand(vcands, 1, 0);
    sort(vcands.begin(), vcands.end());
    //for(unsigned int i = 0; i< vcands.size(); ++i){
    //    printf("%lld\n", vcands[i]);
    //}
    //void create_phi_factors(vector<i64>& vcands, vector<i64>& vphi) 
    //create_phi_factors(vcands);
    //printf("%zu\n", vcands.size());

    //first test find_phi looks like something wrong
    //find_phi(1LL, 1LL, vcands.size());

    search2(0, 1LL, 1LL);
    printf("number %zu\n", nset.size());
    i64 cnt=0;
    for(set<i64>::iterator iter = nset.begin(); iter!=nset.end(); ++iter){
        ++cnt;
        if(cnt == 150000 ) {
            //i64 c1 = *iter;
            //if(c1 % 58081 == 0)
                printf("%lld\n", *iter);
        }
    }
    exit(1);

    //find_all_candidate( vfac, primes, vps, vcand);
    //printf("cnt = %d\n", static_cast<int>(vps.size()));
    //vnlog.resize(vps.size(), 0);
    //for(unsigned int i = 0; i< vps.size(); ++i){
    //    vnlog[i] = log10(static_cast<double>(vps[i]));
    //}
    //vector<int> vpow0(vpow);
    //search_numbers(vpow0, vps.size()-1, 1, 0);
    //printf("number of phi==13! is %d\n", static_cast<int>(nset.size()));
    ////i64 cnt = 0;
    //printf("value is %lld\n", cnt);
}
