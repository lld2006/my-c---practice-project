#include <cstdio>
//any better algo?
int main()
{
    int low = 1; int high = 1;
    int count = 0;
    for(int n=2;n<=9; ++n)//number of digits
    {
        low *= 10;
        high = low*10 ;
        for(int i =low+2; i< high - 2;  ++i){//all number that have n digits
            if(i % 100000000 ==0)printf("%d\n", i);
            bool flag = true;
            int res = i %10;
            if(res == 0) continue;
            int hdigi = i / low;
            if(hdigi >= res ||((hdigi+res) %2==0)) continue;
            int norig = i;
            int nrev =0 ;
            for(int j = 0 ; j <n; ++j){
                int res = norig % 10;
                nrev *= 10;
                nrev += res;
                norig /= 10;
            }
            int sum = nrev + i;
            while(sum){
                    flag = false;
                    break;
                }
                sum/=10;
            }
            if(flag)
                ++count;
        }

    }
    printf("%d\n", 2*count);
}
