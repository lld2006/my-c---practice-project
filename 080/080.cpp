#include "../lib/int.h"
#include <cstdlib>
#include <numeric>
#include <cmath>
#include "../lib/typedef.h"
int target = 1000;
using namespace std;
i64 check_period(i64 num, i64 root, vector<int>& vroot)
{
    vroot.clear();
    //initialization nt
    i64 nt = root;//nt is the number in the numerator
    assert(root*root < num);
    //negative sign is not included
    i64 stop = root * 2;
    i64 q = root; // the integer part for each step
    vroot.push_back(root);
    i64 period = 0;
    i64 den = 1; //initialization of denominator 
    while(q != stop){
        assert((num - nt * nt) % den == 0);
        den = (num - nt * nt)/den;
        q = (root + nt)/ den;
        vroot.push_back(q);
        nt =  q * den - nt;
        ++period;
    }
    assert(period + 1 == static_cast<int>(vroot.size()));
    return period;
}
int sum_of_digits(int num, vector<int>& vroot)
{
    GeneralInteger p0(vroot[0]);
    GeneralInteger q0(1);
    GeneralInteger p1(vroot[0]*vroot[1]+1);
    GeneralInteger q1(vroot[1]);
    GeneralInteger p2(1);
    GeneralInteger q2(1);

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    
    int s = 1%vsize;
    while(q2.numberDigit() < 502){
        int value = vroot[s];
        p2 = p1.multiply(value) + p0;
        q2 = q1.multiply(value) + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
        ++s;
        s%=vsize;
        //p2.print(1);
        //q2.print(1);
    }
    vector<int> v1;
    v1.resize(target+1, 0);
    v1.push_back(1);
    GeneralInteger g100(v1);
    p2 = p2.multiply(g100);
    p2 = p2.divide(q2, g100);
    //p2.print(1);
    vector<int>& vn(p2.getNumber());
    return accumulate(vn.end()-target, vn.end(), 0);
}
int main()
{
    int sum = 0;
    int limit = target;
    for( int i = 2; i< 100; ++i ){
       int root = (sqrt(i));
       if(root*root ==i) continue;
       vector<int> vroot;
       check_period(i , root, vroot);
       sum +=  sum_of_digits(i, vroot);
    }
    printf("%d \n", sum);
}
