#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cassert>
#include "../lib/tools.h"
#include <cstdlib>
//#include <boost::lexical_cast>
using namespace std;

typedef multimap<string, string>::iterator mmiter;
//int distinct (int num){
//    vector<int> flag;
//    flag.resize(10 , 0);
//    while(num ){
//        int res = num % 10;
//        num /= 10;
//        if(flag[res] == 0)
//            flag[res] = 1;
//        else
//            return 0;
//    }
//    return 1;
//}
int main(){
    int maxsize = 5;
    multimap<string, string> wordmap;
    FILE* fp;
    fp = fopen("words.txt", "r");
    char buf[256] ;
    unsigned int cmax=0;
    string sm1, sm2;
    while(fscanf(fp, "%s", buf) == 1){
        string st(buf);
        string st2(buf);
        if(st.size() == 1) continue;
        sort(st2.begin(), st2.end());
        wordmap.insert(make_pair(st2, st));
    }
    fclose(fp);
    for(mmiter iter = wordmap.begin();
        iter != wordmap.end(); ){
        string st(iter->first);
        int num = wordmap.count(st);
        if(num > 1){ 
            pair<mmiter, mmiter> eq = wordmap.equal_range(st);
            iter = eq.second;
            if(st.size()== maxsize){
                for(mmiter m1 = eq.first; m1 != eq.second; ++m1)
                printf("%s\n", m1->second.c_str());
                mmiter m1 = eq.first; 
                sm1 = (m1++)->second;
                sm2 = m1->second;
            }
            if(st.size() > cmax){
                cmax = st.size();
            }
        }
        else{
            wordmap.erase(iter++);
        }
    }
    //printf("%s %s\n", sm1.c_str(), sm2.c_str());
    for (mmiter iter = wordmap.begin(); iter != wordmap.end(); ++iter){
        if(iter->first.size()!=maxsize) continue;
        string st = iter->first;
        pair<mmiter, mmiter> eq = wordmap.equal_range(st);
        sm1 = eq.first->second;
        sm2 = (++eq.first)->second;
        vector<int> strmap;
        int sf = -1;
        st = sm2;
        for(unsigned int i = 0; i < sm1.size(); ++i){
            if((sf = st.find(sm1[i]))==string::npos)
                assert(0);
            else{
                st[sf] = 1;
                strmap.push_back(sf);
            }
        }

        vector<int> square;
        //int x0 = pow(10, maxsize);
        //double x1 = sqrt()
        for(int i = 100; i<= 316;++i){
            int isq = i * i;
            square.push_back(isq);
        }

        for(unsigned int i = 0; i < square.size(); ++i){
            int base = 10;
            int value = square[i];
            int sum = 0;
            int pos = maxsize-1;
                //assert(value > 100000 && value <999999);
            vector<int> vflag;
            vflag.resize(maxsize, 0);
            while(value){
                int v = value % base;
                vflag[maxsize-1-pos]=v;
                value /= 10;
                sum += v * power(base, maxsize-1-strmap[pos--]);
            }
            bool flag =true;
            for(int i1 = 0; i1 < maxsize; ++i1){
                for(int j1 =0; j1 < maxsize; ++j1){
                    if(sm1[i1]==sm1[j1] && vflag[i1] == vflag[j1])continue;
                    if(sm1[i1]!=sm1[j1] && vflag[i1] != vflag[j1])continue;
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;
            for(unsigned int j = 0; j< square.size();++j){
                if(sum == square[j] &&square[i] != square[j]){
                    printf("%s %s\n", sm1.c_str(), sm2.c_str());
                    printf("%d %d\n", square[i], square[j]);
                }
            }
        }
    }
}
