#include "../lib/typedef.h"
#include "../lib/tools.h"
#include "../lib/int.h"
#include <set>
#include <cstdlib>
using namespace std;
//lesson, when write a less operator, be careful about all situations that may occur

int main(){
    int limit = 50;
    int count = 1;
    vector<IntPairVec> facs;
    vector<GeneralInteger> triangle;
    set<GeneralInteger> numberset;
    vector<int> factors; // simple implementation
    triangle.resize(limit/2+1, GeneralInteger(0));
    triangle[0] = GeneralInteger(1);
    facs.resize(52);
    vector<int> primes;
    primeWithin(primes, 50); 
    for(int i = 2; i<= limit; ++i){
        factor(i, facs[i], primes);
    }
    for(int i = 2; i<=limit; ++i){
        //first generate the value on row i
        for(int j = i/2; j >= 0; --j){
            int fir = j;
            int sec = j-1;
            if( fir > (i-1)/2) {
                assert(j >= 1);
                triangle[j] = triangle[j-1].multiply(2);
            }else if ( sec < 0){
                continue; //keep the value 1
            }else{
                triangle[j]= triangle[fir]+triangle[sec];
            }
        }
        //check square item, insert square free item into set
        for(int j=1; j<=i/2;++j){
            factors.clear();
            factors.resize(48,0);
            for(int k = i; k >= i-j+1; --k){
                for(unsigned int p=0; p<facs[k].size();++p){
                    assert(facs[k][p].first > 1);
                    assert(facs[k][p].first <=47);
                    factors[facs[k][p].first] += facs[k][p].second;
                }
            }// large values positive
            for(int k = 2; k <= j; ++k){ //!! 1 has no factor
                for(unsigned int p=0; p<facs[k].size(); ++p){
                    assert(facs[k][p].first > 1);
                    assert(facs[k][p].first <=47);
                    factors[facs[k][p].first] -= facs[k][p].second;
                }
            }//small values negative
            //check square now
            bool flag = false;
            for(int k = 2; k <= 47; ++k){
                assert(factors[k]>=0);
                if(factors[k] >= 2){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                ++count;
                //printf("%d %d ", i, j);
                //triangle[j].print();
                //printf("\n");
                numberset.insert(triangle[j]);
            }
        }
    }
    //sum the items in the set
    //triangle[25].print();
    printf("\n");
    GeneralInteger gx(1);
    for(set<GeneralInteger>::iterator iter = numberset.begin(); iter != numberset.end(); ++iter){
        gx += *iter;
        //iter->print();
        //printf("\n");
    }
    gx.print();
    printf("\n");
    printf("%d %d\n", count, numberset.size());

}
