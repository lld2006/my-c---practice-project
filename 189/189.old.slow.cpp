#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
//OK, let us say two different type of triangles: normal and reversed.
//normal has 8 rows and reversed has 7 rows. 
//so we will loop each rows from 1 to 7. then the eigth row only need
//a count
//each color are labeled as 1 2 3;
//lesson 1, need to set value before recursive calls. I defered the set value to 
//next_config, which is totally wrong.
//lesson 2, sometimes the original definition of some vector might have changed,
//it would be wise to give some comment to each of the key variables 
//vectors some comments
//this is a bad approach the time taken is almost days, we need to use dynamic programming
//for better performance 
vector<vector<int> > normal, reversed;// curr index of each level, constrained by index vector
vector<vector<int> > norval, revval; //  setting value of each level;
vector<vector<int> > cand;
unsigned int level_max = 6;
i64 fill_reversed(unsigned level);
bool next_config(int level, vector<int>& vindex, bool is_normal)
{
    int carry = 0;//if the last one still has carry_over, return false;
    vector<int>& cfg = is_normal? normal[level]:reversed[level];
    unsigned int ni = 0;
    do{
        if(ni == cfg.size())
            break;
        ++cfg[ni];
        if(cfg[ni] == static_cast<int>(cand[vindex[ni]].size())){
            cfg[ni] = 0; 
            carry = 1;
            ++ni;
        }else{
            carry = 0;
        }
    }while(carry);
    return !carry;
}
i64 fill_normal(unsigned level)
{
    i64 sum = 0;
    if(level == level_max){
        i64 result = 4; 
        for(unsigned int i = 1; i < level - 1; ++i)
            if(revval[level-1][i- 1] == revval[level-1][i])
                result *= 2;
        return result; //TODO
    }
    vector<int> cand_index;
    cand_index.resize(level); //vector index for ith triangle in this level
    assert(reversed[level-1].size()==level-1);
    cand_index[0]       = 7 ^ revval[level-1][0];
    cand_index[level-1] = 7 ^ revval[level-1][level-2];
    for(unsigned int i = 1; i < level - 1; ++i){
        if(revval[level-1][i-1] == revval[level-1][i]){ // two colors are identical
            cand_index[i] = 7 ^ revval[level-1][i-1];
        }else{//two different colors
            int index = 7;
            index ^= revval[level-1][i-1];
            index ^= revval[level-1][i];
            cand_index[i] = index;
        }
    }

    do{
        //set norval vector;
        for(unsigned int i = 0; i < normal[level].size(); ++i){
            vector<int>& candvec = cand[cand_index[i]];
            int index = normal[level][i];
            norval[level][i] = candvec[index];
        }
        sum += fill_reversed(level);
    }while(next_config(level, cand_index, true));

    return sum;
}
i64 fill_reversed(unsigned int level)
{
    int sum = 0;
    vector<int> cand_index;
    cand_index.resize(level);
    for(unsigned int i = 0; i < level; ++i)
        cand_index[i] = 7 ^ norval[level][i];
    do{
        //set revval vector;
        for(unsigned int i = 0; i < reversed[level].size(); ++i){
            vector<int>& candvec = cand[cand_index[i]];
            revval[level][i] = candvec[reversed[level][i]];
        }
        sum += fill_normal(level+1);
    }while(next_config(level, cand_index, false));
    return sum;
}
int main()
{
    normal.resize(8); reversed.resize(8); //level 0 will not be used
    norval.resize(8); revval.resize(8); //level 0 will not be used
    cand.resize(7);
    cand[1].push_back(1); 
    cand[2].push_back(2); 
    cand[3].push_back(1); cand[3].push_back(2);
    cand[4].push_back(4); 
    cand[5].push_back(1); cand[5].push_back(4);
    cand[6].push_back(2); cand[6].push_back(4);
    //0 is not used 7 never to happen; 
    for(unsigned int i = 1; i <= 7; ++i){
        norval[i].resize(i, 0); normal[i].resize(i, 0);
        revval[i].resize(i, 0); reversed[i].resize(i, 0);
    }
    //final result should be multiplied by 6
    norval[1][0]=1;
    revval[1][0]=2;
    i64 sum = fill_normal(2);
    printf("%lld\n", sum*6);
}
