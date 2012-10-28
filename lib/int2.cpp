# include "int2.h"
# include "tools.h"
# include <cassert>
# include <algorithm>
using namespace std;
// now I need to do some modification. A vector of numbers is not a bad idea, but each number is
// less than 10 is definitely a bad idea. Let us now changed the number to be anything less than
// 10000.

//extern void kara_mult(unsigned int nsize, int* a, int* b, int* ret);
int GeneralInteger::nblk = 10;
GeneralInteger::GeneralInteger(const GeneralInteger& gi):numbers(gi.numbers) 
{ }
GeneralInteger::GeneralInteger(const string & str)
{
    assert(0); //TODO
    unsigned int size = str.size();
    numbers.resize(size);
    for(unsigned int i=0; i<size; ++i)
        numbers[i]= str[size-1-i]-'0';
}

GeneralInteger::GeneralInteger(int num ){
    int n = num;
    if( n == 0)
        numbers.push_back(0);
    else
        while( n ) {
            int na = n;
            n /= nblk;
            int res = na - n * nblk;
            numbers.push_back(res);
        }
}

GeneralInteger::GeneralInteger( i64 num )
{
    numbers.clear();
    if( num == 0)
        numbers.push_back(0);
    else
        while( num ) {
            i64 na = num;
            num /= nblk;
            i64 res = na - num * nblk;
            numbers.push_back(res);
        }
}

GeneralInteger::GeneralInteger(const vector<int>& nvec):numbers(nvec) {}

GeneralInteger& GeneralInteger::operator=(const GeneralInteger& gi) {
    if(this != &gi)
        numbers = gi.numbers;
    
    return *this;
}

int GeneralInteger :: modulus(const int num) const
{
    assert(0);
    int residue = 0;
    for( int riter = static_cast<int>(numbers.size()-1); riter >= 0; --riter) {
      residue = residue *10+ numbers[riter];
      if(residue < num) continue;
      residue = residue % num;
    }
    return residue;
}

GeneralInteger& GeneralInteger::operator*=(const GeneralInteger& g1)
{
    assert(!g1.numbers.empty());
    int size1 = numbers.size();
    int size2 = g1.numbers.size();
    vector<int> vec1(numbers);
    numbers.clear();
    numbers.resize(size1+size2, 0);
    for(int i1 = 0; i1< size1; ++i1){
        for(int i2 = 0; i2 < size2; ++i2){
            numbers[i1+i2] += vec1[i1]*g1.numbers[i2];
        }
    }
    int carry = 0;
    for(int i =0; i< size1+size2; ++i){
        numbers[i]+= carry;
        carry = numbers[i] / nblk;
        numbers[i] -=  nblk * carry;
    }
    clear0();
    return *this;
}

GeneralInteger GeneralInteger::multiply2(const GeneralInteger& g1) const
{
    assert(0);
    unsigned int size2 = numbers.size()> g1.numbers.size()?numbers.size(): g1.numbers.size();
    unsigned int maxsize = 1;
    while(maxsize < size2){
        maxsize = (maxsize << 1);
    }

    unsigned int max6 = maxsize * 6;
    int *ret = new int[max6];
    int *na = new int[maxsize];
    int *nb = new int[maxsize];

    for(unsigned int i = 0; i < maxsize; ++i){
        na[i] = 0; 
        nb[i] = 0;
    }
    for(unsigned int i = 0; i < numbers.size(); ++i)
        na[i] = numbers[i];
    for(unsigned int i = 0; i < g1.numbers.size(); ++i)
        nb[i] = g1.numbers[i];
    for(unsigned int i = 0; i < max6; ++i)
        ret[i] = 0;

    kara_mult(static_cast<int>(maxsize), na, nb, ret);
    unsigned int max2 = maxsize * 2, carry = 0;
    for(unsigned int i = 0 ; i < max2; ++i){
        ret[i] += carry;
        carry = 0;
        if( ret[i] < 0 ){
            carry = -(-(ret[i]+1)/10+1);
            ret[i] -= carry * 10;
        }else if(ret[i] >= 10){
            carry = ret[i]/10;
            ret[i] -= carry * 10;
        }
    }
    vector<int> vres;
    vres.resize(max2, 0);
    unsigned int last = 0;
    for(unsigned int i = 0; i < max2; ++i){
        if(ret[i]){
            vres[i] = ret[i];
            last = i;
        }
    }
    if(last + 1 < max2)
        vres.resize(last +1);
    delete [] ret;
    delete [] na;
    delete [] nb;

    GeneralInteger gret(vres);
    return gret;
}


//this operator+= need to be enhanced use resize instead of current method
//resize to maximum size instead of push_back
GeneralInteger& GeneralInteger::operator+=(const GeneralInteger& g1 )
{
    int sum, carry=0;
    unsigned int sumDigit = max(numberBlk(), g1.numberBlk());
    vector<int> vec2(g1.numbers);
    if(numbers.size() < sumDigit)
        numbers.resize(sumDigit, 0);
    if(vec2.size() < sumDigit)
        vec2.resize(sumDigit, 0);
    for(unsigned int i = 0; i< sumDigit; ++i){
        sum = numbers[i] + vec2[i]+carry;
        assert( 0 <= sum && sum < nblk << 1);
        if ( sum >= nblk ) {
            carry = 1;
            sum -= nblk;
        }else{
            carry = 0;
        }
        numbers[i] = sum;
    }

    if( carry )
        numbers.push_back( carry );
    return *this;
}

GeneralInteger GeneralInteger::operator* (const GeneralInteger& g) const
{
    GeneralInteger ret(*this);
    ret *= g;
    return ret;
}

GeneralInteger GeneralInteger::operator+ (const GeneralInteger& g ) const
{
    GeneralInteger ret(*this);
    ret += g;
    return ret;
}

void GeneralInteger::truncate( const unsigned int size)
{
    if (numbers.size()> size)
        numbers.resize(size);
}

bool GeneralInteger::operator==(const GeneralInteger& g) const
{
    assert(numbers.size()>0 && g.numbers.size()>0);
    return (numbers == g.numbers);
}

void GeneralInteger::clear0()
{
    while(numbers.size() > 1 && numbers.back() == 0)
        numbers.pop_back();
}

//always assume this > g1, will generalize it later
GeneralInteger GeneralInteger::minus(const GeneralInteger& g1)const{
    //the following assert is not sufficent enough
    vector<int> result;
    assert(g1.numberBlk() > 0);
    assert(numberBlk() >= g1.numberBlk());
    int size = g1.numberBlk();
    int borrow = 0;
    for( int i = 0; i < size; ++i){
        int fir = numbers[i];
        int sec = g1.numbers[i];
        int diff = fir -sec-borrow;
        borrow = 0;
        if(diff < 0){
            borrow = 1;
            diff= diff +10;
        }
        result.push_back(diff);
    }
    unsigned int j = size;
    while(j < numbers.size()){
        int tmp = numbers[j] - borrow;
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
    ret.clear0(); // remove unnecessary leading zeros
    return ret;
}

//this is kind of different with stdlib keep it.
bool GeneralInteger::operator<(const GeneralInteger& gi)const{
    assert(gi.numbers.size() > 0);
    assert(numbers.size() > 0);
    if ( numbers.size() < gi.numbers.size()) return true;
    else if(numbers.size() > gi.numbers.size()) return false;
    else{//equal number of digits
        for(int i = numbers.size() - 1; i >= 0; --i){
            if(numbers[i] == gi.numbers[i]) 
                continue;
            else if(numbers[i]< gi.numbers[i])
                return true;
            else
                return false;

        }
        return false;
    }
}


void GeneralInteger::power(int n) {
    assert(0);
    //need to be rewritten
    GeneralInteger g1(*this);
    for(int i = 1; i< n; ++i){
        (*this) *= g1;           
    }
}

//leave remainder in the interface
GeneralInteger GeneralInteger::divide(const GeneralInteger& denom, GeneralInteger& remainder) const
{
    GeneralInteger numerator(*this);   //u_0, u_1, ..., u_m+n-1
    GeneralInteger denominator(denom); //v_0, v_1, ..., v_n-1
    vector<int> qres;
    //normalize to make the denominator first digit large! d0 <= 5
    //if the numberator first digit is large, then by this opeartion 
    //it should be small enough that the division in the loop is less
    //then 10 times of v_n-1
    int d0 = 10 / (denominator.numbers.back()+1);
    int sn = numerator.numberBlk();
    int sd = denominator.numberBlk();
    assert( d0 >= 1 );
    if(d0 == 1)
        numerator.numbers.push_back(0);
    else{
        GeneralInteger gd(d0);
        numerator *= gd;
    }
    if(numerator.numberBlk() == numberBlk())
        numerator.getNumber().push_back(0);
    GeneralInteger gd(d0);
    denominator *= gd;
    //denominator size not changed
    assert(denominator.numberBlk() == denom.numberBlk());
    int j =  sn - sd;
    while(j >= 0){
        int nt = numerator.getNthDigit(j + sd) * 10;   
        nt += numerator.getNthDigit(j+sd-1);
        int qtilde = nt/denominator.getNthDigit(sd-1);
        int rtilde = nt - qtilde * denominator.getNthDigit(sd-1);
        bool needAdjust= true && denominator.numberBlk() > 1;
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
    remainder.numbers = numerator.numbers;
    remainder.clear0();
    return gret;
}
GeneralInteger GeneralInteger::divide(const int den){
    assert(den > 0 && den < 10);
    vector<int> result;
   int value = 0;
   int remainder = 0;
   for( int i = numbers.size() -1 ; i >=0; --i){
       value = remainder*10+numbers[i];
       int quotient = (value) /den;
       remainder = value%den;
       result.push_back( quotient );
   }
   reverse(result.begin(), result.end());
   GeneralInteger ret(result);
   ret.clear0();
   return ret;
}
i64 GeneralInteger::to_i64() const
{
    //assert(numbers.size() * 4 <= 19); //do not overflow
    i64 ret = 0;
    for(int i = numbers.size()-1; i >= 0; --i){
        ret *= nblk;
        ret += numbers[i];
    }
    return ret;
}

void GeneralInteger::print()const
{
   // assert(0);
  for( int riter = static_cast<int>(numbers.size()-1); riter >= 0;  --riter){
      assert(numbers[riter] >= 0 && numbers[riter] < 10);
      printf("%d", numbers[riter]);
  }
  printf("\n");
}
