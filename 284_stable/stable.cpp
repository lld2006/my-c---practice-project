#include <cstdio>
#include "../lib/typedef.h"
//nd is the number of digits considered now, nd-1 is the existing ones
//if shifting is desired nd-1 should be used 
//the number is just opposite to our conventional usage, 0 is the last digit
void find_next_digit(vector<int>& v8, vector<int>& vsquare, int nd)
{
    //do not clear vsquare for efficiency
    vsquare.resize(2*nd+1, 0);
    vstp(vsquare);
    vector<int> vtp;     
    vtp.resize(v8.size() + 1+ nd - 1, 0 );
    for(unsigned int na = 1; na <= 13; ++na){
        for(unsigned int j = 0; j < v8.size(); ++j){
            vtp[j+3] = v8[j] * na;//initial value may be 
        }
    }
}
int main()
{
    vector<int> v8, vsquare;
    v8.push_back(8);//first digit;
    for(unsigned int i =2; i<=10000; ++i){
        find_next_digit(v8, vsquare); 
    }
    printf("%lld\n", total);
}
