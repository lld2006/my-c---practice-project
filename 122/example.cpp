#include <cstdio>
int cost[7000], p[7000];
int target = 6000;

int min(int a, int b){ return a < b ? a : b; }
void bt(int power, int depth){
   if(power > target || depth > cost[power]) return;
   cost[power] = depth;
   p[depth] = power;
   for(int i = depth; i >= 0; --i)
      bt(power + p[i], depth + 1);
}
int main(void){
   int ans = 0;
   //clock_t start = clock();
   for(int i = 0; i <= target; ++i) cost[i] = 1024;
   bt(1, 0);
   for(int i = 1; i <= target; ++i) ans += cost[i];
   printf("Answer: %d\n", ans);
   //printf("Elapsed time: %.6lfs\n", (clock() - start) / double(CLOCKS_PER_SEC));

   return 0;
}
