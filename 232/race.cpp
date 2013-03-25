#include "../lib/tools.h"
//#include <cmath>
#include <cassert>
#include <cstdio>
int dim = 100;
vector<long double> vrace;
void prace(int na, int nb){

    double pa = 1, pb = 1;
    double pam = 1, pbm = 1;
    for(int j = 1; j <= 8; ++j){
        int bindex = nb+power(2, j-1);
        int nbprime = bindex > dim? dim:bindex;
        pa = vrace[index0(dim+1, na, nbprime)]/(power(2, j)-1);
        pb = vrace[index0(dim+1, na+1, nbprime)]/(power(2, j)-1);
        if( pam < pa)
            pam = pa;
        if(pbm < pb)
            pbm = pb;
    }
    vrace[index0(dim+1, na, nb)]= (pam +pbm)/2;
}
int main(){
   vrace.resize((dim+1)*(dim+1), 0);
   int na, nb;
   na = dim;
   for(nb=0; nb <= dim; ++nb)
       vrace[index0(dim+1, na, nb)] = 0;
   nb = dim;
   for(na = 0; na < dim; ++na)
       vrace[index0(dim+1, na, nb)] = 1;
   for(int loop = dim-1; loop >= 0; --loop){
       na = loop;
       for(nb = loop; nb >=0; --nb){
            prace(na, nb);
       }
       nb = loop;
       for(na = loop-1; na >=0; --na)
            prace(na, nb);
   }
   printf("%30.20Lf\n", vrace[0]);
}
