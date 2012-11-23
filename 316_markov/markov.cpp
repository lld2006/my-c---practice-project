#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include "../lib/typedef.h"
#include "../lib/tools.h"

//got a new idea after some thought, the state number 
//need not to be in the same left to right as the number is;
//actually, it is better to put the last digit first; it is easier
//to check if the states are same or different; it is critical
//to set the initial value to be zero to keep the initial zeros from 
//the right side
int check_states(string& si, int level, const vector<string>& states)
{
    while(level >= 0){
        if(states[level] == si)
            return level;
        si.erase(si.begin());
        --level;
    }
    assert(0);
    return -1;
}
//how states change between various states
void create_states(i64 n, vector<vector<int> >& vtransit )
{
    //states gives us all effective numbers, the last one is n
    vector<string> states;//for each state, empty, a, ab, abc....;
    states.push_back(string());
    string tstr(to_string(n));
    for(unsigned int i = 0; i < tstr.size(); ++i){
        states.push_back(tstr.substr(0,i+1));
    }

    vtransit.clear();
    
    //vtransit tells us how the state changes when we have 
    //some new input
    vtransit.resize(states.size());
    for(unsigned int i = 0; i < vtransit.size(); ++i){
        vtransit[i].resize(states.size(), 0);
    }

    //the last state is not necessary to consider
    for(unsigned int j = 0; j < states.size()-1; ++j){

        i64 n0 = 0;
        if(!states[j].empty())
            n0 = stoll(states[j]);
        n0 *= 10;
        for(unsigned int i = 0; i < 10; ++i){
            i64 num = n0 + i;
            string si(to_string(num));
            int matched = check_states(si, j+1, states);
            ++vtransit[j][matched];
        }
    }
}

void gauss_elimination(int n, vector<long double>& a)
{
    assert(static_cast<int>(a.size()) == n * n);
    for(int i = 0; i < n; ++i){
        long double diag = a[index0(n, i, i)];
        for(int j = i+1; j < n; ++j){
            //first find the aji/aii
            if(a[index0(n, j, i)]!=0)
                a[index0(n, j, i)] /= diag;
            //update jth row
            for(int k = i+1; k<n; ++k){
                a[index0(n, j, k)] -= a[index0(n, j, i)] * a[index0(n,i,k)];
            }
        }
    }
}
void LU(vector<long double>& a, vector<long double>& rhs, vector<long double>& sol)
{
    int nsize = rhs.size();
    sol.clear();
    sol.resize(nsize, 0);
    //forward
    assert(static_cast<int>(a.size()) == nsize * nsize);
    vector<long double> y(rhs);
    //diagonal belongs to upper triangle matirx
    for(int i = 0 ; i < nsize; ++i){
        for(int j = 0; j < i; ++j){
            y[i]-= a[index0(nsize, i,j)] * y[j];
        }
    }
    //backward
    for(int i = nsize -1 ; i>=0; --i){
        for(int j = nsize - 1; j > i; --j){
            y[i] -= a[index0(nsize, i, j)] * sol[j];
        }
        sol[i] = y[i]/a[index0(nsize, i, i)];
    }
}
int main()
{
    i64 nup = 10000000000000000LL;
    //nup = 1000000;
    i64 ndown = 999999;
    i64 total = 0;
    for(unsigned int j = 2; j <= ndown; ++j){
        if(j % 1000 == 0)
            printf("%u %lld\n", j, total);
        i64 nj = nup/j;
        string sn(to_string(nj));
        //how many digits are there
        int nsize = sn.size();
        vector<vector<int> > vtran;
        create_states(nj, vtran);
        vector<long double> vmat;
        vector<long double> rhs;
        vector<long double> sol;
        vmat.resize(nsize*nsize, 0);
        rhs.resize(nsize, 10);
        for(unsigned int i = 0; i < vtran.size()-1; ++i){
            vmat[index0(nsize, i, i)] = 10;
            vector<int>& vti = vtran[i];
            int zt = 0;
            for(unsigned int k = 0; k < vti.size()-1; ++k){//the last one is our destination
                if(vti[k] != 0){
                    zt += vti[k];
                    vmat[index0(nsize, i, k)] -= vti[k];
                }
            }
            assert(zt == 10||(zt==9 && i==(nsize-1)));

        }
        gauss_elimination(nsize, vmat);
        LU(vmat, rhs, sol);
        for(unsigned int ii = 0; ii<nsize; ++ii){
            i64 xtotal = 0;
            for(unsigned int jj = 0; jj<nsize; ++jj){
                xtotal += (i64)(vmat[index0(nsize, ii, jj)]) * (i64)sol[jj];
            } 
            assert(xtotal = 10);
        }
        i64 ts = sol[0]+0.5;
        //assert(ts >= 10 && ts < nup);
        assert(abs(sol[0] - ts) < 1e-4);
        total += (i64)(sol[0]+1.5-nsize);
    }
    printf("%lld\n", total);
}
