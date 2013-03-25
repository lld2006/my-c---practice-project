#include "../lib/tools.h"
#include <cstdio>
#include <algorithm>

bool vless(const vector<int>& veca, const vector<int>& vecb){
    for(int i = 0; i < 6; ++i){
        if(veca[i] < vecb[i]) 
            return true;
        else if( veca[i] > vecb[i])
            return false;
    }
    return false;
}

bool findab(const vector<int>& va, const vector<int>& vb, int i, int j){
     bool b1 = binary_search(va.begin(), va.end(), i) && 
               binary_search(vb.begin(), vb.end(), j);
     bool b2 = binary_search(va.begin(), va.end(), j) && 
               binary_search(vb.begin(), vb.end(), i);
     return b1 || b2;
}
bool checkSquare(const vector<int>& veca, const vector<int>& vecb){
    if(vless(vecb, veca)) return false;
    if(!findab(veca, vecb, 0, 4)) return false;
    if(!findab(veca, vecb, 0, 1)) return false;
    if(!findab(veca, vecb, 2, 5)) return false;
    if(!findab(veca, vecb, 1, 8)) return false;
    bool flag = findab(veca, vecb, 0, 9) || findab(veca, vecb, 0 ,6);
    if(!flag) return false;
    flag = findab(veca, vecb, 1, 9) || findab(veca, vecb, 1 ,6);
    if(!flag) return false;
    flag = findab(veca, vecb, 3, 9) || findab(veca, vecb, 3 ,6);
    if(!flag) return false;
    flag = findab(veca, vecb, 4, 9) || findab(veca, vecb, 4 ,6);
    if(!flag) return false;
    return true;
}
int main(){
    int count = 0, ac=0;
    vector<int> veca, vecb;
    veca.resize(6, 0);
    vecb.resize(6, 0);
    for(unsigned int i = 0; i< 6; ++i){
        veca[i] = i;
        vecb[i] = i;
    }

    do{
        do{ 
            ++ac;
            //printf("A %d %d %d %d %d %d\n",veca[0], veca[1], veca[2], veca[3], veca[4], veca[5]);
            //printf("B %d %d %d %d %d %d\n",vecb[0], vecb[1], vecb[2], vecb[3], vecb[4], vecb[5]);
            if(checkSquare(veca, vecb))
                ++count; // all test passed
        }while(next_combination(vecb, 10, 6));   //for b
    }while(next_combination(veca, 10, 6));       //for a
    printf("%d %d\n", count, ac);
}
