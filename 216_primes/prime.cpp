#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "../lib/tools.h"
#include "../lib/int.h"

//lesson, make sure write the code as described. in witness part, I made 
//a mistake on xi= x_{i-1}^2;
void psimplify(GeneralInteger& gi, unsigned int& p2, GeneralInteger& gu){
    p2 = 0;
    GeneralInteger one(1);
    gu = gi.minus(one);
    bool flag = true;
    while(flag){
        int remainder = gu.getNumber()[0] %2;
        if(remainder == 0)
            ++p2;
        else
            break;
        gu = gu.divide(2);
    }
    return;
}
GeneralInteger modularExp(GeneralInteger& base, GeneralInteger& pwr, const GeneralInteger& mod){
    GeneralInteger gb(base);
    GeneralInteger product(1);
    GeneralInteger gr(1);
    GeneralInteger gt(1);
    while(pwr.numberDigit()> 1 || pwr.getNthDigit(0)!=0){
        int remainder= pwr.getNthDigit(0) %2;
        pwr = pwr.divide(2);
        if(remainder) {
            gt = product.multiply(gb);
            product = gt.divide(mod, gr);
            assert(gr.numberDigit() <= mod.numberDigit());
            product = gr;
        }  //adjust the base
        gt = gb;
        gt = gb.multiply(gt);
        gb = gt.divide(mod, gr);
        assert(gr.numberDigit() <= mod.numberDigit());
        gb = gr;
    }
    return product;
}
//return true if it is composite
bool witness(GeneralInteger& ga, GeneralInteger& cand){
    unsigned int pt = 0;
    GeneralInteger gu(1);
    psimplify(cand, pt, gu);
    GeneralInteger gt(1);
    gt = modularExp(ga, gu, cand);//a^u
    GeneralInteger residual(gt);
    GeneralInteger one(1);
    for(unsigned int i = 0; i < pt; ++i){
        bool flag = !((residual == one)||residual==cand.minus(one));
        gt = residual;
        gu = residual.multiply(gt); 
        gu.divide(cand, residual);
        if(residual == one && flag) return true;
    }
    if(residual == one) return false; 
    return true;
}

bool miller_rabin(GeneralInteger& cand, unsigned int sample){
    for(unsigned int j = 0; j < sample; ++j){
        int xa =1;
	while(xa < 2)
    	   xa = rand()%2791;
	assert(xa > 0);
        GeneralInteger gxa(xa);
        GeneralInteger remainder(1);
        GeneralInteger gy = gxa.divide(cand, remainder);
        if (witness(remainder, cand))
            return false;
    }
    return true;
}

int main(){
    //GeneralInteger gx("197979797979657");
    //GeneralInteger gy("73987946658");
    //GeneralInteger gz(1);
    //GeneralInteger gr(1);
    //gz = gx.divide(gy, gr);  
    //GeneralInteger gx( 3 );
    //GeneralInteger gy( 465789 );
    //GeneralInteger gr(1);
    //gr = modularExp(gx, 3892, gy);
    //gr.print();
    //printf("\n");
    //exit(0);
    //int limit  = 50000000; 
    int limit  = 10;
    int count = 0;
    GeneralInteger two(2);
    GeneralInteger one(1);
    for(int i = 2; i<= limit ; ++i){
        if(i % 10000 == 0) printf("%d, %d\n", i, count);
        GeneralInteger gi(i);
        GeneralInteger gu(i);
        gi = gu.multiply(gi);
        gi = gi.multiply(two);
        gi = gi.minus(one);
        bool flag = miller_rabin(gi , 5);
	if(flag){
		++count;
		gi.print();
		printf("\n");
	}
    }
    printf("%d\n", count);
}
