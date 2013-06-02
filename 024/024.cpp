#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector<int> vn={2,7,0,1,3,4,5,6,8,9};
    int target = 1000000-362880*2-6*40320;
    int i = 0;
    while(i < target - 1){
        next_permutation(vn.begin(), vn.end());
        ++i;
    }
    for(unsigned int i = 0; i< vn.size(); ++i){
        printf("%d",vn[i]);
    }
    printf("\n");

}
