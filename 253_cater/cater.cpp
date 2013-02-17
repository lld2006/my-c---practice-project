#include <map>
#include <bitset>
#include <vector>
#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

//the simple idea is to create a vector and max segment so far 
//as the key The vector contains the number for each consecutive empty 
//pieces. The segment at the boundaries are not changable. We can 
//sort those in the middles so to reduce the number of different situations.
//store all these stuffs in a map. and evolve from one piece to 40. It is 
//solved. My code run 16 seconds. There is a much better solution in the 
//solution thread.
const int pieces = 40;
const int nbits = 6; //up to 63
const int bsize = nbits*(pieces/2+2); //pieces/2+2 for bits 
const int nsize = bsize/nbits;

void set_bits(bitset<bsize>& vbit, int idx, int value);

vector<double> vfact;
double result = 0.0;
bool debug= false;

struct caterpillar
{
    caterpillar(vector<short>& vn, int m0):vnum(vn), nmax(m0)
    {
        //TODO
    }
    //bitset<bsize> bitstr; //bit string
    vector<short> vnum;
    short nmax; //maximum segment seen so far
};


bool operator< (const caterpillar& c1, const caterpillar& c2)
{
    if(c1.nmax< c2.nmax)
        return true;
    else if(c2.nmax < c1.nmax)
        return false;
    else{
        const vector<short>& v1(c1.vnum);
        const vector<short>& v2(c2.vnum);
        if(v1.size() < v2.size()){
            return true; 
        }else if(v1.size()>v2.size()){
            return false;
        }else{
            for(unsigned int i = 0; i < v1.size(); ++i)
                if(v1[i]<v2[i])
                    return true;
                else if (v1[i]>v2[i])
                    return false;
        }
    }
    return false;
}
bool operator== (const caterpillar& c1, const caterpillar& c2)
{
    if(c1.nmax == c2.nmax && c1.vnum.size()==c2.vnum.size() && c1.vnum == c2.vnum)
        return true;
    return false;
}

void insert_or_update(map<caterpillar, double>& cmap, const caterpillar& cater, double weight)
{
    map<caterpillar,double>::iterator iter = cmap.lower_bound(cater);
    //lesson 4, the insertion criteria need an ==op, less op is not right
    //lesson 5 the criteria forgot iter == end
    if(iter== cmap.end() || !(iter->first == cater))
        cmap.insert(iter, make_pair(cater, weight));
    else{
        (iter->second) += weight;
    }
}
void process_cfg(pair<caterpillar, double>& p1, map<caterpillar,double>& newcmap)
{
    const vector<short>& vn(p1.first.vnum);
    assert(!vn.empty());

    for(unsigned int i = 0; i < vn.size(); ++i){
        assert(vn[i] > 0);
        if(vn[i]==63){
            assert(i==0||i==vn.size()-1);
            continue;
        }

        if(vn[i]==1){
            //at the border size 1 means make up a symbol
            vector<short> vn1(vn);
            if(i==0||i==vn.size()-1){
                vn1[i] = 63;
                assert(vn.size()>1);
                insert_or_update(newcmap,caterpillar(vn1, p1.first.nmax),p1.second);
            }else{
                //in the middle means this empty space disappeared
                swap(vn1[i], vn1.back());
                vn1.pop_back();
                insert_or_update(newcmap,caterpillar(vn1, p1.first.nmax),p1.second);
            }
        }else if (i==0){
        //now it is an empty sapce with size >= 2
            //0 boundary
            vector<short> vn1(vn);
            vn1[0] = 63;
            vn1.push_back(vn[0]-1);
            assert(vn[0]!=1);
            int currmax = p1.first.nmax == static_cast<int>(vn.size())-1? p1.first.nmax+1:p1.first.nmax;
            insert_or_update(newcmap, caterpillar(vn1,currmax), p1.second);

            // the other side
            vn1 = vn;
            if(i != vn.size()-1){
                --vn1[i];
                insert_or_update(newcmap, caterpillar(vn1, p1.first.nmax), p1.second);
            }else{//only one segment
                assert(0);
                --vn1[i];
                vn1.push_back(63);
                insert_or_update(newcmap, caterpillar(vn1,p1.first.nmax+1),p1.second);
            }
            
            vn1=vn;
            vn1.push_back(0);
            for(int j = 1; j< vn[i]-1;++j){
                newbits = cater.bitstr;
                split_bits(newbits, i, j, vn[i]-j-1);        
                int currmax = cater.nmax == cater.ncurr? cater.nmax+1:cater.nmax;
                insert_or_update(newcmap, caterpillar(newbits,currmax, cater.weight,  cater.ncurr+1 ));
            }
        }else if(i==vn.size()-1){
            //boundary end 
            newbits = cater.bitstr;
            split_bits(newbits, i, vn[i]-1, 63);
            int currmax = cater.nmax == cater.ncurr? cater.nmax+1:cater.nmax;
            insert_or_update(newcmap, caterpillar(newbits,currmax, cater.weight,  cater.ncurr+1 ));

            //the other end
            newbits = cater.bitstr;
            assert(i > 0);
            set_bits(newbits, i, vn[i]-1);
            insert_or_update(newcmap, caterpillar(newbits, cater.nmax,cater.weight,  cater.ncurr ));

            for(int j = 1; j < vn[i]-1; ++j){
                newbits = cater.bitstr;
                split_bits(newbits, i, j, vn[i]-j-1);
                int currmax = cater.nmax == cater.ncurr? cater.nmax+1:cater.nmax;
                insert_or_update(newcmap, caterpillar(newbits, currmax,cater.weight,  cater.ncurr+1 ));
            }
        }else{
            newbits = cater.bitstr;
            set_bits(newbits, i, vn[i]-1); // this should be multiplied by two
            insert_or_update(newcmap, caterpillar(newbits, cater.nmax, cater.weight*2,  cater.ncurr ));
            //in the middle
            for(int j = 1; j < vn[i]-1; ++j){
                newbits = cater.bitstr;
                split_bits(newbits, i, j, vn[i]-j-1);
                int currmax = cater.nmax == cater.ncurr? cater.nmax+1:cater.nmax;
                insert_or_update(newcmap, caterpillar(newbits,currmax, cater.weight,  cater.ncurr+1 ));
            }
        }
    }
}
bool noNeedToContinue(vector<short> vn)
{
    assert(!vn.empty());
    int start = 0 ;
    int last = vn.size()-1;
    if(start == last)
        return vn[0] <= 1;
    if(vn[0]==63) ++start;
    if(vn[last]==63) --end;
    for(int ni = start; ni <= end; ++ni){
        if(ni==start||ni==end &&vn[ni]> 1)
            return false;
        if(vn[ni]>2)
            return false;
    }
    return true;
}
void process_level(map<pair<caterpillar, double>>& cmap, int level)
{
    map<pair<caterpillar, double>> newcmap;
    int left = pieces + 1 - level;
    for(auto iter=cmap.begin(); iter != cmap.end(); ++iter){
        vector<short>& vn(iter->first.vnum);
        if(noNeedToContinue(vn)){
            // sum up and clear from the set
            // lesson 6, weight is missed in the first version
            result += vfact[left] * iter->second*iter->first.nmax;
            continue;
        }
        process_cfg(*iter, vn, newcmap);
    }
    //lesson 2 forgot to swap newcmap and cset. 
    //The code for this problem takes too much time. I should focus on this problem on some day.
    cmap.swap(newcmap);
}
void debugset(map<caterpillar>& cmap)
{
    for(auto iter = cset.begin(); iter!=cset.end(); ++iter){
        debug_bits(iter->bitstr);
        printf("iter->nmax = %d iter->ncurr=%d weight=%f\n", iter->nmax, iter->ncurr, iter->weight);
    }
}
int main()
{
    vfact.resize(41);
    vfact[1] = 1;
    for(unsigned int i = 2; i< vfact.size(); ++i)
        vfact[i] = vfact[i-1]*i;
    
    //insert all initial 1 piece cfg 
    map<caterpillar, double> cmap;
    for(unsigned int i= 1; i<= pieces; ++i){
        vector<short> vn;
        if(i==1||i== pieces){
            vn.push_back(63);
            vn.push_back(pieces-1);
            cmap.insert(make_pair(caterpillar(vn, 1 ), 1.0));
        }else{
            vector<short> vn;
            short i0 = i < pieces/2? i:pieces -i;
            vn.push_back(i0);
            vn.push_back(pieces-i);
            cmap.insert(make_pair(caterpillar(vn, 1 ), 1.0));
        }
    }
    for(int level = 2; level <= pieces; ++level){
        printf("in level %d map size is %zu %20.10f\n", level, cmap.size(), result);
        process_level(cset, level);
    }
    
    printf("average value is %20.10f %20.10f\n", result, result/vfact[pieces]);
}
