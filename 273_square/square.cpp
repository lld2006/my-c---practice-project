#include "../lib/tools.h"
#include <cstdio>
#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;

vector<int> p1, va, vb;

void find_2_sq(int n, int& a, int& b)
{
    assert((n-1)%4 == 0);
    int root = sqrt(n);
    int i, j;
    bool found = false;
    for( i = 1; i < root; ++i){
        for(j = i+1; j <= root; ++j){
            if(i*i+j*j ==n){
                found = true;
                break;
            }
        }
        if(found) break;
    }
    a = i; 
    b = j;
    assert(a*a+b*b == n);
    return;
}
void search2(unsigned int pos, i64 a, i64 b, int cnt, i64& sum)//0 1
{
    if(pos == p1.size()){
        return;
    }
    search2(pos+1, a, b, cnt, sum);
    i64 c = va[pos];
    i64 d = vb[pos];
    i64 a1 = a*c - b*d;
    i64 b1 = a*d + b*c;
    if(a1 < 0)
        a1= -a1;
    if(a1 > b1)
        swap(a1, b1);
    search2(pos+1, a1, b1, cnt+1, sum);
    sum += a1;
    //if prime, only one solution needed
    if(cnt > 0){
        a1 = a*d-b*c;
        b1 = a*c+b*d;
        if(a1 < 0)
            a1 = -a1;
        if(a1 > b1)
            swap(a1, b1);
        search2(pos+1, a1, b1, cnt+1, sum);
        sum += a1;
    }
}
int main()
{
    int limit = 150;
    vector<int> primes;
    primeWithin(primes, limit);
    for(unsigned int i=0; i < primes.size(); ++i){
        if((primes[i] - 1)%4 ==0){
            p1.push_back(primes[i]);
        }
    }
    for(unsigned int i = 0; i < p1.size(); ++i){
        int a=0, b=0;
        find_2_sq(p1[i], a, b);
        va.push_back(a);
        vb.push_back(b);
    }
    assert(p1.size() == va.size());
    assert(p1.size() == vb.size());
    i64 sum = 0;
    search2(0, 0, 1, 0, sum);
    printf("%lld\n", sum);
}
