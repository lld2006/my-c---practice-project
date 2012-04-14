#include <cassert>
#include "../lib/tools.h"
class rational //negative rational number is not considered yet
{
  public:
    rational():d_num(0), d_den(1) { };
    rational(i64 nx, i64 dx=1):d_num(nx), d_den(dx)
    {
        i64 common = gcd(d_num, d_den);
        if(common != 1){
            d_den /= common;
            d_num /= common;
        }
    };
    rational operator+(const rational& r2) const
    {
        return rational(d_num*r2.d_den+d_den*r2.d_num, d_den*r2.d_den);
    }
    rational operator*(const rational& r2) const
    {
        return rational(d_num*r2.d_num, d_den*r2.d_den);
    }
    rational operator/(const rational& r2)
    {
        assert(r2.d_num > 0);
        return rational(d_num*r2.d_den, d_den*r2.d_num);
    }
    bool operator<(const rational& r2)
    {
       return d_num*r2.d_den < d_den*r2.d_num;
    }
    bool operator>(const rational& r2)
    {
        return d_num*r2.d_den > d_den*r2.d_num;
    }
    i64 pnum()const {return d_num;} ;
    i64 pden()const {return d_den;} ;
  private:
    i64 d_num;
    i64 d_den;
};
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
