#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <map>
#include <algorithm>
#include "../lib/typedef.h"
using namespace std;

//need to write code using zero-suppressed decision diagram (ZDD)
//let us use a trick since the answer is unqiue, when number of
//correct guess exceed the limit, stop. if two guess have the same pattern, stop.

unsigned int nn , ng; //in c++, static in class is better
vector<int> vguess, vcorrect; //guess and number of correct guesses

vector<int> vector_sum(const vector<int>& va, const vector<int>& vb){
    assert(va.size() == vb.size());
    vector<int> result;
    result.resize(va.size(), 0);
    for(unsigned int i = 0; i < va.size(); ++i )
        result[i] = va[i] + vb[i];
    return result;
}

bool vless_or_equal(const vector<int>& va, const vector<int>& vb){
    assert(va.size() == vb.size());
    for(unsigned int i = 0; i < va.size(); ++i){
        if(va[i] > vb[i])
            return false;
    }
    return true;
}

class vectorless{
public:
    bool operator() (const vector<int>& va, const vector<int>& vb){
        assert(va.size() == vb.size());
        for(unsigned int i = 0; i < va.size(); ++i){
            if(va[i] < vb[i])
                return true;
            else if( va[i] > vb[i])
                return false;
        }
        //all equal
        return false;
    }
};

map<vector<int>, int, vectorless> statmap;

class treenode{
public: void setstop(){ stop = true; flag.clear();}
        void setvalue(int val){value = val;}
        void setparent(int index){parent = index;};
        const vector<int>& get_vector() {return flag;}
        int get_value(){return value;}
        int get_parent(){return parent;}
        bool get_stop(){return stop;}
        treenode(int pindex, int val, vector<int> vf): parent(pindex)
                                                      ,value(val)
                                                      ,stop(false)
                                                      ,flag(vf)
        { }
        treenode(){
            parent = -1;
            value = 0;
            stop = false;
            flag.resize(ng, 0);
        }
private:
    int parent; //index of parent
    int value;
    bool stop;
    vector<int> flag; //# of correct for all guess,
};

int main(){
    // start reading data
   FILE* fp;
   fp = fopen("mind16.txt", "r");
   fscanf(fp, "%d %d", &nn, &ng );
   vector<int> vstat, veff, vcolflag;
   vector<vector<int> > vnumber;
   i64 nx;
   vguess.resize(nn*ng); // all guesses
   vcorrect.resize(ng, 0);
   for(unsigned int i = 0; i < ng; ++i){
    int nc=0;
    fscanf(fp, "%lld %d", &nx, &nc);
    vector<int> nt;
    vcorrect[i] = nc;
    nt.resize(nn, 0);
    int start = 0;
    while(nx){
        int nres = nx%10;
        nt[start++] = nres;
        nx /= 10;
    }
    reverse(nt.begin(), nt.end());
    copy(nt.begin(), nt.end(), vguess.begin()+i*nn);
   }
   fclose(fp);
    //data reading end
    vector<vector<treenode> > tree;
    tree.resize(nn+1);
    tree[0].resize(1);
    for(unsigned int level = 1; level <= nn; ++level){
        statmap.clear();
        vector<treenode>& parent(tree[level-1]);

        vector<treenode>& child(tree[level]);
        vector<vector<int> > vcol;
        vcol.resize(10);
        for(unsigned int i = 0; i < 10; ++i){
            vcol[i].resize(ng, 0);
        }
        for(unsigned int ngi = 0; ngi < ng; ++ngi){
            int index = nn * ngi + level - 1;
            int value = vguess[index];
            vcol[value][ngi] = 1;
        }
        child.reserve(parent.size()*10);
        for(unsigned int nodei = 0; nodei < parent.size(); ++nodei){
            if(parent[nodei].get_stop())
                continue;
            int start = (level == 1?1:0);
            for(unsigned num = start; num <= 9; ++num){
                vector<int> tp = vector_sum(parent[nodei].get_vector(), vcol[num] );
                if(vless_or_equal(tp, vcorrect)){
                    typedef map<vector<int>, int, vectorless>::iterator mapiter;
                    pair<mapiter, mapiter> ret;
                    ret = statmap.equal_range(tp);
                    if(ret.first == ret.second){
                        child.push_back(treenode(nodei, num, tp));
                        statmap.insert(pair<vector<int>, int>(tp, child.size()-1));
                    }else{
                        child[ret.first->second].setstop();
                    }
                }
            }
        }
        printf("%d\n", static_cast<int>(child.size()));
    }
    int level = nn;
    int index = 0;
    while(level >= 1){
        printf("%d", tree[level][index].get_value());
        index = tree[level][index].get_parent();
        --level;
    }
    printf("\n");
}
