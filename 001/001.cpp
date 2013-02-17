#include <cstdio>
#include <cstdlib>
int main(int argc, char** argv)
{
    int nmax = atoi(argv[1])-1;
    int n3 = nmax/3;
    int n5 = nmax/5;
    int n15 = nmax/15;
    printf("%d\n", 3*(n3+1)*n3/2+5*(n5+1)*n5/2-15*(n15+1)*n15/2);
}
