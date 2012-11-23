#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
using namespace std;
enum COLOR {WHITE=0, BLACK=1};
enum DIRECTION {UP=0, RIGHT, DOWN, LEFT};
vector<int> vcolor;
int dim = 1000;//-500 -- 500
int color(int posx, int posy)
{
    return vcolor[(posy+dim)*(2*dim+1)+(posx+dim)];
}
void set_color(int posx, int posy, int bw)
{
    vcolor[(posy+dim)*(2*dim+1)+(posx+dim)] = bw;
}
void move(int& posx, int& posy, int dir)
{
    if(dir == UP){
        ++posy;
    }else if(dir ==RIGHT){
        ++posx;
    }else if(dir == DOWN){
        --posy;
    }else{
        --posx;
    }
}
int main()
{
    int steps = 20000;
    vector<int> vcnt;
    vcnt.resize(steps, 0);
    
    vcolor.resize((2*dim+1)*(2*dim+1), 0);
    int posx=0, posy=0;
    int dir = 0;
    int cnt = 0;
    for(unsigned int i = 0; i< steps; ++i){
        if(color(posx, posy)== WHITE){
            set_color(posx, posy, BLACK);
            ++dir;
            dir %= 4;
            move(posx, posy, dir);
            ++cnt;
            vcnt[i] = cnt;
        }else{
            set_color(posx, posy, WHITE);
            --dir;
            if(dir < 0) dir += 4;
            move(posx, posy, dir);
            --cnt;
            vcnt[i] = cnt;
        }
    }
    for(int ns = 12000; ns < 12500; ++ns)
        printf("%d\n", vcnt[ns]-vcnt[ns-104]);
    i64 nx = 1000000000000000000LL;
    i64 res = nx % 104;
    i64 ny = (15000/104)*104+res;
    assert((nx-ny)%104==0);
    i64 result = (nx - ny)/104*12+vcnt[ny-1];
    printf("%lld\n", result);
}
