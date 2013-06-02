#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vn;
    vn.resize(1000, 0);
    vn[1]=1;
    vn[2]=2;
    for(unsigned int i = 3; i< vn.size(); ++i){
        if(i & 1){
            vn[i] = vn[i/2];
        }else{
            vn[i] = vn[i/2] + vn[i/2-1];
        }
        printf("%d %d\n",i, vn[i]);
    }
}
