#include <cstdio>
#include <bitset>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
int limit = 2000;
int lim1 = 1000;
bitset<1357668501> fbit;
//lesson, first index3o is not correct! ssecond, process is not quite right especially xy
//need to speed up
void set_fbit(int x, int y, int z, int x0, int y0, int z0)
{
    assert(x != x0 || y != y0 || z!= z0);
    assert(z<=limit);
    fbit.set(index3o(x,y,z));
}
void process_x(int x, int y, int z)
{
    for(int i = x+1; i <= y; ++i)
        set_fbit(i,y,z, x, y, z);
    for(int i = y+1; i <= z; ++i)
        set_fbit(y,i,z, x,y, z);
    for(int i = z+1; i <= limit-x; ++i)
        set_fbit(y,z,i, x,y,z);
}

void process_y(int x, int y, int z)
{
    for(int j = x+1; j < y; ++j)
        set_fbit(x,j,z, x,y,z);
    for(int j = y+1; j <= z; ++j)
        set_fbit(x,j,z, x,y,z);
    for(int j = z+1; j <= limit; ++j)
        set_fbit(x,z,j, x,y,z);
}
void process_z(int x, int y, int z)
{
    for(int k = x+1; k < y; ++k)
        set_fbit(x,k,y,x,y,z);
    for(int k = y; k < z; ++k)
        set_fbit(x,y,k,x,y,z);
    for(int k = z+1; k <= limit; ++k)
        set_fbit(x,y,k, x,y,z);
}
void process_xy(int x, int y, int z)
{
    //all in up direction
    for( int t = 1; t<= z-y; ++t)
        set_fbit(x+t, y+t,z, x,y,z);
    if(limit -y < z-x){
        for( int t = z-y+1; t<= limit-y; ++t)
            set_fbit(x+t,z, y+t,x,y,z);
    }else{
        for(int t = z-y+1; t<= z-x; ++t)
            set_fbit(x+t, z,y+t,x,y,z);
        
        for(int t = z-x+1; t<=limit-y;++t)
            set_fbit(z,x+t,y+t,x,y,z);
    }
}
void process_yz(int x, int y, int z)
{
    for( int t = 1; t<= limit-z; ++t)//up
        set_fbit(x,y+t,z+t,x,y,z);
    for( int t = 1; t<= y-x; ++t)//down
        set_fbit(x,y-t,z-t,x,y,z);
}
void process_xz(int x, int y, int z)
{
    if(y-x < limit -z){
        for( int t = 1; t<= y-x; ++t)
            set_fbit(x+t,y,z+t, x,y,z);
        for( int t =y-x+1;t<=limit-z;++t)
            set_fbit(y,x+t,z+t,x,y,z);
    }else{
        for(int t=1; t<=limit-z; ++t)
            set_fbit(x+t,y,z+t,x,y,z);
    }
}
void process_xyz(int x, int y, int z)
{
    for( int t = 1; t<= limit-z; ++t)
        set_fbit(x+t,y+t,z+t, x,y,z);
}
void process(int x, int y, int z)
{
    assert(x <=y && y<=z && z<=limit);
    assert(!fbit.test(index3o(x, y, z)));
    process_x(x,y,z);
    process_y(x,y,z);
    process_z(x,y,z);
    process_xy(x,y,z);
    process_yz(x,y,z);
    process_xz(x,y,z);
    process_xyz(x,y,z);
}
int main()
{
    i64 total = 0;
    for(int k = 0; k<=limit;++k){
        if(k % 20 == 0) printf("%d\n", k);
        for( int j = 0; j<=k; ++j){
            for( int i = 0; i<=j;++i){
                if(fbit.test(index3o(i,j,k)))
                    continue;
                //printf("p %d %d %d\n",i,j,k);
                process(i, j, k);
            }
        }
    }
    vector<int> va, vb, vc;
    for( int i = 0; i<=lim1; ++i)
        for( int j = i; j<=lim1;++j)
            for( int k = j; k<=lim1;++k){
                if(!fbit.test(index3o(i,j,k))){
                    va.push_back(i);
                    vb.push_back(j);
                    vc.push_back(k);
                    total += (i+j+k);
                }
            }
    printf("%lld\n", total);
}
