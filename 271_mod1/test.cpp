#include <cstdio>
typedef long long int i64;
int main()
{
    i64 prod = 210;
    for(i64 i = 1; i<prod; ++i){
        i64 n3 = i *i*i; 
        if(n3 % prod == 1)
            printf("%lld\n", i);
    }
}
