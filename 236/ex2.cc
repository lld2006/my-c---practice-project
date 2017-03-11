#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
   int c;
   if(a < b) {
      c = a; a = b; b = c;
   }
   while(b) {
      c = a; a = b; b = c % b;
    }
    return a;
}

struct Frac {
    int p, q, u, v, w;
} f[2000000];
int n;

int comp(const void *a, const void *b)
{
    long long r = (long long)((struct Frac *)a)->p * (long long)((struct Frac *)b)->q
                - (long long)((struct Frac *)b)->p * (long long)((struct Frac *)a)->q;
    return r>0 ? 1 : (r < 0 ? -1 : 0);
}

int dp[] = {1, 5, 59, 5*59};
int dq[] = {1,    2,    3,    5,    6,    9,    10,    15,    18,    30,    45,    90,
            1*41, 2*41, 3*41, 5*41, 6*41, 9*41, 10*41, 15*41, 18*41, 30*41, 45*41, 90*41};
int main()
{
    const int sa1 = 5248, sa235 = 1312+2624+3936, sa4 = 5760;
    const int sb1 = 640, sb235 = 1888+3776+5664, sb4 = 3776;
    const int sa = sa1+sa4+sa235, sb = sb1+sb4+sb235;
    int n = 0, cp = 0;
    //   a1=p*41/d1*u,   b1=q*5/d1*u,  d1=gcd(p,5)*gcd(q,41)
    //   a2=p*90/d2*v,   b2=q*59/d2*v, d2=gcd(p,59)*gcd(q,90)
    // a235=p*41/d3*w, b235=q*59/d3*w, d3=gcd(p,59)*gcd(q,41)
    // u <= 128*d1/p, u <= 128*d1/q
    // v <=  64*d2/p, v <=  64*d2/q
    // w <= 192*d3/p, w <= 192*d3/q
    // (p2*41/d1*sb-q2*5/d1*sa)u+(p2*90/d2*sb-q2*59/d2*sa)v+(p2*41/d3*sb-q2*59/d3*sa)w=0
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 24; j++) {
            int d1 = gcd(dp[i], 5) * gcd(dq[j], 41);
            int d2 = gcd(dp[i],59) * gcd(dq[j], 90);
            int d3 = gcd(dp[i],59) * gcd(dq[j], 41);
            for(int q = dq[j]; q <= 128*d1 && q <= 64*d2 && q <= 192*d3; q += dq[j]) {
                for(int p = dp[i]; p < q; p += dp[i]) {
                    if(gcd(p, q) > 1) continue;
                    if(gcd(41*p, 5*q) != d1 || gcd(90*p, 59*q) != d2
                       || gcd(41*p, 59*q) != d3)
                        continue;
                    cp ++;

                    long long a = (long long)p*(long long)p*41LL/d1*sb
                                    -(long long)q*(long long)q*5LL/d1*sa;
                    long long b = (long long)p*(long long)p*90LL/d2*sb
                                    -(long long)q*(long long)q*59LL/d2*sa;
                    long long c = (long long)p*(long long)p*41LL/d3*sb
                                    -(long long)q*(long long)q*59LL/d3*sa;
                    long long uc = 128*d1/q, vc = 64*d2/q, wc = 192*d3/q;
                       
                    //check if a*u+b*v+c*w has a solution
                    bool valid = false;
                    for(long long u = 1; u <= uc && !valid; u++)
                        for(long long v = 1; v <= vc && !valid; v++)
                            if((a*u+b*v) % c == 0 && (a*u+b*v) / (-c) > 0
                                && (a*u+b*v) / (-c) <= wc) {
                                f[n].u = (int)(u); f[n].v = (int)(v);
                                f[n].w = (int)(-(a*u+b*v)/c);
                                f[n].p = q; f[n].q = p;
                                ++n;
                                valid = true;
                            }
                }
            }
        }
    qsort(f, n, sizeof(Frac), comp);
    printf("total: %d (pairs<p,q> checked : %d)\n", n, cp);
    for(int i = 0; i < n; i++)
        printf("%d / %d : %d %d %d\n", f[i].p, f[i].q, f[i].u, f[i].v, f[i].w);
    return 0;
}
