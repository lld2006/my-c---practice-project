#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
//this problem is nice, it is very easy to make mistakes. 
//first the numbers should start with leading zeros!!!
//second, multiplier "1" is kind of special, it is better to 
// figure them out alone. the rest of  them are easy to calculate
int get_last_5(const vector<int>& vec){
    assert(vec.size() >= 5);
    int sum = 0;
    for( int i = 4; i >= 0; --i)
        sum = sum * 10+ vec[i] ;
    return sum;
}
void printvec (const vector<int>& vec){
    for(unsigned int n = 0; n < vec.size(); ++n){
        printf("%d", vec[n]);
    }
    printf("  %u\n", vec.size());
}
int main(){
    vector<vector<vector<int> > > rdata;
    rdata.resize(10);
    i64 sum  = 45*(1233+11111*96);
    for(int mult = 2; mult<=9; ++mult){
        for(int ld = 1; ld<=9; ++ld){//when last digit equals multiply result
                                     //result is found
           int l5 = ld; 
           int digit = 1; 
           int current = ld;
           int carry = 0;
           bool valid = false;
           vector<int> vt;
           vt.push_back(ld);
           while(digit < 100){
                ++digit; //current digit
                current = current * mult + carry; //
                carry = current/10; 
                current = current % 10; //real current digit
                if(digit <= 5){
                    l5 += power(10, digit-1)*current;
                }
                if(current == ld && carry == 0){
                    valid = true;
                    break;
                }
                else
                    vt.push_back(current);
           }
           if(!vt.empty() && valid && vt.back() != 0)
                rdata[mult].push_back(vt);
        }
    }
    for(int mult = 2; mult <=9; ++mult){
        printf("mult ===== %d\n", mult);
        for(unsigned int i = 0; i< rdata[mult].size(); ++i){
            printvec(rdata[mult][i]);
            int tvalue = get_last_5(rdata[mult][i]);
            int cnt = 100 / rdata[mult][i].size();
            sum += cnt * tvalue;
        }
    }
    sum %= 100000;
    printf("%lld\n",sum);
}
