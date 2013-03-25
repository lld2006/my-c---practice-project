#include <cstdio>
#include <vector>
using namespace std;
int SumOfFactDigits34(int n)
{
   static const int facts[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
   int sum = 0;

   while (n > 0)
   {
      sum += facts[n % 10];
      n /= 10;
   }

   return sum;
}

void Problem34()
{
    int total = 0;
   for (int n = 10; n < 362880 * 7; n++)
   {
      if (SumOfFactDigits34(n) == n)
          total += n;
   }
   printf("%d\n", total);
}
int main()
{
    Problem34();
}
