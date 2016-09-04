#include "../lib/tools.h"
#include <cassert>
#include <map>
#include <bitset>
#include <algorithm>
typedef map<int, int> IntMap;
map<int, IntMap> congmap;//congruence map
vector<int> primes;
int sieve_interval = 100;


//given the limit for primes, generate all quadratic residues for primes;
//actually each entry corresponds to two value
//the purpose of congmap is to find the quadratic residue for all primes.
//so we do not need to test all numbers 
void generate_congmap(map<int, IntMap>& congmap, int plimit)
{
    //0 for -1
    for(unsigned int i = 1; i < primes.size(); ++i){
        int px = primes[i];
        congmap.insert(pair<int, IntMap>(px, IntMap()));
        IntMap& imap= congmap[px];
        for(int i = 1; i<= px/2; ++i){
            int ix = i * i;
            ix %= px;
            assert(imap.find(ix)==imap.end());
            imap.insert(pair<int, int>(ix, i));
        }
    }
}
// candidate primes that might help the factorization
// remember -1 should be in prime list, not in this function
void generate_factor_base(i64 n, vector<int>& candidates)
{
    bool debug = true;
    candidates.clear();
    
    for(unsigned int i = 1; i < primes.size(); ++i){
       i64 px = primes[i];
       i64 nx = n%px;
       i64 npow = (px-1)/2;
       i64 result = powermodule(nx, npow, px);
       assert(result == 1 || result == px-1);
       if(result == 1)
           candidates.push_back(i);//prime's index in vector primes
    }
    if(debug) {
        for(unsigned int i =0; i < candidates.size(); ++i){
            assert( candidates[i]> 0 && candidates[i] < static_cast<int>(primes.size()));
            printf("%d\n", primes[candidates[i]]);
        }
    }
}

//vbase is the factor base -1 not included
void generate_sieves(i64 num, int interval, const vector<int>& vbase, 
                     vector<vector<int> >& vexp, vector<int>& vselect)
{
    vexp.clear();
    vselect.clear();
    vexp.resize(interval*2+1);

    i64 root = sqrt(num);
    vector<i64> squares;
    squares.resize(2*interval+1, 0);
    for(int i = -interval, index = 0 ; i <= interval; ++i, ++index){
       vexp[index].resize(vbase.size()+1, 0);
       i64 value = root + i;
       squares[index] = value * value - num;
       if(squares[index] < 0){
           squares[index] = -squares[index];
           vexp[index][0] = 1; // -1 as a special prime, index is correspondent to i
       }
    } 
    //here we need to use toneli shanks algo to accelerate the sieve process
    for(unsigned int i = 0; i < vbase.size(); ++i){
        int pindex = vbase[i];
        int px = primes[pindex];
        for(unsigned int j = 0; j < squares.size(); ++j){
            while(squares[j] % px  == 0){
                squares[j] /= px;
                ++vexp[j][i+1];
            }
        }
    }
    for(unsigned int i = 0; i < squares.size(); ++i){
        if(squares[i] == 1)
            vselect.push_back(i); //store all factorable numbers
    }
}
//vselect provides all n that can be reduced to 1;
//vexp provides the power for all bases
void generate_bitset(const vector<int>& vselect, const vector<vector<int> >& vexp, 
                     vector<bitset<30> >& vbit)
{
    vbit.clear();
    vbit.resize(vselect.size(), 0);
    unsigned int base_size = vexp[0].size();
    for(unsigned int i = 0; i < vselect.size(); ++i){
        int index = vselect[i];
        for(unsigned int j = 0; j < base_size; ++j){
            if(vexp[index][j] %2)
                vbit[i].set(j);
        }
    }
}
//check each column, if 1 is found, then use this
void gauss_elimination(vector<bitset<30> >& vbit, vector<bitset<61> >& history)
{
    vector<int> used;
    used.resize(vbit.size(), 0); // check which row was used
    history.clear(); 
    history.resize(vbit.size(), 0);
    for(unsigned int i = 0; i < history.size(); ++i){
        history[i].set(i);
    }
    unsigned int dim = vbit.size();
    for(unsigned int icol = 0; icol < dim; ++icol){
        bool found_first = false;
        int first_row = -1;
        for(unsigned int j = 0; j < vbit.size(); ++j){
            if((!vbit[j].test(icol)) ||(used[j])) 
                continue;
            else{
                if(found_first){
                    vbit[j] ^=  vbit[first_row];
                    history[j] ^= history[first_row];
                } else{ //first row found
                    found_first = true;
                    first_row = j;
                    used[first_row] = 1;
                }
            }
        }
    }
}
i64 analysis_history(i64 num, vector<int>& candidates, vector<int>& vselect, vector<vector<int> >& vexp, bitset<61>& hi)
{
    i64 prod = 1;
    i64 root = sqrt(num);
    vector<int> sel_exps;
    sel_exps.resize(vexp[0].size(), 0);

    for(unsigned int i = 0; i<vexp[0].size(); ++i){
        if(hi.test(i)) {
            int index = vselect[i];
            prod *= (root-sieve_interval+vselect[i]);
            prod %= num;
            for(unsigned int j = 0; j < vexp[index].size(); ++j){
                sel_exps[j] += vexp[index][j];
            }
        }
    }
    i64 prod2 = 1;
    assert(sel_exps.size() == candidates.size()+1);
    for(unsigned int i = 1; i < sel_exps.size(); ++i){
        assert(sel_exps[i] % 2 == 0);
        prod2 *= power(primes[candidates[i-1]], sel_exps[i]/2);
        prod2 %= num;
    }
    i64 delta = prod>prod2?prod-prod2:prod2-prod;
    i64 ret = gcd(delta, num);
    return ret;
}

vector<i64> quadratic_sieve(i64 num) 
{   
    vector<i64> results;
    vector<int> candidates; 
    vector<vector<int> > vexp;
    vector<int> vselect;
    generate_factor_base(num, candidates);
    generate_sieves(num, sieve_interval, candidates, vexp, vselect);
    vector<bitset<30> > vbit;
    vector<bitset<61> > history;
    generate_bitset(vselect, vexp, vbit);
    //vbit1 will be modified, need to keep an original copy 
    vector<bitset<30> > vbit1(vbit);
    gauss_elimination(vbit1, history);
    for(unsigned int i = 0; i <vbit1.size(); ++i){
        if(vbit1[i].any()) continue;
        i64 ret = analysis_history(num, candidates, vselect, vexp, history[i]);
        if(ret != num && ret != 1)
            results.push_back(ret);
    }
    return results;
}
int main()
{
    int limit = 60;
    primeWithin(primes, limit);    
    primes.push_back(-1);
    sort(primes.begin(), primes.end());
    //this prime vector is  special, -1 included in the first place, 
    //when primes are used as regular prime vector start from 1
    generate_congmap(congmap, limit);
    i64 num=600851475143LL;
    vector<i64> vresult;
    vresult = quadratic_sieve(num);
    for(unsigned int i = 0; i < vresult.size(); ++i)
        printf("%lld\n", vresult[i]);
}
