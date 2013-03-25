//from 1 to num;
#include <cstdio>
int f(int num)
{
    int nd=1;
    int prod = 10;
    int p2  = 9;
    int cnt = 0;
    while(prod <= num){
        cnt += p2*nd;
        prod *= 10;
        p2 *= 10;
        ++nd;
    }
    cnt += (num-prod/10+1)*nd;
    return cnt;
}
int search_digit(int nt)
{
    int low = 1; 
    int high = 1000000;
    int flow = f(low);
    int fhigh = f(high);
    int fmid;
    int mid;
    while(low < high){
        mid = (low+high)/2+1;
        fmid = f(mid);
        if(fmid < nt){
            low = mid;
            flow = fmid;
        }else{
            high = mid - 1;
            fhigh = fmid;
        }
    }
    if(flow < nt)
        flow = f(++low);
        
    while(nt < flow){
        --flow;
        low/=10;
    }
    return low%10;
}
int main()
{
    printf("%d %d %d %d %d %d %d\n", search_digit(1), search_digit(10), search_digit(100), search_digit(1000), search_digit(10000), search_digit(100000), search_digit(1000000));
}
