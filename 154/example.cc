#include <cstdio>
int mul2(int n){
    int m = 0;
    while(!(n&1)){
        m++;
        n >>= 1;
    }
    return m;
}

int mul5(int n){
    int m = 0;
    while(!(n%5)){
        m++;
        n /= 5;
    }
    return m;
}

int main(){
    int bound = 200000;
    long long sum = 0;
    int val2[bound+1], val5[bound+1]; // number of factors 2/5 in i!
    val2[0] = 0;
    val2[1] = 0;
    val5[0] = 0;
    val5[1] = 0;
    val5[2] = 0;
    val5[3] = 0;
    val5[4] = 0;
    int v2 = 0, v5  = 0;
    int i;
    for(i = 2; i < bound; i += 2){
        v2 += mul2(i);
        val2[i] = val2[i+1] = v2;
    }
    v2 += 6;
    val2[bound] = v2;
    for(i = 5; i < bound; i += 5){
        v5 += mul5(i);
        val5[i] = val5[i+1] = val5[i+2] = val5[i+3] = val5[i+4] = v5;
    }
    v5 += 5;
    val5[bound] = v5;
    v2 -= 11;
    v5 -= 11;
    int j,k,vi2,vi5;
    for(i = 2; i < 65625; i++){
        if (!(i&1023)){
            // look how many we got so far
            printf("%d:\t%lld\n",i,sum);
        }
        vi5 = val5[i];
        vi2 = val2[i];
        int jb = ((bound - i) >> 1)+1;
        // I want i <= j <= k
        // by carry analysis, I know that if i < 4*5^5+2, then
        // j must be at least 2*5^6+2
        for(j = (i < 12502) ? 31252 : i; j < jb; j++){
            k = bound - i - j;
            if (vi5 + val5[j] + val5[k] < v5
                    && vi2 + val2[j] + val2[k] < v2){
                if (j == k || i == j){
                    sum += 3;
                } else {
                    sum += 6;
                }
            }
        }
    }
    printf("Total:\t%lld\n",sum);
    return 0;
}
