#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/tools.h"
//this is the correct way to solve this problem
    int n1[] = {-2, -2, -1, -1, -1,  1, 2, -1, -1}; 
    int n2[] = {-1, -1,  0,  0, -1,  2, 1,  1,  1}; 
    int i1[] = {-1,  1, -1,  1,  1,  0, 1, -1,  1}; //row shift
    int i2[] = {-1,  1, -2,  2, -1, -1, 0,  0,  0}; 
vector<int> primes;
i64 row_start(i64 row)
{
    return row*(row-1)/2+1;
}

i64 check_row(int row)
{
    int rowsign = -1;
    if(row % 2 == 0) 
        rowsign = 1;

    vector<i64> vstart;
    for(int irow = row-2; irow <= row +3; ++irow)
        vstart.push_back(row_start(irow));

    int nsize = vstart[5]-vstart[0]; 
    vector<bool> vnum;
    vnum.resize(nsize, true);
    i64 n0= vstart[0];
    i64 nend = row_start(row+3)-1;
    //sieve 
    for(unsigned int i = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        if(px * px > nend){
            printf("break for %lld %d\n", px, row );
            break;
        } 
        
        i64 sfirst = (n0+px-1)/px*px-n0;
        for(int j = sfirst; j < nsize; j+=px)
            vnum[j] = false;
        
    }//sifting done;
    //now let us check
    i64 nshift2 = vstart[2]- vstart[0]; //shift between row2 and row0
    assert(row == vstart[3] -vstart[2]);
    
    vector<bool> flags;
    flags.resize(row, false);//number of values in row2
    i64 i0 = row_start(row)  & 1 ? 0: 1;
    for(int irow = i0; irow < row; irow+=2){
        if(!vnum[nshift2+irow])//not a prime number
            continue;
        
        //potential triples
        for(unsigned int i = 0; i < 9; ++i){
            i64 indexa, indexb;
            indexa = irow + i1[i];
            indexb = irow + i2[i];
            //check boundary
            if(indexa < 0 || indexa > row + n1[i])
                continue;
            if(indexb < 0 || indexb > row + n2[i])
                continue;

            if( vnum[vstart[rowsign*n1[i]+2]+indexa-vstart[0]] && vnum[vstart[rowsign*n2[i]+2]+indexb-vstart[0]]){
                flags[irow] = true;
                break;
            }
        }
    }
    i64 sum = 0; 
    for(unsigned int i = 0; i < flags.size(); ++i)
        if(flags[i]) sum += vstart[2] + i;
        
    return sum;
}
//deciding to use sift instead of prime detection algorithm
int main()
{
    i64 nmax = 7208785;
    int pmax = sqrt((nmax+1)*(nmax+2)/2);
    primeWithin(primes, pmax);
    i64 sum = 0;
    sum += check_row(7208785);
    sum += check_row(5678027);
    printf("%d  %lld\n",pmax, sum);
}

