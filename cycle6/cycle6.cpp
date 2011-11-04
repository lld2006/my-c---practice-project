#include <cassert>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
// lesson, learnt how to delete elements while iterating.
int fnum(const int ti, const int i){ 
    switch(ti){
        case 3:
            return i * (i + 1)/2;
        case 4:
            return i * i;
        case 5:
            return i* (3 * i - 1)/2;
        case 6:
            return i*(2*i-1);
        case 7:
            return i*(5*i-3)/2;
        case 8:
            return i*(3*i-2);
        default:
            assert(0);
    }
}
// the first version of this part is buggy, need to consider hi lo in different set
bool find (int ni, int num, const vector<set<int> >& number ){
    int hi = num / 100;
    int lo = num % 100;
    int hicount =0, locount = 0;
    int hiset = -1; 
    int loset = -1;
    for(int i = 0; i < 6; ++i){
        if( i == ni ) continue;
        const set<int>& tset = number[i];
        set<int>::const_iterator iter;
        for(iter = tset.begin(); iter != tset.end(); ++iter){
            int thi = (*iter)/100;
            int tlo = (*iter)/100;
            if(thi == lo) {
                ++hicount;
                hiset = i;
            }
            if(tlo == hi ){
                ++locount;
                loset = i;
            }
            if( (hiset >= 0 && loset >= 0) && (hicount+locount>2|| hiset != loset))
                return true;
        }
    }
    return false;
}
    
int main(){
   vector<set<int> > number, nh2, nl2; // 3 4 5 6 7 8 ~ 0 - 5
   number.resize(6); 
   for(int i = 0; i < 6; ++i){
       for( int j = 10; j; ++j){
           int num = fnum(i+3, j);
           if(num < 1010) continue;
           if(num > 9999) break;
           int res = num % 100;
           if(res < 10) continue;
           number[i].insert(num);
       }
   }
   for(int i= 0; i <6; ++i){
        printf("number in %d is %u\n",i+3, number[i].size() );
   }
   set<int>& tset = number[i]; 
   vector<int> flag;
   vector<int> stackvec;
   set<int>::iterator iter1, iter2, iter3, iter4, iter5, iter6;
   for(iter1 = tset.begin(); iter1 != tset.end(); ){
        flag.resize(6,0);
        flag[0] = 1;
        int num = *iter;
        if(hasCyclic(i, num, number )){
            ++iter;
            continue;
        } else{
            tset.erase(iter++);
        }
   }
   for(int i= 0; i <6; ++i){
        printf("number in %d is %u\n",i+3, number[i].size() );
   }
}
