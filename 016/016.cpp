#include <cstdio>
#include <bitset>
#include <vector>
using namespace std;
// I saw that one of the guy in project euler used bitset 
// as carry over  for this problem. but the code is not so clear.
// I will try my own version
const int npow = 1000;
int main()
{
    bitset<npow+1> carry1;
    bitset<npow+1> carry2;
    vector<int> digits;
    digits.resize(npow+1, 0);
    //digits stores each digit of 2^n
    digits[1] = 2;
    int start = 2;
    int next_start = 2;
    int sum = 0;
    for(int i = 1; i <= npow; ++i) {
        start = next_start;
        next_start = 0;
        for(int j = start; j <= npow; ++j){
            digits[j] = (2 * digits[j-1] + carry1[j-1]) % 10;
            if(digits[j-1] > 4) {
                carry2.set(j-1);
                if(next_start == 0)
                    next_start=j;
            }
        }
        sum += digits[npow];
        if(next_start == 0)
            break;
        digits[next_start-1] = 0;
        swap(carry1, carry2);
        carry2.reset();
    }
    printf("%d\n", sum);
}
