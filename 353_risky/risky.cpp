#include <cstdio>
#include <tuple>
#include <cmath>
#include <map>
#include <complex>
#include <set>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
typedef tuple<int,int,int> Triplet;
typedef vector<tuple<int,int,int>> VTriplet;
vector<int> ftable; 
map<int, IntPair> msq2;
class tripleless{
    public:
bool operator() ( const Triplet& t1, const Triplet& t2)
{
    int t1x = get<0>(t1);
    int t1y = get<1>(t1);
    int t1z = get<2>(t1);
    int t2x = get<0>(t2);
    int t2y = get<1>(t2);
    int t2z = get<2>(t2);
    if(t1z < t2z)
        return true;
    else if(t1z>t2z)
        return false;
    else{
        if(t1y<t2y){
            return true;
        }else if(t1y > t2y){
            return false;
        }else{
            if(t1x < t2x)
                return true;
            else
                return false;
        }
    }
}
};
void merge_factors(const IntPairVec& v1, const IntPairVec& v2, IntPairVec& v)
{
    v.clear();
    auto iter1 = v1.begin();
    auto iter2 = v2.begin();

    while (iter1 != v1.end() && iter2 != v2.end()){
        while(iter1 != v1.end() && iter1->first < iter2->first){
            v.push_back(*iter1++);        
        };
        if(iter1 == v1.end())
            break;
        while(iter2 != v2.end() && iter2->first < iter1->first){
            v.push_back(*iter2++);
        }
        if(iter2 == v2.end())
            break;
        while(iter1 != v1.end() && iter2!= v2.end() && iter1->first==iter2->first){
            v.push_back(IntPair(iter1->first, iter1->second+iter2->second));
            ++iter1;
            ++iter2;
        }
    }
    if(iter1 != v1.end()){
        assert(iter2 == v2.end());
        for(;iter1 != v1.end(); ++iter1){
            v.push_back(*iter1);
        }
    }else if(iter2 != v2.end()){
        assert(iter1 == v1.end());
        for(;iter2 != v2.end(); ++iter2){
            v.push_back(*iter2);
        }
    }
}
bool generate_all_squares(vector<IntPair>& vresults, 
                          vector<IntPair>& vpairs,
                          map<int, IntPair>& msq2)
{
    vresults.clear();

    vector<complex<int>> results;
    vector<complex<int>> r2;//for swap purpose
    results.push_back(complex<int>(1,0));
    i64 n2 = 1;
    bool mult2 = false;//anything extra to multiply?
    
    int jstart = 0;
    if(vpairs[0].first == 2){
        jstart = 1;
        mult2 = true;
    }
    for(unsigned int j = jstart; j < vpairs.size(); ++j){
        int px = vpairs[j].first;//prime factor
        int exp = vpairs[j].second;//power of this factor
        if(px %4 ==3){
            if(exp %2 == 0){
                n2 *= power(px, exp/2);
                continue;
            }else
                return false;
        }
        int p1, p2;
        auto iter = msq2.lower_bound(px);
        if(iter != msq2.end() && iter->first == px){
            //directly use it
            p1 = iter->second.first;
            p2 = iter->second.second;
        }else{
            //generate the twins then insert into map
            prime_generate_sq2(px, p1, p2);
            msq2.insert(iter, make_pair(px, IntPair(p1, p2)));
        }
        int pn = p1*p1+p2*p2;

        vector<complex<int>> vt;
        complex<int> cs, c2;//cs is start number, c2 is square
        int start = 0;
        if(exp % 2==1){
            start = 1;
            cs = complex<int>(p1, p2);
            c2 = cs * cs;
        }else{
            start = 0;
            cs = complex<int>(0,1);
            c2 = complex<int>(p1,p2)*complex<int>(p1,p2);
        }
        //create all prime power number pairs;
        for( int j = start; j <= exp; j+=2){
            int tp = power(pn, (exp-j)/2);
            vt.push_back(tp*cs);
            cs *= c2;
        }

        r2.clear();
        for(unsigned int j = 0; j < results.size();++j){
            for(unsigned int k = 0; k < vt.size();++k){
                if(results[j].real() == 0 || results[j].imag()==0)
                    r2.push_back(results[j] * vt[k]);
                else if(vt[k].real()==0|| vt[k].imag()==0)
                    r2.push_back(results[j] * vt[k]);
                else{
                    r2.push_back(results[j]*vt[k]);
                    r2.push_back(results[j]*conj(vt[k]));
                }
            }
        }
        results.swap(r2);
    }
    if(vpairs[0].first == 2){
        n2 *= power(2, vpairs[0].second/2);
    }
    for(unsigned int i = 0; i < results.size(); ++i){
        int r1 = abs(results[i].real());
        int r2 = abs(results[i].imag());
        if( r1 > r2)
            swap(r1, r2);
        if(mult2 || n2 > 1){
            r1 *= n2;
            r2 *= n2;
            if(vpairs[0].first==2 && vpairs[0].second % 2 == 1){
                int t = r1 + r2;
                r2 =  t;
                t = r2 -2* r1;//ah here is a tricky bug! r2 has changed value
                r1 =  t;
            }
        }
        vresults.push_back(IntPair(r1, r2));
    }
    return true;
}
void create_all_triplets(int radius, VTriplet& vtrip)
{
    //0 0 r should be added to the vector, this
    //trivial solution makes trouble for my code;
    //should be added manually 
    IntPairVec vpairs;
    i64 zmin = radius/sqrt(3.0)+1;
    vtrip.push_back(Triplet(0,0,radius));
    for(i64 z = zmin; z < radius; ++z){
        IntPairVec vp1, vp2;
        factor_using_table(radius - z, vp1, ftable);
        factor_using_table(radius + z, vp2, ftable);
        merge_factors(vp1, vp2, vpairs);
        IntPairVec vresults;
        bool succeed = generate_all_squares(vresults, vpairs, msq2);
        if(!succeed) continue;
        for(unsigned int i = 0; i < vresults.size();++i){
            assert(vresults[i].first <= vresults[i].second);
            if(vresults[i].second <= z)
                vtrip.push_back(Triplet(vresults[i].first, vresults[i].second, z)); 
        }
    }

    set<Triplet, tripleless > strip;
    for(unsigned int i = 0; i < vtrip.size();++i){
        int x = get<0>(vtrip[i]);
        int y = get<1>(vtrip[i]);
        int z = get<2>(vtrip[i]);
        assert(x <=y && y<= z);
        assert(z!=0);
        strip.insert(Triplet(x,y,z));
        strip.insert(Triplet(x,y,-z));

        if(z != y)
            strip.insert(Triplet(x,z,y));
        if(y != 0)
            strip.insert(Triplet(x,z,-y));
        if(x!=y && x != z){
            strip.insert(Triplet(y,z,x));
            if(x!=0)
                strip.insert(Triplet(y,z,-x));
        }
    }
    //now all triplets in z direction are created
    //put all these triplets into vector
    VTriplet vt1;
    for(auto iter = strip.begin(); iter!=strip.end(); ++iter){
        vt1.push_back(*iter);
    }
    vt1.swap(vtrip);
}
void debug(const VTriplet& vt)
{
    for(unsigned int i = 0; i< vt.size(); ++i){
        printf("%d %d %d\n", get<0>(vt[i]), get<1>(vt[i]), get<2>(vt[i]));
    }
}
void debugs(const set<Triplet, tripleless>& st)
{
    for(auto iter = st.begin(); iter != st.end(); ++iter)
        printf("%d %d %d\n", get<0>(*iter), get<1>(*iter), get<2>(*iter));

}
int main()
{
    int limit = 32767;
    factor_table_min(2*limit, ftable);
    for(unsigned int i = 1; i<=15; ++i){
        i64 radius = (1<<i)-1;
        VTriplet vtrip;
        create_all_triplets(radius, vtrip);
        //if(i==4) debug(vtrip);
        printf("%lld %zu\n",radius, vtrip.size());
    }
}
