#include <cassert>
#include <cstdio>
#include "../lib/tools.h"
#include <numeric>
#include <cstdlib>

int maxsam(int px, const vector<int>& transition){
    if( px < 10 ) return 0;
    vector<int> nall, npart;
    nall.reserve(8);
    npart.reserve(2);
    while(px > 0){
        int res = px % 10;
        nall.push_back(res);
        px /= 10;
    }
    int sum = accumulate(nall.begin(), nall.end(), 0);
    assert(sum < 100);
    int sum1 = sum;
    while(sum > 0){
        int res = sum % 10;
        npart.push_back(res);
        sum /= 10;
    }
    assert(nall.size() >= npart.size());
    nall.resize(npart.size());
    int xsum = 0;
    for(unsigned int i = 0; i < nall.size(); ++i){
        xsum += transition[index0(11, nall[i], 10)] + transition[index0(11, 10, npart[i])];
        xsum -= transition[index0(11, nall[i], npart[i])];
    }
    xsum += maxsam(sum1, transition);
    return xsum;
}

int main()
{
    vector<vector<int> > display;//display of 0 --> 9 and nothing as 10th
    display.resize(11);
    FILE* fp;
    fp = fopen("disp.txt","r");
    for(unsigned int i = 0; i < display.size(); ++i){
        display[i].resize(7, 0);
        fscanf(fp, "%d %d %d %d %d %d %d", &display[i][0], &display[i][1], &display[i][2], 
                &display[i][3], &display[i][4], &display[i][5], &display[i][6]);
    }
    fclose(fp);
    //      0    1   2   3   4   5   6
    //      ul   ur  bl  br  top mid bot
    // 0    1    1   1   1    1   0    1
    // 1    0    1   0   1    0   0    0
    // 2    0    1   1   0    1   1    1
    // 3    0    1   0   1    1   1    1
    // 4    1    1   0   1    0   1    0
    // 5    1    0   0   1    1   1    1
    // 6    1    0   1   1    1   1    1
    // 7    1    1   0   1    1   0    0
    // 8    1    1   1   1    1   1    1
    // 9    1    1   0   1    1   1    1 
    // off  0    0   0   0    0   0    0
    vector<int> transition; // used to find out number of transitions when number changed
    transition.resize(121, 0);
    for(unsigned int i = 0; i < 11; ++i)
        for(unsigned int j = 0; j < 11; ++j){
            int cnt = 0;
            for(unsigned int k = 0; k < 7; ++k){
                if(display[i][k] != display[j][k])
                    ++cnt;
            }
            transition[index0(11, i, j)] = cnt;
        }
    //int ix = maxsam(137, transition);
    //printf("test %d\n", ix);
    //exit(1);
    vector<int> primes;
    primeWithin(primes, 20000000);
    i64 diff=0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] < 10000000) continue;
        diff += maxsam(primes[i], transition);
    }
    printf("%lld\n", diff);
}
