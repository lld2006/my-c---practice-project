#include <cassert>

class triomino //object
{
  public:
  triomino():  d_left(0)
              ,d_right(0)
              ,d_up(0)
              ,d_right(0)
              ,d_head_column(0)
  {}
  void set_neighbors(triomino* l, triomino* r, triomino* u, triomino* d, triomino* h){
      set_left(l);
      set_right(r);
      set_up(u);
      set_down(d);
      set_head(h);
  }
  void set_left(triomino* l) {d_left = l;}
  void set_right(triomino* r){d_right = r;}
  void set_up(triomino* u)   {d_up = u;}
  void set_down(triomino* d) {d_down = d;}
  void set_head(triomino* h) {d_head_column = h;}
  void inc_size()            {++d_size;}
  void dec_size()            {--d_size;}
  triomino* left(){return d_left;}
  triomino* right(){return d_right;}
  triomino* up() {return d_up;}
  triomino* down() {return d_down;}
  triomino* c() {return d_column_head;}
  private:
    triomino* d_left;
    triomino* d_right;
    triomino* d_up;
    triomino* d_down;
    triomino* d_column_head;
    int d_size;
};
class exact_cover_solver
{
  public:
  triomino* create_root()
  {
      d_root = new triomino;
  }
  void create_columns(int row, int col)//create all column objects; empty and linked
  {
    triomino* ptrio = new triomino[row*col];
    int csize = col * row;
    for(unsigned int i = 1; i < csize-1; ++i)
        prio[i].set_neighbors(ptrio-1, ptrio+1, ptrio+i, ptrio+i, 0);
    
    ptrio[0].set_neighbors(d_root, ptrio+1, ptrio, ptrio, 0);
    ptrio[csize-1].set_neighbors(csize-2, d_root, ptrio+csize-1, ptrio+csize-1, 0);
    d_root->set_neighbors(ptrio+csize-1, ptrio, 0,0, 0);
    d_columns = ptrio;
  }
  
  triomino* previous_obj_in_col(int col, int row)
  { 
      triomino* col_head = d_columns[col];
      if(col_head->down()==col_head)
          return col_head;
      triomino* prev = col_head->down();
      while(prev-d_rows < row && prev != col_head){
        prev = prev->down();
      }
      return prev;
  }
  void create_objects_of_type(int row, int col, int type)
  {
    vector<int> vtype;
    int shift = 0, cnt = 0;
    vtype.resize(3, 0);
    if(type == 1){
        vtype[0] = 0; 
        vtype[1] = 1;
        vtype[2] = col;
        shift = 0;
    }else if(type == 2){
        vtype[0] = 0; 
        vtype[1] = 1;
        vtype[2] = col+1;
        shift = (row-1)*(col-1);
    }else if(type == 3){
        vtype[0] = 0; 
        vtype[1] = col;
        vtype[2] = col+1;
        shift = 2*(row-1)*(col-1);
    }else if(type == 4){
        vtype[0] = 1; 
        vtype[1] = col;
        vtype[2] = col+1;
        shift = 3*(row-1)*(col-1);
    }else if(type == 5){//flat
        vtype[0] = 0; 
        vtype[1] = 1;
        vtype[2] = 2;
        shift = 4*(row-1)*(col-1);
    }else if(type == 6){//vertical
        vtype[0] = 0; 
        vtype[1] = col;
        vtype[2] = 2*col;
        shift = 4*(row-1)*(col-1)+(col-2)*row;
    }else{
        assert(0);
    }
    int rowlimit = 0, collimit = 0;
    if(type <= 4){
        rowlimit = row-1;
        collimit = col-1;
    }else if (type == 5){
        rowlimit = row;
        collimit = col-2;
    }else{
        rowlimit = row - 2;
        collimit = col;
    }
    cnt = shift;
    for(unsigned int rowi = 0; rowi < rowlimit;++rowi){
        for(unsigned int coli=0; coli < collimit; ++coli){
            int col_index = rowi*col+coli+vtype[0];
            triomino* prev_col = previous_obj_in_col(col_index, cnt);
            d_rows[cnt].set_neighbors(d_rows[cnt+2], d_rows[cnt+1], prev_col, prev_col.down(), d_columns+col_index);
            col_index = rowi*col+coli+vtype[1];
            prev_col = previous_obj_in_col(col_index, cnt+1);
            d_rows[cnt+1].set_neighbors(d_rows[cnt], d_rows[cnt+2], prev_col, prev_col.down(), d_columns+col_index);
            col_index = rowi*col+coli+vtype[2];
            prev_col = previous_obj_in_col(col_index, cnt+2);
            d_rows[cnt+2].set_neighbors(d_rows[cnt+1], d_rows[cnt], prev_col, prev_col.down(), d_columns+col_index);
            cnt += 3;//each block consists of 3 squares
        }
    }
  }
  void create_rows(int row, int col)
  {
    int nrow=0;
    if(col >= 2){
        nrow += (row-1)*(col-1)*4;
    }
    if(col >= 3)
        nrow += row * (col -2);
    if(row >= 3)
        nrow += (row-2)*col;
    //all 6 types(with orientations) triomino has been considered;
    triomino* ptrio = new triomino[nrow*3];
    int cnt = 0;
    if(col>=2 && row >=2){
        create_objects_of_type(row, col, 1);
        create_objects_of_type(row, col, 2);
        create_objects_of_type(row, col, 3);
        create_objects_of_type(row, col, 4);
        create_objects_of_type(row, col, 6);
    }
    if(col >= 3)
        create_objects_of_type(row, col, 5);
    if(row>= 3)
        create_objects_of_type(row, col, 5);
  }
  private:
    triomino* d_root;
    triomino* d_columns;
    triomino* d_rows;
};
int main()
{

}
