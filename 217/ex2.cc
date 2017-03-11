#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_N 20000
#define MAX_LEN (MAX_N/2)*9

typedef unsigned long long int_64;

int main (int argc, const char * argv[]) {
    int_64 MOD = 1;
    
    int_64 s[MAX_LEN];  // sum with no leading zeros
    int_64 ss[MAX_LEN]; // sum with leading zeros (sum of all s[i] up to current)
    int_64 c[MAX_LEN];  // count with no leading zeros
    int_64 cc[MAX_LEN]; // count with leading zeros (count of all c[i] up to current)
    
    int_64 total, pow_10, sub;
    int_64 cci, ssi, si, ci, cij;
    
    int n, sum_limit, i, j;
    clock_t start = clock();
    
    /* calculate MOD */
    for (i=0; i < 15; i++) {
        MOD *= 3ULL;
    }
    
    total = 45ULL;
    pow_10 = 1ULL;
    n = 1;
    sum_limit = 9;
    
    if (MAX_N == 1) {
        printf("%lld\n",total);
        return 0;
    }
    
    /* zero arrays */
    memset(s, 0,sizeof(int_64)*MAX_LEN);
    memset(ss,0,sizeof(int_64)*MAX_LEN);
    memset(c, 0,sizeof(int_64)*MAX_LEN);
    memset(cc,0,sizeof(int_64)*MAX_LEN);
    
    /* initialise DP */
    for(i=0; i<sum_limit; i++) {
        s[i] = 1ULL+(int_64)i;
        c[i] = 1ULL;
    }
    
    while (1) {
        pow_10 = (pow_10*10ULL)%MOD;
    
        /* add to the total for string of length n and n+1 */
        //printf("sum %d\n", sum_limit);
        for(i=0; i<sum_limit; i++) {
            ci = c[i] %= MOD;
            si = s[i] %= MOD;
            
            cc[i] = (cc[i]+c[i])%MOD;
            cci = (cc[i]*pow_10)%MOD;
            
            ssi = ss[i] = (s[i] + ss[i])%MOD;
            
            total += 101ULL*cci*si + 11ULL*ci*ssi + 45ULL*ci*cci;
            total %= MOD;
        }
        
        n+=2;
        
        if(n >= MAX_N) {
            break;
        }
        
        /* calculate the next row */
        //printf("update %d\n", sum_limit*10);
        for(i=sum_limit-1; i >= 0; i--) {
            si = s[i] = s[i]*10;
            ci = c[i];
            cij = ci;
            for(j=i+1; j<i+10; j++) {
                s[j] += si + cij;
                c[j] += ci;
                cij += ci;
            }
        }
        
        sum_limit += 9;
    }
    
    /* We overshot the value if MAX_N is even so compensate */
    if(MAX_N%2 == 0) {
        sub = 0ULL;
        for(i=0; i<sum_limit; i++) {
            cci = (pow_10*cc[i])%MOD;
            sub += 100ULL*cci*s[i]+10ULL*c[i]*ss[i]+45ULL*c[i]*cci;
            sub %= MOD;
            //printf("%d %lld %lld\n",i, sub);
        }
        
        total = (total + MOD - sub)%MOD;
    }

    printf("T(%d) = %lld\n",MAX_N,total);
    printf("Time taken: %f s\n", ((float)(clock()-start))/CLOCKS_PER_SEC);
    return 0;
}
