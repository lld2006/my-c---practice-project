#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
#include <limits>
using namespace std;

//assignment problem
//unsigned int dim = 5;
unsigned int dim = 15;
enum {MARKED = - 1000, EXCLUDED = -500, UNSETTLED=0};
vector<int> vmat;
int index0(int dim, int i, int j) { return i*dim+j;}
void checkRow(vector<int>& vmat){
    for(unsigned int row =0; row < dim; ++row){
        int min = vmat[index0(dim, row, 0)];
        for(unsigned int col = 1; col < dim; ++col){
            if(vmat[index0(dim, row, col )] < min)
                min = vmat[index0(dim, row, col )];
        }
        for(unsigned int col = 0; col < dim; ++col)
            vmat[index0(dim, row, col)] -= min;
    }
}

void checkCol(vector<int>& vmat){
    for(unsigned int col = 0; col < dim; ++col){
        int min = vmat[index0(dim, 0, col)];
        if(min == 0) continue;
        for(unsigned int row = 1; row < dim; ++row){
            if(vmat[index0(dim, row, col)] < min)
                min = vmat[index0(dim, row, col)];
            if(min == 0) continue;
        }
        for(unsigned int row = 0; row < dim; ++row)
            vmat[index0(dim, row, col)] -= min;
    }
}

int markRow(vector<int>& vmat){
    int row_mark = 0;
    for(unsigned int row = 0; row < dim; ++row){
        int count = 0;
        unsigned int mcol = 0;
        for(unsigned int col = 0; col < dim; ++col){
            if(vmat[index0(dim, row, col)] == UNSETTLED){
                ++count;
                mcol = col;      
            }
        }
        if(count == 1){
            assert(mcol >=0 && mcol < dim);
            vmat[index0(dim, row, mcol)] = MARKED;
            for(unsigned int prow = 0; prow < dim; ++prow){
                if(prow == row) continue;
                if(vmat[index0(dim, prow, mcol)]==UNSETTLED)
                    vmat[index0(dim, prow, mcol)] = EXCLUDED;
            }
            ++row_mark;
        }
        //otherwise we can not do anything
    }
    return row_mark;
}
int markCol(vector<int>& vmat){
    int col_mark = 0;
    for(unsigned int col = 0; col < dim; ++col){
        int count = 0; 
        unsigned int mrow = 0;
        for(unsigned int row = 0; row < dim; ++row){
            if(vmat[index0(dim, row, col)] == UNSETTLED){
                  ++count;
                  mrow = row;
            }
        }
        if(count == 1){
            assert(mrow >= 0 && mrow < dim);
            vmat[index0(dim, mrow, col)] = MARKED;
            for(unsigned int pcol = 0; pcol < dim; ++pcol){
                if(pcol == col) continue;
                if(vmat[index0(dim, mrow, pcol)] == UNSETTLED)
                    vmat[index0(dim, mrow, pcol)] = EXCLUDED;
            }
            ++col_mark;
        }
    }
    return col_mark;
}
void initTickRow(vector<int>& vmat, set<int>& rset){
    for(unsigned int row = 0; row < dim; ++row){
        bool need_insertion = true;
        for(unsigned int col =0; col < dim; ++col)
            if(vmat[index0(dim, row, col)]==MARKED){
                need_insertion = false;
                break;
            }

        if(need_insertion) rset.insert(row);
    }
}
//rowset is input, ticked rows to find cols to be ticked to output set colset
void tickCol(vector<int>& vmat, set<int>& rowset, set<int>& colset){
    for(set<int>::iterator iter = rowset.begin(); iter != rowset.end(); ++iter){
        int row = *iter;
        for(unsigned int col = 0; col < dim; ++col){
            int index = index0(dim, row, col);
            if(vmat[index] == UNSETTLED || vmat[index] == EXCLUDED)
                colset.insert(col);
        }
    }
}
//colset is input, rowset is output, need to be careful, ticking method is different 
void tickRow(vector<int>& vmat, set<int>& colset, set<int>& rowset){
    for(set<int>::iterator iter = colset.begin(); iter != colset.end(); ++iter){
        int col = *iter;
        for(unsigned int row = 0; row < dim; ++row){
            int index = index0(dim, row, col);
            if(vmat[index] == MARKED)
                rowset.insert(row);
        }
    }
}
int main(){
    set<int> xtickset, ytickset;
    //matrix 
    vmat.resize(dim*dim, 0);
    int tp = 0, pos = 0;
    FILE* fp = fopen("mat.txt", "r");
    while(fscanf(fp, "%d", &tp) == 1)
        vmat[pos++] = tp;
    vector<int> optmat;
    optmat.resize(dim*dim, 0);
    for(unsigned int i = 0; i < dim * dim; ++i){
        optmat[i] = - vmat[i];
    }
    int round = 0;
    do{
        ++round;
        printf("%d\n", round);
        //initial adjustment to make 
        checkRow(optmat);
        checkCol(optmat);
        //enum is reasonable since all values are greater than(equal to) 0
        unsigned int tot_row_mark = 0; 
        unsigned int tot_col_mark = 0; 
        int row_mark, col_mark;
        vector<int> vrow, vcol;
        // use vrow and vcol as flag vectors
        vrow.resize(dim, 0);
        vcol.resize(dim, 0);
        do{
            row_mark = markRow(optmat);
            col_mark = markCol(optmat);
            tot_row_mark += row_mark;
            tot_col_mark += col_mark;
            //all set;
            if(tot_row_mark+tot_col_mark == dim) 
                break; //exit marking
        }while(row_mark + col_mark > 0);
        //need to check again what happened, 
        if(tot_row_mark+tot_row_mark == dim)
            break; //successful to exit
        // need to tick row and col;
        set<int> rowset;
        initTickRow(optmat, rowset);
        if(rowset.empty())
            break;
        vrow.clear();
        vcol.clear();
        vrow.resize(10, 0);
        vcol.resize(10, 0);
        bool updated;
        do{
            updated = false;
            for(set<int>::iterator iter=rowset.begin(); iter != rowset.end(); ++iter)
                vrow[*iter] = 1;
            set<int> colset;
            //rowset as input output is the cols that need to be ticked
            tickCol(optmat, rowset, colset);
            if(colset.empty())
                break;
            for(set<int>::iterator iter=colset.begin(); iter != colset.end(); ++iter)
                vcol[*iter] = 1;
            rowset.clear();
            tickRow(optmat, colset, rowset);
            if(!rowset.empty())
                updated = true;
        }while(updated);//break when noupdate
        //find minimum based on the ticking
        int min = numeric_limits<int>::max();
        for(unsigned int row = 0; row < dim; ++row){
            if(!vrow[row]) continue; //only check ticked row and unticked col
            for(unsigned int col = 0; col < dim; ++col){
                if(vcol[col]) continue;
                int index = index0(dim, row, col);
                if(optmat[index] < min)
                    min = optmat[index];
            }
        }
        // adjust the optmat to make optimization equvialent
        // newly introduced markers should be erased
        for(unsigned int row = 0; row < dim; ++row)
            for(unsigned int col = 0; col < dim; ++col){
                int cross = !vrow[row] + vcol[col] - 1;
                int index = index0(dim, row, col); 
                if(optmat[index] == MARKED || optmat[index] == EXCLUDED )
                    optmat[index] = UNSETTLED;
                optmat[index0(dim, row, col)] += cross * min;
            }
    }while(1);
    int max = 0;
    unsigned int ct = 0;
    for(unsigned int i = 0; i < dim*dim; ++i){
        if(optmat[i] == MARKED){
            max += vmat[i];
            ++ct;
        }
    }
    assert(ct == dim);
    printf("%d\n", max);
}
