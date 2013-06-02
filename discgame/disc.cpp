#include "../lib/int.h"
#include "../lib/tools.h"
int main(){
    int round = 15;
    GeneralInteger gden(1);
    GeneralInteger gnum(0);
    for(int i= 0; i< round; ++i){
        gden = gden.multiply(i+2);
    }
    gden.print();
    printf("\n");
    for(int i = (round/2)+1; i<=round; ++i){
        vector<int> combi;
        vector<int> flag;
        combi.resize(i);
        for(unsigned int j = 0; j < combi.size(); ++j)
            combi[j]= j;
        do{
            flag.clear();
            flag.resize(round, 0);
            for(unsigned int j = 0; j < combi.size(); ++j)
                flag[combi[j]] = 1;
            GeneralInteger gtp(1);
            for(unsigned int j = 0; j < flag.size(); ++j){
                if(flag[j] == 0)
                    gtp = gtp.multiply(j+1);
            }
            gnum += gtp;
        }while(next_combination(combi, round, i));
    }
    gnum.print(1);
    GeneralInteger gr(1);
    gden.print();
    //gr= gden.divide();
    printf("\n");
}
