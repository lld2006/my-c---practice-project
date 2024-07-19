#include "tools.h"
#include "typedef.h"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <numeric>
#include <sys/time.h>
#include <unordered_set>
#include <vector>

using namespace std;
// here I tried some other possibility like char or short
// but bool has the best performance
namespace {
using i64 = long long int;

// pi is a very small prime number
// number is now less than 2^32;
// p-1 = odd *2^power_of_two
bool strong_pseudo_test_int(i64 pi, i64 odd, i64 power_of_two, i64 p) {
  if (pi == p)
    return true;
  bool is_strong_pseudo_prime = true;
  i64 result = powermodule(pi, odd, p);
  if (result == 1)
    return is_strong_pseudo_prime;
  else if (result == p - 1)
    return is_strong_pseudo_prime;
  else {
    i64 prod = result;
    // the last one should be 1, and the number before the
    // the first 1 should be negative 1
    for (unsigned int j = 1; j < power_of_two; ++j) {
      prod = mult64mod(prod, prod, p);
      if (prod == p - 1)
        return is_strong_pseudo_prime;
    }
  }
  return !is_strong_pseudo_prime;
}

} // namespace

vector<int> primeWithin(const int limit) {
  std::vector<int> primes;
  if (limit == 1)
    return primes;
  int odd = (limit + 1) / 2;
  vector<bool> vec; // for i >=1 number represent 2i+1 assume all prime
  vec.resize(odd, true);
  vec[0] = 0;
  int ip = 1; // prime number from 2 3 5 ....
  int iprime = 3;
  int max = sqrt((double)limit) + 1;
  while (iprime <= max) {
    // sieve
    for (int i = (iprime * iprime - 1) / 2; i < odd; i += iprime)
      vec[i] = false;
    // find next prime
    while (!vec[++ip])
      ;

    iprime = 2 * ip + 1;
  }
  primes.push_back(2);
  int nx = accumulate(vec.begin(), vec.end(), 0);
  primes.reserve(nx + 1);
  for (int i = 1; i < odd; ++i)
    if (vec[i])
      primes.push_back(2 * i + 1);
  return primes;
}

vector<int> sievePrimes(int limit) { return primeWithin(limit); }

// with prime list
bool isPrime(u64 num, vector<int> &primes) {
  if (num < 2)
    return false;
  if (num == 2)
    return true;
  int root = round(sqrt((double)num) + 1);
  // this assert should be guarranted.
  assert(primes.back() >= root);
  u64 value = num;
  int pk = 0;
  bool factorNotFound = true;
  while (factorNotFound) {
    int remainder = value % primes[pk];
    if (remainder == 0)
      return false;
    ++pk;
    if (primes[pk] >= root)
      return true;
  }
  return true;
}

// pollard rho prime
// check return values, if non-zero, factor, else return 0, not composite
// the original version of this function is kind of brute force.
// I will try the unordered map way
i64 pollard_rho(i64 n, int n0, int debug) {
  typedef std::unordered_set<i64> hashset;
  hashset hset;

  i64 limit = 2000;
  i64 i = 1;
  i64 x = n0;
  i64 y = x;
  i64 k = 2;
  int iter = 0;
  hashset::iterator hiter;
  while (iter != limit) {
    ++i;
    ++iter;
    // check paper: compute A*B mod N efficiently in ansi c
    if (x > 1000000000LL) {
      double dn = n;
      double dx = x;
      double dp = dx * dx - 1;
      double dq = dp / dn;
      i64 qpp = dq + 0.5;
      i64 rp = x * x - 1 - qpp * n;
      i64 r = (rp & 0x8000000000000000LL) ? rp + n : rp;
      x = r;
    } else {
      x = x * x - 1;
      x %= n;
    }
    hiter = hset.find(x);
    if (hiter == hset.end())
      hset.insert(x);
    else {
      // printf("hashset size %d\n", static_cast<int>(hset.size()));
      return 0; // loop detected but still no factors found hopeless
    }
    if (x < 0)
      x += n;
    i64 delta = y - x;
    if (delta < 0)
      delta = -delta;
    i64 d = gcd(delta, n);
    if (d != 1 && d != n) {
      if (debug)
        printf("DEBUG %d %lld %lld \n", iter, n, d);
      // printf("hashset size %d\n", static_cast<int>(hset.size()));
      return d;
    }
    if (i == k) {
      y = x;
      k <<= 1;
    }
  }
  // printf("hashset size %d\n", static_cast<int>(hset.size()));
  return 0;
}

// the factors are from small to large
// first is prime number, second is power
void factor_using_table(i64 n, IntPairVec &vpairs, const vector<int> &ftable) {
  vpairs.clear();
  int pwr = 0;
  int curr_fac = ftable[n];
  while (curr_fac > 1) {
    ++pwr;
    n /= ftable[n];
    while (curr_fac == ftable[n]) {
      ++pwr;
      n /= ftable[n];
    }
    vpairs.push_back(IntPair(curr_fac, pwr));
    curr_fac = ftable[n];
    pwr = 0;
  }
}
// input is a combination of  0, 1, ..., k-1(distinct) from 0 -- n-1,
// return the next combination
// the maximum for each bit is n-k,..., n-1
bool next_combination(vector<int> &cvec, int n, int k) {
  assert(static_cast<int>(cvec.size()) == k);
  assert(n >= k);
  int i = 0;
  ++cvec[k - 1];
  while (i <= k - 1 && cvec[k - 1 - i] > n - 1 - i) {
    ++i;
    if (k - 1 - i >= 0)
      ++cvec[k - 1 - i];
  }
  if (i > k - 1) {
    for (int i = 0; i < k; ++i)
      cvec[i] = i;
    return false;
  }
  // key part of the function
  assert(k >= i);
  for (int j = i; j >= 1; --j) {
    cvec[k - j] = cvec[k - j - 1] + 1;
  }
  if (cvec[0] > n - k) {
    for (int i = 0; i < k; ++i)
      cvec[i] = i;
    return false;
  } else
    return true;
}

bool isPermutation(i64 im, i64 in) {
  if ((im - in) % 9)
    return false;
  vector<int> digits;
  digits.resize(10, 0); // 0----9
  while (im) {
    int res = im % 10;
    ++digits[res];
    im /= 10;
  }
  while (in) {
    int res = in % 10;
    if (digits[res] == 0)
      return false;
    --digits[res];
    in /= 10;
  }

  return true;
}

// not bad!
bool isPalindromic(i64 num, int base) {
  int nr = 0;
  if (num % base == 0)
    return false;
  while (num > 0) {
    nr *= base;
    int res = num % base;
    nr += res;
    num /= base;
  }
  return (num == nr);
}
// find the position of the elem
int binary_find(int num, vector<int> &vec) {
  if (vec.empty())
    return -1;
  unsigned int head = 0;
  unsigned int tail = vec.size() - 1;
  while (head < tail) {
    int mid = (head + tail) / 2;
    if (vec[mid] == num)
      return mid;
    else if (vec[mid] < num) {
      head = mid + 1;
    } else { // mid > num
      tail = mid - 1;
    }
  }
  assert(head == tail);
  if (vec[head] == num)
    return head;
  else
    return -1;
}

// did not find too much difference in my two versions
//  a * x + b * y = gcd
//  x y maybe negative
//  x y gcd are output and a b are input
void extended_euclid(i64 a, i64 b, i64 &x, i64 &y, i64 &gcd) {
  if (b == 0) {
    gcd = a;
    x = 1;
    y = 0;
  } else {
    i64 residue = a % b;
    extended_euclid(b, residue, x, y, gcd);
    i64 tp = x;
    x = y;
    y = tp - (a / b) * y;
  }
}
void extended_euclid2(i64 a, i64 b, i64 &x, i64 &y, i64 &gcd) {
  if (b == 0) {
    gcd = a;
    x = 1;
    y = 0;
  } else if (b == 1) {
    gcd = 1;
    x = 0;
    y = 1;
  } else if (a % b == 0) {
    gcd = b;
    x = 0;
    y = 1;
  } else {
    i64 q = 0;
    i64 v[9] = {a, 1, 0, b, 0, 1, 1, 0, 0};
    i64 *va = &v[0];
    i64 *vb = &v[3];
    i64 *vc = &v[6];
    while (vc[0]) {
      q = va[0] / vb[0];
      for (unsigned int i = 0; i < 3; ++i) {
        vc[i] = va[i] - q * vb[i];
      }
      if (vb[0] % vc[0] == 0)
        break;
      swap(va, vb);
      swap(vb, vc);
    }
    x = vc[1];
    y = vc[2];
    gcd = vc[0];
  }
  // assert(a*x+b*y==gcd);//may fail if x and y are huge
}

// Sometimes a series numbers are in quadratic form, so with
// this function, we can sieve out those numbers that are composite.
// if the boolean returned is false, it means no solutiona available for
// the quadratic mod equation n^2 = residue(mod prime);
// otherwise the solution is in "sol"
bool tonelli_shank(i64 prime, i64 residue, i64 &sol) {
  sol = 0;

  assert(prime & 1);
  i64 pow = (prime - 1) / 2;
  if (powermodule(residue, pow, prime) != 1)
    return false;
  int s = 0;
  i64 q = prime - 1;
  while ((q & 1) == 0) {
    ++s;
    q >>= 1;
  }
  if (s == 1) {
    pow = (prime + 1) / 4;
    sol = powermodule(residue, pow, prime);
    return true;
  } else {
    bool found = false;
    i64 z = 0;
    // old trial and error method for non residual
    // for(i64 i = 2; i < prime -1; ++i){
    //     i64 ret = powermodule(i, (prime-1)/2, prime);
    //     if(ret == prime-1){
    //         z = i;
    //         found = true;
    //         break;
    //     }
    // }
    // following jacobi symbol is from PE problem 216
    //  stubbscroll in page 5 of the discussion
    for (z = 3; z < prime - 1; z += 2) {
      if (jacobi(z, prime) == -1) {
        found = true;
        break;
      }
    }
    assert(found == true);
    // old shank tonelli method
    i64 r = powermodule(residue, (q + 1) / 2, prime);
    i64 t = powermodule(residue, q, prime);
    i64 c = powermodule(z, q, prime); // equivalent to b ofsq
    i64 m = s;
    i64 b = 0;
    while (t != 1) {
      int ix = 0;
      i64 t1 = t;
      while (t1 != 1) {
        t1 *= t1;
        t1 %= prime;
        ++ix;
        assert(ix < m);
      }
      int px = m - ix - 1;
      b = c;
      for (int j = 0; j < px; ++j) {
        b *= b;
        b %= prime;
      }

      r = r * b;
      r %= prime;
      c = b * b;
      c %= prime;
      t = t * c;
      t %= prime;
      m = ix;
    }
    sol = r;
    // from stubb
    // i64 b = powermodule(z,q, prime);
    // i64 r = powermodule(residue, (q+1)/2, prime);
    // i64 r2a = r*powermodule(residue,(q+1)/2-1,prime)%prime;
    // int J=0;
    // for(int i=0;i<s-1;i++) {
    //    i64 c=powermodule(b,2*J,prime);
    //    c=r2a*c%prime;
    //    c=powermodule(c,1ULL<<(s-i-2),prime);
    //    if(c==prime-1) J+=1ULL<<i;
    // }
    // sol =  r*powermodule(b,J,prime)%prime;
    return true;
  }
}
// factor_table_min is now renamed as min_factor_sieve
vector<int> min_factor_sieve(int nmax) {
  vector<int> ftable;
  ftable.resize(nmax + 1);
  for (unsigned int i = 1; i < ftable.size(); ++i)
    ftable[i] = i & 1 ? i : 2;

  int root = sqrt(nmax);

  for (int i = 3; i <= root; i += 2) {
    if (ftable[i] < static_cast<int>(i))
      continue;
    // i is a prime now.
    for (unsigned int j = i * i; j < ftable.size(); j += i << 1) {
      if (ftable[j] == j) // no smallest factor found yet.
        ftable[j] = i;
    }
  }
  return ftable;
}
// no even number in the table
void factor_using_table_odd(i64 n, IntPairVec &vpairs,
                            const vector<int> &ftable) {
  vpairs.clear();
  i64 n2 = 0;
  while ((n & 1) == 0) {
    n >>= 1;
    ++n2;
  }
  if (n2)
    vpairs.push_back(IntPair(2, n2));

  assert((n & 1) > 0);
  int np = (n - 1) >> 1;
  int pwr = 0;
  int curr_fac = ftable[np];
  while (curr_fac > 1) {
    ++pwr;
    n /= curr_fac;
    np = (n - 1) >> 1;
    while (curr_fac == ftable[np]) {
      ++pwr;
      n /= ftable[np];
      np = (n - 1) >> 1;
    }
    vpairs.push_back(IntPair(curr_fac, pwr));
    curr_fac = ftable[np];
    pwr = 0;
  }
}

// just for even numbers, need to double the space is not a good
// idea. let me try
vector<int> factor_table_min_odd(int nmax) {
  int nsize = (nmax + 1) / 2; // the numbers are 1 3 5 7 ...
  vector<int> ftable(nsize);
  for (unsigned int i = 0; i < ftable.size(); ++i)
    ftable[i] = (i << 1) + 1;

  int root = sqrt(nmax);

  for (int i = 1; i <= root; ++i) {
    int value = (i << 1) + 1;
    // already assigned a min factor to i, so it
    // is not a prime
    if (ftable[i] < value)
      continue;
    int start = (value * value - 1) >> 1;
    for (unsigned int j = start; j < ftable.size(); j += value) {
      if (ftable[j] > value)
        ftable[j] = value;
    }
  }
}
// if not necessary, use min, which is faster
void factor_table_max(int nmax, vector<int> &ftable) {
  ftable.resize(nmax + 1);
  for (unsigned int i = 1; i < ftable.size(); ++i)
    ftable[i] = i;

  for (unsigned int i = 2; i < ftable.size(); ++i) {
    if (ftable[i] < static_cast<int>(i))
      continue;
    for (unsigned int j = 2 * i; j < ftable.size(); j += i)
      ftable[j] = i; // overwrite to find the largest factor
  }
}
// quadratic reciprocity
// quadratic_residue_test(int num, int prime)
/*
//implement a 64 bit integer version Miller-Rabin primality test
//composite == 0 prime == 1
bool miller_rabin(i64 xn, unsigned int nsampling)
{
    for(unsigned int cnt = 0; cnt < nsampling; ++cnt){
      i64 xa = rand() %(xn-2)+2;//TODO refine this part since rand is not well
written assert(xa < 4000000000LL); if(witness(xa, xn)) return 0;
    }
    return 1;
}

bool witness(i64 xa, i64 xn)
{
    i64 xn1 = xn - 1;
    unsigned int expo = 0;
    while(xn1 % 2  == 0){
       xn1 = xn1 >> 1;
       ++expo;
    }
    //modular exponentiation
    i64 x0 = powermodule2(xa, xn1, xn);
    i64 x1;
    for(unsigned int i = 1; i <= expo; ++i){
        x1 = product_mod(x0, x0, xn);
        if(x1 == 1 && x0 != 1 && x0 != xn - 1)
            return 1;
        x0 = x1;
    }
    if(x1 != 1)
        return 1;
    return 0;
}

*/

// what is the upper limit with 6 smallest primes?
bool strong_pseudo_test(i64 p) {
  if (p == 2)
    return true;
  if (p % 2 == 0 || p == 1)
    return false;
  vector<int> vp = {2, 3, 5, 7, 11, 13};
  i64 p1 = p - 1;
  int o2 = 0;
  while (!(p1 & 1)) {
    p1 >>= 1;
    ++o2;
  }
  for (unsigned int i = 0; i < vp.size(); ++i) {
    if (!strong_pseudo_test_int(vp[i], p1, o2, p)) // true composite
      return false;
  }
  return true;
}

i64 mult64mod(i64 a, i64 b, i64 mod) {
  a %= mod;
  b %= mod;
  i64 ret = 0;
  i64 tmp = a;
  while (b) {
    if (b & 1) {
      ret += tmp;
      if (ret > mod)
        ret -= mod;
    }
    tmp <<= 1;
    if (tmp > mod)
      tmp -= mod;
    b >>= 1;
  }
  assert(ret < mod && ret >= 0);
  return ret;
}

i64 powermodule(i64 base, i64 expo, i64 module) {
  assert(expo >= 0);
  i64 result = 1;
  i64 cbase = base;
  while (expo) {
    int remainder = expo & 1;
    if (remainder) {
      result = mult64mod(result, cbase, module);
    }
    cbase = mult64mod(cbase, cbase, module);
    assert(cbase >= 0);
    expo >>= 1;
  }
  return result;
}

void farey_sequence(vector<IntPair> &vf, int nlimit, bool ascending) {
  vf.clear();
  int a = 0, b = 1, c = 1, d = nlimit;
  int k = 0;
  if (!ascending) {
    a = 1;
    b = 1;
    c = nlimit - 1;
    d = nlimit;
  }
  if (ascending) {
    vf.push_back(IntPair(0, 1));
  } else {
    vf.push_back(IntPair(1, 1));
  }

  while ((ascending && c <= nlimit) || (!ascending && a > 0)) {
    k = (nlimit + b) / d;
    int a1 = a, b1 = b;
    a = c;
    b = d;
    c = k * c - a1;
    d = k * d - b1;
    // if(a + b <=  nlimit)
    vf.push_back(IntPair(a, b));
  }
}

void prime_generate_sq2(i64 p, int &a, int &b) {
  assert((p - 1) % 4 == 0);
  i64 result = 0;
  for (i64 n = 2; n <= p - 2; ++n) {
    result = powermodule(n, (p - 1) / 4, p);
    i64 r2 = result * result;
    if ((r2) % p == 1)
      continue;
    else
      break;
  }
  double root = sqrt(p);
  i64 rk = p;
  i64 rk1 = result;
  i64 tp;
  while (rk >= root) {
    tp = rk % rk1;
    rk = rk1;
    rk1 = tp;
  }
  assert(rk * rk + rk1 * rk1 == p); // this is what this function about
  a = rk;
  b = rk1;
  if (a > b)
    swap(a, b);
}

// sieve version for totient
std::vector<int> TotientFunctions::totient_sieve_0(int nmax) {
  std::vector<int> totients(nmax + 1);
  // assign the coprime counts to n for totients[n]
  // but since even numbers will be divided by 2 anyway,
  // so it is handled at the very beginning.
  for (unsigned int i = 0; i < totients.size(); ++i)
    totients[i] = i & 1 ? i : i >> 1;

  // sieving start from 3, since prime 2 has been handled.
  for (unsigned int i = 3; i < totients.size(); i += 2) {
    if (totients[i] != i)
      continue;
    totients[i] = i - 1;
    for (unsigned int j = i << 1; j < totients.size(); j += i) {
      totients[j] -= totients[j] / i;
    }
  }
  return totients;
}

std::vector<int> TotientFunctions::totient_sieve_1(int nmax) {
  // smallest_factor_sieve
  std::vector<int> spf = min_factor_sieve(nmax);
  std::vector<int> totients(nmax + 1);
  for (unsigned int i = 0; i < totients.size(); ++i)
    totients[i] = i;

  for (unsigned int i = 2; i < totients.size(); ++i) {
    if (spf[i] == i) { // it is a prime
      totients[i] = i - 1;
    } else {
      int p = spf[i];
      int m = i / p;
      int factor = (spf[m] == p) ? p : p - 1;
      totients[i] = totients[m] * factor;
    }
  }
  return totients;
}

int jacobi(int a, int m) {
  int t = 1, z;
  a %= m;
  while (a) {
    int cnt = 0;
    while (!(a & 1)) {
      a >>= 1;
      ++cnt;
    }
    if ((cnt & 1) && (((m & 7) == 3 || (m & 7) == 5)))
      t = -t;
    z = a, a = m, m = z;
    if ((a & 3) == 3 && (m & 3) == 3)
      t = -t;
    a %= m;
  }
  if (m == 1)
    return t;
  return 0;
}

// It is not needed in linux or mac since we can use time command.
// double gettime() {
//   struct timeval t;
//   gettimeofday(&t, NULL);
//   return t.tv_sec + t.tv_usec / 1000000.;
// }

void xgcd(const i64 p, const i64 q, i64 &gcd, i64 &pcoeff, i64 &qcoeff) {
  i64 a[3];
  a[0] = 1;
  a[1] = 0;
  a[2] = p;
  i64 b[3];
  b[0] = 0;
  b[1] = -1;
  b[2] = q;
  while (a[2] != 0) {
    i64 k = b[2] / a[2];
    b[0] -= k * a[0];
    b[1] -= k * a[1];
    b[2] -= k * a[2];
    if (b[2] == 0) {
      b[0] = a[0];
      a[0] = 0;
      b[1] = a[1];
      a[1] = 0;
      b[2] = a[2];
      a[2] = 0;
    } else {
      i64 k = a[2] / b[2];
      a[0] -= k * b[0];
      a[1] -= k * b[1];
      a[2] -= k * b[2];
    }
  }
  gcd = b[2];
  pcoeff = b[0];
  qcoeff = b[1];
}

// TODO check numbers in vp has no common factors
i64 chinese_remainder_theorem(const vector<i64> &vp, const vector<i64> &vr) {
  i64 N = 1;
  for (unsigned int i = 0; i < vp.size(); ++i)
    N *= vp[i];
  i64 sum = 0;
  for (unsigned int i = 0; i < vp.size(); ++i) {
    i64 a = N / vp[i];
    i64 b = vp[i];
    i64 x = 1, y = 1, gcd = 1;
    extended_euclid(a, b, x, y, gcd);
    if ((a * x) % b != 1) {
      assert(x < 0);
      x += b;
      assert((a * x) % b == 1);
    }
    sum += vr[i] * a * x;
  }
  sum %= N;
  return sum;
}

// this function is now used for number that can be expressed as prime^power
// only
int find_multiplicative_order(i64 nbase, i64 prime, int np,
                              const vector<int> &vfac) {
  IntPairVec vpairs;
  assert(prime & 1);
  // find totient number
  i64 nmod = power(prime, (i64)np);
  int totient = nmod / prime * (prime - 1);

  // this is the factorization of the totient number
  factor_using_table(prime - 1, vpairs, vfac);
  if (np > 1)
    vpairs.push_back(IntPair(prime, np - 1));

  i64 result = 1;
  for (unsigned int i = 0; i < vpairs.size(); ++i) {
    int qi = vpairs[i].first;    // base
    int powi = vpairs[i].second; // power
    int yi = totient / power(qi, powi);
    int xi = powermodule((i64)nbase, (i64)yi, nmod);
    if (xi == 1)
      continue; // has nothing to do with this prime factor
    i64 t = xi;
    int cnt = 0;
    do {
      t = powermodule((i64)t, qi, nmod); // t^(q^n) == (t^q)^(q^(n-1)) !!!!!!
      ++cnt;
      assert(cnt <= powi);
    } while (t != 1);
    assert(t == 1);
    result *= power(qi, cnt);
  }
  return result;
}

// should be only used when overflow would not happen.
i64 product_mod(i64 n1, i64 n2, i64 mod) {
  n1 %= mod;
  n2 %= mod;
  n1 *= n2;
  n1 %= mod;
  return n1 >= 0 ? n1 : n1 + mod;
}

vector<i64> matrix_multiplication(const vector<i64> &A, const vector<i64> &B,
                                  i64 nmod, int dim) {
  vector<i64> C;
  C.resize(dim * dim, 0);
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      for (int k = 0; k < dim; ++k) {
        C[i * dim + j] += multmod(A[i * dim + k], B[k * dim + j], nmod);
        C[i * dim + j] %= nmod;
      }
    }
  }
  return C;
}

vector<i64> matrix_power(vector<i64> A, i64 np, i64 nmod, int dim) {
  vector<i64> base(A);
  vector<i64> result;
  result.resize(dim * dim, 0);
  for (int i = 0; i < dim; ++i)
    result[i * dim + i] = 1;
  while (np) {
    if (np & 1) {
      result = matrix_multiplication(result, base, nmod, dim);
    }
    base = matrix_multiplication(base, base, nmod, dim);
    np >>= 1;
  }
  return result;
}
