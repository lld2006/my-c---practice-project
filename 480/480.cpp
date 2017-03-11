#include <algorithm>
#include <cstdio>
#include <string>
#include <map>
#include "../lib/tools.h"
using namespace std;
//missed one important info letters should be le 15
vector<i64> vfac;
map<string, i64> strNumberMap;
map<char, int> mCount;
map<char, int> charIndex;
vector<char> vchars; //used to access all chars available
vector<i64> vall; //all strings up to x*
i64 strNumber( string str);
i64 position(const string & str);
//need to form a nLetter word, which can be constructed by n1 1 letters and other letters
i64 numberOfWords(int nLetter, int n1, int index, i64 prod, const vector<int>& nmult)
{
    if(nLetter == 0) return prod;
    if(index == (int)nmult.size()-1){
        //speed up a little bit
        if(nmult[index] >= nLetter){
            assert(prod && (prod % vfac[nLetter] == 0));
            return prod/vfac[nLetter];
        }else
            return 0LL;
    }
    i64 sum = 0LL;
    if(index == -1){
        int nmax = n1;
        if(nLetter < n1) nmax = nLetter;
        for(int k = 0; k <= nmax; ++k){
            i64 ways = vfac[n1]/vfac[k]/vfac[n1-k];
            sum += ways * numberOfWords(nLetter-k, 0, index+1, vfac[nLetter],nmult);
        }
    }else{
        int nmax = nmult[index]< nLetter? nmult[index]:nLetter;
        for(int k = 0; k<= nmax; ++k){
            assert(prod && (prod % vfac[nLetter] == 0));
            i64 t = numberOfWords(nLetter-k, 0, index+1, prod/vfac[k], nmult);
            sum += t;
        }
    }
    return sum;
}
string word(i64 pos)
{
    //I will use a stupid method, but it should not be too slow
    //based on my data structure
    assert(pos > 0);//make sure == is handled in last iteration
    string str;
    for(int ii = 0; ii<15; ++ii){
        str.append("a");
        for(unsigned int i = 0; i<vchars.size(); ++i){
            str[ii]=vchars[i];
            i64 t = position(str);
            if(t == pos) 
                return str;
            else if( t > pos){
                str[ii] = vchars[i-1];//roll back and go to next character
                break;
            }
        }
    }
    return str;
}

int cIndex(char c)
{
    auto iter = charIndex.find(c);
    assert(iter != charIndex.end());
    return iter->second;
}
i64 position(const string & str)
{
    string tstr="0";
    tstr[0]=str[0];
    int index = cIndex(str[0]); 
    i64 n0 = vall[index+1]; //accumulated numbers start from letter x
    for(unsigned int i = 1; i<str.size(); ++i){
        string s=str.substr(0, i+1);
        char c = str[i];
        index = cIndex(c);
        for(int j = index+1;j <(int)vchars.size();++j){
            s[i] = vchars[j];
            i64 npart = strNumber(s);
            n0 -= npart;
        }
    }
    i64 npart = strNumber(str);
    return n0-npart+1;
}
//how many strings start with "str"? 
//I was planning to check how many are less, but feels it is painful to
//build a huge map, so finally decide to "start with"
i64 strNumber( string str)
{
    assert(!str.empty());
    auto iter = strNumberMap.find(str);
    if(iter != strNumberMap.end()){
        return iter->second;
    }
    vector<int> mLetter;
    int n1 = 0;
    for(auto iter = mCount.begin(); iter != mCount.end(); ++iter){
        int val = count(str.begin(), str.end(), iter->first);
        i64 n = iter->second - val;
        if(n < 0)
            return 0;
        else if(n == 0) 
            continue;
        else if(n==1) 
            ++n1;
        else
            mLetter.push_back(n);
    }
    i64 val = 0;
    for(int n = str.size(); n <=15; ++n){
        i64 t = numberOfWords(n-str.size(), n1, -1, vfac[n-str.size()], mLetter);
        val += t;
    }
    strNumberMap[str] = val;
    return val;
}
int main()
{
    string s("thereisasyetinsufficientdataforameaningfulanswer");
    int cCount = 0;
    for(unsigned int i = 0; i < 26; ++i){
        char c = 'a'+i;
        int n = count(s.begin(), s.end(), c);
        if(n > 0){
            mCount.insert(pair<char, int>(c, n));
            charIndex.insert(pair<char, int>(c, cCount++));
            vchars.push_back(c);
        }
    }
    printf("%zu %zu\n", mCount.size(), s.size());
    vfac.resize(16, 1);
    i64 prod = 1;
    for(i64 k = 2; k< (int)vfac.size(); ++k){
        prod *= k;
        vfac[k] = prod;
    }
    string str = "0";
    i64 val = 0;
    vall.push_back(0);
    for(auto iter = mCount.begin(); iter!=mCount.end(); ++iter){
        str[0]=iter->first;
        val += strNumber(str);
        vall.push_back(val);
    }
    i64 pos = position(string("legionary"));
    printf("%zu\n", strNumberMap.size());
    pos += position(string("calorimeters"));
    printf("%zu\n", strNumberMap.size());
    pos -= position(string("annihilate"));
    printf("%zu\n", strNumberMap.size());
    pos += position(string("orchestrated"));
    printf("%zu\n", strNumberMap.size());
    pos -= position(string("fluttering"));
    printf("%zu\n", strNumberMap.size());
    printf("%lld %e\n", pos, (float)pos);
    printf("%s\n", word(pos).c_str());
}
