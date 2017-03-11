#include <iostream>
#include <cmath>
using namespace std;

double h[21][21];
double mem[21][1<<21];

double f(int i, int s) {
   if ((s & s-1) == 0) {
      return 30+i;
   }

   if (mem[i][s] == 0) {
      mem[i][s] = 1e100;
      int ss = s ^ 1<<i;
      for (int j = 0; j < 21; j++) {
         if (ss & (1<<j)) {
            mem[i][s] = min(mem[i][s], f(j, ss) + h[i][j]);
         }
      }
   }
   return mem[i][s];
}

int main() {
   for (int i = 0; i < 21; i++) {
      for (int j = i+1; j < 21; j++) {
         int a = 100 - (30+i) - (30+j);
         int c = 30+i + 30+j;
         h[i][j] = h[j][i] = sqrt((double)c*c - a*a);
      }
   }

   double ans = 1e100;
   for (int i = 0; i < 21; i++) {
      ans = min(ans, f(i, (1<<21) - 1) + 30+i);
   }

   cout << (int)(ans*1000 + 0.5) << endl;
   return 0;
}
