#include <cassert>
#include <iostream>
typedef unsigned int uint;
typedef unsigned long long ull;
uint const N=2400;
uint const M=1000000007;

// A[k1][k2]: how many ways to have trios with k1x1 open slot, k2x2 open slots
uint A[N+1][N+1]={};
uint B[N+1][N+1]={};

void wat(uint s1, uint s2, uint k=0, uint b1=0, uint b2=0, uint n=1)
{
	if(k<4)
	{
		if(0<s1)
			wat(s1-1,s2,k+1,b1,b2,ull(n)*s1%M);
		if(0<s2)
			wat(s1,s2-1,k+1,b1+1,b2,ull(n)*s2%M);
		wat(s1,s2,k+1,b1,b2+1,n);
	}
	else
	{
		uint n1=s1+b1;
		uint n2=s2+b2;
		assert(n1<=N);
		assert(n2<=N);
		B[n1][n2]=(B[n1][n2]+n)%M;
	}
}

main()
{
	A[0][4]=1;
	for(uint n=4; n<N; n+=4)
	{
		for(uint k1=0; k1<=N; ++k1)
			for(uint k2=0; k2<=N; ++k2)
				B[k1][k2]=0;
		for(uint k1=0; k1<=N; ++k1)
			for(uint k2=0; k2<=N; ++k2)
				if(A[k1][k2])
					wat(k1,k2,0,0,0,A[k1][k2]);
		uint m=N-n;
		for(uint k1=0; k1<=N; ++k1)
			for(uint k2=0; k2<=N; ++k2)
				if(k1+k2*2<=m)
					A[k1][k2]=B[k1][k2];
				else A[k1][k2]=0;
	}
	std::cout << A[0][0] << std::endl;
}
