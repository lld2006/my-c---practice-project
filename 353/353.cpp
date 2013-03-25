#include <cstdio>
#include <tuple>
#include <cmath>
#include <map>
#include <complex>
#include <set>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <algorithm>
#include <queue>
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
// this function create all triplets in z direction, x, y, z and x, y, -z
// but -x, y, z are not included
void create_all_triplets(int radius, VTriplet& vtrip)
{
    //0 0 r should be added to the vector, this
    //trivial solution makes trouble for my code;
    //so added manually 
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

        if(z != y) {
            strip.insert(Triplet(x,z,y));
            if(y != 0)
                strip.insert(Triplet(x,z,-y));
            if(x != y){
                strip.insert(Triplet(y,z,x));
                if(x!=0)
                    strip.insert(Triplet(y,z,-x));
            }
        }else{//z==y
            if(x != y){
                strip.insert(Triplet(y,z,x));
                if(x!=0)
                    strip.insert(Triplet(y,z,-x));
            }
        }
    }
    //now all triplets in z direction are created
    //put all these triplets into vector
    VTriplet vt1;
    for(auto iter = strip.begin(); iter!=strip.end(); ++iter){
        vt1.push_back(*iter);
    }
    vt1.swap(vtrip);
    sort(vtrip.begin(), vtrip.end(), tripleless() );
}
void debug(const VTriplet& vt)
{
    for(unsigned int i = 0; i< vt.size(); ++i){
        printf("%d %d %d\n", get<0>(vt[i]), get<1>(vt[i]), get<2>(vt[i]));
    }
}
//radius square
double risk(Triplet& t1, Triplet& t2, i64 r2)
{
    int x1 = get<0>(t1);
    int y1 = get<1>(t1);
    int z1 = get<2>(t1);
    int x2 = get<0>(t2);
    int y2 = get<1>(t2);
    int z2 = get<2>(t2);
    assert(x1 >=0 && y1 >= 0);
    assert(x2>=0 && y2>= 0); 
    double d21 = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    double d22 = (x2-y1)*(x2-y1)+(y2-x1)*(y2-x1);
    double d2min = d21 < d22? d21:d22;
    d2min += (z2-z1)*(z2-z1);
    double cs = 1.0- d2min/(2*r2);
    assert(cs >= -1.0);
    double risk = acos(cs);
    risk *= risk;
    return risk;
}
class diless{
    public: 
        bool operator() (const pair<double, int>& p1, const pair<double,int>& p2 )
        {
            if (p1.first < p2. first)
                return false;
            else if(p1.first > p2.first)
                return true;
            else{
                return p1.second > p2.second;
            }
        }
};
void find_shortest_path(vector<double>& cmin, VTriplet& vtrip, i64 r2)
{
    cmin.resize(vtrip.size(), 1e20);
    cmin[0] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, diless> psq;
    psq.push(pair<double, int>(0.0, 0));
    vector<int> flags; 
    flags.resize(vtrip.size(), 0);
    flags[0] = 1;// 1 means the shortest path has been determined
    while(!psq.empty()){
        double dmin = 0;
        int index = 0;
        while(true){
            const pair<double,int>& ret = psq.top();
            dmin = ret.first;
            index = ret.second;
            psq.pop();
            assert(dmin>=cmin[index]);
            if(dmin == cmin[index])
                break;
            if(psq.empty())
                return;
        }
        //current minimum set is as found
        flags[index] = 1;
        for(unsigned int i = 0; i < flags.size(); ++i){
            if(flags[i]) continue;
            double dt = risk(vtrip[index], vtrip[i], r2);
            if(cmin[i] > dmin+dt){
                cmin[i] = dmin + dt;
                psq.push(pair<double, int>(cmin[i], i));
            }
        }
    }
}
int main()
{
    int limit = 32767;
    double PI = atan(1.0)*4.0;
    factor_table_min(2*limit, ftable);
    double total = 0.0;
    for(unsigned int i = 1; i<=15; ++i){
        i64 radius = (1<<i)-1;
        i64 r2 = radius * radius;
        VTriplet vtrip ;
        create_all_triplets(radius, vtrip);
        printf("V %lld %zu\n",radius, vtrip.size());
        //now all triplets needed are created. Since the z direction is
        //constrained to limit which is not a big number, I will create
        //a vector to restrict the unnecessary search.
        vector<double> cmin;
        //using priority queue to find shortest path
        find_shortest_path(cmin, vtrip, r2);
        double trisk = cmin.back()/(PI*PI);
        printf("%d %30.20f\n", i, trisk);
        total += trisk;
    }
    printf("%30.20f\n", total);
}
