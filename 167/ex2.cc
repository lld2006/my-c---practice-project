#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long ulam2(int n, long long i){
    if (i < 1 || !(n&1) || n < 5) return 0;
    if (i == 1) return 2;
    if (i < (n+7)/2) return (n + 2*(i-2));
    if (2*i == n+7) return (2*n+2);
    long long l = i - 4;
    long long ul = n+2;
    long long st = 1 | (1LL << (int)n);
    long long nxt = st | (1LL << (int)(n-1));
    double start = clock();
    for(; l > 0; l--){
        if (nxt == st){
            double stop = clock();
            long long per = i-3-l;
            printf("Ulam(2,%d): Found quasiperiod of length %lld, spanning %lld in %.3lf seconds\n"
                   ,n, per,ul-n, (stop-start)/CLOCKS_PER_SEC);
            long long q = l/per;
            long long r = l%per;
            ul = (q+1)*(ul-n) +n;
            if (!r) return ul;
            ul += 2;
            nxt |= 1LL << (int)(n-1);
            l = r;
            continue;
        }
        int a = 1;
        while(!(nxt&1)){
            a++;
            nxt >>= 1;
        }
        nxt >>= 1;
        nxt ^= st;
        ul += (a << 1);
    }
    return ul;
}

int main(int argc, char** argv){
    int n;
    long long k = 100000000000LL;
    long long sum = 0, ul;
    double start = clock();
    for(n = 5; n <= 21; n += 2){
        ul = ulam2(n,k);
        sum += ul;
        printf("%lld\n",ul);
    }
    printf("Sum: %lld\n",sum);
    double stop = clock();
    printf("took %.3lf seconds\n",(stop-start)/CLOCKS_PER_SEC);
    return 0;
}
