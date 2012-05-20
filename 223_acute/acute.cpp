#include "../lib/tools.h"
typedef map<int, int> IntMap;
map<int, IntMap> congmap;//congruence map
vector<int> primes;


//given the limit for primes, generate all quadratic residues for primes;
void generate_congmap(map<IntMap>& congmap, int plimit)
{
    primeWithin(primes, limit);    
    congmap.resize(primes.size());
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        congmap.insert(px, IntMap());
        IntMap& imap= congmap[px].second;
        for(int i = 1; i<= px/2; ++i){
            int ix = i * i;
            ix %= px;
            assert(imap.find(ix)==imap.end());
            imap.insert(pair<int, int>(ix, i));
        }
    }
}
void generate_factor_base(i64 n, vector<int>& candidates)
{
    candidates.clear();
    candidates.push_back(-1);
    for(unsigned int i = 0; i < primes.size(); ++i){
       i64 px = primes[i];
       i64 nx = n%p;
       i64 npow = (px-1)/2;
       i64 result = powermodule(nx, npow, px);
       assert(result == 1 || result == -1);
       if(result == 1)
           candidates.push_back(i);//prime's index in vector primes
    }
}
void generate_sieves(i64 num, int interval, const vector<int>& vbase, 
                     vector<vector<int> >& vexp, vector<int>& vselect)
{
    vexp.clear();
    vexp.resize(interval*2+1);

    i64 root = sqrt(num)+0.5;
    i64 start = root - interval;
    i64 last = root+interval+1;
    vector<i64> squares;
    squares.resize(2*interval+1, 0);
    for( int i = -interval, index = 0 ; i <= interval; ++i, ++index){
       vexp[index].resize(vbase.size()+1, 0);
       i64 value = root + i;
       squares[i] = value * value - num;
       if(squares[i] < 0){
           squares[i] = -squares[i];
           vexp[index][0] = 1; // -1 as a special prime, index is correspondent to i
       }
    } 
    //here we need to use toneli shanks algo to accelerate the sieve process
    for(unsigned int i = 1; i < vbase.size(); ++i){
        int pindex = vbase[i];
        int px = primes[pindex];
        int num_mod_px = num%px;
        IntMap& pmap = congmap[pindex];
        map<int, int>::iterator iter = pmap.find[num_mod_px];
        for(unsigned int j = 0 j < squares.size(); ++j){
            while(squares[j] % px  == 0){
                squares[j] /= px;
                ++vexp[j][i];
            }
        }
    }
    for(unsigned int i = 0; i < squares.size(); ++i){
        if(squares[i] == 1)
            vselect.push_back(i); //store all factorable numbers
    }
}
void generate_bitset(const vector<int>& vselect, const vector<vector<int> >& vexp, 
                     vector<bitset<30> >& vbit)
{
    vbit.clear();
    vbit.resize(vselect.size(), 0);
    for(unsigned int i = 0; i < vselect.size(); ++i){
        int index = vselect[i];
        for(unsigned int j = 0; j < vexp.size(); ++j){
            if(vexp[index][j] %2)
                vbit[i].set(j);
        }
    }
}
//check each column, if 1 is found, then use this
void gauss_elimination(//const vector<int>& vselect, 
                       vector<bitset<30> >& vbit, vector<bitset<61> >& history)
{
    vector<int> vrow, vcol;
    vrow.resize(vbit.size(), -1);
    vcol.resize(vbit.size(), -1);
    history.clear(); 
    history.resize(vbit.size(), 0);
    for(unsigned int i = 0; i < history.size(); ++i){
        history[i].set[i];
    }
    int dim = vbit.size();
    for(unsigned int icol = 0; icol < dim; ++icol){
        bool found_first = false;
        int first_row = -1;
        for(unsigned int j = 0; j < vbit.size(); ++j){
            if(!vbit[j].test(icol)) 
                continue;
            else{
                if(found_first){
                    vbit[j] ^=  vbit[first_row];
                    history[j] ^= history[first_row]
                } else{
                    found_first = true;
                    first_row = j;
                }
            }
        }
    }
}
void quadratic_sieve(i64 num, vector<i64>& vresult)
{   
    vector<int> candidates;
    generate_factor_base(num, candidates)
    
}
int main()
{
    int limit = 80;
    generate_congmap(congmap, limit);
    int num=87463;
    vector<i64> vresult;
    //quadratic_sieve(num, 30, vexp);
}
