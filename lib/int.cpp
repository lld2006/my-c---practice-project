# include "int.h"
# include <cassert>
# include <algorithm>
# ifdef GINT_H
using namespace std;
// lesson be careful about size and '0' convention(array start from 0)
// lesson getNthDigit assert  when n > numberDigit
// lesson multiply process is not clear in mind, should start from top digit
// lesson when do add, it is not good to set the size of "ret" greater than
// the size of this by 1, if ret's size is greater than this, bug.
//
// operator += is not well written, should consider the size of this and gi
// consider three different situations.
// fixed two bugs, first divide --j part need to be set for both if and else branch
// second when want to convert a negative number to a positive number by +carry*10,
// need to use (-number+9)/10, number < 0
// lesson, operator== is illdefined, I myself forgot the rule of return, use more reasonable
// definition now.
GeneralInteger::GeneralInteger(const string & str)
{
    unsigned int size = str.size();
    number.resize(size);
    for(unsigned int i=0; i<size; ++i)
        number[i]= str[size-1-i]-'0';
}

GeneralInteger::GeneralInteger(const int num ){
    number.clear();
    int n = num;
    if( n == 0)
        number.push_back(0);
    else
        while( n ) {
            int res = n % 10;
            number.push_back(res);
            n /= 10;
        }
}

GeneralInteger::GeneralInteger(const vector<int>& nvec):number(nvec) {}

GeneralInteger& GeneralInteger::operator=(const GeneralInteger& gi) {
    if(this != &gi)
        number = gi.number;
    
    return *this;
}

int GeneralInteger :: modulus(const int num) const
{
    int residue = 0;
    for( int riter = static_cast<int>(number.size()-1); riter >= 0; --riter) {
      residue = residue *10+ number[riter];
      if(residue < num) continue;
      residue = residue % num;
    }
    return residue;
}

GeneralInteger GeneralInteger::multiply(const GeneralInteger& g1)const{
    assert(!g1.number.empty());
    int size1 = number.size();
    int size2 = g1.number.size();
    vector<int> result;
    result.resize(size1+size2, 0);
    for(int i1 = 0; i1< size1; ++i1){
        if(number[i1] == 0) continue;
        for(int i2 = 0; i2 < size2; ++i2){
            result[i1+i2] += number[i1]*g1.number[i2];
        }
    }
    int carry = 0;
    for(int i =0; i< size1+size2; ++i){
        result[i]+= carry;
        carry = result[i] / 10;
        result[i] = result[i]%10;
    }
    GeneralInteger ret(result);
    ret.clear0();
    return ret;
}

//this operator+= need to be enhanced use resize instead of current method
//resize to maximum size instead of push_back
GeneralInteger& GeneralInteger::operator+=(const GeneralInteger& g1 )
{
    int sum, res, incre=0;
    int sumDigit = min(numberDigit(), g1.numberDigit());
    for(int i = 0; i< sumDigit; ++i){
        sum = getNthDigit(i) + g1.getNthDigit(i)+incre;
        res = sum %10;
        incre = sum/10;
        number[i] = res;
    }

    if(numberDigit() > g1.numberDigit()){
        if(incre) {
            for(int i = g1.numberDigit(); i < numberDigit(); ++i){
                sum = getNthDigit(i) + incre;
                res = sum % 10;
                number[i] = res;
                incre = sum / 10;
                if(incre == 0) break;
            }
        }
    }else if(g1.numberDigit() > numberDigit()){
        for( int i = numberDigit(); i < g1.numberDigit(); ++i){
            sum = g1.getNthDigit(i) + incre;
            res = sum % 10;
            number.push_back(res);
            incre = sum / 10;
        }
    }
    if( incre )
        number.push_back( incre );
    return *this;
}

GeneralInteger GeneralInteger ::operator+ (const GeneralInteger& g )
{
    GeneralInteger ret(*this);
    ret += g;
    return ret;
}

void GeneralInteger::truncate( const unsigned int size)
{
    if (number.size()> size)
        number.resize(size);
}

bool GeneralInteger::operator==(const GeneralInteger& g) const
{
    assert(number.size()>0 && g.number.size()>0);
    if(numberDigit() > g.numberDigit())
        return 0;
    else if (numberDigit() < g.numberDigit())
        return 0;
    else // same number of digit
    {
        int size = static_cast<int>(number.size());
        for (int j = size -1; j >= 0; --j)
        {
            int diff = getNthDigit(j) - g.getNthDigit(j);
            if(diff == 0)
                continue;
            else if ( diff > 0)
                return 0;
            else 
                return 0;
        }
    }
    return 1;    
}

void GeneralInteger::clear0()
{
    while(number.size() > 1 && number.back() == 0)
        number.pop_back();
}

//always assume this > g1, will generalize it later
GeneralInteger GeneralInteger::minus(const GeneralInteger& g1)const{
    //the following assert is not sufficent enough
    vector<int> result;
    assert(g1.numberDigit() > 0);
    assert(numberDigit() >= g1.numberDigit());
    int size = g1.numberDigit();
    int borrow = 0;
    for( int i = 0; i < size; ++i){
        int fir = number[i];
        int sec = g1.number[i];
        int diff = fir -sec-borrow;
        borrow = 0;
        if(diff < 0){
            borrow = 1;
            diff= diff +10;
        }
        result.push_back(diff);
    }
    unsigned int j = size;
    while(j < number.size()){
        int tmp = number[j] - borrow;
        borrow = 0;
        if(tmp < 0){
            tmp += 10;
            borrow = 1;
        }
        result.push_back(tmp);
        ++j;
    }
    assert(borrow == 0);
    GeneralInteger ret(result);
    ret.clear0();
    return ret;
}

bool GeneralInteger::operator<(const GeneralInteger& gi)const{
    assert(gi.number.size() > 0);
    assert(number.size() > 0);
    if ( number.size() < gi.number.size()) return true;
    else if(number.size() > gi.number.size()) return false;
    else{//equal number of digits
        for(int i = number.size() - 1; i >= 0; --i){
            if(number[i] == gi.number[i]) 
                continue;
            else if(number[i]< gi.number[i])
                return true;
            else
                return false;

        }
        return false;
    }
}
void GeneralInteger::power(int n) {
    GeneralInteger g1(*this);
    for(int i = 1; i< n; ++i){
        *this = multiply(g1);           
    }
}

//leave remainder in the interface
GeneralInteger GeneralInteger::divide(const GeneralInteger& denom, GeneralInteger& remainder) const{
    GeneralInteger numerator(*this);   //u_0, u_1, ..., u_m+n-1
    GeneralInteger denominator(denom); //v_0, v_1, ..., v_n-1
    vector<int> qres;
    //normalize to make the denominator first digit large! d0 <= 5
    //if the numberator first digit is large, then by this opeartion 
    //it should be small enough that the division in the loop is less
    //then 10 times of v_n-1
    int d0 = 10 / (denominator.number.back()+1);
    int sn = numerator.numberDigit();
    int sd = denominator.numberDigit();
    assert( d0 >= 1 );
    if(d0 == 1)
        numerator.number.push_back(0);
    else{
        GeneralInteger gd(d0);
        numerator = numerator.multiply(gd);
    }
    if(numerator.numberDigit() == numberDigit())
        numerator.getNumber().push_back(0);
    GeneralInteger gd(d0);
    denominator = denominator.multiply(gd);
    //denominator size not changed
    assert(denominator.numberDigit() == denom.numberDigit());
    int j =  sn - sd;
    while(j >= 0){
        int nt = numerator.getNthDigit(j + sd) * 10;   
        nt += numerator.getNthDigit(j+sd-1);
        int qtilde = nt/denominator.getNthDigit(sd-1);
        int rtilde = nt - qtilde * denominator.getNthDigit(sd-1);
        bool needAdjust= true && denominator.numberDigit() > 1;
        while( needAdjust){
            needAdjust = (qtilde>= 10) || 
            qtilde * denominator.getNthDigit(sd-2)>10*rtilde+numerator.getNthDigit(j+sd-2);
            if(needAdjust){
                --qtilde;
                rtilde += denominator.getNthDigit(sd-1);
            }
        }
        int carry = 0;
        vector<int>& nv = numerator.getNumber();
        vector<int>& dv = denominator.getNumber();
        for(int k = 0; k < sd; ++k){
            nv[k+j] -= (qtilde * dv[k] +carry);
            if(nv[k+j] <0){
                carry = (-nv[k+j]+9)/10;
                assert(carry >= 0);
                nv[k+j] += carry * 10;
                assert(nv[k+j] >=0);
            }else{
                carry = 0;
            }
        }
        nv[j+sd]-=carry;
        if(nv[j+sd] >= 0){
            qres.push_back(qtilde);
            --j;
        }else{
            nv[j+sd] += 10;
            int carry = 0;
            qres.push_back(qtilde-1);
            for(int k =0; k < sd; ++k){
                nv[k+j] += dv[k]+carry;
                if(nv[k+j] >= 10){
                    carry = nv[k+j]/10;
                    nv[k+j] -= 10*carry;
                }else{
                    carry = 0;
                }
            }
            nv[j+sd] += carry;
            assert(nv[j+sd] >=10);
            nv[j+sd] -= 10;
            --j;
        }
    }
    reverse(qres.begin(), qres.end());
    vector<int>& nv = numerator.getNumber();
    int carry = 0;
    for(unsigned int i = 0; i< nv.size(); ++i){
        nv[i] += carry;
        if(nv[i] >= 10){
            carry = nv[i]/10;
            nv[i] %= 10;
        }else{
            carry = 0;
        }
    }
    numerator=numerator.divide(d0);

    GeneralInteger gret(qres);
    gret.clear0();
    remainder.number = numerator.number;
    remainder.clear0();
    return gret;
}
GeneralInteger GeneralInteger::divide(const int den){
    assert(den > 0 && den < 10);
    vector<int> result;
   int value = 0;
   int remainder = 0;
   for( int i = number.size() -1 ; i >=0; --i){
       value = remainder*10+number[i];
       int quotient = (value) /den;
       remainder = value%den;
       result.push_back( quotient );
   }
   reverse(result.begin(), result.end());
   GeneralInteger ret(result);
   ret.clear0();
   return ret;
}
#endif
