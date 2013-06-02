#include <cstdio>
int total = 0;
// create a 792*792 one dimensional array, 
// for rows, (3 dimensional row, col, value)
// for columns, (also 3 dimensional row, col, square i)
class cell
{
    public:
        cell():  d_left(0)
                ,d_right(0)
                ,d_up(0)
                ,d_down(0)
                ,d_head(0){}
        void set_neighbors(cell* l, cell* r, cell* u, cell* d, cell* h){
            d_left = l; d_right = r; d_up = u; d_down = d; d_head = h;
        }
        void set_left(cell* l){d_left = l;}
        void set_right(cell* r){d_right = r;}
        void set_up(cell * u){d_up = u;}
        void set_down(cell *d){d_down = d;}
        void set_head(cell *h){d_head = h;}
        void set_rc(int row, int col) {d_row = row; d_col = col;}
        void inc_size(){++d_size;}
        void dec_size(){--d_size;}
        cell* left()  const {return d_left;}
        cell* right() const {return d_right;}
        cell* up()    const {return d_up;}
        cell* down()  const {return d_down;}
        cell* head()  const {return d_head; }
        int row() const {return d_row;} 
        int col() const {return d_col;}
    private: 
        cell* d_left;
        cell* d_right;
        cell* d_up;
        cell* d_down;
        cell* d_head;
        int d_row;
        int d_col;
        int d_size;
};
class sudoku_solver
{
    public:
        sudoku_solver():d_root(0), d_head(0), d_cells(0) { }
        int debug_curr() const
        {
            return 1;
        }
        void create_solver(int row, int col)
        {
            assert(row == col && row == 9)
            d_root = new cell;
            d_heads = new cell[729];
            d_cells = new cell[729*729];
            int nsize = 729;
            for(int i = 1; i <nsize-1; ++i ){
                d_heads[i].set_neighbors(d_heads+i-1, d_heads+i+1, d_heads+i, d_heads+i, 0);
                d_heads[i].set_rc(-1, i);
            }
            d_heads[0].set_neighbors(d_root, d_heads+1, d_head, d_head, 0);
            d_heads[0].set_rc(-1, 0);
            d_heads[nsize-1].set_neighbors(d_heads+nsize-2, d_root, d_heads+nsize-1, d_heads+nsize-1, 0)
            d_heads[0].set_rc(-1, nsize-1);

            d_root->set_neighbors(d_heads+nsize-1, d_heads, 0,0,0);
            d_root->set_rc(-1, -1);
        }
    private:
        cell* d_root;
        cell* d_cells;
        
};
int main()
{
    FILE *fp;
    fp = fopen("sudoku.txt", "r");
    char a1[128], a2[128];
    int numSolved = 0;
    int sum = 0;
    for(int ig = 0; ig<50; ++ig){
        vector<int> grid; 
        //read grid # i
        sudoku_solver solver;
        solver.create_solver(9, 9);
        fscanf(fp, "%s %s", a1, a2);
        for(int i =0; i<9; ++i){
            fscanf(fp, "%s", a1);
            for(int j = 0; j<9; ++j){
                int tp = a1[j]-'0';
                grid[i*9+j] = tp;
                if(tp){
                    solver.insert(i+1, j+1, tp);
                }
            }
        }
    }
}
