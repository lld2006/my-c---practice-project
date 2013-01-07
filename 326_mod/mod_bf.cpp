#include <cstdio>
int f(int n0)
{
    int res = n0%6;
    int n = n0/6;
    switch(res){
        case 0:
            return 3*n;
        case 1:
            return 4*n+1;
        case 2:
            return 3*n+1;
        case 3:
            return n;
        case 4:
            return 6*n+3;
        case 5:
            return n;
    }
}
int main()
{
    int range = 10000;
    int nmod = 1000;
    int cnt = 0;
    int phase1=0, phase2=0, phase3=0;
    for(unsigned int start = 1; start <= range; ++start){
        int sum = 0;
        for(unsigned int end = start; end<=range; ++end){
            sum += f(end);
            if(sum % nmod ==0){
                printf("%d %d\n", start, end);
                ++cnt;
                int ns = (start-1)/6;
                if(end <= (ns+1)*6)
                    ++phase1;
                else if(end <=(ns+2)*6)
                    ++phase2;
                else
                    ++phase3;
            }
        }
    }
    printf("%d %d %d %d\n", phase1, phase2, phase3, cnt);
}
