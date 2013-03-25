#include <cstdio>
#include <vector>

using namespace std;

int main()
{
   int total = 0;
   vector<int> nvec;
   //354294=6*9^5
   for(int n =2; n<=354294; ++n)
   {
        nvec.clear();
	int n0=n;
        while(n0)
        {
          int res = n0%10;
          n0 = n0/10;
          nvec.push_back(res);
        }
        int sum = 0;
        for(unsigned int i=0; i<nvec.size(); ++i)
        {
          int vi = nvec[i];
          sum += vi*vi*vi*vi*vi;
        }
        if( sum == n){
          //printf("%d\n", n);
          total += n;
        }
   }
   printf("%d\n", total);
   return 0;
}
