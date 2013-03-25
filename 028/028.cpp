#include <cstdio>
int main()
{
    int n = 500;
    int val = 1;
    val += 2*n*(n+3)+n*(n+1)*(2*n+1)/3*8;
    printf("%d\n", val);
}
