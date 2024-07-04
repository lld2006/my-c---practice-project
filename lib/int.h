#ifndef GINT_H
#define GINT_H
#include "../lib/typedef.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
constexpr int kNum = 10000;
constexpr int dLen = 4;
class BigInt {
public:
  // this expedites the calculation since it makes full use of int32.
  // not sure if it is better to use int64
  const static int kMod = kNum;
  const static int DLEN = dLen;

  // default constructors
  BigInt() = default;

  // from integer
  BigInt(i64 num) {
    do {
      blocks_.push_back(num % kMod);
      num /= kMod;
    } while (num);
  }

  // from string
  BigInt(const string &s) {
    int d_length = (s.size() + DLEN - 1) / DLEN;
    blocks_.reserve(d_length);
    // we need to iterate backwards such that the last four digis in digits[0].
    for (int low_end = s.size() - 1; low_end >= 0; low_end -= DLEN) {
      int value = 0;
      int high_end = max(low_end - DLEN + 1, 0);
      for (int j = high_end; j <= low_end; ++j) {
        value = value * 10 + s[j] - '0';
      }
      blocks_.push_back(value);
    }
  }

  // copy constructor
  BigInt(const BigInt &gi) : blocks_(gi.blocks_) {};
  // operator overloadings
  BigInt &operator=(const BigInt &gi);

  bool operator==(const BigInt &g) const;

  bool operator<(const BigInt &gi) const;
  bool operator<=(const BigInt &gi) const;
  bool operator>(const BigInt &gi) const;
  bool operator>=(const BigInt &gi) const;

  BigInt operator+(const BigInt &g);
  BigInt &operator+=(const BigInt &g);

  BigInt operator*(const BigInt &right) const;
  BigInt &operator*=(const BigInt &g1);

  BigInt operator/(const BigInt &right) const;
  BigInt operator/(int num) const;
  BigInt &operator/=(const BigInt &g1);

  // TODO, use conversion is better!!!
  BigInt divide(const BigInt &denom,
                        BigInt &remainder) const;
  // int modulus(const int mod) const;
  // void truncate(const unsigned int size);
  // BigInt minus(const BigInt &g1) const;

  BigInt power(int n);
  // this is the way for print a large integer.
  operator std::string() const {
    string s;
    s.reserve(blocks_.size() * 4);
    for (int i = blocks_.size() - 1; i >= 0; --i) {
      auto tmp = std::to_string(blocks_[i]);
      s += tmp;
    }
    return s;
  }

  std::string to_string() {
    std::string s(*this);
    return s;
  }

private:
  vector<int> blocks_; // B_0, B_1, B_2,...,B_n-2, B_n-1;
};
#endif
