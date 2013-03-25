#include <vector>
#include <cstdio>
using namespace std;
enum {UNDECIDED=0, ODD, EVEN};
vector<vector<vector<int>>> vflag;
vector<vector<int>> vdisp;
int check(int x, int y, int z)
{
    int t = vflag[x][y][z] ;
    if(t != UNDECIDED)
        return t;
        
    for(unsigned int dir = 0; dir < vdisp.size(); ++dir){
        for(unsigned int j = 1; ;++j){
            int x1 = x - vdisp[dir][0]*j;
            int y1 = y - vdisp[dir][1]*j;
            int z1 = z - vdisp[dir][2]*j;
            if(x1 < 0 || y1 <0 || z1 < 0) break;
            if(check(x1,y1,z1) == EVEN){
                vflag[x][y][z] = ODD;
                return ODD;
            }
        }
    }
    vflag[x][y][z] = EVEN;
    return EVEN;
}
int main()
{
    vdisp.resize(7); 
    for(unsigned int i= 0; i < vdisp.size(); ++i)
        vdisp[i].resize(3, 0);
    vdisp[0][0] = 1;
    vdisp[1][1] = 1;
    vdisp[2][2] = 1;
    vdisp[3][0] = 1;
    vdisp[3][1] = 1;
    vdisp[4][0] = 1;
    vdisp[4][2] = 1;
    vdisp[5][1] = 1;
    vdisp[5][2] = 1;
    vdisp[6][0] = 1;
    vdisp[6][1] = 1;
    vdisp[6][2] = 1;
    int limit = 100;
    vflag.resize(limit+1);
    for(unsigned int i = 0; i < vflag.size(); ++i)
        vflag[i].resize(limit+1);
    for(unsigned int i = 0; i< vflag.size(); ++i)
        for(unsigned int j = 0; j < vflag[i].size(); ++j)
            vflag[i][j].resize(limit+1, 0);
    int ucnt = limit*limit*limit-1;
    vflag[0][0][0]=EVEN;
    int total = 0;
    for(unsigned int i = 0; i<=limit;++i)
        for(unsigned int j =i;j<=limit;++j)
            for(unsigned int k= j; k<=limit; ++k){
                int t = check(i,j,k); 
                if(t == EVEN){
                    printf("%d %d %d\n",i,j,k);
                    total += (i+j+k);
                }
            }
    printf("%d\n", total);
}
