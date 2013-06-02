#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;

vector<i64> v5;
i64 vn(int nth)
{
    assert(nth > 0);
    if(v5[nth] > 0)
       return v5[nth];
    if(nth == 1){
        v5[nth] = 1;
        return 1;
    }
    if(nth == 2){
       v5[nth] = 3;
       return 3;
    } 
    i64 result = 2*vn(nth-1)+5*vn(nth-2);
    v5[nth] = result;
    return result;
}
//ndigits is the totoal number of digits
//cdigit is the current digit under consideration, cth
//restricted is tricky if it is 0, not restricted,
//if it is one totally restricted.
//if it equals 2, somehow restricted by a consecutive of 2's in front of it'
i64 find_all_t5(int cdigit, int pcarriers, int carriers, vector<int>& vtarget, int ndigits, int restricted)
{
    i64 sum = 0;
    //nleft is number of active digits. # of carriers are set 
    //to zero (actually one more, considered in main)
    int nleft = ndigits - cdigit -carriers;
    if(nleft < 0) return 0;
    if(nleft == 0){
        //if(restricted==0) 
        //    return 0;
        //else
            return 1;
    }
    int nc = vtarget[cdigit];
    if(restricted == 0){
        //if(cdigit ==0)
        //    return vn(nleft+1)-1;
        //else
            return vn(nleft+1);

    }else if(restricted == 1){
        for(int i = 0; i< nc; ++i){
            if(i<2){
                sum += find_all_t5(cdigit+1, 0, carriers, vtarget, ndigits, 0);
            }else if(i==2){
                //how to solve this part, 
                sum += find_all_t5(cdigit+1, pcarriers+1, carriers, vtarget, ndigits, 2);
            }else{
                assert(i==3);
                sum += find_all_t5(cdigit+1, 0, carriers+pcarriers+1, vtarget, ndigits, 0);
            }
        }
        //==nc case added
        if(nc < 2){
            sum += find_all_t5(cdigit+1, 0, carriers, vtarget, ndigits, 1);
        }else if (nc == 2){
            sum += find_all_t5(cdigit+1, pcarriers+1, carriers, vtarget, ndigits, 1);
        }else{//nc > 2
            sum += find_all_t5(cdigit+1, 0, carriers+pcarriers+1, vtarget, ndigits, 1);
        }
    }else{//not restricted, but need to check everything
        for(int i = 0; i< 5; ++i){
            if(i<2){
                sum += find_all_t5(cdigit+1, 0, carriers, vtarget, ndigits, 0);
            }else if(i==2){
                sum += find_all_t5(cdigit+1, pcarriers+1, carriers, vtarget, ndigits, 2);
            }else{
                sum += find_all_t5(cdigit+1, 0, carriers+pcarriers+1, vtarget, ndigits, 0);
            }
        }
    } 

    return sum;
}
int main()
{
    v5.resize(30, 0);
    i64 target = 1000000000000000000LL;
    //target = 1000000000;
    vector<int> vtarget;
    i64 t = target;
    while(t){
        int res = t % 5;
        vtarget.push_back(res);
        t/=5;
    }
    reverse(vtarget.begin(), vtarget.end());
    //now vtarget provide the limit from high digits to low.
    i64 sum = 0;
    int ndigit = vtarget.size();
    //current implementation will incur double counting in zeros.
    sum += find_all_t5(0, 0, 0, vtarget, ndigit-1, true);
    printf("%lld\n", sum-1);//an extra 0 is introduced!
}
