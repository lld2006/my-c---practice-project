#include <cstdio>
#include <vector>
#include <cstdlib>
#include <set>
#include <cassert>
#include <algorithm>
using namespace std;
/*  
lesson, when we have determined a value in a grid, we should go through the 
standard procedure determine instead of clear the candidate set; 
lesson be careful about continue, especially in if!!! 
using names with very clear meaning, avoid writing say a write b !
lesson in a loop, be careful about the initialization, where you should put it.
and if you need to clear the vector
*/
class sudoku
{
    public:
        sudoku();
        void init();
        void print();
        void determine(int i, int value );
        void simpleRowDetermine(int row );
        void simpleColDetermine(int col );
        void simpleBlockDetermine(int block);
        void eraseValueFromCRow(int row, int value ); //candidate update
        void eraseValueFromCCol(int row, int value );
        void eraseValueFromCBlock(int block, int value );
        void eraseValueInRowi(int row, int value ); //erase candidate in all grids in row i
        void eraseValueInColi(int col, int value );
        void eraseValueInBlocki(int block, int value );
        void searchGrid();//check if any grid may have an determine simple check
        bool searchPairs(); //if two digits as candidates in the same row col block
        bool searchPairsInRow(int row);
        bool searchPairsInCol(int col);
        bool searchPairsInBlock(int block);
        bool searchSingles(); // if a candidate only exist in one grid, then a determine;
        bool searchSinglesInRow(int row);
        bool searchSinglesInCol(int col);
        bool searchSinglesInBlock(int block);
        bool searchLockedCandidate();
        bool searchLockedCandidateInRow();
        bool searchLockedCandidateInCol();
        bool searchLockedCandidateInBlock();
        bool searchAllTriplet();
        bool searchTriplet(set<int>& candidate, vector<int>& cgrid);
        bool searchXWing();
        vector<int> getPosInRow(int value, int row);
        vector<int> getPosInCol(int value, int col);
        vector<int> getGridInRow(int row); //only undetermined grid index
        vector<int> getGridInCol(int col);
        vector<int> getGridInBlock(int block);
        vector<int>& getGrid(){return grid;}
    private:
        vector<int> grid; //contain all current valid results
        vector<set<int> > rowCand;
        vector<set<int> > colCand;
        vector<set<int> > blockCand;
        vector<set<int> > gridCand; 
};
vector<int> sudoku::getPosInRow(int value, int row){
    vector<int> colVec;
    if(rowCand[row].find(value) == rowCand[row].end())
        return colVec;
    for(int col = 0; col <9; ++col){
        int idx = row*9+col;
        if(grid[idx] != 0)continue;
        if(gridCand[idx].find(value) != gridCand[idx].end())
            colVec.push_back(col);
    }
    return colVec;
}

vector<int> sudoku::getPosInCol(int value, int col){
    vector<int> rowVec;
    if(colCand[col].find(value) == colCand[col].end())
        return rowVec;
    for(int row = 0; row < 9; ++row){
        int idx = row*9+col;
        if(grid[idx] != 0) continue;
        if(gridCand[idx].find(value) != gridCand[idx].end())
            rowVec.push_back(row);
    }
    return rowVec;
}

vector<int> sudoku::getGridInRow(int row){
    vector<int> candidate;
    for(int col = 0; col < 9; ++col){
        int idx = row*9+col;
        if(grid[idx] == 0)
            candidate.push_back(idx);
    }
    return candidate;
}
vector<int> sudoku::getGridInCol(int col){
    vector<int> candidate;
    for(int row =0; row<9 ; ++row){
        int idx = row*9+col;
        if(grid[idx]==0) 
            candidate.push_back(idx);
    }
    return candidate;
}
vector<int> sudoku::getGridInBlock(int block){
    unsigned int colStart = (block % 3)*3;
    unsigned int rowStart = (block / 3)*3; // row row+1 row+2
    vector<int> candidate;
    for(unsigned int row = rowStart; row < rowStart+3; ++row)
        for(unsigned int col = colStart; col <colStart+3; ++col){
            int idx = row*9+col;
            if(grid[idx]==0) 
                candidate.push_back(idx);
        }
    return candidate;
}
void sudoku::init()
{
    vector<int> nall;
    nall.resize(9, 0);
    for(int i = 0; i < 9; ++i){
        nall[i] = i +1;
    }
    grid.resize(81, 0);
    rowCand.resize(9, set<int>(nall.begin(), nall.end()));
    colCand.resize(9, set<int>(nall.begin(), nall.end()));
    blockCand.resize(9, set<int>(nall.begin(), nall.end()));
    gridCand.resize(81, set<int>(nall.begin(), nall.end()));
}
sudoku::sudoku()
{
    grid.clear();
    grid.resize(81, 0);
}
class sutility
{
    public:
    inline static int row(int num){
        return num / 9;
    }
    inline static int col(int num){
        return num % 9;
    }
    inline static int block(int num){
        return row(num)/3 *3 + col(num)/3;
    }
};
void sudoku::print(){
    printf("\n|-------|-------|-------|\n");
    for( int i = 0; i<9; ++i){
        printf("|");
        for (int j = 0; j < 9; ++j){
            if((j+1)%3==0) 
                printf("%d|", grid[i*9+j]);
            else 
                printf("%d  ", grid[i*9+j]);
        }
        if((i+1)%3==0) printf("\n|-------|-------|-------|");
        printf("\n");
    }
}
void sudoku::simpleRowDetermine(int row )
{
    assert(rowCand[row].size() == 1);
    //how many grid are still unfilled
    int left = count(grid.begin()+row*9, grid.begin()+row*9+9, 0);
    if(left == 0){
        rowCand[row].clear();
        return;
    }
    assert(left == 1);
    int det = -1;
    int value = *rowCand[row].begin();
    for(int i =0 ; i < 9; ++i){
        if(grid[row*9+i] == 0)
            det = row * 9 + i;
    }
    assert(det >=0 && det < 81);
    determine(det, value); 
}
void sudoku::simpleColDetermine(int col){
    assert(colCand[col].size() == 1);
    int cnum = 0;
    int det = -1;
    int value = *colCand[col].begin();
    for(int j = 0; j < 9; ++j){
        if(grid[j*9+col] == 0){
            det = j*9+col;
            ++cnum;
        }
    }
    if(cnum == 0){
        colCand[col].clear();
        return;
    }
    assert(cnum == 1);
    assert(det >=0 && det < 81);
    determine(det, value);
}
void sudoku::simpleBlockDetermine(int block){
    assert(blockCand[block].size() == 1);
    int cnum = 0;
    int det = -1;
    int value = *blockCand[block].begin();
    unsigned int colStart = (block % 3)*3;
    unsigned int rowStart = (block / 3)*3; // row row+1 row+2
    for(unsigned int i = rowStart ; i < rowStart + 3; ++i)
        for(unsigned int j = colStart; j <colStart + 3; ++j){
            if(grid[i*9+j]==0){
                det = i*9+j;
                ++cnum;
            }
        }
    if(cnum == 0){
        blockCand[block].clear();
        return;
    }
    assert(cnum == 1);
    assert(det >= 0 && det < 81);
    determine(det, value);
}
void sudoku::eraseValueFromCRow(int row, int value ){
    if(rowCand[row].empty()) return;
    rowCand[row].erase(value);
    if(rowCand[row].size() == 1) simpleRowDetermine(row);
}
void sudoku::eraseValueFromCCol(int col, int value ){
    if(colCand[col].empty()) return;
    colCand[col].erase(value);
    if(colCand.size() == 1) simpleColDetermine(col);
}
void sudoku::eraseValueFromCBlock(int block, int value ){
    if(blockCand[block].empty()) return;
    blockCand[block].erase(value);
    if(blockCand[block].size() == 1) simpleBlockDetermine(block);
}
void sudoku::eraseValueInRowi(int row, int value){
    for(unsigned int i = 0; i <9; ++i){
        if(!gridCand[9*row+i].empty()) {
            gridCand[9*row+i].erase(value);
            //if(count)
            //    printf("rowi %d value %d\n", 9*row+i, value);
        }
    }
}
void sudoku::eraseValueInColi(int col, int value ){
    for(unsigned int i = 0; i < 9; ++i){
        if(!gridCand[9*i+col].empty()){
            gridCand[9*i+col].erase(value);
            //if(count)
            //    printf("coli %d value %d\n", 9*i+col, value);
        }
    }
}
//lesson this is not well thought before use, just copy!!
void sudoku::eraseValueInBlocki(int block, int value ){
    unsigned int colStart = (block % 3)*3;
    unsigned int rowStart = (block / 3)*3; // row row+1 row+2
    for(unsigned int i = rowStart ; i < rowStart + 3; ++i)
        for(unsigned int j = colStart; j <colStart + 3; ++j){
            if(!gridCand[i*9+j].empty()){
                gridCand[i*9+j].erase(value);
                //if(count)
                //    printf("blocki %d value %d\n", i*9+j, value);
            }
        }
}
//based on a determine ith grid with value
void sudoku::determine(int i, int value ){
    int irow = sutility::row(i);
    int icol = sutility::col(i);
    int iblock = sutility::block(i);
    //first clean it self
    gridCand[i].clear();
    grid[i] = value;
    eraseValueInBlocki(iblock, value);// in all related block member
    eraseValueInColi(icol, value ); // in all related col
    eraseValueInRowi(irow, value ); //in all related row
    eraseValueFromCRow(irow, value );  //update row candidates
    eraseValueFromCCol(icol, value );  //update col candidates
    eraseValueFromCBlock(iblock,value ); //update block candidates
}

void sudoku::searchGrid()
{
    for(unsigned int i = 0; i < gridCand.size(); ++i){
        if(gridCand[i].size() == 1){
            //printf("grid %d %d %d %d determined\n", 
            //    sutility::row(i), sutility::col(i), sutility::block(i), *gridCand[i].begin());
            determine(i, *gridCand[i].begin());
            gridCand[i].clear();
        }
    }
}
bool sudoku::searchSingles(){
    bool changed = false;
    for(int i = 0; i < 9; ++i){
        changed |= searchSinglesInRow(i);
        changed |= searchSinglesInCol(i);
        changed |= searchSinglesInBlock(i);
    }
    return changed;
}
//if a number only appears in just one grid in a row(col, block)
//then the value is determined
//here I made a mistake on how to erase value from set again. invalid iterator!
bool sudoku::searchSinglesInRow(int row){
    bool changed = false;
    if(rowCand[row].empty()) 
        return false;
    for(set<int>::iterator iter = rowCand[row].begin(); 
            iter != rowCand[row].end();++iter){
        int fcol = -1, count = 0;
        int value = *iter;
        for(unsigned int col = 0; col < 9; ++col){
            if( gridCand[9*row+col].find(value) != gridCand[9*row+col].end()){
                ++count;
                fcol = col;
            }
            if(count > 1) break;
        }
        if(count == 1){
            determine(9*row+fcol, value);
            changed = true;
            break; //stop, iterator invalid
        }
    }
    return changed;
}
bool sudoku::searchSinglesInCol(int col){
    bool changed = false;
    if(colCand[col].empty())
        return false;
    for(set<int>::iterator iter = colCand[col].begin();
            iter != colCand[col].end(); ++iter){
        int value = *iter;
        int frow = -1, count = 0;
        for(unsigned int row = 0; row < 9; ++ row){
            if(gridCand[9*row+col].find(value) != gridCand[9*row+col].end()){
                ++count;
                frow = row;
            }
            if(count > 1)break;
        }
        if(count == 1){
            determine(9*frow+col, value);
            changed = true;
            break;
        }
    }
    return changed; 
}

bool sudoku::searchSinglesInBlock(int block){
    bool changed = false;
    if(blockCand[block].empty())
        return false;
    for(set<int>::iterator iter = blockCand[block].begin();
            iter != blockCand[block].end();++iter){
        int value = *iter;
        int fgrid = -1, count = 0;
        unsigned int colStart = (block % 3)*3;
        unsigned int rowStart = (block / 3)*3;
        for( unsigned int row = rowStart; row < rowStart+3; ++row)
            for ( unsigned int col = colStart; col < colStart+3; ++col){
                int grid = row * 9 + col;
                if(gridCand[grid].find(value) != gridCand[grid].end()){
                    ++count;
                    fgrid = grid;
                }
                if(count > 1) break;
            }
        if(count == 1) {
            determine(fgrid, value);
            changed = true;
            break;
        }
    }
    return changed;
}
bool sudoku::searchPairs(){
    bool changed = false;
    for(int i = 0; i <9; ++i){
        changed |= searchPairsInRow(i);
        changed |= searchPairsInCol(i);
        changed |= searchPairsInBlock(i);
    }
    return changed;
}
bool sudoku::searchPairsInBlock(int block){
    bool changed = false;
    vector<int> candidate;
    unsigned int colStart = (block %3)*3;
    unsigned int rowStart = (block /3)*3;
    for(unsigned int row = rowStart; row < rowStart+3; ++row)
        for(unsigned int col = colStart; col < colStart+3; ++col){
            if(gridCand[9*row+col].size()==2)
                candidate.push_back(9*row+col);
        }
    if(candidate.size() <= 1) return 0;
    for(unsigned int i = 0; i < candidate.size(); ++i)
        for(unsigned int j = i+1; j < candidate.size(); ++j){
            if(gridCand[candidate[i]] == gridCand[candidate[j]]){
                set<int>::iterator iter = gridCand[candidate[i]].begin();
                int vfirst = *iter++;
                int vsecond = *iter;
                for(unsigned int row = rowStart; row < rowStart+3; ++row)
                    for(unsigned int col = colStart; col < colStart+3; ++col){
                        int gridi = row*9+col;
                        if(gridi != candidate[i] && gridi != candidate[j]){
                            int count1 = gridCand[gridi].erase(vfirst); 
                            changed |= count1;
                            //if(count1)
                            //    printf("blockp %d value %d\n", gridi, vfirst);
                            int count2 = gridCand[gridi].erase(vsecond); 
                            changed |= count2;
                            //if(count2)
                            //    printf("blockp %d value %d\n", gridi, vsecond);
                        }
                    }
            }
        }
    return changed;
}
bool sudoku::searchPairsInRow(int row){
    bool changed = false;
    vector<int> candidate;
    for(int col = 0; col < 9; ++col){
        if(gridCand[row*9+col].size()==2) 
            candidate.push_back(col);
    }
    if(candidate.size() <= 1)return 0;
    for(unsigned int i = 0; i < candidate.size(); ++i)
        for(unsigned int j = i+1; j < candidate.size(); ++j){
            if(gridCand[row*9+candidate[i]]==gridCand[row*9+candidate[j]] ){
                //pair found
                set<int>::iterator iter = gridCand[row*9+candidate[i]].begin();
                //values that need to be excluded from other grids in this row
                int vfirst = *iter++;
                int vsecond =*iter;
                for(int col = 0; col < 9; ++col){
                    if(col != candidate[i] && col != candidate[j]){
                         int count1 = gridCand[row*9+col].erase(vfirst);
                        changed |= count1;
                        //if(count1)
                        //    printf("rp %d value %d\n", row*9+col, vfirst);
                        int count2 = gridCand[row*9+col].erase(vsecond);
                        changed |= count2;
                        //if(count2)
                        //    printf("rp %d value %d\n", row*9+col, vsecond);
                    }
                }
            }
        }
    return changed;
}
bool sudoku::searchPairsInCol(int col){
    bool changed = false;
    vector<int> candidate;
    for(int row = 0; row < 9; ++row){
        if(gridCand[row*9+col].size()==2)
            candidate.push_back(row);
    }
    if(candidate.size() <= 1)return 0;
    for(unsigned int i = 0; i < candidate.size(); ++i)
        for(unsigned int j = i + 1; j < candidate.size(); ++j){
            if(gridCand[candidate[i]*9+col]==gridCand[candidate[j]*9+col]){
                set<int>::iterator iter = gridCand[candidate[i]*9+col].begin();
                int vfirst  = *iter++;
                int vsecond = *iter;
                for(int row = 0; row < 9; ++row){
                    if(row != candidate[i] && row != candidate[j]){
                         int count1 = gridCand[row*9+col].erase(vfirst); 
                        changed |= count1;
                        //if(count1)
                        //    printf("pc %d value %d\n", row*9+col, vfirst);
                        int count2 = gridCand[row*9+col].erase(vsecond);
                        changed |= count2;
                        //if(count2)
                        //    printf("pc %d value %d\n", row*9+col, vsecond);
                    }
                }
            }
        }
    return changed;
}
//search a block and find number in just one row(col)
bool sudoku::searchLockedCandidateInBlock(){
    bool changed = false;
    for(int block = 0; block < 9; ++block){
        unsigned int colStart = (block %3)*3;
        unsigned int rowStart = (block /3)*3;
        for(set<int>::iterator iter = blockCand[block].begin();
                iter != blockCand[block].end(); ++iter){
            int value = *iter;
            int frvalue = -1, fcvalue= -1;
            int frow = -1, fcol=-1;
            for(unsigned int row = rowStart; row < rowStart +3 ;++row)
                for(unsigned int col = colStart; col < colStart +3; ++col){
                    int grid = row*9+col;
                    if(gridCand[grid].empty())continue;
                    if(gridCand[grid].find(value) != gridCand[grid].end()){
                        if(frow == -1){
                            frow = row;
                            frvalue = value;
                        }
                        else if(frow == row) {
                            assert(frow >= 0);
                        }
                        else
                            frow = 100;
                        if(fcol == -1){
                            fcol = col;
                            fcvalue = value;
                        }
                        else if(fcol == col){
                            assert(fcol >= 0);
                        }
                        else
                            fcol = 100;
                    }
                }//end search grid
            if(fcol >= 0 && fcol < 9){
                for(int row = 0; row < 9; ++row){
                    int grid = row * 9 + fcol;
                    int xblock = sutility::block(grid);
                    if(xblock == block) continue;
                    int count1 = gridCand[grid].erase(fcvalue);
                    changed |= count1;
                    //if(count1)
                    //    printf("lockc %d value %d\n", grid, fcvalue);
                }
            }
            if(frow >= 0 && frow < 9){
                for(int col = 0; col < 9; ++col){
                    int grid = frow*9+col;
                    int xblock = sutility::block(grid);
                    if(xblock == block)continue;
                    int count2 = gridCand[grid].erase(frvalue);
                    changed |= count2;
                    //if(count2)
                    //    printf("lockr %d value %d\n", grid, frvalue);
                }
            }
        }//end block candidate
    }//end block
    return changed;
}

bool sudoku::searchLockedCandidate(){
    bool changed = false;
    changed |= searchLockedCandidateInBlock();
    changed |= searchLockedCandidateInRow();
    changed |= searchLockedCandidateInCol();
    return changed;
}

bool sudoku::searchLockedCandidateInRow(){
    bool changed = false;
    set<int>::iterator iter;
    for(int row = 0; row < 9; ++row){
        for(iter = rowCand[row].begin(); iter != rowCand[row].end(); ++iter){
            int value = *iter;
            int fblock = -1;
            for(int col = 0; col < 9; ++col){
                int grid = row*9+col;
                if(gridCand[grid].find(value) != gridCand[row*9+col].end()){
                    int xblock = sutility::block(grid);
                    if(fblock == -1){
                        fblock = xblock;
                    }else if(fblock == xblock){
                        ;//doing nothing
                    }else{
                        fblock = 100;
                    }
                }
            }//all columns checked now
            if(fblock >= 0 && fblock <9){
                unsigned int colStart = (fblock % 3)*3;
                unsigned int rowStart = (fblock / 3)*3; // row row+1 row+2
                for(unsigned int frow = rowStart; frow < rowStart+3; ++frow){
                    if(row == frow) continue;
                    for(unsigned int col = colStart; col <colStart+3; ++col){
                        int grid= frow*9+col;
                        changed |= gridCand[grid].erase(value);
                    }
                }
            }
        }
    }//for a row
    return changed;
}
bool sudoku::searchLockedCandidateInCol(){
    bool changed = false;
    set<int>::iterator iter;
    for(int col = 0; col < 9; ++col){
        for(iter = colCand[col].begin(); iter !=colCand[col].end(); ++iter){
            int fblock = -1;
            int value = *iter;
            for(int row = 0; row < 9; ++row){
                int grid = row*9+col;
                if(gridCand[grid].find(value)!=gridCand[grid].end()){
                    int xblock = sutility::block(grid);
                    if(fblock == -1){
                        fblock = xblock;
                    }else if(fblock == xblock){
                        ;//doing nothing
                    }else{
                        fblock = 100;
                    }
                }
            }// all rows checked;
            if(fblock >= 0 && fblock < 9){
                unsigned int colStart = (fblock % 3)*3;
                unsigned int rowStart = (fblock / 3)*3; // row row+1 row+2
                for(unsigned int fcol = colStart; fcol < colStart+3; ++fcol){
                    if(fcol == col) continue;
                    for(unsigned int row = rowStart; row < rowStart +3; ++row){
                        int grid = row *9+fcol;
                        changed |= gridCand[grid].erase(value);
                    }
                }
            }
        }// all candidate checked
    }
    return changed;
}

bool sudoku::searchTriplet(set<int>& cand, vector<int>& cgrid){
    if(cand.size() <= 3) return false;
    bool changed = false;
    int size = cgrid.size();
    vector<int> intsec;
    for(int i = 0; i < size; ++i)
        for(int j = i+1; j <size; ++j){
            vector<int> tmpvec;
            set_union(gridCand[cgrid[i]].begin(), gridCand[cgrid[i]].end(),
                             gridCand[cgrid[j]].begin(), gridCand[cgrid[j]].end(),
                             back_inserter(tmpvec));
            for(int k=j+1; k < size; ++k){
                intsec.clear();
                set_union(tmpvec.begin(), tmpvec.end(),
                                 gridCand[cgrid[k]].begin(), gridCand[cgrid[k]].end(),
                                 back_inserter(intsec));
                if(intsec.size()==3){ //found triplet
                    for(int m = 0; m < size; ++m){
                        if(m ==i || m ==j ||m ==k) continue;
                        int idx = cgrid[m];
                        changed |= gridCand[idx].erase(intsec[0]);
                        changed |= gridCand[idx].erase(intsec[1]);
                        changed |= gridCand[idx].erase(intsec[2]);
                    }
                }
            }
        }
    return changed;
}

bool sudoku::searchAllTriplet(){
    bool changed = false;
    for(int i = 0; i < 9; ++i){
        vector<int> cgrid = getGridInRow(i);
        changed |= searchTriplet(rowCand[i], cgrid);
        cgrid = getGridInCol(i);
        changed |= searchTriplet(colCand[i], cgrid);
        cgrid = getGridInBlock(i);
        changed |= searchTriplet(blockCand[i], cgrid);
    }
    return changed;
}

bool sudoku::searchXWing(){
    bool changed = false;
    vector<int> colvec, colvec2;
    vector<int> rowvec, rowvec2;
    for(int value = 1; value <= 9; ++value){
        for(int row = 0; row < 9; ++row){
            colvec = getPosInRow(value, row);
            if(colvec.size() !=2) continue;
            for(int row2 = row+1; row2 <9; ++row2){
                colvec2 = getPosInRow(value, row2);
                if(colvec == colvec2){
                    for( int erow = 0; erow < 9; ++erow){
                        if(erow !=row && erow != row2){
                            changed |= gridCand[erow*9+colvec[0]].erase(value);
                            changed |= gridCand[erow*9+colvec[1]].erase(value);
                        }
                    }
                }
            }
        }
        for(int col = 0; col < 9; ++col){
            rowvec = getPosInCol(value, col);
            if(rowvec.size() != 2) continue;
            for(int col2 = col+1; col2 < 9; ++col2){
                rowvec2 = getPosInCol(value, col2);
                if(rowvec == rowvec2){
                    for(int ecol = 0; ecol < 9; ++ecol){
                        if(ecol != col && ecol != col2){
                            changed |= gridCand[rowvec[0]*9+ecol].erase(value);
                            changed |= gridCand[rowvec[1]*9+ecol].erase(value);
                        }
                    }
                }
            }
        }
    }
    return changed;
}

int main(){
    FILE *fp;
    fp = fopen("sudoku.txt", "r");
    char a1[128], a2[128];
    int numSolved = 0;
    int sum = 0;
    for(int ig = 0; ig<50; ++ig){
        sudoku sgrid;
        sgrid.init();
        vector<int>& grid = sgrid.getGrid();
        //read grid # i
        fscanf(fp, "%s %s", a1, a2);
        for(int i =0; i<9; ++i){
            fscanf(fp, "%s", a1);
            for(int j = 0; j<9; ++j){
                int tp = a1[j]-'0';
                grid[i*9+j] = tp;
            }
        }
        //sgrid.print();
        // from data given, initialize sgrid candidate
        for(unsigned int i = 0; i< grid.size(); ++i){
            if(grid[i] != 0)
                sgrid.determine(i, grid[i]);
        }
        int count0, count1;
        bool flag = false;
        do{
            flag = false;
            count0 = count(sgrid.getGrid().begin(), sgrid.getGrid().end(), 0);
            sgrid.searchGrid();
            sgrid.searchPairs();
            flag |= sgrid.searchSingles();//hidden single
            flag |= sgrid.searchLockedCandidate();
            flag |= sgrid.searchAllTriplet();
            flag |= sgrid.searchXWing();
            count1 = count(sgrid.getGrid().begin(), sgrid.getGrid().end(), 0);
            //sgrid.print();
        }while(flag ||(count0 > count1 &&  count1!= 0)); 
        //result check;
        //printf("grid %d has %d 0\n", ig, count1);
        if(count1 != 0) 
            sgrid.print();
        if(count1 == 0) ++numSolved;
        int temp = 100*grid[0]+10*grid[1]+grid[2];
        sum += temp;
        //extract the number we want;
    }
    printf("solved %d sum is %d\n", numSolved, sum);
}
