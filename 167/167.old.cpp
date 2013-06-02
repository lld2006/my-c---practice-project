#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include "../lib/typedef.h"
//a serious problem with current algo, ftable contains some 
//unnecessary info. now start with a completely new ftable
//one big mistake is that I start from index 0 not 1
void create_ulam_table(vector<i64>& vnu, unsigned int limit)
{
    vnu.reserve(limit+1);
    vector<short> ftable;
    ftable.resize(1000, 0);
    ftable[vnu[0]]=2;
    ftable[vnu[1]]=2;
    //find even number that is great than 2
    for(unsigned int i = 1; i < 100; ++i){//each time get one number
        assert(i == vnu.size() - 1);
        for(unsigned int j = 0; j < i; ++j){
            i64 index = vnu[i] + vnu[j];
            assert(index < static_cast<int>(ftable.size()));
            ++ftable[index];
        }
        int next = 0;
        for(unsigned int k = vnu[i]+1; k< ftable.size(); ++k){
            assert(k < ftable.size());
            if( ftable[k] == 1){
                next = k;
                ftable[k] = 2;
                break;
            }
        } 
        vnu.push_back(next);
        if(next %2 == 0) break;
    }
    //find two even numbers
    vector<int> even;
    even.push_back(2);
    for(unsigned int i = 1; i < vnu.size(); ++i){
        if(vnu[i] % 2 ==0){
            even.push_back(vnu[i]);
            //printf("even found index is %d value is %lld\n", i, vnu[i]);
        }
    }
    assert(even.size() == 2);
    //now we just need odd + even;
    ftable.clear();
    ftable.resize(10*limit, 0);
    
    for(unsigned int i = 0; i < vnu.size(); ++i)
        for(unsigned int j =i+1; j < vnu.size(); ++j){
            int index = vnu[i] + vnu[j];
            if(index <= vnu.back() || index % 2 == 0)
                continue;
            else
                ++ftable[index];
        }
    // ftable now created
    // first find the next one to vnu, pushback;
    // then update ftable
    
    int istart = vnu.size() - 1;
    for(unsigned int i = istart; i<=limit; ++i){
        assert(i == vnu.size() - 1);
        int next = 0;
        for(unsigned int k = vnu[i]+1; k< ftable.size(); ++k){
            assert(k < ftable.size());
            if( ftable[k] == 1){
                next = k;
                ftable[k] = 2;
                break;
            }
        } 
        vnu.push_back(next);
        for(unsigned int j = 0; j < 2; ++j){
            i64 index = vnu.back() + even[j];
            assert(index < static_cast<int>(ftable.size()));
            ++ftable[index];
        }
    }
    if(vnu[1] == 5){
        for(unsigned int i = 0; ; ++i){
            if(vnu[i] < 150)
                printf("%d %d\n", i, vnu[i]);
            else
                break;
        }
    }
}

int main()
{
    i64 nt = 100000000000LL-1;
    //nt = 100-1;
    vector<i64> vperiods;
    vector<i64> vspans;
    vperiods.push_back(32);
    vperiods.push_back(26);
    vperiods.push_back(444);
    vperiods.push_back(1628);
    vperiods.push_back(5906);
    vperiods.push_back(80);
    vperiods.push_back(126960);
    vperiods.push_back(380882);
    vperiods.push_back(2097152);

    vspans.push_back(126);
    vspans.push_back(126);
    vspans.push_back(1778);
    vspans.push_back(6510);
    vspans.push_back(23622);
    vspans.push_back(510);
    vspans.push_back(507842);
    vspans.push_back(1523526);
    vspans.push_back(8388606);
    for(unsigned int i = 0; i< vperiods.size(); ++i)
        printf("%d %lld\n", 2*i+5, nt%vperiods[i]);

    i64 sum = 0;
    for(unsigned int a = 5; a< 23; a +=2) {
        vector<i64> vnu;
        vnu.push_back(2);
        vnu.push_back(a);
        int xp = (a-5)/2;
        i64 value = nt % vperiods[xp];
        i64 value1 = value;
            value1 = 6000000;
        create_ulam_table(vnu, value1);

        i64 mult = nt /vperiods[xp];
        assert(value+vperiods[xp] < static_cast<int>(vnu.size()));
        while(vnu[value] +vspans[xp] != vnu[value+vperiods[xp]]){
            value += vperiods[xp];
            --mult;
            assert(value+vperiods[xp] < static_cast<int>(vnu.size()));
        }
        assert(value + mult * vperiods[xp] == nt);
        i64 vx = mult*vspans[xp] + vnu[value];
        printf("%d %lld\n",a, vx);
        sum += vx;
    }
    printf("%lld\n", sum);
    return 0;
}
