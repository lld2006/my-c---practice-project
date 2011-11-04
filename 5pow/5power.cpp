#include <cstdio>
#include <vector>

using namespace std;

int main()
{
   vector<int> nvec;
   for(int n =2; n<=999999; ++n)
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
        for(int i=0; i<nvec.size(); ++i)
        {
          int vi = nvec[i];
          sum += vi*vi*vi*vi*vi;
        }
        if( sum == n)
          printf("%d\n", n);
   }
   return 0;
}
