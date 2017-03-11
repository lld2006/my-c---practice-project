#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

const int U = 100000;
using namespace std;

typedef long long ll;
double sum = 0;

inline bool lt(ll x, ll y, ll z, ll u) {
  if (x < z) return true;
  if (x == z && y < u) return true;
  return false;
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

inline void update(ll x, ll y, ll z, ll u) {
  if (valid(x, y, z, u)) {
    double p = dist(x, y, z, u)
      + dist(z, u, 5-x-z, -y-u)
      + dist(5-x-z, -y-u, x, y);
    if (p <= U) {
      sum += p;
      cout << "(" << setw(6) << x << "," << setw(6) << y << "), "
           << "(" << setw(6) << z << "," << setw(6) << u << "), "
           << "(" <<  setw(6) << 5-x-z << "," << setw(6) << -y-u << "), "
           << "p = " << p << endl;
           // << ", r = " << x*x+y*y << endl;
    }
  }
}

inline void search(ll x, ll g, ll y0) {
  for (ll y = y0; y <= g; y+=5) {
    ll a = (x-5)*(x-5)+y*y, d = a*(3*x*x+10*x+3*y*y-25), sd = sqrt(d);
    if (d != sd*sd) continue;
    ll n = -(x-5)*a - y * sd;
    if (n % (2*a) != 0) continue;
    ll z = n / (2*a), u = sqrt(x*x+y*y-z*z);
    if (x*x + y*y != z*z + u*u) continue;
    update(x,  y, z, u);
    if (y > 0) update(x, -y, z, u);
    if (u != 0) update(x, y, z, -u);
    if (y > 0 && u != 0) update(x, -y, z, -u);
  }
}

int main() {
  cout << fixed << setprecision(4);
  for (ll x = -U/3-5; x <= 1; ++x) {
    if (x % 1000 == 0) cout << "x = " << x << ", sum = " << sum << endl;
    double g = min((double)U/3-abs(x), sqrt(x*(3*x-20)+25));
    switch (x*x % 5) {  // observation: 5 | x*x+y*y, I don't have proof.
    case 1: search(x, g, 2), search(x, g, 3);
      break;
    case 4: search(x, g, 1), search(x, g, 4);
      break;
    case 0: search(x, g, 0);
      break;
    }
   }
  cout << sum << endl;
}
