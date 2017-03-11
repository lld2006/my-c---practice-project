#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

const int U = 100000;
using namespace std;

typedef long long ll;
double s = 0;

inline bool lt(ll x, ll y, ll z, ll u) {
  if (x < z) return true;
  if (x == z && y < u) return true;
  return false;
}

inline bool isSq(ll x) {
  ll s = sqrt(x);
  return x == s*s;
}

inline bool valid(ll x, ll y, ll z, ll u) {
  ll v = 5-x-z, w = -y-u;
  if (lt(x, y, z, u) && lt(z, u, v, w)) {
    return x*x + y*y == v*v + w*w;
  }
  return false;
}

inline double dist(ll x, ll y, ll z, ll u) {
  return sqrt( (x-z)*(x-z) + (y-u)*(y-u) );
}

inline double perimeter(ll x, ll y, ll z, ll u) {
  ll v = 5-x-z, w = -y-u;
  return
    dist(x, y, z, u) +
    dist(z, u, v, w) +
    dist(v, w, x, y);
}

inline void update(ll x, ll y, ll z, ll u) {
  if (valid(x, y, z, u)) {
    double p = perimeter(x, y, z, u);
    if (p <= U) s += p;
    }
}

inline void check(ll x, ll y, ll a, ll n) {
  if (n % (2*a) == 0) {
    ll z = n / (2*a), u = sqrt(x*x+y*y-z*z);
    if (x*x + y*y == z*z + u*u) {
      update(x, y, z, u);
      if (u != 0) update(x, y, z, -u);
    }
  }
}

int main() {
  cout << fixed << setprecision(4);
  for (ll x = -U/3-5; x <= U/3+5; ++x) {
    if (x % 1000 == 0) cout << "x = " << x << ", s = " << s << endl;
    for (ll y = 0; y <= U/3-abs(x); ++y) {
      if (x == 5 && y == 0) continue;
      ll a = (x-5)*(x-5)+y*y, d = a*(3*x*x+10*x+3*y*y-25);
      if (!isSq(d)) continue;
      check(x, -y,  a, -(x-5)*a - y * sqrt(d));
      if (y == 0 || d == 0) continue;
      check(x, -y, a, (5-x)*a + y * sqrt(d));
      check(x,  y, a, (5-x)*a - y * sqrt(d));
      check(x,  y, a, (5-x)*a + y * sqrt(d));
    }
  }
  cout << s << endl;
}
