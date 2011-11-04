#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
void primeWithin( vector<int>& vecr, int limit)
{
    int odd = (limit-1)/2;
    vector<int> vec; 
    vec.resize(odd+1);
    vec[0] = 0;
    for(int i = 1; i< odd+1; ++i)
    {
      vec[i] = 1; //for i >=1 number represent 2i+1; 
                  // assume all prime
    }
    int ip= 1;  // prime number from 2 3 5 ....
    int factor = 2*ip+1;
    int max = sqrt((double) limit)+1;
    printf(" %d\n", max);
    while( factor <= max)
    {
      // sieve
        for(int i =ip+1; i < odd+1; ++i)
          if( (2*i+1) % factor ==0)
            vec[i] = 0;
      //find next prime
        ++ip;
        while(vec[ip] == 0)
        { 
          ++ip;
        }
        factor = 2*ip+1;
    }
    vecr.push_back(2);
    for( int i = 1; i< odd+1; ++i)
      if( vec[i] == 1)
	{
        vecr.push_back(2*i+1);
	}
}

int main()
{
    vector<int> prime;
    vector<int> factor;
    primeWithin(prime, 1000000);
    int trinum = 0;
    for(int i = 3; i < 20000; ++i)
    {
      factor.clear();
      trinum = i*(i+1)/2;
      int limit = sqrt((double)trinum);
      //calculate prime factors
      while(true)
      {
        int tri = trinum;
        for(int pi =0 ; pi < static_cast<int>(prime.size()); ++pi)
        {
            if(prime[pi] > limit) break;
            int count = 0;
            while( tri%prime[pi] == 0)
            {
              tri /= prime[pi];
              ++count;
            } 
            if(count > 0) factor.push_back(count);
        }
	//if( tri != 1)printf("trinum =%d tri=%d\n", trinum, tri);
	//assert(tri == 1);
	if(tri == 1)
	  break;
	else
	  {
	    factor.push_back(1);
	    break;
	  }
      }
      int product = 1;
      for( int j = 0; j<factor.size(); ++j)
        product *= (factor[j]+1);
      printf("trinum = %d product is %d\n", trinum, product);
     if( product > 500) break;   
    }
    printf("the first triangle number is %d\n", trinum);
}

