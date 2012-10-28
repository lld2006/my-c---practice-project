#include <cassert>
#include "../lib/tools.h"
//internal rep, den num are all positive or 0; now considering negative rationals
//when I added negative sign to the class, the operator+ is not well defined, missed to assigne the sign
//when I introduced the operator- which is not defined before, to change the sign, I used a *= which should be =
class rational 
{
  public:
    rational():d_num(0), d_den(1), d_sign(1) { };
    rational(i64 nx, i64 dx=1, int pm=1):d_num(nx), d_den(dx), d_sign(pm)
    {
        if(nx < 0){
            d_num = -nx;
            d_sign = -d_sign;
        }
        if(dx < 0){
            d_den = -dx;
            d_sign = -d_sign;
        }
        i64 common = gcd(d_num, d_den);
        if(common != 1){
            d_den /= common;
            d_num /= common;
        }
    };
    //the following code need to be careful, overflow;
    rational operator+(const rational& r2) const
    {
        i64 common = gcd(r2.d_den, d_den);
        if(d_sign == r2.d_sign)
            return rational(d_num*(r2.d_den/common)+d_den/common*r2.d_num, d_den/common*r2.d_den, d_sign);
        else{
            i64 result = d_num*(r2.d_den/common)-d_den/common*r2.d_num;
            return rational(result, d_den/common*r2.d_den, d_sign);
        }
    }
    rational operator-(const rational& r2) const
    {
        rational r2t(r2);
        r2t.d_sign = -r2t.d_sign;
        return operator+(r2t);
    }

    rational& operator+=(const rational& r2){
        assert(0);
        i64 common = gcd(r2.d_den, d_den);
        if(d_sign == r2.d_sign){
            d_num = d_num*(r2.d_den/common)+d_den/common*r2.d_num;
        }else{
            d_num = d_num*(r2.d_den/common)-d_den/common*r2.d_num;
            if(d_num < 0){
                d_num = -d_num;
                d_sign = -d_sign;
            }
        }
        d_den *= (r2.d_den/common);
        common = gcd(d_num, d_den);
        if(common != 1){
            d_den /= common;
            d_num /= common;
        }
        return *this;
    }
    rational operator*(const rational& r2) const
    {
        return rational(d_num*r2.d_num, d_den*r2.d_den, d_sign==r2.d_sign? 1:-1);
    }
    rational operator/(const rational& r2)const
    {
        assert(r2.d_num > 0);
        return rational(d_num*r2.d_den, d_den*r2.d_num, d_sign==r2.d_sign?1:-1);
    }
    bool operator>(const rational& r2)const
    {
        assert(0);
        if(d_sign > r2.d_sign ){
            return d_num>0 || r2.d_num>0;//possible: d_num==0
        }else if(d_sign < r2.d_sign){
            return false; 
        }else{
            i64 diff = d_num*r2.d_den - d_den*r2.d_num;
            return d_sign? diff>0:d_sign<0;
        }
    }
    i64 pnum()const {return d_num;}
    i64 pden()const {return d_den;} 
    i64 psign() const {return d_sign;}
  private:
    i64 d_num;
    i64 d_den;
    int d_sign; //-1 for negative, 1 for positive
};
bool operator<(const rational& r1, const rational& r2)
{
   if(r1.psign() < r2.psign()){
       return !(r1.pnum()==0 && r2.pnum() == 0);
   }else if(r1.psign() > r2.psign()){
       return false;
   }else{
        i64 diff = r1.pnum()*r2.pden() - r1.pden()*r2.pnum();
        return r1.psign() ? diff < 0: diff > 0;
   }
}
class coord_less
{
// (0, 0 ) zero
// (pos, 0), (pos, inf)  1
// (0, pos), (-inf, pos) 2
// (neg, 0), (neg, -inf) 3
// (0, neg), (inf, neg)  4
public:
int quadrant(int num, int den ) const
//                x       y
{
   if(num == 0 )
   {
        if(den == 0) 
            return 0;
        else if ( den > 0 )
            return 2; // 0 1
        else
            return 4;  //0 -1
   }
   if(den == 0){
        if(num > 0)
            return 1; // 1 0
        else
            return 3; // -1 0
   }
   assert(num != 0 && den != 0);
   if ( num > 0){
       if(den > 0)
           return 1;
       else 
           return 4;

   }else{// num < 0
        if(den > 0)
            return 2;
        else
            return 3;
   }
}

public:
bool operator() (const IntPair& pair1, const IntPair& pair2)const 
{
   int q1 = quadrant(pair1.first, pair1.second); 
   int q2 = quadrant(pair2.first, pair2.second);
   if(q1 < q2)
       return true;
   else if ( q1 > q2)
       return false;
   else{
        assert(pair1.first * pair2.first >= 0);
        if( pair1.first > 0){
            bool ret = pair1.first* pair2.second > pair2.first * pair1.second;
            //printf("pair1 %d %d pair2 %d %d less? %d\n", pair1.first, pair1.second, 
            //        pair2.first, pair2.second, ret);
            return ret;
        } else {
            bool ret = pair1.first* pair2.second > pair2.first * pair1.second;
            //printf("pair1 %d %d pair2 %d %d less? %d\n", pair1.first, pair1.second, 
            //        pair2.first, pair2.second, ret);
            return ret;
        }
   }
   assert(0);
   return true;
}
};
