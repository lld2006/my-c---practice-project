#include <cassert>
#include <cstdio>
#include "../lib/typedef.h"

i64 sum = 0;
class triomino //object
{
  public:
  triomino():  d_left(0)
              ,d_right(0)
              ,d_up(0)
              ,d_down(0)
              ,d_column_head(0)
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
  void set_head(triomino* h) {d_column_head= h;}
  void set_rc(int nr, int nc) 
  {
      d_nrow = nr;
      d_ncol = nc;
  }
  void inc_size()            {++d_size;}
  void dec_size()            {--d_size;}
  int size()                 { return d_size;}
  triomino* left(){return d_left;}
  triomino* right(){return d_right;}
  triomino* up() {return d_up;}
  triomino* down() {return d_down;}
  triomino* c() {return d_column_head;}
  int row() {return d_nrow;}
  int col() {return d_ncol;}
  private:
    triomino* d_left;
    triomino* d_right;
    triomino* d_up;
    triomino* d_down;
    triomino* d_column_head;
    int d_nrow;
    int d_ncol;
    int d_size;
};
class exact_cover_solver
{
  public:
  int debug_curr() const
  {
      return 1;
      static int debug_cnt = 0;
      ++debug_cnt;
      int tot_col = 0;
      triomino *head = d_root;
      //while(true){
      //  printf("col %d left %d right %d\n", head-d_columns, head->left()-d_columns, head->right()-d_columns);
      //  if(head->right()==d_root) break;
      //  ++head;
      //}
      head = d_root->right();
      while(head != d_root){
          assert(head->right()->left()==head);
          assert(head->left()->right()==head);
          ++tot_col;
          int cnt = 0;
          triomino *entry = head->down();
          while(entry != head){
              printf("entry %p row= %d col=%d\n", entry, entry->row(), entry->col());
              ++cnt;
              entry = entry->down();
          }
          assert(head->size() == cnt);
          printf("col summary: col %d # %d cnt %d\n", (int)(head-d_columns), head->size(), cnt);
          head = head->right();
      }
      printf("cfg: total column %d\n", tot_col);
      return 1;
  }
  exact_cover_solver()
  {
      d_rows = 0;
      d_root = 0;
      d_columns = 0;
  }
  ~exact_cover_solver()
  {
      delete d_rows;
      delete d_columns;
      delete d_root;
  }
  void create_solver(int row, int col)
  {
      create_root();
      create_columns(row, col);
      create_rows(row, col);
  }
  void create_root()
  {
      d_root = new triomino;
  }
  //create_columns create all heads of the column
  void create_columns(int row, int col)//create all column objects; empty and linked
  {
    triomino* ptrio = new triomino[row*col];
    int csize = col * row;
    for( int i = 1; i < csize-1; ++i){
        ptrio[i].set_neighbors(ptrio+i-1, ptrio+i+1, ptrio+i, ptrio+i, 0);
        ptrio[i].set_rc(-1, i);
    }
    
    ptrio[0].set_neighbors(d_root, ptrio+1, ptrio, ptrio, 0);
    ptrio[0].set_rc(-1, 0);
    ptrio[csize-1].set_neighbors(ptrio+csize-2, d_root, ptrio+csize-1, ptrio+csize-1, 0);
    ptrio[csize-1].set_rc(-1, csize-1);
    d_root->set_neighbors(ptrio+csize-1, ptrio, 0,0, 0);
    d_root->set_rc(-1,-1);
    d_columns = ptrio;
  }
  
  triomino* previous_obj_in_col(int col, int row)
  { 
      triomino* col_head = d_columns+col;
      if(col_head->down()==col_head)  // nothing except the col_head
          return col_head;
      triomino* prev = col_head, *curr = col_head->down(); 
      while( curr < d_rows+ row && curr != col_head){
        prev = curr;
        curr = curr->down();
      }
      return prev;
  }
  void create_objects_of_type(int row, int col, int type)
  {
    vector<int> vtype;
    int shift = 0; //shift is the shift of triominos
    vtype.resize(3, 0);
    if(type == 1){
        vtype[0] = 0;       //  * *
        vtype[1] = 1;       //  *
        vtype[2] = col;
        shift = 0;
    }else if(type == 2){
        vtype[0] = 0;       // * *
        vtype[1] = 1;       //   *
        vtype[2] = col+1;
        shift = 3*(row-1)*(col-1);
    }else if(type == 3){
        vtype[0] = 0;       // *
        vtype[1] = col;     // * *
        vtype[2] = col+1;
        shift = 6*(row-1)*(col-1);
    }else if(type == 4){
        vtype[0] = 1;       //   *
        vtype[1] = col;     // * *
        vtype[2] = col+1;
        shift = 9*(row-1)*(col-1);
    }else if(type == 5){//flat
        vtype[0] = 0;   // * * *
        vtype[1] = 1;
        vtype[2] = 2;
        shift = 12*(row-1)*(col-1);
    }else if(type == 6){//vertical
        vtype[0] = 0;       // *   
        vtype[1] = col;     // *
        vtype[2] = 2*col;   // *
        shift = 12*(row-1)*(col-1)+3*(col-2)*row;
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
        rowlimit = row-2;
        collimit = col;
    }
    int cnt = shift;
    for( int rowi = 0; rowi < rowlimit;++rowi){
        for( int coli=0; coli < collimit; ++coli){
            int col_index = rowi*col+coli+vtype[0];
            triomino* prev_col = previous_obj_in_col(col_index, cnt);
            d_rows[cnt].set_neighbors(d_rows+cnt+2, d_rows+cnt+1, prev_col, prev_col->down(), d_columns+col_index);
            prev_col->down()->set_up(d_rows+cnt);
            prev_col->set_down(d_rows+cnt);
            d_rows[cnt].set_rc(cnt/3, col_index);
            d_columns[col_index].inc_size();

            col_index = rowi*col+coli+vtype[1];
            prev_col = previous_obj_in_col(col_index, cnt+1);
            d_rows[cnt+1].set_neighbors(d_rows+cnt, d_rows+cnt+2, prev_col, prev_col->down(), d_columns+col_index);
            d_rows[cnt+1].set_rc(cnt/3, col_index);
            prev_col->down()->set_up(d_rows+cnt+1);
            prev_col->set_down(d_rows+cnt+1);
            d_columns[col_index].inc_size();

            col_index = rowi*col+coli+vtype[2];
            prev_col = previous_obj_in_col(col_index, cnt+2);
            d_rows[cnt+2].set_neighbors(d_rows+cnt+1, d_rows+cnt, prev_col, prev_col->down(), d_columns+col_index);
            d_rows[cnt+2].set_rc(cnt/3, col_index);
            prev_col->down()->set_up(d_rows+cnt+2);
            prev_col->set_down(d_rows+cnt+2);
            d_columns[col_index].inc_size();
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
    assert(d_rows == 0);
    d_rows = new triomino[nrow*3];
    if(col>=2 && row >=2){
        create_objects_of_type(row, col, 1);
        create_objects_of_type(row, col, 2);
        create_objects_of_type(row, col, 3);
        create_objects_of_type(row, col, 4);
    }
    if(col >= 3)
        create_objects_of_type(row, col, 5);
    if(row >= 3)
        create_objects_of_type(row, col, 6);
  }
  void search(int k)
  {
    // find one solution
    if(d_root->right() == d_root){
        //printf("let me see");
        ++sum;
        return;
    }
    //find the column with minimum branches
    int branch_min = 1000000;
    triomino* curr = d_root->right(), *tc = d_root;
    while(curr != d_root){
        assert(curr->size() >= 0);
        if(curr->size() < branch_min){
            branch_min = curr->size();
            tc = curr;
        }
        curr = curr->right();
    };

    //cover column with minimum branch
    debug_curr();
    cover(tc);//tc header
    debug_curr();
    triomino* tr = tc->down();
    while(tr != tc){
        triomino* t_k = tr;
        triomino* trj = tr->right();
        while(trj != tr){
            cover(trj->c());
            trj = trj->right();
        }
        debug_curr();
        search(k+1);
        debug_curr();
        tr = t_k;
        tc = tr->c();
        //uncover
        triomino* tl = tr->left();
        while(tl != tr){
            uncover(tl->c());
            tl = tl->left();
        }
        tr = tr->down();
    };
    debug_curr();
    uncover(tc);
    debug_curr();
    return;
  }

  void uncover(triomino* ctrio)
  {
//      printf("uncovering %d\n", (int)(ctrio-d_columns));
      assert(ctrio->c() == 0);
        triomino* tui = ctrio->up();
        while(tui != ctrio){
            assert(tui->row()!=-1|| tui==ctrio);
            triomino* tlj = tui->left();
            while(tlj != tui){
                tlj->c()->inc_size();
                tlj->down()->set_up(tlj);
                tlj->up()->set_down(tlj);
                tlj = tlj->left();
            }
            assert(ctrio->right()->left() == ctrio->left());
            assert(ctrio->left()->right() == ctrio->right());
            tui = tui->up();
        }
        ctrio->right()->set_left(ctrio);
        ctrio->left()->set_right(ctrio);
  }
  void cover(triomino* ctrio)
  {
    //printf("covering %d\n", (int)(ctrio-d_columns));
    assert(ctrio->c() == 0);
    triomino *lt, *rt, *dt;
    //first remove the column from the header 
    rt = ctrio->right();
    lt = ctrio->left();
    ctrio->right()->set_left(lt);
    ctrio->left()->set_right(rt);
    //cover
    dt = ctrio->down();
    while(dt != ctrio){
        triomino *dtrj = dt->right();
        while( dtrj != dt ){
            (dtrj->down())->set_up(dtrj->up());
            (dtrj->up())->set_down(dtrj->down());
            dtrj->c()->dec_size();
            assert(dtrj->c()->size() >= 0);
            dtrj = dtrj->right();
        }
        dt = dt->down();
    };

  }
  private:
    triomino* d_root;
    triomino* d_columns; //triomino head
    triomino* d_rows; // rows of triominos
};
int main()
{
    exact_cover_solver esolver;
    int trow = 9, tcol = 12;
    esolver.create_solver( trow, tcol );
    esolver.search(0);
    printf("%lld\n", sum);
}
