#include "int.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

BigInt &BigInt::operator=(const BigInt &gi) {
  if (this != &gi)
    blocks_ = gi.blocks_;
  return *this;
}

// int BigInt ::modulus(const int num) const {
//   // TODO, use / operator
//   int residue = 0;
//   for (int riter = static_cast<int>(blocks_.size() - 1); riter >= 0; --riter)
//   {
//     residue = residue * 10 + blocks_[riter];
//     if (residue < num)
//       continue;
//     residue = residue % num;
//   }
//   return residue;
// }

BigInt &BigInt::operator*=(const BigInt &g1) {
  int size1 = blocks_.size();
  int size2 = g1.blocks_.size();
  assert(!g1.blocks_.empty());
  vector<int> result;
  result.resize(size1 + size2, 0);
  int carry = 0;
  for (int i1 = 0; i1 < size1; ++i1) {
    for (int i2 = 0; i2 < size2; ++i2) {
      result[i1 + i2] += blocks_[i1] * g1.blocks_[i2] + carry;
      carry = result[i1 + i2] / kMod;
      result[i1 + i2] %= kMod;
    }
  }
  if (carry)
    result.back() += carry;
  if (result.back() == 0 && result.size() > 1)
    result.pop_back();
  assert(result.back() != 0 || result.size() == 1);
  swap(blocks_, result);
  return *this;
}

// this operator+= need to be enhanced use resize instead of current method
// resize to maximum size instead of push_back
BigInt &BigInt::operator+=(const BigInt &g1) {
  auto &b = g1.blocks_;
  int vec_length = max(blocks_.size(), b.size());
  blocks_.resize(vec_length, 0);
  int carry = 0;
  for (int i = 0; i < vec_length; ++i) {
    auto ai = i < blocks_.size() ? blocks_[i] : 0;
    auto bi = i < b.size() ? b[i] : 0;
    ai += bi + carry;
    blocks_[i] = ai % kMod;
    carry = ai / kMod;
  }
  if (carry)
    blocks_.push_back(carry);

  return *this;
}

BigInt BigInt ::operator+(const BigInt &g) {
  BigInt ret(*this);
  ret += g;
  return ret;
}

bool BigInt::operator==(const BigInt &g) const {
  std::string sg(g);
  assert(blocks_.size() > 0 && g.blocks_.size() > 0);
  if (blocks_.size() != g.blocks_.size())
    return false;
  else { // same number of blocks
    int size = static_cast<int>(blocks_.size());
    for (int j = size - 1; j >= 0; --j) {
      if (blocks_[j] != g.blocks_[j])
        return false;
    }
  }
  return true;
}

// always assume this > g1, will generalize it later
// BigInt BigInt::minus(const BigInt &g1) const {
//   // the following assert is not sufficent enough
//   vector<int> result;
//   assert(g1.blocks_.size() > 0);
//   assert(blocks_.size() >= g1.blocks_.size());
//   int size = g1.blocks_.size();
//   int borrow = 0;
//   for (int i = 0; i < size; ++i) {
//     int fir = blocks_[i];
//     int sec = g1.blocks_[i];
//     int diff = fir - sec - borrow;
//     borrow = 0;
//     if (diff < 0) {
//       borrow = 1;
//       diff = diff + 10;
//     }
//     result.push_back(diff);
//   }
//   unsigned int j = size;
//   while (j < blocks_.size()) {
//     int tmp = blocks_[j] - borrow;
//     borrow = 0;
//     if (tmp < 0) {
//       tmp += 10;
//       borrow = 1;
//     }
//     result.push_back(tmp);
//     ++j;
//   }
//   assert(borrow == 0);
//   BigInt ret;
//   swap(ret.blocks_, result);
//   return ret;
// }

bool BigInt::operator<(const BigInt &gi) const {
  assert(gi.blocks_.size() > 0);
  assert(blocks_.size() > 0);
  if (blocks_.size() < gi.blocks_.size())
    return true;
  else if (blocks_.size() > gi.blocks_.size())
    return false;
  else { // equal blocks_ of digits
    for (int i = blocks_.size() - 1; i >= 0; --i) {
      if (blocks_[i] == gi.blocks_[i])
        continue;
      else if (blocks_[i] < gi.blocks_[i])
        return true;
      else
        return false;
    }
    return false;
  }
}
// this is ugly should be rewritten
BigInt BigInt::power(int n) {
  BigInt ret(1), base(*this);
  while (n) {
    if (n & 1) {
      ret *= base;
    }
    n >>= 1;
    base *= base;
  }
  return ret;
}

// leave remainder in the interface
// BigInt BigInt::divide (const BigInt &denom,
//                                       BigInt &remainder) const {
//   auto& n_vector = blocks_;   // u_0, u_1, ..., u_m+n-1
//   auto& d_vector(denom.blocks_); // v_0, v_1, ..., v_n-1
//   vector<int> qres;
//   // normalize to make the denominator first digit large! d0 <= 5
//   // if the blocks_ator first digit is large, then by this opeartion
//   // it should be small enough that the division in the loop is less
//   // then 10 times of v_n-1
//   int d0 = kMod / (d_vector.back() + 1);
//   int sn = n_vector.size();
//   int sd = d_vector.size();
//   assert(d0 >= 1);
//   if (d0 == 1)
//     n_vector.push_back(0);
//   else {
//     BigInt gd(d0);
//     numerator = numerator.multiply(gd);
//   }
//   if (numerator.blocks_Digit() == blocks_Digit())
//     numerator.Digits().push_back(0);
//   BigInt gd(d0);
//   denominator = denominator.multiply(gd);
//   // denominator size not changed
//   assert(denominator.blocks_Digit() == denom.blocks_Digit());
//   int j = sn - sd;
//   while (j >= 0) {
//     int nt = numerator.getNthDigit(j + sd) * 10;
//     nt += numerator.getNthDigit(j + sd - 1);
//     int qtilde = nt / denominator.getNthDigit(sd - 1);
//     int rtilde = nt - qtilde * denominator.getNthDigit(sd - 1);
//     bool needAdjust = true && denominator.blocks_Digit() > 1;
//     while (needAdjust) {
//       needAdjust =
//           (qtilde >= 10) || qtilde * denominator.getNthDigit(sd - 2) >
//                                 10 * rtilde + numerator.getNthDigit(j + sd -
//                                 2);
//       if (needAdjust) {
//         --qtilde;
//         rtilde += denominator.getNthDigit(sd - 1);
//       }
//     }
//     int carry = 0;
//     vector<int> &nv = numerator.getblocks_();
//     vector<int> &dv = denominator.getblocks_();
//     for (int k = 0; k < sd; ++k) {
//       nv[k + j] -= (qtilde * dv[k] + carry);
//       if (nv[k + j] < 0) {
//         carry = (-nv[k + j] + 9) / 10;
//         assert(carry >= 0);
//         nv[k + j] += carry * 10;
//         assert(nv[k + j] >= 0);
//       } else {
//         carry = 0;
//       }
//     }
//     nv[j + sd] -= carry;
//     if (nv[j + sd] >= 0) {
//       qres.push_back(qtilde);
//       --j;
//     } else {
//       nv[j + sd] += 10;
//       int carry = 0;
//       qres.push_back(qtilde - 1);
//       for (int k = 0; k < sd; ++k) {
//         nv[k + j] += dv[k] + carry;
//         if (nv[k + j] >= 10) {
//           carry = nv[k + j] / 10;
//           nv[k + j] -= 10 * carry;
//         } else {
//           carry = 0;
//         }
//       }
//       nv[j + sd] += carry;
//       assert(nv[j + sd] >= 10);
//       nv[j + sd] -= 10;
//       --j;
//     }
//   }
//   reverse(qres.begin(), qres.end());
//   vector<int> &nv = numerator.getblocks_();
//   int carry = 0;
//   for (unsigned int i = 0; i < nv.size(); ++i) {
//     nv[i] += carry;
//     if (nv[i] >= 10) {
//       carry = nv[i] / 10;
//       nv[i] %= 10;
//     } else {
//       carry = 0;
//     }
//   }
//   numerator = numerator.divide(d0);
//
//   BigInt gret(qres);
//   gret.clear0();
//   remainder.blocks_ = numerator.blocks_;
//   remainder.clear0();
//   return gret;
// }
BigInt BigInt::operator/(int den) const {
  assert(den > 0 && den < 10);
  vector<int> result;
  int value = 0;
  int remainder = 0;
  for (int i = blocks_.size() - 1; i >= 0; --i) {
    value = remainder * 10 + blocks_[i];
    int quotient = (value) / den;
    remainder = value % den;
    result.push_back(quotient);
  }
  reverse(result.begin(), result.end());
  BigInt ret;
  swap(ret.blocks_, result);
  return ret;
}
