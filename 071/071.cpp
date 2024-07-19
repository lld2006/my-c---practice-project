#include <cstdio>
// this code is very stupid. Based on Farey's Sequence property, the fraction on the left side of 3/7
// should be satisfy a/b < a1/b1 and b*a1-a*b1=1, so we just need to use extended Euclidean
// or just be observation to find a special solution of the equation and then find the largest 
// denominator of all fractions less than 3/7.
int main()
{
    int nx = 1;
    int dx = 3;
    for(unsigned int i = 3; i <= 1000000; ++i){
        if(i % 7 == 0) continue;
        int num = i * 3/7;
        if(num * dx > nx * i){
            nx = num;
            dx = i;
        }
    }
    printf("%d %d\n", nx, dx);
}
