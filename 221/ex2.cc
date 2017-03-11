#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

set<long long> ans;

const int limit = 150000;

long long sieve[limit+1];

vector<long long> pdivs[limit+1]; // array of vectors

void dfs(long long num, int ind, long long div, long long div2)
{
        if(div > num) return;
        if(ind == pdivs[num].size()) {
                long long p = num + div;
                long long q = num + div2;
                if ( LLONG_MAX/p/q/num < 1000) return;
                ans.insert(p*q*num);
                if(ans.size() > limit)
                        ans.erase(--ans.end());
                return;
        }

        dfs(num,ind+1,div,div2);
        while(div2 % pdivs[num][ind] == 0)
        {
                div2 /= pdivs[num][ind];
                div *= pdivs[num][ind];
                dfs(num,ind+1,div,div2);
        }
}

int main()
{
        sieve[0] = 1;
        for(int n = 1; n <= limit; n ++) {
                sieve[n] = n*(long long)n + 1;// original value n^2+1
        }
        for(int n = 1; n <= limit; n ++) {
                if(sieve[n] < 2) continue;
                pdivs[n].push_back(sieve[n]); //for each 
                if(sieve[n] > limit) continue;
                for(int j = n + sieve[n]; j <= limit; j += sieve[n]) {
                        if (sieve[j] % sieve[n] == 0) {
                                pdivs[j].push_back(sieve[n]);
                        }
                        while(sieve[j] % sieve[n] == 0) {
                                sieve[j] /= sieve[n];
                        }
                }
        }

        for(long long r = 1;r < limit; r++)
        {
                dfs(r, 0, 1, r*r+1);
        }
        printf("%d: %lld\n",(int)ans.size(), *ans.rbegin());
        return 0;
}
