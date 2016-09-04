//this problem is kind of difficult if the method is not correct.
//one of the method that might be the genetic algorithm. using mutation
//and cross overs, the solution maybe found in 2 minutes. still need
//to find better method.
//the following code are not working in a couple of minutes.
//#include <tr1/unordered_map>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;

unsigned int nn, ng;//nn is the number of digit, ng is the number of guesses
vector<int> vguess; //guess and number of correct guesses
vector<int> vcorrect;
void search_nint(const vector<int>& match, const vector<int>& vc,
                 vector<int> vcand, int index, int ncr);
void search_ni(const vector<int>& match, const vector<int>& vcorrect)
{
    vector<int> vcand;
    for (unsigned int ni = 1; ni < ng; ni++) {
        //lesson vcand should be cleared before next time use
        vcand.clear();
        vcand.push_back(ni);
        search_nint(match, vcorrect, vcand, ni+1, vcorrect[ni]);
    }
}
void search_nint(const vector<int>& match, const vector<int>& vc,
                 vector<int> vcand, int index, int ncr)
{
    if(index == static_cast<int>(ng)) return;
    if(ncr <14){
        for(unsigned int j = index; j < ng; ++j){
            for(int i = 0; i < static_cast<int>(vcand.size()); ++i){
                if(match[index0(ng, vcand[i], j)] > 0){
                    continue;
                }else{
                    vector<int> vcd1(vcand);
                    vcd1.push_back(j);
                    search_nint(match, vc, vcd1, j+1, ncr+vcorrect[j]);
                }
            }
        }
    }else{
        int total_match = 0;
        for(unsigned int j = 1; j < ng; ++j){
            if(find(vcand.begin(), vcand.end(), j) != vcand.end())
                continue;
            for(unsigned int i = 0; i <vcand.size(); ++i)
                total_match += match[index0(ng,j, vcand[i])];
            if( ncr +vcorrect[j] < 17){
                if(total_match== 0){
                    vector<int> vcd1(vcand);
                    vcd1.push_back(j);
                    search_nint(match, vc, vcd1, j+1, ncr+vcorrect[j]);
                }else{
                    assert(total_match != 1);
                    //lazy to write code later if necessary
                    continue;
                }
            }else if(ncr+vcorrect[j]==17){
                if(total_match > 1 || total_match == 0)
                    continue;
               printf("j %d ", j);
               for(unsigned int i = 0; i < vcand.size(); ++i){
                    printf("%d ", vcand[i]);
                    if(match[index0(ng, j, vcand[i])]==1){
                        for(unsigned int k = 0; k < nn; ++k){
                            printf("\n%d %d %d", k, vguess[j*nn+k], vguess[vcand[i]*nn+k] );
                        }
                        printf("\n");
                        exit(1);
                    }
               }
            }else{
                continue;
            }
        }
    }
}
int main(){
    // start reading data
    FILE* fp;
    fp = fopen("mind16.txt", "r");
    fscanf(fp, "%d %d", &nn, &ng );
    i64 nx;
    vguess.resize(nn*ng); // all guesses
    vcorrect.resize(ng, 0);
    vector<int> nt; //temporaray vector
    for(unsigned int i = 0; i < ng; ++i){
        char nc='0';
        fscanf(fp, "%lld %c", &nx, &nc);
        vcorrect[i] = nc-'0';
        nt.clear();
        nt.resize(nn, 0);
        int start = 0;
        while(nx){
            int nres = nx%10;
            nt[start++] = nres;
            nx /= 10;
        }
        reverse(nt.begin(), nt.end());
        copy(nt.begin(), nt.end(), vguess.begin()+i*nn);
    }
    fclose(fp); //data reading end

    //initial guess
    vector<int> match;
    match.resize(ng*ng, 0);
    //first update the guess vector, all incorrect guesses are
    //marked as -1
    for(unsigned int i = 1; i < ng; ++i)
        for(unsigned int j = 0; j < nn; ++j){
            if(vguess[j] == vguess[i*nn+j])
                vguess[i*nn+j] = -1;
        }
    
    for(unsigned int i=1; i < ng; ++i){
        for(unsigned int j= i +1; j <ng; ++j){
            int nmatch = 0;
            for(unsigned ni = 0; ni < nn; ++ni){
                if (vguess[i*nn+ni]!=-1 && vguess[i*nn+ni] == vguess[j*nn+ni])
                    ++nmatch;
            }
            match[index0(ng, i, j)] = nmatch;
            match[index0(ng, i, j)] = nmatch;
        }
    }
    int mcount = 0;
    for(unsigned int ix = 1 ; ix <ng; ++ix)
        for (unsigned int iy = 1; iy < ng; iy++) {
            if(match[index0(ng, ix, iy)]== 0)
                ++mcount;
        }
    printf("total 0s %d\n", mcount);
    search_ni(match, vcorrect);
}
