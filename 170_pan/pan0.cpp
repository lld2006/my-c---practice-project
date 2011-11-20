#include <cstdio>
#include "../lib/typedef.h"
#include <cassert>
bool firstdig(i64 i1, i64 i2){
    while(i1>10){
        i1/=10;
    }
    while(i2 > 10){
        i2/=10;
    }
    assert(i1 != i2);
    return (i1 > i2);
}
void span(const i64 single, const i64 nused, const i64 maxsofar, const i64 max, i64& mfinal, const vector<i64> flags, const vector<i64> flagm, const vector<i64> mult){
    for(unsigned int i= 0; i < mult.size(); ++i){
        i64 value = mult[i]; 
        while(value){
            int res = value % 10;
            assert(flagm[res]==1);
            value /= 10;
        }
    }
    if(nused == 10){
        if(maxsofar < max) return;
        vector<i64>  fm2(flagm);
        i64 vm2 = maxsofar*single;
        while(vm2){
            i64 res = vm2 % 10;
            vm2 /= 10;
            if(fm2[res] == 0){
                fm2[res] = 1;
            }else{
                return;
            }
        }
        vm2 = maxsofar*single;
        vector<i64> m2(mult);
        m2.push_back(vm2);
        i64 tresult = 0;
        while(!m2.empty()){
            for(unsigned int j = 0; j< m2.size()-1; ++j){
                if(firstdig(m2[j], m2.back())){
                    swap(m2.back(), m2[j]);        
                }
            }
            i64 cv = m2.back();
            i64 order = 1;
            while(cv){
                order *= 10;
                cv/=10;
            }
            cv = m2.back();
            tresult = tresult * order + cv ;
            m2.pop_back();
        }
        if(tresult > mfinal){
            mfinal = tresult;
            for(unsigned int i = 0; i < mult.size();++i)
                printf("%lld  ", mult[i]);
            printf("%lld \n", vm2);
            printf("%lld\n", mfinal);
        }
        return;
    }
    for( i64 i = 0; i< static_cast<int>(flags.size()); ++i){
        if(flags[i]) continue;
        //if(maxsofar == 0 && i == 0) continue;
        vector<i64> f2(flags);
        f2[i] = 1;
        i64 mfar2 = maxsofar*10+ i;
        span(single, nused +1, mfar2, max, mfinal, f2, flagm, mult); 
        if(mfar2 > max) {
            i64 vm2 = mfar2*single;
            bool nooverlap = true;
            vector<i64> fm2(flagm);
            while(vm2){
                i64 res = vm2 % 10;
                vm2 /= 10;
                if(fm2[res] == 0){
                    fm2[res] = 1;
                }else{
                    nooverlap = false;
                    break;
                }
            }
            if(nooverlap){
                vector<i64> m2(mult);
                vm2 = mfar2*single;
                m2.push_back(vm2);
                span(single, nused +1,   0, mfar2, mfinal, f2, fm2, m2); 
            } 
        }
    }
}
int main(){
    vector<i64> flags;
    vector<i64> flagm;
    vector<i64> mult;
    i64 max = 0;
    i64 result = 0;
    for(i64  single = 2; single<=9; ++single){
        flags.clear();    
        mult.clear();
        flags.resize(10,0);
        flagm.resize(10,0);
        flags[single] = 1;
        span(single, 1, 0, max, result, flags, flagm, mult);
    }
    //printf("%lld\n", result);
}
