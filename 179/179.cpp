#include <cstdio>
#include <vector>
using namespace std;
//lesson, for each div less than sqrt(target), if
//n divide this number x, so will be n div n/x
//in this way the run time can be reduce by a factor of 2
int main()
{
    int target = 100000000;
    vector<int> vn;
    vn.resize(target + 1, 2);
    vn[0] = 1;
    vn[1] = 1;
    for(int nx = 2; nx*nx <= target; ++nx){
        vn[nx*nx] += 1;
        for(int ny = nx*nx+nx; ny < vn.size(); ny += nx){
            vn[ny] += 2;
        }
    }
    int cnt = 0;
    for(unsigned int i = 2; i< target-1; ++i){
        if(vn[i] == vn[i+1]) 
            ++cnt;
    }
    printf("%d\n", cnt);
}
