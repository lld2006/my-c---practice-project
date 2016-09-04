#include "../lib/tools.h"
#include <algorithm>
#include <ctime>
#include "../lib/tools.h"
#include <set>
#include <complex>
using namespace std;
//find the unique solutions of a prime 4k+1 = a^2 + b^2;
//lesson 1, 4k+3 should never be considered, since x1+x2+x3 = (4k+3)*n
//can not be 5!
//lesson 2, r should be n*5; this will at least reduce the calculation
//by a factor of 5
//lesson 3, set is evil. If it can be avoided, avoid it.
//now the bottle neck is generate all squares for a composite number.
//Just because there are duplicates, I used set. lazy!
double total = 0;
int perilimit = 100000;
int cnt = 0;
bool operator<(const IntPair& p1, const IntPair& p2)
{
    if(p1.first < p2.first)
        return true;
    else if( p1.first > p2.first){
        return false;
    }else{
        return (p1.second < p2.second);
    }
}

//only for this problem, can not be generalized
void find_factors(int n, const vector<int>& ftable, vector<IntPair>& vpairs)
{
    vpairs.clear();
    int pwr = 0;
    int curr_fac = ftable[n];
    int f5 = false;
    while(curr_fac>1){
        ++pwr;
        n /= ftable[n];
        while(curr_fac == ftable[n]){
            ++pwr;
            n /= ftable[n];
        }
        if(curr_fac !=5)
            vpairs.push_back(IntPair(curr_fac, pwr));
        else{
            vpairs.push_back(IntPair(curr_fac, pwr+1));
            f5 = true;
        }
        curr_fac = ftable[n];
        pwr = 0;
    }
    if(!f5){
        vpairs.push_back(IntPair(5,1));
    }
}
void generate_all_squares2(vector<IntPair>& vres, vector<IntPair>& vpairs, 
                           vector<int>& primes, vector<int>& vpos,
                           vector<IntPair>& vsq2)
{
    vres.clear();
    vector<complex<int>> results;
    vector<complex<int>> r2;
    results.push_back(complex<int>(1,0));
    for(unsigned int j = 0; j < vpairs.size(); ++j){
        int px = vpairs[j].first;//prime factor
        int exp = vpairs[j].second;//power of this factor
        int pos = vpos[px];
        int p1 = vsq2[pos].first;
        int p2 = vsq2[pos].second;
        int pn = p1*p1+p2*p2;

        vector<complex<int>> vt;
        complex<int> cs, c2;
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
    for(unsigned int i = 0; i < results.size(); ++i){
        int r1 = abs(results[i].real());
        int r2 = abs(results[i].imag());
        if(r1 < r2)
            vres.push_back(IntPair(r1, r2));
        else
            vres.push_back(IntPair(r2, r1));
    }
}
double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//this part is most time consuming, try to optimize it!!!!
void check_ortho(int n, vector<IntPair>& results)
{
    n *= 5;
    for(unsigned int i =0 ;i < results.size(); ++i){
        int x1 = results[i].first;
        int y1 = results[i].second;
        for(unsigned int j =i+1; j < results.size(); ++j){
            int x2 = results[j].first;
            int y2 = results[j].second;
            int x3 = 5-x1-x2;
            int y3 = -y1-y2;
            if(x3 < x1|| x3 < x2) continue;
            if(x3 == x2 && y3 <= y2) continue;
            if(x3 == x1 && y3 <= y1) continue;
            double t1 = 0;
            if(25-10*(x1+x2)+2*(x1*x2+y1*y2) + n == 0){
                t1= dist(x1, y1, x2, y2);
                t1 += dist(x1, y1, x3, y3);
                t1 += dist(x2, y2, x3, y3);
                if(t1 <= perilimit){
                    ++cnt;
                    total += t1;
                }
            }
        }
    }
}
void create_and_sort_pairs(vector<IntPair>& results)
{
    vector<IntPair> vr(results);
    results.clear();
    for(unsigned int i = 0; i < vr.size(); ++i){
        int x = vr[i].first;
        int y = vr[i].second;
        if(x == 0){
            assert(y >0);
            results.push_back(IntPair(0, y));
            results.push_back(IntPair(0, -y));
            results.push_back(IntPair(y, 0));
            results.push_back(IntPair(-y, 0));
        }else if(y==0){
            assert(0);
            if(x<0){
                results.push_back(IntPair(x, 0));
                results.push_back(IntPair(-x, 0));
            }
        }else if(x != y){
            results.push_back(IntPair(x, y));
            results.push_back(IntPair(x, -y));
            results.push_back(IntPair(-x, y));
            results.push_back(IntPair(-x, -y));
            results.push_back(IntPair(y, x));
            results.push_back(IntPair(y, -x));
            results.push_back(IntPair(-y, x));
            results.push_back(IntPair(-y, -x));
        }else{
            assert(x == y);
            results.push_back(IntPair(x, x));
            results.push_back(IntPair(x, -x));
            results.push_back(IntPair(-x, x));
            results.push_back(IntPair(-x, -x));
        }
    }
    sort(results.begin(), results.end());
}
int main()
{
    int limit=70000000;
    int rlimit = limit;
    vector<int> primes;
    primeWithin(primes, rlimit);
    vector<int> p1;//4k+1 vector
    vector<int> vflags;// remove 4k+3^odd type
    vflags.resize(rlimit+1, 1);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int np = primes[i];
        if(primes[i] % 4 != 1){
            for(unsigned int j = np; j <vflags.size(); j+=np){
                vflags[j] = 0;
            }
        }
    }
    vflags[0] = 1;//for prime 2
    //primes to squares
    vector<IntPair> vsq2;
    int a=0, b=0;
    vsq2.push_back(IntPair(1, 1));
    for(unsigned int i = 1; i < primes.size(); ++i){
        if(primes[i] % 4 ==3){ 
            vsq2.push_back(IntPair(0, 0));
        }else{
            prime_generate_sq2(primes[i],a, b);
            vsq2.push_back(IntPair(a, b));
        }
    }
    //easier to find all prime square
    vector<int> vpos;
    vpos.resize(limit+1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        vpos[primes[i]] = i;
    }

    vector<int> ftable;
    vector<IntPair> vpairs;
    factor_table_min(rlimit, ftable);
    vector<IntPair> results;
    for(int i = 1; i<= rlimit; ++i){
        if( i % 10000000 == 0)
            printf("%d\n",i);
        if(vflags[i] == 0) continue;

        find_factors(i, ftable, vpairs);//actually i*5

        generate_all_squares2(results, vpairs, primes, vpos, vsq2);

        create_and_sort_pairs(results);

        check_ortho(i, results);

    }
    printf("%30.15f %d\n", total, cnt);
}
