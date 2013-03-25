#include <cstdio>
int main(){
    long double prob=1;
    int prime = 22;
    int total = 97;
    for(int i = 1; i<= 22; ++i){
        long double tpb = 1;
        for(int j = 1; j<= i; ++j)
            tpb *= (long double)(prime+1-j)/(long double)j/(long double)(total+1-j);
        prob += (i & 1)? -tpb:tpb;
    }
    prob *= (long double)(23)/(99*98);
    printf("%30.20Lf\n", prob);
}
