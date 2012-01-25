#include <tr1/unordered_map>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <string>
#include "../lib/typedef.h"
using namespace std;
//using std::tr1::unordered_map;

//need to write code using zero-suppressed decision diagram (ZDD)
//let us use a trick since the answer is unqiue, when number of 
//correct guess exceed the limit, stop. if two guess have the same pattern, stop.

unsigned int nn , ng; //in c++, static in class is better
vector<int> vguess; //guess and number of correct guesses
string vcorrect;
vector<int> selected;
typedef std::tr1::unordered_map<std::string, int> hashmap;

string string_sum(const string& va, const string& vb){//special version not applicable for general 
    // purpose vb is string of 0 1
    assert(va.size() == vb.size());
    string result;
    result.resize(va.size(), '0');
    for(unsigned int i = 0; i < va.size(); ++i ){
        assert(vb[i]=='1' || vb[i] =='0');
        result[i] = (vb[i]=='1'?va[i]+1:va[i]);
    }
    return result;
}

int same_digits(const int a, const int b){
    int cnt = 0;
    int indexa = a *nn;
    int indexb = b *nn;
    for(unsigned int i = 0; i < nn; ++i)
        if(vguess[indexa++] == vguess[indexb++])
            ++cnt;
    return cnt;
}

//less or equal than the constrain
bool string_less(const string& sa, const string & sb){
    assert(sa.size() == sb.size());
    for(unsigned int i = 0; i < sa.size(); ++i)
        if(sa[i] > sb[i]) 
            return false;
    return true;
}

hashmap statmap;

class treenode{
public: void setstop(){ stop = true; flag.clear();}
        void setvalue(int val){value = val;}
        void setparent(int index){parent = index;};
        const string& get_vector() {return flag;}
        int  get_value(){return value;}
        int  get_parent(){return parent;}
        bool get_stop(){return stop;}
        treenode(int pindex, int val, const string& vf): parent(pindex)
                                                      ,value(val) 
                                                      ,stop(false)
                                                      ,flag(vf)
        { }
        treenode(){
            parent = -1;
            value = 0;
            stop = false;
            flag.resize(ng, '0');
        }
private:
    int parent; //index of parent
    int value;
    bool stop;
    string flag; //# of correct for all guess, 
};

int select_next_col(vector<treenode>& parent, const vector<vector<std::string> >& v_level_col)
{
    hashmap stat;
    i64 min_branch = 1000000000000, total;
    int col_sel = -1;
    for(unsigned int col = 1; col < selected.size(); ++col){
        stat.clear();
        if(!selected[col]){
            int nrmv = 0;
            int start = (col == 1? 1 : 0);
            int nsel = 10 -start;
            total = parent.size()*nsel;
            for(unsigned int nodei = 0; nodei < parent.size(); ++nodei){
                if(parent[nodei].get_stop()){
                    total -= nsel;
                    continue;
                }
                for(unsigned int num = start; num <= 9; ++num){
                    string tp = string_sum(parent[nodei].get_vector(), v_level_col[col][num]);
                    if(string_less(tp, vcorrect)){
                        hashmap::iterator iter = stat.find(tp);
                        if(iter == stat.end()){
                            stat.insert(pair<string, int>(tp, 0));
                        }else{
                            ++nrmv;
                        }
                    }
                }
            }
            assert( nrmv < total);
            if(total - nrmv < min_branch){
                min_branch = total - nrmv;
                col_sel = col;
            }
        }
    }
    assert(col_sel >= 0);
    return col_sel;    
}

int main(){
    // start reading data
   FILE* fp;
   fp = fopen("mind16.txt", "r");
   fscanf(fp, "%d %d", &nn, &ng );
   i64 nx;
   vguess.resize(nn*ng); // all guesses
   vcorrect.resize(ng, 0);
   for(unsigned int i = 0; i < ng; ++i){
    char nc='0';
    fscanf(fp, "%lld %c", &nx, &nc);
    vector<int> nt;//temporaray vector
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
   //statistics about all guesses
   //for(unsigned int i = 0 ; i < ng  -1; ++i)
   //    for(unsigned int j = i+1; j < ng; ++j){
   //         int isame = same_digits(i, j);
   //         printf("%d %d %d\n", i, j, isame);
   //    }
   //exit(0);
    //data reading end
    vector<vector<treenode> > tree;
    selected.resize(nn+1, 0);
    tree.resize(nn+1);
    tree[0].resize(1);
    //gather levelized correct guess info.
    vector<vector<std::string> > v_level_col;
    v_level_col.resize(nn+1); //0th level is ignored
    for(unsigned int leveli = 1; leveli <= nn; ++leveli){
        v_level_col[leveli].resize(10);
        for(unsigned int i = 0; i < 10; ++i)
            v_level_col[leveli][i].resize(ng, '0');
        for(unsigned int ngi = 0; ngi < ng; ++ngi){
            int index = nn * ngi + leveli - 1;
            int value = vguess[index];
            v_level_col[leveli][value][ngi] = '1';
        }
    }
    //start levelized tree
    for(unsigned int level = 1; level <= nn;  ++level){
        statmap.clear();
        vector<treenode>& parent(tree[level-1]);
        vector<treenode>& child(tree[level]);
        
        int col = select_next_col(parent, v_level_col);
        selected[col] = 1;
        child.reserve(parent.size()*10);
        for(unsigned int nodei = 0; nodei < parent.size(); ++nodei){
            if(parent[nodei].get_stop())
                continue;
            int start = (col == 1?1:0);
            for(unsigned num = start; num <= 9; ++num){
                string tp = string_sum(parent[nodei].get_vector(), v_level_col[col][num]);
                if(string_less(tp, vcorrect)){
                    hashmap::iterator iter = statmap.find(tp);
                    if(iter == statmap.end()){
                        child.push_back(treenode(nodei, num, tp));
                        statmap.insert(pair<string, int>(tp, child.size()-1));
                    }else{
                        child[iter->second].setstop();
                    }
                }
            }
        }
        printf("col %d size %d\n", col, static_cast<int>(child.size()));
    }
    int level = nn;
    int index = 0;
    int count = 0;
    for(unsigned int i = 0; i < tree[level].size(); ++i){
        if(tree[level][i].get_stop())
            continue;
        if(tree[level][i].get_vector() != vcorrect)
            continue;
        else{
            ++count;
            index = i;
        }
    }
    assert(count == 1);
    while(level >= 1){
        printf("%d", tree[level][index].get_value());
        index = tree[level][index].get_parent();
        --level;
    }
    printf("\n");
}
