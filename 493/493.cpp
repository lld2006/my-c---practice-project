# include "../lib/tools.h"
int main()
{
    //i64 n19 = 19;
    i64 ntotal = 0;
    i64 sum = 0;
    //for(i64 ncolor = 2; ncolor <= 7; ++ncolor ){
    //    ni = combination(19LL, ncolor-1LL);
    //    nj = 0;
    //    for(i64 n1 = 11; n1 <= 21-ncolor; ++n1){
    //        nj += combination(19-n1, ncolor - 2LL);
    //    }
    //    nj*=ncolor;
    //    ni -= nj;
    //    ni *= combination(7LL, ncolor);
    //    ntotal += ni;
    //    ni *= ncolor; //sum * ncolor
    //    sum += ni;
    //    printf("%Ld %Ld\n", ncolor, ni);
    //}
    for(i64 ni=10; ni >=1; --ni){
        sum += combination(10LL, ni) * combination(60LL, 20-ni);
    }
    sum *= 7LL;
    ntotal = combination(70LL, 20LL);
    double value = double(sum)/double(ntotal);
    printf("%Ld %Ld %20.15f\n", sum, ntotal, value);
}
