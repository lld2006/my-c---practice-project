#include <cstdio>
#include <vector>
using namespace std;
int main() {
  int limit = 12000;
  int topmax = 0;
  vector<int> stack;
  stack.resize(limit, 0);
  int left = 2, right = 3;
  int top = 0;
  int cnt = 0;
  while (true) {
    if (topmax < top)
      topmax = top;
    if (top < 0)
      break;
    int median = left + right;
    if (median <= limit) {
      stack[top++] = right;
      right = median;
      ++cnt;
    } else {
      left = right;
      right = stack[--top];
    }
  }
  printf("%d %d\n", cnt, topmax);
}
