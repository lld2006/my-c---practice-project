#include "../lib/tools.h"
#include <cmath>
#include <cassert>
#include <algorithm>
#include <cstdio>
using namespace std;
//lesson, when some criteria is met, we need to exit the loop. do not forget the break;

enum operation {ADD = 0, MINUS = 1, MULT=2, DIV=3};
//double value = calc(pnumber, op, opOrder);
double calc(const vector<int>& pnumber, const vector<int>& op, const vector<int>& opOrder){
    double ret = 0;
    vector<double> pd;
    vector<int> opc, order;
    opc = op;
    order = opOrder;
    pd.resize(4, 0);
    for(int i = 0; i < 4; ++i){
        pd[i]=pnumber[i]+1;
    }
    while(order.size()){
        int iorder = order[0];
        double nfir = pd[iorder];
        double nsec = pd[iorder+1];
        switch(opc[iorder]){
            case ADD:
                ret = nfir + nsec;
                break;
            case MINUS:
                ret = nfir-nsec;
                break;
            case MULT:
                ret = nfir*nsec;
                break;
            case DIV:
                ret = nfir/nsec;
                break;
            default:
                assert(0);
        }
        pd[iorder]=ret;
        pd.erase(pd.begin()+iorder+1);
        opc.erase(opc.begin()+iorder);
        order.erase(order.begin());
        for(unsigned int i = 0; i < order.size(); ++i){
            if(order[i] > iorder)
                --order[i];
        }
    }
    return ret;
}
int main(){
    vector<int> number, valFlag, opOrder, op, pnumber;
    int amax = 0;
    number.resize(4,0);
    opOrder.resize(3, 0);
    op.resize(3,0);
    for(int i =0 ; i<=3; ++i){
        number[i] = i;
    }
    for(int i=0; i<=2; ++i){
        opOrder[i]=i;
    }
    do{//each digit set
        valFlag.clear();
        valFlag.resize(500, 0);
        valFlag[0]=1;//start from 1
        pnumber = number;
        do{
            do{
                for(op[0] = 0; op[0]<=3; ++op[0]) //operator 0 -1
                    for(op[1] = 0; op[1]<=3; ++op[1])// 1--2
                        for(op[2]=0; op[2]<=3; ++op[2]){//2--3
                            double value = calc(pnumber, op, opOrder);
                            if(value < 500 && value >0){
                                int rval = round(value);
                                if(fabs(value - rval) < 1e-6)
                                    valFlag[rval]=1;
                            }
                        }
            }while(next_permutation(opOrder.begin(), opOrder.end()));
        }while(next_permutation(pnumber.begin(), pnumber.end()));
        //check consecutive vals
        int tmax = 0;
        for(unsigned int i =1; i< valFlag.size(); ++i){
            if(valFlag[i])
                continue;
            else{
                tmax = i -1;
                break;
            }
        }
        if(tmax > amax){    
            amax = tmax;
            printf("%d %d %d %d %d\n",number[0], number[1], number[2], number[3], amax);
        }
    }while(next_combination(number, 9, 4));
}

