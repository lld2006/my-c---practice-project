#include <vector>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include "../lib/rational.h"
#include <cstdio>
#include <cassert>
#include <set>
#include <algorithm>
//lesson 1, be careful, prime may not always appear in the summation
//lesson 2, be careful about integer division, a/(bc) != (a/b)/c if
//rational number is concerned!
//lesson 3, searching part has a bug, all rational numbers are irreducible
//lesson 4, must return something if recursion must end, it might be 0 or something
//it would be best to first have a very clear idea, then coding, if some of the plan
//has changed, sometimes some bug are extremely difficult to track.
vector<vector<rational> >vr_prime;
vector<int> pcand;
int nmult = 16;
//this function create all the possible summation of rationals from 1 to 1/16^2
//this would create 2^16 numbers
void create_summation_vector(const vector<int>& vn, vector<rational>& vr)
{
    vr.clear();
    int nsize = vn.size();
    int rsize = power(2, nsize);
    vr.resize(rsize);
    vr[0] = rational(0, 1);
    unsigned int nl = 1;
    for(unsigned int i = 0; i < vn.size(); ++i){
        rational rx (1, vn[i]*vn[i]);
        for(unsigned int j= 0; j < nl; ++j){
           vr[j+nl] = vr[j] + rx; 
           assert(j+nl < vr.size());
        }
        nl *= 2;
    }
    return;
}
//this function is not correct, I should sort all the numbers
//and give an log(n) algo, which is much better than n
int search_two(int pos, const rational sum ){
    if(sum.pden() < sum.pnum()*2) return 0;
    int nsum = 0;
    int px = pcand[pos];
    int p2 = px *px;
    if(pos == static_cast<int>(vr_prime.size())){
        //assert(gcd(sum.pnum(), sum.pden())==1);
        if(sum.pnum()==1 && sum.pden()==2)
            return 1;
        else 
            return 0;//must return if pos == size
    }
    if(sum.pnum() == 0 || sum.pden()%px != 0){//initialization part
        vector<rational>& vr=vr_prime[pos];
        assert(vr[0].pnum() == 0);
        for(unsigned int i = 0; i <vr.size(); ++i){
            if(vr[i].pnum() % p2 == 0){
                rational sum1 = sum + rational(vr[i].pnum(), vr[i].pden()*p2);
                nsum += search_two(pos + 1, sum1);
            }
        }
    }else{//start searching part
        vector<rational>& vr=vr_prime[pos];
        for(unsigned int i = 0; i <vr.size(); ++i){
          rational sum1 = sum + rational(vr[i].pnum(), vr[i].pden()*p2);
          if(sum1.pden() % px != 0|| px==2 ){
              nsum += search_two(pos +1, sum1);
          }
        }
    }
    return nsum;
}
int main()
{
    int nmax = 80;
    int limit = nmax/2;
    vector<int> primes, prime80;
    primeWithin(primes, limit);
    primeWithin(prime80, nmax);
    vector<rational> result;
    vector<int> vt;
    vt.resize(nmult);
    for(unsigned int i = 0; i <nmult; ++i)
        vt[i] = i+1 ;
    create_summation_vector(vt, result); 
    //I am not doing good enough here!
    //all the numbers can be tested including composite!
    vector<int> reducible;
    reducible.resize(limit+1, 0);
    reducible[0]=reducible[1]=0;
    reducible[2] = 1;
    for(int i = 3;  i <= limit; --i){
       int nx = nmax/ primes[i]; //maximum multiplier for the prime
       unsigned int np = power(2, nx);
       unsigned int p2 = i*i;
       for(unsigned int sumi = 0; sumi < np; ++sumi ){
            if(result[sumi].pnum()!= 0 && result[sumi].pnum() % p2 == 0)
                reducible[i] = 1;
       }
    }
    set<int> primeset(prime80.begin(), prime80.end());
    for(unsigned int i = 0; i < reducible.size(); ++i){
        if(reducible[i]){
            primeset.erase(primes[i]);
            pcand.push_back(primes[i]);
        }
    }
    reverse(pcand.begin(), pcand.end()); 
    printf("number cand %d\n", static_cast<int>(pcand.size()));
    //from here we have found all candidates stored in pcand

    vector<int> ncand;
    ncand.resize(nmax+1,1);
    ncand[0]=ncand[1]=0;
    for(set<int>::iterator iter=primeset.begin(); iter != primeset.end(); ++iter){
        int nrmv = *iter;
        for(int nx = nrmv; nx < nmax; nx+=nrmv){
            ncand[nx] = 0;
        }
    }
    vector<vector<int> > cand_per_prime;
    cand_per_prime.resize(pcand.size());
    for(unsigned int i = 0; i < pcand.size(); ++i){
        int px = pcand[i];
        vector<int>& vp=cand_per_prime[i];
        for(unsigned int i = 0; i < ncand.size(); ++i){
            if(ncand[i] == 0) continue;
            if(i % px == 0){
                vp.push_back(i/px);
                ncand[i] = 0;
            }
        }
    }
    vr_prime.resize(pcand.size());
    for(unsigned int i = 0; i<pcand.size(); ++i){//create each prime numbers possible summation
        create_summation_vector(cand_per_prime[i], vr_prime[i]);
    }
    
    int xresult = 0; 
    rational asum(0, 1);
    xresult += search_two(0,asum); 
    printf("the end %d\n", xresult);
}
