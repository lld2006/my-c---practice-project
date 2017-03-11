#include "../lib/typedef.h"
#include <cstdio>
#include <vector>
#include <cassert>
struct sexlet 
{
    int x; int y; int z;
    int dx; int dy; int dz;
    sexlet(int x1, int y1, int z1, int dx1, int dy1, int dz1){
        x = x1; y = y1; z = z1;
        dx = dx1; dy = dy1; dz = dz1;
    }
};

vector<vector<vector<vector<sexlet>>>> vblk;
int limit = 50000;
void newxdx(int x1, int dx1, int  x2, int dx2, int& x, int& dx)
{
    int max2 = x2 + dx2;
    int max1 = x1 + dx1;
    if(max1 <= x2 || max2<= x1) {
        x = 0; 
        dx = 0;
    }else{
        if(x1 < x2 ) {
            x = x2;
            dx = max1 < max2? max1 -x : dx2;
        }else{
            x= x1; 
            dx = max1 < max2? dx1: max2 - x;
        }
    }
    assert(dx>= 0);
}

vector<i64> vn;
void create_positions(vector<i64>& vn)
{
    vn.resize(6*limit+1);
    for( int i = 1; i <= 6*limit; ++i){
        if(i <= 55 ) { //lesson missed a equal sign here
            i64 val = 100003LL-200003LL*i+300007LL*i*i*i;// lesson overflow
            val %= 1000000;
            vn[i] = val;
        }else{
            vn[i] = vn[i-55] + vn[i-24];
            vn[i] %= 1000000;
        }
    }
    for(unsigned int i = 1; i < vn.size(); ++i){
        if((i-1) % 6 < 3){
            vn[i] %= 10000;
        }else{
            vn[i] %= 399;
            ++vn[i];
        }
    }
}
i64 in_ex(int cindex, sexlet clet, const vector<sexlet>& vlet){
    if(clet.dx == 0|| clet.dy==0 ||clet.dz==0) return 0;
    i64 sum = 0;
    for(unsigned int j = cindex+1; j <vlet.size(); ++j ){
        int xt, dxt, yt, dyt, zt, dzt;
        newxdx(clet.x, clet.dx, vlet[j].x, vlet[j].dx, xt, dxt );
        newxdx(clet.y, clet.dy, vlet[j].y, vlet[j].dy, yt, dyt );
        newxdx(clet.z, clet.dz, vlet[j].z, vlet[j].dz, zt, dzt );
        sum += dxt*dyt*dzt;
        sum -= in_ex(j, sexlet(xt, yt, zt, dxt, dyt, dzt), vlet );
    }
    return sum;
}
i64 volume(vector<sexlet>& vi)
{
   i64 sum = 0; 
   for(unsigned int i = 0; i < vi.size(); ++i){
        sum += vi[i].dx * vi[i].dy * vi[i].dz;
        sum -= in_ex(i, vi[i], vi);
   }
   return sum;
}
void divide_cube(int x, int y, int z, int dx, int dy, int dz, int seg)
{
    vector<IntPair> vx, vy, vz;
    int nx1 = x/seg; 
    int nx2 = (x+dx)/seg;
    int ny1 = y/seg;
    int ny2 =(y+dy)/seg;
    int nz1 = z/seg;
    int nz2 = (z+dz)/seg; //lesson, copy from x dx, did not change to the correct value
    if(nx1 ==nx2){
        vx.push_back(IntPair(x, dx));
    }else{
        vx.push_back(IntPair(x, nx2*seg-x));
        vx.push_back(IntPair(nx2*seg, x+dx-nx2*seg));
    }
    if(ny1 ==ny2){
        vy.push_back(IntPair(y, dy));
    }else{
        vy.push_back(IntPair(y, ny2*seg-y));
        vy.push_back(IntPair(ny2*seg, y+dy-ny2*seg));
    }
    if(nz1 ==nz2){
        vz.push_back(IntPair(z, dz));
    }else{
        vz.push_back(IntPair(z, nz2*seg-z));
        vz.push_back(IntPair(nz2*seg, z+dz-nz2*seg));
    }
    for(unsigned int i = 0; i < vx.size(); ++i){
        for(unsigned int j = 0; j<vy.size(); ++j){
            for(unsigned int k = 0; k < vz.size(); ++k){
               vblk[nx1+i][ny1+j][nz1+k].push_back(sexlet(vx[i].first, vy[j].first, vz[k].first, vx[i].second, vy[j].second, vz[k].second));
            }
        }
    }
}
int main()
{
    int dim = 10000;
    int seg = 400;
    unsigned int nb = dim/seg+1;
    create_positions(vn);
    vblk.resize(nb);
    for(unsigned int i = 0; i< vblk.size(); ++i)
        vblk[i].resize(nb);
    
    for(unsigned int i = 0; i<vblk.size(); ++i){
        for(unsigned int j = 0; j <vblk.size(); ++j){
            vblk[i][j].resize(nb);
        }
    }
    
    for( int index = 0; index < limit; ++index){
        int x = vn[6*index+1];
        int y = vn[6*index+2];
        int z = vn[6*index+3];
        int dx = vn[6*index+4];
        int dy = vn[6*index+5];
        int dz = vn[6*index+6];
        divide_cube(x,y,z,dx,dy, dz, seg);
    }
    //index is ordered in each block!
    i64 vol = 0;
    for(unsigned int nx = 0; nx < nb; ++nx){
        for(unsigned int ny = 0; ny < nb; ++ny){
            for(unsigned int nz = 0; nz < nb; ++nz){
                vol += volume(vblk[nx][ny][nz]);
            }
        }
    }
    printf("%lld\n", vol);
}
