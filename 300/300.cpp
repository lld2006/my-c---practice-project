#include <cstdio>
#include <vector>
using namespace std;
//1 for H and 0 for P
int target = 15;
int dim = 2*target+1;

int index(int row, int col, int dim)
{
    return (row)*dim + col;
}
int bond(vector<int>& vgrids, int xc, int yc, int vc)
{
    if(vc == 0)
        return 0;
    int total = (vgrids[index(xc+1, yc, dim)] == 1) 
            +(vgrids[index(xc-1, yc, dim)] == 1)
            +(vgrids[index(xc,yc+1, dim)] == 1)
            +(vgrids[index(xc, yc-1, dim)] == 1);
    return total;
}
int search_cfg(vector<int>& vgrids, const int value, int nc, int xc, int yc, int nb)
{
    int fmax = 0;
    if(nc == target) {
        return nb;
    }
    int tb = 0;
    int nt = ((value >> nc) & 1);
    if(vgrids[index(xc+1, yc, dim)] == -1){
        vgrids[index(xc+1, yc, dim)] = nt; 
        tb = bond(vgrids, xc+1, yc, nt);
        int tmax = search_cfg(vgrids, value, nc+1, xc+1, yc, nb+tb);
        if(tmax > fmax) fmax = tmax;
        vgrids[index(xc+1, yc, dim)] = -1;
    }
    if(vgrids[index(xc-1,yc, dim)] == -1){ //empty
        vgrids[index(xc-1,yc,dim)] = nt;
        tb = bond(vgrids, xc-1, yc, nt);
        int tmax = search_cfg(vgrids, value, nc+1, xc-1, yc, nb+tb);
        if(tmax > fmax) fmax = tmax;
        vgrids[index(xc-1, yc, dim)] = -1;
    }
    if(vgrids[index(xc,yc+1, dim)] == -1){ //empty
        vgrids[index(xc,yc+1,dim)] = nt;
        tb = bond(vgrids, xc, yc+1, nt);
        int tmax = search_cfg(vgrids, value, nc+1, xc, yc+1, nb+tb);
        if(tmax > fmax) fmax = tmax;
        vgrids[index(xc, yc+1, dim)] = -1;
    }
    if(vgrids[index(xc,yc-1, dim)] == -1){ //empty
        vgrids[index(xc,yc-1,dim)] = nt;
        tb = bond(vgrids, xc, yc-1, nt);
        int tmax = search_cfg(vgrids, value, nc+1, xc, yc-1, nb+tb);
        if(tmax > fmax) fmax = tmax;
        vgrids[index(xc, yc-1, dim)] = -1;
    }
    return fmax;
}
int main(int argc, const char *argv[])
{
    int nmax = 1<<target;
    int sum = 0;
    for(int i = 2; i < nmax; ++i){
        if( i % 100 == 0)
            printf("%d\n", i);
        vector<int> vgrids;
        vgrids.resize((dim)*(dim), -1);
        int total = 0;
        int a0 = (i & 1);
        int a1 = ( i>>1) & 1;
        int a2 =  (i >> 2) & 1;
        vgrids[index(target, target,dim)] = a0;
        vgrids[index(target, target-1, dim)] = a1;
        if(a0 == 1&& a1 == 1) ++total;
        if(a1 ==1 && a2 == 1) ++total;
        //first search vertical dir for 3
        vgrids[index(target, target-2, dim)] = a2;
        int f1 = search_cfg(vgrids, i, 3, target, target-2, total);
        vgrids[index(target, target-2, dim)] = -1;

        vgrids[index(target+1, target-1, dim)] = a2;
        int f2 = search_cfg(vgrids, i, 3, target+1, target-1, total);
        vgrids[index(target+1, target-1, dim)] = -1;
        sum += f1 > f2? f1:f2;
    }
    printf("%d\n", sum);
    return 0;
}
