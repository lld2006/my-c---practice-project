#include "../lib/tools.h"
#include <cstdio>
#include <algorithm>

vector<int> vn1 ={0, 0, 0, 1, 2,3,4,6,8};
vector<int> vn0 ={1, 4, 9, 6, 5,6,9,4,1};

bool vless(const vector<int>& veca, const vector<int>& vecb){
    for(int i = 0; i < 6; ++i){
        if(veca[i] < vecb[i]) 
            return true;
        else if( veca[i] > vecb[i])
            return false;
    }
    return false;
}

bool criteria(const vector<int>& va, const vector<int>& vb)
{
    vector<int> vf1, vf2;
    vf1.resize(10, 0);
    vf2.resize(10, 0);
    for(unsigned int i = 0; i < 6; ++i){
        int na = va[i];
        int nb = vb[i];
        vf1[na] = 1;
        vf2[nb] = 1;
        if(na == 6){
            vf1[9] = 1;
        }else if(na == 9){
            vf1[6] = 1;
        }

        if(nb == 6){
            vf2[9] = 1;
        }else if(nb == 9){
            vf2[6] = 1;
        }
    }
    for(unsigned int i = 0; i < 9; ++i){
        int n1 = vn1[i];
        int n2 = vn0[i];
        if((vf1[n1] && vf2[n2])||(vf1[n2] && vf2[n1]) ){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

bool checkSquare(const vector<int>& veca, const vector<int>& vecb){
    if(vless(vecb, veca)) return false;
    return criteria(veca, vecb);
}

int main(){
    int count = 0, ac=0;
    vector<int> veca, vecb;
    veca.resize(6);
    vecb.resize(6);
    for(unsigned int i = 0; i< 6; ++i){
        veca[i] = i;
        vecb[i] = i;
    }

    do{
        do{ 
            ++ac;
            if(checkSquare(veca, vecb))
                ++count; // all test passed
        }while(next_combination(vecb, 10, 6));   //for b
    }while(next_combination(veca, 10, 6));       //for a
    printf("%d %d\n", count, ac);
}
