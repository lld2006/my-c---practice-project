#include <cstdio>
#include <cstdlib>
int main(int argc, char** argv)
{
    if(argc < 2)
        printf("please provide nmax to this problem\n");
    int nmax = atoi(argv[1]);
    int value = nmax*(nmax+1);
    int value2 = value*(2*nmax+1)/6;
    value /= 2;
    printf("%d\n", value*value-value2 );
}
