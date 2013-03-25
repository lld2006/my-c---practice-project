#include <cstdio>
#include <cmath>
#include <map>
#include "../lib/tools.h"
#include <complex>
//lesson always check iterator reaches end of the container
//lesson 2, if something will be reused, clean it before use if necessary.
//lesson 3, if a set of operation needed on variable x, y, z, make sure 
//x, y, z's value are not changed during these operation, or consider 
//the change carefully
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

int main()
{
    i64 rf = 10000000000LL/1024;
    vector<int> ftable;
    factor_table_min(2*rf,ftable);
    i64 total = 0;
    //let us consider the situation 0<= a <= b <= c;
    //be careful about the equal or zero cases;
    IntPairVec vpairs;
    IntPairVec vresults;
    map<int, IntPair> msq2;
    i64 cmin = rf/sqrt(3.0)+1;
    for(i64 c = cmin; c < rf; ++c){
        IntPairVec vp1, vp2;
        factor_using_table(rf-c, vp1, ftable);
        factor_using_table(rf+c, vp2, ftable);
        merge_factors(vp1, vp2, vpairs);
        bool succeed = generate_all_squares(vresults, vpairs, msq2);
        if(!succeed) continue;
        //now sum up all results
        for(unsigned int j = 0; j < vresults.size(); ++j){
            i64 n1 = vresults[j].first;
            i64 n2 = vresults[j].second;
            assert(n1 <= n2);
            if(n2 > c)continue;
            i64 sum = n1 + n2 + c;
            i64 mult = 1;
            if(n2 == 0)
                mult = 6; // 0 0 c
            else if (n1 == 0){
                assert(n2 > 0 && n2 <= c);
                if(n2 == c){
                    mult = 12;
                }else{
                    mult = 24;
                }
            }else{//all greater than 0
                if(n1 == n2 && n2 == c){//a a a
                    mult = 8;
                }else if( n1 == n2 || n2 == c){
                    mult = 24;
                }else{
                    mult = 48;
                }
            }
            ///printf("%lld %lld %lld %lld\n", n1, n2, c, sum);
            assert(n1*n1+n2*n2+c*c==rf*rf);
            total += mult * sum;
        }
    }
    total += rf * 6;
    printf("%lld\n", total*1024);
}
