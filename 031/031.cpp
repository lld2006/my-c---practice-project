#include <cstdio>
#include <vector>
using namespace std;
int recursive_find(int value, int cpos, const vector<int>& vc )
{
    if(cpos == 0)
        return 1;
    int unit = vc[cpos];
    int nmax = value / unit;
    int sum = 0;
    for( int i = 0; i <= nmax; ++i ){
        sum += recursive_find(value - i*unit, cpos-1, vc);
    }
    return sum;
}
int main()
{
    vector<int> vc = {1,2,5,10, 20,50,100,200};
    int value = recursive_find(200, 7, vc);
    printf("%d\n", value);
}
