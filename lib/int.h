#ifndef GINT_H
#define GINT_H
#include <string>
#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"

using namespace std;

class GeneralInteger
{
public:
  //constructors
  GeneralInteger(const i64 num);
  GeneralInteger(const string& string);
  GeneralInteger(const vector<int>& nvec);
  //copy constructor
  GeneralInteger(const GeneralInteger& gi):number(gi.number) { };
  //operator overloadings
  GeneralInteger& operator=(const GeneralInteger& gi);
  bool operator< (const GeneralInteger& gi) const;
  GeneralInteger& operator+=(const GeneralInteger& g );
  GeneralInteger operator+(const GeneralInteger& g) ;
  bool operator==(const GeneralInteger& g) const;

  //accessors
  vector<int>& getNumber() {return number;}
  int getNthDigit (const int& n) const 
    {
        assert( n>= 0 && n < static_cast<int>(number.size()));
        if(n >= static_cast<int>(number.size()))
            return 0;
        else
            return number[n];
    };
  int numberDigit() const 
  {
      assert(!number.empty());
      return number.size();
  }
  void print(int endl = 0)const
  {
    for( int riter = static_cast<int>(number.size()-1); riter >= 0;  --riter){
        assert(number[riter] >= 0 && number[riter] < 10);
        printf("%d", number[riter]);
    }
    if(endl){printf("\n");}
  }
  int modulus(const int num) const;
  void truncate(const unsigned int size);
  GeneralInteger minus(const GeneralInteger& g1)const;
  GeneralInteger multiply(const GeneralInteger& g1)const;
  GeneralInteger power(int n);
  GeneralInteger divide(const GeneralInteger& denom, GeneralInteger& remainder) const;
  GeneralInteger divide(int den);
  i64 to_i64() const;
  void clear0();
private:
  vector<int> number;  //A_0, A_1, A_2,...,A_n-2, A_n-1;
  // clear trivial heading 0s
};
#endif
