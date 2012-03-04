class rational
{
  public:
    rational():num(0), den(1) { };
    rational(i64 nx, i64 dx):num(nx), den(dx)
    {
        i64 common = gcd(num, den);
        if(common != 1){
            den /= common;
            num /= common;
        }
    };
    rational operator+(const rational& r2) const{
        return rational(num*r2.den+den*r2.num, den*r2.den);
    }
    i64 pnum()const {return num;} ;
    i64 pden()const {return den;} ;
  private:
    i64 num;
    i64 den;
};

