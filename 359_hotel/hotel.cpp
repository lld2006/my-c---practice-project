#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
i64 mod = 100000000;
i64 mod8 = 800000000;
void create_f4_for_floor_n(i64 floor, vector<i64>& v4, bool debug)
{
    v4.clear();
    if(floor == 1){
        v4.push_back(1);
        v4.push_back(3);
        v4.push_back(6);
        v4.push_back(10);
        return;
    }
    floor %= (mod8);
    if(floor %2 == 1){
        i64 value = (floor*floor-1)/2;
        value %= mod8; 
        v4.push_back(value);
        i64 nsq = floor;
        for(i64 i = 1; i < 4; ++i, ++nsq){
            value = nsq*nsq - v4.back(); 
            value %= mod8;
            v4.push_back(value);
        }
    }else{
        i64 value = floor*floor/2;
        value %= mod8;
        v4.push_back(value);
        i64 nsq = floor+1;
        for(i64 i = 1; i < 4; ++i, ++nsq){
            value = nsq*nsq-v4.back();
            value %= mod8;
            v4.push_back(value);
        }
    }
    assert(v4.size() == 4);
    if(debug){
        printf("floor %lld\n",floor);
        for(unsigned int i = 0; i < v4.size(); ++i){
            printf("%lld ", v4[i]);
        }
        printf("\n");
    }
}
i64 val(vector<i64>& c4, i64 n)
{    
    n %= (mod*8);
    i64 mod1 = 8*mod;
    i64 sum = 0;
    if( n%2 == 0)
       sum = c4[3] + c4[0];
    else
       sum = c4[3] - c4[0];
    i64 tp = c4[2]*n;
    sum += tp;
    sum %= mod1;
    tp = n*n;
    tp %= mod;
    tp *= c4[1];
    sum += tp;
    sum %= mod1;
    assert(sum % 8 == 0);
    sum /= 8;
    if(sum < 0) sum += mod;
    return sum;
}
//actually 8 times what we expected, so mod is different;
void find_coefficients(const vector<i64>& v4, vector<i64>& c4, bool debug)
{
    c4.clear();
    i64 coeff=v4[3]-3*v4[2]+3*v4[1]-v4[0];
    coeff %= (mod*8);
    c4.push_back(coeff);
    coeff = 2*(v4[3]-v4[2]-v4[1]+v4[0]);
    coeff %= (mod*8);
    c4.push_back(coeff);
    coeff = 4*(3*v4[2]+2*v4[1]-2*v4[3]-3*v4[0]);
    coeff %= (mod*8);
    c4.push_back(coeff);
    coeff = 7*v4[3]-13*v4[2]-3*v4[1]+17*v4[0];
    coeff %= (mod*8);
    c4.push_back(coeff);
    if(debug){
        for(i64 i= 1; i <= 4; ++i){
            printf("%lld    ", val(c4, i));
        }
        printf("\n");
    }
}
i64 find_value(i64 floor, i64 room)
{
    bool debug = false;
    vector<i64>  v4, c4;
    create_f4_for_floor_n(floor, v4, debug);
    find_coefficients(v4, c4, debug);
    i64 ret = val(c4, room);
    assert(ret > 0);
    return ret;
}
int main()
{
    i64 nv = 71328803586048;
    i64 sum = 0;
    for(i64 i = 0; i <=27; ++i)
        for(i64 j = 0; j <= 12; ++j){
            i64 v2 = power(2LL, i);
            i64 v3 = power(3LL, j);
            i64 floor = v2*v3;
            i64 room = nv/floor;
            assert(floor*room==nv);
            sum += find_value(floor, room);
            printf("%lld %lld %lld\n",i,j, sum);
        }
    printf("%lld\n",sum%mod);
    printf("%lld\n", find_value(929,934));
}
