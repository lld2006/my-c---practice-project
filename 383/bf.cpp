#include <cstdio>
#include <string>
using namespace std;
int f5(int num)
{
    int ret = num;
    while(num){
        int res = num % 5;
        ret -= res;
        num/=5;
    }
    return ret;
}
int main(int argc, char** argv)
{
    int target = stoi(string(argv[1]));
    int cnt = 0;
    for(unsigned int i = 5; i <= target; i+=5){
        if(2*f5(i) > f5(2*i-1) ){
            ++cnt;
            printf("%u %d\n", i, cnt);
        }
    }
    printf("%d\n", cnt);
}
