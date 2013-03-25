#include "../lib/int.h"
#include <cstdlib>
#include <numeric>
using namespace std;
int main(){
    int nextSquare = 2;
    int sum =0;
    for(int i = 2; i<= 99; ++i){
        if(i==nextSquare*nextSquare){
            ++nextSquare;
            continue;
        }
        vector<int> init ;
        init.resize( 240, 0);
        int j = i;
        while(j){
            int res = j%10;
            init.push_back(res);
            j /= 10;
        }
        //initialization done
        //initial guess 
        init.clear();
        init.resize(116, 0);
        init.push_back(9);
        init.push_back(9);
        GeneralInteger x0(init);
        init.clear();
        init.resize(240, 0);
        init.push_back(3);
        GeneralInteger three(init);
        GeneralInteger x1(0);
        GeneralInteger x2(0);
        while(true){
            x1 = x0.multiply(three); 
            x2 = x0.multiply(x0);
            x2 = x2.multiply(x0);
            x2 = x2.multiply(i);
            x2 = x1.minus(x2);
            x2 = x2.divide(2);
            x2.clear0();
            if(x0.getNumber() == x2.getNumber())
                break;
            x0 = x2;
        };
        x2=x2.multiply(i);
        //x2.print();
        //printf("   %d \n", i);
        sum += accumulate(x2.getNumber().end()-100, x2.getNumber().end(), 0);
    }
    printf("%d \n", sum);
}
