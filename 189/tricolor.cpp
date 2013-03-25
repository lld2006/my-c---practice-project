//dynamic programming approach to figure out how many cfgs available 
//surface constrained cfgs are critical in this approach
//how to reorgnize the code for clean and easy to read and implement
#include <cstdio>
#include <cassert>
#include <map>
#include "../lib/typedef.h"
vector<vector<int> > normal, reversed;// curr index of each level, constrained by index vector
vector<vector<int> > norval, revval; //  setting value of each level;
vector<vector<int> > cand;
map<int, int> constrained_cfgs;
unsigned int level_max = 4;
i64 fill_reversed(unsigned level);
bool next_cfg(vector<int>& constrain);
int calc_ni(vector<int>& vec);
bool next_config(const vector<int>& vindex, vector<int>& cfg)
{
    int carry = 0;//if the last one still has carry_over, return false;
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
    }while(next_config(cand_index, normal[level]));

    return sum;
}
i64 fill_reversed(unsigned int level)
{
    if(level == level_max){
        i64 result = 1;
        int nt = calc_ni(norval[level_max]);
        result *= constrained_cfgs[nt];
        vector<int> vt;
        for(unsigned int i = 1; i <= level_max; ++i)
            vt.push_back(norval[i][0]);
        nt = calc_ni(vt);
        result *= constrained_cfgs[nt];
        vt.clear(); 
        for(unsigned int i = 1; i <= level_max; ++i)
            vt.push_back(norval[i].back());
        nt = calc_ni(vt);
        result *= constrained_cfgs[nt];
        return result;
    }
    i64 sum = 0;
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
    }while(next_config(cand_index, reversed[level]));
    return sum;
}
int find_constrained_cfgs(unsigned int level, const vector<int>& vcstrn)
{
    if(level == 1)
        return 2;
    
    int sum = 0;
    vector<int> cand_index, c2, vnorm, val_norm, vrev, val_rev;
    assert(vcstrn.size() == level);
    assert(level > 1);
    cand_index.resize(level, 0);
    c2.resize(level - 1, 0);
    vnorm.resize(level, 0); val_norm.resize(level, 0);
    vrev.resize(level - 1, 0); val_rev.resize(level-1, 0);
    for(unsigned int i = 0; i < level; ++i)
        cand_index[i] = 7^vcstrn[i];
    do{
       // first get the normal values in level
       for(unsigned int i = 0; i < level; ++i)
           val_norm[i] = cand[cand_index[i]][vnorm[i]];
       //then get the reversed values in level - 1;
       for(unsigned int i = 0; i < level - 1; ++i){
           if(val_norm[i] == val_norm[i+1]) 
               c2[i] = 7 ^ val_norm[i];
           else{
               c2[i] = 7 ^ val_norm[i];
               c2[i] = c2[i] ^ val_norm[i+1];
           }
       }
       do{
            for(unsigned int i = 0; i < level - 1; ++i)
               val_rev[i] = cand[c2[i]][vrev[i]];
            sum += find_constrained_cfgs( level - 1, val_rev);
       }while(next_config(c2, vrev));      // for reversed triangles
    }while(next_config(cand_index, vnorm));  // for normal triangles;
    return sum;
}
int main()
{
    normal.resize(9); reversed.resize(9); //level 0 will not be used
    norval.resize(9); revval.resize(9); //level 0 will not be used
    cand.resize(7);
    cand[1].push_back(1); 
    cand[2].push_back(2); 
    cand[3].push_back(1); cand[3].push_back(2);
    cand[4].push_back(4); 
    cand[5].push_back(1); cand[5].push_back(4);
    cand[6].push_back(2); cand[6].push_back(4);
    //0 is not used 7 never to happen; 
    for(unsigned int i = 1; i <= 8; ++i){
        norval[i].resize(i, 0); normal[i].resize(i, 0);
        revval[i].resize(i, 0); reversed[i].resize(i, 0);
    }
    //final result should be multiplied by 6
    norval[1][0]=1;
    revval[1][0]=2;
    //dynmaic programmings
    vector<int> vec_constrain;
    vec_constrain.resize(level_max, 1);
    int cnt = 0;
    int ni = 1111;
    if(level_max == 3) ni = 111;
    while(ni <= 4444){
        ++cnt;
        int ncfg = find_constrained_cfgs(level_max, vec_constrain);
        //printf("%d %d %d\n", ni, cnt, ncfg);
        constrained_cfgs.insert(pair<int, int>(ni, ncfg));
        if(!next_cfg(vec_constrain))
            break;
        ni = calc_ni(vec_constrain);
    }

    i64 sum = fill_normal(2);
    printf("%lld\n", sum*6);
}
int calc_ni(vector<int>& vec)
{
    int sum = 0; 
    for(unsigned int i = 0; i < vec.size(); ++i){
        sum *= 10;
        sum += vec[i];
    }
    return sum;
}
bool next_cfg(vector<int>& constrain)
{
    unsigned int carry = 0, ni = 0;
    do{
       if(ni == constrain.size()) break;
       carry = 0;
       if(constrain[ni] == 1){
           constrain[ni] = 2;
       } else if(constrain[ni] == 2){
           constrain[ni] = 4;
       }else{
           constrain[ni] = 1;
           carry = 1;
           ++ni;
       }
    }while(carry);
    return !carry;
}
