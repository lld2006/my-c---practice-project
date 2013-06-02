#include <iostream>

using namespace std;

const int ramp = 55;
const long mod = 1000000;

int pm = 524287;
int nxt[mod];
int sz[mod];

int maxcomp_size = 1;
int maxcomp = 0;
int misdials = 0;

int add(int x, int y) {
    if (x == y) {
        ++misdials;
        return 0;
    }
    int ox = x, oy = y;

    while (nxt[x] != x) x = nxt[x];
    while (nxt[y] != y) y = nxt[y];
    if (x == y) return 0;

    if (sz[x] > sz[y]) swap(x, y);
    nxt[x] = y;
    sz[y] += sz[x];
    if (sz[y] > maxcomp_size) {
        maxcomp = y;
        maxcomp_size = sz[y];
    }

    int t;
    while (nxt[ox] != ox) { t = ox; ox = nxt[ox]; nxt[t] = y; }
    while (nxt[oy] != oy) { t = oy; oy = nxt[oy]; nxt[t] = y; }

    return 1;
}

int main() {
    for (int i = 0; i < mod; ++i) {
        nxt[i] = i;
        sz[i] = 1;
    }

    int S1 = 0;
    int S2 = 0;
    long k;
    long ks[ramp];
    long edges = 0;
    for (k = 1; k <= ramp; k++) {
        S1 = S2;
        S2 = (100003L - k*(200003L - 300007L*k*k)) % mod;
        ks[(k-1)%ramp] = S2;
        if (0 == k % 2) {
            edges += add(S1, S2);
        }
    }

    for (;; k++) {
        S1 = S2;
        S2 = (ks[(k-25)%ramp] + ks[(k-56)%ramp]) % mod;
        ks[(k-1)%ramp] = S2;
        if (0 == k % 2) {
            edges += add(S1, S2);
            // check
            if (100*maxcomp_size >= 99*mod) {
                int p = pm;
                while (nxt[p] != p) p = nxt[p];
                if (p == maxcomp) {
                    cout << "\n\n" << (k/2 - misdials) << " edges; " << edges << " MST edges; "
                         << maxcomp_size << " maximum component size\n\n";
                    return 0;
                }
            }
        }
    }
}
