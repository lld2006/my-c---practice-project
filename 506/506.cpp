//first I need to figure out how many numbers are needed
//since the pattern is 123432 so sum is 15 for every 6 number
//so the sum of 1 to 1e14 -1 is 
//now I see that it is zero so for 1e14, it starts from 123432.....
//
//my god, it is the sum of all, not just 1e14 mod nmod!!!!
#include "../lib/tools.h"
#include <deque>
i64 nmax= 100000000000000LL;
i64 nmod = 123454321LL;
i64 calc_repetitive_number(const deque<int>& deq)
{
    int sum = 0;
    for(unsigned int i =0; i< deq.size(); ++i){
        sum *=10;
        sum += deq[i];
    }
    return sum;
}
//produce the new deq and number 
void deque_rotate(deque<int>& deq, int sum, i64& repet, i64& tail)
{
   repet= calc_repetitive_number(deq); 
   assert(repet > 100000 && repet < 500000);
   int sx = 0;
   int n5= 0;
   while(sx < sum){
     int val = deq[0];
     n5 *= 10;
     n5 += val;
     deq.pop_front();
     deq.push_back(val);
     sx += val;
   }
   tail = n5;
}
i64 sumAllWithSameTail(i64 tail, i64 rep, i64 sum)
{
    //sum == 1-->15
    i64 n = (nmax-sum)/15; //start from index 0 value=sum
    //6 digits repetitive pattern
    int temp = tail;
    int cnt = 0; //number of tail digits
    do{
        temp/=10;
        ++cnt;
    }while(temp);
    i64 x, y, gcd;
    extended_euclid(999999LL, nmod, x, y, gcd);
    if(x < 0) {
        x += nmod;
        assert(x >= 0 && x < nmod);
    }
    i64 n91 = x;
    extended_euclid(999999LL*999999LL, nmod, x, y, gcd);
    if(x < 0) {
        x += nmod;
        assert(x >= 0 && x < nmod);
    }
    i64 n92 = x;
    i64 r1 = powermodule(10LL, 6LL*n, nmod);
    --r1;
    r1= multmod(r1 ,n92, nmod);
    r1= multmod(r1, 1000000LL, nmod);

    i64 r2 = multmod(n, n91, nmod);

    r1 -= r2;
    r1 = multmod(r1, rep, nmod );
    i64 pten = power(10LL, (i64)cnt);
    r1 = multmod(r1, pten, nmod);
    r1 += multmod(tail, n+1, nmod);
    return r1;
}
int main()
{
    vector<i64> v15;
    vector<i64> vrep;
    deque<int> deq = {1,2,3,4,3,2};

    i64 repet, tail;
    for(unsigned int i = 0; i<15; ++i){
       deque_rotate(deq, i+1, repet, tail ) ;
       printf("%u %lld %lld\n", i+1, repet, tail);
       v15.push_back(tail);
       vrep.push_back(repet);
    }

    i64 sum = 0;
    for(unsigned int i = 0; i < v15.size(); ++i){
        sum += sumAllWithSameTail(v15[i], vrep[i], i+1);
    }
    sum %= nmod;
    printf("test result %lld\n", sum);




    return 0;
    printf("%lld %lld\n", nmax/15, nmax%15);
    i64 p = 41*41;
    i64 q = 271*271;

    i64 quo = nmax/15;
    i64 p1 = (6*quo) % (41*40);
    i64 p2 = (6*quo) % (271*270);
    i64 x, y, gcd = 0;
    extended_euclid(999999LL, nmod, x, y, gcd);
    x+= nmod;
    printf("inverse of 999999 is %lld\n", x);
    i64 mult = 1234320000LL % nmod;
    i64 r1 = powermodule(10LL, p1, p);
    --r1;
    r1 *= x;
    r1 %= nmod;
    r1 *= mult;
    r1 %= nmod;
    i64 r2 = powermodule(10LL, p2, q);
    --r2;
    r2 *= x;
    r2 %= nmod;
    r2 *= mult;
    r2 %= nmod;
    vector<i64> vp, vq;
    vector<i64> vr;
    vp.push_back(p);
    vp.push_back(q);
    vr.push_back(r1);
    vr.push_back(r2);

    i64 result = chinese_remainder_theorem(vp, vr);
    result += 1234;
    result %= nmod;
    printf("%lld\n", result);
}
