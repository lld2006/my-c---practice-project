#include "../lib/tools.h"
//vn how are the number used
//nt is the total sum
//ncur is the current number to be continued
//ncount is the number counted should be less than equal to 10
//4511732542
//40561817703823564929
int ng = 10;
i64 ngf=3628800LL;
i64 find_all_sol(const vector<int>& vn, i64 nt, int ncur, int ncount)
{
    if(ncur == ng){ //all processed
        if(ncount != ng) return 0LL;
        if((ng*(ng-1)-2*nt)%11 != 0) return 0LL;
        assert(vn.size()==ng);
        //need some post processing especially for 0
        i64 fac = ngf*ngf;
        if(vn[0] == 0){
            for(int i = 0; i < ng; ++i){
                if(vn[i] == 0|| vn[i]==2)
                    fac /= 2;
            }
        }else if(vn[0] == 1){
            fac *= ng-1; //0 can not be the first number
            fac /= ng;
            for(int i = 1; i < ng; ++i){
                if(vn[i] == 0|| vn[i]==2)
                    fac /= 2;
            }
        }else{//two zero in odd positions
            fac *= ng-2; //0 can not be the first number
            fac /= ng;
            for(int i = 0; i < ng; ++i){
                if(vn[i] == 0|| vn[i]==2)
                    fac /= 2;
            }
        }
        return fac;
    }
    vector<int> vn1(vn);
    i64 sum = 0LL;
    int nmax = 2 <= (10-ncount)? 2:(10-ncount);
    for(int i = 0; i <=nmax; ++i){
        vn1[ncur] = i;
        sum += find_all_sol(vn1, nt+i*ncur, ncur+1, ncount+i);
    }
    return sum;

}
int main()
{
    vector<int> vn;
    vn.resize(10, 0);
    i64 sum = find_all_sol(vn, 0, 0, 0);
    printf("%lld\n", sum);
}
