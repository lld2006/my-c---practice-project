#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <set>
using namespace std;
long long pp(long long a, int b) {
    long long ret = 1;
    for (int i=0; i<b; i++) ret *= a;
    return ret;
}
bool isprime(long long x) {
    if (x==1) return false;
    if (x%2==0) return x==2;
    for (long long y=3; y*y<=x; y+=2) if (x%y==0) return false;
    return true;
}
vector<long long> primes;
vector<long long> res;
void solve(int top, long long cur, long long rem) {
    if (rem==1) res.push_back(cur);
    for (int i=top-1; i>=0; i--) {
        long long p = primes[i];
        if (rem%(p-1)!=0) continue;
        solve(i,cur*p,rem/(p-1));
        long long trem = rem/(p-1);
        long long tcur = cur*p;
        while (trem%p==0) {
            trem/=p;
            tcur*=p;
            solve(i,tcur,trem);
        }
    }

}
int main() {
    for (int i=0; i<=10; i++)
    for (int j=0; j<=5; j++)
    for (int k=0; k<=2; k++)
    for (int l=0; l<=1; l++)
    for (int m=0; m<=1; m++)
    for (int n=0; n<=1; n++) {
        long long num = pp(2,i)*pp(3,j)*pp(5,k)*pp(7,l)*pp(11,m)*pp(13,n);
        if (isprime(num+1)) {primes.push_back(num+1);}
    }
    sort(primes.begin(),primes.end());
    printf("%zu\n", primes.size());
    res.clear();
    solve(primes.size(),1,6227020800LL);
    sort(res.begin(),res.end());
    printf("%lld\n",res[149999]);
}
