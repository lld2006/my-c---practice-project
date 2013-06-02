//---------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <time.h>
#include "../lib/typedef.h"

int gcd(int a, int b) {
  int c = 0;
  while (b) {
     c = a % b;
     a = b;
     b = c;
  }
  return a;
}

int main()
{
int N=1200;
int N2=N*N, NN=0,x,y;
for( x=-N;x<N;x++)
for( y=0;y<N;y++)
        {
        if(y==0&&x<=0) continue;
        if (x*x+y*y<N2)NN++;
        }
i64 N3=1;
N3=N3*NN*(NN-1)*(NN-2)/6;

i64 bad2=0,bad3=0;
int b1=N-1;
i64 b2=b1*(b1-1)/2;
int b3=b2*(b1-2)/3;
bad2+=b2*(NN-b1);
bad3+=b3;
int x2,y2,r2;
for( x=x2=1;x<N;x++,x2=x*x)
for( y=y2=1;y<N;y++,y2=y*y)
if ((r2=x2+y2)*4<N2)
if (gcd(x,y)==1)
        {
        b1=2;
        while(r2*b1*b1<N2)b1++;
        b1--;
        b2=b1*(b1-1)/2;
        b3=b2*(b1-2)/3;
        bad2+=b2*(NN-b1);
        bad3+=b3;
        }
cout<<(N3-(bad2+bad3)*2)*2;
}
