#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include "../lib/tools.h"
#include <queue>
#include <algorithm>
#include <set>
//find a huge mistake! if one is 512034045 and the other one 
//is                             5987645
//so it is better to use the second 4 instead of the first one
//so it should be 5120340987645 instead of 
//                5120398764045
// finally, I still go back to use the original string
int nmax = 100;
class pairLess2
{
  public:
    bool operator()(const IntPair& p1, const IntPair& p2)
    {
        return (p1.first + p1.second < p2.first + p2.second) 
            ||((p1.first+p1.second == p2.first+p2.second) && p1.first < p2.first);

    }
};
map<IntPair, string, pairLess2> vdata; //two dimensional v[i][j]
int maxShared = 0;
set<string> vMaxCand;
void clear_unused_map(int num)
{
    auto iter = vdata.begin();
    while(iter != vdata.end() && iter->first.first + iter->first.second < num)
        vdata.erase(iter++);
}
void insert_into_map(int x, int y, const string& str)
{
    assert(!str.empty());
    IntPair p= IntPair(x,y);
    auto iter = vdata.lower_bound(p);
    if(iter == vdata.end()|| !(iter->first==p ))
        vdata.insert(pair<IntPair, string>(p, str));
    else
        iter->second = str;
}

void itoa(int n, char& c)
{
    assert(0<n && n<10);//for this problem only, should be >= 0
    c = '0'+n;
}

//the index is the index in str, i.e., which number should be merged next
//vcand is the numer of letters left

enum state {NOHISTORY = 0, LESS=1, GREATER=2, MIXED=3, PROHIBITED=4};
state find_merged_string(const string& sharedStr, const string& cStr, int index, int s1, int e1, int s2, int e2, int state, bool pushLast) 
{
    if(sharedStr.size() == index) {
        return;
    }
    string nStr(cStr);
    int n = str[index]-'0';
    int i1 = s1, i2=s2;
    char cc, cp;
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
            //if(pushLast) //false means please attach all the rest, no matter what happens
                return PROHIBITED;   
            //else{
            //    nStr.push_back(cc);
            //    ++i1;
            //    ++i2;
            //}
        }
        if((oldState == LESS && larger)||(oldState==GREATER && smaller))
            return PROHIBITED;
    }
    assert(i1 == e1 || i2 == e2);
    if(larger && smaller){
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
        if(index == (int)sharedStr.size()-1){
            //only need to append all rest numbers
            state s = find_merged_string(sharedStr, nStr, index+1, e1+1, nmax, e2+1, nmax, NOHISTORY, false);
            assert(s!= PROHIBITED); // cannot figure out why PROHIBITED is possible
            //TODO post processing
        }else{
            int n = sharedStr[index+1] - '0'; //please advance to the next 'n'
            int ne1 = vvpnext[n][e1];
            int ne2 = vvcnext[n][e2];
            if(ne1 > nmax || ne2 > nmax) return PROHIBITED; //NO string available
            state s = find_merged_string(sharedStr, nStr, index+1, e1+1, ne1, e2+1, ne2, NOHISTORY, true);
            //TODO post processing
        }
    }else if(larger && !smaller){

    }else if(!larger && smaller){

    }else{//no compare
        assert(s1 == e1 && s2 ==e2 && pushLast);

    }
}
int sumdigit(int num){
    if(num < 10) return num;
    int sum = 0;
    while(num){
        int res = num % 10;
        sum += res;
        num /= 10;
    }
    return sumdigit(sum);
}
 
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
//a function to merge two of the sequence
vector<int> vpd, vcd;//prime digit sum and composite digit sum
void updateMaxCandidate(const string& str)
{
    int newSize = str.size();
    if(newSize> maxShared){
        maxShared = newSize;
        vMaxCand.clear();
        vMaxCand.insert(str);
    }else if(newSize == maxShared){
        vMaxCand.insert(str);
    }
}
//should visit the array backward
void create_vvnext(vector<int>& vvnext, vector<int>& vpn)
{
    vvnext.clear();
    vvnext.resize(nmax+1, 0);
    int curIndex = 0;
    int next = nmax+1; 
    if(!vpn.empty()){
        next = vpn[curIndex];
    }
    for( int j = 0; j < (int)vvnext.size(); ++j){
        if(j < next){
            vvnext[j] = next;
        }else{
            ++curIndex;
            if(curIndex ==(int)vpn.size()){
                next = nmax+1;
            }else{
                next = vpn[curIndex];
            }
            vvnext[j] = next;
        }
    }
}
int main(int argc, char* argv[])
{
    i64 nmod = 1000000007LL;
    if(argc == 2)
        nmax = atol(argv[1]);;
    vector<int> primes; 
    sievePrimes(110000, primes);
    vector<int> vcomps; 
    vcomps.reserve(nmax);
    int pindex = 0;
    for(int i = 2; i<=110000; ++i){
        if(i == primes[pindex]){
            pindex++;
            continue;
        }else{
            vcomps.push_back(i);
            if((int)vcomps.size() == nmax)
                break;
        }
    }
    primes.resize(nmax);
    vpd.reserve(nmax);
    vcd.reserve(nmax);
    for(unsigned int i = 0; i<primes.size(); ++i){
        vpd.push_back(sumdigit(primes[i]));
        vcd.push_back(sumdigit(vcomps[i]));
    }
    //now 10000 digits of both numbers are produced.
    //first I want to put all the index of each digit into a vector
    //so all numbers of the same val can be found sequentially
    vector<vector<int>> vpn; 
    vector<vector<int>> vcn;
    vpn.resize(10); vcn.resize(10);
    for(unsigned int i = 0; i < vpd.size(); ++i){
        vpn[vpd[i]].push_back(i);
        vcn[vcd[i]].push_back(i);
    }
    tpq vpq;
    //initialize the priority queue. //the first digit is 
    //0 1 ...9, at least one of them is true
    for(unsigned int i = 1; i < 10; ++i){
        if(vpn[i].empty() || vcn[i].empty()) continue;
        int x = vpn[i][0];
        int y = vcn[i][0];
        vpq.push(IntPair(x,y));
        insert_into_map(x, y, string(1, '0'+i));
    }
    //to make some fun let me create a vector of vector to find the next i in O(1) op
    vector<vector<int>> vvpnext, vvcnext;
    vvpnext.resize(10); vvcnext.resize(10);
    for(unsigned int i = 1; i<10; ++i){
        create_vvnext(vvpnext[i], vpn[i]);
        create_vvnext(vvcnext[i], vcn[i]);
    }
    //=============================================================================
    IntPair p0;
    while(!vpq.empty()){
        p0 = vpq.top();
        vpq.pop();
        clear_unused_map(p0.first + p0.second);
        for(unsigned int i = 1; i < 10; ++i){
            //auto iter1 = upper_bound(vpn[i].begin(), vpn[i].end(), p0.first);
            //if(iter1== vpn[i].end()) continue;
            //auto iter2 = upper_bound(vcn[i].begin(), vcn[i].end(), p0.second);
            //if(iter2 == vcn[i].end()) continue;
            //int index1 = *iter1; //at first I tried to use distance, but it is not necessary, use iter directly
            //int index2 = *iter2;
            //assert(index1 == vvpnext[i][p0.first]);
            //assert(index2 == vvcnext[i][p0.second]);
            int index1 = vvpnext[i][p0.first];
            int index2 = vvcnext[i][p0.second];
            if(index1 > nmax || index2 > nmax) continue;
            assert(index2 > p0.second);
            assert(index1 > p0.first);
            assert(vpd[index1] == vcd[index2]);
            auto niter  = vdata.find(IntPair(index1, index2));
            auto oiter  = vdata.find(p0);
            assert(oiter != vdata.end());
            string oStr = oiter->second; 
            oStr.push_back('0'+i);
            //printf("oInd %d %d %s\nnInd %d %d %s\n\n", p0.first, p0.second, oStr.c_str(), index1, index2, nStr.c_str());
            if(niter == vdata.end()){
                vpq.push(IntPair(index1, index2));
                insert_into_map(index1, index2, oStr);
                updateMaxCandidate(oStr);
                continue;
            }
            string nStr = niter->second;
            assert(!nStr.empty()); 
            if(oStr.size() < nStr.size()) continue; //better solution already exists
            if((oStr.size() > nStr.size() ||(oStr.size()==nStr.size() && oStr < nStr))){
                niter->second=oStr;
                updateMaxCandidate(oStr);
            }
        }
    }

    printf("maxShared = %d cand=%zu\n", maxShared, vMaxCand.size());
    string t;
    find_merged_string(t);
    //i64 sum = 0;
    //for(unsigned int i = 0; i < minStr.size(); ++i ){
    //    i64 val = minStr[i]-'0';
    //    assert(val >= 0);
    //    sum *= 10LL;
    //    sum += val;
    //    sum %= nmod;
    //    //sum=multmod(sum, 10LL, nmod);
    //    //sum=addmod(sum, val, nmod);
    //}
    for(unsigned int i = 0; i < vpd.size(); ++i){
        printf("%d", vpd[i]);
    }
    printf("\n");
    for(unsigned int i = 0; i < vcd.size(); ++i){
        printf("%d", vcd[i]);
    }
    printf("\n");
    //printf("%s\nres=%lld size=%zu\n", minStr.c_str(), sum, minStr.size());
}
