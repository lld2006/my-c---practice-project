#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector<int> vn;
    vn.push_back(2);
    vn.push_back(0);
    vn.push_back(1);
    vn.push_back(3);
    vn.push_back(4);
    vn.push_back(5);
    vn.push_back(6);
    vn.push_back(7);
    vn.push_back(8);
    vn.push_back(9);
    int target = 1000000-362880*2;
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
