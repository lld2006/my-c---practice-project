#include <set>
#include <vector>
#include <cstdio>
#include <cassert>
#include <numeric>
#include "../lib/tools.h"
#include "../lib/int.h"
using namespace std;

int sqsum(const int num, const int count)
{
    int sum = 0;
    assert( num >= count);
    for( int i = num ; i < num + count; ++i)
        sum += i*i;
    return sum;
}
int main()
{
    vector<int> squaresum;
    set<int> panset;
    int limit = 100000000;
    squaresum.resize(1818, 0);
    for(int i = 0; i<=1817; ++i){
        if(i%3==0|| i%3==2)
            squaresum[i] = i*(i+1)/6*(2*i+1); //up to i located in i-1
        else
            squaresum[i] = (i*(i+1)/2)*((2*i+1)/3); //up to i located in i-1
    }
    
    for( int i = 1818; i <=7071; ++i){
        int sum = i*i;
        int k = i;
        while( true ){
            --k;
            sum += k * k;
            if(sum > limit )break;
            assert(sum > 0);
            if(isPalindromic(sum, 10))
                panset.insert(sum);
        }
    }
    for(int i = 2; i <=1817; ++i)
        for(int j= i-2; j>=0; --j){
            int sum = squaresum[i]-squaresum[j];
            if(sum > limit )break;
            assert(sum > 0);
            if(isPalindromic(sum, 10))
                panset.insert(sum);
        }
    GeneralInteger total(0); 
    for(set<int>::iterator iter=panset.begin(); iter!= panset.end(); ++iter)
        total += *iter;
    total.print();
}

