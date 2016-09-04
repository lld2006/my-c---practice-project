#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "../lib/typedef.h"
#include <algorithm>
using namespace std;

//need to write code using zero-suppressed decision diagram (ZDD)
unsigned int nn , ng;
void numbermind(unsigned int nc, const vector<int>& vguess, const vector<int>& vstat,
                const vector<int>& veff, const vector<vector<int> >& vnumber,
                const vector<int>& vcolflag){
    //vcolflag: how many candidates in this col
    //use the one with maximum correct guesses as candidate
    if(nc == nn){
        for(unsigned int i =0; i < vnumber.size(); ++i){
            assert(vnumber[i].size()==1);
            printf("%d", vnumber[i][0]);
        }
        printf("\n");
        exit(0);
    }
    for(unsigned int i = 0; i < vnumber.size();++i){
        if(vnumber[i].size()==0)
            return;//error! at least one
        if(vnumber[i].size()==1 && vcolflag[i] == 1){//one candidate left
            vector<int> vg2(vguess), ve2(veff), vstat2(vstat), vcol2(vcolflag);
            for(unsigned int j = 0; j < ng; ++j){
                int index = j * nn + i;
                if(vg2[index] != -1){
                    if(vg2[index] == vnumber[i][0])
                        --vstat2[j];
                    vg2[index] = -1;
                    --ve2[j];
                }
            }
            vcol2[i] = 0;
            numbermind(nc+1, vg2, vstat2, ve2, vnumber, vcol2); //nguess same
            return;// if no solution found till this point, some trial is wrong in upper level
        }
    }
    unsigned int selected_guess = 0;
    double ncand = 0;
    for(unsigned int i = 0; i < vstat.size(); ++i){
        if(veff[i] != -1 && (double)vstat[i]/(double)veff[i] > ncand){
            ncand = (double)vstat[i]/(double)veff[i];
            selected_guess = i;
            if(ncand == 0)break;
        }
    }
    if(ncand == 0){// run out of numbers from guessed number, check candidates from vnumber
        vector<int> vstat2(vstat);//correct
        vector<int> vg2(vguess); //effective guess update
        vector<int> ve2(veff); //how many numbers are still not determined in ith guess
        vector<int> vcol2(vcolflag);
        for(unsigned int i = 0; i < vnumber.size(); ++i){
            if(vnumber[i].size()>1){
                vector<vector<int> > vn2(vnumber);
                swap(vn2[i].back(), vn2[i][0]);//
                vn2.pop_back();
                numbermind(nc+1, vg2, vstat2, ve2, vn2, vcol2);
            }
        }
    }else{//need to consider where contradiction occurs
        for(unsigned int i = 0; i < nn; ++i){
            int index = selected_guess * nn + i;
            if(vguess[index] == -1)
                continue;
            vector<int> vstat2(vstat);
            vector<int> vg2(vguess);
            vector<int> ve2(veff);
            bool contra = false;
            for(unsigned int j = 0; j < ng; ++j){
                if(j == selected_guess)
                    continue;
                if(vg2[j*nn+i]==vg2[index])
                    --vstat2[j];//less correct
                vg2[j*nn+i] = -1;
                --ve2[j];
                if(vstat2[j] > ve2[j] || vstat2[j] < 0){
                    contra = true;
                    break;
                }
            }
            if(contra)
                continue;
            vector<vector<int> > vn2(vnumber);
            vector<int> vcol2(vcolflag);
            vcol2[i] = 0;
            vn2[i].clear();
            vn2[i].push_back(vg2[index]);
            vg2[index] = -1;
            --ve2[selected_guess];
            --vstat2[selected_guess];
            numbermind(nc+1, vg2, vstat2, ve2, vn2, vcol2);
        }
    }
}
int main(){
   FILE* fp;
   fp = fopen("mind16.txt", "r");
   fscanf(fp, "%d %d", &nn, &ng );
   vector<int> vguess;
   vector<int> vcorrect; //number of correct guesses
   vector<int> vstat, veff, vcolflag;
   vector<vector<int> > vnumber;
   i64 nx;
   vguess.resize(nn*ng); // all guesses
   vcorrect.resize(ng, 0);
   for(unsigned int i = 0; i < ng; ++i){
    int nc=0;
    fscanf(fp, "%lld %d", &nx, &nc);
    vector<int> nt;
    vcorrect[i] = nc;
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
   fclose(fp);
   vnumber.resize(nn);
   for(unsigned int i = 0; i < 9; ++i){
       vnumber[0].push_back(i);
   }
   for(unsigned int i = 1; i < nn; ++i){
       vnumber[i] = vnumber[0];
   }
   veff.resize(ng, nn); //each bit is a candidate
   vcolflag.resize(nn, 1);
   vstat=vcorrect;//how many numbers are still correct
   
   numbermind(0, vguess, vstat, veff, vnumber, vcolflag);
}
