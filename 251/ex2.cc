
#include <iostream>
#include <cmath>
using namespace std;

static const long long u = 110000000;

int gcd(int a, int b) {
  return b != 0 ? gcd(b, a % b) : a;
}

void extGcd(int a, int b, int& x, int& y) {
  if (b == 0) { x = 1, y = 0; return;}
  extGcd( b, a % b, y, x ), y -= a / b * x;
}

int main(){
  long long count = 0;
  for (long long n = 1, n_max = sqrt(u / 5); n <= n_max; n++) // I think l >= 5, but no proof...
    for (long long d = 1, d_max = sqrt(u - 5 * n * n - n); d < d_max; d += 2) {
      if (gcd(d, n) != 1) continue;
      int q, l;
      extGcd(d, 8 * n, q, l); // q = d ^ (-1) (mod 8 * n)
      l = -3 * q * q % (8 * n); l += l < 0 ? 8 * n: 0;
      long long c = u + 1 - (3 * n + d) * (d * d * l + 3) / (8 * n) - n * n * l;
      count += c >= 0 ? c / (8 * n * n * n + (3 * n + d) * d * d) + 1: 0;
    }
  cout << count << endl;
}
