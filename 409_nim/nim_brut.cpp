#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int dim = 5;
i64 search_for_winning_position(int nselected, int cpos, const vector<int>& vn )
{
    int dsize = 1<<dim;
    if(cpos==dsize||nselected == dim){
        if(nselected == dim) {
            int result = 0;
            for(unsigned int i = 0; i<vn.size(); ++i){
                result ^= vn[i];
            } 
            if(result)
                return 1;
            else
                return 0;
        }else{
            return 0;
        }
    }
    i64 total = 0;
    for( int j = cpos; j <= dsize - dim +nselected; ++j){
        vector<int> vn1(vn);
        vn1.push_back(j);
        total += search_for_winning_position(nselected+1,j+1, vn1 );
    }
    return total;
}
int main()
{
    vector<int> vflags;
    vector<int> vn;
    i64 result =  search_for_winning_position(0, 1, vn);
    printf("%lld\n", result);
}
