#include <cstdio>
#include <unordered_set>
#include <vector>
using namespace std;

int limit = 1000000;
int mark_numbers(int num, vector<int>& flags, vector<int>& vn, int& level,
       unordered_set<int>& hashset )
{
    if(flags[num] >= 0 || vn[num] > limit){ //the behavior of this number clear, stop.
        return 0;
    } 

    if(hashset.find(num) != hashset.end()){
        level = 0;
        return num;
    }

    hashset.insert(num);
    int value = mark_numbers(vn[num], flags, vn, level, hashset);
    //now we know how the chain ended;
    if(value == num) {
        flags[num] = ++level;
    }else{
        flags[num] = 0;
        ++level;
    }
    return value;
}
int main()
{
    vector<int> vn;
    vn.resize(limit+1, 1);
    vn[0] = 0;
    for( int i =2; i <= limit/2; ++i){
        int nx = i;
        for(unsigned int j = 2*nx; j < vn.size(); j+=nx){
            vn[j] += nx;
        }
    }
    vector<int> flags;//this vector is used to find those numbers 
    //that return to itself
    flags.resize(limit+1, -1);//-1 means uninitialized
    for(unsigned int i = 2; i <vn.size(); ++i ){
        unordered_set<int> hashset;
        int level = 0;
        mark_numbers(i,flags, vn, level, hashset);
    }
    int chain_length = 0;
    int maxi = 0;
    for(unsigned int i = 1; i < flags.size(); ++i){
        if(flags[i] > chain_length){
            chain_length = flags[i];
            maxi = i;
        }
    }
    printf("value is %d length is %d\n", maxi, chain_length);
}
