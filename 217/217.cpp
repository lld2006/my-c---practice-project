#include <cstdio>
//#include <cassert>
#include <cstring>
//lesson, I am too stupid, I do not need to keep the sum of each digit.
//I just need a number.
        //if(vlcnt[nsum] ==0 || vrcnt[nsum]==0) continue;
        ////lesson! bug even if cont == 0, still need to multiply 10!
        //this is not good for coding. but I avoided the leading zero issue in this way
//using namespace std;
typedef unsigned long long i64;
const int maxlevel = 20000;
const int maxsum = (maxlevel/2)*9+1;
i64 npow10 = 1ULL;
i64 nmod = 1ULL;
//update left part only
inline void updateVector(int level, i64* vleft, i64* vlcnt)
{
    //printf("update %d\n", 90*level);
    for( int i = 9*level; i >= 0; --i ){
        vleft[i] *= 10ULL;
        i64 cij = vlcnt[i];
        for( int j = i+1; j < i+10; ++j ){
            vleft[j] += vleft[i] + cij;
            vlcnt[j] += vlcnt[i];
            cij += vlcnt[i];
        }
    }
}

inline i64 sum_all_new(int nd, i64* vleft, i64* vright, i64* vlcnt, i64* vrcnt)
{
    npow10 *= 10ULL;
    npow10 %= nmod;
    i64 sum = 0;
    i64 ci,si,cci,ssi;
    for( int nsum = 1; nsum <= nd*9; ++nsum){
        //assert(vleft[nsum] > 0 && vlcnt[nsum] > 0);
        si = vleft[nsum] %= nmod;
        ci = vlcnt[nsum] %= nmod;

        vrcnt[nsum] = (vrcnt[nsum] + vlcnt[nsum])%nmod;
        cci = (vrcnt[nsum]*npow10)%nmod;
        ssi = vright[nsum] = (vright[nsum] + vleft[nsum])%nmod;
           
        sum += 101ULL*cci * si + ci*cci*45ULL + 11ULL*ci*ssi;
        sum %= nmod;
    }
    return sum;
}

int main()
{   
    //sum; //sum of each digits //cnt
    nmod = 14348907ULL;
    int tlevel = maxlevel;
    //vector<i64> vleft, vright;
    i64 vleft[maxsum], vright[maxsum];
    i64 vlcnt[maxsum], vrcnt[maxsum];
    memset(vlcnt, 0,sizeof(i64)*maxsum);
    memset(vrcnt, 0,sizeof(i64)*maxsum);
    memset(vright, 0,sizeof(i64)*maxsum);
    memset(vleft, 0,sizeof(i64)*maxsum);
    //vleft.resize(maxsum, 0); vright.resize(maxsum, 0);
    //vector<i64> vlcnt, vrcnt;
    //vlcnt.resize(maxsum, 0);
    //vrcnt.resize(maxsum, 0);

    vright[0] = 0;
    //vrcnt[0]=1;

    for(unsigned int i = 1; i < 10; ++i){//start from the first digit of the number
        vleft[i] = i;
        vlcnt[i] = 1;
    }
    i64 sum = 45ULL;//1, 9 all qualified
    //first level how many digits, loop
    int t2 = tlevel/2;
    for( int level = 1; level<= t2; ++level){
        sum += sum_all_new(level, vleft, vright, vlcnt, vrcnt);
        sum %= nmod;
        if(level == t2) break; //no need to update left 
        updateVector(level, vleft, vlcnt);
    }
    i64 sum1 = 0;
    i64 sumt = 0;
    if(tlevel %2LL == 0){
        for(int i = 1; i <= maxsum; ++i){
            //assert(vleft[i]< nmod);
            //assert(vrcnt[i]< nmod);
            sumt = 100ULL*vleft[i]*vrcnt[i];
            sumt += 45ULL*vlcnt[i]*vrcnt[i];
            sumt %= nmod;
            sumt *= npow10;
            sumt %= nmod;
            sumt += 10ULL*vlcnt[i]*vright[i];
            sumt %= nmod;
            sum1 += sumt;
            sum1 %= nmod;
            //printf("%d %lld %lld %lld %lld %lld\n",i, sum1);
        }
    }
    //i64 sum2 = sum_all(tlevel+1, vleft, vright, vlcnt, vrcnt);
    //printf("%lld %lld %lld\n", sum1, sum2, npow10);
    sum -= sum1;
    printf("%lld\n", (sum+nmod)%nmod);
}
