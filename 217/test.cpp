#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
//lesson, I am too stupid, I do not need to keep the sum of each digit.
//I just need a number.
        //if(vlcnt[nsum] ==0 || vrcnt[nsum]==0) continue;
        ////lesson! bug even if cont == 0, still need to multiply 10!
        //this is not good for coding. but I avoided the leading zero issue in this way
typedef unsigned long long i64;
//update left part only
void updateVector(int level, i64* vlsum, i64* vlcnt)
{
    for( int i = 9*level; i >= 0; --i ){
        vlsum[i] *= 10;
        i64 cij = vlcnt[i];
        for( int j = i+1; j < i+10; ++j ){
            vlsum[j] += vlsum[i] + cij;
            vlcnt[j] += vlcnt[i];
            cij += vlcnt[i];
        }
    }
}

i64 sum_all_new(int nd, i64* vleft, i64* vright, i64* vlcnt, i64* vrcnt, i64& npow10, const i64 nmod)
{
    npow10 *= 10ULL;
    npow10 %= nmod;
    i64 sum = 0;
    //for( int nsum = 1; nsum <= nd*9; ++nsum){
    //    assert(vleft[nsum] > 0 && vlcnt[nsum] > 0);
    //    vleft[nsum] %= nmod;
    //    vlcnt[nsum] %= nmod;

    //    vright[nsum] += vleft[nsum];
    //    vright[nsum] %= nmod;
    //    vrcnt[nsum] += vlcnt[nsum];
    //    vrcnt[nsum] %= nmod;
    //       
    //    i64 tsum = 101ULL*vleft[nsum] * vrcnt[nsum] + vrcnt[nsum]*vlcnt[nsum]*45ULL;
    //    tsum %= nmod;
    //    tsum *= npow10;
    //    tsum %= nmod;
    //    tsum += 11ULL*vlcnt[nsum] * vright[nsum];
    //    tsum %= nmod;
    //    sum += tsum;
    //}
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
    return sum%nmod;
}

int main()
{   
    //sum; //sum of each digits //cnt
    i64 nmod = 14348907ULL;
    int maxlevel = 20000;
    int maxsum = (maxlevel/2)*9+1;
    int tlevel = maxlevel;
    i64 npow10 = 1ULL;
    //vector<i64> vleft, vright;
    //vleft.resize(maxsum, 0); vright.resize(maxsum, 0);
    //vector<i64> vlcnt, vrcnt;
    //vlcnt.resize(maxsum, 0);
    //vrcnt.resize(maxsum, 0);
    i64 vleft[maxsum], vright[maxsum];
    i64 vlcnt[maxsum], vrcnt[maxsum];
    memset(vlcnt, 0,sizeof(i64)*maxsum);
    memset(vrcnt, 0,sizeof(i64)*maxsum);
    memset(vright, 0,sizeof(i64)*maxsum);
    memset(vleft, 0,sizeof(i64)*maxsum);

    //printf("%zu %zu\n", vlcnt.capacity(), vlcnt.size());
    
    vright[0] = 0;
    vrcnt[0]=1;

    vrcnt[0] = 1;
    for(unsigned int i = 1; i < 10; ++i){//start from the first digit of the number
        vleft[i] = i;
        vlcnt[i] = 1;
    }
    i64 sum = 45;//1, 9 all qualified
    //first level how many digits, loop
    for( int level = 1; level<= tlevel/2; ++level){
        sum += sum_all_new(level, vleft, vright, vlcnt, vrcnt, npow10, nmod);
        sum %= nmod;
        if(level == tlevel/2) break; //no need to update left 
        updateVector(level, vleft, vlcnt);
        //if(level % 100==0 || level==2)printf("%d %lld \n", level*2+1, sum);
    }
    i64 sum1 = 0;
    i64 sumt = 0;
    if(tlevel %2 == 0){
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
