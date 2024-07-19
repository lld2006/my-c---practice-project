#include "../lib/typedef.h"
#include <cstdio>
#include <vector>
using namespace std;
int main() {
  int target = 100;
  vector<long long int> vf(target + 1, 0);
  vf[0] = 1; // sum 
  for (int elem = 1; elem <= target; ++elem){
    for (int start = 0; start<=target -elem; ++start)
        vf[start+elem] += vf[start];
  }
  printf("%lld\n", vf[target]-1);
}
