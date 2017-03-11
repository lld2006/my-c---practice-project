#include "../lib/tools.h"
int main()
{
    
    i64 nmax = 1000000000000000000LL;
    //nmax = 10;
    i64 x17p5=17LL*289*289;
    i64 x17p6=17LL*x17p5;
    i64 nmod = 410338673;//17^7
    i64 x, y, g;
    i64 p1=nmax % x17p5;
    extended_euclid(16LL, x17p5, x,y,g );
    p1 = multmod(p1, x, x17p5);
    p1 *= 16LL;
    p1 %= x17p6;
    if(p1 < 0) p1 += 16LL*x17p6;
    p1 = powermodule(10LL, p1, x17p6);
    extended_euclid(16LL, x17p6, x, y, g);
    p1 = multmod(x, p1, x17p6);
    p1 *= 16;
    p1 %= nmod;
    if(p1 < 0) p1+= 16*x17p6;
    i64 y1 = powermodule(2LL, p1, nmod);
    i64 y2 = powermodule(4LL, p1, nmod);
    extended_euclid(15LL, nmod, x, y, g);
    i64 t = 14-20LL*y1+6*y2;
    t %= nmod;
    t *= x;
    t %= nmod;
    printf("%lld\n", t);
    return 0;
    //int dim = 4;
    //vector<i64> vmat;
    //vmat.resize(16, 0);
    //vmat[0]=6; vmat[1]=-7; vmat[2]=-6; vmat[3]=8;
    //vmat[4] = 1; vmat[9]=1;vmat[14]=1;
    //vector<i64> rhs ={0, 2, 12, 58};
    ////set<int> valueSet = {0, 2, 12, 58}; 
    //int pos = 0;
    //vector<i64> coeff={8,-6,-7,6};
    //for(unsigned int j = 4; j<=100000000; ++j){
    //    i64 val = 0;
    //    for(int k = pos; k <pos+4; ++k){
    //        int kk=k%4;
    //        val += coeff[k-pos]*rhs[kk];
    //    }
    //    val %= nmod;
    //    if(val < 0) val += nmod;
    //    rhs[pos++] = val;
    //    if(pos == 4) pos = 0;
    //    printf("%lld\n", val);
    //    //if(!valuseSet.insert(val).second) break;
    //}

    //vector<i64> result = matrix_power(vmat, nmax, nmod, dim);
    //vector<i64> rrhs ={0, 0,0,0};
    //for( int i = 0; i<dim; ++i){
    //    for( int j = 0; j<dim; ++j){
    //        rrhs[i] += result[i*dim+j]*rhs[j];
    //        rrhs[i]%= nmod;
    //    }
    //}
    //printf("result is %lld\n", (rrhs[0]+rrhs[1]*2)%nmod);
}
