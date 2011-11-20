#include <string>
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
using namespace std;
int main(){
    string str("UDDDUdddDDUDDddDdDddDDUDDdUUDd");
    //string str("DdDddUUdDD");
    i64 limit = 1000000000000000LL;
    int size = str.size();
    i64 value = 1;
    i64 power = 1;
    for(int i= size-1; i >= 0; --i){
       if(str[i] == 'D'){
           value *= 3;
           power *= 3;
       }
       if(str[i]=='d'){
           power *= 3;
           value *= 3;
           ++value;
           if(value % 2 == 0)
               value /= 2;
           else
              value = (value +power)/2;
       }
       if(str[i]== 'U'){
           power *= 3;
           value *= 3;
           value -= 2;
           int vr = value % 4;
           if(vr == 0){
               value /= 4;
               continue;
           }
           int mult = (4-vr)%4;
           if(mult == 2) {
               value += power*2; 
               assert( value % 4 == 0);
               value /=4;
               continue;
           }
           int remainder = power %4;
           if(mult == remainder){
                value += power;
                assert(value %4 == 0);
                value /= 4;
           }else{
                value += power*3;
                assert(value %4 == 0);
                value /= 4;
           }
       }
    }
    i64 ratio = limit / power;
    i64 result = ratio * power + value;
    if(result < limit) 
        result += power;
    printf("value = %lld power %lld res %lld\n", value, power, result);
}
