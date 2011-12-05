#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
//lesson be careful about if elseif and else, did I miss anything like equal? see search_max_sum
void search_cross_max_sum(const vector<int>& vec, const int begin, const int mid, const int end,
                     int& mleft, int& mright, int& msum){
    int left_max = -10000000;
    int sum = 0;
    for(int i = mid; i >= begin; --i){
        sum += vec[i];
        if(sum > left_max){
            left_max = sum;
            mleft = i;
        }
    }
    int right_max = -10000000;
    sum = 0;
    for(int i = mid + 1; i <= end; ++i){
        sum += vec[i];
        if(sum > right_max){
            right_max = sum;
            mright = i;
        }
    }
    msum = left_max+right_max;
    return;
}
void search_max_sum(const vector<int>& vec, const int begin, const int end,
                   int& rbegin, int& rend, int& max_sum){
    //rbegin and rend stand for range begin and range end
    assert(begin >= 0 && begin < static_cast<int>(vec.size()));
    assert(end >= 0 && end < static_cast<int>(vec.size()));
    if(begin == end){
        rbegin = begin;
        rend = end;
        max_sum = vec[begin];
        return;
    } else {
        int mid = (begin + end) /2;
        int leftb=0, lefte=0, leftsum=0;
        int rightb=0, righte=0, rightsum=0;
        int mleft=0, mright=0, msum=0;
        search_max_sum(vec, begin, mid, leftb, lefte, leftsum);
        search_max_sum(vec, mid+1, end, rightb, righte, rightsum);
        search_cross_max_sum(vec, begin, mid, end, mleft, mright, msum);
        if(leftsum >= rightsum && leftsum >= msum){
            rbegin = leftb;
            rend = lefte;
            max_sum = leftsum;
            return;
        }else if(rightsum >= leftsum && rightsum >= msum){
            rbegin = rightb;
            rend = righte;
            max_sum = rightsum;
            return;
        }else{
            rbegin = mleft;
            rend = mright;
            max_sum = msum;
            return;
        }
    }
    assert(0);
    return;
}
int main(){
    int dim = 2000;
    //int dim = 4;
    vector<int> table;
    table.resize(dim*dim, 0);
    //table[0] = -2; table[1]=5; table[2]=3; table[3]=2;
    //table[4] = 9; table[5]=-6; table[6]=5; table[7]=1;
    //table[8] = 3; table[9]=2; table[10]=7; table[11]=3;
    //table[12] = -1; table[13]=8; table[14]=-4; table[15]=8;
    for(int i = 1; i<= 55; ++i){
        i64 value = 100003 - 200003LL*i + 300007LL*i*i*i;
        value %= 1000000;
        table[i-1] =static_cast<int>(value - 500000);
    }
    for(int i = 55; i < dim*dim; ++i){
        table[i] = (table[i-24]+ table[i-55]+1000000);
        assert(table[i] > 0);
        table[i] %= 1000000;
        table[i] -= 500000;
    }
    //this problem is similar to a previous problem, here, the 
    //diagonal finding method is better than what I did before.
    //search row;
    vector<int> rvec;
    int gsum = -100000000;
    for(int row = 0; row < dim; ++row){
        rvec.clear();
        rvec.resize(dim, 0);
        for(int col = 0; col < dim; ++col)
            rvec[col] = table[index0(dim, row, col)];
        int begin=0, end=0, maxsum = 0;
        assert(!rvec.empty());
        search_max_sum(rvec, 0, rvec.size()-1, begin, end, maxsum);
        if(gsum < maxsum)
            gsum = maxsum;
    }
    //search col;
    for(int col = 0; col < dim; ++col){
        rvec.clear();
        rvec.resize(dim, 0);
        for(int row = 0; row < dim; ++row)
            rvec[row] = table[index0(dim, row, col)];
        int begin=0, end=0, maxsum = 0;
        assert(!rvec.empty());
        search_max_sum(rvec, 0, rvec.size()-1, begin, end, maxsum);
        if(gsum < maxsum)
            gsum = maxsum;
    }
    //search main diagonal
    for(int diag = dim-1; diag> -dim; --diag){
         rvec.clear();
         int rsize = diag > 0? dim - diag: dim+diag;
         rvec.resize(rsize, 0);
         for(int j = 0; j < rsize; ++j){
             if(diag >= 0)
                 rvec[j] = table[index0(dim, j, diag+j)];
             else
                 rvec[j] = table[index0(dim, j-diag, j)];
         }
        int begin=0, end=0, maxsum = 0;
        assert(!rvec.empty());
        search_max_sum(rvec, 0, rvec.size()-1, begin, end, maxsum);
        if(gsum < maxsum)
            gsum = maxsum;
    }
    //search anti diagonal
    for(int shift = 0; shift < 2*dim-1; ++shift){
        int rsize = shift < dim? shift+1 : 2*dim-shift-1;
        rvec.clear();
        rvec.resize(rsize, 0);
        for(int j = 0; j < rsize; ++j){
            if(shift > dim - 1)
                rvec[j] = table[index0(dim, shift+j+1-dim, dim -j-1)];
            else
                rvec[j] = table[index0(dim, j, shift -j )];
        }
        int begin=0, end=0, maxsum = 0;
        assert(!rvec.empty());
        search_max_sum(rvec, 0, rvec.size()-1, begin, end, maxsum);
        if(gsum < maxsum)
            gsum = maxsum;
    }
    printf("%d\n", gsum);
}
