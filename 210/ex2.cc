#include <cmath>
#include <cstdio>
int main() {
  long long k=250000000, c=0;
  k = 4;
  long long RR=k*k/2, R=sqrt(RR);
  long long x,xx, y=k/2, yy=(y+1)*(y+1);
  for(x=k/2, xx=x*x; x; x--, xx-=2*x+1){
    if(xx+yy<RR) {
      y++; yy+=2*y+1;
    };
    c+=y-x;
  }
  
  printf("%lld %lld\n",24*k*k+8*c+4*R+(k-2), c);
}
