#include "../lib/tools.h"
#include <cstdlib>
//comment, it seems that 441 by 441 is too big, what should I do?
//from and to a number of pair from x or y index
int oeindex(int maxn, int cn)
{
    assert(maxn < 6 && maxn >= 0);
    assert(cn <= maxn+1 && cn >= 0);
    return (maxn+1)*maxn/2+cn;
}

int Index1d(int eIndex, int oIndex)
{
    assert(oIndex >=0 && oIndex < 21);
    assert(eIndex >=0 && eIndex < 21);
    return eIndex * 21 + oIndex;
}

int matIndex(int x, int y)
{
    assert(0 <= x && x < 441);
    assert(0 <= y && y < 441);
    return 441 * x + y;
}

IntPair indexToXY(int index) //each is oIndex or eIndex
{
    assert(0 <= index && index < 441);
    return IntPair(index/21, index%21);
}

IntPair indexToMaxC(int index)
{
    IntPair p;
    if(index >= 15){
        p.first = 5;
        p.second = index - 15;
    }else if(index >= 10){
        p.first = 4;
        p.second = index - 10;
    }else if(index >= 6){
        p.first = 3;
        p.second = index - 6;
    }else if(index >= 3){
        p.first = 2;
        p.second = index - 3;
    }else if(index >=1){
        p.first = 1;
        p.second = index -1;
    }else{
        p.first = 0;
        p.second = index ;
    }
    return p;
}

vector<i64> createMatrix()
{
    vector<i64> vMat;
    int size = 441 * 441;
    vMat.resize(size , 0);
    for(int i = 0; i<441; ++i){
        IntPair p = indexToXY(i);// eIndex oIndex
        IntPair e = indexToMaxC(p.first);
        IntPair o = indexToMaxC(p.second);
        //add an even number
        if(e.second > 0){//acting on even-numbered even
            int eIndex  = oeindex(e.first, e.second-1);
            int nIndex = Index1d(eIndex, p.second);
            vMat[matIndex(nIndex, i)] += e.second;
        }
        if(e.second < 5){//acting on odd-numbered even
            int eIndex  = oeindex(e.first, e.second+1);
            int nIndex = Index1d(eIndex, p.second);
            vMat[matIndex(nIndex, i)] += e.first - e.second;
        }
        if(e.first < 5){//be able to increase a new digit
            //something is wrong here!!!!!!! 
            int eIndex = oeindex(e.first+1, e.second);
            int nIndex = Index1d(eIndex, p.second);
            vMat[matIndex(nIndex, i)] += 5 - e.first;
        }

        //add an odd number
        if(o.second > 0){//acting on even-numbered odd 
            int oIndex  = oeindex(o.first, o.second-1);
            int nIndex = Index1d(p.first,oIndex);
            vMat[matIndex(nIndex, i)] += o.second;
        }
        if(o.second < 5){//acting on odd-numbered odd
            int oIndex  = oeindex(o.first, o.second+1);
            int nIndex = Index1d(p.first, oIndex);
            vMat[matIndex(nIndex, i)] += o.first - o.second;
        }
        if(o.first < 5){//be able to increase a new digit
            int oIndex = oeindex(o.first+1, o.second);
            int nIndex = Index1d(p.first, oIndex);
            vMat[matIndex(nIndex, i)] += 5 - o.first;
        }
    }
    return vMat;
}
int main(int argc, char* argv[])
{
    i64 nmod = 100000007;
    int nx = 7;
    if(argc==2)
        nx = atol(argv[1]);
    vector<i64> vMatrix = createMatrix();
    vector<i64> result = matrix_power(vMatrix, nx, nmod, 441);
    vector<i64> rhs; 
    rhs.resize(441, 0);
    rhs[Index1d(oeindex(1,0), oeindex(0,0))] = 4;
    rhs[Index1d(oeindex(0,0), oeindex(1,0))] = 5;
    vector<i64> rrhs;
    rrhs.resize(441, 0);
    for(int i  = 0; i < 441; ++i){
        for(int j = 0; j< 441; ++j){
            rrhs[i] += result[441*i+j] * rhs[j];
            rrhs[i] %= nmod;
        }
    }
    i64 sum = 0;
    for(int eMax = 0; eMax<=5; ++eMax){
        int eIndex = oeindex(eMax, eMax);
        for(int oMax =0; oMax<=5; ++oMax){
            int oIndex = oeindex(oMax, 0);
            int index = Index1d(eIndex, oIndex);
            printf("%d %d %d %lld\n", eIndex, oIndex, index, rrhs[index]);
            sum += rrhs[index];
        }
    }
    printf("%lld\n", sum);
}
