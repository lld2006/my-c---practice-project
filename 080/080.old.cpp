#include "../lib/int.h"
#include <cstdlib>
#include <numeric>
using namespace std;
int main(){
    int nextSquare = 2;
    int sum =0;
    vector<int> init;
    init.resize(240, 0);
    init.push_back(3);
    GeneralInteger three(init);// three is 3*10^240
    init.back() = 2;
    GeneralInteger two(init);
    for(int i = 2; i<= 99; ++i){
        //avoid perfect square
        if(i==nextSquare*nextSquare){
            ++nextSquare;
            continue;
        }
        //initial guess 
        init.clear();
        init.resize(119, 0);
        init.push_back(1);
        GeneralInteger x0(init);
        GeneralInteger x1(0);
        GeneralInteger x2(0);
        GeneralInteger remainer(0);
        while(true){
            x1 = x0.multiply(three); 
            x2 = x0.multiply(x0);
            x2 = x2.multiply(x0);
            x2 = x2.multiply(i);
            x2 = x1.minus(x2);
            x2 = x2.divide(two, remainer);
            x2.clear0();
            if(x0.getNumber() == x2.getNumber())
                break;
            x0 = x2;
        }
        x2=x2.multiply(i);
        int value = accumulate(x2.getNumber().end()-100, x2.getNumber().end(), 0);
        sum += value;
    }
    printf("%d \n", sum);
}
