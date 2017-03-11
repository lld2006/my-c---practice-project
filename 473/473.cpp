#include "../lib/tools.h"
#include <cmath>
#include <unordered_map>
typedef pair<i64, I64Pair> PI3;
typedef unordered_map<i64, I64Pair> hashmap;
    
I64PairVec vphi2;
vector<int> vbase;
vector<i64> v5pmax;
vector<i64> v5nmax;

//just find that optimization is needed if the phi
//representation is definitely not an integer

i64 get_all_pal_number(I64Pair np2, int nc);
I64Pair getPhiNext(const I64Pair&  np)
{
    i64 n1 = np.first + np.second * 5;
    i64 n5 = np.first + np.second;
    assert((n1 & 1) == 0);
    assert((n5 & 1) == 0);
    n1 /= 2;
    n5 /= 2;
    return I64Pair(n1, n5);
}
I64Pair getNPhiNext(const I64Pair&  np )
{
    i64 n1 = np.second * 5 - np.first;
    i64 n5 = np.first - np.second;
    assert((n1 & 1) == 0);
    assert((n5 & 1) == 0);
    n1 /= 2;
    n5 /= 2;
    return I64Pair(n1, n5);
}
void getNmaxInVbase(i64 nmax, vector<int>& vbase)
{
    double remain  = nmax;
    double phi = (sqrt(5.0)+1)/2.0;
    int n0 = log(nmax)/log(phi);
    vbase.clear();
    vbase.resize(n0+1, 0);
    int n = n0;
    while(remain > 1){
        if(n+1 == (int)vbase.size() || vbase[n+1] == 0)
            vbase[n] = 1;
        else{//consecutive n are not allowed
            assert(0);
            --n;
            vbase[n] = 1;
        }
        remain -= pow(phi, n);
        n = log(remain)/log(phi);
    }
    if(vbase[0] == 1)
        vbase[0] = 0;//1.1 is not acceptable
}
int calcValue(int n){
    if(n & 1) return 0.0;
    vector<int> vn;
    vn.resize(30);
    vn.push_back(0);
    for(unsigned int i = 1; i < vn.size(); ++i){
        bool ni = n & ( 1<< i );
        bool ni1 = n & (1<<(i-1));
        if(ni && ni1) return 0;
        if(ni) vn[i] = 1;
    }
    int n1 =0; int n5 = 0;
    for(unsigned int i = 0; i < vn.size(); ++i){
        if(vn[i]){
            n1 += vphi2[i].first;
            n5 += vphi2[i].second;
        }
    }
    if(n5 == 0 && ((n1 & 1) == 0))
        return n1 >> 1;
    return 0;
}
int main(int argc, char* argv[])
{
    i64 t = atoll(argv[1]);
    i64 nmax = t;
    //nmax = 10000000000LL ;
    I64PairVec vphi;  // 0 and positive phi powers, multiplied by 2
    I64PairVec vnphi; // negative phi powers, multiplied by 2
    //first integer is integer part and second part is sqrt(5) part
    vphi.push_back(I64Pair(2, 0));
    vnphi.push_back(I64Pair(2, 0));
    //phi power
    for(unsigned i= 1; i < 51; ++i){
        I64Pair np = getPhiNext(vphi.back());
        vphi.push_back(np);
        np = getNPhiNext(vnphi.back());
        vnphi.push_back(np);
    }
    //nmax in phi representation
    getNmaxInVbase(nmax, vbase);
    //need some test code
    printf("size of vbase %d\n", static_cast<int>(vbase.size()));
    //2.5 sum phi and phi inverse to save time.
    for(unsigned int i = 0; i < 50; ++i ){
        i64 a = vphi[i].first + vnphi[i+1].first;
        i64 b = vphi[i].second + vnphi[i+1].second;
        vphi2.push_back(I64Pair(a, b));
    }
    i64 pmax = 0; i64 pmin = 0;
    for(unsigned int i = 0; i < vphi2.size(); ++i ){
        i64 n5 = vphi2[i].second;
        if( n5 > 0)
            pmax += n5;
        else
            pmin += n5;
        v5pmax.push_back(pmax);
        v5nmax.push_back(pmin);
    }
    if(false){
        int sum = 0;
        for(unsigned int i = 2; i<=100000; i+=2){
            int val = calcValue(i);
            if(val > 10000) return 0;

            sum += val;
            if(val > 0)
            printf("%d %d %d\n", i, val, sum);
        }
    }
    //third, use dynamic programming to figure out the sum
    i64 sum = 1;
    //in this loop, all start from 10
    for( int i = 1; i < (int)vbase.size()-1; ++i){
        I64Pair np2 = vphi2[i];
        //i-2 is the next digit to be considered
        sum += get_all_pal_number(np2, i-2);
        printf("part1 i=%d sum=%lld\n", i, sum);
    }
    //in this loop, numbers are restricted to 1?@#$0xyzt
    //and number of digits is fixed
    I64Pair np2;
    np2 = vphi2[vbase.size()-1];
    assert(vbase[vbase.size()-2] == 0);
    for(int i = vbase.size() - 3; i>=0; --i){
        if(vbase[i] == 0) continue;
        sum += get_all_pal_number(np2, i-1);
        printf("part2 i=%d sum=%lld\n", i, sum);
        np2.first += vphi2[i].first;
        np2.second += vphi2[i].second;
    }
    //this is a very special case! need to be very careful!
    if(np2.second == 0 && ((np2.first & 1) == 0))
        sum += np2.first/2;
    printf("%lld\n", sum);
}

void insert_or_update_hashmap(PI3 px, hashmap& hmap, int level)
{
    i64 v5 = px.first;
    i64 n = px.second.second;
    i64 v1 = px.second.first;
    if(v5 > 0 && v5 + v5nmax[level] > 0) return;
    if(v5 < 0 && v5 + v5pmax[level] < 0) return;
    auto iter = hmap.find(v5);
    if(iter == hmap.end())
        hmap.insert(px);
    else{
        iter->second.first += v1;
        iter->second.second += n;
    }
}

void map_change(const hashmap& from, hashmap& to, I64Pair& np2, int level)
{
    for(auto iter = from.begin(); iter != from.end(); ++iter){
        i64 n = iter->second.second;
        i64 v5 = iter->first + np2.second;
        i64 v1 = iter->second.first + np2.first * n;
        PI3 np = PI3(v5, I64Pair(v1, n));
        insert_or_update_hashmap(np, to, level);
    }
}
//nc is the current digit to be investigated
//please notice only zero can be used for digit 0
i64 get_all_pal_number(I64Pair np2 , int nc)
{
    hashmap hmap00, hmap10, hmap11, hmap01;
    hashmap thmap00, thmap10, thmap11, thmap01;
    if(np2.first & 1){
        //hmap01.insert(PI3(np2.second, I64Pair(np2.first, 1LL)));
        insert_or_update_hashmap((PI3(np2.second, I64Pair(np2.first, 1LL))), hmap01, nc);
    }else{
        //hmap00.insert(PI3(np2.second, I64Pair(np2.first, 1LL)));
        insert_or_update_hashmap((PI3(np2.second, I64Pair(np2.first, 1LL))), hmap00, nc);;
    }
    //number should start as 1abc0xyz....
    //first number is last digit and second is even or odd
    //we do not need number like 3/2
    //00 last 0, even; 01 last 0 odd
    //10 last 1, even; 11 last 1 odd
    for(int ni = nc; ni >=0; --ni){
        thmap00.clear(); thmap01.clear();
        thmap10.clear(); thmap11.clear();
        //this is the 0->0 part
        thmap00 = hmap00; //add 0 to the end of hmap00
        
        thmap01 = hmap01; //add 0 to the end of hmap01;

        //add 0 to the end of hmap10, it becomes 00
        for(auto iter = hmap10.begin(); iter != hmap10.end(); ++iter)
            insert_or_update_hashmap(*iter, thmap00, ni);
        //add 0 to the end of hmap11, it becomes 01;
        for(auto iter = hmap11.begin(); iter != hmap11.end(); ++iter)
            insert_or_update_hashmap(*iter, thmap01, ni);

        //this is the 0 -> 1 part
        //hmap00 and hmap 01, add 1 to be hmap 10 or hmap 11 based on 1's "1" odd or even
        i64 n1 = vphi2[ni].first;
        if(n1 & 1){
            map_change(hmap00, thmap11, vphi2[ni], ni);
            map_change(hmap01, thmap10, vphi2[ni], ni);
        }else{//no change parity
            map_change(hmap00, thmap10, vphi2[ni], ni);
            map_change(hmap01, thmap11, vphi2[ni], ni);
        }
        swap(hmap00, thmap00);
        swap(hmap01, thmap01);
        swap(hmap10, thmap10);
        swap(hmap11, thmap11);
    }
    i64 ret = 0;
    auto iter = hmap00.find(0LL);
    if(iter != hmap00.end() )
        ret = iter->second.first/2;
    return ret;
}
