#include "../lib/tools.h"
#include <cassert>
#include <cstdio>
int gsize = 4;
int searchGrid(const int total, const vector<int> grid, const vector<int> vflag, const int nset){
    if(nset == 16) {
        for(int row = 0; row < gsize; ++row){
            int gs = 0;
            for(int col = 0; col < gsize; ++col){
                gs += grid[index0(gsize, row, col)];
            }
            if(gs != total)
                return 0;
        }
        for(int col = 0; col < gsize; ++col){
            int gs = 0;
            for(int row = 0; row < gsize; ++row){
                gs += grid[index0(gsize, row, col)];
            }
            if(gs != total)
                return 0;
        }
        int gs = 0;
        for(int id = 0; id < gsize; ++id){
            gs += grid[index0(gsize, id, id)];
        }
        if(gs != total)
            return 0;
        gs =0;
        for(int id = 0; id <gsize; ++id){
            gs += grid[index0(gsize, id, gsize-1-id)];
        }
        if(gs != total)
            return 0;
        return 1;
    }
    int sum = 0;
    //which row and col that need to be decided
    int row = 0, col = 0;
    unsigned int ix;
    for(ix = 0; ix < vflag.size(); ++ix)
        if(vflag[ix] == 0) break;

    row = ix/gsize;
    col = ix%gsize;

    int row_sum = 0, col_sum = 0, diag_sum = 0, adiag_sum=0;
    int row_vacant = 0, col_vacant = 0, diag_vacant=0, adiag_vacant = 0; 
    row_sum = 0;
    for(int i = 0; i<gsize; ++i){
        int value = grid[index0(gsize, row, i)];
        if(value == -1)
            ++row_vacant;
        else
            row_sum += value;
    }
    for(int i = 0; i<gsize; ++i){
        int value = grid[index0(gsize, i, col)];
        if(value == -1)
            ++col_vacant;
        else
            col_sum += value;
    }
    assert(vflag[index0(gsize, row, col)] == 0);
    assert(row_sum <= total);
    assert(col_sum <= total);
    //row constrain and col constrain
    int min = 0, max = 9;
    int v1 = total - row_sum - (row_vacant-1)*9;
    max = max < total-row_sum? max: total-row_sum;
    min = min < v1 ? v1: min;
    v1 = total - col_sum -(col_vacant - 1)*9;
    min = min < v1 ? v1: min;
    max = max < total-col_sum? max: total-col_sum;
    //diagonal constrain
    if( row == col ){
        for(int i = 0; i < gsize; ++i){
            if(grid[index0(gsize, i, i)] == -1){
                ++diag_vacant;
            }else{
                diag_sum += grid[index0(gsize, i, i)];
            }
        }
        assert(diag_vacant >0);
        v1 = total -diag_sum-(diag_vacant-1) * 9;
        min = min < v1 ? v1: min;
        max = max < total-diag_sum? max: total-diag_sum;
    }
    //anti diagonal constrain
    if(row+col == gsize - 1){
        for(int i = 0; i < gsize; ++i){
            if(grid[index0(gsize, i, gsize-1-i)]==-1){
                ++adiag_vacant;
            }else{
                adiag_sum += grid[index0(gsize, i, gsize-1-i)];
            }
        }
        assert(adiag_vacant > 0);
        v1 = total - adiag_sum - (adiag_vacant - 1)*9;
        min = min < v1 ? v1:min;
        max = max < total-adiag_sum? max: total-adiag_sum;
    }
    for(int i = min;  i <= max; ++i){
        vector<int> f1(vflag), g1(grid);
        int mset = nset;
        int index = index0(gsize, row, col);
        assert(vflag[index] == 0);
        f1[index] = 1;
        g1[index] = i;
        ++mset;
        if(row_vacant == 2){
            int sx = 0, vx = -1;
            for(int icol = 0; icol < gsize; ++icol){
                int index = index0(gsize, row, icol); 
                if(g1[index]== -1){
                    assert(vx == -1);
                    vx = icol;
                }
                else
                    sx += g1[index];
            }
            assert(sx <= total);
            assert(vx >= 0);
            f1[index0(gsize, row, vx)] = 1;
            g1[index0(gsize, row, vx)] = total - sx;
            ++mset;
        }
        if(col_vacant == 2){
            int sx = 0, vx = -1; 
            for(int irow = 0; irow < gsize; ++irow){
                int index = index0(gsize, irow, col);
                if(g1[index] == -1){
                    assert(vx == -1);
                    vx = irow;
                } else
                    sx += g1[index];
            }
            assert(vx >= 0);
            assert(sx <= total);
            f1[index0(gsize, vx, col)] = 1;
            g1[index0(gsize, vx, col)] = total - sx;
            ++mset;
        }
        if(row == col && diag_vacant == 2){
            int sx = 0, vx = -1;
            for(int id = 0; id < gsize; ++id){
                int index = index0(gsize, id, id);
                if(g1[index] == -1){
                    assert(vx == -1);
                    vx = id;
                }else
                    sx += g1[index];
            }
            assert(vx >= 0);
            assert(sx <= total);
            f1[index0(gsize, vx, vx)] = 1;
            g1[index0(gsize, vx, vx)] = total - sx;
            ++mset;
        }
        if(row + col == 3 && adiag_vacant == 2){
            int sx = 0, vx = -1;
            for(int id = 0; id < gsize; ++id){
                int index = index0(gsize, id, gsize-1-id);
                if(g1[index] == -1){
                    assert(vx == -1);
                    vx = id;
                }else
                    sx += g1[index];
            }
            assert(vx >= 0);
            assert(sx <= total);
            f1[index0(gsize, vx, gsize-1-vx)] = 1;
            g1[index0(gsize, vx, gsize-1-vx)] = total - sx;
            ++mset;
        }
        sum += searchGrid(total, g1, f1, mset) ;
    }
    return sum;//
}
int main(){
    int sum = 0;
    vector<int> grid, vflag;
    for(int total = 0; total <= 18; ++total){
        grid.clear();
        grid.resize(16, -1);
        vflag.clear();
        vflag.resize(16, 0);
        int val = searchGrid(total, grid, vflag, 0);
        if(total < 18)
            sum += 2* val;
        else
            sum += val;
        printf("%d %d\n", total, sum);
    }
}
