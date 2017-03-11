#include <cstdio>
int mks(int n, int m, int k, int s){
    if(n > m) 
        return n - s;
    else{
        int value = mks(n+k, m, k, s);
        return mks(value, m, k, s);
    }
}

int sf(int m, int k, int s){
    int total = 0;
    for(int v = m - s; v <= m; ++v){
        if(mks(v, m, k, s) == v){
            total += v;
            printf("fixed point for m %d k %d s %d fix %d\n", m, k, s, v);
        }
    }
    return total;
}

int main()
{
    int ftot = 0;
    int m = 10;
    int p = 10;
    for(int k = 2; k <=p; ++k)
        for(int s = 1; s < k; ++s)
            ftot += sf(m, k, s);
    printf("m %d p %d tot %d\n", m, p, ftot);
}
