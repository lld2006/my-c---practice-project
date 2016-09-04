#include <cstdio>
#include <complex>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
#include <cstdlib>
using namespace std;
//The correct way to solve this problem is to use recursion and complex<int> in c++ 
//we can find d_na d_nb very easily for any n up to 50.  
//the following information needs to be stored, displacement relative to current 
//position, and direction change after the operation relative to the initial
//direction, and number of step moves. then we can use some sort of bisection
//method to search for the position at the nth step.
class move
{
  public:
    move(): dir(1, 0), disp(0, 0), steps(0) {}
    move(i64 stepi, complex<int> di, complex<int> ri):
                              dir(ri)
                            , disp(di)
                            , steps(stepi)
    {}
    complex<int> dir;//direction
    complex<int> disp;//displacement
    i64 steps;
};


void create_next_ab(int ith, vector<move>& va, vector<move>& vb)
{
    //"a" → "aRbFR"
    assert(ith>= 1);
    if(ith==1) return;
    complex<int> right(0,-1), left(0,1);
    complex<int> dir1, disp1;
    dir1 = va[ith-1].dir;
    disp1 = va[ith-1].disp;
    dir1 *= right;
    disp1 += dir1 * vb[ith-1].disp;
    dir1 *= vb[ith-1].dir;
    disp1 += dir1;
    dir1 *= right;

    va[ith].dir = dir1;
    va[ith].disp = disp1;
    va[ith].steps = va[ith-1].steps + vb[ith-1].steps+1;

    //"b" → "LFaLb"
    dir1 = left;
    disp1 = dir1;
    disp1 += dir1*va[ith-1].disp;
    dir1 *= va[ith-1].dir;
    dir1 *= left;
    disp1 += dir1*vb[ith-1].disp;
    dir1 *= vb[ith-1].dir;

    vb[ith].dir = dir1;
    vb[ith].disp = disp1;
    vb[ith].steps = va[ith].steps;// same number of steps as va
}
void find_target(i64 csteps, int level, int ctype, complex<int> cdir, complex<int> cpos, i64 maxstep, 
        vector<move>& vda, vector<move>& vdb)
{
    complex<int> right(0,-1), left(0,1);
    if(csteps == maxstep){
        printf("%d %d %lld\n", cpos.real(), cpos.imag(), maxstep);
        return;
    }
    //"a" → "aRbFR"
    if(ctype == 0){//a type
        if(vda[level-1].steps + csteps > maxstep){
            //a is more than efficient so downgrade one level
            find_target(csteps, level-1, 0, cdir, cpos, maxstep, vda, vdb);
        }else{
            //a
            cpos += cdir*vda[level-1].disp;
            cdir *= vda[level-1].dir;               
            csteps += vda[level-1].steps;
            if(csteps == maxstep){
                printf("%d %d %lld\n", cpos.real(), cpos.imag(), maxstep);
                return;
            }

            //R
            cdir *= right;
            //b
            if(csteps + vdb[level-1].steps < maxstep){
                assert(csteps + vdb[level-1].steps + 1 == maxstep);
                cpos += vdb[level-1].disp*cdir;
                cdir *= vdb[level-1].dir;
                cpos += cdir;
                printf("%d %d %lld\n", cpos.real(), cpos.imag(), maxstep);
                return;
            }else{ // b is sufficient to cover the steps
                find_target(csteps, level-1, 1, cdir , cpos, maxstep, vda, vdb);
            }
        }
    }else{//b type
    //"b" → "LFaLb"
        cdir *= left;    
        cpos += cdir;
        csteps += 1;
        if(csteps == maxstep){
            printf("%d %d %lld\n", cpos.real(), cpos.imag(), maxstep);
            return;
        }
        if(csteps + vda[level-1].steps > maxstep ){
            find_target(csteps, level-1, 0, cdir, cpos, maxstep, vda, vdb);
        }else{
            // process a
            cpos += cdir * vda[level-1].disp;
            cdir *= vda[level-1].dir;
            csteps += vda[level-1].steps;
            if(csteps == maxstep){
                printf("%d %d %lld\n", cpos.real(), cpos.imag(), maxstep);
                return;
            }
            cdir *= left;
            find_target(csteps, level-1, 1, cdir, cpos, maxstep, vda, vdb);
        }
    }
}
int main()
{
    
    vector<move> vda, vdb;
    vda.resize(51);
    vdb.resize(51);
    //"a" → "aRbFR"
    //"b" → "LFaLb"
    vda[1].steps = 1;
    vda[1].dir=complex<int>(-1, 0);
    vda[1].disp = complex<int>(0, -1);

    vdb[1].steps = 1;
    vdb[1].disp = complex<int>(0, 1);
    vdb[1].dir = complex<int>(-1, 0);
    
    for(unsigned int i = 2; i< vda.size(); ++i)
        create_next_ab(i, vda, vdb);
    i64 maxstep = 1000000000000LL ;
    i64 step = 1;
    int level = 50;
    complex<int> cdisp=complex<int>(0,1);
    complex<int> dir = complex<int>(0,1);
    find_target(step, level, 0, dir, cdisp, maxstep, vda, vdb);
}
