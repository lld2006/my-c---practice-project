#include <stdio.h>
enum {
  LIM = 200000,
};
int main() {
  int n2[LIM + 1], n5[LIM + 1];
  n2[0] = n5[0] = 0;
  for(int i = 1; i <= LIM; i++) {
    n2[i] = n2[i - 1];
    n5[i] = n5[i - 1];
    int n = i;
    while(!(n & 1)) n2[i]++, n >>= 1;
    while(!(n % 5)) n5[i]++, n /= 5;
  }
  int count = 0;
  for(int a = (LIM / 3) + 1; a <= LIM - 2; a++) {
    int t5 = n5[LIM] - n5[a];
    if (t5 < 12) continue;
    int t2 = n2[LIM] - n2[a];
    if (t2 < 12) continue;
    int aa = LIM - a;
    int b = aa < a ? aa : a;
    for(;;) {
      int c = aa - b;
      if (b < c) break;
      if (t5 - n5[b] - n5[c] >= 12 && t2 - n2[b] - n2[c] >= 12) {
            if (a == b) {
              count += (b == c) ? 1 : 3;
            } else {
              count += (b == c) ? 3 : 6;
            }
      }
      b--;
    }
  }
  printf("%d\n", count);
  return 0;
}
