#include <vector>
#include <cstdio>
#include "../lib/int.h"
using namespace std;
int main(){
    int minr= 2;
    int init = minr;
    int limit = 51; 
    vector<GeneralInteger> red, black;
    red.resize(init, 0); //0---50
    black.resize(init,1); //0---50
    GeneralInteger sum(0);
    for(int i = minr; i <= limit; ++i){
        sum += black[i-minr];
        red.push_back(sum);
        black.push_back(red[i-1]+black[i-1]);
        printf("%d ",i);
        red[i].print();
        printf(" ");
        black[i].print();
        printf(" \n");
    }
}
