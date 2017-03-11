#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_N 20000
#define MAX_LEN ((MAX_N/2)*9+1)
#define LIMIT_INC 285

typedef unsigned long long int_64;

int main (int argc, const char * argv[]) {
    int_64 MOD = 14348907ULL;
    
    int_64 cc[MAX_LEN];  // count  with leading zeros
    int_64 ss[MAX_LEN];  // sum with leading zeros
    int_64 pcc[MAX_LEN]; // previous count
    int_64 pss[MAX_LEN]; // previous sum
    
    int_64 total, pow_10;
    int_64 sc_sum, ss_sum;
    int_64 si, ci;
    
    int sum_limit, next_limit, i, has_next;
    clock_t start = clock();
    
    total = 45ULL;
    pow_10 = 1ULL;
    sum_limit = 10;
    
    if (MAX_N == 1) {
        printf("T(%d) = %d\n",MAX_N,total);
        return 0;
    }
    
    /* zero arrays */
    memset(ss,0,sizeof(int_64)*MAX_LEN);
    memset(cc,0,sizeof(int_64)*MAX_LEN);
    memset(pss,0,sizeof(int_64)*MAX_LEN);
    memset(pcc,0,sizeof(int_64)*MAX_LEN);
    
    /* initialise DP */
    for(i=0; i<sum_limit; i++) {
        ss[i] = (int_64)i;
        cc[i] = 1ULL;
    }
    pcc[0] = 1ULL;
    
    while (1) {
        pow_10 = (pow_10*10ULL)%MOD;
        has_next = 1;
        
        /* add to the total for numbers of length n+1 and n+2 */
        for(i = next_limit = 1 ; has_next; ) {
            
            next_limit += LIMIT_INC;
            if (next_limit >= sum_limit) {
                next_limit = sum_limit;
                has_next = 0;
            }
            
            for(; i < next_limit; i++) {
                ss[i] %= MOD;      // sum with leading zeros
                cc[i] %= MOD;      // count with leading zeros
                
                si = ss[i] + MOD - pss[i]; // sum without leading zeros
                ci = cc[i] + MOD - pcc[i]; // count without leading zeros

                total += ((cc[i]*pow_10)%MOD)*(101ULL*si+45ULL*ci) + 11ULL*ci*ss[i];
            }
            total %= MOD;
        }
        
        if(sum_limit == MAX_LEN) {
            break;
        }
        
        /* copy new values to prev array */
        memcpy(pcc, cc, sizeof(int_64)*sum_limit);
        memcpy(pss, ss, sizeof(int_64)*sum_limit);
        
        sum_limit += 9;
        
        ss_sum = 0ULL; // sum of ss[i]..ss[i-9]
        sc_sum = 0ULL; // sum of 1*cc[i-1]..9*cc[i-9]
        
        for(i=1; i<10; i++) {
            cc[i] += cc[i-1];
            sc_sum += cc[i-1];
            ss_sum += pss[i];
            ss[i] = 10ULL*ss_sum + sc_sum;
        }
        for(;i<sum_limit; i++) {
            cc[i] = pcc[i] + cc[i-1] - pcc[i-10];
            sc_sum = sc_sum + cc[i-1] - 10ULL*pcc[i-10];
            ss_sum = ss_sum + pss[i] - pss[i-10];
            ss[i] = 10ULL*ss_sum + sc_sum;
        }
    }
    
    /* We overshot the value if MAX_N is even so compensate */
    if(MAX_N%2 == 0) {
        int_64 sub = 0ULL;
        has_next = 1;
        for(i = next_limit = 1 ; has_next; ) {
            
            next_limit += LIMIT_INC;
            if (next_limit >= sum_limit) {
                next_limit = sum_limit;
                has_next = 0;
            }
            
            for(; i < next_limit; i++) {
                si = ss[i] + MOD - pss[i];
                ci = cc[i] + MOD - pcc[i];
            
                sub += ((cc[i]*pow_10)%MOD)*(100ULL*si+45ULL*ci)+10ULL*ci*ss[i];
            }
            
            sub %= MOD;
        }
        
        total = (total + MOD - sub)%MOD;
    }

    printf("T(%d) = %d\n",MAX_N,total);
    printf("Time taken: %f s\n", ((float)(clock()-start))/CLOCKS_PER_SEC);
    return 0;
}
