#include <cstdio>
#include <cassert>
#include <limits>
#include <queue>
#include "../lib/typedef.h"
//lesson 1, I have a wrong impression, the linked list should 
//all ended with minimum value of this array
//lesson 2, npart is only valid before nmid or after the minimum
bool operator< (const IntPair& p1, const IntPair& p2)
{
   if(p1.first < p2.first)
      return true; 
   else if(p1.first == p2.first)
       return p1.second < p2.second;
   return false;
}

vector<int> vn;
vector<int> vnext; //next less;
unsigned int period;
i64 nmid = 0;
i64 minimum = 100000000;
int mpos = 0;

i64 debug(int n)
{
    i64 total = 0;
    int tminimum = vn[n];
    i64 cnt = 0;
    unsigned int k;
    for( k = n; k <= 2*period+1; ++k){
        if(vn[k] < tminimum){
            total += cnt * tminimum;
            tminimum = vn[k];
            //printf("%d %d %lld\n",k, vn[k], total);
            cnt = 0;;
        }
        if(tminimum == minimum) break;
        ++cnt;
    }
    assert(vn[k] == minimum);
    int nw =(k-nmid)/period+1;
    total += (nw*period +nmid - k+1) * minimum;
    return total;
}

void debugpq(const priority_queue<pair<int, int>>& vpq)
{
    priority_queue<pair<int, int>> vpq1(vpq);
    while(!vpq1.empty()){
        const IntPair& p1 = vpq1.top();
        printf("%d %d\n", p1.first, p1.second);
        vpq1.pop();
    }
}

i64 compute_part(int n, int& nfirst, i64& npart)
{
    int nmax = numeric_limits<int>::max();
    i64 nall = 0, nseg = 0;
    if(n ==nmid + 1)
        npart = 0;
    npart = 0;
    i64 current = n;
    i64 next = vnext[current];
    if(n > nmid)
        nseg = nmid + period;
    else
        nseg = nmid;
    while(next < nmax){
        if(next > nseg && current <= nseg){
            npart = nall + (nseg-current+1)*vn[current];
        }
        nall += (next - current)*vn[current];
        current = next;
        next = vnext[current];
    }
    if(next > nseg && current <= nseg)
        npart = nall + (nseg-current+1)*vn[current];
    if(n >nmid && n<=mpos)
        npart = 0;
    //assert(npart == 0);
    assert(vn[current] == minimum);
    
    i64 nw = (current-nmid)/ period;
    assert(nw >= 0);
    
    nfirst = nw+1;

    // the rest of the segment are minimums
    nall += (nfirst*period+nmid- current+1 ) * minimum;
        
    //assert(nall == debug(n));
    return nall;
}

int main()
{
    int range = 2000000000LL;
    //range = 10000;
    period = 6308948;
    vn.resize(2*period+1);
    i64 s0 = 290797;
    vn[0] = s0;
    i64 nmod = 50515093LL;
    //generate  all numbers twice, this needs relatively 
    //large memory 
    for(unsigned int i = 1; i <= period; ++i){
        s0 = s0*s0;
        s0 %= nmod;
        vn[i] = s0;
        if(s0 < minimum){
            minimum = s0;
            mpos = i;
        }
        vn[i+period] = vn[i];//lesson, here I made a mistake, rhs used i
    }
    assert(((i64)vn[period] * vn[period])%nmod==vn[1]);
    bool debug = false;
    if(debug){
        vn = {0, 7,4,6,3, 1,8, 9, 7,4,6,3,1,8,9};
        period = 7;
        range = 24;
        minimum = 1;
        mpos = 5;
    }
    //intmax means minimum not found, better than 0;
    vnext.resize(2*period+1, numeric_limits<int>::max());
   
    //generate a max priority queue to find the next less
    priority_queue<pair<int, int>> vpq;
    for( unsigned int i = 1; i < vn.size(); ++i){
        int val = vn[i];

        while(!vpq.empty() && vpq.top().first > val){
             int nx = vpq.top().second;
             //over a period is OK, 
             //assert(vnext[1] == numeric_limits<int>::max());
             assert(vnext[nx] == numeric_limits<int>::max());
             assert(vn[nx] > vn[i]);
             vnext[nx] = i;
             vpq.pop();
        }
        vpq.push(IntPair(val, i));
        if(vpq.empty() || (i >period && vpq.top().first == minimum))
           break; 
    }
    //now vnext has all the next smaller values in the vector
    //we need to count now
    nmid = range % period;
    i64 nfull, ntotal = 0, npart=0; 
    unsigned int nmax = period <= range? period : range;
    int nfirst = 0;
    for(unsigned int i = 1; i <= nmax; ++i){

            i64 nall = compute_part(i, nfirst, npart);
            //printf("%d %lld %lld %d %lld\n", i, npart, nall,nfirst, ntotal);
            //post processing
            nfull = range / period;
            nfull -= nfirst;
            assert(nfull >= 0);
            ntotal += nfull*(nfull + 1)/2 * (minimum * period) + nall * (nfull +1)+npart;
    }
    printf("%lld\n", ntotal);
}
