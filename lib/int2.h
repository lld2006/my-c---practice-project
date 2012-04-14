#include <string>
#include <cstdio>
#include <vector>
#include <cassert>
#include "typedef.h"
#ifndef GINT_H
#define GINT_H
using namespace std;

class GeneralInteger
{
public:
  //constructors
  GeneralInteger(const int num);
  GeneralInteger( i64 num );
  GeneralInteger(const string& string);
  GeneralInteger(const vector<int>& nvec);
  //copy constructor
  GeneralInteger(const GeneralInteger& gi);
  //operator overloadings
  GeneralInteger& operator=(const GeneralInteger& gi);
  bool operator< (const GeneralInteger& gi) const;
  GeneralInteger& operator+=(const GeneralInteger& g );
  GeneralInteger  operator+ (const GeneralInteger& g ) const;
  GeneralInteger& operator*=(const GeneralInteger& g );
  GeneralInteger  operator* (const GeneralInteger& g ) const;
  bool operator==(const GeneralInteger& g) const;

  //accessors
  vector<int>& getNumber() {return numbers;}
  inline int getNthDigit (int n) const 
  {
      assert( n>= 0 && n < static_cast<int>(numbers.size()));
      return numbers[n];
  }
  inline int numberBlk() const 
  {
      assert(!numbers.empty());
      return numbers.size();
  }
  void print()const;
  int modulus(int num) const;
  void truncate(const unsigned int size);
  GeneralInteger minus(const GeneralInteger& g1)const;
  GeneralInteger multiply2(const GeneralInteger& g1) const;
  void power(int n);
  GeneralInteger divide(const GeneralInteger& denom, GeneralInteger& remainder) const;
  GeneralInteger divide(int den);
  i64 to_i64() const;
  static int nblk; // each number in vector is less than nblk, i.e. 4 digits
private:
  vector<int> numbers;  //A_0, A_1, A_2,...,A_n-2, A_n-1;
  // clear trivial heading 0s
  void clear0();
};
#endif
