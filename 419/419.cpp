#include <cstdio>
#include "../lib/tools.h"
#include <string>
#include <map>
#include <set>
//no clue yet, need to try some small case to see if
//any pattern exists. This is routine work for PE problems.
//after investigate the first several numbers, it is clear that 
//this problem is about states and transitions, althought it is 
//still not very easy, but doable!
//now the problem is how to define a state?
//
#define DEBUG
#ifdef DEBUG
int findStates(const string& str)
{
    set<string> states;
    assert(!str.empty());
    int cp=0, np=0;//position
    char c = str[0];
    while (np != (int)str.size() && str[np] == c){
        ++np;
        //++ccnt;
    }
    string state;
    while (np != (int)str.size()){
        state.append(string(c, np-cp));
        int n0 = c - '0';
        cp = np; c = str[np];
        while (np != (int)str.size() && str[np++] == c);
        if(np - cp == n0)//state not end
            state.append(string(c, np-cp));
        else{//state ended
            states.insert(state);
            state.clear();
        }
    }
    if(!state.empty())
        states.insert(state);
    printf("size is %zu\n", states.size());
    return states.size();
}
int main(int argc, char* argv[])
{
    string old("1");
    string snew;
    int nsize = 20;
    if(argc == 2)
        nsize = atol(argv[1]);
    for(int i = 1; i<= nsize; ++i){
        int nc = 0;
        int nmax = old.size() - 1;
        while(nc <= nmax){
            char c = old[nc];
            int count = 1;
            while(nc <= nmax && old[++nc] == c){
               ++count;
            }
            snew.push_back(char('0'+count));
            snew.push_back(c);
        }
        printf("%d %zu %s\n", i,snew.size(), snew.c_str());
        findStates(snew);
        snew.swap(old);
        snew.clear();
    }
}
#else
void convertString(string strIn, vector<string>& vStrOut)
{
    vector<string> vsplit;
    std::size_t pos1 = strIn.find('_');
    vsplit.push_back(strIn.substr(0, pos1));
    std::size_t pos2 = strIn.find('_', pos1+1);
    vsplit.push_back(strIn.substr(pos1+1, pos2-pos1-1));
    vsplit.push_back(strIn.substr(pos2+1));
    //now convert the string to new state 
    //need to handle the empty string!
    vector<string>& vNewStr(vStrOut);
    //vector<char> 
    for(unsigned int i = 0; i < vsplit.size(); ++i){
        if(vsplit[i].empty()){
            vNewStr.push_back(vsplit[i]);
            continue;
        }
        char c = vsplit[i][0];
        for(unsigned int j = 0; j < vsplit[i].size(); ++j){
            assert(c == vsplit[i][j]);
        }
        string ts = string(1, (char)vsplit[i].size()+'0') + string(1, c);
        vNewStr.push_back(ts);
    }
    //need to figure out how many new states are created!
}
int main()
{
    //create all components;
    vector<string> vchars;
    for(unsigned int i = 1; i<=3; ++i){
        for(unsigned int n = 1; n <=3; ++n){
            if(i==3 && n ==3 ) continue;
            string ts(n, (char)'0'+i);
            vchars.push_back(ts);
        }
    }
    vchars.push_back("");
    //now let me create states
    vector<string> vstates;
    map<string, int> indexMap;
    for(unsigned int i = 0; i < vchars.size(); ++i){
        for(unsigned int j = 0; j < vchars.size(); ++j){
            if((j == i) || (vchars[j].empty())) continue;
            for(unsigned int k = 0; k < vchars.size(); ++k){
                if(k==j) continue;
                string state = vchars[i] + "_"+vchars[j] +"_"+ vchars[k];
                vstates.push_back(state);
                indexMap.insert(pair<string, int>(state, vstates.size()-1));
            }
        }
    }
    printf("chars %zu number of states is %zu\n", vchars.size(), vstates.size());
    vector<string> vresults;
    for(unsigned int i = 0; i < vstates.size(); ++i){
        convertString(vstates[i], vresults);
    }
}
#endif
