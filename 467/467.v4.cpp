#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include "../lib/tools.h"
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <set>
//find a huge mistake! if one is 512034045 and the other one 
//is                             5987645
//so it is better to use the second 4 instead of the first one
//so it should be 5120340987645 instead of 
//                5120398764045
// finally, I still go back to use the original string
// 0228, still need to write some more code to finish this problem
// the trickest thing is that the prime sequence do not have 9, but 
// composites have a lot of 9. which makes the search very inefficient
//===============  global variables and typedef ===================
class pairLess;
class pairLess2
{
  public:
    bool operator()(const IntPair& p1, const IntPair& p2)
    {
        return (p1.first + p1.second < p2.first + p2.second) 
            ||((p1.first+p1.second == p2.first+p2.second) && p1.first < p2.first);

    }
};
class pairLess
{
  public:
    bool operator()(const IntPair& p1, const IntPair& p2)
    {
        return (p1.first + p1.second > p2.first + p2.second) 
            ||((p1.first+p1.second == p2.first+p2.second) && p1.first < p2.first);

    }
};
typedef priority_queue<IntPair, vector<IntPair>, pairLess> tpq;
map<IntPair, string, pairLess2> vdata;  //two dimensional v[i][j]
tpq vpq;
vector<int> vpd, vcd;   //digits in each string sequence
enum state {NOHISTORY = 0, LESS=1, GREATER=2, MIXED=3, PROHIBITED=4};
vector<vector<int>> vvpn, vvcn; 
static string minStr;
vector<vector<int>> vvpnext, vvcnext;
int nmax = 100;
state mergeTwoSequence(string& nStr, int s1, int e1, int s2, int e2, bool pushLast, state oldState);
//=================================================================

void itoa(int n, char& c)
{
    assert(0<n && n<10);//for this problem only, should be >= 0
    c = '0'+n;
}

void clear_unused_map(int num)
{
    auto iter = vdata.begin();
    while(iter != vdata.end() && iter->first.first + iter->first.second < num)
        vdata.erase(iter++);
}
void insert_into_map(int x, int y, const string& str)
{
    assert(!str.empty());
    auto iter = vdata.find(IntPair(x, y));
    if(iter == vdata.end())
        vdata.insert(pair<IntPair, string>(IntPair(x, y), str));
    else
        iter->second = str;
}

/* 
string find_candidate_string(string& sharedStr)
{
    int iterP = 0; int iterC = 0;
    string finalc;
    char cp, cc, cs;
    int index = 0;
    while(iterP != (int)vpd.size() && iterC != (int)vcd.size() && index < (int)sharedStr.size()){
        cp = (char) '0'+vpd[iterP];
        cc = (char) '0'+vcd[iterC];
        cs = sharedStr[index];
        while(cp!=cs && cc !=cs){
            assert(cp != cc);
            if(cc < cp){
                finalc.push_back(cc);
                cc = '0'+vcd[++iterC];
            }else if(cp < cc){
                finalc.push_back(cp);
                cp = '0'+vpd[++iterP];
            }
        }
        while(cc!=cs){
            finalc.push_back(cc);
            cc ='0'+vcd[++iterC];
        }
        while(cp!=cs){
            finalc.push_back(cp);
            cp ='0'+vpd[++iterP];
        }
        assert('0'+vcd[iterC]==cs);
        assert('0'+vpd[iterP]==cs);
        finalc.push_back(cs); ++index; ++iterP; ++iterC;
    }
    while(iterP != (int) vpd.size() && iterC != (int)vcd.size()){
        cp = (char) '0'+vpd[iterP];
        cc = (char) '0'+vcd[iterC];
        if(cp < cc){
            finalc.push_back(cp);
            ++iterP;
        }else{
            finalc.push_back(cc);
            ++iterC;
        }
    }
    while(iterC != (int)vcd.size())finalc.push_back('0'+vcd[iterC++]);
    while(iterP != (int)vpd.size())finalc.push_back('0'+vpd[iterP++]);
    return finalc;
}
*/

void create_vvnext(vector<int>& vvnext, vector<int>& vvpn)
{
    vvnext.clear();
    vvnext.resize(nmax+1, 0);
    int curIndex = 0;
    int next = nmax+1; 
    if(!vvpn.empty()){
        next = vvpn[curIndex];
    }
    for( int j = 0; j < (int)vvnext.size(); ++j){
        if(j < next){
            vvnext[j] = next;
        }else{
            ++curIndex;
            if(curIndex ==(int)vvpn.size()){
                next = nmax+1;
            }else{
                next = vvpn[curIndex];
            }
            vvnext[j] = next;
        }
    }
}

void process_one_step(int i, IntPair p0, state s, vector<int>::iterator iter1, vector<int>::iterator iter2, bool& better, int depth)
{
    if(depth == 10000) return;
    if(s == LESS) ++iter1;
    if(s == GREATER) ++iter2;
    assert(s == LESS || s==GREATER || s==NOHISTORY);
    if(iter1== vvpn[i].end()) return; 
    if(iter2 == vvcn[i].end()) return; 
    int index1 = *iter1; //at first I tried to use distance, but it is not necessary, use iter directly
    int index2 = *iter2;
    assert(index2 > p0.second && index1 > p0.first);
    assert(vpd[index1] == vcd[index2]);
    auto oiter  = vdata.find(p0);
    auto niter  = vdata.find(IntPair(index1, index2));
    assert(oiter != vdata.end());
    string oStr = oiter->second; 
    state news;
    //int sumxy = index1+index2;
    if(niter == vdata.end()){
        news = mergeTwoSequence(oStr, p0.first+1, index1, p0.second+1, index2, true, s);
        if(news == PROHIBITED ||(s !=NOHISTORY && news == MIXED)) return; 
            vpq.push(IntPair(index1, index2));
            printf("push to pqi %d %d\n", index1, index2);
            printf("find new pair from %d %d [%d] to %d %d [%d] %s\n", p0.first, p0.second, vpd[p0.first], index1, index2, vpd[index1], oStr.c_str());
            better = true;
            insert_into_map(index1, index2, oStr);
    }else{
        oStr  = oiter->second;
        string nStr = niter->second;
        assert(!nStr.empty()); 
        news = mergeTwoSequence(oStr, p0.first+1, index1, p0.second+1, index2, true, s);
        if(news == PROHIBITED ||(s !=NOHISTORY && news == MIXED)) return; 
        if(oStr.size() > nStr.size()) return ; //better solution already exists
        if((oStr.size() < nStr.size() ||(oStr.size()==nStr.size() && oStr < nStr))){
                better = true;
                niter->second=oStr;
                printf("updated pair from %d %d [%d] to %d %d [%d]\n", p0.first, p0.second, vpd[p0.first], index1, index2, vpd[index1]);
            //}
        }
    }
    if((news == LESS || news == GREATER))
        process_one_step(i, p0, news, iter1, iter2, better, depth+1);
}

void find_minimum_string(string& sharedStr , string minStr)
{
    //let me assume a candidate string is available as minimum;
}
//need to set some flat for this function, for example
//p always less than c 1, both 0, always greater -1
state mergeTwoSequence(string& nStr, int s1, int e1, int s2, int e2, bool pushLast, state oldState)
{
    int i1=s1, i2=s2;
    assert(!pushLast || vpd[e1] == vcd[e2]);
    char cp, cc;
    bool smaller=false, larger=false;
    while(i1!=e1 && i2!=e2){
        itoa(vpd[i1], cp);
        itoa(vcd[i2], cc);
        if(cp < cc){
            nStr.push_back(cp);
            ++i1;
            smaller = true;
        }else if(cp > cc){
            nStr.push_back(cc);
            ++i2;
            larger = true;
        }else{
            assert(cp == cc);//find some other pairs, prohibited
            if(pushLast) //false means please attach all the rest, no matter what happens
                return PROHIBITED;   
            else{
                nStr.push_back(cc);
                ++i1;
                ++i2;
            }
        }
        if((oldState == LESS && larger)||(oldState==GREATER && smaller))
            return PROHIBITED;
    }
    assert(i1 == e1 || i2 == e2);
    while(i1!=e1){
        itoa(vpd[i1++], cp);
        assert(cp != vcd[i2]);
        if(cp < vcd[i2]) 
            smaller = true;
        else
            larger = true;
        nStr.push_back(cp);
    }
    while(i2!=e2) {
        itoa(vcd[i2++], cc);
        assert('0'+vpd[i1] != cc);
        if(vpd[i1] < cc) 
            smaller = true;
        else
            larger = true;
        nStr.push_back(cc);
    }
    if(pushLast){
        assert(vpd[i1] == vcd[i2]);
        itoa(vpd[i1], cp);
        nStr.push_back(cp);
    }
    if(larger && smaller)
        return MIXED;
    if(larger) return GREATER;
    if(smaller) return LESS;
    assert(!larger && !smaller);
    assert(s1 == e1 && s2 ==e2 && pushLast);
    return NOHISTORY;
}
int sumdigit(int num){
    if(num < 10) return num;
    int sum = 0 ;
    while(num){
        int res = num % 10;
        sum += res;
        num /= 10;
    }
    return sumdigit(sum);
}
 
int main(int argc, char* argv[])
{
    i64 nmod = 1000000007LL;
    if(argc == 2)
        nmax = atol(argv[1]);
    minStr = string(2*nmax, '9');
    vector<int> primes; 
    sievePrimes(120000, primes);
    vector<int> composites; 
    composites.reserve(nmax);
    int pindex = 0;
    for(int i = 2; i<=110000; ++i){
        if(i == primes[pindex]){
            pindex++;
            continue;
        }else{
            composites.push_back(i);
            if((int)composites.size() == nmax)
                break;
        }
    }
    primes.resize(nmax);

    vpd.reserve(nmax);
    vcd.reserve(nmax);
    assert(static_cast<int>(primes.size())==nmax && static_cast<int>(composites.size())==nmax);
    for(unsigned int i = 0; i<primes.size(); ++i){
        vpd.push_back(sumdigit(primes[i]));
        vcd.push_back(sumdigit(composites[i]));
    }
    //now 10000 digits of both numbers are generated.
    //put all the index of each digit into a vector
    //so next digit 'x' can be immediately obtained
    vvpn.resize(10); 
    vvcn.resize(10);
    for(unsigned int i = 0; i < vpd.size(); ++i){
        vvpn[vpd[i]].push_back(i);
        vvcn[vcd[i]].push_back(i);
    }
    //initialize the priority queue. //the first digit is 
    //1 ...9, at least one of them is true
    for(unsigned int i = 1; i < 10; ++i){
        if(vvpn[i].empty() || vvcn[i].empty()) continue;
        int i1 = 0, i2 = 0;
        int x = vvpn[i][i1];
        int y = vvcn[i][i2];
        string nStr;
        state s= mergeTwoSequence(nStr,0, x, 0, y, true, NOHISTORY);
        if(s != PROHIBITED){
            insert_into_map(x, y, nStr);
            vpq.push(IntPair(x,y));
            printf("push to pq0 %d %d %s\n", x, y, nStr.c_str());
        }else{
            continue;
        }

        state news = s;
        while(news == s && (s!=MIXED && s!=PROHIBITED) ){
            nStr.clear();
            if(s == LESS){
                ++i1;
                if(i1 == (int)vvpn[i].size()) break;
                x = vvpn[i][i1];
            }else{
                assert(s == GREATER);
                ++i2;
                if(i2 == (int)vvcn[i].size()) break;
                y = vvcn[i][i2];
            }
            assert(i1 != (int)vvpn[i].size() && i2 != (int)vvcn[i].size());
            news = mergeTwoSequence(nStr, 0, x, 0, y, true, s);
            if(news == s)
                insert_into_map(x, y, nStr);
        }
    }
    vvpnext.resize(10); vvcnext.resize(10);
    for(unsigned int i = 1; i<10; ++i){
        create_vvnext(vvpnext[i], vvpn[i]);
        create_vvnext(vvcnext[i], vvcn[i]);
    }
    IntPair p0(0, 0);
    int cnt = 100;
    while(!vpq.empty()){
        p0 = vpq.top();
        if(p0.first + p0.second == cnt){
            printf("start working on %d\n", cnt);
            cnt += 100;
        }
        vpq.pop();
        clear_unused_map(p0.first + p0.second);
        bool betterFound = false;
        auto oiter  = vdata.find(p0);
        for(unsigned int i = 1; i < 10; ++i){
            auto iter1 = upper_bound(vvpn[i].begin(), vvpn[i].end(), p0.first);
            auto iter2 = upper_bound(vvcn[i].begin(), vvcn[i].end(), p0.second);
            process_one_step(i, p0, NOHISTORY, iter1, iter2, betterFound, 0);
        }
        if(!betterFound){
            string oStr = oiter->second;
            mergeTwoSequence(oStr, p0.first+1, nmax, p0.second+1, nmax, false, NOHISTORY);
            if((oStr.size() < minStr.size()) || (oStr.size() == minStr.size() && oStr < minStr)){
                minStr = oStr;
                printf("MIN %s from %d %d size %zu\n", minStr.c_str(), p0.first, p0.second, minStr.size());
            }
        }
    }
    //prime Str
    for(unsigned int i = 0; i < vpd.size(); ++i){
        printf("%d", vpd[i]);
    }
    printf("\n");
    //composite Str
    for(unsigned int i = 0; i < vcd.size(); ++i){
        printf("%d", vcd[i]);
    }
    printf("\n");
    i64 sum = 0;
    for(unsigned int i = 0; i < minStr.size(); ++i ){
        i64 val = minStr[i]-'0';
        assert(val >= 1 && val <= 9);
        assert(val > 0);
        sum *= 10LL;
        sum += val;
        sum %= nmod;
    }
    printf("minstr %s\nsum %lld\nsize %zu\n", minStr.c_str(), sum, minStr.size());
}
